#if !defined(AFX_SETDAILYDLG_H__8357B67F_1650_4974_B065_412337195494__INCLUDED_)
#define AFX_SETDAILYDLG_H__8357B67F_1650_4974_B065_412337195494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDailyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetDailyDlg dialog
class CXTabCtrl;
class SetDailyDlg : public CDialog
{
// Construction
public:
	SetDailyDlg(CWnd* pParent = NULL);   // standard constructor
	CXTabCtrl* m_pTab;

// Dialog Data
	//{{AFX_DATA(SetDailyDlg)
	enum { IDD = IDD_Daily };
		// NOTE: the ClassWizard will add data members here
	CMagicShutdownApp *app;

	void SetStatus();
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetDailyDlg)
	public:
	protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetDailyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnEveryDay();
	afx_msg void OnNo67();
	afx_msg void OnRADIONo7();
	afx_msg void OnRADIOOnly6();
	afx_msg void OnRADIOOnly7();
	afx_msg void OnRADIOOnly67();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDAILYDLG_H__8357B67F_1650_4974_B065_412337195494__INCLUDED_)
