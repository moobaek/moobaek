
// IMG_KSR_200721View.cpp: CIMGKSR200721View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "IMG_KSR_200721.h"
#endif

#include "IMG_KSR_200721Doc.h"
#include "IMG_KSR_200721View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIMGKSR200721View

IMPLEMENT_DYNCREATE(CIMGKSR200721View, CView)

BEGIN_MESSAGE_MAP(CIMGKSR200721View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIMGKSR200721View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLE, &CIMGKSR200721View::OnDownSample)
	ON_COMMAND(ID_UP_SAMPLING, &CIMGKSR200721View::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CIMGKSR200721View::OnQuantization)
	ON_COMMAND(ID_IMAGEPROCESSING_DOWNSAMPLE, &CIMGKSR200721View::OnImageprocessingDownsample)
	ON_COMMAND(ID_QUANTIZATION_SAMPLE, &CIMGKSR200721View::OnQuantizationSample)
	ON_COMMAND(ID_SUM_CONSTANT, &CIMGKSR200721View::OnSumConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CIMGKSR200721View::OnSubConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CIMGKSR200721View::OnMulConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CIMGKSR200721View::OnDivConstant)
	////

	ON_COMMAND(ID_AND_OPERATE, &CIMGKSR200721View::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CIMGKSR200721View::OnOrOperate)
	ON_COMMAND(ID_OPERATE, &CIMGKSR200721View::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CIMGKSR200721View::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CIMGKSR200721View::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CIMGKSR200721View::OnBinarization)
	ON_COMMAND(ID_HISTO_STRETCH, &CIMGKSR200721View::OnHistoStretch)
	ON_COMMAND(ID_STRESS_TRANSFORM, &CIMGKSR200721View::OnStressTransform)
	
	//
	
	ON_COMMAND(ID_END_IN_SEARCH, &CIMGKSR200721View::OnEndInSearch)
	ON_COMMAND(ID_HISTOGRAM, &CIMGKSR200721View::OnHistogram)
	ON_COMMAND(ID_HISTO_EQUAL, &CIMGKSR200721View::OnHistoEqual)
	ON_COMMAND(ID_HISTO_SPEC, &CIMGKSR200721View::OnHistoSpec)
	ON_COMMAND(ID_EMBOSSING, &CIMGKSR200721View::OnEmbossing)
	ON_COMMAND(ID_BLURR, &CIMGKSR200721View::OnBlurr)
	ON_COMMAND(ID_GUASSIAN_FILTER, & CIMGKSR200721View::OnGaussianFilter)
	ON_COMMAND(ID_SHARPENING, & CIMGKSR200721View::OnSharpening)
	ON_COMMAND(ID_HPF_SHARP, & CIMGKSR200721View:: OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CIMGKSR200721View:: OnLpfSharp)
	ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CIMGKSR200721View:: OnDiffOperatorHor)
	ON_COMMAND(ID_HOMOGEN_OPERATOR, &CIMGKSR200721View:: OnHomogenOperator)
	ON_COMMAND(ID_LAPLACIAN, &CIMGKSR200721View:: OnLaplacian)
	ON_COMMAND(ID_NEAREST, &CIMGKSR200721View:: OnNearest)
	ON_COMMAND(ID_BILINEAR, &CIMGKSR200721View::OnBilinear)
	ON_COMMAND(ID_MEDIAN_SUB, &CIMGKSR200721View::OnMedianSub)
	ON_COMMAND(ID_MEAN_SUB, &CIMGKSR200721View:: OnMeanSub)
	ON_COMMAND(ID_TRANSLATION, &CIMGKSR200721View::OnTranslation)
	ON_COMMAND(ID_MIRROR_HOR, &CIMGKSR200721View:: OnMirrorHor)
	ON_COMMAND(ID_MIRROR_VER, &CIMGKSR200721View:: OnMirrorVer)
	ON_COMMAND(ID_ROTATION, &CIMGKSR200721View:: OnRotation)
END_MESSAGE_MAP()

// CIMGKSR200721View 생성/소멸

CIMGKSR200721View::CIMGKSR200721View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CIMGKSR200721View::~CIMGKSR200721View()
{
}

BOOL CIMGKSR200721View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CIMGKSR200721View 그리기

void CIMGKSR200721View::OnDraw(CDC* pDC)
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	unsigned char R, G, B;
	// 입력 영상 출력
	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = pDoc->m_InputImage[i * pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}
	// 축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j < pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}

}



// CIMGKSR200721View 인쇄


void CIMGKSR200721View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIMGKSR200721View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CIMGKSR200721View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CIMGKSR200721View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CIMGKSR200721View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIMGKSR200721View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIMGKSR200721View 진단

#ifdef _DEBUG
void CIMGKSR200721View::AssertValid() const
{
	CView::AssertValid();
}

void CIMGKSR200721View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIMGKSR200721Doc* CIMGKSR200721View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIMGKSR200721Doc)));
	return (CIMGKSR200721Doc*)m_pDocument;
}
#endif //_DEBUG


// CIMGKSR200721View 메시지 처리기


void CIMGKSR200721View::OnDownSample()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDownSampling(); // Doc 클래스에 OnDownSampling 함수 호출
	Invalidate(TRUE); // 화면 갱신

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxMessageBox(L"Not Support Image Size"); // 해당 크기가 없는 경우
}


void CIMGKSR200721View::OnUpSampling()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출
	Invalidate(TRUE); // 화면 갱신

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CIMGKSR200721View::OnQuantization()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnQuantization1(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CIMGKSR200721View::OnImageprocessingDownsample()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
		// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnUpSampling(); // Doc 클래스에 OnUpSampling 함수 호출
	Invalidate(TRUE); // 화면 갱신
}


void CIMGKSR200721View::OnQuantizationSample()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnQuantization1(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


//void CIMGKSR200721View::OnSumConstant()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}




void CIMGKSR200721View::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnSumConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnSubConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	
}


void CIMGKSR200721View::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnMulConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 구현 코드 추가.// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 구현 코드 추가.// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CIMGKSR200721Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant(); // Doc 클래스에 OnQuantization 함수 호출
	Invalidate(TRUE); // 화면 갱신
	// TODO: 여기에 구현 코드 추가.// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnNegaTransform()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnGammaCorrection()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGammaCorrection();
	Invalidate(TRUE);// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnBinarization()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();
	Invalidate(TRUE);
	// TODO: 여기에 구현 코드 추가.
}



void CIMGKSR200721View::OnStressTransform()
{
	// TODO: Add your command handler code here
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnStressTransform();
	Invalidate(TRUE);

}


void CIMGKSR200721View::OnHistoStretch()
{

	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();
	Invalidate(TRUE);// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnEndInSearch()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
	// TODO: 여기에 구현 코드 추가.
}




void CIMGKSR200721View::OnHistogram()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();
	Invalidate(TRUE);
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnHistoEqual()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoEqual();
	Invalidate(TRUE);
	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnHistoSpec()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//pDoc->OnHistoSpec
	pDoc->OnHistoSpec();
		Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnEmbossing()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmbossing();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnBlurr()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBlurr();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnGaussianFilter()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGaussianFilter();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnSharpening()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSharpening();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnHpfSharp()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnLpfSharp()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	Invalidate(TRUE);

	// TODO: 여기에 구현 코드 추가.
}


void CIMGKSR200721View::OnDiffOperatorHor()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnHomogenOperator()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHomogenOperator();
	Invalidate(TRUE);

}


void CIMGKSR200721View::OnLaplacian()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian();
	Invalidate(TRUE);
}


void CIMGKSR200721View::OnNearest()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNearest();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnBilinear()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBilinear();
	Invalidate(TRUE);
}

void CIMGKSR200721View::OnMedianSub()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMedianSub();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnMeanSub()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMeanSub();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnTranslation()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnTranslation();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnMirrorHor()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorHor();
	Invalidate(TRUE);
}


void CIMGKSR200721View::OnMirrorVer()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnMirrorVer();
	Invalidate(TRUE);
}



void CIMGKSR200721View::OnRotation()
{
	CIMGKSR200721Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnRotation();
	Invalidate(TRUE);
}

