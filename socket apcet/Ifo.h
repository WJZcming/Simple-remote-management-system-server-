#pragma once
#include "afxcmn.h"
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
class CClistensocket;
// CIfo 对话框

class CIfo : public CDialogEx
{
	DECLARE_DYNAMIC(CIfo)

public:
	CIfo(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIfo();

// 对话框数据
	enum { IDD = IDD_IFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ifolist;
	CClistensocket *m_pSocket;
	HTREEITEM m_htree;
	CString m_tname;
	afx_msg void DrawBorder(CDC *pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
