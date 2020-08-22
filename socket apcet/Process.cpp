// Process.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Process.h"
#include "afxdialogex.h"
int iMark = 0;
CString ConstCharToCString(const char* ch);
// CProcess �Ի���

IMPLEMENT_DYNAMIC(CProcess, CDialogEx)

CProcess::CProcess(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcess::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CProcess::~CProcess()
{
}

void CProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CProcess, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CProcess::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NEW, &CProcess::OnBnClickedNew)
	ON_COMMAND(ID_32781, &CProcess::closeprocess)
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

// CProcess ��Ϣ�������


void CProcess::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}

void CProcess::closeprocess()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nItem = m_List.GetSelectionMark();
	CString  str = m_List.GetItemText(iMark, 1);
	CString  strt = m_List.GetItemText(iMark, 0);
	if (nItem<0)
	{
		MessageBoxA(0, "δѡ��ID", "tip", 0);
		return;
	}
	if (strt=="")
	{
		MessageBoxA(0, "�Լ��˱�ǹ��", "tip", 0);
		return;
		
	}
	char ttt[10] = "";
	char st[20] = "";
	char recvdate[15] = "";
	sprintf(st, "%ws", str);
	m_pSocket->Send("closeprocess", 15);
	m_pSocket->Receive(ttt, 10);
	m_pSocket->Send(st, 20);
	m_pSocket->Receive(recvdate, 15);
	MessageBoxA(0, recvdate, "tip", 0);
	if (strcmp("wrong", recvdate) == 0)
	{
		if (MessageBox(_T("�ر�ʧ��,�Ƿ�ʹ�÷�ŵ�������Ʋã�"), _T("Tip"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
		{
			m_pSocket->Send("dirverkill", 20);
			
			m_pSocket->Receive(ttt, 10);
			if (strcmp(ttt,"wrong")==0)
			{
				MessageBox(_T("��������ʧ��"));
				return;
			}
			m_pSocket->Send(st, 50);
			m_List.DeleteItem(nItem);
		}
	}
	else
	{
		m_List.DeleteItem(nItem);
	}
}
CString ConstCharToCString(const char* ch)
{
	char* buf = new char[strlen(ch) + 1];
	memset(buf, 0, sizeof(ch));
	strcpy(buf, ch);
	CString  strName;
	strName = buf;
	delete[]buf;
	return strName;
}

BOOL CProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("������"), LVCFMT_LEFT, 120);
	m_List.InsertColumn(1, _T("����ID"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(2, _T("�߳�����"), LVCFMT_LEFT, 70);
	m_List.InsertColumn(3, _T("·��"), LVCFMT_LEFT, 340);
	int pos = 0;
	m_List.DeleteAllItems();
	m_pSocket->Send("processz", sizeof("processz"));
	char recvd[300] = "";
	int s = 0;
	s = m_pSocket->Receive(recvd, 256);
	if (s < 0)
	{
		MessageBoxA(0, "�Է�����", "tip", 0);
		return TRUE;
	}
	if (strcmp(recvd, "addprocess") == 0)
	{
		m_pSocket->Send("nrong", sizeof("nrong"));
		CString strTemp;
		while (1)
		{
			int h = 0;
			char name[300] = "";
			char pid[20] = "";
			char nub[20] = "";
			char path[300] = "";
			h = m_pSocket->Receive(name, 256);
			if (strcmp(name, "addprocessstop") == 0)
			{
				break;
			}
			m_pSocket->Send("zcmnb", 20);
			//MessageBoxA(0, pid, "1", 0);
			if (h < 0)
			{
				//MessageBoxA(0, "�Է�����", "tip", 0);
				return TRUE;
			}
			else if (strcmp(name, "addprocessstop") == 0)
			{
				break;
			}
			else
			{
				m_pSocket->Receive(pid, 20);
				m_pSocket->Send("zcmnb", 20);
				m_pSocket->Receive(nub, 20);
				m_pSocket->Send("zcmnb", 20);
				m_pSocket->Receive(path, 256);
				m_pSocket->Send("zcmnb", 20);
				m_List.InsertItem(pos, _T(""));
				m_List.SetItemText(pos, 0, ConstCharToCString(name));
				//strTemp.Format(_T("%d"), ConstCharToCString(pid));
				m_List.SetItemText(pos, 1, ConstCharToCString(pid));   //����id
				m_List.SetItemText(pos, 2, ConstCharToCString(nub));    //�߳���
				m_List.SetItemText(pos, 3, ConstCharToCString(path));
			}
		}
	}
	else
	{
		m_pSocket->Send("wrong", 6);
		MessageBoxA(0, "wrong", "tip", 0);
	}
	//SetTimer(1,10000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CProcess::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int pos = 0;
	m_List.DeleteAllItems();
	m_pSocket->Send("processz", sizeof("processz"));
	char recvd[300] = "";
	int s = 0;
	s = m_pSocket->Receive(recvd, 256);
	if (s < 0)
	{
		MessageBoxA(0, "�Է�����", "tip", 0);
		return;
	}
	if (strcmp(recvd, "addprocess") == 0)
	{
		CString strTemp;
		while (1)
		{
			int h = 0;
			char name[300] = "";
			char pid[20] = "";
			char nub[20] = "";
			char path[300] = "";
			h = m_pSocket->Receive(name, 256);

			//MessageBoxA(0, pid, "1", 0);
			if (h < 0)
			{
				//MessageBoxA(0, "�Է�����", "tip", 0);
				return;
			}
			else if (strcmp(name, "addprocessstop") == 0)
			{
				break;
			}
			else
			{
				m_pSocket->Receive(pid, 20);
				m_pSocket->Receive(nub, 20);
				m_pSocket->Receive(path, 256);
				m_List.InsertItem(pos, _T(""));
				m_List.SetItemText(pos, 0, ConstCharToCString(name));
				//strTemp.Format(_T("%d"), ConstCharToCString(pid));
				m_List.SetItemText(pos, 1, ConstCharToCString(pid));   //����id
				m_List.SetItemText(pos, 2, ConstCharToCString(nub));    //�߳���
				m_List.SetItemText(pos, 3, ConstCharToCString(path));
			}
		}
	}
	else
	{
		MessageBoxA(0, "wrong", "tip", 0);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CProcess::OnBnClickedNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int pos = 0;
	m_List.DeleteAllItems();
	m_pSocket->Send("processz", sizeof("processz"));
	char recvd[300] = "";
	int s = 0;
	s = m_pSocket->Receive(recvd, 256);
	if (s < 0)
	{
		MessageBoxA(0, "�Է�����", "tip", 0);
		return;
	}
	if (strcmp(recvd, "addprocess") == 0)
	{
		m_pSocket->Send("nrong", sizeof("nrong"));
		CString strTemp;
		while (1)
		{
			int h = 0;
			char name[300] = "";
			char pid[20] = "";
			char nub[20] = "";
			char path[300] = "";
			h = m_pSocket->Receive(name, 256);
			if (strcmp(name, "addprocessstop") == 0)
			{
				break;
			}
			m_pSocket->Send("zcmnb", 20);
			//MessageBoxA(0, pid, "1", 0);
			if (h < 0)
			{
				//MessageBoxA(0, "�Է�����", "tip", 0);
				return;
			}
			else if (strcmp(name, "addprocessstop") == 0)
			{
				break;
			}
			else
			{
				m_pSocket->Receive(pid, 20);
				m_pSocket->Send("zcmnb", 20);
				m_pSocket->Receive(nub, 20);
				m_pSocket->Send("zcmnb", 20);
				m_pSocket->Receive(path, 256);
				m_pSocket->Send("zcmnb", 20);
				m_List.InsertItem(pos, _T(""));
				m_List.SetItemText(pos, 0, ConstCharToCString(name));
				//strTemp.Format(_T("%d"), ConstCharToCString(pid));
				m_List.SetItemText(pos, 1, ConstCharToCString(pid));   //����id
				m_List.SetItemText(pos, 2, ConstCharToCString(nub));    //�߳���
				m_List.SetItemText(pos, 3, ConstCharToCString(path));
			}
		}
	}
	else
	{
		m_pSocket->Send("wrong", 6);
		MessageBoxA(0, "wrong", "tip", 0);
	}
}
void CProcess::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnRButtonDown(nFlags, point);
}
void CProcess::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
	
	iMark = m_List.GetSelectionMark();
	if (iMark != -1)
	{
		POINT p;
		GetCursorPos(&p);
		CMenu menu;
		menu.LoadMenu(IDR_MENU2);
		CMenu* pMenu;
		pMenu = menu.GetSubMenu(0);
		pMenu->EnableMenuItem(ID_32781, MF_BYCOMMAND | MF_ENABLED);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		pMenu->Detach();
		menu.DestroyMenu();
	}
	else
	{
		//MessageBoxA(0, "12", "1", 0);
	}
}


LRESULT CProcess::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret == HTCLIENT) ? HTCAPTION : ret;
}
void CProcess::DrawBorder(CDC *pDC)
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

LRESULT CProcess::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CDC* pWinDC = GetWindowDC();
	if (pWinDC)
	{
		DrawBorder(pWinDC);
	}
	ReleaseDC(pWinDC);
	return CDialog::DefWindowProc(message, wParam, lParam);
}
