// Filemange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "socket apcet.h"
#include "Filemange.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <winsock2.h>
using namespace std;
char Tes[10] = "";
CString path;
// CFilemange �Ի���
CString CFilemange::getselectpath()
{
	//USES_CONVERSION;
	path = "";
	HTREEITEM hRootItem = m_tree.GetRootItem();
	HTREEITEM htree = m_tree.GetSelectedItem();
	CString tmp = m_tree.GetItemText(htree);
	CString tmp2;
	if (tmp == "A:" || tmp == "B:" || tmp == "C:" || tmp == "D:" || tmp == "E:" || tmp == "F:" || tmp == "G:"
		|| tmp == "H:" || tmp == "I:" || tmp == "J:" || tmp == "K:" || tmp == "L:" || tmp == "M:"
		|| tmp == "N:" || tmp == "O:" || tmp == "P:" || tmp == "Q:" || tmp == "R:" || tmp == "S:"
		|| tmp == "T:" || tmp == "U:" || tmp == "V:" || tmp == "W:" || tmp == "X:" || tmp == "Y:" || tmp == "Z:")
	{
		return _T("");
	}
	while (tmp2 != "A:" && tmp2 != "B:" && tmp2 != "C:" && tmp2 != "D:" && tmp2 != "E:" && tmp2 != "F:" && tmp2 != "G:"
		&& tmp2 != "H:" && tmp2 != "I:" && tmp2 != "J:" && tmp2 != "K:" && tmp2 != "L:" && tmp2 != "M:"
		&& tmp2 != "N:" && tmp2 != "O:" && tmp2 != "P:" && tmp2 != "Q:" && tmp2 != "R:" && tmp2 != "S:"
		&& tmp2 != "T:" && tmp2 != "U:" && tmp2 != "V:" && tmp2 != "W:" && tmp2 != "X:" && tmp2 != "Y:" && tmp2 != "Z:")
	{

		htree = m_tree.GetParentItem(htree);
		tmp2 = m_tree.GetItemText(htree);
		if (path == "")
		{
			path = tmp2;
			continue;
		}
		path = tmp2 + _T("/") + path;
		//MessageBox(tmp2);
	}
	path = path + _T("/") + tmp;
	return path;
	//MessageBoxA(0, T2A(path), "1", 0);
}
IMPLEMENT_DYNAMIC(CFilemange, CDialogEx)

CFilemange::CFilemange(CClistensocket *pSocket, HTREEITEM htree, CString tname, CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilemange::IDD, pParent)
{
	m_pSocket = pSocket;
	m_htree = htree;
	m_tname = tname;
}

CFilemange::~CFilemange()
{
}

void CFilemange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_LIST1, m_List);
}


BEGIN_MESSAGE_MAP(CFilemange, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CFilemange::OnBnClickedButton2)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CFilemange::OnDblclkTree1)
	ON_COMMAND(ID_32791, &CFilemange::addfile)
	ON_COMMAND(ID_32792, &CFilemange::upload)
	ON_COMMAND(ID_32793, &CFilemange::runthis)
	ON_COMMAND(ID_32794, &CFilemange::deletethisfolder)
	ON_COMMAND(ID_32795, &CFilemange::download)
	ON_COMMAND(ID_32798, &CFilemange::deletethisfile)
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CFilemange::OnBnClickedButton1)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CFilemange ��Ϣ�������


void CFilemange::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DestroyWindow();
}
void CFilemange::filename()
{
	USES_CONVERSION;
	SHFILEINFO fileinfo;
	m_List.DeleteAllItems();
	char recvdate[256] = "";
	while (true)
	{
		m_pSocket->Receive(recvdate, 256);
		CString str(recvdate);
		if (str == _T("finish"))
		{
			m_pSocket->Send("zcmingnb", 10);
			break;
		}
		FILE* fp = fopen(T2A(str), "w+");
		fclose(fp);
		SHGetFileInfo(str, 0, &fileinfo, sizeof(fileinfo), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
		remove(T2A(str));
		int n = m_List.GetItemCount();
		m_List.InsertItem(n, str, fileinfo.iIcon);
		m_pSocket->Send("zcmingnb", 10);
	}

}
void CFilemange::recivefile(HTREEITEM tree)
{
	char recvdate[256] = "";
	while (true)
	{
		m_pSocket->Receive(recvdate, 256);
		CString str(recvdate);
		if (str == _T("finish"))
		{
			break;
		}
		HTREEITEM hChildItem = m_tree.GetChildItem(tree);
		bool bFind = false;
		while (hChildItem != NULL)
		{
			if (str.Compare(m_tree.GetItemText(hChildItem)) == 0)
			{
				bFind = true;
				break;
			}
			hChildItem = m_tree.GetNextSiblingItem(hChildItem);
		}
		if (bFind == false)
		{
			m_tree.InsertItem(str,0,0, tree);
		}
		m_pSocket->Send("zcmingnb", 10);
	}
	m_pSocket->Send("zcmingnb", 10);
	filename();
}
BOOL CFilemange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HICON icon[4];

	icon[0] = AfxGetApp()->LoadIcon(IDI_ICON1);

	icon[1] = AfxGetApp()->LoadIcon(IDI_ICON2);
	CImageList *ImageList4Tree;
	ImageList4Tree->Create(16, 16, 0, 4, 4); //16,16Ϊͼ��ֱ��ʣ�4,4Ϊ��list��������ɵ�ͼ����


	for(int i = 0; i < 2; i++)
	{

		ImageList4Tree->Add(icon[i]); //����ͼ��

	}

	m_tree.SetImageList(ImageList4Tree,TVSIL_NORMAL);


	SHFILEINFO ifo;
	HIMAGELIST himage = (HIMAGELIST)SHGetFileInfo(_T(""), 0, &ifo, sizeof(ifo), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	m_imagetree = CImageList::FromHandle(himage);
	m_List.SetImageList(m_imagetree, TVSIL_NORMAL);


	m_pSocket->Send("firstfileview", 15);
	char recvdate[256] = "";
	while (1)
	{
		m_pSocket->Receive(recvdate, 256);
		CString str(recvdate);
		if (str==_T("finish"))
		{
			break;
		}
		memset(recvdate, 0, 256);
		m_pSocket->Send("zcmingnb", 10);
		m_pSocket->Receive(recvdate, 256);
		int val = atoi(recvdate);
		memset(recvdate, 0, 256);
		m_pSocket->Send("zcmingnb", 10);
		HTREEITEM htree= m_tree.InsertItem(str,1,1,TVI_ROOT);
		recivefile(htree);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CFilemange::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	path = "";
	HTREEITEM hRootItem = m_tree.GetRootItem();
	HTREEITEM htree = m_tree.GetSelectedItem();
	CString tmp = m_tree.GetItemText(htree);
	CString tmp2;
	if (tmp == "A:" || tmp == "B:" || tmp == "C:" || tmp == "D:" || tmp == "E:" || tmp == "F:" || tmp == "G:"
		|| tmp == "H:" || tmp == "I:" || tmp == "J:" || tmp == "K:" || tmp == "L:" || tmp == "M:"
		|| tmp == "N:" || tmp == "O:" || tmp == "P:" || tmp == "Q:" || tmp == "R:" || tmp == "S:"
		|| tmp == "T:" || tmp == "U:" || tmp == "V:" || tmp == "W:" || tmp == "X:" || tmp == "Y:" || tmp == "Z:")
	{
		return;
	}
	while (tmp2 != "A:" && tmp2 != "B:" && tmp2 != "C:" && tmp2 != "D:" && tmp2 != "E:" && tmp2 != "F:" && tmp2 != "G:"
		&& tmp2 != "H:" && tmp2 != "I:" && tmp2 != "J:" && tmp2 != "K:" && tmp2 != "L:" && tmp2 != "M:"
		&& tmp2 != "N:" && tmp2 != "O:" && tmp2 != "P:" && tmp2 != "Q:" && tmp2 != "R:" && tmp2 != "S:"
		&& tmp2 != "T:" && tmp2 != "U:" && tmp2 != "V:" && tmp2 != "W:" && tmp2 != "X:" && tmp2 != "Y:" && tmp2 != "Z:")
	{

		htree = m_tree.GetParentItem(htree);
		tmp2 = m_tree.GetItemText(htree);
		if (path == "")
		{
			path = tmp2;
			continue;
		}
		path = tmp2 + _T("/") + path;
		//MessageBox(tmp2);
	}
	HTREEITEM htree2 = m_tree.GetSelectedItem();
	//MessageBox(path);
	path = path + _T("/") + tmp;
	m_pSocket->Send("fileview", 10);
	char recvdate[256] = "";
	m_pSocket->Receive(recvdate,10);
	m_pSocket->Send(T2A(path), 256);
	recivefile(htree2);
	*pResult = 0;
}


void CFilemange::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO:  �ڴ˴������Ϣ����������
	POINT p;
	GetCursorPos(&p);
	CMenu menu;
	menu.LoadMenu(IDR_MENU4);
	CMenu* pMenu;
	pMenu = menu.GetSubMenu(0);
	pMenu->EnableMenuItem(ID_32791, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32792, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32793, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32794, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID_32795, MF_BYCOMMAND | MF_ENABLED);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	pMenu->Detach();
	menu.DestroyMenu();
}
void CFilemange::addfile()
{
	USES_CONVERSION;
	if (m_tree.GetSelectedItem() != NULL)
	{
		CString ppp = getselectpath();//��ӵ�·��ĩβ����/
		if (ppp == _T(""))
		{
			MessageBox(_T("�����ڴ�����ֱ�����"));
		}
		else
		{
			if (MessageBox(ppp, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
			{
				CString ddd=_T("");
				GetDlgItemText(IDC_INPUT, ddd);
				//MessageBox(ddd);
				if (ddd==_T(""))
				{
					MessageBox(_T("���ڲ�����������ļ�����"));
					return;
				}
				ppp = ppp + _T("/") + ddd;
				m_pSocket->Send("addfodler", 10);
				m_pSocket->Receive(Tes, 10);
				m_pSocket->Send(T2A(ppp), 256);
			}
		}
	}
	else
	{
		MessageBox(_T("δѡ���ļ��м�"));
	}
	return;
}
void CFilemange::upload()
{
	USES_CONVERSION;
	CString ddd = _T("");
	GetDlgItemText(IDC_INPUT, ddd);
	//MessageBox(ddd);
	if (ddd == _T(""))
	{
		MessageBox(_T("���ڲ�����������ļ���"));
		return;
	}
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDCANCEL)
		return;
	CString loaclpath= dlg.GetPathName();
	//MessageBox(loaclpath);
	if (m_tree.GetSelectedItem() != NULL&&!loaclpath.IsEmpty())
	{
		CString ppp = getselectpath();//��ӵ�·��ĩβ����/
		if (ppp == _T(""))
		{
			MessageBox(_T("�����ڴ�����ֱ�����"));
		}
		else
		{
			if (MessageBox(ppp, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
			{
				
				ppp = ppp + _T("/") + ddd;
				m_pSocket->Send("upload", 10);
				m_pSocket->Receive(Tes, 10);
				m_pSocket->Send(T2A(ppp), 256);
				m_pSocket->Receive(Tes, 10);
				//////////////sendfile////////
				int haveSend = 0;
				const int bufferSize = 1024;
				char buffer[bufferSize] = { 0 };
				int readLen = 0;
				ifstream srcFile;
				srcFile.open(T2A(loaclpath), ios::binary);
				if (!srcFile){
					MessageBoxA(0, "fail", "tip", 0);
					return;
				}
				while (!srcFile.eof()){
					char test[10] = "";
					srcFile.read(buffer, bufferSize);
					readLen = srcFile.gcount();
					if (readLen <= 0)
					{
						m_pSocket->Send("finish", 10);
						//m_pSocket->Receive(test, 10);
						break;
					}
					m_pSocket->Send(buffer, readLen);
					if (srcFile.eof() == TRUE)
					{
						m_pSocket->Receive(test, 10);
						m_pSocket->Send("finish", 10);
						break;
					}
					m_pSocket->Receive(test, 10);
				}
				//m_pSocket->Send("finish", 10);
				srcFile.close();
			}
		}
	}
	else
	{
		MessageBox(_T("δѡ���ļ���"));
	}
	MessageBoxA(0, "�ļ��ϴ���ɣ�������Ҫ��������˫���ļ���ˢ�²鿴��ǰĿ¼", "Tip", 0);
	return;
}
void CFilemange::runthis()
{
	USES_CONVERSION;
	CString PA = path;
	int pos = m_List.GetSelectionMark();
	int sub = m_List.GetSelectedColumn();
	CString thingsname = m_List.GetItemText(pos, sub);
	if (PA=="")
	{
		MessageBox(_T("��ѡ��·����ע�⣬�޷�ֱ�����д���Ŀ¼�µ��ļ�"));
		return;
	}
	PA = PA + _T("/") + thingsname;
	if (MessageBox(PA, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
	{
		
		m_pSocket->Send("runfile", 10);
		m_pSocket->Receive(Tes, 10);
		m_pSocket->Send(T2A(PA), 256);
	}
	return;
}
void CFilemange::deletethisfolder()
{
	USES_CONVERSION;
	HTREEITEM deleteitem = m_tree.GetSelectedItem();
	if (deleteitem != NULL)
	{
		CString ppp = getselectpath();
		if (ppp==_T(""))
		{
			MessageBox(_T("��ֹɾ������"));
		}
		else
		{
			if (MessageBox(ppp, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
			{
				m_pSocket->Send("deletefolder", 20);
				m_pSocket->Receive(Tes, 10);
				m_pSocket->Send(T2A(ppp), 256);
				m_tree.DeleteItem(deleteitem);
			}
		}
	}
	else
	{
		MessageBox(_T("δѡ���ļ���"));
		////MessageBox(path);
		//int pos = m_List.GetSelectionMark();
		//int sub = m_List.GetSelectedColumn();
		//CString thingsname=m_List.GetItemText(pos,sub);
		//MessageBox(thingsname);

	}
	return;
}
void CFilemange::download()
{
	USES_CONVERSION;
	CString PA = path;
	int pos = m_List.GetSelectionMark();
	int sub = m_List.GetSelectedColumn();
	CString thingsname = m_List.GetItemText(pos, sub);
	if (PA == "")
	{
		MessageBox(_T("��ѡ��·����ע�⣬�޷�ֱ�Ӳ�������"));
		return;
	}
	PA = PA + _T("/") + thingsname;
	if (MessageBox(PA, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
	{
		CFileDialog dlg(FALSE, 0, thingsname,6UL,0,NULL);
		if (dlg.DoModal() == IDCANCEL)
			return;
		CString loaclpath = dlg.GetPathName();
		if (loaclpath.IsEmpty())
		{
			MessageBoxA(0, "ѡ���ļ���", "tip", 0);
			return;
		}
		m_pSocket->Send("download", 10);
		m_pSocket->Receive(Tes, 10);
		m_pSocket->Send(T2A(PA), 256);
		//////////////////recv/////////////////////////
		const int bufferSize = 1024;
		char buffer[bufferSize] = { 0 };
		int readLen = 0;
		ofstream desFile;
		desFile.open(T2A(loaclpath), ios::binary);
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
	}
	return;
}
void CFilemange::deletethisfile()
{
	USES_CONVERSION;
	CString PA = path;
	int pos = m_List.GetSelectionMark();
	int sub = m_List.GetSelectedColumn();
	CString thingsname = m_List.GetItemText(pos, sub);
	if (PA == "")
	{
		MessageBox(_T("��ѡ��·����ע�⣬�޷�ֱ�����д���Ŀ¼�µ��ļ�"));
		return;
	}
	PA = PA + _T("/") + thingsname;
	if (MessageBox(PA, _T("��˶�����·����Ϣ���������밴ȡ������ѡ��"), MB_OKCANCEL | MB_ICONERROR) == IDOK)
	{

		m_pSocket->Send("deletfile", 10);
		m_pSocket->Receive(Tes, 10);
		m_pSocket->Send(T2A(PA), 256);
	}
	char deleteyesoron[10] = "";
	m_pSocket->Receive(deleteyesoron, 10);
	if (strcmp(deleteyesoron,"ɾ��ʧ��")==0)
	{
		MessageBoxA(0, "�ļ�ɾ��ʧ��", "Tip", 0);
		return;
	}
	MessageBoxA(0, "�ļ�ɾ����ɣ�������Ҫ��������˫���ļ���ˢ�²鿴��ǰĿ¼", "Tip", 0);
	return;
}

void CFilemange::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	//ptree->SetItemText(m_htree, m_tname);
}


void CFilemange::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ptree->SetItemText(m_htree, m_tname);
	EndDialog(1);
}


LRESULT CFilemange::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT ret = CDialogEx::OnNcHitTest(point);
	return (ret==HTCLIENT)?HTCAPTION:ret;
}
void CFilemange::DrawBorder(CDC *pDC)
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

LRESULT CFilemange::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
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
