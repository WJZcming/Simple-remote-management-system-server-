#pragma once
#include "Clistensocket.h"
extern CTreeCtrl *ptree;

class CClistensocket;
class CVdio : public CDialogEx
{
	DECLARE_DYNAMIC(CVdio)

public:
	CVdio(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVdio();

// 对话框数据
	enum { IDD = IDD_VIOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	HTREEITEM m_htree;
	CString m_tname;
	afx_msg void DrawBorder(CDC *pDC);
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual BOOL DestroyWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
