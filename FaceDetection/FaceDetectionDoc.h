// FaceDetectionDoc.h : interface of the CFaceDetectionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACEDETECTIONDOC_H__3A40EA97_4A57_4D49_9D91_D936DD28481F__INCLUDED_)
#define AFX_FACEDETECTIONDOC_H__3A40EA97_4A57_4D49_9D91_D936DD28481F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFaceDetectionDoc : public CDocument
{
protected: // create from serialization only
	CFaceDetectionDoc();
	DECLARE_DYNCREATE(CFaceDetectionDoc)

// Attributes
public:
	CFacedetectDlg(CWnd* pParent = NULL);	// standard constructor
/////////////////////////////////////////////////////////////
	CvCapture* capture;
	void detect_and_draw(IplImage* img);
	CvMemStorage* storage;
	CvHaarClassifierCascade* cascade;
	IplImage* src;

// Operations
public:

	IplImage*   pImg;           // 读入图像文件的原始位图
	int m_Display;              // 图像显示标记
	CString m_filepath;         // 图像路径

//	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);//重载打开文档虚函数

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFaceDetectionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFaceDetectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFaceDetectionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACEDETECTIONDOC_H__3A40EA97_4A57_4D49_9D91_D936DD28481F__INCLUDED_)
