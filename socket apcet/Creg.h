#pragma once


// Creg 对话框
#include "Clistensocket.h"
class CClistensocket;
class Creg : public CDialogEx
{
	DECLARE_DYNAMIC(Creg)

public:
	Creg(CClistensocket* pSocket, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Creg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket* m_pSocket;
	CListCtrl m_List;
	CTreeCtrl m_tree;
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void revvv(HTREEITEM item);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void addkey();
	afx_msg void deletkey();
};
