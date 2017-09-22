// SetDailyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "magicshutdown.h"
#include "SetDailyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetDailyDlg dialog

SetDailyDlg::SetDailyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetDailyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetDailyDlg)
		// NOTE: the ClassWizard will add member initialization here
	app=(CMagicShutdownApp*)AfxGetApp(); 
	//}}AFX_DATA_INIT
}

void SetDailyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetDailyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetDailyDlg, CDialog)
	//{{AFX_MSG_MAP(SetDailyDlg)
	ON_BN_CLICKED(IDC_RADIO_EveryDay, OnEveryDay)
	ON_BN_CLICKED(IDC_RADIO_No67, OnNo67)
	ON_BN_CLICKED(IDC_RADIO_No7, OnRADIONo7)
	ON_BN_CLICKED(IDC_RADIO_Only6, OnRADIOOnly6)
	ON_BN_CLICKED(IDC_RADIO_Only7, OnRADIOOnly7)
	ON_BN_CLICKED(IDC_RADIO_Only67, OnRADIOOnly67)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetDailyDlg message handlers

BOOL SetDailyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//COleDateTime curTime = COleDateTime::GetCurrentTime();
	CString CurrentType = app->ini.GetString(_T("Daily"), _T("Type"));
	//set default radio
	if (CurrentType =="EveryDay")
		((CButton *)GetDlgItem(IDC_RADIO_EveryDay))->SetCheck(TRUE);
	else if (CurrentType =="No67")
		((CButton *)GetDlgItem(IDC_RADIO_No67))->SetCheck(TRUE);
	else if (CurrentType =="No7")
		((CButton *)GetDlgItem(IDC_RADIO_No7))->SetCheck(TRUE);
	else if (CurrentType =="Only6")
		((CButton *)GetDlgItem(IDC_RADIO_Only6))->SetCheck(TRUE);
	else if (CurrentType =="Only7")
		((CButton *)GetDlgItem(IDC_RADIO_Only7))->SetCheck(TRUE);
	else if (CurrentType =="Only67")
		((CButton *)GetDlgItem(IDC_RADIO_Only67))->SetCheck(TRUE);
	
	 // for action
	//AfxMessageBox(str);

	SetTimer(110,100,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SetDailyDlg::OnEveryDay() //Ã¿Ìì//Every Day
{

	app->ini.WriteString(_T("Daily"), _T("Type"), _T("EveryDay"));

}

void SetDailyDlg::OnNo67() 
{
	app->ini.WriteString(_T("Daily"), _T("Type"), _T("No67"));

}

void SetDailyDlg::OnRADIONo7() 
{
	app->ini.WriteString(_T("Daily"), _T("Type"), _T("No7"));

}


void SetDailyDlg::OnRADIOOnly6() 
{
	app->ini.WriteString(_T("Daily"), _T("Type"), _T("Only6"));

}

void SetDailyDlg::OnRADIOOnly7() 
{
	app->ini.WriteString(_T("Daily"), _T("Type"), _T("Only7"));

}

void SetDailyDlg::OnRADIOOnly67() 
{
	
	app->ini.WriteString(_T("Daily"), _T("Type"), _T("Only67"));

}

void SetDailyDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}
void SetDailyDlg::SetStatus(){
	
	if(app->IsCountDownNow==1)
	{
		((CButton *)GetDlgItem(IDC_RADIO_EveryDay))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_RADIO_No67))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_RADIO_No7))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_RADIO_Only6))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_RADIO_Only7))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_RADIO_Only67))->EnableWindow(false);
		
	}else{

		((CButton *)GetDlgItem(IDC_RADIO_EveryDay))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_RADIO_No67))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_RADIO_No7))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_RADIO_Only6))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_RADIO_Only7))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_RADIO_Only67))->EnableWindow(true);

	}
	

}