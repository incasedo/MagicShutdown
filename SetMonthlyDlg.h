#if !defined(AFX_SETMONTHLYDLG_H__0AB7047B_A09A_4D30_8BF9_9AF0B1405E53__INCLUDED_)
#define AFX_SETMONTHLYDLG_H__0AB7047B_A09A_4D30_8BF9_9AF0B1405E53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetMonthlyDlg.h : header file
//
class CFPSRecurringDates;

#include "sqlite./CppSQLite3.h"
#include "./date/FPSMiniCalendarCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// SetMonthlyDlg dialog

class SetMonthlyDlg : public CDialog
{
// Construction
public:
	SetMonthlyDlg(CWnd* pParent = NULL);   // standard constructor
	~SetMonthlyDlg();
	void ReloadDateList();

// Dialog Data
	//{{AFX_DATA(SetMonthlyDlg)
	enum { IDD = IDD_Monthly };

		// NOTE: the ClassWizard will add data members here

	CMagicShutdownApp *app;
	CComboBox	m_month_day_slect;
	static BOOL CALLBACK IsDateInPattern(COleDateTime& dt, DWORD dwParm);
	CFPSMiniCalendarCtrl	m_wndCalendar;


	CppSQLite3DB dbm;//sqlite 
	CppSQLite3Query rem;
//	CFPSRecurringDates*		m_pPattern;
	CPtrList				m_DateList;
	CStringList				m_DateListString;
	virtual BOOL OnSetActive();

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetMonthlyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeViewMode();
	afx_msg void OnClearBlackOuts();
	afx_msg void OnClearForceDates();
	//}}AFX_MSG
	afx_msg void OnCalendarViewChange( NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnCalendarClick( NMHDR * pNotifyStruct, LRESULT * result );


// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetMonthlyDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT nIDEvent);
	void SetStatus(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETMONTHLYDLG_H__0AB7047B_A09A_4D30_8BF9_9AF0B1405E53__INCLUDED_)
