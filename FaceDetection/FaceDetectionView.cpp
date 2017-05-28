// FaceDetectionView.cpp : implementation of the CFaceDetectionView class
//
//#pragma comment(lib, "openGL32.lib");
//#pragma comment(lib, "glu32.lib");
//#pragma comment(lib, "glaux.lib");

//#include "cv.h"
//#include "highgui.h"


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
	ON_COMMAND(ID_FaceDetected, OnFaceDetected)
	ON_COMMAND(ID_openpicture, Onopenpicture)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()





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
	

}


// CModificationView message handlers
int  CFaceDetectionView::imageType(IplImage* pImg) 
{
	int	 i,j,k,bpl,n,pg[256];
	BYTE *buf;
	
	k=pImg->nChannels;
	if (k==1) 
	{                         
        for (i=0;i<256;i++) pg[i]=0;
			buf=(BYTE*)pImg->imageData;
		bpl=pImg->widthStep;
        for (i=0;i<pImg->height;i++) 
		{
			for (j=0;j<pImg->width;j++) 
				pg[buf[j]]++;	
			buf+=bpl;
		}
        for (i=0,n=0;i<256;i++) 
		{
			if (pg[i]) n++;
		}
        if (n==2) k=-1;                     
    }
	return(k);
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
//������ѵ������
const char* cascade_name ="haarcascade_frontalface_alt.xml";
///////////////////////////////////////////////


void CFaceDetectionView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
}

void CFaceDetectionView::OnFaceDetected() 
{
	// �������	
}

void CFaceDetectionView::Onopenpicture() 
{
	//������ѵ������	//Ҳ���԰�����ļ�������Ĺ����ļ�����Ȼ����д·����
	cascade_name= "haarcascade_frontalface_alt2.xml"; 

//	cascade_name= "haarcascade_frontalface_alt_tree.xml"; 
//	cascade_name= "haarcascade_frontalface_default.xml"; 
	 

    CString fileName;
	CFileDialog OpenDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR,
		"JPG file format (*.jpg)|*.jpg|ͼ���ļ���ʽ(*.bmp)|*.bmp|",NULL);
	if(OpenDlg.DoModal()!=IDOK)
		return;
	fileName=OpenDlg.GetPathName();
	std::string tempName=(LPCSTR)(fileName);
	const char* tmp=tempName.c_str();
    if((src=cvLoadImage(tmp,CV_LOAD_IMAGE_ANYCOLOR))==0)
		return;

	//��������������õķ�����
	cascade=(CvHaarClassifierCascade*)cvLoad(cascade_name,0,0,0);
//	cvShowImage("�������",img);
	if(cascade)
	{
		storage=cvCreateMemStorage(0);
		cvNamedWindow("�������",CV_WINDOW_AUTOSIZE);
		if(src)
		detect_and_draw(src);
		cvReleaseImage(&src);
		cvReleaseMemStorage(&storage);

	}
	else
	{
		AfxMessageBox("�޷����ط���������ȷ�Ϻ�����");
		//cvReleaseCvHaarClassifierCascade(&cascade);
	}	
}



void CFaceDetectionView::detect_and_draw(IplImage *img)
{
	static CvScalar color[]=
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};
	double scale=1.3;
	IplImage* gray=cvCreateImage(cvSize(img->width,img->height),8,1);
	//��ͼƬ��С���ӿ����ٶ�
    IplImage* small_img=cvCreateImage(cvSize(cvRound(img->width/scale),cvRound((img->height)/scale)),8,1);
	
	int i;
	//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	cvCvtColor(img,gray,CV_BGR2GRAY);

	//���ߴ���С��1/scale,�����Բ�ֵ
	cvResize(gray,small_img,CV_INTER_LINEAR);

	//ֱ��ͼ����
	cvEqualizeHist(small_img,small_img);
	
	cvClearMemStorage(storage);
	if(cascade)
	{
		CvSeq* face=cvHaarDetectObjects(small_img,cascade,storage,1.1,2,0,cvSize(30,30));
		for(i=0;i<(face?face->total:0);i++)
		{
			CvRect* r=(CvRect*)cvGetSeqElem(face,i);
			CvPoint center;
			int radius;
			//��ԭ��ԭ���Ĵ�С
			center.x=cvRound((r->x+r->width*0.5)*scale);
			center.y=cvRound((r->y+r->height*0.5)*scale);
			radius=cvRound((r->height+r->width)*0.25*scale);
			cvCircle(img,center,radius,color[i%8],3,8,0);

		}
	}
	cvShowImage("�������",img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);


}

void CFaceDetectionView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}
