// Cmd.cpp : 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Cmd.h"
#include "afxdialogex.h"
#include "Clistensocket.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <winsock2.h>
using namespace std;
// CCmd 对话框
CCmd *g_dlg = NULL;
IMPLEMENT_DYNAMIC(CCmd, CDialogEx)

CCmd::CCmd(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CCmd::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CCmd::~CCmd()
{
}

void CCmd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RES, m_Ed);
}


BEGIN_MESSAGE_MAP(CCmd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CCmd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_SENDCMD, &CCmd::OnBnClickedSendcmd)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CCmd 消息处理程序


void CCmd::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}

void CCmd::OnBnClickedSendcmd()
{
	// TODO:  在此添加控件通知处理程序代码
	CString ccc;
	//声明标识
	USES_CONVERSION;
	GetDlgItemText(IDC_CMD, ccc);
	char* thing = T2A(ccc);
	if (ccc != ""&&sizeof(ccc) < 100&&strlen(thing)>0)
	{
		char test[20] = "";
		USES_CONVERSION;
		CString string = _T("");
		SetDlgItemText(IDC_RES, string);
		m_pSocket->Send("cmdorder", 15);
		m_pSocket->Receive(test, 20);
		m_pSocket->Send(thing, 100);
		m_pSocket->Receive(test, 20);
		if (strcmp(test,"wrong")==0)
		{
			MessageBoxA(0, "执行错误", "tip", 0);
			return;
		}
		else
		{
			m_pSocket->Send("zsajkdjfh", 20);
			//////////////////recv/////////////////////////
			const int bufferSize = 1024;
			char buffer[bufferSize] = { 0 };
			int readLen = 0;
			ofstream desFile;
			desFile.open("zcming.zcming", ios::binary);
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

			CString strcmd = _T("");
			ifstream srcFile;
			srcFile.open("zcming.zcming", ios::binary);
			while (!srcFile.eof()){
				
				srcFile.read(buffer, bufferSize);
				CString AS(buffer);
				strcmd = strcmd + AS;
			}
			srcFile.close();

			m_Ed.SetWindowText(strcmd);
			remove("zcming.zcming");
		}

	}
	else
	{
		MessageBoxA(0, "命令不合法", "tip", 0);
	}
}


BOOL CCmd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_dlg = this;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


LRESULT CCmd::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}


LRESULT CCmd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}
void CCmd::DrawBorder(CDC *pDC)
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