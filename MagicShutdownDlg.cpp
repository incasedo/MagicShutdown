
// RSA  
//Author Paul Xiao


#include "stdafx.h"
#include "MagicShutdown.h"
#include "MagicShutdownDlg.h"
//#include "vfw.h"
#include "./gui/Hyperlink.h"
#include "sha2.h"
#include "url.h"
#include "./date/oledatetimeex.h"
#include "diskid32lib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



HICON g_hBkupIcon;

const char *pszTrayNfMsg = "Tray Message";


#define WM_FIREEVENT	(WM_USER+0x00f2)

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	CHyperLink	m_cEmail;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_EMAIL, m_cEmail);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cEmail.SetURL(_T("http://cn.No2soft.com/"));
	
	
	CenterWindow();
	
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownDlg dialog

CMagicShutdownDlg::CMagicShutdownDlg(CWnd* pParent /*=NULL*/)
: CDialog(CMagicShutdownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMagicShutdownDlg)
	// NOTE: the ClassWizard will add member initialization here
	m_bImage = FALSE;
	m_hMixer = NULL;
	m_set_year_dlg=NULL;
	m_set_week_dlg=NULL;
	m_set_month_dlg=NULL;
	m_set_daily_dlg=NULL;
	app=(CMagicShutdownApp*)AfxGetApp(); 
	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	//iPlaying = PLAY;
}

void CMagicShutdownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMagicShutdownDlg)
	DDX_Control(pDX, IDC_TAB, m_tabctrl);
	DDX_Control(pDX, IDC_SLIDER, m_ctrlSlider);
	
	DDX_Control(pDX, IDC_BTNAPPLY, m_start);
	DDX_Control(pDX, IDC_BTNPAUSE, m_pause);
	DDX_Control(pDX, IDC_COMBOActionList, m_ActionList);
	
	DDX_Control(pDX, IDC_TimeShow, m_Time);
	DDX_Control(pDX, IDC_DATEAutoShutdown, m_AutoShutdown);
	DDX_Control(pDX, IDC_DATECountDown, m_Countdown);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMagicShutdownDlg, CDialog)
//{{AFX_MSG_MAP(CMagicShutdownDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BTNAPPLY, OnBtnApply)
ON_COMMAND(ID_POP_Restore, OnPopRestore)
ON_COMMAND(ID_POP_EXIT, OnPopExit)
ON_BN_CLICKED(IDC_BTNPAUSE, OnBtnPause)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_OpenFile, OnOpenFile)
ON_COMMAND(ID_POP_Play, OnPOPPlay)
ON_COMMAND(ID_POP_Delete, OnPOPDelete)
ON_WM_DESTROY()
ON_BN_CLICKED(IDRegNow, OnRegNow)
ON_BN_CLICKED(IDOnHelp, OnOnHelp)
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
ON_NOTIFY(NM_CLICK, IDC_TAB, OnClickTab)
ON_BN_CLICKED(IDC_Countdown, OnCountdown)
ON_BN_CLICKED(IDC_IsForceClose, OnIsForceClose)
ON_EN_CHANGE(IDC_EDTSECCNT, OnChangeEdtseccnt)
ON_CBN_SELENDOK(IDC_COMBOActionList, OnSelendokCOMBOActionList)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEAutoShutdown, OnDatetimechangeDATEAutoShutdown)
ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATECountDown, OnDatetimechangeDATECountDown)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagicShutdownDlg message handlers

BOOL CMagicShutdownDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	/*
	for(int i=0,j=IDI_ICON1;i<15;i++,j++)
	{
		m_hAnimIcon[i] = AfxGetApp()->LoadIcon(j);
	}
	m_hBlankIcon = AfxGetApp()->LoadIcon(IDI_ICONBLANK);
	
	m_NotifyData.cbSize = sizeof(NOTIFYICONDATA);
	m_NotifyData.hIcon = m_hIcon;
	m_NotifyData.hWnd = this->m_hWnd;
	m_NotifyData.uFlags = NIF_MESSAGE|NIF_TIP|NIF_ICON;
    _tcscpy(m_NotifyData.szTip, "MagicShutdown");
	m_NotifyData.uID = 1010; 
	m_NotifyData.uCallbackMessage = RegisterWindowMessage(pszTrayNfMsg);
	*/
	
	m_Time.SetDraw3DBar(FALSE);//设置时钟显示模式
	m_Time.Hide();//Hide Static Counter
	
	m_cBrush.CreateSysColorBrush(HS_CROSS);//4
	
	g_hBkupIcon = m_hIcon; 
	
	Reset();
	
	//add TABCtrl
	
	
	
	m_imagelistTab.Create(IDB_TABCTRL_IMAGE,17,0,  ILC_COLOR24);
	m_tabctrl.SetImageList(&m_imagelistTab);
	m_tabctrl.EnableToolTips(TRUE);
	//m_tabctrl.SetToolTips
	//ADD 按日
	m_set_daily_dlg = new SetDailyDlg;
	m_set_daily_dlg->Create(SetDailyDlg::IDD, &m_tabctrl);
	m_tabctrl.AddTab(m_set_daily_dlg, _T(app->ini.GetString(_T("Global"), _T("TAB0")).GetBuffer(0)), 0);
	m_set_daily_dlg->m_pTab = &m_tabctrl;
	//ADD 按周
	m_set_week_dlg = new SetWeeklyDlg;
	m_set_week_dlg->Create(SetWeeklyDlg::IDD, &m_tabctrl);
	m_tabctrl.AddTab(m_set_week_dlg, _T(app->ini.GetString(_T("Global"), _T("TAB1")).GetBuffer(0)), 1);
	//ADD 按月
	m_set_month_dlg = new SetMonthlyDlg;
	m_set_month_dlg->Create(SetMonthlyDlg::IDD, &m_tabctrl);
	m_tabctrl.AddTab(m_set_month_dlg, _T(app->ini.GetString(_T("Global"), _T("TAB2")).GetBuffer(0)), 2);
	
	//ADD 按年
	m_set_year_dlg = new SetYearlyDlg;
	m_set_year_dlg->Create(SetYearlyDlg::IDD, &m_tabctrl);
	m_tabctrl.AddTab(m_set_year_dlg, _T(app->ini.GetString(_T("Global"), _T("TAB3")).GetBuffer(0)), 3);
	
	
	//** customizing the tab control --------
	//	m_tabctrl.SetDisabledColor(RGB(255, 0, 0));
	m_tabctrl.SetSelectedColor(RGB(0, 0, 255));
	m_tabctrl.SetMouseOverColor(RGB(255, 0, 0));
	
	TABSel = app->ini.GetInt(_T("Global"), _T("TABSel"),0);
	m_tabctrl.SetCurFocus(TABSel);
	
	CountdownTimeH = app->ini.GetInt(_T("Global"), _T("CountdownTimeH"),00);
	CountdownTimeM = app->ini.GetInt(_T("Global"), _T("CountdownTimeM"),45);
	CountdownTimeS = app->ini.GetInt(_T("Global"), _T("CountdownTimeS"),0);
	
	CTime timeTime(2006, 1, 18, CountdownTimeH, CountdownTimeM, CountdownTimeS);
    VERIFY(m_Countdown.SetTime(&timeTime));
	
	//init AutoShutdown time control
	
	AutoShutdownTimeH = app->ini.GetInt(_T("Global"), _T("AutoShutdownTimeH"),23);//default 23 o'clock
	AutoShutdownTimeM = app->ini.GetInt(_T("Global"), _T("AutoShutdownTimeM"),0);
	AutoShutdownTimeS = app->ini.GetInt(_T("Global"), _T("AutoShutdownTimeS"),0);
	
	//年月日得从配置文件中取，现在只设定时间
	CTime shuttimeTime(2006, 1, 18, AutoShutdownTimeH, AutoShutdownTimeM, AutoShutdownTimeS);
    VERIFY(m_AutoShutdown.SetTime(&shuttimeTime));
	
	//是否强行关闭程序
	if (app->ini.GetString(_T("Global"), _T("IsForceClose")) == "1") {
		IsForceClose="1";
		((CButton *)GetDlgItem(IDC_IsForceClose))->SetCheck(TRUE);
		
	}else
		IsForceClose="0";
	//是否倒计时
	if (app->ini.GetString(_T("Global"), _T("isCountdown")) == "1") {
		isCountdown="1";
		((CButton *)GetDlgItem(IDC_Countdown))->SetCheck(TRUE);
		m_AutoShutdown.EnableWindow(false);
		m_Countdown.EnableWindow(true);
		app->IsCountDownNow=1;

	}else{
		isCountdown="0";
		//Lock countdown control.
		m_Countdown.EnableWindow(false);
		m_AutoShutdown.EnableWindow(true);
		app->IsCountDownNow=0;
	}
	//init db
	//open db & read db data then insert into play list
    dbfile =  app->m_sAppPath+_T("\\d.db3");
	db.open(dbfile);
	//get user info
	
	CString sql = "select * from user where uid=1";
	re = db.query(sql); 	
	soundname = re.fieldValue("soundname");
	md5code = re.fieldValue("md5");
	
	sleeptime = re.fieldValue("sleeptime");
	//	GetDlgItem(IDC_EDTMINCNT)->SetWindowText(sleeptime);
	
	//get user use count number
	volume = re.getIntField("volume");	
	re.finalize();
	
	//初始化动作列表
	m_ImageList.Attach(ImageList_Create(16,16,ILC_COLORDDB | ILC_MASK,10,10));
	CBitmap bmp;
	bmp.LoadBitmap(IDB_ActionList);
	m_ImageList.Add(&bmp,RGB(0,0,128));
	
	m_ActionList.SetImageList(&m_ImageList);
	
	m_ActionList.SetColumnCount(2);
	m_ActionList.SetColumnWidth(0, 60);
	m_ActionList.SetColumnWidth(1, 180);
	sql = "select * from  action";
    re = db.query(sql); 
	int tmp=-1,ImageNum;
	while (!re.eof())
    {
		tmp++;
		m_ActionList.AddString(re.fieldValue("aname"));
		m_ActionList.SetItemText(tmp,1,re.fieldValue("description"));
		if (tmp>6) ImageNum=6;
		else ImageNum=tmp;
		m_ActionList.SetItemImage(tmp,ImageNum);
		re.nextRow();
	}
	re.finalize();
	tmp=0;
	int GetCurrentAction = app->ini.GetInt(_T("Global"), _T("CurrentAction"),0);
	CurrentAction.Format("%d",GetCurrentAction);
    m_ActionList.SetCurSel(GetCurrentAction);
	

	
	m_pause.EnableWindow(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CMagicShutdownDlg::OnDestroy() 
{
	if (m_set_year_dlg)
		delete m_set_year_dlg;
	
	if (m_set_week_dlg)
		delete m_set_week_dlg;
	
	if (m_set_month_dlg)
		delete m_set_month_dlg;
	
	if (m_set_daily_dlg)
		delete m_set_daily_dlg;
	
	
	CDialog::OnDestroy();
}


CString CMagicShutdownDlg::GetFileNameInPath(CString name)
{
	CString sql = "select * from nlist where vname='"+name+"' ";
	re = db.query(sql); 	
    CString result; 
	result = re.fieldValue("path");
	re.finalize();
	
	//check file wether exist.
	if( !finder.FindFile(result) ) 
	{	  
		CString strPath,m_sFile; 	
		TCHAR exeFullPath[MAX_PATH]; 
		GetModuleFileName(NULL,exeFullPath,MAX_PATH); 
		strPath=(CString)exeFullPath; 
		int position=strPath.ReverseFind('\\'); 
		strPath=strPath.Left(position+1); 	
		result = strPath +"\\sound\\" + name +".mp3";
	}
	//AfxMessageBox(result);
    return result;
}

void CMagicShutdownDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
		if (nID == SC_MINIMIZE) 
		{
			//Shell_NotifyIcon(NIM_ADD,&m_NotifyData);
			//ShowWindow(SW_HIDE);
			//m_bMinimized = true;
		} 
		else if (nID == SC_RESTORE)
		{
			//Shell_NotifyIcon(NIM_DELETE,&m_NotifyData);
			//m_bMinimized = false;
		}
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMagicShutdownDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMagicShutdownDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMagicShutdownDlg::OnCancel() 
{
/*
if(MessageBox("Do you want to exit ?","MagicShutdown",MB_YESNO|MB_ICONQUESTION) == IDNO)
return;

  GetDlgItem(IDC_FRAOPT)->SetWindowPos(NULL,11,0,457-11,242-0,SWP_SHOWWINDOW);
  int tmp;
  tmp = m_ctrlSlider.GetPos();
  CString tmp1;
  tmp1.Format("%d",tmp);
  
	
	  CString sql = "update user set volume='"+ tmp1 +"' where uid=1";
	  db.query(sql); 	
	  
	*/
	
	Shell_NotifyIcon(NIM_DELETE,&m_NotifyData);
	CDialog::OnCancel();
	
}

/// need to handle tray icon
LRESULT CMagicShutdownDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CMenu cMenu, *pSubMenu;
	if(message == m_NotifyData.uCallbackMessage)
	{
		if (LOWORD(lParam) == WM_RBUTTONUP)
		{    
			if (!cMenu.LoadMenu(IDR_MNUTRAY)) return 0;
			if (!(pSubMenu = cMenu.GetSubMenu(0))) return 0;
			
			// Make chosen menu item the default (bold font)
			//::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);
			
			// Display and track the popup menu
			CPoint pos;
			GetCursorPos(&pos);
			
			SetForegroundWindow();  
			::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, GetSafeHwnd(), NULL);
			
			// BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
			PostMessage(WM_NULL, 0, 0);
			
			cMenu.DestroyMenu();
		} 
		else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
		{
			// double click received, the default action is to execute default menu item
			SetForegroundWindow();  
			
			UINT uItem;
			if (!cMenu.LoadMenu(IDR_MNUTRAY)) return 0;
			if (!(pSubMenu = cMenu.GetSubMenu(0))) return 0;
			uItem = pSubMenu->GetMenuItemID(0);
			
			SendMessage(WM_COMMAND, uItem, 0);
			
			cMenu.DestroyMenu();
		}
		
	}
	return CDialog::WindowProc(message, wParam, lParam);	
}

// when apply button clicked
void CMagicShutdownDlg::OnBtnApply() 
{
	m_StartTime = CHighTime::GetPresentTime();
	//Show Time Counter
	m_Time.Show();
	
	
	if (isCountdown == "1") {

		m_TimeLeft.SetHighTimeSpan(0, CountdownTimeH, CountdownTimeM, CountdownTimeS, 0, 0, 0);	// for timer
		m_Time.Display(m_TimeLeft.Format(TIME_DISPLAY_FORMAT));
		
	}else {
		m_Time.Display(m_StartTime.Format(TIME_DISPLAY_FORMAT));
	}
	
	
	SetTimer(101,100,0); // for action
//	SetTimer(102,30,0); // for animated icon
	
	m_bMinimized = m_bStarted = true;
	
	// after auccessful apply minimize the dialog
	
	
	
//	Shell_NotifyIcon(NIM_ADD,&m_NotifyData);
	m_start.EnableWindow(false);
	m_pause.EnableWindow(true);
	
	
	//SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
	m_tabctrl.EnableTab(0,0);
	m_tabctrl.EnableTab(1,0);
	m_tabctrl.EnableTab(2,0);
	m_tabctrl.EnableTab(3,0);


}

// on the tay popup menu user cliecked restore
void CMagicShutdownDlg::OnPopRestore() 
{
	ShowWindow(SW_SHOWNORMAL);
	m_bMinimized = false;
	Shell_NotifyIcon(NIM_DELETE,&m_NotifyData);
}

// on the tay popup menu user cliecked exit
void CMagicShutdownDlg::OnPopExit() 
{
	PostQuitMessage(0);
}

// when pause button clicked 
void CMagicShutdownDlg::OnBtnPause() 
{
	KillTimer(101);
	KillTimer(102);
	if(m_bMinimized)
	{
		m_NotifyData.hIcon = m_hIcon;
		_tcscpy(m_NotifyData.szTip, "MagicShutdown");
		
		Shell_NotifyIcon(NIM_MODIFY,&m_NotifyData);
	}
	
	m_hIcon = m_hAnimIcon[m_nIdxIcon];
	
	
	m_bPaused = true;
	m_bStarted = false;
	m_pause.EnableWindow(false);
	m_start.EnableWindow(true);
	m_tabctrl.EnableTab(0,1);
	m_tabctrl.EnableTab(1,1);
	m_tabctrl.EnableTab(2,1);
	m_tabctrl.EnableTab(3,1);

}

// this is the timer starts ticking when applied
//    this also makes the icon blink
void CMagicShutdownDlg::OnTimer(UINT nIDEvent) 
{/// two timer event comes here
	
	if(nIDEvent == 101)
	{
		
		CString s = _T("");
		//m_Time.Display(curtime.Format(TIME_DISPLAY_FORMAT));
		if (isCountdown=="1") {//倒计时模式
			CHighTimeSpan ts = CHighTimeSpan(0, 0, 0, 0, 100, 0, 0);//10毫秒递减
			m_TimeLeft -= ts;
			m_Timetmp = m_TimeLeft;
			m_Timetmp-=200;
			s = m_Timetmp.Format(TIME_DISPLAY_FORMAT);	
			if (m_TimeLeft >= CHighTimeSpan(0, 0, 0, 0, 100, 0, 0))
			{
				m_Time.Display(s);
				m_Time.UpdateWindow();
				return;
			}else{//执行动作
				
				//MessageBox("dd");
				KillTimer(101);
				KillTimer(102);
				//	if (CheckDate(TABSel) )//方便测试，到时要去掉
				ExcuAction(CurrentAction);

			}
		}else{//普通模式,计时模式    
			::GetLocalTime(&systime);
			CHighTimeSpan checkcurtime =  CHighTimeSpan(0, systime.wHour, systime.wMinute, systime.wSecond, 0, 0, 0);
			if (checkcurtime != CHighTimeSpan(0, AutoShutdownTimeH, AutoShutdownTimeM, AutoShutdownTimeS, 0, 0, 0))
			{
				CHighTimeSpan curtime = CHighTimeSpan(0, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds, 0, 0);
				m_Time.Display(curtime.Format(TIME_DISPLAY_FORMAT));		
				m_Time.UpdateWindow();
				return;
			}else{//执行动作
				//MessageBox("dd");
				if (CheckDate(TABSel) ) {//检查当天是否要响应动作

					//KillTimer(101);
					//KillTimer(102);
					ExcuAction(CurrentAction);
					return;	
				}
			}
			
		}
		
	}
	else if(nIDEvent == 102)
	{// this is the secon timer
		//   blinks the icon and displays the tool tip on the tray
		
		//whether loop
		
		if(m_bMinimized)
		{
			if(m_bStarted)
			{
				m_NotifyData.hIcon = m_hAnimIcon[m_nIdxIcon];
				m_nIdxIcon++;
				if(m_nIdxIcon >=14)
					m_nIdxIcon = 0;
				
				sprintf(m_NotifyData.szTip,"Min: %d, Sec: %d",m_dwMin,m_dwSec);
			}
			else
				m_NotifyData.hIcon = m_hIcon;
			Shell_NotifyIcon(NIM_MODIFY,&m_NotifyData);
		}
		else
		{
			if(m_bStarted)
			{
				m_nIdxIcon++;
				if(m_nIdxIcon >=14)
					m_nIdxIcon = 0;
				
			}
			else
			{
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

// resets any action going
//  if the user changes the combo the on going action will be reset
void CMagicShutdownDlg::Reset()
{
	if(m_bPaused)
	{
		m_bPaused = false;
		GetDlgItem(IDC_BTNPAUSE)->SetWindowText("暂停");
	}
	m_bStarted = false;
	
	// kill the timers
	KillTimer(101);
	KillTimer(102);
	
	m_NotifyData.hIcon = m_hIcon;
	_tcscpy(m_NotifyData.szTip, "MagicShutdown");
	
	if(m_bMinimized)
	{
		Shell_NotifyIcon(NIM_MODIFY,&m_NotifyData);
	}
	
	m_hIcon = g_hBkupIcon;
	
	// incase the dialog is minimized restore it
	m_bMinimized = false;
	m_nIdxIcon = 0;
	m_NotifyData.hIcon = m_hIcon;
}

BOOL CMagicShutdownDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_KEYDOWN)
	{
		if (pMsg->wParam==VK_ESCAPE)
			return TRUE;
		if (pMsg->wParam==VK_RETURN)
			return TRUE;
	}







	return CDialog::PreTranslateMessage(pMsg);
}


void CMagicShutdownDlg::OnOpenFile() 
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[]= _T("Exe File (*.exe)|*.exe|");
	CFileDialog MediaFile(TRUE, _T("Exe File"), _T("*.exe"),
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_LONGNAMES,
		szFilter);
	
	TCHAR szTitle[]=_T("Open File");
	MediaFile.m_ofn.lpstrTitle=szTitle;
	
	int iResult;
	iResult=MediaFile.DoModal();
	if (iResult==IDOK)
	{	
		//增加自定义动作
		InsertAction(MediaFile.GetPathName());	
		
	}	
}

bool CMagicShutdownDlg::InsertAction(CString path){//插入动作
	
	//parse path
	//得到纯文件名（不带路径） strFilename
	CString strFilename(path);
	strFilename=strFilename.Right(strFilename.GetLength() - strFilename.ReverseFind('\\') - 1);
    //得到文件名
	int nlen=strFilename.ReverseFind('.');
	strFilename = strFilename.Left(nlen);
	//AfxMessageBox(strFilename);
	
	//insert into db
	
	CString sql;
	sql = "insert into action (aname,run) values ('"+strFilename+"','"+path+"')";
	re = db.query(sql); 	
	re.finalize();
	
	sql = "select count(id) as tt from action";
	re = db.query(sql); 		
	int tmpimg = re.getIntField("tt");
	re.finalize();
	
	
	AfxMessageBox(app->ini.GetString(_T("Message"), _T("HaveBeenInsertAction")));
    m_ActionList.AddString(strFilename);
	m_ActionList.SetItemImage(tmpimg,6);//?
	
	
	
	return 0;
}

void CMagicShutdownDlg::OnPOPPlay() 
{
	//写入状态库
	/*
	CString sql = "update user set soundname='"+pString+"' where uid=1";
	db.query(sql); 	
	
	  if (!pString.IsEmpty()) {
	  SetTimer(102,30,0);
	  pString = GetFileNameInPath(pString);//get path			
	  
		MCIWndStop(m_Video);
		Play(pString,1000);
		
		  }
	*/
	
}

void CMagicShutdownDlg::OnPOPDelete() 
{
	// TODO: Add your command handler code here
	
	
	/*	
	CString sql;
	sql = "delete from nlist where vname='"+pString1+"' ";
	db.query(sql); 	
	
	  UpdateData(TRUE);
	  
	*/
	
    
	//MessageBox(pString);//显示当前选中的路径
}



void CMagicShutdownDlg::OnRegNow() 
{
	// TODO: Add your control notification handler code here
	CString infoOrderURL;
	infoOrderURL.LoadString(IDS_OrderURL);
	//CURL url;
	//	url.Open(infoOrderURL);	
	
	::ShellExecute(NULL, NULL, _T(infoOrderURL), NULL, NULL, SW_SHOWNORMAL);
	   // ShowRegister dlg;	
	//	dlg.DoModal();
	
}

void CMagicShutdownDlg::OnOnHelp() 
{
	
    CString helpfile =  app->m_sAppPath+_T("\\help.chm");
	//WinExec("hh.exe" + helpfile,SW_SHOWNORMAL);
	ShellExecute (0, "open", helpfile, "", "", SW_SHOWNORMAL);
	//HtmlHelp(NULL, (LPCSTR)helpfile, HH_DISPLAY_TOPIC, 0);

}

void CMagicShutdownDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CMagicShutdownDlg::OnClickTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString tmp;
	tmp.Format ("%d",m_tabctrl.GetCurSel( ));
	//取得当前在第几个TAB选项中。
	app->ini.WriteString(_T("Global"), _T("TABSel"), _T(tmp));
	TABSel=m_tabctrl.GetCurSel( );
    //	AfxMessageBox(tmp);
	*pResult = 0;
}

void CMagicShutdownDlg::OnCountdown() 
{
	
	
	//是否要倒计时
	if ( ((CButton *)GetDlgItem(IDC_Countdown))->GetCheck() ) {
		m_Countdown.EnableWindow(true);
		m_AutoShutdown.EnableWindow(false);
		isCountdown="1";

		//禁用Ctab
			m_tabctrl.EnableTab(0,0);
			m_tabctrl.EnableTab(1,0);
			m_tabctrl.EnableTab(2,0);
			m_tabctrl.EnableTab(3,0);
			app->IsCountDownNow=1;
	}else{
		
		isCountdown="0";
		m_Countdown.EnableWindow(false);
		m_AutoShutdown.EnableWindow(true);
		m_tabctrl.EnableTab(0,1);
		m_tabctrl.EnableTab(1,1);
		m_tabctrl.EnableTab(2,1);
		m_tabctrl.EnableTab(3,1);
		app->IsCountDownNow=0;

	}
	app->ini.WriteString(_T("Global"), _T("isCountdown"), _T(isCountdown));
	//停止运行
	m_Time.Hide();
	m_start.EnableWindow(true);
	m_pause.EnableWindow(false);
	KillTimer(101);
	KillTimer(102);
	Shell_NotifyIcon(NIM_DELETE,&m_NotifyData);
	//进行子窗口的状态设定
	if (TABSel ==0)
		m_set_daily_dlg->SetStatus();
	else if (TABSel ==1)
	    m_set_week_dlg->SetStatus();
	else if (TABSel ==2)
	    m_set_month_dlg->SetStatus();
	else if (TABSel ==3)
	    m_set_year_dlg->SetStatus();

}

void CMagicShutdownDlg::OnIsForceClose() 
{
	//是否强行关闭程序
	if ( ((CButton *)GetDlgItem(IDC_IsForceClose))->GetCheck() ) {
		IsForceClose="1";
	}else
		IsForceClose="0";
	app->ini.WriteString(_T("Global"), _T("IsForceClose"), _T(IsForceClose));
}

void CMagicShutdownDlg::OnChangeEdtseccnt() 
{
	CString ShutSecondTime;
	GetDlgItem(IDC_EDTSECCNT)->GetWindowText(ShutSecondTime);
	app->ini.WriteString(_T("Global"), _T("ShutSecondTime"), _T(ShutSecondTime));	
}

void CMagicShutdownDlg::OnSelendokCOMBOActionList() 
{
	int n = m_ActionList.GetCurSel();
	
	CurrentAction.Format ("%d",n);
	app->ini.WriteString(_T("Global"), _T("CurrentAction"), _T(CurrentAction));
	
}
bool CMagicShutdownDlg::CheckDate(int TABSel){
	CString CurrentType;
	CString W1,W2,W3,W4,W5,W6,W7; 
	CString sql_m,m_date_now;
	SetMonthlyDlg mdlg;
	
	::GetLocalTime(&CheckNowTime);//取得当前时间
	COleDateTimeEx dt;
	dt.SetDate(CheckNowTime.wYear,CheckNowTime.wMonth,CheckNowTime.wDay);
	CString strDate = dt.Format("%m-%d-%Y");
	//开始按规则处理

	switch(TABSel){
	case 0:{//按天来分动作
		CurrentType = app->ini.GetString(_T("Daily"), _T("Type"));
		if (CurrentType =="EveryDay"){//每天
			return true;
		}else if (CurrentType =="No67"){//没有周六日
			if (CheckNowTime.wDayOfWeek != 6 && CheckNowTime.wDayOfWeek != 0)
				return true;
		}else if (CurrentType =="No7"){
			if ( CheckNowTime.wDayOfWeek != 0)
				return true;
		}else if (CurrentType =="Only6"){
			if ( CheckNowTime.wDayOfWeek == 6)
				return true;
			
		}else if (CurrentType =="Only7"){
			if ( CheckNowTime.wDayOfWeek == 0)
				return true;
			
		}else if (CurrentType =="Only67"){
			if (CheckNowTime.wDayOfWeek == 6 || CheckNowTime.wDayOfWeek == 0 )
				return true;
		}
		
		break;
		   }
	case 1:{//按周来分
		
		
		W1 = app->ini.GetString(_T("Weekly"), _T("W1"));
		W2 = app->ini.GetString(_T("Weekly"), _T("W2"));
		W3 = app->ini.GetString(_T("Weekly"), _T("W3"));
		W4 = app->ini.GetString(_T("Weekly"), _T("W4"));
		W5 = app->ini.GetString(_T("Weekly"), _T("W5"));
		W6 = app->ini.GetString(_T("Weekly"), _T("W6"));
		W7 = app->ini.GetString(_T("Weekly"), _T("W7"));
		
		if (W1 =="1" && CheckNowTime.wDayOfWeek==1)
			return true;
		else if (W2 =="1" && CheckNowTime.wDayOfWeek==2)
			return true;		
		else if (W3 =="1" && CheckNowTime.wDayOfWeek==3)
			return true;
		else if (W4 =="1" && CheckNowTime.wDayOfWeek==4)
			return true;
		else if (W5 =="1" && CheckNowTime.wDayOfWeek==5)
			return true;
		else if (W6 =="1" && CheckNowTime.wDayOfWeek==6)
			return true;
		else if (W7 =="1" && CheckNowTime.wDayOfWeek==0)
			return true;
		
		break;
		   }case 2:{//按月来分	
			   
			   mdlg.dbm.open(app->m_sAppPath+_T("\\monthly.db3"));
			   sql_m = "select * from  monthly";
			   mdlg.rem = mdlg.dbm.query(sql_m); 
			   while (!mdlg.rem.eof())
			   {
				   
				   if (strDate == mdlg.rem.fieldValue("date") ) {//如果附合条件，就返回真
					   return true;
					   break;
				   }
				   
				   mdlg.rem.nextRow();
			   }
			   mdlg.rem.finalize();
			   break;
		   }case 3:{
			   CString Currentdate = app->ini.GetString(_T("Yearly"), _T("date"));
			   if (Currentdate == strDate)
				   return true;
			   break;
			   
		   }
	default:
		return false;
		break;
	}


	return false;
}
bool CMagicShutdownDlg::ExcuAction(CString CurrentAction){
	
	//get shutdown function
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	// Get a token for this process. 
	
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		return false;
	// Get the LUID for the shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 	(PTOKEN_PRIVILEGES)NULL, 0); 
	
	
	CString LBtext,aname,run;
	int id;
	m_ActionList.GetLBText(m_ActionList.GetCurSel(),LBtext);
	
	
	CString sql = "select * from  action where aname='"+LBtext+"'";
	re = db.query(sql); 
	if (!re.eof())
	{
		aname = re.fieldValue("aname");
		id = atoi(re.fieldValue("id"));
		run = re.fieldValue("run");
		
		switch (id) {
			
		case 1:{//关机Shut down
			if ( IsForceClose == "1" )
				ExitWindowsEx(EWX_SHUTDOWN|EWX_POWEROFF|EWX_FORCE,0);
			else
				ExitWindowsEx(EWX_SHUTDOWN|EWX_POWEROFF,0);
			
			break;
			
			   }case 2://重启Restart
			if (IsForceClose == "1" )
				ExitWindowsEx(EWX_REBOOT|EWX_FORCE,0);
			else
				ExitWindowsEx(EWX_REBOOT,0);		
			break;
		case 3://注销Log Off
			if (IsForceClose == "1" )
				ExitWindowsEx(EWX_LOGOFF|EWX_FORCE,0);
			else
				ExitWindowsEx(EWX_LOGOFF,0);					
			break;
		case 4://休眠 Hibernate
			SetSystemPowerState( FALSE, FALSE );			
			break;
		case 5://等待Stand By
			SetSystemPowerState( TRUE, TRUE);
			break;
		case 6:{//挂断网络
			///InternetCheckConnection(HostName.c_str(),   1,   0) 
			break;
			   }
		case 7://锁定电脑
			
			break;
		case 8://锁定IE
			
			break;	
		default:
			WinExec(run,SW_NORMAL);
			break;
		}
		
		
		
		re.nextRow();
	}
	re.finalize();	

	m_start.EnableWindow(true);
	m_pause.EnableWindow(false);

	return false;
}



void CMagicShutdownDlg::OnDatetimechangeDATEAutoShutdown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	//MessageBox("dd");
	CTime shuttimeTime;
	m_AutoShutdown.GetTime(shuttimeTime);

	AutoShutdownTimeH = shuttimeTime.GetHour() ;
	AutoShutdownTimeM = shuttimeTime.GetMinute();
	AutoShutdownTimeS = shuttimeTime.GetSecond();

	app->ini.WriteInt(_T("Global"), _T("AutoShutdownTimeH"), _T(shuttimeTime.GetHour() ));
	app->ini.WriteInt(_T("Global"), _T("AutoShutdownTimeM"), _T(shuttimeTime.GetMinute() ));
	app->ini.WriteInt(_T("Global"), _T("AutoShutdownTimeS"), _T(shuttimeTime.GetSecond() ));
	
	*pResult = 0;
}

void CMagicShutdownDlg::OnDatetimechangeDATECountDown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	CTime CountdownTimet;
	m_Countdown.GetTime(CountdownTimet);
	CountdownTimeH = CountdownTimet.GetHour();
	CountdownTimeM = CountdownTimet.GetMinute() ;
	CountdownTimeS = CountdownTimet.GetSecond();

	app->ini.WriteInt(_T("Global"), _T("CountdownTimeH"), _T(CountdownTimet.GetHour() ));
	app->ini.WriteInt(_T("Global"), _T("CountdownTimeM"), _T(CountdownTimet.GetMinute() ));
	app->ini.WriteInt(_T("Global"), _T("CountdownTimeS"), _T(CountdownTimet.GetSecond() ));
	
	*pResult = 0;
}
