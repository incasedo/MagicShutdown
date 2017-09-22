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

#if !defined(AFX_FPSRECURRINGDATES_H__42511021_DC4E_432D_BBE9_FD5941997D26__INCLUDED_)
#define AFX_FPSRECURRINGDATES_H__42511021_DC4E_432D_BBE9_FD5941997D26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "OleDateTimeEx.h"

#define FPSDATE_RECUR_BASE_METHOD_DAILY				0
#define FPSDATE_RECUR_BASE_METHOD_WEEKLY			1
#define FPSDATE_RECUR_BASE_METHOD_MONTHLY			2
#define FPSDATE_RECUR_BASE_METHOD_YEARLY			3

#define FPSDATE_RECUR_END_METHOD_NONE				0
#define FPSDATE_RECUR_END_METHOD_OCRNC				1
#define FPSDATE_RECUR_END_METHOD_DATE				2

#define FPSDATE_RECUR_DAILY_METHOD_EVERY_X_DAYS		0
#define FPSDATE_RECUR_DAILY_METHOD_EVERY_WEEKDAY	1

#define FPSDATE_RECUR_MONTHLY_METHOD_OPTION_1		0
#define FPSDATE_RECUR_MONTHLY_METHOD_OPTION_2		1
#define FPSDATE_RECUR_MONTHLY_METHOD_OPTION_3		2

#define FPSDATE_RECUR_YEARLY_METHOD_OPTION_1		0
#define FPSDATE_RECUR_YEARLY_METHOD_OPTION_2		1

#define FPSDATE_RECUR_WEEK_FIRST					0
#define FPSDATE_RECUR_WEEK_SECOND					1
#define FPSDATE_RECUR_WEEK_THIRD					2
#define FPSDATE_RECUR_WEEK_FOURTH					3
#define FPSDATE_RECUR_WEEK_LAST						4

#define FPSDATE_RECUR_SKIP_METHOD_SKIP				-1
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_DAY			0
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_WEEK_DAY		1
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_WEEKEND_DAY	2
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_SUNDAY		3
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_MONDAY		4
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_TUESDAY		5
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_WEDNESDAY	6
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_THURSDAY		7
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_FRIDAY		8
#define FPSDATE_RECUR_SKIP_METHOD_NEXT_SATURDAY		9

#define FPSDATE_RECUR_MATH_OP_PLUS			0
#define FPSDATE_RECUR_MATH_OP_MINUS			1


class CFPSRecurringDate_Skip
{
public:
	CFPSRecurringDate_Skip() {};
	~CFPSRecurringDate_Skip() {};

	int		m_iDateOption;
	CString	m_strDate;
	short	m_sSkipMethod;
	BOOL	m_bEnabled;
};

class CFPSRecurringDates  
{
public:
	virtual void Serialize(CArchive& ar);
	CFPSRecurringDates();
	virtual ~CFPSRecurringDates();

	// support functions
	virtual BOOL IsValid();
	virtual BOOL IsDateInPattern(COleDateTime& dtCheck);
	virtual BOOL IsDateInPattern(CPtrList& List, COleDateTime &dtCheck);
	virtual BOOL GeneratePattern(CPtrList& List);
	virtual BOOL GeneratePattern(CPtrList& List, COleDateTime& dtEndBy);
	virtual BOOL GeneratePattern(CPtrList& List, int iMaxOccurences);

	virtual BOOL IsDateBlackedOut(COleDateTime& dtCheck);
	virtual BOOL IsDateSkipped(COleDateTime& dtCheck, short& sSkipMethod);
	virtual BOOL GetBuiltInDate(int iType, COleDateTime& dt, int iYear);
	virtual void CleanupDateList(CPtrList& List);

	// methods for accessing and manipulating basic method selection
	virtual short GetBaseMethod() {return m_sBasicMethod;}
	virtual void SetBaseMethod(short sValue) {m_sBasicMethod = sValue;}
	virtual BOOL IsBaseMethodDaily() {return m_sBasicMethod == FPSDATE_RECUR_BASE_METHOD_DAILY;}
	virtual BOOL IsBaseMethodWeekly() {return m_sBasicMethod == FPSDATE_RECUR_BASE_METHOD_WEEKLY;}
	virtual BOOL IsBaseMethodMonthly() {return m_sBasicMethod == FPSDATE_RECUR_BASE_METHOD_MONTHLY;}
	virtual BOOL IsBaseMethodYearly() {return m_sBasicMethod == FPSDATE_RECUR_BASE_METHOD_YEARLY;}
	virtual void SetBaseMethodDaily() {m_sBasicMethod = FPSDATE_RECUR_BASE_METHOD_DAILY;}
	virtual void SetBaseMethodWeekly() {m_sBasicMethod = FPSDATE_RECUR_BASE_METHOD_WEEKLY;}
	virtual void SetBaseMethodMonthly() {m_sBasicMethod = FPSDATE_RECUR_BASE_METHOD_MONTHLY;}
	virtual void SetBaseMethodYearly() {m_sBasicMethod = FPSDATE_RECUR_BASE_METHOD_YEARLY;}

	// methods for accessing and manipulating start/end times
	virtual CString GetStartTime() {return m_strStartTime;}
	virtual CString GetEndTime() {return m_strEndTime;}
	virtual void SetStartTime(LPCTSTR lpszStart) {m_strStartTime = lpszStart;}
	virtual void SetEndTime(LPCTSTR lpszEnd) {m_strEndTime = lpszEnd;}

	// methods for accessing and manipulating end options
	virtual short GetEndMethod() {return m_sEndMethod;}
	virtual void SetEndMethod(short sValue) {m_sEndMethod = sValue;}
	virtual BOOL IsEndMethodNone() {return m_sEndMethod == FPSDATE_RECUR_END_METHOD_NONE;}
	virtual BOOL IsEndMethodOccurence() {return m_sEndMethod == FPSDATE_RECUR_END_METHOD_OCRNC;}
	virtual BOOL IsEndMethodDate() {return m_sEndMethod == FPSDATE_RECUR_END_METHOD_DATE;}
	virtual void SetEndMethodNone() {m_sEndMethod = FPSDATE_RECUR_END_METHOD_NONE;}
	virtual void SetEndMethodOccurence() {m_sEndMethod = FPSDATE_RECUR_END_METHOD_OCRNC;}
	virtual void SetEndMethodDate() {m_sEndMethod = FPSDATE_RECUR_END_METHOD_DATE;}

	// methods for accessing start/end date and occurence count
	virtual CString GetStartDate() {return m_strStartDate;}
	virtual CString GetEndDate() {return m_strEndDate;}
	virtual int GetEndOccurenceCount() {return m_iEndOccurences;}
	virtual void SetStartDate(LPCTSTR lpszValue) {m_strStartDate = lpszValue;}
	virtual void SetEndDate(LPCTSTR lpszValue) {m_strEndDate = lpszValue;}
	virtual void SetEndOccurenceCount(int iValue) {m_iEndOccurences = iValue;}

	// methods for accessing daily control options
	virtual short GetDailyMethod() {return m_sDailyMethod;}
	virtual void SetDailyMethod(short sValue) {m_sDailyMethod = sValue;}
	virtual BOOL IsDailyMethodEveryXDays() {return m_sDailyMethod == FPSDATE_RECUR_DAILY_METHOD_EVERY_X_DAYS;}
	virtual BOOL IsDailyMethodEveryWeekday() {return m_sDailyMethod == FPSDATE_RECUR_DAILY_METHOD_EVERY_WEEKDAY;}
	virtual void SetDailyMethodEveryXDays() {m_sDailyMethod = FPSDATE_RECUR_DAILY_METHOD_EVERY_X_DAYS;}
	virtual void SetDailyMethodEveryWeekday() {m_sDailyMethod = FPSDATE_RECUR_DAILY_METHOD_EVERY_WEEKDAY;}
	virtual int GetDailyCount() {return m_iEveryXDayCount;}
	virtual void SetDailyCount(int iValue) {m_iEveryXDayCount = iValue;}

	// methods for accessing and setting weekly control options
	virtual int GetWeeklyCount() {return m_iEveryWeekCount;}
	virtual void SetWeeklyCount(int iValue) {m_iEveryWeekCount = iValue;}
	virtual BOOL IsWeeklySunday() {return m_bWeeklySunday;}
	virtual BOOL IsWeeklyMonday() {return m_bWeeklyMonday;}
	virtual BOOL IsWeeklyTuesday() {return m_bWeeklyTuesday;}
	virtual BOOL IsWeeklyWednesday() {return m_bWeeklyWednesday;}
	virtual BOOL IsWeeklyThursday() {return m_bWeeklyThursday;}
	virtual BOOL IsWeeklyFriday() {return m_bWeeklyFriday;}
	virtual BOOL IsWeeklySaturday() {return m_bWeeklySaturday;}
	virtual void SetWeeklySunday(BOOL bValue) {m_bWeeklySunday = bValue;}
	virtual void SetWeeklyMonday(BOOL bValue) {m_bWeeklyMonday = bValue;}
	virtual void SetWeeklyTuesday(BOOL bValue) {m_bWeeklyTuesday = bValue;}
	virtual void SetWeeklyWednesday(BOOL bValue) {m_bWeeklyWednesday = bValue;}
	virtual void SetWeeklyThursday(BOOL bValue) {m_bWeeklyThursday = bValue;}
	virtual void SetWeeklyFriday(BOOL bValue) {m_bWeeklyFriday = bValue;}
	virtual void SetWeeklySaturday(BOOL bValue) {m_bWeeklySaturday = bValue;}

	// methods for accessing and setting monthly control options
	virtual short GetMonthlyMethod() {return m_sMonthlyMethod;}
	virtual void SetMonthlyMethod(short sValue) {m_sMonthlyMethod = sValue;}
	virtual BOOL IsMonthlyMethodOption1() {return m_sMonthlyMethod == FPSDATE_RECUR_MONTHLY_METHOD_OPTION_1;}
	virtual BOOL IsMonthlyMethodOption2() {return m_sMonthlyMethod == FPSDATE_RECUR_MONTHLY_METHOD_OPTION_2;}
	virtual void SetMonthlyMethodOption1() {m_sMonthlyMethod = FPSDATE_RECUR_MONTHLY_METHOD_OPTION_1;}
	virtual void SetMonthlyMethodOption2() {m_sMonthlyMethod = FPSDATE_RECUR_MONTHLY_METHOD_OPTION_2;}
	virtual int GetMonthlyCount1() {return m_iMonthlyCount1;}
	virtual void SetMonthlyCount1(int iValue) {m_iMonthlyCount1 = iValue;}
	virtual int GetMonthlyCount2() {return m_iMonthlyCount2;}
	virtual void SetMonthlyCount2(int iValue) {m_iMonthlyCount2 = iValue;}
	virtual int GetMonthlyCount3() {return m_iMonthlyCount3;}
	virtual void SetMonthlyCount3(int iValue) {m_iMonthlyCount3 = iValue;}
	virtual int GetMonthlyCount4() {return m_iMonthlyCount4;}
	virtual void SetMonthlyCount4(int iValue) {m_iMonthlyCount4 = iValue;}
	virtual int GetMonthlyTheOption() {return m_iMonthlyTheOption;}
	virtual void SetMonthlyTheOption(int iValue) {m_iMonthlyTheOption = iValue;}
	virtual int GetMonthlyDayOption() {return m_iMonthlyDayOption;}
	virtual void SetMonthlyDayOption(int iValue) {m_iMonthlyDayOption = iValue;}
	virtual int GetMonthlyTheOption1() {return m_iMonthlyTheOption1;}
	virtual void SetMonthlyTheOption1(int iValue) {m_iMonthlyTheOption1 = iValue;}
	virtual int GetMonthlyDayOption1() {return m_iMonthlyDayOption1;}
	virtual void SetMonthlyDayOption1(int iValue) {m_iMonthlyDayOption1 = iValue;}
	virtual int GetMonthlyMathOp() {return m_iMonthlyMathOp;}
	virtual void SetMonthlyMathOp(int iValue) {m_iMonthlyMathOp = iValue;}
	virtual int GetMonthlyMathDays() {return m_iMonthlyMathDays;}
	virtual void SetMonthlyMathDays(int iValue) {m_iMonthlyMathDays = iValue;}
	
	// methods for accessing and setting yearly control options
	virtual short GetYearlyMethod () {return m_sYearlyMethod;}
	virtual void SetYearlyMethod(short sValue) {m_sYearlyMethod = sValue;}
	virtual BOOL IsYearlyMethodOption1() {return m_sYearlyMethod == FPSDATE_RECUR_YEARLY_METHOD_OPTION_1;}
	virtual BOOL IsYearlyMethodOption2() {return m_sYearlyMethod == FPSDATE_RECUR_YEARLY_METHOD_OPTION_2;}
	virtual void SetYearlyMethodOption1() {m_sYearlyMethod = FPSDATE_RECUR_YEARLY_METHOD_OPTION_1;}
	virtual void SetYearlyMethodOption2() {m_sYearlyMethod = FPSDATE_RECUR_YEARLY_METHOD_OPTION_2;}
	virtual int GetYearlyMonth1() {return m_iYearlyMonth1;}
	virtual void SetYearlyMonth1(int iValue) {m_iYearlyMonth1 = iValue;}
	virtual int GetYearlyMonth2() {return m_iYearlyMonth2;}
	virtual void SetYearlyMonth2(int iValue) {m_iYearlyMonth2 = iValue;}
	virtual int GetYearlyDayOfMonth() {return m_iYearlyMonthDay;}
	virtual void SetYearlyDayOfMonth(int iValue) {m_iYearlyMonthDay = iValue;}
	virtual int GetYearlyTheOption() {return m_iYearlyTheOption;}
	virtual void SetYearlyTheOption(int iValue) {m_iYearlyTheOption = iValue;}
	virtual int GetYearlyDayOption() {return m_iYearlyDayOption;}
	virtual void SetYearlyDayOption(int iValue) {m_iYearlyDayOption = iValue;}

	// methods for accessing and setting black out dates
	virtual void ClearBlackOutDates();
	virtual int GetBlackOutDateCount() {return m_BlackOutDates1.GetCount();}
	virtual POSITION GetFirstBlackOutPosition() {return m_BlackOutDates1.GetHeadPosition();}
	virtual CString GetNextBlackOut(POSITION& Pos) {return m_BlackOutDates1.GetNext(Pos);}
	virtual void RemoveBlackOut(COleDateTime& dt);
	virtual void AddBlackOutDate(COleDateTime& dt);

	// methods for accessing and setting force dates
	virtual void ClearForceDates();
	virtual void RemoveForceDate(COleDateTime& dt);
	virtual void AddForceDate(COleDateTime& dt);
	virtual POSITION GetFirstForceDatePosition() {return m_ForceDates.GetHeadPosition();}
	virtual CString GetNextForceDate(POSITION& Pos) {return m_ForceDates.GetNext(Pos);}

	// method for accessing and setting skip dates
	virtual void ClearSkipDates();
	virtual int GetSkipDateCount() {return m_SkipDates.GetCount();}
	virtual POSITION GetFirstSkipPosition() {return m_SkipDates.GetHeadPosition();}
	virtual CFPSRecurringDate_Skip* GetNextSkip(POSITION& Pos) {return m_SkipDates.GetNext(Pos);}
	virtual void RemoveSkip(CFPSRecurringDate_Skip* pEntry);

	// methods for controlling build-in defaults
	static CString GetDefaultStartTime() {return m_strDefaultStartTime;}
	static void SetDefaultStringTime(LPCTSTR lpszValue) {m_strDefaultStartTime = lpszValue;}
	static CString GetDefaultEndTime() {return m_strDefaultEndTime;}
	static void SetDefaultEndTime(LPCTSTR lpszValue) {m_strDefaultEndTime = lpszValue;}

protected:
	virtual void ProcessSkip(COleDateTimeEx& dtWorking, short sSkipMethod, CPtrList& List, COleDateTimeEx& dtLast, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL CheckForEnd(CPtrList& List, COleDateTime& dt, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL AddDateToList(COleDateTime& dt, CPtrList& List);
	virtual BOOL GeneratePattern(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL GeneratePattern_Daily(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL GeneratePattern_Weekly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL GeneratePattern_Monthly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);
	virtual BOOL GeneratePattern_Yearly(CPtrList& List, short sEndMethod, int iMaxOccurences, COleDateTime& dtEnd);

	// basic options
	short	m_sBasicMethod;
	CString	m_strStartTime;
	CString	m_strEndTime;
	short	m_sEndMethod;
	CString	m_strStartDate;
	CString	m_strEndDate;
	int		m_iEndOccurences;

	// daily control options
	short	m_sDailyMethod;
	int		m_iEveryXDayCount;

	// weekly control options
	int		m_iEveryWeekCount;
	BOOL	m_bWeeklySunday;
	BOOL	m_bWeeklyMonday;
	BOOL	m_bWeeklyTuesday;
	BOOL	m_bWeeklyWednesday;
	BOOL	m_bWeeklyThursday;
	BOOL	m_bWeeklyFriday;
	BOOL	m_bWeeklySaturday;

	// monthly control options
	short	m_sMonthlyMethod;
	int		m_iMonthlyCount1;
	int		m_iMonthlyCount2;
	int		m_iMonthlyTheOption;
	int		m_iMonthlyDayOption;
	int		m_iMonthlyCount3;

	int		m_iMonthlyTheOption1;
	int		m_iMonthlyDayOption1;
	int		m_iMonthlyCount4;
	int		m_iMonthlyMathOp;
	int		m_iMonthlyMathDays;

	// yearly control options
	short	m_sYearlyMethod;
	int		m_iYearlyMonth1;
	int		m_iYearlyMonthDay;
	int		m_iYearlyTheOption;
	int		m_iYearlyDayOption;
	int		m_iYearlyMonth2;

	// black out and skip exceptions
	CStringList	m_ForceDates;
	CStringList	m_BlackOutDates1;
	CTypedPtrList<CPtrList, CFPSRecurringDate_Skip*> m_SkipDates;

	// static members used for defaults
	static	CString m_strDefaultStartTime;
	static	CString m_strDefaultEndTime;

private:
	CString CStr(long lValue);
};

#endif // !defined(AFX_FPSRECURRINGDATES_H__42511021_DC4E_432D_BBE9_FD5941997D26__INCLUDED_)
