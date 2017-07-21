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
:  ViewSTR1(_T(""))
, ViewSTR2(_T(""))
, ViewSTR3(_T(""))
//, ViewBU1(false)
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

//////////////////
//Graph 資料結構//
/////////////////
/*
有向
點的名稱：ABCDEFG
邊的內容：AB,BC,CE,BE,BD,DA,DE,EG,EF,FG,DF
*/
//暫1=有向,0=無向

void Cdemot1View::OnDemo()
{
	// TODO: Add your command handler code here
	CClientDC aDC(this);
	CString op1,op2, opnum;
	CTest1 aDlg;
	if (aDlg.DoModal() == IDOK)
	{
		//ViewINT = aDlg.UpdateDialogControls;
		CString opp;
		string point, temA;
		string edge, temB[3600], temC[60][60];
		ViewSTR1 = aDlg.DialogSTR1;			//輸入是否向量
		ViewSTR2 = aDlg.DialogSTR2;			//輸入點
		ViewSTR3 = aDlg.DialogSTR3;			//輸入邊
//		ViewBU1 = aDlg.DialogBU1;
//		ViewBU2 = aDlg.DialogBU2;

		int nump = ViewSTR2.GetLength();		//GET ViewSTR2字符個數 = 輸入的點有多少個
		for (int i = 0; i < nump; i++)			//CString to string
			 point += ViewSTR2[i];

		int nume = ViewSTR3.GetLength();		//GET ViewSTR3字符個數
		for (int i = 0; i < nume; i++)			//CString to string
			edge += ViewSTR3[i];

		size_t pos = edge.find_first_of(",");					//用","分割string a		//處理字串中逗號 to int b[]
		int i = 0;
		int start = 0;
		while (pos != string::npos)
		{
			size_t newpos = edge.find_first_of(",", pos + 1);
			temB[i] = edge.substr(start, pos - start).c_str();			//提取已分割字串 -> string轉char *(CString) .c_str() -> 轉??(atoll) -> 放入temB 陣列
			start = pos + 1;
			pos = newpos;
			i++;
		}
		temB[i] = edge.substr(start, pos - start).c_str();				//放最後一個元素進b[]

		
//-----------------------------------------------------------------------------------------------------------

		int orix=10, oriy=10, nx=(nump+1)*40, ny=(nump+1)*40;		//畫框
		aDC.Rectangle(orix, orix, nx, ny);
		int chx = orix, chy = oriy;
		for (int i = 0; i < nump; i++)							//畫橫線
		{
			chy += 39;
			aDC.MoveTo(orix, chy);
			aDC.LineTo(nx, chy);
			temA = point[i];
			opp = temA.c_str();
			aDC.DrawText(opp, CRect(orix + 10, chy + 10, orix + 50, chy + 50), 0);
		}
		for (int i = 0; i < nump; i++)							//畫直線
		{
			chx += 39;
			aDC.MoveTo(chx, oriy);
			aDC.LineTo(chx, ny);
			temA = point[i];
			opp = temA.c_str();
			aDC.DrawText(opp, CRect(chx + 10, oriy + 10, chx + 50, oriy + 50), 0);
		}
//------------------------------------------------------------------------------------------

		string temp1, temp2, temp3, temp4;		//分別為:邊始,邊末,點的名稱*2
		int IIX = orix + (nump + 1) * 40 + 100, IIY = oriy;
		int II[2][60] ,IIx1,IIx2,IIy1,IIy2,midpy,midpx,M,tritopx,tritopy,tritailx,tritaily;		//坐標
		int s=0;
		
		for (int i = 0; i < nump; i++)			//畫圈&字母
		{

			temp3 = point[i];
			op1 = temp3.c_str();
			aDC.Ellipse(IIX, IIY, IIX + 30, IIY + 30);
			aDC.DrawText(op1, CRect(IIX + 10, IIY + 8, IIX + 40, IIY + 40), 0);
			II[0][i] = IIX + 15;
			II[1][i] = IIY + 15;

			if (!((i + 3) % 3))
			{
				IIX += 90;
				IIY += 30;
			}
			else if (!((i + 2) % 3))
			{
				IIX += 90;
				IIY -= 30;
			}
			else if (!((i + 1) % 6)){
				IIX -= 180;
				IIY += 90;
			}
			else if(!((i+1)%3)){
				IIX -= 160;
				IIY += 90;
			}
//			else if ((i+1)%3){
//				IIX += 90;
//			}
/*			else if((i+1)%6) {
			IIX -= 225;
			IIY += 140;
			}
			else {
			IIX -= 135;
			IIY += 140;
			}
*/

		}

		if (ViewSTR1 == "1")			//有向
		{

			for (int k = 0; k < nume; k++)
			{
				for (int i = 0; i < nump; i++)
				{
					for (int j = 0; j < nump; j++)
					{
						temp1 = temB[k];
						temp3 = point[i];
						temp4 = point[j];
						if (temp1.find(temp3) == 0 && temp1.find(temp4) == 1)
						{
							temC[i][j] = "1";
							IIx1 = II[0][i];								//邊起點的x坐標
							IIy1 = II[1][i];								//-------y坐標
							IIx2 = II[0][j];								//邊終點的x坐標
							IIy2 = II[1][j];								//-------y坐標
							midpx = (IIx1 + IIx2) / 2;						//邊中點x
							midpy = (IIy1 + IIy2) / 2;						//------y
							tritailx = ((midpx + IIx2) / 2);				//箭頭末端x
							tritaily = ((midpy + IIy2) / 2);				//-------y
							tritopx = (((midpx + IIx2) / 2) + IIx2) / 2;	//箭頭頂點x
							tritopy = (((midpy + IIy2) / 2) + IIy2) / 2;	//-------y
							aDC.DrawText(_T("1"), CRect((orix + 40) + (j * 40), (oriy + 40) + (i * 40), nx, ny), 0);
							aDC.MoveTo(IIx1, IIy1);							//畫字母之間線
							aDC.LineTo(IIx2, IIy2);
							aDC.MoveTo(tritopx, tritopy);
//							if (!(IIx2-IIx1==0) && !(IIy2-IIy1!=0))
							if ((IIy2 - IIy1 != 0) && (IIx2 - IIx1 == 0)){			//畫箭頭
								aDC.LineTo(tritailx + 5, tritaily);
								aDC.LineTo(tritailx - 5, tritaily);
								aDC.LineTo(tritopx, tritopy);
							}
							else
							{
								M = ((IIy2 - IIy1) / (IIx2 - IIx1));		//斜率	
								if (M == 0){
									aDC.LineTo(tritailx, tritaily + 5);			
									aDC.LineTo(tritailx, tritaily - 5);
									aDC.LineTo(tritopx, tritopy);
								}
								else if (M > 0){
									//aDC.MoveTo(tritopx, tritopy);
									aDC.LineTo(tritailx - 3 , tritaily + 3 );
									aDC.LineTo(tritailx + 3 , tritaily - 3 );
									aDC.LineTo(tritopx, tritopy);
								}
								else if (M < 0){
									//aDC.MoveTo(tritopx-10, tritopy-10);
									aDC.LineTo(tritailx - 3, tritaily - 3 );
									aDC.LineTo(tritailx + 5, tritaily + 5);
									aDC.LineTo(tritopx, tritopy);
								}

							}
						
						}
						else if (temC[i][j] != "1")
						{
							temC[i][j] = "0";
							aDC.DrawText(_T("0"), CRect((orix + 40) + (j * 40), (oriy + 40) + (i * 40), nx, ny), 0);
						}

					}

				}
			}
		}
		
		if (ViewSTR1 == "0")			//無向
		{
			for (int k = 0; k < nume; k++)
			{
				for (int i = 0; i < nump; i++)
				{
					for (int j = 0; j < nump; j++)
					{
						temp1 = temB[k];
						temp3 = point[i];
						temp4 = point[j];
						if ((temp1.find(temp3) == 0 && temp1.find(temp4) == 1) || (temp1.find(temp4) == 0 && temp1.find(temp3)==1))
						{
							temC[i][j] = "1";
							IIx1 = II[0][j];
							IIy1 = II[1][j];
							IIx2 = II[0][i];
							IIy2 = II[1][i];

							aDC.DrawText(_T("1"), CRect((orix + 40) + (j * 40), (oriy + 40) + (i * 40), nx, ny), 0);	//ij掉轉,無向->對稱
							aDC.DrawText(_T("1"), CRect((orix + 40) + (i * 40), (oriy + 40) + (j * 40), nx, ny), 0);
							aDC.MoveTo(IIx1, IIy1);
							aDC.LineTo(IIx2, IIy2);
						}
						else if (temC[i][j] != "1")
						{
							temC[i][j] = "0";
							aDC.DrawText(_T("0"), CRect((orix + 40) + (j * 40), (oriy + 40) + (i * 40), nx, ny), 0);
						}
					}
				}
			}

		}
		IIX = orix + (nump + 1) * 40 + 100; IIY = oriy;
		for (int i = 0; i < nump; i++)			//畫圈&字母
		{

			temp3 = point[i];
			op1 = temp3.c_str();
			aDC.Ellipse(IIX, IIY, IIX + 30, IIY + 30);
			aDC.DrawText(op1, CRect(IIX + 10, IIY + 8, IIX + 40, IIY + 40), 0);
			II[0][i] = IIX + 15;
			II[1][i] = IIY + 15;

			if (!((i + 3) % 3))
			{
				IIX += 90;
				IIY += 30;
			}
			else if (!((i + 2) % 3))
			{
				IIX += 90;
				IIY -= 30;
			}
			else if (!((i + 1) % 6)){
				IIX -= 180;
				IIY += 90;
			}
			else if (!((i + 1) % 3)){
				IIX -= 160;
				IIY += 90;
			}
		}
		//		aDC.DrawText(ViewSTR1, CRect(0, 0, 100, 100), 0);
//		opnum = temB[1].c_str();
//		aDC.DrawText(opnum, CRect(0, 0, 100, 100), 0);

	}
	
}
