// FaceDetectionView.cpp : implementation of the CFaceDetectionView class
//
#pragma comment(lib, "openGL32.lib");
#pragma comment(lib, "glu32.lib");
#pragma comment(lib, "glaux.lib");

#include "cv.h"
#include "highgui.h"



#include "stdafx.h"
#include "FaceDetection.h"

#include "FaceDetectionDoc.h"
#include "FaceDetectionView.h"



#include <string>





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView

IMPLEMENT_DYNCREATE(CFaceDetectionView, CView)

BEGIN_MESSAGE_MAP(CFaceDetectionView, CView)
	//{{AFX_MSG_MAP(CFaceDetectionView)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView construction/destruction
// CFaceDetectionView ����/����
const char* cascade_name ="haarcascade_frontalface_alt.xml";//������������



CFaceDetectionView::CFaceDetectionView()
{
	// TODO: add construction code here

}

CFaceDetectionView::~CFaceDetectionView()
{
}

BOOL CFaceDetectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView drawing

void CFaceDetectionView::OnDraw(CDC* pDC)
{
	CFaceDetectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	 if (pDoc->pImg != NULL)         //  �д�������ͼ��
    {
        if (pDoc->m_Display == 0)   // ����������ͼ��, δ��ʾ
        {
            // �ͷ�ԭͼ��
            if (workImg) cvReleaseImage(&workImg);
            if (saveImg) cvReleaseImage(&saveImg);

            // ���·���ռ�
            CvSize size= cvGetSize(pDoc->pImg);
            int dep = pDoc->pImg->depth;
            int chan = pDoc->pImg->nChannels;

            workImg= cvCreateImage(size,dep,chan);
            saveImg= cvCreateImage(size,dep,chan);

            // ����ͼ��
            cvCopy(pDoc->pImg,workImg);
            cvCopy(pDoc->pImg,saveImg);

            m_ImageType = imageType(workImg);   //ͼ������

            pDoc->m_Display = 1;    // ��ʾ��ǣ���1
        }
    }

    if (workImg) //  ˢ�´��ڻ���
    {
        // ͼ�������Ϣ
        m_nWidth    = workImg->width;
        m_nHeight   = workImg->height;
        m_nWidthStep= workImg->widthStep;
        m_nChannels = workImg->nChannels;
        m_nDepth    = workImg->depth;

        // ���ù����� -- ��Ҫ������ͼ����ΪScrollView������ɾ������3��
        CSize  sizeTotal;
        sizeTotal = CSize(workImg->width,workImg->height);
//        SetScrollSizes(MM_TEXT,sizeTotal); 

        // ��ʾ
        RECT rect;      // ʹ��CvvImage���ͼ�����ı�Ҫ����
        rect.top = 0;
        rect.left=0;
        rect.bottom=m_nHeight;
        rect.right=m_nWidth;

        HDC hDC = pDC->GetSafeHdc() ;   //pDC->m_hDC;this->m_hDc  // ��ȡ���������, ::GetDC(m_hWnd)Ϊȫ�ֺ���
        CvvImage image;
        image.CopyOf(workImg,workImg->nChannels);
        image.DrawToHDC(hDC, &rect);    //  image.Show(hDC,0,0,m_nWidth,m_nHeight); // ����cv��ͼ��ʽ��ԭ�������½ǡ�

        image.Destroy();
    }

}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView printing

BOOL CFaceDetectionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceDetectionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceDetectionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView diagnostics

#ifdef _DEBUG
void CFaceDetectionView::AssertValid() const
{
	CView::AssertValid();
}

void CFaceDetectionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFaceDetectionDoc* CFaceDetectionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceDetectionDoc)));
	return (CFaceDetectionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionView message handlers

//�������˵���Ӧ





void CFaceDetectionView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	  if (!workImg)
    {   
        MessageBox("Current View has no image!");
        return;
    }

    CString csBMP="BMP Files(*.BMP)|*.BMP|";
    CString csJPG="JPG Files(*.JPG)|*.JPG|";
    CString csTIF="TIF Files(*.TIF)|*.TIF|";
    CString csPNG="PNG Files(*.PNG)|*.PNG|";
    CString csDIB="DIB Files(*.DIB)|*.DIB|";
    CString csPBM="PBM Files(*.PBM)|*.PBM|";
    CString csPGM="PGM Files(*.PGM)|*.PGM|";
    CString csPPM="PPM Files(*.PPM)|*.PPM|";
    CString csSR ="SR  Files(*.SR) |*.SR|";
    CString csRAS="RAS Files(*.RAS)|*.RAS||";

    CString csFilter=csBMP+csJPG+csTIF+csPNG+csDIB
        +csPBM+csPGM+csPPM+csSR+csRAS;

    CString name[]={"","bmp","jpg","tif","png","dib",
        "pbm","pgm","ppm","sr", "ras",""};

    CString strFileName;
    CString strExtension;

    CFileDialog FileDlg(false,NULL,NULL,OFN_HIDEREADONLY,csFilter);
    //  �ļ����̶Ի���
    if (FileDlg.DoModal()==IDOK ) //  �������ļ���
    {        
        strFileName = FileDlg.m_ofn.lpstrFile;
        if (FileDlg.m_ofn.nFileExtension == 0) //  ���ļ���׺
        {  
            strExtension = name[FileDlg.m_ofn.nFilterIndex];
            strFileName = strFileName + '.' + strExtension;
            //  ���ļ���׺
        }

        cvSaveImage(strFileName,workImg);   //  ��ǰ�������  
    }
}
