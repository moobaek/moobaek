
// IMG_KSR_200721Doc.cpp: CIMGKSR200721Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KSR_200721.h"
#include "math.h"
#include "CQuantizationDlg.h"
#include "CconstantDlg.h"
#include "CStressTransformDlg.h"

#endif

#include "IMG_KSR_200721Doc.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMGKSR200721Doc

IMPLEMENT_DYNCREATE(CIMGKSR200721Doc, CDocument)

BEGIN_MESSAGE_MAP(CIMGKSR200721Doc, CDocument)
	ON_COMMAND(ID_UP_SAMPLING, &CIMGKSR200721Doc::OnUpSampling)
END_MESSAGE_MAP()


// CIMGKSR200721Doc 생성/소멸

CIMGKSR200721Doc::CIMGKSR200721Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CIMGKSR200721Doc::~CIMGKSR200721Doc()
{
}

BOOL CIMGKSR200721Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CIMGKSR200721Doc serialization

void CIMGKSR200721Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CIMGKSR200721Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CIMGKSR200721Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CIMGKSR200721Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CIMGKSR200721Doc 진단

#ifdef _DEBUG
void CIMGKSR200721Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIMGKSR200721Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIMGKSR200721Doc 명령


BOOL CIMGKSR200721Doc::OnOpenDocument(LPCTSTR lpszPathName)


{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File; // 파일 객체 선언
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택
	// 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
	if (File.GetLength() == 256 * 256) { // RAW 파일의 크기 결정
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { // RAW 파일의 크기 결정
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) { // RAW 파일의 크기 결정
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
		return 0;
	}
	m_size = m_width * m_height; // 영상의 크기 계산
	m_InputImage = new unsigned char[m_size];
	// 입력 영상의 크기에 맞는 메모리 할당
	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255; // 초기화
	File.Read(m_InputImage, m_size); // 입력 영상 파일 읽기
	File.Close(); // 파일 닫기


	return TRUE;
}
void CIMGKSR200721Doc::OnDownSampling()
{
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		// 축소 영상의 세로 길이를 계산
		m_Re_width = m_width / dlg.m_DownSampleRate;
		// 축소 영상의 가로 길이를 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 축소 영상의 크기를 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 축소 영상을 위한 메모리 할당
		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
				// 축소 영상을 생성
			}
		}
	}
}






BOOL CIMGKSR200721Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File; // 파일 객체 선언
	CFileDialog SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);
	// raw 파일을 다른 이름으로 저장하기를 위한 대화상자 객체 선언
	if (SaveDlg.DoModal() == IDOK) {
		// DoModal 멤버 함수에서 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		// 파일 열기
		File.Write(m_InputImage, m_size); // 파일 쓰기
		File.Close(); // 파일 닫기
	}
	return CDocument::OnSaveDocument(lpszPathName);
}


void CIMGKSR200721Doc::OnUpSampling()
{
	int i, j;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK) { // DoModal 대화상자의 활성화 여부
		m_Re_height = m_height * dlg.m_UpSampleRate;
		// 확대 영상의 세로 길이 계산
		m_Re_width = m_width * dlg.m_UpSampleRate;
		// 확대 영상의 가로 길이 계산
		m_Re_size = m_Re_height * m_Re_width;
		// 확대 영상의 크기 계산
		m_OutputImage = new unsigned char[m_Re_size];
		// 확대 영상을 위한 메모리 할당
		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0; // 초기화
		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
					dlg.m_UpSampleRate * j] = m_InputImage[i * m_width + j];
			} // 재배치하여 영상 확대
		}
	}

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CIMGKSR200721Doc::OnQuantization1()
{
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)
		// 양자화 비트 수를 결정하는 대화상자의 활성화 여부
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		// 양자화 처리된 영상을 출력하기 위한 메모리 할당
		TEMP = new double[m_size];
		// 입력 영상 크기(m_size)와 동일한 메모리 할당
		LEVEL = 256; // 입력 영상의 양자화 단계(28=256)
		HIGH = 256.;
		value = (int)pow(2, dlg.m_QuanBit);
		// 양자화 단계 결정(예 : 24=16)
		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
					TEMP[i] = (double)(HIGH / value) * j; // 양자화 수행
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
			// 결과 영상 생성
		}
	}
	}

	// TODO: 여기에 구현 코드 추가.



void CIMGKSR200721Doc::OnSumConstant()
{
	CconstantDlg dlg; // 상수 값을 입력받는 대화상자
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			// 출력 값이 255보다 크면 255 출력
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
			// 상수 값과 화소 값과의 덧셈
		}
	}
	// TODO: 여기에 구현 코드 추가.
}



void CIMGKSR200721Doc::OnSubConstant()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0; // 출력 값이 255보다 크면 255를 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] - dlg.m_Constant);
			// 상수 값과 화소 값과의 뺄셈
		}
	}
	// TODO: 여기에 구현 코드 추가.
}




void CIMGKSR200721Doc::OnMulConstant()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] * dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			// 곱의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] * dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			// 곱의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
			// 상수 값과 화소 값 곱셈
		}
	}// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnDivConstant()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] / dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			// 나눗셈의 값이 255보다 크면 255를 출력
			else if (m_InputImage[i] / dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			// 나눗셈의 값이 0보다 작으면 0을 출력
			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
			// 상수 값과 화소 값 나눗셈
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnAndOperate()
{
	{
		CconstantDlg dlg;
		int i;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		if (dlg.DoModal() == IDOK) {
			for (i = 0; i < m_size; i++) {
				// 비트 단위 AND 연산
				if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
				{
					m_OutputImage[i] = 255;
				}
				else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
				{
					m_OutputImage[i] = 0;
				}
				else {
					m_OutputImage[i] = (m_InputImage[i]
						& (unsigned char)dlg.m_Constant);
				}
			}
		}
		// TODO: 여기에 구현 코드 추가.
	}
}


void CIMGKSR200721Doc::OnOrOperate()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 OR 연산
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i] |
					(unsigned char)dlg.m_Constant);
			}
		}
	}
}


void CIMGKSR200721Doc::OnXorOperate()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 비트 단위 XOR 연산
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255) {
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0) {
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i]
					^ (unsigned char)dlg.m_Constant);
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnNegaTransform()
{

	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i]; // 영상 반전을 수행

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnGammaCorrection()
{
	CconstantDlg dlg;
	int i;
	double temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
			// 감마 값 계산
			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnBinarization()
{
	CconstantDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255; // 임계 값보다 크면 255 출력
			else
				m_OutputImage[i] = 0; // 임계 값보다 작으면 0 출력
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnStressTransform()
{
	CStressTransformDlg dlg;
	int i;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			// 입력 값이 강조 시작 값과 강조 종료 값 사이에 위치하면 255 출력
			if (m_InputImage[i] >= dlg.m_StartPoint &&
				m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnHistoStretch()
{

	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	MIN = m_InputImage[0]; // 최소값을 찾기 위한 초기값
	MAX = m_InputImage[0]; // 최대값을 찾기 위한 초기값
	// 입력 영상의 최소값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}
	// 입력 영상의 최대값 찾기
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}
	m_OutputImage = new unsigned char[m_Re_size];
	// 히스토그램 stretch 표시, 바로 아래에 중단점 걸고 실행후 인풋 이미지의 값이 얼만데 어떤 계산하에 아웃풋 이미지가 어떤지 시뮬해봐라
	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnEndInSearch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	MIN = m_InputImage[0];
	MAX = m_InputImage[0];
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}
	m_OutputImage = new unsigned char[m_Re_size]; 
		for (i = 0; i < m_size; i++) {
			// 원본 영상의 최소값보다 작은 값은 0
			if (m_InputImage[i] <= MIN) {
				m_OutputImage[i] = 0;
			}
			// 원본 영상의 최대값보다 큰 값은 255
			else if (m_InputImage[i] >= MAX) {
				m_OutputImage[i] = 255;
			}
			else
				m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
					MIN) * HIGH / (MAX - MIN));
		}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnHistogram()
{
	// 히스토그램의 값은 0~255
// 히스토그램의 크기 값을 MAX=255로 정규화하여 출력
// 히스트그램의 크기 : 256*256 지정
	int i, j, value;
	unsigned char LOW, HIGH;
	double MAX, MIN, DIF;
	m_Re_height = 256;
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	// 정규화
	MAX = m_HIST[0];
	MIN = m_HIST[0];
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] > MAX)
			MAX = m_HIST[i];
	}
	for (i = 0; i < 256; i++) {
		if (m_HIST[i] < MIN)
			MIN = m_HIST[i];
	}
		
		DIF = MAX - MIN;
	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);
	// 정규화된 히스토그램 출력
	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];
	for (i = 0; i < m_Re_size; i++)
		m_OutputImage[i] = 255;
	// 정규화된 히스토그램의 값은 출력 배열에 검은 점(0)으로 표현
	for (i = 0; i < 256; i++) {
		for (j = 0; j < m_Scale_HIST[i]; j++) {
			m_OutputImage[m_Re_width * (m_Re_height - j - 1) + i] = 0;
		}
	}
	// 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i < m_Re_height + 5; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}
	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
		for (j = 0; j < 256; j++) {
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}
	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height * m_Re_width;
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnHistoEqual()
{
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	// 누적 히스토그램 생성
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}
	m_OutputImage = new unsigned char[m_Re_size];
	// 입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnHistoSpec()
{
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char* m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];
	unsigned char LOW, HIGH, Temp, * m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
	double DMAX, DMIN;
	top = 255;
	bottom = top - 1;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_Org_Temp = new unsigned char[m_size];
	CFile File;
	CFileDialog OpenDlg(TRUE);
	m_DTEMP = new unsigned char[m_size];
	// 원하는 히스토그램이 있는 영상을 입력받음
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetFileName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			//m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(L"Image size not matched");
			// 같은 크기의 영상을 대상으로 함
			return;
		}
	}
	LOW = 0;
	HIGH = 255;
	// 초기화
	for (i = 0; i < 256; i++) {
		m_HIST[i] = LOW;
		m_DHIST[i] = LOW;
		m_TABLE[i] = LOW;
		
	}
	// 빈도 수 조사
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];
		m_DHIST[Dvalue]++;
	}
	// 누적 히스토그램 조사
	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
		DSUM += m_DHIST[i];
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// 원본 영상의 평활화
	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// 누적 히스토그램에서 최소값과 최대값 지정
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];
	// 원하는 영상을 평활화
for(i=0 ; i<256 ; i++){
m_Sum_Of_ScHIST[i]=(unsigned char)((m_Sum_Of_DHIST[i]
-DMIN)*HIGH/(DMAX - DMIN));
}
// 룩업테이블을 이용한 명세화
for( ; ; ){
for(i=m_Sum_Of_ScHIST[bottom] ;
i <= m_Sum_Of_ScHIST [top] ; i++){
m_TABLE[i] = top;
}
top = bottom;
bottom = bottom - 1;
if(bottom < -1)
break;
}
for(i=0 ; i<m_size ; i++){
DADD = (int)m_Org_Temp[i];
m_OutputImage[i] = m_TABLE[DADD];
}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnEmbossing()
{
	int i, j;
	double EmboMask[3][3] = {{-1., 0., 0.}, {0., 0., 0.}, {0., 0., 1.}}; // 마스크 선택
	//double EmboMask[3][3] = {{0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.}};
	//double EmboMask[3][3] = {{1., 1., 1.}, {1., -8., 1.}, {1., 1., 1.}};
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char [m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
	// OnMaskProcess 함수를 호출하여 회선처리를 한다.

	for(i=0 ; i<m_Re_height ; i++){
		for(j=0 ; j<m_Re_width ; j++){
			
			/////////////////////////////////////////////////////////////
			m_tempImage[i][j] += 128;  //  회선처리 결과에 128값을 더함
			//////////////////////////////////////////////////////////////

			if(m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if(m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	} // 회선처리 결과값이 0~255 사이 값을 갖도록 한다


	// 회선처리 결과 또는 정규화 처리 결과는 2차원 배열값이므로 2차원 배열을 1차원 배열로 바꾸어 출력하도록 한다.
	for(i=0 ; i<m_Re_height ; i++){
		for(j=0 ; j<m_Re_width ; j++){
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}

double** CIMGKSR200721Doc::OnMaskProcess(unsigned char* Target, double Mask[3][3])
{
	int i, j, n, m;
	double** tempInputImage, ** tempOutputImage, S = 0.0;
	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	// 입력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	// 출력 값을 위한 메모리 할당
	// 1차원 입력 영상의 값을 2차원 배열에 할당한다.
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)Target[i * m_width + j];
		}
	}
	// 회선연산
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			} // 회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempOutputImage[i][j] = S; // 누적된 값을 출력 메모리에 저장
			S = 0.0; // 다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	return tempOutputImage; // 결과 값 반환
	// TODO: 여기에 구현 코드 추가.
	return nullptr;
}


double** CIMGKSR200721Doc::OnScale(double** Target, int height, int width)
{
	// 정규화를 위한 함수
	int i, j;
	double min, max;
	
	min = max = Target[0][0];
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (Target[i][j] <= min)
				min = Target[i][j];
		}
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (Target[i][j] >= max)
				max = Target[i][j];
		}
	}
	max = max - min;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			Target[i][j] = (Target[i][j] - min) * (255. / max);
		}
	}
	return Target;
	// TODO: 여기에 구현 코드 추가.

}


double** CIMGKSR200721Doc::Image2DMem(int height, int width)
{
	// 2차원 메모리 할당을 위한 함수
	double** temp;
	int i, j;
	temp = new double* [height];
	for (i = 0; i < height; i++) {
		temp[i] = new double[width];
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			temp[i][j] = 0.0;
		}
	} // 할당된 2차원 메모리를 초기화
	return temp;

	// TODO: 여기에 구현 코드 추가.

}


void CIMGKSR200721Doc::OnBlurr()
{
	int i, j;
	double BlurrMask[3][3] = { {1. / 9., 1. / 9., 1. / 9.},
	{1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
	// 블러링 처리
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	// 정규화
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnGaussianFilter()
{
	int i, j;
	double GaussianMask[3][3] = { {1. / 16., 1. / 8., 1. / 16.},
	{1. / 8., 1. / 4., 1. / 8.}, {1. / 16., 1. / 8., 1. / 16.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnSharpening()
{
	int i, j;
	double SharpeningMask[3][3] = {{-1., -1., -1.},
	{-1., 9., -1.}, { -1., -1., -1. }
};

m_Re_height = m_height;
m_Re_width = m_width;
m_Re_size = m_Re_height * m_Re_width;
m_OutputImage = new unsigned char[m_Re_size];
m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
//m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
for (i = 0; i < m_Re_height; i++) {
	for (j = 0; j < m_Re_width; j++) {
		if (m_tempImage[i][j] > 255.)
			m_tempImage[i][j] = 255.;
		if (m_tempImage[i][j] < 0.)
			m_tempImage[i][j] = 0.;
	}
}
for (i = 0; i < m_Re_height; i++) {
	for (j = 0; j < m_Re_width; j++) {
		m_OutputImage[i * m_Re_width + j]
			= (unsigned char)m_tempImage[i][j];
	}
}

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721Doc::OnHpfSharp()
{
	int i, j;
	double HpfSharpMask[3][3] = { {-1. / 9., -1. / 9., -1. / 9.},
	{-1. / 9., 8. / 9., -1. / 9.}, {-1. / 9., -1. / 9., -1. / 9.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CIMGKSR200721Doc::OnLpfSharp()
{
	CconstantDlg dlg; // 상수를 입력받으려고 대화상자 선언
	int i, j, alpha;
	double LpfSharpMask[3][3] = { {1. / 9., 1. / 9., 1. / 9.},
	{1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_Constant;
		// 대화상자를 이용하여 상수를 입력받는다.
	}
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (alpha * m_InputImage
				[i * m_width + j]) - (unsigned char)m_tempImage[i][j];
		}
	// TODO: 여기에 구현 코드 추가.
}
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CIMGKSR200721Doc::OnDiffOperatorHor()
{
	int i, j;
	double DiffHorMask[3][3]
		= { {0., -1., 0.}, {0., 1., 0.}, {0., 0., 0.} };
	// 수평 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}

}


void CIMGKSR200721Doc::OnHomogenOperator()
{
	int i, j, n, m;
	double max, ** tempOutputImage;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (DoubleABS(m_tempImage[i + 1][j + 1] -
						m_tempImage[i + n][j + m]) >= max)
						// 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값
						// 중에서 최대값을 찾는다.
						max = DoubleABS(m_tempImage[i + 1]
							[j + 1] - m_tempImage[i + n][j + m]);
				}
			}
			tempOutputImage[i][j] = max; // 찾은 최대값을 출력 값으로 지정
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempOutputImage[i][j];
		}
	}
}

double CIMGKSR200721Doc::DoubleABS(double X)
{ // 실수의 절대 값 연산 함수
	if (X >= 0)
		return X;
	else
		return -X;
}


void CIMGKSR200721Doc::OnLaplacian()
{
	int i, j;
	double LaplacianMask[3][3] = { {0., 1., 0.}, {1., -4., 1.}, {0., 1., 0.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, LaplacianMask);
	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CIMGKSR200721Doc::OnNearest()
{
	int i, j;
	int ZoomRate = 2; // 영상 확대 배율
	double** tempArray;
	m_Re_height = int(ZoomRate * m_height); // 확대된 영상의 높이
	m_Re_width = int(ZoomRate * m_width); // 확대된 영상의 너비
	m_Re_size = m_Re_height * m_Re_width;
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];
			// 이웃한 화소를 이용한 보간
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
}


void CIMGKSR200721Doc::OnBilinear()
{
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double ZoomRate = 2.0, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;
	m_Re_height = (int)(m_height * ZoomRate); // 확대된 영상의 높이
	m_Re_width = (int)(m_width * ZoomRate); // 확대된 영상의 너비
	m_Re_size = m_Re_height * m_Re_width;
	m_tempImage = Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;
			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);
			s_H = r_H - i_H;
			s_W = r_W - i_W;
			if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0
				|| i_W >= (m_width - 1))
			{
				point = i * m_Re_width + j;
				m_OutputImage[point] = 255;
			}
			else
			{
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W + 1];
				C3 = (double)m_tempImage[i_H + 1][i_W + 1];
				C4 = (double)m_tempImage[i_H + 1][i_W];
				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W)
					+ C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				point = i * m_Re_width + j;
				m_OutputImage[point] = newValue;
			}
		}
	}
}



void CIMGKSR200721Doc::OnMedianSub()
{
	int i, j, n, m, M = 2, index = 0; // M = 서브 샘플링 비율
	double* Mask, Value;
	Mask = new double[M * M]; // 마스크의 크기 결정
	m_Re_height = (m_height + 1) / M;
	m_Re_width = (m_width + 1) / M;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
					// 입력 영상을 블록으로 잘라 마스크 배열에 저장
				}
			}
			OnBubleSort(Mask, M * M); // 마스크에 저장된 값을 정렬
			Value = Mask[(int)(M * M / 2)]; // 정렬된 값 중 가운데 값을 선택
			m_OutputImage[index] = (unsigned char)Value;
			// 가운데 값을 출력
			index++;
		}
	}
}



void CIMGKSR200721Doc::OnBubleSort(double* A, int MAX)
{ // 데이터의 정렬을 처리하는 함수
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}



void CIMGKSR200721Doc::OnSwap(double* a, double* b)
{ // 데이터 교환 함수
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}



void CIMGKSR200721Doc::OnMeanSub()
{
	int i, j, n, m, M = 3, index = 0, k; // M = 서브 샘플링 비율
	double* Mask, Value, Sum = 0.0;
	Mask = new double[M * M];
	m_Re_height = (m_height + 1) / M;
	m_Re_width = (m_width + 1) / M;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
				}
			}
			for (k = 0; k < M * M; k++)
				Sum = Sum + Mask[k];
			// 마스크에 저장된 값을 누적
			Value = (Sum / (M * M)); // 평균을 계산
			m_OutputImage[index] = (unsigned char)Value;
			// 평균값을 출력
			index++;
			Sum = 0.0;
		}
	}
}


void CIMGKSR200721Doc::OnTranslation()
{
	int i, j;
	int h_pos = 30, w_pos = 130;
	double** tempArray;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_height - h_pos; i++) {
		for (j = 0; j < m_width - w_pos; j++) {
			tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
			// 입력 영상을 h_pos, w_pos만큼 이동
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}


void CIMGKSR200721Doc::OnMirrorHor()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i * m_width + m_width - j - 1] =
				m_InputImage[i * m_width + j];
			// 입력 영상의 배열 값을 출력 영상을 위한
			// 배열의 수평축 뒷자리부터 저장
		}
	}
}


void CIMGKSR200721Doc::OnMirrorVer()
{
	int i, j;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[(m_height - i - 1) * m_width + j]
				= m_InputImage[i * m_width + j];
			// 입력 영상의 값을 출력 영상을 위한 배열의 수직축 뒷자리부터 저장
		}
	}
}


void CIMGKSR200721Doc::OnRotation()
{
	int i, j, CenterH, CenterW, newH, newW, degree = 45;
	// degree = 회전할 각도
	double Radian, PI, ** tempArray, Value;
	PI = 3.14159265358979; // 회전각을 위한 PI 값
	Radian = (double)degree * PI / 180.0;
	m_Re_width = m_height * cos(PI / 2 - Radian) + m_width * cos(Radian);
	m_Re_height = m_height * cos(Radian) + m_width * cos(PI / 2 - Radian);
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	// degree 값을 radian으로 변경
	CenterH = m_height / 2; // 영상의 중심 좌표
	CenterW = m_width / 2; // 영상의 중심 좌표
	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			// 회전 변환 행렬을 이용하여 회전하게 될 좌표 값 계산
			newH = (int)((i - CenterH) * cos(Radian)
				- (j - CenterW) * sin(Radian) + CenterH);
			newW = (int)((i - CenterH) * sin(Radian)
				+ (j - CenterW) * sin(Radian) + CenterW);
			if (newH < 0 || newH >= m_height) {
				// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
				Value = 0;
			}
			else if (newW < 0 || newW >= m_width) {
				// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
				Value = 0;
			}
			else {
				Value = m_tempImage[newH][newW];
			}
			tempArray[i][j] = Value;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;
}

	//수정 예정
