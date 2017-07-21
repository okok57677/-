///////////////
//demo2_julia//
///////////////

// demot1View.cpp : implementation of the Cdemot1View class
//

#include "stdafx.h"
#include "iostream"
#include <sstream>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "demot1.h"
#endif

#include "demot1Doc.h"
#include "demot1View.h"

#include <cstring>
#include <string>
#include <vector>

#include <stdlib.h> 
#include <cstdlib>
using namespace std;

#include "Test1.h"
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
:  ViewCS(_T(""))
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

//////////////
//quick sort//
//////////////
/*TESTING DATA
123,241,42,2,321,215,531,421
5,51,2,532,1,85,7,89,31,2,42,41,6,4,19
5,51,2,532,1,85,2999999999
*/
void quicksort(long long *data, int left, int right, int len, Cdemot1View*const that, int *t)
{
	CClientDC aDC(that);
	long long v, tmp;
	int i, j;
	if (right > left)
	{
		v = data[right];
		i = left-1;
		j = right;
		do
		{
			do
				i++;
			while (data[i] < v);

			do
				j--;
			while ((data[j] > v) && (j > left));
			
			tmp = data[i];		//EXCHANGE
			data[i] = data[j];
			data[j] = tmp;


		
		} while (i < j);

		data[j] = data[i];
		data[i] = data[right];
		data[right] = tmp;
		
		CString op, opnum;
		string tmpS;
		op = _T("");
		for (int k = 0; k < len; k++)
		{
			tmpS = to_string(data[k]);
			opnum = tmpS.c_str();		//string to CString
			op = op + opnum;
//			if (k != len - 1)			//因為OUTPUT畫圖處已指定每行位置,不用處理換行
				op += ' ';
//			else if (k == i)
//				op += '\n';
		}
		aDC.DrawText(op, CRect(0, 16*(*t), 1000, 1000), 0);
		(*t)++;


		quicksort(data, left, i - 1, len, that, t);
		quicksort(data, i+1, right, len, that, t);


		}

	return ;

}

void Cdemot1View::OnDemo()
{
	// TODO: Add your command handler code here
	CClientDC aDC(this);
	CTest1 aDlg;
	int line=0;
	if (aDlg.DoModal() == IDOK)
	{
		//ViewINT = aDlg.UpdateDialogControls;
		ViewCS = aDlg.DialogCS;
		string a;
		long long b[1000];

		int n = ViewCS.GetLength();			//字串長度
		for (int i = 0; i < n; i++)			//CString to string
			a += ViewCS[i];

		size_t pos = a.find_first_of(",");					//用","分割string a		//處理字串中逗號 to int b[]
		int i = 0;
		int start = 0;
		while (pos != string::npos)
		{
			size_t newpos = a.find_first_of(",", pos + 1);
			b[i] = atoll(a.substr(start, pos - start).c_str());			//提取已分割字串 -> string轉char *(CString) -> 轉long long -> 放入long long b 陣列
			start = pos + 1;
			pos = newpos;
			i++;
		}
		b[i] = atoll(a.substr(start, pos - start).c_str());				//放最後一個元素進b[]

		quicksort(b, 0, i, i+1, this, (&line));
		
		CString op, opnum;
		for (int k = 0; k < i + 1; k++) 
		{
			string tmpS;
			tmpS = to_string(b[k]);
			opnum = tmpS.c_str();		//string to CString
			op = op + opnum;
//			if (k != i + 1 - 1)			//因為OUTPUT畫圖處已指定每行位置,不用處理換行
				op += ' ';
//			else if (k == i )
//				op += '\n';
		}
		aDC.DrawText(op, CRect(0, 16*(line), 1000, 1000), 0);


	}
		
		
	
}
