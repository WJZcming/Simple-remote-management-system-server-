#pragma once

extern CTreeCtrl *ptree;
// ClistenShow �Ի���
class CClistensocket;
class ClistenShow : public CDialogEx
{
	DECLARE_DYNAMIC(ClistenShow)

public:
	ClistenShow(CClistensocket *pSocket, HTREEITEM hnewItem, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ClistenShow();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
