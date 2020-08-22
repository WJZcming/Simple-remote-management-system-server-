// Creg.cpp: 实现文件
//
#include"stdafx.h"
#include "socket apcet.h"
#include "Creg.h"
#include "afxdialogex.h"
CString pathr;

// Creg 对话框

IMPLEMENT_DYNAMIC(Creg, CDialogEx)

Creg::Creg(CClistensocket* pSocket, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REG, pParent)
{
	m_pSocket = pSocket;
}

Creg::~Creg()
{
}

void Creg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_TREE1, m_tree);
}


BEGIN_MESSAGE_MAP(Creg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &Creg::OnDblclkTree1)
	ON_COMMAND(ID__32796, &Creg::addkey)
	ON_COMMAND(ID__32797, &Creg::deletkey)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// Creg 消息处理程序


BOOL Creg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.InsertColumn(0, _T("数值名称"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, _T("数值"), LVCFMT_LEFT, 900);
    m_pSocket->Send("firstreg", 15);
    char recvdateregt[256] = "";
    HTREEITEM mytree;
    while (true)
    {
        m_pSocket->Receive(recvdateregt, 256);

        CString mainname(recvdateregt);
        if (mainname == _T("mainfinish"))
        {
            break;
        }
        mytree = m_tree.InsertItem(mainname, 1, 0, TVI_ROOT);
        //MessageBox(mainname);
        m_pSocket->Send("zcmingnb", 10);
        revvv(mytree);
    }
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Creg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
    pathr = _T("");
    CString rootname;
    USES_CONVERSION;
    HTREEITEM tre = m_tree.GetSelectedItem();
    CString name = m_tree.GetItemText(tre);
    CString tmp2;
    if (name == _T("HKEY_CURRENT_USER") || name == "HKEY_CLASSES_ROOT"
        || name == "HKEY_LOCAL_MACHINE" || name == "HKEY_USERS" || name == "HKEY_CURRENT_CONFIG")
    {
        return;
    }
    while (tmp2 != _T("HKEY_CURRENT_USER") && tmp2 != _T("HKEY_CLASSES_ROOT")
        && tmp2 != _T("HKEY_LOCAL_MACHINE") && tmp2 != _T("HKEY_USERS") && tmp2 != _T("HKEY_CURRENT_CONFIG"))
    {

        tre = m_tree.GetParentItem(tre);
        tmp2 = m_tree.GetItemText(tre);
        if (tmp2 == _T("HKEY_CURRENT_USER") || tmp2 == "HKEY_CLASSES_ROOT"
            || tmp2 == "HKEY_LOCAL_MACHINE" || tmp2 == "HKEY_USERS" || tmp2 == "HKEY_CURRENT_CONFIG")
        {
            rootname = tmp2;
            break;
        }
        if (pathr == "")
        {
            pathr = tmp2;
            continue;
        }
        pathr = tmp2 + _T("\\") + pathr;
    }
    if (pathr == "")
    {
        pathr = name;
    }
    else
    {
        pathr = pathr + _T("\\") + name;
    }
    tre = m_tree.GetSelectedItem();
    m_pSocket->Send("regview", 10);
    char ret[10] = "";
    m_pSocket->Receive(ret, 10);
    m_pSocket->Send(T2A(pathr), 256);
    m_pSocket->Receive(ret, 10);
    m_pSocket->Send(T2A(rootname), 256);
    //MessageBox(pathr);
    revvv(tre);
	*pResult = 0;
}
void Creg::revvv(HTREEITEM item)
{
    m_List.DeleteAllItems();
    BOOL bRet = FALSE;
    HTREEITEM hChildItem = NULL;
    while (TRUE)
    {
        bRet = m_tree.ItemHasChildren(item);
        if (!bRet)//没有孩子
        {
            break;
        }
        else
        {
            hChildItem = m_tree.GetChildItem(item);
            m_tree.DeleteItem(hChildItem);
        }
    }
    char recvkey[256] = "";
    while (1)
    {
        m_pSocket->Receive(recvkey,256);
        CString key(recvkey);
        if (key == _T("finishc"))
        {
            m_pSocket->Send("zcmingnb", 10);
            break;
        }
        m_tree.InsertItem(key, item);
        m_pSocket->Send("zcmingnb", 10);
    }
    while (1)
    {
        m_pSocket->Receive(recvkey, 256);
        CString key(recvkey);
        if (key == _T("finishc"))
        {
            m_pSocket->Send("zcmingnb", 10);
            break;
        }
        m_List.InsertItem(0, _T(""));
        m_List.SetItemText(0, 0, key);
        m_pSocket->Send("zcmingnb", 10);
        m_pSocket->Receive(recvkey, 256);
        CString keyvale(recvkey);
        m_List.SetItemText(0, 1, keyvale);
        m_pSocket->Send("zcmingnb", 10);
    }
}

void Creg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO:  在此处添加消息处理程序代码
	POINT p;
	GetCursorPos(&p);
	CMenu menu;
	menu.LoadMenu(IDR_MENU5);
	CMenu* pMenu;
	pMenu = menu.GetSubMenu(0);
	pMenu->EnableMenuItem(ID__32796, MF_BYCOMMAND | MF_ENABLED);
	pMenu->EnableMenuItem(ID__32797, MF_BYCOMMAND | MF_ENABLED);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
	pMenu->Detach();
	menu.DestroyMenu();
}
void Creg::addkey()
{
	return;
}
void Creg::deletkey()
{
	return;
}