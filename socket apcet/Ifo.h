#pragma once
#include "afxcmn.h"
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
class CClistensocket;
// CIfo �Ի���

class CIfo : public CDialogEx
{
	DECLARE_DYNAMIC(CIfo)

public:
	CIfo(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIfo();

// �Ի�������
	enum { IDD = IDD_IFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
