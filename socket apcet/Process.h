#pragma once
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
// CProcess �Ի���
class CClistensocket;
class CProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CProcess)

public:
	CProcess(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcess();

// �Ի�������
	enum { IDD = IDD_PROCESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CClistensocket *m_pSocket;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CListCtrl m_List;
	HTREEITEM m_htree;
	CString m_tname;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedNew();
	afx_msg void DrawBorder(CDC *pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void closeprocess();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
