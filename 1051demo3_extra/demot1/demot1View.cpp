
// demot1View.cpp : implementation of the Cdemot1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "demot1.h"
#endif

#include "demot1Doc.h"
#include "demot1View.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Test1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cdemot1View

IMPLEMENT_DYNCREATE(Cdemot1View, CView)

BEGIN_MESSAGE_MAP(Cdemot1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cdemot1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DEMO, &Cdemot1View::OnDemo)
END_MESSAGE_MAP()

// Cdemot1View construction/destruction

Cdemot1View::Cdemot1View()
: ViewINT(0)
{
	// TODO: add construction code here

}

Cdemot1View::~Cdemot1View()
{
}

BOOL Cdemot1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cdemot1View drawing

void Cdemot1View::OnDraw(CDC* pDC)
{
	Cdemot1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	POINT cursorPos;
	GetCursorPos(&cursorPos);
//	string s1, s2;
	
//	string x = cursorPos.x;
//	string y = cursorPos.y;

	CPen penRED(PS_SOLID, 30, RGB(255, 0, 0));
	CPen penBLACK(PS_SOLID, 10, RGB(0, 0, 0));
	CPen * oldPen = pDC->SelectObject(&penRED);

	CBrush REDbrush(RGB(255, 0, 0));
	CBrush WHITEbrush(RGB(255, 255, 255));
	CBrush YELLOWbrush(RGB(255, 255, 0));
	CBrush GREENbrush(RGB(0, 255, 0));
	CBrush BLACKbrush(RGB(0, 0, 0));
	
	oldPen = pDC->SelectObject(&penBLACK);
	pDC->MoveTo(140, 36);
	pDC->LineTo(140, 356);

	pDC->MoveTo(252, 36);//second perpendicular
	pDC->LineTo(252, 356);

	pDC->MoveTo(36, 140);//first horizon
	pDC->LineTo(356, 140);

	pDC->MoveTo(36, 252);
	pDC->LineTo(356, 252);

	pDC->MoveTo(20, 20);
	pDC->LineTo(20, 372);
	pDC->LineTo(372, 372);
	pDC->LineTo(372, 20);
	pDC->LineTo(20, 20);
//	pDC->DrawText(x, 121, 121, &penBLACK);
/*	oldPen = pDC->SelectObject(&penBLACK);
	CBrush * oldBrush = pDC->SelectObject(&BLACKbrush);
	pDC->Rectangle(140, 225, 160, 275);
	pDC->Rectangle(170, 225, 190, 275);
	pDC->Rectangle(200, 225, 370, 275);


	oldPen = pDC->SelectObject(&penRED);
	pDC->MoveTo(150, 150);
	pDC->LineTo(350, 350);
	// TODO: add draw code for native data here
*/

}

// Cdemot1View printing


void Cdemot1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cdemot1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cdemot1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cdemot1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void Cdemot1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cdemot1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cdemot1View diagnostics

#ifdef _DEBUG
void Cdemot1View::AssertValid() const
{
	CView::AssertValid();
}

void Cdemot1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cdemot1Doc* Cdemot1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cdemot1Doc)));
	return (Cdemot1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cdemot1View message handlers

void Cdemot1View::OnDemo()
{
	// TODO: Add your command handler code here
	/*CClientDC aDC(this);
	CTest1 aDlg;
	int x = 200;		//¤¤¤ß®y¼Ð
	int y = 200;
	if (aDlg.DoModal() == IDOK)
	{
		//ViewINT = aDlg.UpdateDialogControls;
		ViewINT = aDlg.DialogINT;
		int times = 2;
		CBrush abrush(RGB(0, 0, 0));

		int i = ViewINT;
		int cd = 40;
		for (int j = 0; j <= i; j++)
		{
			aDC.SelectObject(abrush);
			aDC.Rectangle(x-cd,y-cd,x+cd,y+cd);

			fractal(j, x - cd, y - cd, x + cd, y - cd, this);
			fractal(j, x - cd, y + cd, x + cd, y + cd, this);

		}

	}*/
}
