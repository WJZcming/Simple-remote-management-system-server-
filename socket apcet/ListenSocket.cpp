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
	// TODO:  �ڴ����ר�ô����/����û���
	m_pMainDlg-> OnAccept();
	CSocket::OnAccept(nErrorCode);
}
