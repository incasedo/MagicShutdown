#if !defined(AFX_SETYEARLYDLG_H__AA213551_B43E_4CBD_9A62_B37D177E87E0__INCLUDED_)
#define AFX_SETYEARLYDLG_H__AA213551_B43E_4CBD_9A62_B37D177E87E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetYearlyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetYearlyDlg dialog

class SetYearlyDlg : public CDialog
{
// Construction
public:
	SetYearlyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetYearlyDlg)
	enum { IDD = IDD_Yearly };
	CMagicShutdownApp *app;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetYearlyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetYearlyDlg)

	afx_msg void OnCloseupDATETIMEPICKERYears(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetStatus(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETYEARLYDLG_H__AA213551_B43E_4CBD_9A62_B37D177E87E0__INCLUDED_)
