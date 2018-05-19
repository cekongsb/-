
// MFCSocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSocket.h"
#include "MFCSocketDlg.h"
#include "afxdialogex.h"

#include <string>
#include "Md5Encode.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <WinBase.h>


#include "WebPage.h"		//add 2017-09-14     to show map 

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CM_RECEIVED  WM_USER+2

string s1="";
string s2="";

static CString SendInfo="";
static CString RecvInfo="";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSocketDlg �Ի���



CMFCSocketDlg::CMFCSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSocketDlg::IDD, pParent)
	//, m_strAddress(_T("112.124.8.246"))
	, m_intPort(6666)
	, m_strLock(_T("����"))
	, m_strLogin(_T("δ��¼"))
	, m_Xvalue(0)
	, m_Yvalue(0)
	, m_nCount(0)
	, m_strJD(_T("108.2704783"))
	, m_strWD(_T("22.8520666"))
	, m_nTimeCount(20)
	, m_dbFX(0.001)
	, m_nRockSleep(0)
	, m_nRockCount(1)
	, m_iBatteryPower(0)
	, m_strCarTrip(_T("0"))
	, m_strPowerLock(_T("����"))
	, m_nTimeCount2(20)
	, m_nCount2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//ServerIP = _T("");
	m_strGlRec=_T("");

	strN_value=_T("");
	strE_value=_T("");

	GlCarNum=_T("");
	Server_IP=_T("");
	OutLineCount=0;
	isLogin=false;
	
	Int_Sleep = 0;
	Int_Count = 0;

	IntBatteryPower = 0;
	LockInfo = "04";
	PowerLockInfo = "04";
	TripGl = "0";

	Md5Info = "";
	ExitStr1 = "";
	ExitStr2 = "";
}

void CMFCSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_ADR, m_strAddress);
	DDX_Text(pDX, IDC_EDIT_PORT, m_intPort);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_BtConnect);
	DDX_Control(pDX, IDC_BUTTON_DISCONENCT, m_BtDisconnect);
	DDX_Control(pDX, IDC_BUTTONSEND, m_BtSend);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_BtModify);
	DDX_Text(pDX, IDC_STATIC_LOCK, m_strLock);
	DDX_Text(pDX, IDC_STATIC_LOGIN, m_strLogin);
	DDX_Text(pDX, IDC_EDIT_X, m_Xvalue);
	DDX_Text(pDX, IDC_EDIT_Y, m_Yvalue);
	DDX_Text(pDX, IDC_STATIC_COUNT, m_nCount);
	DDX_Text(pDX, IDC_EDIT_JD, m_strJD);
	DDX_Text(pDX, IDC_EDIT_WD, m_strWD);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_BtRest);
	DDX_Control(pDX, IDC_BUTTON_RET_TIMER, m_BtRetTimer);
	DDX_Text(pDX, IDC_EDIT_TIMECOUNT, m_nTimeCount);
	DDX_Text(pDX, IDC_EDIT_MDV, m_dbFX);
	DDX_Control(pDX, IDC_COMBO_CARNUM, m_ctlCombo);
	DDX_Control(pDX, IDC_BUTTON_SAVE_ZB, m_BtSaveZb);
	DDX_Control(pDX, IDC_BUTTON_EXITCAR, m_BtExitCar);
	DDX_Control(pDX, IDC_BUTTON_SENDONTIME, m_BtSendOnTime);
	//  DDX_CBString(pDX, IDC_COMBO_SERVER_IP, m_ComboServerIP);
	DDX_Control(pDX, IDC_COMBO_SERVER_IP, m_ComboServerIP);
	DDX_Control(pDX, IDC_EXPLORER1, m_myweb);
	DDX_Text(pDX, IDC_EDIT_SLEEP, m_nRockSleep);
	DDX_Text(pDX, IDC_EDIT_ROCKTIME, m_nRockCount);
	DDX_Control(pDX, IDC_BUTTON_MDFROCK_TIME, m_BtMdfRcok);
	DDX_Text(pDX, IDC_EDIT_BATTERY, m_iBatteryPower);
	DDX_Control(pDX, IDC_BUTTON_ADDPOWER, m_BtAddPower);
	DDX_Control(pDX, IDC_BUTTON_DELEPOWER, m_BtDelePower);
	DDX_Control(pDX, IDC_BUTTON_ADD_TRIP, m_BtAddTrip);
	DDX_Control(pDX, IDC_BUTTON_DEL_TRIP, m_BtDelTrip);
	DDX_Text(pDX, IDC_EDIT_CARTRIP, m_strCarTrip);
	DDX_Text(pDX, IDC_STATIC_POWERLOCK, m_strPowerLock);
	//  DDX_Text(pDX, IDC_EDIT_TIMECOUNT2, m_nTimeCount2);
	DDX_Control(pDX, IDC_BUTTON_RET_TIMER2, m_BtRetTimer2);
	DDX_Text(pDX, IDC_EDIT_TIMECOUNT2, m_nTimeCount2);
	DDX_Text(pDX, IDC_STATIC_COUNT2, m_nCount2);
}

BEGIN_MESSAGE_MAP(CMFCSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMFCSocketDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTONSEND, &CMFCSocketDlg::OnBnClickedButtonsend)
	ON_MESSAGE(CM_RECEIVED,ReceiveData)
	ON_BN_CLICKED(IDC_BUTTON_DISCONENCT, &CMFCSocketDlg::OnBnClickedButtonDisconenct)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CMFCSocketDlg::OnBnClickedButtonModify)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMFCSocketDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_RET_TIMER, &CMFCSocketDlg::OnBnClickedButtonRetTimer)
	ON_BN_CLICKED(IDC_BUTTON_SENDONTIME, &CMFCSocketDlg::OnBnClickedButtonSendontime)
	ON_BN_CLICKED(IDC_BUTTON_XB, &CMFCSocketDlg::OnBnClickedButtonXb)
	ON_BN_CLICKED(IDC_BUTTON_B, &CMFCSocketDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_DB, &CMFCSocketDlg::OnBnClickedButtonDb)
	ON_BN_CLICKED(IDC_BUTTON_X, &CMFCSocketDlg::OnBnClickedButtonX)
	ON_BN_CLICKED(IDC_BUTTON_D, &CMFCSocketDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_XN, &CMFCSocketDlg::OnBnClickedButtonXn)
	ON_BN_CLICKED(IDC_BUTTON_N, &CMFCSocketDlg::OnBnClickedButtonN)
	ON_BN_CLICKED(IDC_BUTTON_DN, &CMFCSocketDlg::OnBnClickedButtonDn)
	ON_CBN_SELCHANGE(IDC_COMBO_CARNUM, &CMFCSocketDlg::OnCbnSelchangeComboCarnum)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_ZB, &CMFCSocketDlg::OnBnClickedButtonSaveZb)
	ON_BN_CLICKED(IDC_BUTTON_EXITCAR, &CMFCSocketDlg::OnBnClickedButtonExitcar)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER_IP, &CMFCSocketDlg::OnCbnSelchangeComboServerIp)
	ON_BN_CLICKED(IDC_BUTTON_MDFROCK_TIME, &CMFCSocketDlg::OnBnClickedButtonMdfrockTime)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADDPOWER, &CMFCSocketDlg::OnBnClickedButtonAddpower)
	ON_BN_CLICKED(IDC_BUTTON_DELEPOWER, &CMFCSocketDlg::OnBnClickedButtonDelepower)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TRIP, &CMFCSocketDlg::OnBnClickedButtonAddTrip)
	ON_BN_CLICKED(IDC_BUTTON_DEL_TRIP, &CMFCSocketDlg::OnBnClickedButtonDelTrip)
	ON_BN_CLICKED(IDC_BUTTON_RET_TIMER2, &CMFCSocketDlg::OnBnClickedButtonRetTimer2)
END_MESSAGE_MAP()


// CMFCSocketDlg ��Ϣ�������

BOOL CMFCSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//tmpLoginFlag = false;
	m_pMainWnd = AfxGetMainWnd();
	//m_pMainWnd->SetWindowText(_T("�������Ϊ��755000001��")); 
	
	m_iBatteryPower = 100;
	IntBatteryPower = m_iBatteryPower;
	m_strCarTrip = "060";
	TripGl = m_strCarTrip;

	m_SupMinft.CreatePointFont(100, _T("Arial"));
	m_Minft.CreatePointFont(200, _T("Arial"));
	m_Midft.CreatePointFont(350, _T("Arial"));
	m_Maxft.CreatePointFont(1000,_T("Arial"));
	m_RUNINft.CreatePointFont(500,_T("Arial"));

	m_Redbh.CreateSolidBrush(RGB(255,0,0));
	m_Greenbh.CreateSolidBrush(RGB(0,255,0));
	m_Yellowbh.CreateSolidBrush(RGB(255,255,0));
	m_Grancybh.CreateSolidBrush(RGB(82,64,111));


	CString strURL;//htm�ļ���ȫ·��  
	char chCurtPath[MAX_PATH];//��ǰĿ¼  
	 
	GetCurrentDirectory(MAX_PATH,chCurtPath);//��ȡ��ǰĿ¼��������chCurtPath��  	
	strURL = (CString)chCurtPath + "\\Map.htm" ;//��chCurtDrct����ǿ��ת����CString,��ƴ�ӳ�ȫ·��  
	m_myweb.Navigate(strURL, NULL, NULL, NULL, NULL); 

	//**��ʼ����������Լ�ָ��������ŵ�����**//
	((CComboBox*)GetDlgItem(IDC_COMBO_CARNUM))->ResetContent();
	
	char RecvInfo[64];
	CString init_select;
	char init_eValue[64];
	char init_nValue[64];

	for(int i=1; i <= 1000; i++)
	{
		CString str_i;
		CString PrefixCar="car";
		str_i.Format("%d",i);
		PrefixCar += str_i;

		GetPrivateProfileString("CarData",PrefixCar,"",RecvInfo,64,".\\CarNumData.ini");

		if (strcmp(RecvInfo, "")==0)
		{
			break;
		}

		((CComboBox*)GetDlgItem(IDC_COMBO_CARNUM))->AddString(RecvInfo);
	}

	m_ctlCombo.SetCurSel(0);
	m_ctlCombo.GetLBText(0,init_select);
	
	GetPrivateProfileString(init_select, "E_value", "", init_eValue, 64, ".\\CarLocateInfo.ini");
	GetPrivateProfileString(init_select, "N_value", "", init_nValue, 64, ".\\CarLocateInfo.ini");

	m_strJD = init_eValue;
	m_strWD = init_nValue;

	GlCarNum=init_select;

	//**��ʼ�����ӷ�������IP��ַ**//
	((CComboBox*)GetDlgItem(IDC_COMBO_SERVER_IP))->ResetContent();
	
	char RecvServerIP[64];
	CString init_ServerIP;

	for (int i = 1; i <= 20; i++)
	{
		CString str_serverIP;
		CString PrefixIP = "IP";

		str_serverIP.Format("%d",i);
		PrefixIP += str_serverIP;

		GetPrivateProfileString("ServerIP",PrefixIP,"",RecvServerIP,64,".\\CarNumData.ini");

		if (strcmp(RecvServerIP, "")==0)
		{
			break;
		}

		((CComboBox*)GetDlgItem(IDC_COMBO_SERVER_IP))->AddString(RecvServerIP);
	}

	m_ComboServerIP.SetCurSel(0);
	m_ComboServerIP.GetLBText(0,init_ServerIP);
	Server_IP=init_ServerIP;
	
	m_BtSend.EnableWindow(false);
	m_BtModify.EnableWindow(false);
	m_BtDisconnect.EnableWindow(false);
	m_BtRest.EnableWindow(false);
	m_BtSaveZb.EnableWindow(false);
	m_BtExitCar.EnableWindow(false);
	m_BtRetTimer.EnableWindow(false);
	m_BtRetTimer2.EnableWindow(false);
	m_BtSendOnTime.EnableWindow(false);
	m_BtMdfRcok.EnableWindow(false);
	m_BtAddPower.EnableWindow(false);
	m_BtDelePower.EnableWindow(false);
	m_BtAddTrip.EnableWindow(false);
	m_BtDelTrip.EnableWindow(false);
	Int_Count = m_nRockCount;
	Int_Sleep = m_nRockSleep;

	UpdateData(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCSocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCSocketDlg::OnBnClickedButtonConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	//hostent* phost=gethostbyname("");
	//char* localIP=inet_ntoa(*(struct in_addr*)*phost->h_addr_list);
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_Socket == INVALID_SOCKET){
		MessageBox("�׽��ִ���ʧ�ܣ�");
		return;
	}
	
	if(Server_IP.IsEmpty() || m_intPort == 0){
		MessageBox("�����������IP��ַ�Ͷ˿ںţ�");
		return;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(Server_IP);
	addr.sin_port = htons(m_intPort);

	if (connect(m_Socket, (sockaddr*)&addr, sizeof(addr)) != 0){
		MessageBox("����ʧ��");
		return;
	}
	else{
		MessageBox("���ӳɹ�");
	}
	
	m_BtConnect.EnableWindow(false);
	m_ComboServerIP.EnableWindow(false);
	m_BtSend.EnableWindow(true);
	m_BtDisconnect.EnableWindow(true);
	m_ctlCombo.EnableWindow(true);
	m_BtConnect.SetWindowText("���ӳɹ�");
	//GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(false); 
	WSAAsyncSelect(m_Socket, m_hWnd, CM_RECEIVED, FD_READ);
}


void CMFCSocketDlg::OnBnClickedButtonsend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);	
	if(GlCarNum.IsEmpty()){
		MessageBox("�����복����ţ�");
		return;
	}

	if (m_strJD.IsEmpty()||m_strWD.IsEmpty()){
		MessageBox("�����복����γ�ȣ�");
		return;
	}
	else{
		strN_value = m_strWD;
		strE_value = m_strJD;
	}

	//MessageBox(m_strMsg.GetBuffer(0));
	CString strMd5Info;
	CString strs1;
	CString strs2;
	strs2 = GlCarNum.Trim();			//modify by me 2017-09-04

	int IntS1;
	//int IntS2;
	string s3,src;
	//s1="352923051336";
	//s2="70677170100001";
	s3 = "XIAOMIKEJI";
	
	srand(clock());				//��ʱ��Ϊ�������������
	//IntS1=rand()%100000;
	//IntS2=rand()%100000;		//modify by me 2017-09-04
	//IntS1 = atoi(GlCarNum.Trim())%100000;
	//s1 = to_string(IntS1);
	s1 = GlCarNum.Trim().Mid(3,10);
	//MessageBox(s1.c_str());
	s1 = "8685750" + s1;
	//MessageBox(s1.c_str());
	//s1 = "IMEI";				//2018-04-26
	//s2=to_string(IntS2);		//modify by me 2017-09-04
	//s2 = strs2.GetBuffer(strs2.GetLength());
	s2 = UnixTime().GetBuffer(0);
	src = s1+s2+s3;
	
    Md5Encode encode_obj;					//md5���ܷ�������
    string ret = encode_obj.Encode(src);	//md5����
	transform(ret.begin(), ret.end(), ret.begin(), ::toupper);		//����stl�㷨���ַ���ת�ɴ�д
	
	strMd5Info = ret.c_str();			//string��ת��ΪCString
	strs1 = s1.c_str();
	//strs2=s2.c_str();				//modify by 2017-09-04
		
	Md5Info = strMd5Info;
	ExitStr1 = strs1;
	ExitStr2 = strs2;

	//m_strSendMsg.Format("{DEVICE*P00-V1.0.0*1497584473*LOGIN*XM_BICY_B01Pro_V11*%s*%s*%s*NULL}", strMd5Info, strs1, strs2);	
	//{DEVICE*P00-V1.0.0*1497584473*LOGIN_M2*XM_BICY_B01Pro_V11*CC0A3AD5A1C7CFE595F80AE31127D9F0*32302*77600000100*NULL}
	//{DEVICE*P00-V1.0.0*1497584473*LOGIN_M2*XM_BICY_B01Pro_V11*CC0A3AD5A1C7CFE595F80AE31127D9F0*IMEI*77600000100*NULL}
	m_strSendMsg.Format("{DEVICE*P00-V1.0.0*%s*LOGIN_M2*XM_BICY_B01Pro_V11*%s*%s*%s*NULL}", s2.c_str(), strMd5Info, strs1, strs2);
	
	//MessageBox(m_strSendMsg);
	//UpdateData(false);

	if (!m_strSendMsg.IsEmpty()){
		int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
		DisplaySend(m_strSendMsg);
		m_strSendMsg.ReleaseBuffer();
		
		if (i == -1){
			MessageBox("��������ʧ�ܣ�");
			return;
		}
	}
	else{
		MessageBox("�������¼��Ϣ");
		return;
	}
}

HRESULT CMFCSocketDlg::ReceiveData(WPARAM p1,LPARAM p2)
{
	char buffer[1024];
	int num = recv(m_Socket, buffer, 1024, 0);
	m_strRecvMsg = buffer;
	DisplayRecv(m_strRecvMsg);

	//SC001*D*066*SET*7f0000010b5700000001*END
	int LoginFlag = -1;			//0��ʾ�ҵ�, -1��ʾû�ҵ�
	int MotorLockFlag = -1;
	int BatteryLockFlag = -1;
	int ExitLoginFlag = -1;
	int TimerFlag = -1;

	TimerFlag = m_strRecvMsg.Find("SC000");
	LoginFlag = m_strRecvMsg.Find("SC001");
	ExitLoginFlag = m_strRecvMsg.Find("SC002");
	MotorLockFlag = m_strRecvMsg.Find("SC102");
	BatteryLockFlag = m_strRecvMsg.Find("SC103");

	if(LoginFlag == 0){
		CString strs2;
		CString strRec;
		int intBegin,intEnd;
		intBegin = m_strRecvMsg.Find("SET");
		intBegin = m_strRecvMsg.Find("*",intBegin);
		intEnd = m_strRecvMsg.Find("*",intBegin+1);
		strRec = m_strRecvMsg.Mid(intBegin+1,intEnd-intBegin-1);

		m_strGlRec = strRec;
		isLogin = true;
		SetTimer(1, 20000, NULL);
		SetTimer(2, 20000, NULL);
		m_strLogin = "��¼�ɹ�";
		ChangeCoordinate(strE_value, strN_value, GlCarNum);		//add 2017-09-14  to show map
		m_pMainWnd->SetWindowText(_T("M2_")+_T(GlCarNum));
		m_BtModify.EnableWindow(true);
		m_BtSend.EnableWindow(false);
		m_BtRest.EnableWindow(true);
		m_ctlCombo.EnableWindow(false);
		m_BtSaveZb.EnableWindow(true);
		m_BtExitCar.EnableWindow(true);
		m_BtRetTimer.EnableWindow(true);
		m_BtRetTimer2.EnableWindow(true);
		m_BtSendOnTime.EnableWindow(true);
		m_BtMdfRcok.EnableWindow(true);
		m_BtAddPower.EnableWindow(true);
		m_BtDelePower.EnableWindow(true);
		m_BtAddTrip.EnableWindow(true);
		m_BtDelTrip.EnableWindow(true);
		UpdateData(false);			
		
	}
	//����:SC102*D*051*SET*75512345678*STATE=OPEN*END
	//->SC102*S*066*SET*75512345678*OPEN=TRUE/FALSE/ERROR*END
	//����:SC102*D*052*SET*75512345678*STATE=CLOSE*END
	//->SC102*S*066*SET*75512345678*CLOSE=TRUE/FALSE/ERROR*END
	else if(MotorLockFlag == 0)		//�����
	{
		int isOpenFlag = -1;
		int isCloseFlag = -1;
		isOpenFlag = m_strRecvMsg.Find("OPEN");
		isCloseFlag = m_strRecvMsg.Find("CLOSE");

		if (isOpenFlag > 0){
			m_strLock="����";
			UpdateData(false);
			LockInfo = "02";
						
			//SC102*S*066*SET*75512345678*OPEN=TRUE/FALSE/ERROR*END            -->to M2
			m_strSendMsg.Format("SC102*S*066*SET*%s*OPEN=TRUE*END",GlCarNum.Trim());
			for(int icount=1; icount<=Int_Count; icount++){
				int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
				DisplaySend(m_strSendMsg);
							
				if (i == -1){
					MessageBox("����--�������--����ʧ�ܣ�");
					return false;
				}
				else{							
					CString strCount;
					strCount.Format("%d", icount);
					DisplaySend("����--�������--������" + strCount);	
					//delay()ʱ������
					if (Int_Sleep != 0){
						Sleep(Int_Sleep * 1000);
					}
					else{
						Sleep(1000);
					}
				}						
			}
			m_strSendMsg.ReleaseBuffer();
		}
		else if(isCloseFlag > 0){
			m_strLock = "����";
			UpdateData(false);
			LockInfo = "04";

			//SC102*S*066*SET*75512345678*CLOSE=TRUE/FALSE/ERROR*END
			m_strSendMsg.Format("SC102*S*066*SET*%s*CLOSE=TRUE*END", GlCarNum.Trim());
			for(int icount=1; icount<=Int_Count; icount++){
				int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
				DisplaySend(m_strSendMsg);
			
				if (i == -1){
					MessageBox("����--�������--����ʧ�ܣ�");
					return false;
				}
				else{
					CString strCount;
					strCount.Format("%d",icount);
					DisplaySend("����--�������--������" + strCount);
					//delay()ʱ������
					if (Int_Sleep != 0){
						Sleep(Int_Sleep * 1000);
					}
					else{
						Sleep(1000);
					}
				}
			}		
			m_strSendMsg.ReleaseBuffer();
		}
		else{
			//
		}

	}
	else if(BatteryLockFlag == 0)	//�����
	{
		int isOpenFlag = -1;
		int isCloseFlag = -1;
		isOpenFlag = m_strRecvMsg.Find("OPEN");
		isCloseFlag = m_strRecvMsg.Find("CLOSE");

		if (isOpenFlag > 0){
			m_strPowerLock = "����";
			UpdateData(false);
			PowerLockInfo = "02"; 
						
			//SC103*S*066*SET*75512345678*OPEN=TRUE/FALSE/ERROR*END            -->to M2
			m_strSendMsg.Format("SC103*S*066*SET*%s*OPEN=TRUE*END",GlCarNum.Trim());
			for(int icount=1; icount<=Int_Count; icount++){
				int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
				DisplaySend(m_strSendMsg);
							
				if (i == -1){
					MessageBox("����--��ؿ���--����ʧ�ܣ�");
					return false;
				}
				else{						
					CString strCount;
					strCount.Format("%d", icount);
					DisplaySend("����--��ؿ���--������" + strCount);
					//delayʱ������
					if (Int_Sleep != 0){
						Sleep(Int_Sleep * 1000);
					}
					else{
						Sleep(1000);
					}
				}							
			}
			m_strSendMsg.ReleaseBuffer();
		}
		else if(isCloseFlag > 0){
			m_strLock = "����";
			UpdateData(false);
			LockInfo = "04";
						
			//SC103*S*066*SET*75512345678*CLOSE=TRUE/FALSE/ERROR*END
			m_strSendMsg.Format("SC103*S*066*SET*%s*CLOSE=TRUE*END", GlCarNum.Trim());
			for(int icount=1; icount<=Int_Count; icount++){
				int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
				DisplaySend(m_strSendMsg);
			
				if (i == -1){
					MessageBox("����--��ع���--����ʧ�ܣ�");
					return false;
				}
				else{
					CString strCount;
					strCount.Format("%d",icount);
					DisplaySend("����--��ع���--������" + strCount);
					//delayʱ������
					if (Int_Sleep != 0){
						Sleep(Int_Sleep * 1000);
					}
					else{
						Sleep(1000);
					}
				}		
			}	
			m_strSendMsg.ReleaseBuffer();
		}
		else{
			//
		}
	}
	//���������
	else if(TimerFlag == 0){
		
		//SC999*S*031*GET*75512345678*END\r\n		
		m_strSendMsg.Format("SC999*S*031*GET*%s*END\r\n", GlCarNum.Trim());
		int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
		Sleep(200);
		DisplaySend(m_strSendMsg);
		
		if (i == -1){
			MessageBox("����������ݰ�ʧ��");
			return false;
		}
		m_strSendMsg.ReleaseBuffer();
	}
	else if(ExitLoginFlag == 0){
		KillTimer(1);
		KillTimer(2);
		m_strLogin = "δ��¼";
		m_strLock = "����";
		m_strPowerLock = "����";
		SendInfo = "";
		RecvInfo = "";
		m_nCount = 0;
		m_nCount2 = 0;
		LockInfo = "04";
		PowerLockInfo = "04";
		ResetMap();

		m_pMainWnd->SetWindowText(_T("M2_�����ͻ���"));
		((CEdit*)GetDlgItem(IDC_EDIT_MSG))->SetWindowText("");
		((CEdit*)GetDlgItem(IDC_EDIT_SHMSG))->SetWindowText("");	
		m_ctlCombo.EnableWindow(false);
		m_BtSend.EnableWindow(false);
		m_BtExitCar.EnableWindow(false);
		m_BtRest.EnableWindow(false);
		m_BtModify.EnableWindow(false);
		m_BtSaveZb.EnableWindow(false);
		m_BtRetTimer.EnableWindow(false);
		m_BtRetTimer2.EnableWindow(false);
		m_BtSendOnTime.EnableWindow(false);
		m_BtMdfRcok.EnableWindow(false);
		m_BtAddPower.EnableWindow(false);
		m_BtDelePower.EnableWindow(false);
		m_BtAddTrip.EnableWindow(false);
		m_BtDelTrip.EnableWindow(false);
		UpdateData(false);
	}
	else{
		//other not use Msg
	}
	return true;
}

void CMFCSocketDlg::OnBnClickedButtonDisconenct()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	closesocket(m_Socket);
	m_strLogin="δ��¼";
	m_strLock="����";
	m_strPowerLock = "����";
	LockInfo = "04";
	PowerLockInfo = "04";
	
	((CEdit*)GetDlgItem(IDC_EDIT_MSG))->SetWindowText("");
	((CEdit*)GetDlgItem(IDC_EDIT_SHMSG))->SetWindowText("");
	SendInfo = "";
	RecvInfo = "";	
	m_nCount = 0;
	m_nCount2 = 0;
	KillTimer(1);
	KillTimer(2);
	ResetMap();

	m_pMainWnd->SetWindowText(_T("M2_�����ͻ���"));
	m_BtConnect.SetWindowText("���ӷ�����");
	m_BtConnect.EnableWindow(true);
	m_ComboServerIP.EnableWindow(true);
	m_BtSend.EnableWindow(false);
	m_BtModify.EnableWindow(false);
	m_BtDisconnect.EnableWindow(false);
	m_BtRest.EnableWindow(false);
	m_BtSaveZb.EnableWindow(false);
	m_BtRetTimer.EnableWindow(false);
	m_BtRetTimer2.EnableWindow(false);
	m_BtSendOnTime.EnableWindow(false);
	m_BtExitCar.EnableWindow(false);
	m_BtMdfRcok.EnableWindow(false);
	m_BtAddPower.EnableWindow(false);
	m_BtDelePower.EnableWindow(false);
	m_BtAddTrip.EnableWindow(false);
	m_BtDelTrip.EnableWindow(false);
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN += m_Xvalue;
	DbeE += m_Yvalue;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	UpdateData(false);
		
}

void CMFCSocketDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;
	if(nIDEvent == 1)
	{
		//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
		SendSocketMsg();
		m_nCount++;
	}
	else if(nIDEvent == 2)
	{
		SendSocketMsgSec();
		m_nCount2++;
	}

	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCSocketDlg::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	strN_value = m_strWD;
	strE_value = m_strJD;
}

void CMFCSocketDlg::OnBnClickedButtonRetTimer()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(1);
	UpdateData(true);
	SetTimer(1, 1000*m_nTimeCount, NULL);
}

void CMFCSocketDlg::OnBnClickedButtonRetTimer2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(2);
	UpdateData(true);
	SetTimer(2, 1000*m_nTimeCount2, NULL);
}


inline void CMFCSocketDlg::DisplaySend(CString sendmsg)
{
	SendInfo += sendmsg;
	SendInfo += "\r\n";
	SetDlgItemText(IDC_EDIT_MSG, SendInfo.GetBuffer(SendInfo.GetLength()));
	int a=((CEdit*)GetDlgItem(IDC_EDIT_MSG))->GetLineCount();
	((CEdit*)GetDlgItem(IDC_EDIT_MSG))->LineScroll(a,0);
	//UpdateData(false);
}


inline void CMFCSocketDlg::DisplayRecv(CString recvmsg)
{
	RecvInfo += recvmsg;
	RecvInfo += "\r\n";
	SetDlgItemText(IDC_EDIT_SHMSG, RecvInfo.GetBuffer(RecvInfo.GetLength()));
	int a = ((CEdit*)GetDlgItem(IDC_EDIT_SHMSG))->GetLineCount();
	((CEdit*)GetDlgItem(IDC_EDIT_SHMSG))->LineScroll(a,0);
	//UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonSendontime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	
	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsg();
	SendSocketMsgSec();
	m_nCount++;
	m_nCount2++;
	UpdateData(false);

	
	////////////////////һ��Ϊ������///////////////////////
	
}


void CMFCSocketDlg::OnBnClickedButtonXb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN += m_dbFX;
	DbeE -= m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN += m_dbFX;
	//DbeE -= m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonDb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN += m_dbFX;
	DbeE += m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonX()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	//DbeN  = m_dbFX;
	DbeE -= m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonD()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	//DbeN  = m_dbFX;
	DbeE += m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonXn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN -= m_dbFX;
	DbeE -= m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonN()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN -= m_dbFX;
	//DbeE += m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonDn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	double DbeN;
	double DbeE;

	DbeN = atof(m_strWD.GetBuffer());
	DbeE = atof(m_strJD.GetBuffer());

	DbeN -= m_dbFX;
	DbeE += m_dbFX;

	m_strWD.Format("%.7lf",DbeN);
	m_strJD.Format("%.7lf",DbeE);

	strE_value = m_strJD;
	strN_value = m_strWD;

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsgSec();
	m_nCount2++;
	UpdateData(false);
}

void CMFCSocketDlg::OnCbnSelchangeComboCarnum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str_select;
	char eValue[64];
	char nValue[64];
	int nselect=m_ctlCombo.GetCurSel();
	m_ctlCombo.GetLBText(nselect,str_select);

	GetPrivateProfileString(str_select,"E_value","",eValue,64,".\\CarLocateInfo.ini");
	GetPrivateProfileString(str_select,"N_value","",nValue,64,".\\CarLocateInfo.ini");

	m_strJD = eValue;
	m_strWD = nValue;

	GlCarNum = str_select;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonSaveZb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WritePrivateProfileString(GlCarNum, "E_value", m_strJD, ".\\CarLocateInfo.ini");
	WritePrivateProfileString(GlCarNum, "N_value", m_strWD, ".\\CarLocateInfo.ini");
}


void CMFCSocketDlg::OnBnClickedButtonExitcar()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//{DEVICE*P00-V1.0.0*1497584473*LOGOUT_M2*XM_BICY_B01Pro_V11*CC0A3AD5A1C7CFE595F80AE31127D9F0*32302*77600000100*NULL}
	m_strSendMsg.Format("{DEVICE*P00-V1.0.0*1497584473*LOGOUT_M2*XM_BICY_B01Pro_V11*%s*%s*%s*NULL}", Md5Info, ExitStr1, ExitStr2);
	//UpdateData(false);

	if (!m_strSendMsg.IsEmpty()){
		int i = send(m_Socket, m_strSendMsg.GetBuffer(0), m_strSendMsg.GetLength(), 0);
		DisplaySend(m_strSendMsg);
		m_strSendMsg.ReleaseBuffer();
		
		if (i == -1){
			MessageBox("��������ʧ�ܣ�");
			return;
		}
	}
	else{
		MessageBox("�������¼��Ϣ");
		return;
	}	
}


void CMFCSocketDlg::OnCbnSelchangeComboServerIp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int select_ServerIP;
	CString TempServerIP;

	select_ServerIP = m_ComboServerIP.GetCurSel();
	m_ComboServerIP.GetLBText(select_ServerIP,TempServerIP);

	Server_IP = TempServerIP;
	UpdateData(false);
}


inline void CMFCSocketDlg::ChangeCoordinate(CString Web_JD, CString Web_WD, CString Web_CarNum)
{
	CWebPage web;
	web.SetDocument(m_myweb.get_Document());

	CStringArray caParam;
	caParam.Add(Web_JD);
	caParam.Add(Web_WD);
	caParam.Add(Web_CarNum);
	web.CallJScript("justmarkfun",caParam);
}


void CMFCSocketDlg::ResetMap(void)
{
	CWebPage web;
	web.SetDocument(m_myweb.get_Document());

	CStringArray caParam;
	web.CallJScript("RemoveMarker",caParam);
}


void CMFCSocketDlg::OnBnClickedButtonMdfrockTime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	Int_Count = m_nRockCount;
	Int_Sleep = m_nRockSleep;
}


HBRUSH CMFCSocketDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	/*
	m_SupMinft.CreatePointFont(100, _T("Arial"));
	m_Minft.CreatePointFont(200, _T("Arial"));
	m_Midft.CreatePointFont(350, _T("Arial"));
	m_Maxft.CreatePointFont(1000,_T("Arial"));
	m_RUNINft.CreatePointFont(500,_T("Arial"));

	m_Redbh.CreateSolidBrush(RGB(255,0,0));
	m_Greenbh.CreateSolidBrush(RGB(0,255,0));
	m_Yellowbh.CreateSolidBrush(RGB(255,255,0));
	m_Grancybh.CreateSolidBrush(RGB(82,64,111));
	*/

	if(IDC_STATIC_LOGIN == pWnd->GetDlgCtrlID()){
		pDC->SelectObject(&m_SupMinft);
		pDC->SetBkMode(TRANSPARENT);
		if(!strcmp("δ��¼", m_strLogin)){
			pDC->SetTextColor(RGB(255,255,0));
			return m_Redbh;
		}
		
		if(!strcmp("��¼�ɹ�", m_strLogin)){
			pDC->SetTextColor(RGB(82,64,111));
			return m_Greenbh;	
		}
	}

	if(IDC_STATIC_LOCK == pWnd->GetDlgCtrlID()){
		pDC->SelectObject(&m_SupMinft);
		pDC->SetBkMode(TRANSPARENT);
		/*if(!strcmp("δ֪", m_strLock))
		{
			pDC->SetTextColor(RGB(0,255,0));
			return m_Yellowbh;
		}*/
		
		if(!strcmp("����", m_strLock)){
			pDC->SetTextColor(RGB(82,64,111));
			return m_Greenbh;	
		}

		if(!strcmp("����", m_strLock)){
			pDC->SetTextColor(RGB(255,255,0));
			return m_Redbh;	
		}
	}

	if(IDC_STATIC_POWERLOCK == pWnd->GetDlgCtrlID()){
		pDC->SelectObject(&m_SupMinft);
		pDC->SetBkMode(TRANSPARENT);
				
		if(!strcmp("����", m_strPowerLock)){
			pDC->SetTextColor(RGB(82,64,111));
			return m_Greenbh;	
		}

		if(!strcmp("����", m_strPowerLock)){
			pDC->SetTextColor(RGB(255,255,0));
			return m_Redbh;	
		}
	}
	
	// ���������ʾ
	if(IDC_EDIT_BATTERY == pWnd->GetDlgCtrlID()){
		pDC->SelectObject(&m_SupMinft);
		pDC->SetBkMode(TRANSPARENT);
		if(m_iBatteryPower >=40 && m_iBatteryPower < 80){
			pDC->SetTextColor(RGB(0,255,0));
			return m_Yellowbh;
		}
		
		if(m_iBatteryPower >=80 && m_iBatteryPower <= 100){
			pDC->SetTextColor(RGB(82,64,111));
			return m_Greenbh;	
		}

		if(m_iBatteryPower >=0 && m_iBatteryPower < 40 ){
			pDC->SetTextColor(RGB(255,255,0));
			return m_Redbh;	
		}
	}

	if(IDC_EDIT_CARTRIP == pWnd->GetDlgCtrlID()){
		pDC->SelectObject(&m_SupMinft);
		pDC->SetBkMode(TRANSPARENT);
		
		pDC->SetTextColor(RGB(128,0,64));
		return m_Greenbh;		
	}
		
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CMFCSocketDlg::OnBnClickedButtonAddpower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_iBatteryPower < 100){
		m_iBatteryPower++;
	}

	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsg();
	m_nCount++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonDelepower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_iBatteryPower > 0){
		m_iBatteryPower--;
	}
	
	IntBatteryPower = m_iBatteryPower;
	TripGl = m_strCarTrip;

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsg();
	m_nCount++;
	UpdateData(false);
}


void CMFCSocketDlg::SendSocketMsg(void)
{
	//{DEVICE*0a1b9a8b0fa0000020b6*01000000029*DTU*DE,S,166,01000000029,50,GET,02,NORMAL,�����,�����02��04��,94+ERROR+0000,065,00,000000UP0NORM,12+12+0+337+40,(E+116.3330166+0.00+N+39.9750150+0.00),(E+000.000000+N+000.000000+0.000),All,END*}
	/*m_strSendMsg.Format("{DEVICE*%s*%s*DTU*DE,S,166,%s,50,GET,02,NORMAL,%s,%s,%d+ERROR+0565,%s,00,000000UP0NORM,12+4+0+111+14,(E+%s+0.00+N+%s+0.00),(E+000.000000+N+000.000000+0.000),All,END*}", 
		m_strGlRec, GlCarNum.Trim(), GlCarNum.Trim(), LockInfo, PowerLockInfo, IntBatteryPower, TripGl, strE_value, strN_value);*/	
	
	//SC011*S*066*GET*75512345678*CLOSE*CLOSE*072000mV*099*088*066*NORMAL*END\r\n
	m_strSendMsg.Format("SC011*S*066*GET*%s*CLOSE*CLOSE*072000mV*%03d*%s*066*NORMAL*END\r\n", GlCarNum.Trim(), IntBatteryPower, TripGl);
	
	if (!m_strSendMsg.IsEmpty()){
		int i = send(m_Socket,m_strSendMsg.GetBuffer(0),m_strSendMsg.GetLength(),0);
		
		ChangeCoordinate(strE_value, strN_value, GlCarNum);		//add 2017-09-14  to show map
		DisplaySend(m_strSendMsg);
		m_strSendMsg.ReleaseBuffer();
		
		if (i == -1){			
			OutLineCount++;
			if (OutLineCount == 3){
				KillTimer(1);
				MessageBox("�豸��������쳣������֮���������ӷ�������");
				return;
			}
			else{
				MessageBox("��ʱ��������Ϣ����ʧ�ܣ�");
				return;
			}
		}
		else{
			OutLineCount=0;
		}
	}
	else{
		MessageBox("���鷢�͵�������Ϣ��");
		return;
	}
}

void CMFCSocketDlg::SendSocketMsgSec(void)
{
	//{DEVICE*0a1b9a8b0fa0000020b6*01000000029*DTU*DE,S,166,01000000029,50,GET,02,NORMAL,�����,�����02��04��,94+ERROR+0000,065,00,000000UP0NORM,12+12+0+337+40,(E+116.3330166+0.00+N+39.9750150+0.00),(E+000.000000+N+000.000000+0.000),All,END*}
	/*m_strSendMsg.Format("{DEVICE*%s*%s*DTU*DE,S,166,%s,50,GET,02,NORMAL,%s,%s,%d+ERROR+0565,%s,00,000000UP0NORM,12+4+0+111+14,(E+%s+0.00+N+%s+0.00),(E+000.000000+N+000.000000+0.000),All,END*}", 
		m_strGlRec, GlCarNum.Trim(), GlCarNum.Trim(), LockInfo, PowerLockInfo, IntBatteryPower, TripGl, strE_value, strN_value);*/	
	
	//SC012*S*066*GET*75512345678*32*22*08*123*099*223*E,121.12345,N,31.23456*5678*END\r\n
	//SC012*S*066*GET*01100000002*21*15**26*0.051*42*E,11631.38477,N,3948.74550**A*END      ----2018-5-10
	double IntE = atof(strE_value);
	double IntN = atof(strN_value);
	IntE = IntE*100;
	IntN = IntN*100;
	
	CString CStrE;
	CString CStrN;
	CStrE.Format("%.5lf",IntE);
	CStrN.Format("%.5lf",IntN);

	m_strSendMsg.Format("SC012*S*066*GET*%s*21*15**26*0.051*42*E,%s,N,%s**A*END", GlCarNum.Trim(), CStrE, CStrN);
	if (!m_strSendMsg.IsEmpty()){
		int i = send(m_Socket,m_strSendMsg.GetBuffer(0),m_strSendMsg.GetLength(),0);
		
		ChangeCoordinate(strE_value, strN_value, GlCarNum);		//add 2017-09-14  to show map
		DisplaySend(m_strSendMsg);
		m_strSendMsg.ReleaseBuffer();
		
		if (i == -1){			
			OutLineCount++;
			if (OutLineCount == 3){
				KillTimer(2);
				MessageBox("�豸��������쳣������֮���������ӷ�������");
				return;
			}
			else{
				MessageBox("��ʱ��������Ϣ����ʧ�ܣ�");
				return;
			}
		}
		else{
			OutLineCount=0;
		}
	}
	else{
		MessageBox("���鷢�͵�������Ϣ��");
		return;
	}
}

void CMFCSocketDlg::OnBnClickedButtonAddTrip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int iTrip;
	iTrip = atoi(m_strCarTrip);

	if(iTrip >= 0){
		iTrip++;
	
		m_strCarTrip.Format("%03d", iTrip);
		TripGl = m_strCarTrip;
	}
	else{
		MessageBox("�г���̲���ȷ��");
		return;
	}

	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsg();
	m_nCount++;
	UpdateData(false);
}


void CMFCSocketDlg::OnBnClickedButtonDelTrip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	int iTrip;
	iTrip = atoi(m_strCarTrip);

	if (iTrip > 0){
		iTrip--;
		m_strCarTrip.Format("%03d", iTrip);
		TripGl = m_strCarTrip;
	}
	else{
		MessageBox("�г���̲���ȷ��");
		return;
	}
	
	//ʵʱ���ͳ�����Ϣ		modify by lkz 2017-10-20 
	SendSocketMsg();
	m_nCount++;
	UpdateData(false);
}

//ʮλʱ���
CString CMFCSocketDlg::UnixTime()
{
	/*SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	CString seconds;
	seconds.Format(_T("%.3ld"), sysTime.wMilliseconds);
	MessageBox("seconds:"+seconds);*/
	
	CString nowTime;
	time_t unixTime;
	time(&unixTime);
	nowTime.Format(_T("%d"), unixTime);
	//MessageBox("nowTime:"+nowTime);

	return nowTime;
}
