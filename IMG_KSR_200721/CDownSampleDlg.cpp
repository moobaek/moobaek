// CDownSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "IMG_KSR_200721.h"
#include "CDownSampleDlg.h"
#include "afxdialogex.h"
#include "CUpSampleDlg.h"


// CDownSampleDlg 대화 상자

IMPLEMENT_DYNAMIC(CDownSampleDlg, CDialog)

CDownSampleDlg::CDownSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_DownSampleRate(0)
	, m_EndPoint(0)
{

}

CDownSampleDlg::~CDownSampleDlg()
{
}

void CDownSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DownSampleRate);
	DDX_Text(pDX, IDC_EDIT2, m_EndPoint);
	DDV_MinMaxInt(pDX, m_EndPoint, 0, 255);
}


BEGIN_MESSAGE_MAP(CDownSampleDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CDownSampleDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CDownSampleDlg 메시지 처리기


void CDownSampleDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
