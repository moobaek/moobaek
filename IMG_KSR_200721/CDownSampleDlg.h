#pragma once


// CDownSampleDlg 대화 상자

class CDownSampleDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownSampleDlg)

public:
	CDownSampleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDownSampleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_DownSampleRate;
	afx_msg void OnEnChangeEdit1();
	int m_EndPoint;
};
