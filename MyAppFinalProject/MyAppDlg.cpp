/* �����α׷� �ۼ���

OS : Windows 10 Pro 1909(18363.535)
IDE : Visual Studio 2019 16.4.1

���� �ۼ����� �˷��帳�ϴ�.
*/

// MyAppDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MyApp.h"
#include "MyAppDlg.h"
#include "afxdialogex.h"
#include "MyBusDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMyAppDlg ��ȭ ����



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


// CMyAppDlg �޽��� ó����

BOOL CMyAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_bConnected = FALSE;
	m_hComm = NULL;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMyAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMyAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyAppDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CMyAppDlg::OnBnClickedBtnCommConfig()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CallCommSetDlg();
}


void CMyAppDlg::OnBnClickedBtnCommOpenClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
  // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�
  CString str;			// ��ſ��� ����ǥ�ÿ� ���ڿ�
  char cParity;			// �и�Ƽ ǥ�ÿ� ���ں���
  char* cStopBits;	// Stop bit ǥ�ÿ� ���ڿ� ������
  CommConfigData *pCommCfg = new CommConfigData;

// �����Ʈ ���Ῡ�� Ȯ��
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
       GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("��Ʈ�ݱ�"));
       GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(false);
    } // if
   else{
       str.Format(_T("Open Error COM%d"),pCommCfg->PortNum);
       GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
    }
  }// if
  // �����Ʈ��������
 else{
     CommClose();
     m_bConnected = FALSE;
     str.Format(_T(" Closed "));
     GetDlgItem(IDC_COMM_STATUS)->SetWindowText(str);
     GetDlgItem(IDC_BTN_COMM_OPEN_CLOSE)->SetWindowText(_T("��Ʈ����"));
     GetDlgItem(IDC_BTN_COMM_CONFIG)->EnableWindow(true);
  }
  delete pCommCfg;
}


void CMyAppDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bConnected){
		CommClose();
	}

	CDialogEx::OnClose();
}



void CMyAppDlg::Send(UINT8 f, UINT8 a, UINT8 h, UINT8 l)
{
	// TODO: ���⿡ ���� �ڵ� �߰�
	_MyBusFrame Q;
	Q.ui8Func = f;         // LED �������� ���� ���
	Q.ui8Addr = a;         // �������� A
	Q.ui8DataH = h;
	Q.ui8DataL = l;
	MyBusSendFrame(&Q);
}


void CMyAppDlg::OnBnClickedButtonSs()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int toggle = 1;
	if (toggle) {
		Send(0x06, 0x48, 0x00, 0x02); //ADC1(��������)�̺�Ʈ Ȱ��ȭ
		Send(0x06, 0x49, 0x00, 0x0a); // ��ȯ�ð� 10ms
		toggle = 0;
		GetDlgItem(IDC_BUTTON_SS)->SetWindowTextW(_T("����"));
	}
	else
	{
		Send(0x06, 0x48, 0x00, 0x00); // �������� ��Ȱ��ȭ
		Send(0x06, 0x49, 0x00, 0x00); // ��ȯ����
		Send(0x06, 0x70, 0x00, 0x00); // �ǿ��� ��
		ledon(0); //LED��
		Fndon(0); //FND��
		toggle = 1;
		GetDlgItem(IDC_EDIT_COM)->SetWindowTextW(_T("")); //���� �ʱ�ȭ
		GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T(""));
		GetDlgItem(IDC_BUTTON_SS)->SetWindowTextW(_T("����"));
	}
}


afx_msg LRESULT CMyAppDlg::ADV1Access(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.

	CString str;
	int Temp;
	UINT8 ui8Func = (UINT8)(lParam >> 24) & 0xff;
	UINT8 ui8Addr = (UINT8)(lParam >> 16) & 0xff;
	UINT16 ui16Value = (UINT16)lParam & 0xffff;

	if (ui8Func == 33) {  // FC_ACE
		switch (ui8Addr) {
		case 0x41: // ADC1==����
			Temp = (int)ui16Value;
			str.Format(_T("%d"), Temp);
			GetDlgItem(IDC_EDIT_COM)->SetWindowText(str);
			if (Temp >= 1000) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("�ſ����"));
				ledon(0);
			}
			else if(Temp >= 750) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("����"));
				ledon(3);
			}
			else if (Temp >= 400) {
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("��ο�"));
				ledon(2);
			}
			else
			{
				GetDlgItem(IDC_EDIT_SET)->SetWindowTextW(_T("�ſ� ��ο�"));
				ledon(1);
				Fndon(4);
				PiezoTone(); //������ FND�� ������ ����..
			}
			break;
		default:
			break;
		}
	}
	return afx_msg LRESULT();
}


//LED �Ӱ� �����ִ� �ڵ�
void CMyAppDlg::ledon(int a)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
	default: // LED����
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
	// TODO: ���⿡ ���� �ڵ� �߰�.
 
	switch (v)
	{
	case 4:
		Send(0x06, 0x31, 0x00, 0x00);
		Send(0x06, 0x32, 0x00, 0x38); // FND�� LOU ǥ�� (W = > U)
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
