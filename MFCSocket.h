
// MFCSocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



// CMFCSocketApp:
// �йش����ʵ�֣������ MFCSocket.cpp
//

class CMFCSocketApp : public CWinApp
{
public:
	CMFCSocketApp();

// ��д
public:
	virtual BOOL InitInstance();
	

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CMFCSocketApp theApp;