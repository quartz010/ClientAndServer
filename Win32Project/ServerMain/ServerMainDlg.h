
// ServerMainDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TrueColorToolBar.h"



// CServerMainDlg �Ի���
class CServerMainDlg : public CDialogEx
{
// ����
public:
	CServerMainDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CTrueColorToolBar mToolBar;        // ��������չ��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERMAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
//�Ի����ʼ��

protected:
	void CServerMainDlg::CreateToolBar(void);


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void On32771();

	//toolBar ����Ϣӳ�亯�� 
	//�൱��Qt�еĲۺ���
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
	//�Զ�����Ϣӳ�亯��
	afx_msg LRESULT OnOpenRegEditDialog(WPARAM, LPARAM);    //�Զ�����Ϣ��ע���
	afx_msg	LRESULT	OnOpenWebCamDialog(WPARAM, LPARAM);     //�Զ�����Ϣ����Ƶ����
	afx_msg void OnIconNotify(WPARAM wParam, LPARAM lParam); //�Զ�����Ϣ(ϵͳ����)
	afx_msg LRESULT OnOpenShellDialog(WPARAM, LPARAM);       //�Զ�����Ϣ(Զ���ն�)
	afx_msg LRESULT OnOpenSystemDialog(WPARAM, LPARAM);      //�Զ�����Ϣ�����̹���
	afx_msg LRESULT OnOpenManagerDialog(WPARAM, LPARAM);    //�Զ�����Ϣ���ļ�����
	afx_msg	LRESULT	OnOpenAudioDialog(WPARAM, LPARAM);      //�Զ�����Ϣ����Ƶ����
	afx_msg	LRESULT OnOpenScreenSpyDialog(WPARAM, LPARAM);  //�Զ�����Ϣ���������
	afx_msg	LRESULT	OnOpenServerDialog(WPARAM, LPARAM);     //�Զ�����Ϣ ���������
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);

};
