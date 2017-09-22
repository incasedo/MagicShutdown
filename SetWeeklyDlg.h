#if !defined(AFX_SETWEEKLYDLG_H__80F2AAB0_D2AC_453C_9B91_53F6D994BB44__INCLUDED_)
#define AFX_SETWEEKLYDLG_H__80F2AAB0_D2AC_453C_9B91_53F6D994BB44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWeeklyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetWeeklyDlg dialog

class SetWeeklyDlg : public CDialog
{
// Construction
public:
	SetWeeklyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetWeeklyDlg)
	enum { IDD = IDD_Weekly };
	//}}AFX_DATA
	CMagicShutdownApp *app;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetWeeklyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetWeeklyDlg)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
	void SetStatus(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETWEEKLYDLG_H__80F2AAB0_D2AC_453C_9B91_53F6D994BB44__INCLUDED_)
