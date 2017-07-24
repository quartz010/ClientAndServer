
// ServerMainDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TrueColorToolBar.h"



// CServerMainDlg 对话框
class CServerMainDlg : public CDialogEx
{
// 构造
public:
	CServerMainDlg(CWnd* pParent = NULL);	// 标准构造函数
	CTrueColorToolBar mToolBar;        // 工具条扩展类

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERMAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
//对话框初始化

protected:
	void CServerMainDlg::CreateToolBar(void);


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void On32771();

	//toolBar 的消息映射函数 
	//相当于Qt中的槽函数
	afx_msg void OnOnlineCmd();
	afx_msg void OnOnlineProcess();
	afx_msg void OnOnlineWindow();
	afx_msg void OnOnlineDesktop();
	afx_msg void OnOnlineFile();
	afx_msg void OnOnlineAudio();
	afx_msg void OnOnlineVideo();
	afx_msg void OnOnlineServer();
	afx_msg void OnOnlineRegister();
	afx_msg void OnOnlineDelete();
	afx_msg void OnMainClose();
	afx_msg void OnMainAbout();
	afx_msg void OnMainSet();
	afx_msg void OnMainBuild();
	afx_msg void OnOnlineRegedit();
	//自定义消息映射函数
	afx_msg LRESULT OnOpenRegEditDialog(WPARAM, LPARAM);    //自定义消息（注册表）
	afx_msg	LRESULT	OnOpenWebCamDialog(WPARAM, LPARAM);     //自定义消息（视频管理）
	afx_msg void OnIconNotify(WPARAM wParam, LPARAM lParam); //自定义消息(系统托盘)
	afx_msg LRESULT OnOpenShellDialog(WPARAM, LPARAM);       //自定义消息(远程终端)
	afx_msg LRESULT OnOpenSystemDialog(WPARAM, LPARAM);      //自定义消息（进程管理）
	afx_msg LRESULT OnOpenManagerDialog(WPARAM, LPARAM);    //自定义消息（文件管理）
	afx_msg	LRESULT	OnOpenAudioDialog(WPARAM, LPARAM);      //自定义消息（音频管理）
	afx_msg	LRESULT OnOpenScreenSpyDialog(WPARAM, LPARAM);  //自定义消息（桌面管理）
	afx_msg	LRESULT	OnOpenServerDialog(WPARAM, LPARAM);     //自定义消息 （服务管理）
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);

};
