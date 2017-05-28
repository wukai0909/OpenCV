// FaceDetectionView.h : interface of the CFaceDetectionView class
//
/////////////////////////////////////////////////////////////////////////////
#include "cv.h"
#include "highgui.h"


#if !defined(AFX_FACEDETECTIONVIEW_H__5D5AA329_D478_4D6F_83A0_B720A04BCA48__INCLUDED_)
#define AFX_FACEDETECTIONVIEW_H__5D5AA329_D478_4D6F_83A0_B720A04BCA48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// FaceDetectionView.h : CFaceDetectionView 类的接口

//class CFaceDetectionView : public CView 
class CFaceDetectionView : public CScrollView
{
protected: // create from serialization only
	CFaceDetectionView();
	DECLARE_DYNCREATE(CFaceDetectionView)

// Attributes
public:
	CFaceDetectionDoc* GetDocument();


	CvHaarClassifierCascade *cascade;//特征器分类
	CvMemStorage *storage;//内存存储块
	void detect_and_draw( IplImage *img );//检测和标识函数
	IplImage *src; //载入的图像


// Operations
public:

	IplImage* saveImg;      // 备份位图
	IplImage* workImg;      // 工作位图
	// workImg的信息;
	int m_nHeight, m_nWidth, m_nWidthStep, m_nChannels, m_nDepth;
	
	int m_ImageType;

public:
	int imageType(IplImage* p);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectionView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectionView)
	afx_msg void OnFileSaveAs();
	afx_msg void OnFaceDetected();
	afx_msg void Onopenpicture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FaceDetectionView.cpp
inline CFaceDetectionDoc* CFaceDetectionView::GetDocument()
   { return (CFaceDetectionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTIONVIEW_H__5D5AA329_D478_4D6F_83A0_B720A04BCA48__INCLUDED_)
