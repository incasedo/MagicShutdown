// MagicShutdown.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MagicShutdown.h"
#include "MagicShutdownDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownApp

BEGIN_MESSAGE_MAP(CMagicShutdownApp, CWinApp)
	//{{AFX_MSG_MAP(CMagicShutdownApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownApp construction

CMagicShutdownApp::CMagicShutdownApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMagicShutdownApp object

CMagicShutdownApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownApp initialization

BOOL CMagicShutdownApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif



  ::GetModuleFileName(NULL, m_sAppPath.GetBuffer(MAX_PATH), MAX_PATH);
	m_sAppPath.ReleaseBuffer();
	if (m_sAppPath.Find('\\') != -1)
	{
		for (int i = m_sAppPath.GetLength() - 1; i >= 0; i--)
		{
			TCHAR ch = m_sAppPath[i];
			m_sAppPath.Delete(i);
			if (ch == '\\')
				break;	
		}
	}


	ini.SetPathName(m_sAppPath + _T("\\config.ini"));
	DateFormat = ini.GetString(_T("Global"), _T("DateFormat"));



	CMagicShutdownDlg dlg;


	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}