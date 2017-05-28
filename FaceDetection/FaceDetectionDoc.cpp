// FaceDetectionDoc.cpp : implementation of the CFaceDetectionDoc class
//

#include "stdafx.h"
#include "FaceDetection.h"

#include "FaceDetectionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//人脸的训练数据
//const char* cascade_name ="haarcascade_frontalface_alt.xml";
/////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc

IMPLEMENT_DYNCREATE(CFaceDetectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CFaceDetectionDoc, CDocument)
	//{{AFX_MSG_MAP(CFaceDetectionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc construction/destruction

CFaceDetectionDoc::CFaceDetectionDoc()
{
	// TODO: add one-time construction code here

	src = NULL; 
	m_Display = -1;     // 初始为-1
	m_filepath="";

}

CFaceDetectionDoc::~CFaceDetectionDoc()
{

}

BOOL CFaceDetectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)


	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc serialization

void CFaceDetectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc diagnostics

#ifdef _DEBUG
void CFaceDetectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFaceDetectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceDetectionDoc commands

BOOL CFaceDetectionDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here
	m_filepath = lpszPathName; 

	/*	选择一副临时图像	*/
	IplImage* pTempImg=NULL;
	pTempImg = cvLoadImage(lpszPathName,-1);      
	if (!pTempImg) 
	{
		AfxMessageBox("Load Image Error!");
		return FALSE;
	}
                      
	/*  图像保存在Doc类成员  */
	if (src) 	
		cvReleaseImage(&src);

	src=cvCreateImage(cvGetSize(pTempImg),pTempImg->depth,pTempImg->nChannels);	
	cvCopy(pTempImg,src);	// 复制图像
	cvReleaseImage(&pTempImg);	// 释放临时图像

//	pImg=cvCloneImage(pTempImg);    //可代替上面三行 (但易造成内存泄漏，推荐用cvCopy)

	m_Display = 0;			// 读取到图像后为0

	return TRUE;
}
