/* 본프로그램 작성은

OS : Windows 10 Pro 1909(18363.535)
IDE : Visual Studio 2019 16.4.1

에서 작성됨을 알려드립니다.
*/

// MyAppDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "afxdialogex.h"
#include "MyBusDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMyAppDlg 대화 상자



CMyAppDlg::CMyAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyAppDlg::IDD, pParent)
	, m_bConnected(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_COMM_CONFIG, &CMyAppDlg::OnBnClickedBtnCommConfig)
	ON_BN_CLICKED(IDC_BTN_COMM_OPEN_CLOSE, &CMyAppDlg::OnBnClickedBtnCommOpenClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SS, &CMyAppDlg::OnBnClickedButtonSs)
	ON_MESSAGE(WM_MYBUS_ADC_VALUE, & CMyAppDlg::ADV1Access)
END_MESSAGE_MAP()


// CMyAppDlg 메시지 처리기

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_bConnected = FALSE;
	m_hComm = NULL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMyAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CallCommSetDlg();
}


void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
  // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다
  CString str;			// 통신연결 상태표시용 문자열
  char cParity;			// 패리티 표시용 문자변수
  char* cStopBits;	// Stop bit 표시용 문자열 포인터
  CommConfigData *pCommCfg = new CommConfigData;

// 통신포트 연결여부 확인
  if(!m_bConnected){
    GetCommCfgData(pCommCfg);
    pCommCfg->hOwner = m_hWnd;
    if((m_hComm=CommOpen(*pCommCfg)) != NULL){

       m_bConnected = TRUE;

       if(pCommCfg->Parity == EVENPARITY) cParity = 'E';
       else if(pCommCfg->Parity == ODDPARITY) cParity = 'O';
       else cParity = 'N';

       if(pCommCfg->StopBits == TWOSTOPBITS) cStopBits = "2";
       else if(pCommCfg->StopBits == ONE5STOPBITS) cStopBits = "1.5";
       else cStopBits = "1";

       str.Format(_T("COM%d,%d,%c,%d,%s"), pCommCfg->PortNum,
          pCommCfg->BaudRate,cParity,pCommCfg->ByteSize,cStopBits);

       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("포트닫기"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);
    } // if
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }// if
  // 통신포트연결해제
 else{
     CommClose();
     m_bConnected = FALSE;
     str.Format(_T(" Closed "));
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("포트열기"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);
  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_bConnected){
		CommClose();
	}

	CDialogEx::OnClose();
}



void CMyAppDlg::Send(UINT8 f, UINT8 a, UINT8 h, UINT8 l)
{
	// TODO: 여기에 구현 코드 추가
	_MyBusFrame Q;
	Q.ui8Func = f;         // LED 레지스터 제어 명령
	Q.ui8Addr = a;         // 레지스터 A
	Q.ui8DataH = h;
	Q.ui8DataL = l;
	MyBusSendFrame(&Q);
}


void CMyAppDlg::OnBnClickedButtonSs()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int toggle = 1;
	if (toggle) {
		Send(0x06, 0x48, 0x00, 0x02); //ADC1(조도센서)이벤트 활성화
		Send(0x06, 0x49, 0x00, 0x0a); // 반환시간 10ms
		toggle = 0;
		GetDlgItem(IDC_BUTTON_SS)->SetWindowTextW(_T("정지"));
	}
	else
	{
		Send(0x06, 0x48, 0x00, 0x00); // 조도센서 비활성화
		Send(0x06, 0x49, 0x00, 0x00); // 반환종료
		Send(0x06, 0x70, 0x00, 0x00); // 피에조 끔
		ledon(0); //LED끔
		Fndon(0); //FND끔
		toggle = 1;
		GetDlgItem(IDC_EDIT_COM)->SetWindowTextW(_T("")); //숫자 초기화
		GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_BUTTON_SS)->SetWindowTextW(_T("시작"));
	}
}


afx_msg LRESULT CMyAppDlg::ADV1Access(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 구현 코드 추가.

	CString str;
	int Temp;
	UINT8 ui8Func = (UINT8)(lParam >> 24) & 0xff;
	UINT8 ui8Addr = (UINT8)(lParam >> 16) & 0xff;
	UINT16 ui16Value = (UINT16)lParam & 0xffff;

	if (ui8Func == 33) {  // FC_ACE
		switch (ui8Addr) {
		case 0x41: // ADC1==조도
			Temp = (int)ui16Value;
			str.Format(_T("%d"), Temp);
			GetDlgItem(IDC_EDIT_COM)->SetWindowText(str);
			if (Temp >= 1000) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("매우밝음"));
				ledon(0);
			}
			else if(Temp >= 750) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("밝음"));
				ledon(3);
			}
			else if (Temp >= 400) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("어두움"));
				ledon(2);
			}
			else
			{
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("매우 어두움"));
				ledon(1);
				Fndon(4);
				PiezoTone(); //넣을시 FND가 동작을 안함..
			}
			break;
		default:
			break;
		}
	}
	return afx_msg LRESULT();
}


//LED 켤고 끌수있는 코드
void CMyAppDlg::ledon(int a)
{
	// TODO: 여기에 구현 코드 추가.
	switch (a)
	{
	case 1: 
		Send(0x05, 0x00, 0x07, 0xff);
		Send(0x05, 0x00, 0x06, 0xff);
		Send(0x05, 0x00, 0x05, 0xff);
		Send(0x05, 0x00, 0x04, 0xff);
		Send(0x05, 0x00, 0x03, 0xff);
		Send(0x05, 0x00, 0x02, 0xff);
		Send(0x05, 0x00, 0x01, 0xff);
		Send(0x05, 0x00, 0x00, 0xff);
		break;
	case 2:
		Send(0x05, 0x00, 0x07, 0xff);
		Send(0x05, 0x00, 0x06, 0xff);
		Send(0x05, 0x00, 0x05, 0xff);
		Send(0x05, 0x00, 0x04, 0xff);
		Send(0x05, 0x00, 0x03, 0x00);
		Send(0x05, 0x00, 0x02, 0x00);
		Send(0x05, 0x00, 0x01, 0x00);
		Send(0x05, 0x00, 0x00, 0x00);
		break;
	case 3:
		Send(0x05, 0x00, 0x07, 0x00);
		Send(0x05, 0x00, 0x06, 0x00);
		Send(0x05, 0x00, 0x05, 0x00);
		Send(0x05, 0x00, 0x04, 0x00);
		Send(0x05, 0x00, 0x03, 0xff);
		Send(0x05, 0x00, 0x02, 0xff);
		Send(0x05, 0x00, 0x01, 0xff);
		Send(0x05, 0x00, 0x00, 0xff);
	default: // LED종료
		Send(0x05, 0x00, 0x07, 0x00);
		Send(0x05, 0x00, 0x06, 0x00);
		Send(0x05, 0x00, 0x05, 0x00);
		Send(0x05, 0x00, 0x04, 0x00);
		Send(0x05, 0x00, 0x03, 0x00);
		Send(0x05, 0x00, 0x02, 0x00);
		Send(0x05, 0x00, 0x01, 0x00);
		Send(0x05, 0x00, 0x00, 0x00);
		break;
	}
}


void CMyAppDlg::Fndon(int v)
{
	// TODO: 여기에 구현 코드 추가.
 
	switch (v)
	{
	case 4:
		Send(0x06, 0x31, 0x00, 0x00);
		Send(0x06, 0x32, 0x00, 0x38); // FND에 LOU 표시 (W = > U)
		Send(0x06, 0x33, 0x00, 0x3f);
		Send(0x06, 0x34, 0x00, 0x3e);
	default:
		Send(0x06, 0x31, 0x00, 0x00);
		Send(0x06, 0x32, 0x00, 0x00);
		Send(0x06, 0x33, 0x00, 0x00);
		Send(0x06, 0x34, 0x00, 0x00);
		break;
	}
}

void CMyAppDlg::PiezoTone()
{
	_MyBusFrame  p_Query;
	p_Query.ui8Func = FC_WOR;
	p_Query.ui8Addr = VC_PIEZO_ENABLE;
	p_Query.ui8DataH = 0;
	p_Query.ui8DataL = 1;
	MyBusSendFrame(&p_Query);

	p_Query.ui8Func = FC_WOR;
	p_Query.ui8Addr = VC_PIEZO_TONE;
	p_Query.ui8DataH = 0x53;
	p_Query.ui8DataL = 0x0e8;
	MyBusSendFrame(&p_Query);
}
