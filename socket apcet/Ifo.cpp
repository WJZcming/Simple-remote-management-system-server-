// Ifo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Ifo.h"
#include "afxdialogex.h"

// CIfo �Ի���

IMPLEMENT_DYNAMIC(CIfo, CDialogEx)

CIfo::CIfo(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CIfo::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CIfo::~CIfo()
{
}

void CIfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ifolist);
}


BEGIN_MESSAGE_MAP(CIfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CIfo::OnBnClickedButton1)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CIfo ��Ϣ�������


BOOL CIfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ifolist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pSocket->Send("getifomation", 20);
	m_ifolist.InsertColumn(0, _T("��Ϣ�б�"), LVCFMT_LEFT, 200);
	char ifo[108] = "";
	m_pSocket->Receive(ifo, 100);
	//sprintf(ifo, "�������:%s", ifo);
	CString hhh(ifo);
	m_ifolist.InsertItem(0, _T("�������:") + hhh);
	m_pSocket->Send("zcming", 10);

	char ifo2[50] = "";
	m_pSocket->Receive(ifo2, 50);
	CString hhh2(ifo2);
	m_ifolist.InsertItem(0, _T("����ϵͳ:") + hhh2);
	m_pSocket->Send("zcming", 10);

	char ifo3[20] = "";
	m_pSocket->Receive(ifo3, 10);
	CString hhh3(ifo3);
	m_ifolist.InsertItem(0, _T("CUP������:") + hhh3);
	m_pSocket->Send("zcming", 10);

	char ifo4[30] = "";
	m_pSocket->Receive(ifo4, 20);
	CString hhh4(ifo4);
	m_ifolist.InsertItem(0, _T("CUP��Ƶ:") + hhh4 + _T("~MHZ"));
	m_pSocket->Send("zcming", 10);

	char ifo5[30] = "";
	m_pSocket->Receive(ifo5, 30);
	CString hhh5(ifo5);
	m_ifolist.InsertItem(0, _T("��ǰ�ڴ�ʹ��:") + hhh5 + _T("KB"));
	m_pSocket->Send("zcming", 10);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CIfo::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT CIfo::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
void CIfo::DrawBorder(CDC *pDC)
{
	if (m_hWnd)
	{
		CBrush Brush(RGB(185, 184, 182));
		CBrush* pOldBrush = pDC->SelectObject(&Brush);

		CRect rtWnd;
		GetWindowRect(&rtWnd);

		CPoint point;
		//��䶥�����
		point.x = rtWnd.Width();
		point.y = GetSystemMetrics(SM_CYFRAME) + 5;
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//��������
		point.x = GetSystemMetrics(SM_CXFRAME);
		point.y = rtWnd.Height();
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//���ײ����
		point.x = rtWnd.Width();
		point.y = GetSystemMetrics(SM_CYFRAME) + 5;
		pDC->PatBlt(0, rtWnd.Height() - point.y, point.x, point.y, PATCOPY);
		//����Ҳ���
		point.x = GetSystemMetrics(SM_CXFRAME);
		point.y = rtWnd.Height();
		pDC->PatBlt(rtWnd.Width() - point.x, 0, point.x, point.y, PATCOPY);
	}
}

LRESULT CIfo::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}
