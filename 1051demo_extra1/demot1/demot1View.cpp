
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
	
	CPen penRED(PS_SOLID, 20, RGB(255, 0, 0));
	CPen penBLACK(PS_SOLID, 1, RGB(0, 0, 0));
	CPen penYELLOW(PS_SOLID, 20, RGB(255, 255, 0));
	CPen penGREEN(PS_SOLID, 20, RGB(0, 255, 0));
	CPen * oldPen = pDC->SelectObject(&penRED);

	CBrush REDbrush(RGB(255, 0, 0));
	CBrush WHITEbrush(RGB(255, 255, 255));
	CBrush YELLOWbrush(RGB(255, 255, 0));
	CBrush GREENbrush(RGB(0, 255, 0));
	CBrush BLACKbrush(RGB(0, 0, 0));
	
	CBrush * oldBrush = pDC->SelectObject(&REDbrush);
	CPoint pts[3];
	pts[0].x = 280;
	pts[0].y = 40;
	pts[1].x = 10;
	pts[1].y = 510;
	pts[2].x = 540;
	pts[2].y = 510;
	pDC->Polygon(pts, 3);

	oldBrush = pDC->SelectObject(&WHITEbrush);
	pts[0].x = 280;
	pts[0].y = 80;
	pts[1].x = 50;
	pts[1].y = 490;
	pts[2].x = 505;
	pts[2].y = 490;
	pDC->Polygon(pts, 3);

	oldPen = pDC->SelectObject(&penBLACK);
	oldBrush = pDC->SelectObject(&BLACKbrush);
	pDC->Rectangle(245, 185, 315, 470);

	oldPen = pDC->SelectObject(&penRED);
	oldBrush = pDC->SelectObject(&REDbrush);
	pDC->Ellipse(260, 220, 300, 260);
	
	oldPen = pDC->SelectObject(&penYELLOW);
	oldBrush = pDC->SelectObject(&YELLOWbrush);
	pDC->Ellipse(260, 310, 300, 350);

	oldPen = pDC->SelectObject(&penGREEN);
	oldBrush = pDC->SelectObject(&GREENbrush);
	pDC->Ellipse(260, 400, 300, 440);
	// TODO: add draw code for native data here
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
