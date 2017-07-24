
// ServerMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerMain.h"
#include "ServerMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)



END_MESSAGE_MAP()


// CServerMainDlg 对话框



CServerMainDlg::CServerMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERVERMAIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerMainDlg::OnBnClickedOk)

	//比如这里映射了个函数
	ON_COMMAND(ID_32771, &CServerMainDlg::On32771)
	//相当于连接信号和槽 (命令消息映射宏)
	ON_COMMAND(IDM_ONLINE_CMD, &CServerMainDlg::OnOnlineCmd)
	ON_COMMAND(IDM_ONLINE_PS, &CServerMainDlg::OnOnlineProcess)
	ON_COMMAND(IDM_ONLINE_WIN, &CServerMainDlg::OnOnlineWindow)
	ON_COMMAND(IDM_ONLINE_DESKTOP, &CServerMainDlg::OnOnlineDesktop)
	ON_COMMAND(IDM_ONLINE_FILE, &CServerMainDlg::OnOnlineFile)
	ON_COMMAND(IDM_ONLINE_VOICE, &CServerMainDlg::OnOnlineAudio)
	ON_COMMAND(IDM_ONLINE_VIDEO, &CServerMainDlg::OnOnlineVideo)
	ON_COMMAND(IDM_ONLINE_SERVER, &CServerMainDlg::OnOnlineServer)
	ON_COMMAND(IDM_ONLINE_REG, &CServerMainDlg::OnOnlineRegister)
	//	ON_COMMAND(IDM_ONLINE_DELETE, &CRemoteDlg::OnOnlineDelete)
	//	ON_COMMAND(IDM_MAIN_CLOSE, &CRemoteDlg::OnMainClose)

	//可以把不同的东西写成同一个ID这样两个效果对应同一个映射
	ON_COMMAND(IDM_MAIN_ABOUT, &CServerMainDlg::OnMainAbout)
	ON_COMMAND(IDM_MAIN_SET, &CServerMainDlg::OnMainSet)
	ON_COMMAND(IDM_MAIN_GEN, &CServerMainDlg::OnMainBuild)
	//	ON_COMMAND(IDM_MAIN_CLOSE, &CServerMainDlg::OnMainClose)
END_MESSAGE_MAP()


// CServerMainDlg 消息处理程序

BOOL CServerMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//以上为系统生成代码

	// TODO: 在此添加额外的初始化代码
	
	CreateToolBar();               //添加工具条


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//初始化工具条
void CServerMainDlg::CreateToolBar(void)
{

	if (!mToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!mToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))  //创建一个工具条  加载资源
	{

		return;
	}
	mToolBar.ModifyStyle(0, TBSTYLE_FLAT);    //Fix for WinXP
	mToolBar.LoadTrueColorToolBar
	(
		54,    //加载真彩工具条
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN
	);  //和我们的位图资源相关联
	RECT rt, rtMain;
	GetWindowRect(&rtMain);   //得到整个窗口的大小
	rt.left = 0;
	rt.top = 0;
	rt.bottom = 80;
	rt.right = rtMain.right - rtMain.left + 10;
	mToolBar.MoveWindow(&rt, TRUE);

	mToolBar.SetButtonText(0, "终端管理");     //在位图的下面添加文字
	mToolBar.SetButtonText(1, "进程管理");
	mToolBar.SetButtonText(2, "窗口管理");
	mToolBar.SetButtonText(3, "桌面管理");
	mToolBar.SetButtonText(4, "文件管理");
	mToolBar.SetButtonText(5, "语音管理");
	mToolBar.SetButtonText(6, "视频管理");
	mToolBar.SetButtonText(7, "服务管理");
	mToolBar.SetButtonText(8, "注册表管理");
	mToolBar.SetButtonText(9, "参数设置");
	mToolBar.SetButtonText(10, "生成服务端");
	mToolBar.SetButtonText(11, "帮助");

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);  //显示

}

void CServerMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	//this->CloseWindow();
}



void CServerMainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




void CServerMainDlg::On32771() //菜单关于
{	
	CDialogEx::OnOK();	
	// TODO: 在此添加命令处理程序代码
}

void CServerMainDlg::OnOnlineCmd()
{
}

void CServerMainDlg::OnOnlineProcess()
{
}

void CServerMainDlg::OnOnlineWindow()
{
}

void CServerMainDlg::OnOnlineDesktop()
{
}

void CServerMainDlg::OnOnlineFile()
{
}

void CServerMainDlg::OnOnlineAudio()
{
}

void CServerMainDlg::OnOnlineVideo()
{
}

void CServerMainDlg::OnOnlineServer()
{
}

void CServerMainDlg::OnOnlineRegister()
{
}

void CServerMainDlg::OnOnlineDelete()
{
}

void CServerMainDlg::OnMainClose()
{
}

void CServerMainDlg::OnMainAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CServerMainDlg::OnMainSet()
{
}

void CServerMainDlg::OnMainBuild()
{
}

void CServerMainDlg::OnOnlineRegedit()
{
}

LRESULT CServerMainDlg::OnOpenRegEditDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenWebCamDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

void CServerMainDlg::OnIconNotify(WPARAM wParam, LPARAM lParam)
{
}

LRESULT CServerMainDlg::OnOpenShellDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenSystemDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenManagerDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenAudioDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenScreenSpyDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnOpenServerDialog(WPARAM, LPARAM)
{
	return LRESULT();
}

LRESULT CServerMainDlg::OnAddToList(WPARAM, LPARAM)
{
	return LRESULT();
}
