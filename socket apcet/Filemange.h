#pragma once
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
// CFilemange 对话框
class CClistensocket;
class CFilemange : public CDialogEx
{
	DECLARE_DYNAMIC(CFilemange)

public:
	CFilemange(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFilemange();

// 对话框数据
	enum { IDD = IDD_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	afx_msg void OnBnClickedButton2();
	afx_msg void recivefile(HTREEITEM tree);
	afx_msg void filename();
	virtual BOOL OnInitDialog();
	CImageList* m_imagetree;
	CTreeCtrl m_tree;
	afx_msg void DrawBorder(CDC *pDC);
	HTREEITEM m_htree;
	CString m_tname;
	CListCtrl m_List;
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void addfile();
	afx_msg void upload();
	afx_msg void runthis();
	afx_msg void deletethisfolder();
	afx_msg void deletethisfile();
	afx_msg void download();
	afx_msg CString getselectpath();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
