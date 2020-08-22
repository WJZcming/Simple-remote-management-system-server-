#pragma once
#include "Clistensocket.h"

// CServer 对话框
class CClistensocket;
class CServer : public CDialogEx
{
	DECLARE_DYNAMIC(CServer)

public:
	CServer(CClistensocket* pSocket,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CServer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket* m_pSocket;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRen();
	CListCtrl m_Lists;
	virtual BOOL OnInitDialog();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void startserver();
	afx_msg void stopserver();
	afx_msg void deleteserver();
	afx_msg void creatserver();
	afx_msg void recvs();
	afx_msg void unable();
	afx_msg void use();
	afx_msg void hand();
};
