
// demot1View.cpp : implementation of the Cdemot1View class
//
#include "stdafx.h"
#include "iostream"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "demot1.h"
#endif

#include "demot1Doc.h"
#include "demot1View.h"

#include "Test1.h"

#include <cstring>
#include <string>
#include <vector>
using namespace std;
#define _SCL_SECURE_NO_WARNINGS


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
, ViewSTR(_T(""))
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
	CClientDC aDC(this);
	CTest1 aDlg;
	CString op;
	//aDlg.DoModal();
	if (aDlg.DoModal() == IDOK)
	{
		//ViewINT = aDlg.UpdateDialogControls;
		ViewSTR = aDlg.DialogSTR;
		string a;
		int n = ViewSTR.GetLength();		// 字串長度
		for (int i = 0; i < n; i++)		// CString --> string
			a += ViewSTR[i];

		size_t pos = a.find_first_of(" ");		//刪除字串中空格
		while (pos != string::npos)
		{
			a.erase(pos, 1);
			pos = a.find_first_of(" ", pos + 1);
		}

		n = a.length();		//重設字串長度
		int temp;
		for (int i = 0; i<n; i++)		//加入起始值(輸入值)至op(輸出結果)
			op = op + a[i] + ' ';		//重新加入空格至輸出結果
		op += '\r';		// 指標移到最左,換行
		op += '\n';

		for (int i = 0; i<n; i++)			// 排序找出第i小的牌
		{
			int min = i;
			for (int j = i + 1; j<n; j++)		// 剩下的n-i張中,找出目前最小的
			{
				if (a[j] < a[min])
					min = j;
			}
			temp = a[min];				// exchange a[i],a[min]
			a[min] = a[i];
			a[i] = temp;

			if (a[min] != a[i])		//若有字母交換時
			{
				for (int i = 0; i<n; i++)
					op = op + a[i] + ' ';		//重新加入空格至輸出結果
				op += '\r';		// 指標移到最左,換行
				op += '\n';
			}
		}
		aDC.DrawText(op, CRect(0, 0, 500, 500), 0);
		
	}
}
