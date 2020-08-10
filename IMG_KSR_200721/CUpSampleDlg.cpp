// CUpSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "IMG_KSR_200721.h"
#include "CUpSampleDlg.h"
#include "afxdialogex.h"


// CUpSampleDlg 대화 상자

IMPLEMENT_DYNAMIC(CUpSampleDlg, CDialog)

CUpSampleDlg::CUpSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
	, m_UpSampleRate(0)
{

}

CUpSampleDlg::~CUpSampleDlg()
{
}

void CUpSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UpSampleRate);
}


BEGIN_MESSAGE_MAP(CUpSampleDlg, CDialog)
END_MESSAGE_MAP()


// CUpSampleDlg 메시지 처리기

void OnQuantization();
void OnUpSampling();
int m_Re_size;
int m_Re_height;
int m_Re_width;

void OnDownSampling();
int m_width;
int m_height;
int m_size;
unsigned char* m_OutputImage;


void CUpSampleDlg::OnUpSampling()
{
	// TODO: 여기에 구현 코드 추가.
}
