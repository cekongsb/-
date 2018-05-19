
// MFCSocketDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "explorer1.h"


// CMFCSocketDlg 对话框
class CMFCSocketDlg : public CDialogEx
{
// 构造
public:
	CMFCSocketDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCSOCKET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	SOCKET m_Socket;
	//CString ServerIP;
	sockaddr_in addr1;
	//CString m_strAddress;
	
//	CString m_strMsg;
//	CString m_strShMsg;

	CString m_strSendMsg;
	CString m_strRecvMsg;


	afx_msg void OnBnClickedButtonConnect();
	UINT m_intPort;
	afx_msg void OnBnClickedButtonsend();
	afx_msg HRESULT ReceiveData(WPARAM p1,LPARAM p2);
	
	afx_msg void OnBnClickedButtonDisconenct();
	CButton m_BtConnect;
	CButton m_BtDisconnect;
	CButton m_BtSend;
	//CString m_strCarNum;
	CButton m_BtModify;
	afx_msg void OnBnClickedButtonModify();
	CString m_strLock;
	CString m_strLogin;

	CString m_strGlRec;
	bool isLogin;

	CString strN_value;
	CString strE_value;
	double m_Xvalue;
	double m_Yvalue;
	UINT m_nCount;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_strJD;
	CString m_strWD;
	CButton m_BtRest;
	afx_msg void OnBnClickedButtonReset();
	CButton m_BtRetTimer;
	afx_msg void OnBnClickedButtonRetTimer();
	UINT m_nTimeCount;
	void DisplaySend(CString sendmsg);
	void DisplayRecv(CString recvmsg);


	afx_msg void OnBnClickedButtonSendontime();
	afx_msg void OnBnClickedButtonXb();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonDb();
	afx_msg void OnBnClickedButtonX();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonXn();
	afx_msg void OnBnClickedButtonN();
	afx_msg void OnBnClickedButtonDn();
	double m_dbFX;
	CComboBox m_ctlCombo;
	afx_msg void OnCbnSelchangeComboCarnum();

	CString GlCarNum;
	afx_msg void OnBnClickedButtonSaveZb();
	CButton m_BtSaveZb;
	CButton m_BtExitCar;
	afx_msg void OnBnClickedButtonExitcar();
	CButton m_BtSendOnTime;
//	CString m_ComboServerIP;
	CComboBox m_ComboServerIP;

	CString Server_IP;
	afx_msg void OnCbnSelchangeComboServerIp();
	CExplorer1 m_myweb;
	void ChangeCoordinate(CString Web_JD, CString Web_WD, CString Web_CarNum);
	void ResetMap(void);
	UINT OutLineCount;
	afx_msg void OnBnClickedButtonMdfrockTime();
	UINT m_nRockSleep;
	UINT m_nRockCount;

	UINT Int_Sleep;
	UINT Int_Count;
	CButton m_BtMdfRcok;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	UINT IntBatteryPower;

private:
	CFont			m_SupMinft, m_Minft, m_Midft, m_Maxft, m_Supft, m_RUNINft;
	CBrush			m_Redbh, m_Greenbh, m_Yellowbh, m_Grancybh, m_Blackbh;
public:
	UINT m_iBatteryPower;
	afx_msg void OnBnClickedButtonAddpower();
	afx_msg void OnBnClickedButtonDelepower();
	void SendSocketMsg(void);
	void SendSocketMsgSec(void);
	CButton m_BtAddPower;
	CButton m_BtDelePower;

	CString LockInfo;
	CString PowerLockInfo;
	CButton m_BtAddTrip;
	CButton m_BtDelTrip;
	CString m_strCarTrip;
	afx_msg void OnBnClickedButtonAddTrip();
	afx_msg void OnBnClickedButtonDelTrip();

	CString TripGl;

	CWnd *m_pMainWnd;
	CString m_strPowerLock;

	bool tmpLoginFlag;
//	CString m_nTimeCount2;
	afx_msg void OnBnClickedButtonRetTimer2();
	CButton m_BtRetTimer2;
	UINT m_nTimeCount2;

	CString Md5Info;
	CString ExitStr1;
	CString ExitStr2;
	UINT m_nCount2;
	CString UnixTime();
};
