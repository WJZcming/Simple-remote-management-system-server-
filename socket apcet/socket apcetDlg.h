
// socket apcetDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ListenSocket.h"
#include"resource.h"
#include "Ctip.h"
// CsocketapcetDlg 对话框
class CsocketapcetDlg : public CDialogEx
{
// 构造
public:
	CsocketapcetDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SOCKETAPCET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
