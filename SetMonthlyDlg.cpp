// SetMonthlyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "magicshutdown.h"
#include "SetMonthlyDlg.h"

#include "./date/FPSRecurringDates.h"
#include "./date/oledatetimeex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetMonthlyDlg dialog


SetMonthlyDlg::SetMonthlyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetMonthlyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetMonthlyDlg)
		// NOTE: the ClassWizard will add member initialization here
	app=(CMagicShutdownApp*)AfxGetApp(); 
	//}}AFX_DATA_INIT
}

SetMonthlyDlg::~SetMonthlyDlg()
{

}
void SetMonthlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetMonthlyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_COMBO_Month2_Days, m_month_day_slect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetMonthlyDlg, CDialog)
	//{{AFX_MSG_MAP(SetMonthlyDlg)
	ON_NOTIFY(WM_FPSMINICLNDR_VIEWCHANGE, 1001, OnCalendarViewChange)
	ON_NOTIFY(NM_CLICK, 1001, OnCalendarClick)

	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetMonthlyDlg message handlers
BOOL SetMonthlyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//COleDateTime curTime = COleDateTime::GetCurrentTime();
     CString dbfile =  app->m_sAppPath+_T("\\monthly.db3");
	 dbm.open(dbfile);



	
	CRect ClientRect;
	GetClientRect(ClientRect);

	m_wndCalendar.Create(NULL, NULL,  WS_CHILD | WS_VISIBLE |  FMC_AUTOSETTINGS | FMC_NO3DBORDER, 
						 CRect(8,2,ClientRect.Width(), ClientRect.Height()), 
						 this, 
						 1001);
	m_wndCalendar.SetSpecialDaysColor(RGB(255,0,0));
	m_wndCalendar.SetSpecialDaysCallback(SetMonthlyDlg::IsDateInPattern, (DWORD)this);
	//m_wndCalendar.SetBackColor(RGB(212,208,200));
	m_month_day_slect.SetCurSel(2);
	OnSelchangeViewMode();
	//AfxMessageBox(str);


	//从数据库中将已经选中的数据显示出来
	CString sql;
	sql = "select * from  monthly";
    rem = dbm.query(sql); 
	while (!rem.eof())
    {
		m_DateListString.AddTail(rem.fieldValue("date"));
		
       rem.nextRow();
     }
	rem.finalize();



	SetTimer(110,100,0);
	return TRUE;  
}
void SetMonthlyDlg::OnSelchangeViewMode() 
{
	int iSel = m_month_day_slect.GetCurSel();

	switch (iSel)
	{
	case 0:		// 1 month
		{
			m_wndCalendar.SetRowsAndColumns(1,1);
			break;
		}
	case 1:		// 4 month
		{
			m_wndCalendar.SetRowsAndColumns(2,2);
			break;
		}
	case 2:		// 6 month
		{
			m_wndCalendar.SetRowsAndColumns(2,3);
			break;
		}
	case 3:		// 8 month
		{
			m_wndCalendar.SetRowsAndColumns(2,4);
			break;
		}
	case 4:		// 12 month
		{
			m_wndCalendar.SetRowsAndColumns(3,4);
			break;
		}
	default:
		{
			ASSERT(FALSE);
			break;
		}
	}
}

BOOL SetMonthlyDlg::OnSetActive() 
{
	COleDateTimeEx dt;

	// set start month/year for calendar
	m_wndCalendar.SetCurrentMonthAndYear(dt.GetMonth(), dt.GetYear());
	int iMonths = m_wndCalendar.GetRows() * m_wndCalendar.GetCols();

	ReloadDateList();
	RedrawWindow();

	return SetMonthlyDlg::OnSetActive();
}
BOOL CALLBACK SetMonthlyDlg::IsDateInPattern(COleDateTime& dt, DWORD dwParm)
{
	BOOL bReturn = FALSE;
	SetMonthlyDlg* pDialog = (SetMonthlyDlg*)dwParm;

	ASSERT(pDialog);

	if (pDialog)
	{
		CString strDate = dt.Format("%m-%d-%Y");

		if (pDialog->m_DateListString.Find(strDate))
			bReturn = TRUE;
	}

	return bReturn;
}
void SetMonthlyDlg::OnCalendarClick( NMHDR * pNotifyStruct, LRESULT * result )
{
	COleDateTimeEx dt = m_wndCalendar.GetDate();
	CString strDate = dt.Format("%m-%d-%Y");


	if (m_DateListString.Find(strDate))
	{
		POSITION Pos = m_DateListString.Find(strDate);
		m_DateListString.RemoveAt(Pos);



		strDate = dt.Format(app->DateFormat);

		CString strMessage;
		strMessage.Format(IDS_RPATTERN_REMOVE, (LPCTSTR)strDate);
		
		//移除月中哪些日子设定
		CString sql;
		sql = "delete from  monthly where date = '"+strDate+"'";
     	dbm.query(sql); 
		//	AfxMessageBox(strDate);
	}
	else
	{
		m_DateListString.AddTail(strDate);


	   //	AfxMessageBox("df");
		strDate = dt.Format(app->DateFormat);

		CString strMessage;
		strMessage.Format(IDS_RPATTERN_ADD, (LPCTSTR)strDate);

		//插入月中哪些日子设定
		CString sql;
		sql = "insert into monthly (date) values ('"+strDate+"')";
     	dbm.query(sql); 	 
	  // AfxMessageBox(strDate);
	}

	dt.SetStatus(COleDateTime::invalid);
	m_wndCalendar.SetDate(dt);

	m_wndCalendar.Invalidate();
	RedrawWindow();
}

void SetMonthlyDlg::ReloadDateList()
{
	// cleanup old date list


}

void SetMonthlyDlg::OnClearBlackOuts() 
{

}

void SetMonthlyDlg::OnClearForceDates() 
{

}

void SetMonthlyDlg::OnCalendarViewChange( NMHDR * pNotifyStruct, LRESULT * result )
{
	ReloadDateList();
	m_wndCalendar.Invalidate();
	RedrawWindow();
	
}



void SetMonthlyDlg::OnTimer(UINT nIDEvent)
{

	CDialog::OnTimer(nIDEvent);
}

void SetMonthlyDlg::SetStatus(void)
{
	if(app->IsCountDownNow==1)
	{
		m_wndCalendar.EnableWindow(false);
		m_wndCalendar.SetBackColor(RGB(183,182,179));
	}else{
		m_wndCalendar.EnableWindow(true);
		m_wndCalendar.SetBackColor(::GetSysColor(COLOR_WINDOW));
	}
	RedrawWindow();
}
