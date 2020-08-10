
// IMG_KSR_200721Doc.h: CIMGKSR200721Doc 클래스의 인터페이스
//


#include "CDownSampleDlg.h" 
#include "CUpSampleDlg.h"
#pragma once


class CIMGKSR200721Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CIMGKSR200721Doc() noexcept;
	DECLARE_DYNCREATE(CIMGKSR200721Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CIMGKSR200721Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// input Buffer


	
	
	
	int m_width=0;
	int m_height=0;
	int m_size=0;
	int width=0;
	int height=0;

	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	// OnDownSampling
public:

	void OnDownSampling();
	int m_Re_width=0;
	int m_Re_height=0;
	int m_Re_size=0;
	
	unsigned char* m_OutputImage;

	double** m_tempImage;

	unsigned char* m_InputImage;

	
	afx_msg void OnUpSampling();
	void OnQuantization1();
	//void OnConstant();
	void OnSumConstant();
	//void OnSumConstant();
	void OnSubConstant();
	void OnMulConstant();
	void OnDivConstant();
	void OnAndOperate();
	void OnOrOperate();
	void OnXorOperate();
	void OnNegaTransform();
	void OnGammaCorrection();
	void OnBinarization();
	void OnStressTransform();
	void OnHistoStretch();
	void OnEndInSearch();
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];
	void OnHistogram();
	void OnHistoEqual();
	void OnHistoSpec();
	void OnEmbossing();
	double** OnMaskProcess(unsigned char* Target, double Mask[3][3]);
	double** OnScale(double** Target, int height, int width);
	double** Image2DMem(int,int);
	
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpening();
	void OnHpfSharp();
	void OnLpfSharp();
	void OnDiffOperatorHor();
	void OnHomogenOperator();
	double DoubleABS(double X);
	void OnLaplacian();
	void OnNearest();
	void OnBilinear();
	void OnMedianSub();
	void OnBubleSort(double* A, int MAX);
	void OnSwap(double* a, double* b);
	void OnMeanSub();
	void OnTranslation();
	void OnMirrorHor();
	void OnMirrorVer();
	void OnRotation();
};
