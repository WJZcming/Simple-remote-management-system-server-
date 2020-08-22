#pragma once
#include"socket apcetDlg.h"
extern CTreeCtrl *ptree;
class CClistensocket;
// Ctip 对话框

class Ctip : public CDialogEx
{
	DECLARE_DYNAMIC(Ctip)

public:
	Ctip(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Ctip();

// 对话框数据
	enum { IDD = IDD_TIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CClistensocket *m_pSocket;
	afx_msg void DrawBorder(CDC *pDC);
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	HTREEITEM m_htree;
	CString m_tname;
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
