#pragma once
#include "afxwin.h"
extern CTreeCtrl *ptree;

// CCmd 对话框
class CClistensocket;
class CCmd : public CDialogEx
{
	DECLARE_DYNAMIC(CCmd)

public:
	CCmd(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCmd();

// 对话框数据
	enum { IDD = IDD_CMD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedSendcmd();
	CEdit m_Ed;
	HTREEITEM m_htree;
	afx_msg void DrawBorder(CDC *pDC);
	CString m_tname;
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
