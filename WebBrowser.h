#pragma once


// CWebBrowser �Ի���

class CWebBrowser : public CDialogEx
{
	DECLARE_DYNAMIC(CWebBrowser)

public:
	CWebBrowser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWebBrowser();

// �Ի�������
	enum { IDD = IDD_MFCSOCKET_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
