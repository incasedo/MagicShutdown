// MagicShutdownDlg.h : header file
//// Author: Paul Xiao

#if !defined(AFX_MagicShutdownDLG_H__F96B2364_EC17_4359_B825_8B6B07DA569A__INCLUDED_)
#define AFX_MagicShutdownDLG_H__F96B2364_EC17_4359_B825_8B6B07DA569A__INCLUDED_

#include "sqlite./CppSQLite3.h"
#include "afx.h"
#include "XTabCtrl.h"
#include "./gui/ComboBoxSuper.h"
#include "./gui/StaticCounter.h"
#include "./date/hightime.h"

#include "SetYearlyDlg.h"
#include "SetWeeklyDlg.h"
#include "SetMonthlyDlg.h"
#include "SetDailyDlg.h"
#include "ProcessDate.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define TIME_DISPLAY_FORMAT _T("%H:%M:%S.%s")

/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownDlg dialog
class SetDailyDlg;
class CMagicShutdownDlg : public CDialog
{
// Construction
public:
	CMagicShutdownDlg(CWnd* pParent = NULL);	// standard constructor

	CXTabCtrl	m_tabctrl;
	CImageList m_imagelistTab;
	SetYearlyDlg* m_set_year_dlg;
	SetWeeklyDlg* m_set_week_dlg;
	SetMonthlyDlg* m_set_month_dlg;
	SetDailyDlg* m_set_daily_dlg;
	CStaticCounter	m_Time;//数字式时钟
	
	ProcessDate m_pro_date;
	CHighTime		m_StartTime;//时间处理库
	CHighTimeSpan	m_Timetmp,m_TimeLeft;				// for timer

	BOOL	m_bImage;
	bool     isreg;
    CButton m_start;
	CButton m_pause;


	HWND m_Video;
	BOOL Pause;
	//user information
	CString uname,SN,soundname,sleeptime,usecount,md5code,setusecount;
	DWORD volume,dtvol,dttime,rate;
	int	TABSel;


	CString m_Path,dbfile;
	CString CurrentAction;//当前选中的动作
	CString isCountdown,IsForceClose;//是不是倒计时模式
	int CountdownTimeH,CountdownTimeM,CountdownTimeS,AutoShutdownTimeH,AutoShutdownTimeM,AutoShutdownTimeS;
	SYSTEMTIME systime,CheckNowTime;
	//sqlite connecter
    CppSQLite3DB db,db1;//sqlite 
	CppSQLite3Query re,re1;//sqlite Query data and also show results of inserts into auto-increment field
	

	bool CheckDate(int TABSel);
	bool ExcuAction(CString CurrentAction);
// Dialog Data
	//{{AFX_DATA(CMagicShutdownDlg)
	enum { IDD = IDD_MagicShutdown_DIALOG };
	CSliderCtrl	m_ctrlSlider;
	CMagicShutdownApp *app;
	CDateTimeCtrl  m_AutoShutdown;
	CDateTimeCtrl m_Countdown;

//	CComboBox m_ActionList;
	CComboBoxSuper	m_ActionList;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagicShutdownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//}}AFX_VIRTUAL

// Implementation
protected:
    //ctrl list

     CFileFind finder;


	BOOL m_bMinimized;
	void Reset();
	BOOL m_bStarted;
	BOOL m_bPaused;
	DWORD m_dwAction;
	HICON m_hIcon;

	HICON m_hAnimIcon[16], m_hBlankIcon;
	DWORD m_nIdxIcon;
	CBrush m_cBrush; 				

	NOTIFYICONDATA m_NotifyData;

	DWORD m_dwSec,m_dwMin;

	COleDateTime m_oleDateTime;
	CImageList m_ImageList;
	// Generated message map functions
	//{{AFX_MSG(CMagicShutdownDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnBtnApply();
	afx_msg void OnPopRestore();
	afx_msg void OnPopExit();
	afx_msg void OnBtnPause();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenFile();
	afx_msg bool InsertAction(CString path);
	afx_msg void OnPOPPlay();
	afx_msg void OnPOPDelete();
	afx_msg CString GetFileNameInPath(CString name);
	afx_msg void OnDestroy();
	afx_msg void Loop();
	afx_msg void OnRegNow();
	afx_msg void OnOnHelp();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCountdown();
	afx_msg void OnIsForceClose();
	afx_msg void OnChangeEdtseccnt();
	afx_msg void OnSelendokCOMBOActionList();
	afx_msg void OnDatetimechangeDATEAutoShutdown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDATECountDown(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	private:
	UINT m_nNumMixers;
	HMIXER m_hMixer;
	MIXERCAPS m_mxcaps;

	DWORD m_dwMinimum, m_dwMaximum;
	DWORD m_dwVolumeControlID;
	CString m_strDstLineName, m_strVolumeControlName;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MagicShutdownDLG_H__F96B2364_EC17_4359_B825_8B6B07DA569A__INCLUDED_)
