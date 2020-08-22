// SCREEN.cpp : 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "SCREEN.h"
#include "afxdialogex.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
using namespace std;
// CSCREEN 对话框

IMPLEMENT_DYNAMIC(CSCREEN, CDialogEx)

CSCREEN::CSCREEN(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CSCREEN::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CSCREEN::~CSCREEN()
{
}

void CSCREEN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSCREEN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSCREEN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSCREEN::OnBnClickedButton2)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CSCREEN 消息处理程序



void CSCREEN::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_pSocket->Send("screenshot", 20);
	
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char nowpathname[256] = "";
	sprintf(nowpathname, "%d年%d月%d日%d时%d分%d秒%d毫秒.png", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond,sys.wMilliseconds);
	//MessageBoxA(0, nowpathname, "Tip", 0);
	int readLen = 0;
	ofstream desFile;
	desFile.open(nowpathname, ios::binary);
	do
	{
		readLen = m_pSocket->Receive(buffer, bufferSize);
		//MessageBoxA(0, buffer, "1", 0);
		if (strcmp("finish", buffer) == 0)
		{
			//m_pSocket->Send("imokeee", 10);
			break;
		}
		m_pSocket->Send("imokeee", 10);
		desFile.write(buffer, readLen);
	} while (true);
	desFile.close();
	MessageBoxA(0, "截屏完成，已放在当前目录下", "Tip", 0);
}


void CSCREEN::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT CSCREEN::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
void CSCREEN::DrawBorder(CDC *pDC)
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

LRESULT CSCREEN::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}
