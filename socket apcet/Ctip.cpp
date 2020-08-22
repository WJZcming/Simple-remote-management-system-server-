// Ctip.cpp : 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Ctip.h"
#include "afxdialogex.h"
#include "Clistensocket.h"

// Ctip 对话框

IMPLEMENT_DYNAMIC(Ctip, CDialogEx)

Ctip::Ctip(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(Ctip::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

Ctip::~Ctip()
{
}

void Ctip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Ctip, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Ctip::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctip::OnBnClickedButton2)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// Ctip 消息处理程序


void Ctip::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	
	CString str;
	//声明标识
	USES_CONVERSION;
	GetDlgItemText(IDC_EDIT1, str);
	if (str != ""&&sizeof(str)<100)
	{
		m_pSocket->Send("tipmessagebox", 15);
		m_pSocket->Send(T2A(str),500);
	}
	else
	{
		MessageBoxA(0, "命令不合法", "tip", 0);
	}
}


void Ctip::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	//delete[] m_pSocket;
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT Ctip::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
void Ctip::DrawBorder(CDC *pDC)
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

LRESULT Ctip::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}
