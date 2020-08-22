// CServer.cpp: 实现文件
//

#include "stdafx.h"
#include "socket apcet.h"
#include "CServer.h"
#include "afxdialogex.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

// CServer 对话框
CString ConstCharToCStrings(const char* ch)
{
	char* buf = new char[strlen(ch) + 1];
	memset(buf, 0, sizeof(ch));
	strcpy(buf, ch);
	CString  strName;
	strName = buf;
	delete[]buf;
	return strName;
}
IMPLEMENT_DYNAMIC(CServer, CDialogEx)

CServer::CServer(CClistensocket* pSocket,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER, pParent)
{
	m_pSocket = pSocket;
}

CServer::~CServer()
{
}

void CServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_Lists);
}


BEGIN_MESSAGE_MAP(CServer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CServer::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_REN, &CServer::OnBnClickedRen)
	ON_COMMAND(ID_S_S, &CServer::startserver)
	ON_COMMAND(ID_S_32785, &CServer::stopserver)
	ON_COMMAND(ID_S_32786, &CServer::deleteserver)
	ON_COMMAND(ID_S_32787, &CServer::creatserver)
	ON_COMMAND(ID__32788, &CServer::unable)
	ON_COMMAND(ID__32789, &CServer::use)
	ON_COMMAND(ID__32790, &CServer::hand)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CServer 消息处理程序


void CServer::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	DestroyWindow();
}
void CServer::recvs()
{
	char sername[300] = "";
	char zt[50] = "";
	char path[256] = "";
	int pos = 0;
	m_Lists.DeleteAllItems();
	m_pSocket->Send("servermanger", 13);

	char recvd[300] = "";
	int s = 0;
	s = m_pSocket->Receive(recvd, 256);
	if (s < 0)
	{
		MessageBoxA(0, "对方掉线", "tip", 0);
		return;
	}
	if (strcmp(recvd, "mserver") == 0)
	{
		m_pSocket->Send("nrong", sizeof("nrong"));
		while (1)
		{
			
			m_pSocket->Receive(sername, 256);
			
			if (strcmp(sername, "mserverstop") == 0)
			{
				break;
			}
			else
			{
				m_pSocket->Send("wcndfg", 20);
				m_pSocket->Receive(zt, 50);
				m_pSocket->Send("wcndfg", 20);
				m_pSocket->Receive(path, 256);
				m_pSocket->Send("wcndfg", 20);
				m_Lists.InsertItem(pos, _T(""));
				if (strcmp(zt, "mserverstop") == 0 || strcmp(path, "mserverstop") == 0)
				{
					break;
				}
				m_Lists.SetItemText(pos, 0, ConstCharToCStrings(sername));
				m_Lists.SetItemText(pos, 1, ConstCharToCStrings(zt));
				m_Lists.SetItemText(pos, 2, ConstCharToCStrings(path));
			}
		}
		m_Lists.InsertItem(pos, _T(""));
		m_Lists.SetItemText(pos, 0, ConstCharToCStrings("+新建"));

	}
	else
	{
		m_pSocket->Send("wrong", 6);
		MessageBoxA(0, "wrong", "tip", 0);
	}
}

void CServer::OnBnClickedRen()
{
	// TODO: 在此添加控件通知处理程序代码
	recvs();
}


BOOL CServer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化
	
	m_Lists.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_Lists.InsertColumn(0, _T("服务名"), LVCFMT_LEFT, 250);
	m_Lists.InsertColumn(1, _T("状态"), LVCFMT_LEFT, 250);
	m_Lists.InsertColumn(2, _T("路径"), LVCFMT_LEFT, 400);
	
	recvs();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CServer::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	int iMark = 0;
	iMark = m_Lists.GetSelectionMark();
	if (iMark != -1)
	{
		POINT p;
		GetCursorPos(&p);
		CMenu menu;
		menu.LoadMenu(IDR_MENU3);
		CMenu* pMenu;
		pMenu = menu.GetSubMenu(0);
		//pMenu->EnableMenuItem(ID_32781, MF_BYCOMMAND | MF_ENABLED);
		CString str = m_Lists.GetItemText(iMark, 1);
		char zt[30];
		sprintf(zt, "%ws", str);
		//MessageBoxA(0, zt, "1", 0);
		std::string sz2 = CT2A(str.GetBuffer());
		if (strstr(sz2.c_str(), "自动") != NULL)
		{
		pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_ENABLED);
		}
		else if (strstr(sz2.c_str(), "手动") != NULL)
		{
		pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_ENABLED);
		}
		else if (strstr(sz2.c_str(), "禁用") != NULL)
		{
		pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_ENABLED);
		pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_ENABLED);
		}
		else
		{
		pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_GRAYED);
		pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_GRAYED);
		}
		if (strstr(sz2.c_str(), "RUNNING") != NULL)
		{
			pMenu->EnableMenuItem(ID_S_S, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32787, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32785, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem(ID_S_32786, MF_BYCOMMAND | MF_ENABLED);
		}
		else if (strstr(sz2.c_str(), "STOPPED") != NULL)
		{
			pMenu->EnableMenuItem(ID_S_S, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem(ID_S_32785, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32786, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem(ID_S_32787, MF_BYCOMMAND | MF_GRAYED);
		}
		else if (str == "")
		{
			pMenu->EnableMenuItem(ID_S_32787, MF_BYCOMMAND | MF_ENABLED);
			pMenu->EnableMenuItem(ID_S_S, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32785, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32786, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_GRAYED);
		}
		else
		{
			pMenu->EnableMenuItem(ID_S_32787, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_S, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32785, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID_S_32786, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32790, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32789, MF_BYCOMMAND | MF_GRAYED);
			pMenu->EnableMenuItem(ID__32788, MF_BYCOMMAND | MF_GRAYED);
		}
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		pMenu->Detach();
		menu.DestroyMenu();
	}
}
void CServer::startserver()
{
	MessageBoxA(0, "start", "tip", 0);
	return;
}
void CServer::stopserver()
{
	MessageBoxA(0, "stop", "tip", 0);
	return;
}
void CServer::deleteserver()
{
	MessageBoxA(0, "delete", "tip", 0);
	return;
}
void CServer::creatserver()
{
	MessageBoxA(0, "creat", "tip", 0);
	return;
}
void CServer::unable()
{
	MessageBoxA(0, "unable", "tip", 0);
	return;
}
void CServer::use()
{
	MessageBoxA(0, "use", "tip", 0);
	return;
}
void CServer::hand()
{
	MessageBoxA(0, "hand", "tip", 0);
	return;
}