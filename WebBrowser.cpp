// WebBrowser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSocket.h"
#include "WebBrowser.h"
#include "afxdialogex.h"


// CWebBrowser �Ի���

IMPLEMENT_DYNAMIC(CWebBrowser, CDialogEx)

CWebBrowser::CWebBrowser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWebBrowser::IDD, pParent)
{

}

CWebBrowser::~CWebBrowser()
{
}

void CWebBrowser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWebBrowser, CDialogEx)
END_MESSAGE_MAP()


// CWebBrowser ��Ϣ�������
