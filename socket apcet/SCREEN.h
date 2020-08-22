#pragma once
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
// CSCREEN 对话框
class CClistensocket;
class CSCREEN : public CDialogEx
{
	DECLARE_DYNAMIC(CSCREEN)

public:
	CSCREEN(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSCREEN();

// 对话框数据
	enum { IDD = IDD_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	HTREEITEM m_htree;
	CString m_tname;
	afx_msg void DrawBorder(CDC *pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
