// SetCountDownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "magicshutdown.h"
#include "SetCountDownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCountDownDlg dialog


SetCountDownDlg::SetCountDownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetCountDownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetCountDownDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SetCountDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetCountDownDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetCountDownDlg, CDialog)
	//{{AFX_MSG_MAP(SetCountDownDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetCountDownDlg message handlers
