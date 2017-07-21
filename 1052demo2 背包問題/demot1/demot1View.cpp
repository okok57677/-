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

////////////////////////////////////////////
//1052 2nd demo:三、加分題（5 分）：背包問題///
////////////////////////////////////////////

void knapSack(string *name,int *weight,int *price,int* values,int* items,int length,int limit)
{
	int i, w;
	for (i = 0; i < length; i++)
	{
		for (w = weight[i]; w <= limit; w++)
		{
			int p = w-weight[i];
			int newValue = values[p] + price[i];
			if (newValue > values[w])
			{
				values[w] = newValue;
				items[w] = i;
			}
		}
	}
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
		int b1[1000];
		string b2[1000];
		int itemsize[1000];
		int itemvalue[1000];
		string itemname[1000];

		int n = ViewCS.GetLength();			//字串長度
		for (int i = 0; i < n; i++)			//CString to string
			a += ViewCS[i];

		size_t pos = a.find_first_of("\n");					//分割string a		//string a to int b[]
		int i = 0;
		int start = 0;
		while (pos != string::npos)
		{
			size_t newpos = a.find_first_of("\n", pos + 1);
			if (i<2)
				b1[i] = atoll(a.substr(start, pos - start).c_str());			//string轉char *(CString) -> 轉long long -> 放入int b 陣列
			else
				b2[i-2] = a.substr(start, pos - start).c_str();
			start = pos + 1;
			pos = newpos;
			i++;
		}
		b2[i-2] = a.substr(start, pos - start).c_str();				//放最後一個元素進b[]

		for (int j = 0; j <= i - 2; j++)
		{
			size_t pos = b2[j].find_first_of(" ");					//分割string a		//string a to int b[]
			int k = 0;
			int start = 0;
			while (pos != string::npos)
			{
				size_t newpos = b2[j].find_first_of(" ", pos + 1);
				if (k == 0)
					itemsize[k + j] = atoll(b2[j].substr(start, pos - start).c_str());			
				else if (k == 1)
					itemvalue[k - 1 + j] = atoll(b2[j].substr(start, pos - start).c_str());
			//	else if (k == 2)
			//		itemname[k - 2+j] = a.substr(start, pos - start).c_str();
				start = pos + 1;
				pos = newpos;
				k++;
			}
			itemname[k - 2 + j] = b2[j].substr(start, pos - start).c_str();
		}

		int items[1000] = { 0 };
		int values[1000] = { 0 };
		knapSack(itemname, itemsize, itemvalue, values, items, b1[1], b1[0]);

		CString op, opnum;
		string tmpS;
		tmpS = to_string(values[b1[0]]);
		opnum = tmpS.c_str();		//string to CString
		aDC.DrawText(opnum, CRect(0, 16 , 1000, 1000), 0);


	}
		
		
	
}
