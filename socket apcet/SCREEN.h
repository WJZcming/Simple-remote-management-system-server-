#pragma once
#include "Clistensocket.h"
extern CTreeCtrl *ptree;
// CSCREEN �Ի���
class CClistensocket;
class CSCREEN : public CDialogEx
{
	DECLARE_DYNAMIC(CSCREEN)

public:
	CSCREEN(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSCREEN();

// �Ի�������
	enum { IDD = IDD_SCREEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
