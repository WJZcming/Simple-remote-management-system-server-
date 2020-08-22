// Vdio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Vdio.h"
#include "afxdialogex.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
using namespace std;

// CVdio �Ի���

IMPLEMENT_DYNAMIC(CVdio, CDialogEx)

CVdio::CVdio(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CVdio::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CVdio::~CVdio()
{
}

void CVdio::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVdio, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CVdio::OnBnClickedButton1)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON3, &CVdio::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CVdio::OnBnClickedButton2)
END_MESSAGE_MAP()


// CVdio ��Ϣ�������


void CVdio::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT CVdio::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
void CVdio::DrawBorder(CDC *pDC)
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

BOOL CVdio::DestroyWindow()
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CDialogEx::DestroyWindow();
}


LRESULT CVdio::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CVdio::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char recvdata[10] = "";
	m_pSocket->Send("vdiomaner", 15);
	m_pSocket->Receive(recvdata, 10);
	if (strcmp(recvdata,"wrong") == 0)
	{
		MessageBoxA(0, "������", "Tip", 0);
		return;
	}
	m_pSocket->Send("okokv", 10);
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char nowpathname[256] = "";
	sprintf(nowpathname, "%d��%d��%d��%dʱ%d��%d��%d����.bmp", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
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
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // �õ� Picture Control ���
	pWnd->ModifyStyle(0, SS_BITMAP); // �޸���������Ϊλͼ
	CString pattttttt(nowpathname);
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL, pattttttt,
		IMAGE_BITMAP,
		640/2,
		480/2,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	MessageBoxA(0, "������ɣ��ѷ��ڵ�ǰĿ¼��", "Tip", 0);
}


void CVdio::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char recvdata[10] = "";
	m_pSocket->Send("vdiomaner", 15);
	m_pSocket->Receive(recvdata, 10);
	if (strcmp(recvdata, "wrong") == 0)
	{
		MessageBoxA(0, "������", "Tip", 0);
		return;
	}
	m_pSocket->Send("okokv", 10);
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	char nowpathname[256] = "";
	sprintf(nowpathname, "1.bmp", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
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
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_STATIC); // �õ� Picture Control ���
	pWnd->ModifyStyle(0, SS_BITMAP); // �޸���������Ϊλͼ
	pWnd->SetBitmap((HBITMAP)::LoadImage(NULL, _T("1.bmp"),
		IMAGE_BITMAP,
		640/2,
		480/2,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	remove("1.bmp");
}
