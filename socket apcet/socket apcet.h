
// socket apcet.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsocketapcetApp: 
// �йش����ʵ�֣������ socket apcet.cpp
//

class CsocketapcetApp : public CWinApp
{
public:
	CsocketapcetApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsocketapcetApp theApp;