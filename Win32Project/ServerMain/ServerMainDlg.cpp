
// ServerMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerMain.h"
#include "ServerMainDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CServerMainDlg �Ի���



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

	//��������ӳ���˸�����
	ON_COMMAND(ID_32771, &CServerMainDlg::On32771)
	//�൱�������źźͲ� (������Ϣӳ���)
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

	//���԰Ѳ�ͬ�Ķ���д��ͬһ��ID��������Ч����Ӧͬһ��ӳ��
	ON_COMMAND(IDM_MAIN_ABOUT, &CServerMainDlg::OnMainAbout)
	ON_COMMAND(IDM_MAIN_SET, &CServerMainDlg::OnMainSet)
	ON_COMMAND(IDM_MAIN_GEN, &CServerMainDlg::OnMainBuild)
	//	ON_COMMAND(IDM_MAIN_CLOSE, &CServerMainDlg::OnMainClose)
END_MESSAGE_MAP()


// CServerMainDlg ��Ϣ�������

BOOL CServerMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	//����Ϊϵͳ���ɴ���

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	CreateToolBar();               //��ӹ�����


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//��ʼ��������
void CServerMainDlg::CreateToolBar(void)
{

	if (!mToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!mToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))  //����һ��������  ������Դ
	{

		return;
	}
	mToolBar.ModifyStyle(0, TBSTYLE_FLAT);    //Fix for WinXP
	mToolBar.LoadTrueColorToolBar
	(
		54,    //������ʹ�����
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN,
		IDB_BITMAP_MAIN
	);  //�����ǵ�λͼ��Դ�����
	RECT rt, rtMain;
	GetWindowRect(&rtMain);   //�õ��������ڵĴ�С
	rt.left = 0;
	rt.top = 0;
	rt.bottom = 80;
	rt.right = rtMain.right - rtMain.left + 10;
	mToolBar.MoveWindow(&rt, TRUE);

	mToolBar.SetButtonText(0, "�ն˹���");     //��λͼ�������������
	mToolBar.SetButtonText(1, "���̹���");
	mToolBar.SetButtonText(2, "���ڹ���");
	mToolBar.SetButtonText(3, "�������");
	mToolBar.SetButtonText(4, "�ļ�����");
	mToolBar.SetButtonText(5, "��������");
	mToolBar.SetButtonText(6, "��Ƶ����");
	mToolBar.SetButtonText(7, "�������");
	mToolBar.SetButtonText(8, "ע������");
	mToolBar.SetButtonText(9, "��������");
	mToolBar.SetButtonText(10, "���ɷ����");
	mToolBar.SetButtonText(11, "����");

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);  //��ʾ

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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	//this->CloseWindow();
}



void CServerMainDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}




void CServerMainDlg::On32771() //�˵�����
{	
	CDialogEx::OnOK();	
	// TODO: �ڴ���������������
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
