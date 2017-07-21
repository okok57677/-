
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
	if (aDlg.DoModal() == IDOK)
	{
		ViewSTR = aDlg.DialogSTR;
		CString op,opnum;
		string a;
		string b[20];

		int n = ViewSTR.GetLength();						//字串長度
		for (int i = 0; i<n; i++)							//CString to string
			a += ViewSTR[i];

		size_t pos = a.find_first_of(" ");					//處理字串中空格 to string b
		int i = 0;
		int start = 0;
		while (pos != string::npos)
		{
			size_t newpos = a.find_first_of(" ", pos + 1);
			b[i] = a.substr(start, pos - start);			//提取字串to string b 陣列
			start = pos + 1;
			pos = newpos;
			i++;
		}
		b[i] = a.substr(start, pos - start);				//把最後的元素放進陣列

		n = i+1;				//重設字串長度

		for (int i = 0; i < n; i++)			//把輸入值寫進op(輸出值)
		{
			opnum = b[i].c_str();
			op = op + opnum + ' ';
		}
		op += '\r';				// 指標移到最左,換行
		op += '\n';

		string strtemp;
		do
		{
			strtemp = b[0];
			for (int j = 1; j<n; j++)
			{
				if (atoi(b[j-1].c_str()) > atoi(b[j].c_str()) )			//把String b[] 字元轉INT並比較整數大小
				{
					strtemp = b[j];			//EXCHANGE
					b[j] = b[j-1];
					b[j-1] = strtemp;
				
					for (int i = 0; i < n; i++)								//若有進行交換(if b),把值寫進op(輸出值)
					{
						opnum = b[i].c_str();		//string to CString
						op = op + opnum + ' ';
					}
					op += '\r';				// 指標移到最左,換行
					op += '\n';	

				}
				
			}
		} while (strtemp != b[0]);;


		aDC.DrawText(op, CRect(0, 0, 1000, 1000), 0);

	}
}
