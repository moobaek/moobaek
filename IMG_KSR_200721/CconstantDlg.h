#pragma once


// CconstantDlg 대화 상자

class CconstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CconstantDlg)

public:
	CconstantDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CconstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCostantSample();
	double m_Constant;
};
