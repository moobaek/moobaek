#pragma once


// CSumConstantSampleDig 대화 상자

class CSumConstantSampleDig : public CDialog
{
	DECLARE_DYNAMIC(CSumConstantSampleDig)

public:
	CSumConstantSampleDig(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSumConstantSampleDig();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
