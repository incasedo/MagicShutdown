// CFPSMiniCalendarCtrl
// Author:	Matt Gullett
//			gullettm@yahoo.com
// Copyright (c) 2002
//
// This is a back-end utility class implementing support for date
// recurrence patterns.
// The implementation is based on MS Outlook with numerous enhancements.
//
// You may freely use this source code in personal, freeware, shareware
// or commercial applications provided that 1) my name is recognized in the
// code and if this code represents a substantial portion of the application
// that my name be included in the credits for the application (about box, etc)
//
// Use this code at your own risk.  This code is provided AS-IS.  No warranty
// is granted as to the correctness, usefulness or value of this code.
//
// Special thanks to Keith Rule for the CMemDC class
// http://www.codeproject.com/gdi/flickerfree.asp
//
// *******************************************************************
// TECHNICAL NOTES:
//
// See .cpp file for tech notes
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FPSRecurringDates.h"

#include "OleDateTimeEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// allocate static members
CString CFPSRecurringDates::m_strDefaultStartTime = "08:00 AM";
CString CFPSRecurringDates::m_strDefaultEndTime = "08:30 AM";


//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////
CFPSRecurringDates::CFPSRecurringDates()
{
	// basic control options
	COleDateTimeEx dt = COleDateTime::GetCurrentTime();
	m_sBasicMethod = FPSDATE_RECUR_BASE_METHOD_DAILY;
	m_strStartTime = m_strDefaultStartTime;
	m_strEndTime = m_strDefaultEndTime;
	m_sEndMethod = FPSDATE_RECUR_END_METHOD_NONE;
	m_iEndOccurences = 10;
	m_strStartDate = dt.Format(dt.GetSystemShortDateFormat());

	dt += 14;
	m_strEndDate = dt.Format(dt.GetSystemShortDateFormat());

	// reformat time variables
	dt.ParseDateTime(m_strStartTime);
	m_strStartTime = dt.Format("%X");

	dt.ParseDateTime(m_strEndTime);
	m_strEndTime = dt.Format("%X");

	// daily control options
	m_sDailyMethod = FPSDATE_RECUR_DAILY_METHOD_EVERY_X_DAYS;
	m_iEveryXDayCount = 1;

	// weekly control options
	m_iEveryWeekCount = 1;
	m_bWeeklySunday = FALSE;
	m_bWeeklyMonday = FALSE;
	m_bWeeklyTuesday = FALSE;
	m_bWeeklyWednesday = FALSE;
	m_bWeeklyThursday = FALSE;
	m_bWeeklyFriday = FALSE;
	m_bWeeklySaturday = FALSE;

	// default to current day of week
	switch (COleDateTime::GetCurrentTime().GetDayOfWeek())
	{
	case 1: {m_bWeeklySunday = TRUE; break;}
	case 2: {m_bWeeklyMonday = TRUE; break;}
	case 3: {m_bWeeklyTuesday = TRUE; break;}
	case 4: {m_bWeeklyWednesday = TRUE; break;}
	case 5: {m_bWeeklyThursday = TRUE; break;}
	case 6: {m_bWeeklyFriday = TRUE; break;}
	case 7: {m_bWeeklySaturday = TRUE; break;}
	}

	// monthly control options
	m_sMonthlyMethod = FPSDATE_RECUR_MONTHLY_METHOD_OPTION_1;
	m_iMonthlyCount1 = 1;
	m_iMonthlyCount2 = 1;
	m_iMonthlyTheOption = FPSDATE_RECUR_WEEK_FIRST;
	m_iMonthlyDayOption = FPSDATE_RECUR_SKIP_METHOD_NEXT_DAY;
	m_iMonthlyCount3 = 1;

	m_iMonthlyTheOption1 = FPSDATE_RECUR_WEEK_FIRST;
	m_iMonthlyDayOption1 = FPSDATE_RECUR_SKIP_METHOD_NEXT_DAY;
	m_iMonthlyCount4 = 1;
	m_iMonthlyMathOp = 0;
	m_iMonthlyMathDays = 1;

	// yearly control options
	m_sYearlyMethod = FPSDATE_RECUR_YEARLY_METHOD_OPTION_1;
	m_iYearlyMonth1 = COleDateTime::GetCurrentTime().GetMonth();
	m_iYearlyMonthDay = 1;
	m_iYearlyTheOption = FPSDATE_RECUR_WEEK_FIRST;
	m_iYearlyDayOption = FPSDATE_RECUR_SKIP_METHOD_NEXT_DAY;
	m_iYearlyMonth2 = COleDateTime::GetCurrentTime().GetMonth();
}

//////////////////////////////////////////////////////////////////////
// Destruction
//////////////////////////////////////////////////////////////////////
CFPSRecurringDates::~CFPSRecurringDates()
{
	ClearBlackOutDates();
	ClearSkipDates();
}


CString CFPSRecurringDates::CStr(long lValue)
{
	char szValue[20];

	_ltoa(lValue, szValue, 10);

	return szValue;
}


//////////////////////////////////////////////////////////////////////
// cleanup memory used by black out dates list
//////////////////////////////////////////////////////////////////////
void CFPSRecurringDates::ClearBlackOutDates()
{
	m_BlackOutDates1.RemoveAll();
}

// cleanup memory used by skip dates
void CFPSRecurringDates::ClearSkipDates()
{
	POSITION Pos = m_SkipDates.GetHeadPosition();
	while (Pos)
	{
		CFPSRecurringDate_Skip* pEntry = m_SkipDates.GetNext(Pos);
		ASSERT(pEntry);

		if (pEntry)
			delete pEntry;
	}
	m_SkipDates.RemoveAll();
}

void CFPSRecurringDates::RemoveBlackOut(COleDateTime& dt)
{
	CString strDate = dt.Format("%B %d %Y");
	POSITION Pos = m_BlackOutDates1.Find(strDate);

	if (Pos)
		m_BlackOutDates1.RemoveAt(Pos);
}

void CFPSRecurringDates::RemoveSkip(CFPSRecurringDate_Skip* pEntry)
{
	if (pEntry)
	{
		POSITION Pos = m_SkipDates.Find(pEntry);
		ASSERT(Pos);

		if (Pos)
		{
			m_SkipDates.RemoveAt(Pos);
			delete pEntry;
		}
	}
}

BOOL CFPSRecurringDates::GetBuiltInDate(int iType, COleDateTime &dt, int iYear)
{
	BOOL bReturn = FALSE;
	COleDateTimeEx dtTemp;

	dtTemp.GetBuiltInValue(iType, iYear);

	if (dtTemp.GetStatus() == COleDateTime::valid)
	{
		dt = dtTemp;
		bReturn = TRUE;
	}

	return bReturn;
}

void CFPSRecurringDates::CleanupDateList(CPtrList &List)
{
	POSITION Pos = NULL;
	COleDateTime* pDate = NULL;

	Pos = List.GetHeadPosition();
	while (Pos)
	{
		pDate = (COleDateTime*)List.GetNext(Pos);
		ASSERT(pDate);

		if (pDate)
			delete pDate;
	}

	List.RemoveAll();
}

BOOL CFPSRecurringDates::IsDateInPattern(COleDateTime &dtCheck)
{
	BOOL bReturn = FALSE;
	CPtrList List;

	if (GeneratePattern(List, dtCheck))
		bReturn = IsDateInPattern(List, dtCheck);

	CleanupDateList(List);

	return bReturn;
}

BOOL CFPSRecurringDates::IsDateInPattern(CPtrList& List, COleDateTime &dtCheck)
{
	BOOL bReturn = FALSE;
	POSITION Pos = NULL;
	COleDateTime* pDate = NULL;

	Pos = List.GetHeadPosition();
	while (Pos && !bReturn)
	{
		pDate = (COleDateTime*)List.GetNext(Pos);
		ASSERT(pDate);

		if (pDate)
		{
			if (*pDate == dtCheck)
				bReturn = TRUE;
		}
	}

	return bReturn;
}

// ************************************************************
// BEGIN
// utility methods used when generating the pattern
// ************************************************************
BOOL CFPSRecurringDates::IsDateBlackedOut(COleDateTime &dtCheck)
{
	BOOL bReturn = FALSE;
	CString strDate = dtCheck.Format("%B %d %Y");

	if (m_BlackOutDates1.Find(strDate))
		bReturn = TRUE;

	return bReturn;
}

BOOL CFPSRecurringDates::IsDateSkipped(COleDateTime &dtCheck, short& sSkipMethod)
{
	BOOL bReturn = FALSE;
	sSkipMethod = FPSDATE_RECUR_SKIP_METHOD_SKIP;

	POSITION Pos = m_SkipDates.GetHeadPosition();
	while (Pos && !bReturn)
	{
		CFPSRecurringDate_Skip* pEntry = m_SkipDates.GetNext(Pos);

		if (pEntry->m_bEnabled)
		{
			COleDateTime dt;

			// determine the date used by the skip pattern.  Built in dates
			// are calculated dates such as (Christmas, easter, new years,
			// etc.)
			if (pEntry->m_iDateOption == 0)
				dt.ParseDateTime(pEntry->m_strDate);
			else
				GetBuiltInDate(pEntry->m_iDateOption, dt, dtCheck.GetYear());

			// if matches, return TRUE and set desired skip method
			if (dt.GetStatus() == COleDateTime::valid && dtCheck == dt)
			{
				sSkipMethod = pEntry->m_sSkipMethod;
				bReturn = TRUE;
			}
		}
	}

	return bReturn;
}
void CFPSRecurringDates::ProcessSkip(COleDateTimeEx &dtWorking, short sSkipMethod, CPtrList &List, COleDateTimeEx& dtLast, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	switch (sSkipMethod)
	{
	case FPSDATE_RECUR_SKIP_METHOD_SKIP:
		{
			// do nothing, since this is a total skip
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_DAY:
		{
			dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_WEEK_DAY:
		{
			dtWorking += 1;
			while (!dtWorking.IsWeekDay())
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_WEEKEND_DAY:
		{
			dtWorking += 1;
			while (!dtWorking.IsWeekendDay())
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_SUNDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 1)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_MONDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 2)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_TUESDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 3)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_WEDNESDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 4)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_THURSDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 5)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_FRIDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 6)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	case FPSDATE_RECUR_SKIP_METHOD_NEXT_SATURDAY:
		{
			dtWorking += 1;
			while (dtWorking.GetDayOfWeek() != 7)
				dtWorking += 1;

			if (dtWorking > dtLast && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtWorking <= dtEnd))
				AddDateToList(dtWorking, List);
			break;
		}
	}
}

BOOL CFPSRecurringDates::AddDateToList(COleDateTime& dt, CPtrList& List)
{
	BOOL bReturn = TRUE;

	try
	{
		COleDateTime* pNewDate = new COleDateTime;

		if (pNewDate)
		{
			(*pNewDate) = dt;

			List.AddTail(pNewDate);
		}
		else
		{
			ASSERT(pNewDate);
			bReturn = FALSE;
		}
	}
	catch(...)
	{
		ASSERT(FALSE);
		bReturn = FALSE;
	}

	return bReturn;
}

BOOL CFPSRecurringDates::CheckForEnd(CPtrList& List, COleDateTime& dt, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = FALSE;

	switch (sEndMethod)
	{
	case FPSDATE_RECUR_END_METHOD_OCRNC:
		{
			if (List.GetCount() >= iMaxOccurences)
				bReturn = TRUE;
			break;
		}
	case FPSDATE_RECUR_END_METHOD_DATE:
		{
			if (dt > dtEnd)
				bReturn = TRUE;
			break;
		}
	default:
		{
			ASSERT(FALSE);
			bReturn = TRUE;
			break;
		}
	}

	return bReturn;
}
// ************************************************************
// END
// utility methods used when generating the pattern
// ************************************************************


// ************************************************************
// BEGIN
// methods used to generate the pattern result set
// ************************************************************
BOOL CFPSRecurringDates::GeneratePattern(CPtrList& List)
{
	BOOL bReturn = TRUE;
	short sEndMethod = m_sEndMethod;
	int iEndOccurence = m_iEndOccurences;
	COleDateTime dtEnd;

	switch (m_sEndMethod)
	{
	case FPSDATE_RECUR_END_METHOD_NONE:
		{
			// when no end date/occurence count is specified AND this
			// version of the function is called, we force the usage
			// of max-occurence rules (w/max=31)
			sEndMethod = FPSDATE_RECUR_END_METHOD_OCRNC;
			iEndOccurence = 31;
			break;
		}
	case FPSDATE_RECUR_END_METHOD_DATE:
		{
			dtEnd.ParseDateTime(m_strEndDate);
			ASSERT(dtEnd.GetStatus() == COleDateTime::valid);

			if (dtEnd.GetStatus() != COleDateTime::valid)
				bReturn = FALSE;
			break;
		}
	}

	if (bReturn)
		bReturn = GeneratePattern(List, sEndMethod, iEndOccurence, dtEnd);

	return bReturn;
}

BOOL CFPSRecurringDates::GeneratePattern(CPtrList& List, COleDateTime& dtEnd)
{
	return GeneratePattern(List, FPSDATE_RECUR_END_METHOD_DATE, 0, dtEnd);
}

BOOL CFPSRecurringDates::GeneratePattern(CPtrList& List, int iMaxOccurences)
{
	return GeneratePattern(List, FPSDATE_RECUR_END_METHOD_OCRNC, iMaxOccurences, COleDateTime::GetCurrentTime());
}

BOOL CFPSRecurringDates::GeneratePattern(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = TRUE;

	switch (m_sBasicMethod)
	{
	case FPSDATE_RECUR_BASE_METHOD_DAILY: {bReturn = GeneratePattern_Daily(List, sEndMethod, iMaxOccurences, dtEnd); break;}
	case FPSDATE_RECUR_BASE_METHOD_WEEKLY: {bReturn = GeneratePattern_Weekly(List, sEndMethod, iMaxOccurences, dtEnd); break;}
	case FPSDATE_RECUR_BASE_METHOD_MONTHLY: {bReturn = GeneratePattern_Monthly(List, sEndMethod, iMaxOccurences, dtEnd); break;}
	case FPSDATE_RECUR_BASE_METHOD_YEARLY: {bReturn = GeneratePattern_Yearly(List, sEndMethod, iMaxOccurences, dtEnd); break;}
	}

	// add force dates to list
	POSITION Pos = m_ForceDates.GetHeadPosition();
	while (Pos)
	{
		CString strDate = m_ForceDates.GetNext(Pos);
		COleDateTime dt;
		dt.ParseDateTime(strDate);

		AddDateToList(dt, List);
	}

	return bReturn;
}

BOOL CFPSRecurringDates::GeneratePattern_Daily(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = TRUE;
	COleDateTimeEx dtStart;
	COleDateTimeEx dtWorking;
	COleDateTimeEx dtLast;

	dtStart.ParseDateTime(m_strStartDate);

	if (dtStart.GetStatus() == COleDateTime::valid)
	{
		dtLast = dtStart;  dtLast -= 1;	// start with a last date of less than start date
		dtWorking = dtStart;

		switch (m_sDailyMethod)
		{
		case FPSDATE_RECUR_DAILY_METHOD_EVERY_X_DAYS:
			{
				int iDayCount = m_iEveryXDayCount;
				BOOL bEnd = FALSE;

				while (!bEnd)
				{
					// we take every day when daycount = option value
					if (iDayCount == m_iEveryXDayCount)
					{
						if (dtWorking >= dtLast && !IsDateBlackedOut(dtWorking))
						{
							short sSkipMethod = 0;

							if (!IsDateSkipped(dtWorking, sSkipMethod))
							{
								AddDateToList(dtWorking, List);
								dtLast = dtWorking;
							}
							else
							{
								COleDateTimeEx dtTemp = dtWorking;

								ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

								if (dtTemp > dtLast)
									dtLast = dtTemp;
							}
						}
					}
			
					// move forward 1 day and check for overflow of day count
					dtWorking += 1;
					iDayCount++;
					if (iDayCount > m_iEveryXDayCount)
						iDayCount = 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		case FPSDATE_RECUR_DAILY_METHOD_EVERY_WEEKDAY:
			{
				BOOL bEnd = FALSE;

				while (!bEnd)
				{
					// we take every day when daycount = option value
					if (dtWorking.IsWeekDay())
					{
						if (dtWorking >= dtLast && !IsDateBlackedOut(dtWorking))
						{
							short sSkipMethod = 0;

							if (!IsDateSkipped(dtWorking, sSkipMethod))
							{
								AddDateToList(dtWorking, List);
								dtLast = dtWorking;
							}
							else
							{
								COleDateTimeEx dtTemp = dtWorking;

								ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

								if (dtTemp > dtLast)
									dtLast = dtTemp;
							}
						}
					}
				
					// move forward 1 day and check for overflow of day count
					dtWorking += 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		default:
			{
				bReturn = FALSE;
				break;
			}
		}
	}
	else
	{
		ASSERT(FALSE);
		bReturn = FALSE;
	}

	return bReturn;
}

BOOL CFPSRecurringDates::GeneratePattern_Weekly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = TRUE;
	COleDateTimeEx dtStart;
	COleDateTimeEx dtWorking;
	COleDateTimeEx dtLast;

	dtStart.ParseDateTime(m_strStartDate);

	if (dtStart.GetStatus() == COleDateTime::valid)
	{
		dtLast = dtStart;  dtLast -= 1;	// start with a last date of less than start date
		dtWorking = dtStart;

		int iWeekCount = m_iEveryWeekCount;
		BOOL bEnd = FALSE;

		while (!bEnd)
		{
			// we take every day when daycount = option value
			if (iWeekCount == m_iEveryWeekCount)
			{
				BOOL bAdd = FALSE;

				// must be on an enabled day-of-week
				if (dtWorking.GetDayOfWeek() == 1 && m_bWeeklySunday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 2 && m_bWeeklyMonday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 3 && m_bWeeklyTuesday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 4 && m_bWeeklyWednesday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 5 && m_bWeeklyThursday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 6 && m_bWeeklyFriday)
					bAdd = TRUE;
				if (dtWorking.GetDayOfWeek() == 7 && m_bWeeklySaturday)
					bAdd = TRUE;

				if (bAdd)
				{
					if (dtWorking >= dtLast && !IsDateBlackedOut(dtWorking))
					{
						short sSkipMethod = 0;

						if (!IsDateSkipped(dtWorking, sSkipMethod))
						{
							AddDateToList(dtWorking, List);
							dtLast = dtWorking;
						}
						else
						{
							COleDateTimeEx dtTemp = dtWorking;

							ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

							if (dtTemp > dtLast)
								dtLast = dtTemp;
						}
					}
				}
			}
	
			// move forward 1 day
			dtWorking += 1;
			if (dtWorking.GetDayOfWeek() == 1)
			{
				// increment week counter and check for overflow
				iWeekCount++;
				if (iWeekCount > m_iEveryWeekCount)
					iWeekCount = 1;
			}

			// check for an ending condition
			bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
		}
	}
	else
	{
		ASSERT(FALSE);
		bReturn = FALSE;
	}

	return bReturn;
}

BOOL CFPSRecurringDates::GeneratePattern_Monthly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = TRUE;
	COleDateTimeEx dtStart;
	COleDateTimeEx dtWorking;
	COleDateTimeEx dtLast;

	dtStart.ParseDateTime(m_strStartDate);

	if (dtStart.GetStatus() == COleDateTime::valid)
	{
		dtLast = dtStart;  dtLast -= 1;	// start with a last date of less than start date
		dtWorking = dtStart;

		switch (m_sMonthlyMethod)
		{
		case FPSDATE_RECUR_MONTHLY_METHOD_OPTION_1:
			{
				int iMonthCount = m_iMonthlyCount2;
				BOOL bEnd = FALSE;

				while (!bEnd)
				{
					// we take every day when daycount = option value
					if (iMonthCount == m_iMonthlyCount2 && dtWorking.GetDay() == m_iMonthlyCount1)
					{
						if (dtWorking >= dtLast && !IsDateBlackedOut(dtWorking))
						{
							short sSkipMethod = 0;

							if (!IsDateSkipped(dtWorking, sSkipMethod))
							{
								AddDateToList(dtWorking, List);
								dtLast = dtWorking;
							}
							else
							{
								COleDateTimeEx dtTemp = dtWorking;

								ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

								if (dtTemp > dtLast)
									dtLast = dtTemp;
							}
						}
					}
			
					// move forward 1 day 
					dtWorking += 1;

					// check for month change
					if (dtWorking.GetDay() == 1)
					{
						iMonthCount++;
						if (iMonthCount > m_iMonthlyCount2)
							iMonthCount = 1;
					}

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		case FPSDATE_RECUR_MONTHLY_METHOD_OPTION_2:
			{
				BOOL bEnd = FALSE;
				int iLastMonth = -1;
				int iMonthCounter = m_iMonthlyCount3;

				while (!bEnd)
				{
					if (dtWorking.GetMonth() != iLastMonth)
					{
						if (iMonthCounter == m_iMonthlyCount3)
						{
							COleDateTimeEx dtValue;
							
							dtValue.GetDayInMonth(dtWorking.GetMonth(), dtWorking.GetYear(), m_iMonthlyTheOption, m_iMonthlyDayOption);

							if (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtValue <= dtEnd)
							{
								if (dtValue >= dtLast && !IsDateBlackedOut(dtValue))
								{
									short sSkipMethod = 0;

									if (!IsDateSkipped(dtValue, sSkipMethod))
									{
										AddDateToList(dtValue, List);
										dtLast = dtValue;
									}
									else
									{
										COleDateTimeEx dtTemp = dtValue;

										ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

										if (dtTemp > dtLast)
											dtLast = dtTemp;
									}
								}
							}
						}

						// increment month counter and overflow if necessary
						iMonthCounter++;
						if (iMonthCounter > m_iMonthlyCount3)
							iMonthCounter = 1;

						// record last month
						iLastMonth = dtWorking.GetMonth();
					}
				
					// move forward 1 day and check for overflow of day count
					dtWorking += 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		case FPSDATE_RECUR_MONTHLY_METHOD_OPTION_3:
			{
				BOOL bEnd = FALSE;
				int iLastMonth = -1;
				int iMonthCounter = m_iMonthlyCount4;

				while (!bEnd)
				{
					if (dtWorking.GetMonth() != iLastMonth)
					{
						if (iMonthCounter == m_iMonthlyCount4)
						{
							COleDateTimeEx dtValue;
							
							dtValue.GetDayInMonth(dtWorking.GetMonth(), dtWorking.GetYear(), m_iMonthlyTheOption1, m_iMonthlyDayOption1);

							// make necessary adjustment
							if (m_iMonthlyMathOp == FPSDATE_RECUR_MATH_OP_PLUS)
								dtValue += m_iMonthlyMathDays;
							else
								dtValue -= m_iMonthlyMathDays;

							if (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtValue <= dtEnd)
							{
								if (dtValue >= dtLast && !IsDateBlackedOut(dtValue))
								{
									short sSkipMethod = 0;

									if (!IsDateSkipped(dtValue, sSkipMethod))
									{
										AddDateToList(dtValue, List);
										dtLast = dtValue;
									}
									else
									{
										COleDateTimeEx dtTemp = dtValue;

										ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

										if (dtTemp > dtLast)
											dtLast = dtTemp;
									}
								}
							}
						}

						// increment month counter and overflow if necessary
						iMonthCounter++;
						if (iMonthCounter > m_iMonthlyCount4)
							iMonthCounter = 1;

						// record last month
						iLastMonth = dtWorking.GetMonth();
					}
				
					// move forward 1 day and check for overflow of day count
					dtWorking += 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		default:
			{
				bReturn = FALSE;
				break;
			}
		}
	}
	else
	{
		ASSERT(FALSE);
		bReturn = FALSE;
	}

	return bReturn;
}

BOOL CFPSRecurringDates::GeneratePattern_Yearly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd)
{
	BOOL bReturn = TRUE;
	COleDateTimeEx dtStart;
	COleDateTimeEx dtWorking;
	COleDateTimeEx dtLast;

	dtStart.ParseDateTime(m_strStartDate);

	if (dtStart.GetStatus() == COleDateTime::valid)
	{
		dtLast = dtStart;  dtLast -= 1;	// start with a last date of less than start date
		dtWorking = dtStart;

		switch (m_sYearlyMethod)
		{
		case FPSDATE_RECUR_YEARLY_METHOD_OPTION_1:
			{
				BOOL bEnd = FALSE;
				int iLastYear = -1;

				while (!bEnd)
				{
					if (dtWorking.GetYear() != iLastYear)
					{
						COleDateTimeEx dtValue;

						dtValue.SetDate(dtWorking.GetYear(), m_iYearlyMonth1, m_iYearlyMonthDay);

						if (dtValue.GetStatus() == COleDateTime::valid && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtValue <= dtEnd) && dtValue >= dtStart)
						{
							if (dtValue >= dtLast && !IsDateBlackedOut(dtValue))
							{
								short sSkipMethod = 0;

								if (!IsDateSkipped(dtValue, sSkipMethod))
								{
									AddDateToList(dtValue, List);
									dtLast = dtValue;
								}
								else
								{
									COleDateTimeEx dtTemp = dtValue;

									ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

									if (dtTemp > dtLast)
										dtLast = dtTemp;
								}
							}
						}

						// save last year
						iLastYear = dtWorking.GetYear();
					}
			
					// move forward 1 day 
					dtWorking += 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		case FPSDATE_RECUR_YEARLY_METHOD_OPTION_2:
			{
				BOOL bEnd = FALSE;
				int iLastYear = -1;

				while (!bEnd)
				{
					if (dtWorking.GetYear() != iLastYear)
					{
						COleDateTimeEx dtValue;

						dtValue.GetDayInMonth(m_iYearlyMonth2, dtWorking.GetYear(), m_iYearlyTheOption, m_iYearlyDayOption);

						if (dtValue.GetStatus() == COleDateTime::valid && (sEndMethod != FPSDATE_RECUR_END_METHOD_DATE || dtValue <= dtEnd) && dtValue >= dtStart)
						{
							if (dtValue >= dtLast && !IsDateBlackedOut(dtValue))
							{
								short sSkipMethod = 0;

								if (!IsDateSkipped(dtValue, sSkipMethod))
								{
									AddDateToList(dtValue, List);
									dtLast = dtValue;
								}
								else
								{
									COleDateTimeEx dtTemp = dtValue;

									ProcessSkip(dtTemp, sSkipMethod, List, dtLast, sEndMethod, iMaxOccurences, dtEnd);

									if (dtTemp > dtLast)
										dtLast = dtTemp;
								}
							}
						}

						// save last year
						iLastYear = dtWorking.GetYear();
					}
			
					// move forward 1 day 
					dtWorking += 1;

					// check for an ending condition
					bEnd = CheckForEnd(List, dtWorking, sEndMethod, iMaxOccurences, dtEnd);
				}
				break;
			}
		default:
			{
				bReturn = FALSE;
				break;
			}
		}
	}
	else
	{
		ASSERT(FALSE);
		bReturn = FALSE;
	}

	return bReturn;
}
// ************************************************************
// END
// methods used to generate the pattern result set
// ************************************************************

// ************************************************************
// BEGIN
// utility methods for validating the setup of the pattern
// ************************************************************
BOOL CFPSRecurringDates::IsValid()
{
	BOOL bReturn = TRUE;

	return bReturn;
}
// ************************************************************
// END
// utility methods for validating the setup of the pattern
// ************************************************************

void CFPSRecurringDates::AddBlackOutDate(COleDateTime &dt)
{
	CString strDate = dt.Format("%B %d %Y");
	m_BlackOutDates1.AddTail(strDate);
}

void CFPSRecurringDates::AddForceDate(COleDateTime &dt)
{
	CString strDate = dt.Format("%B %d %Y");
	m_ForceDates.AddTail(strDate);
}

void CFPSRecurringDates::RemoveForceDate(COleDateTime &dt)
{
	CString strDate = dt.Format("%B %d %Y");

	POSITION Pos = m_ForceDates.Find(strDate);
	if (Pos)
		m_ForceDates.RemoveAt(Pos);
}

void CFPSRecurringDates::ClearForceDates()
{
	m_ForceDates.RemoveAll();
}

void CFPSRecurringDates::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		ar << m_sBasicMethod;
		ar << m_strStartTime;
		ar << m_strEndTime;
		ar << m_sEndMethod;
		ar << m_strStartDate;
		ar << m_strEndDate;
		ar << m_iEndOccurences;

		ar << m_sDailyMethod;
		ar << m_iEveryXDayCount;

		ar << m_iEveryWeekCount;
		ar << m_bWeeklySunday;
		ar << m_bWeeklyMonday;
		ar << m_bWeeklyTuesday;
		ar << m_bWeeklyWednesday;
		ar << m_bWeeklyThursday;
		ar << m_bWeeklyFriday;
		ar << m_bWeeklySaturday;

		ar << m_sMonthlyMethod;
		ar << m_iMonthlyCount1;
		ar << m_iMonthlyCount2;
		ar << m_iMonthlyTheOption;
		ar << m_iMonthlyDayOption;
		ar << m_iMonthlyCount3;

		ar << m_sYearlyMethod;
		ar << m_iYearlyMonth1;
		ar << m_iYearlyMonthDay;
		ar << m_iYearlyTheOption;
		ar << m_iYearlyDayOption;
		ar << m_iYearlyMonth2;

		m_ForceDates.Serialize(ar);
		m_BlackOutDates1.Serialize(ar);
		//CTypedPtrList<CPtrList, CFPSRecurringDate_Skip*> m_SkipDates;
	}
	else
	{
		ar >> m_sBasicMethod;
		ar >> m_strStartTime;
		ar >> m_strEndTime;
		ar >> m_sEndMethod;
		ar >> m_strStartDate;
		ar >> m_strEndDate;
		ar >> m_iEndOccurences;

		ar >> m_sDailyMethod;
		ar >> m_iEveryXDayCount;

		ar >> m_iEveryWeekCount;
		ar >> m_bWeeklySunday;
		ar >> m_bWeeklyMonday;
		ar >> m_bWeeklyTuesday;
		ar >> m_bWeeklyWednesday;
		ar >> m_bWeeklyThursday;
		ar >> m_bWeeklyFriday;
		ar >> m_bWeeklySaturday;

		ar >> m_sMonthlyMethod;
		ar >> m_iMonthlyCount1;
		ar >> m_iMonthlyCount2;
		ar >> m_iMonthlyTheOption;
		ar >> m_iMonthlyDayOption;
		ar >> m_iMonthlyCount3;

		ar >> m_sYearlyMethod;
		ar >> m_iYearlyMonth1;
		ar >> m_iYearlyMonthDay;
		ar >> m_iYearlyTheOption;
		ar >> m_iYearlyDayOption;
		ar >> m_iYearlyMonth2;

		m_ForceDates.Serialize(ar);
		m_BlackOutDates1.Serialize(ar);
		//CTypedPtrList<CPtrList, CFPSRecurringDate_Skip*> m_SkipDates;
	}
}
