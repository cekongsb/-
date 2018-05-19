// WebBrowser.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCSocket.h"
#include "WebBrowser.h"
#include "afxdialogex.h"


// CWebBrowser 对话框

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


// CWebBrowser 消息处理程序
