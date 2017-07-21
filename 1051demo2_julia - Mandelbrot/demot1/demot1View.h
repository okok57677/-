
// demot1View.h : interface of the Cdemot1View class
//

#pragma once


class Cdemot1View : public CView
{
protected: // create from serialization only
	Cdemot1View();
	DECLARE_DYNCREATE(Cdemot1View)

// Attributes
public:
	Cdemot1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cdemot1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDemo();
//	float ViewF1;
//	float ViewF2;
	CString ViewCS;
};

#ifndef _DEBUG  // debug version in demot1View.cpp
inline Cdemot1Doc* Cdemot1View::GetDocument() const
   { return reinterpret_cast<Cdemot1Doc*>(m_pDocument); }
#endif

