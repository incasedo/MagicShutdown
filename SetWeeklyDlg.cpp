// SetWeeklyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "magicshutdown.h"
#include "SetWeeklyDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;

#endif



/////////////////////////////////////////////////////////////////////////////
// SetWeeklyDlg dialog


SetWeeklyDlg::SetWeeklyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetWeeklyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetWeeklyDlg)
		app=(CMagicShutdownApp*)AfxGetApp(); 
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SetWeeklyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetWeeklyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetWeeklyDlg, CDialog)
	//{{AFX_MSG_MAP(SetWeeklyDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetWeeklyDlg message handlers
BOOL SetWeeklyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//COleDateTime curTime = COleDateTime::GetCurrentTime();

	CString W1 = app->ini.GetString(_T("Weekly"), _T("W1"));
	CString W2 = app->ini.GetString(_T("Weekly"), _T("W2"));
	CString W3 = app->ini.GetString(_T("Weekly"), _T("W3"));
	CString W4 = app->ini.GetString(_T("Weekly"), _T("W4"));
	CString W5 = app->ini.GetString(_T("Weekly"), _T("W5"));
	CString W6 = app->ini.GetString(_T("Weekly"), _T("W6"));
	CString W7 = app->ini.GetString(_T("Weekly"), _T("W7"));

	//set default radio
	if (W1 =="1")
		((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK1))->SetCheck(FALSE);

	if (W2 =="1")
		((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
	
	if (W3 =="1")
		((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK3))->SetCheck(FALSE);

	if (W4 =="1")
		((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK4))->SetCheck(FALSE);

	if (W5 =="1")
		((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK5))->SetCheck(FALSE);


	if (W6 =="1")
		((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK6))->SetCheck(FALSE);

	if (W7 =="1")
		((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(TRUE);
	else 
		((CButton *)GetDlgItem(IDC_CHECK7))->SetCheck(FALSE);

	
	//AfxMessageBox(str);

	SetTimer(110,100,0);
	return TRUE;  
}
void SetWeeklyDlg::OnCheck1() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W1"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W1"), _T("0"));
}

void SetWeeklyDlg::OnCheck2() 
{
		if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W2"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W2"), _T("0"));

}

void SetWeeklyDlg::OnCheck3() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W3"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W3"), _T("0"));

}

void SetWeeklyDlg::OnCheck4() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W4"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W4"), _T("0"));

}

void SetWeeklyDlg::OnCheck5() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W5"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W5"), _T("0"));
	
}

void SetWeeklyDlg::OnCheck6() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W6"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W6"), _T("0"));

}

void SetWeeklyDlg::OnCheck7() 
{
	if (((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck())
		app->ini.WriteString(_T("Weekly"), _T("W7"), _T("1"));
	else
		app->ini.WriteString(_T("Weekly"), _T("W7"), _T("0"));
	
}

void SetWeeklyDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}

void SetWeeklyDlg::SetStatus(void)
{

	if( app->IsCountDownNow==1)
	{
		
		((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK2))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK3))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK4))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK5))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK6))->EnableWindow(false);
		((CButton *)GetDlgItem(IDC_CHECK7))->EnableWindow(false);
	
		
	}else{

		((CButton *)GetDlgItem(IDC_CHECK1))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK2))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK3))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK4))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK5))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK6))->EnableWindow(true);
		((CButton *)GetDlgItem(IDC_CHECK7))->EnableWindow(true);

	}
}
