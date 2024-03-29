
// MyAppDlg.h : 헤더 파일
//

#pragma once


// CMyAppDlg 대화 상자
class CMyAppDlg : public CDialogEx
{
// 생성입니다.
public:
	CMyAppDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MYAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL m_bConnected;
	HANDLE m_hComm;
	afx_msg void OnBnClickedBtnCommConfig();
	afx_msg void OnBnClickedBtnCommOpenClose();
	afx_msg void OnClose();
	void Send(UINT8 f, UINT8 a, UINT8 h, UINT8 l);
	afx_msg void OnBnClickedButtonSs();
	afx_msg LRESULT ADV1Access(WPARAM wParam, LPARAM lParam);
	void ledon(int a);
	void Fndon(int v);
	void PiezoTone();
};
