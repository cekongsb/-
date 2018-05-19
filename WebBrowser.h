#pragma once


// CWebBrowser 对话框

class CWebBrowser : public CDialogEx
{
	DECLARE_DYNAMIC(CWebBrowser)

public:
	CWebBrowser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWebBrowser();

// 对话框数据
	enum { IDD = IDD_MFCSOCKET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
