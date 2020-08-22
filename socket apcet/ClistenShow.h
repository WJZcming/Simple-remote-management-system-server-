#pragma once

extern CTreeCtrl *ptree;
// ClistenShow 对话框
class CClistensocket;
class ClistenShow : public CDialogEx
{
	DECLARE_DYNAMIC(ClistenShow)

public:
	ClistenShow(CClistensocket *pSocket, HTREEITEM hnewItem, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ClistenShow();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	HTREEITEM Item;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();

	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
