// SetYearlyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "magicshutdown.h"
#include "SetYearlyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetYearlyDlg dialog


SetYearlyDlg::SetYearlyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetYearlyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetYearlyDlg)
		// NOTE: the ClassWizard will add member initialization here
	app=(CMagicShutdownApp*)AfxGetApp(); 

	//}}AFX_DATA_INIT
}


void SetYearlyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetYearlyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetYearlyDlg, CDialog)
	//{{AFX_MSG_MAP(SetYearlyDlg)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKERYears, OnCloseupDATETIMEPICKERYears)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetYearlyDlg message handlers
BOOL SetYearlyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//COleDateTime curTime = COleDateTime::GetCurrentTime();

	CString Currentdate = app->ini.GetString(_T("Yearly"), _T("date"));
    CDateTimeCtrl* pCtrl = (CDateTimeCtrl*) GetDlgItem(IDC_DATETIMEPICKERYears);
    ASSERT(pCtrl != NULL);
	


	 SYSTEMTIME sysTime;
	 memset(&sysTime, 0, sizeof(sysTime));
	 sysTime.wYear = atoi(Currentdate.Right (4));
	 sysTime.wMonth =  atoi(Currentdate.Left (2));
	 sysTime.wDay = atoi(Currentdate.Mid (3,2));
	 VERIFY(pCtrl->SetTime(&sysTime));


	



	return TRUE;  
}


void SetYearlyDlg::OnCloseupDATETIMEPICKERYears(NMHDR* pNMHDR, LRESULT* pResult) 
{
	 CDateTimeCtrl* pCtrl = (CDateTimeCtrl*) GetDlgItem(IDC_DATETIMEPICKERYears);

      ASSERT(pCtrl != NULL);
	  CTime timeTime;
	  DWORD dwResult = pCtrl->GetTime(timeTime);
		if (dwResult == GDT_VALID)
		   {
			  // the user checked the box and specified data
			  CString str;

			  // is it a time-only control, or a date-only control?
			  if ((pCtrl->GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
				 str = timeTime.Format(_T("%m-%d-%Y"));
			  else
				 str = timeTime.Format(_T("%m-%d-%Y"));
			  //Ð´ÈëiniÎÄ¼þ
			  app->ini.WriteString(_T("Yearly"), _T("date"), _T(str));
			  //AfxMessageBox(str);
		   }
		   else
		   {
			  // the user unmarked the "none" box
			  AfxMessageBox(_T("Time not set!"));
		   }

	*pResult = 0;
}

void SetYearlyDlg::SetStatus(void)
{
	if(app->IsCountDownNow==1)
	{
		(CDateTimeCtrl*) GetDlgItem(IDC_DATETIMEPICKERYears)->EnableWindow(false);
	}else{
		(CDateTimeCtrl*) GetDlgItem(IDC_DATETIMEPICKERYears)->EnableWindow(true);
	}
	
}
