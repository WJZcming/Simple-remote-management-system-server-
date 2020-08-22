// Ifo.cpp : 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Ifo.h"
#include "afxdialogex.h"

// CIfo 对话框

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


// CIfo 消息处理程序


BOOL CIfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ifolist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pSocket->Send("getifomation", 20);
	m_ifolist.InsertColumn(0, _T("信息列表"), LVCFMT_LEFT, 200);
	char ifo[108] = "";
	m_pSocket->Receive(ifo, 100);
	//sprintf(ifo, "计算机名:%s", ifo);
	CString hhh(ifo);
	m_ifolist.InsertItem(0, _T("计算机名:") + hhh);
	m_pSocket->Send("zcming", 10);

	char ifo2[50] = "";
	m_pSocket->Receive(ifo2, 50);
	CString hhh2(ifo2);
	m_ifolist.InsertItem(0, _T("操作系统:") + hhh2);
	m_pSocket->Send("zcming", 10);

	char ifo3[20] = "";
	m_pSocket->Receive(ifo3, 10);
	CString hhh3(ifo3);
	m_ifolist.InsertItem(0, _T("CUP核心数:") + hhh3);
	m_pSocket->Send("zcming", 10);

	char ifo4[30] = "";
	m_pSocket->Receive(ifo4, 20);
	CString hhh4(ifo4);
	m_ifolist.InsertItem(0, _T("CUP主频:") + hhh4 + _T("~MHZ"));
	m_pSocket->Send("zcming", 10);

	char ifo5[30] = "";
	m_pSocket->Receive(ifo5, 30);
	CString hhh5(ifo5);
	m_ifolist.InsertItem(0, _T("当前内存使用:") + hhh5 + _T("KB"));
	m_pSocket->Send("zcming", 10);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CIfo::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT CIfo::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
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
		//填充顶部框架
		point.x = rtWnd.Width();
		point.y = GetSystemMetrics(SM_CYFRAME) + 5;
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//填充左侧框架
		point.x = GetSystemMetrics(SM_CXFRAME);
		point.y = rtWnd.Height();
		pDC->PatBlt(0, 0, point.x, point.y, PATCOPY);
		//填充底部框架
		point.x = rtWnd.Width();
		point.y = GetSystemMetrics(SM_CYFRAME) + 5;
		pDC->PatBlt(0, rtWnd.Height() - point.y, point.x, point.y, PATCOPY);
		//填充右侧框架
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
