#include "stdafx.h"
#include "ListenSocket.h"
#include "socket apcetDlg.h"

CListenSocket::CListenSocket(CsocketapcetDlg *pDlg)
{
	m_pMainDlg = pDlg;
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	m_pMainDlg-> OnAccept();
	CSocket::OnAccept(nErrorCode);
}
