#pragma once
#include "afxsock.h"
class CsocketapcetDlg;
class CListenSocket :
	public CSocket
{
private:
	CsocketapcetDlg *m_pMainDlg;
public:
	CListenSocket(CsocketapcetDlg *pDlg);
	~CListenSocket();
	virtual void OnAccept(int nErrorCode);
};

