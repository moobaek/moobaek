
// IMG_KSR_200721View.h: CIMGKSR200721View 클래스의 인터페이스
//

#pragma once


class CIMGKSR200721View : public CView
{
protected: // serialization에서만 만들어집니다.
	CIMGKSR200721View() noexcept;
	DECLARE_DYNCREATE(CIMGKSR200721View)

// 특성입니다.
public:
	CIMGKSR200721Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CIMGKSR200721View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDownSample();
	afx_msg void OnUpSampling();
	afx_msg void OnQuantization();
	afx_msg void OnImageprocessingDownsample();
	afx_msg void OnQuantizationSample();
	afx_msg void OnSumConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	void OnNegaTransform();
	void OnGammaCorrection();
	void OnBinarization();
	void OnStressTransform();
	void OnHistoStretch();
	void OnEndInSearch();
	void OnHistogram();
	void OnHistoEqual();
	void OnHistoSpec();
	void OnEmbossing();
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpening();
	void OnHpfSharp();
	void OnLpfSharp();
	void OnDiffOperatorHor();
	void OnHomogenOperator();
	void OnLaplacian();
	void OnNearest();
	void OnBilinear();
	void OnMedianSub();
	void OnMeanSub();
	void OnTranslation();
	afx_msg void OnTranslation1();
	afx_msg void OnUpdateTranslation1(CCmdUI* pCmdUI);
	void OnMirrorHor();
	void OnMirrorVer();
	void OnRotation();
};

#ifndef _DEBUG  // IMG_KSR_200721View.cpp의 디버그 버전
inline CIMGKSR200721Doc* CIMGKSR200721View::GetDocument() const
   { return reinterpret_cast<CIMGKSR200721Doc*>(m_pDocument); }
#endif

