// CconstantDlg.cpp: 구현 파일
//

#include "pch.h"
#include "IMG_KSR_200721.h"
#include "CconstantDlg.h"
#include "afxdialogex.h"


// CconstantDlg 대화 상자

IMPLEMENT_DYNAMIC(CconstantDlg, CDialog)

CconstantDlg::CconstantDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG4, pParent)
	, m_Constant(0)
{

}

CconstantDlg::~CconstantDlg()
{
}

void CconstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CconstantDlg, CDialog)

END_MESSAGE_MAP()


// CconstantDlg 메시지 처리기


void CconstantDlg::OnCostantSample()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
