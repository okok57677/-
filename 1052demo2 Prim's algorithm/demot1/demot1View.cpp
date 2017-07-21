
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

////////////////////
//Prim's algorithm//
////////////////////
/*
點的名稱：ABCDEFG
邊的內容：AB 7,BC 8,CE 5,BE 7,BD 9, AD 5,DE 15,EG 9,EF 8,FG
11 ,DF 6
開始的點：D
範例Output：D→A→F→B→E→C→G(輸出此字串4 分)
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
		string point[50], temA;					//點
		string edge, temB[200], temC[50][50];	//邊;temB[]=邊名稱
		long long weight[200];					//weight[]=邊權重
		ViewSTR1 = aDlg.DialogSTR1;			//輸入點
		ViewSTR2 = aDlg.DialogSTR2;			//輸入邊+權重
		ViewSTR3 = aDlg.DialogSTR3;			//輸入開始的點
//		ViewBU1 = aDlg.DialogBU1;
//		ViewBU2 = aDlg.DialogBU2;

		int nump = ViewSTR1.GetLength();		//GET ViewSTR1字符個數 = 輸入的點有多少個
		for (int i = 0; i < nump; i++)			//CString to string
			 point[i] += ViewSTR1[i];

		int nume = ViewSTR2.GetLength();		//GET ViewSTR2字符個數
		for (int i = 0; i < nume; i++)			//CString to string
			edge += ViewSTR2[i];

//-------------------------------------------------------------------------------------------------

		size_t pos = edge.find_first_of(",");	//用","﹑" "分割string		//處理字串中逗號及空格
		size_t wpos = edge.find_first_of(" ");
		int i = 0;	//共有多少條邊(?)
		int start = 0, wstart = 0;
		while (pos != string::npos)
		{
			size_t newpos = edge.find_first_of(",", pos + 1);
			size_t wnewpos = edge.find_first_of(" ", wpos + 1);

			temB[i] = edge.substr(start, wpos - start).c_str();			//提取已分割字串(邊名稱) -> string轉char *(CString) .c_str() ->  放入temB[0]陣列
			weight[i] = atoll(edge.substr(wpos + 1, pos - wpos-1).c_str());		//提取權重 ----------> 把權重轉int->放weight[]陣列
			start = pos + 1;
			if (pos - wnewpos == 1 || wnewpos - pos == 1){			//防止，前後的空格
				wnewpos = edge.find_first_of(" ", wnewpos + 1);
				start += 1;
			}
			pos = newpos;
			wpos = wnewpos;
			i++;
		}
		temB[i] = edge.substr(start, wpos - start).c_str();				//放最後一個元素進temB[]
		weight[i] = atoll(edge.substr(wpos + 1, pos - wpos - 1).c_str());	//把權重轉int->放weight[]
		
//---------------------------------------------------------------------------------------------------

		string startP,nextsP;					//startP:起始點or目前目標點 nextsP:預定下一目標點
		startP = ViewSTR3[0];					//CString to string
		string  outnode[50] = { "" };		//新加入的點
		outnode[0] = startP;

		long long wemin;			//最小權重
		string outedge[200],outweight[200];	//與接下來被加入點連接的邊 (最短路徑
		string swedge[200];		//目前點連接的邊的[名稱]
		long long sweight[200];					//				[權重]
		size_t tarpos;			//起始點or目前被加入點POSITION  (在一條邊中的位置
		int pk = 1,ek = 0,h=0;

		for (int m = 0; m <= i; m++)
		{
			//----------------------------------------------------------------------------------------------
			for (int j = 0; j <= i; j++)				//找出起始點所連接的邊
			{
				tarpos = temB[j].find_first_of(startP);
				if (tarpos != string::npos)	
				{
					swedge[h] = temB[j];			//把所有與目前點連接的邊放入sedge[1][] (未visited)
					sweight[h] = weight[j];
//					wemin =  weight[j];
					temB[j] = "";
					h++;
				}
				wemin = 999999999999;
			}

			//----------------------------------------------------------------------------------------------
			int tem = 0;								//找權重最小的邊
			for (int a = 0; a <= i; a++)	
			{
				if (sweight[a] <= wemin && sweight[a] >= 0)
				{
					outedge[ek] = swedge[a];
					outweight[ek] = to_string(sweight[a]);
					wemin = sweight[a];
					tem = a;
				}
			}
			swedge[tem] = "";		//刪剛VISITED邊 (最短路徑)
			sweight[tem] = 19999999999;
			//----------------------------------------------------------------------------------------------

			for (int b = 0; b <= i; b++)								//加入與最短邊連接的點
			{
				size_t oetem = outedge[ek].find_first_of(outnode[b]);
				if (static_cast<int>(oetem) == 0 && outnode[b] != "")
				{
					nextsP = outedge[ek].substr(1, 1);			//加入新點(node) : visited
					outnode[pk] = outedge[ek].substr(1, 1);
					break;

				}
				else if (static_cast<int>(oetem) == 1 && outnode[b] != "")
				{
					nextsP = outedge[ek].substr(0, 1);
					outnode[pk] = outedge[ek].substr(0, 1);			
					break;
				}

				//else if (oetem == string::npos){}
			}
			//---------------------------------------------------------------------------------------------
			startP = nextsP;
			pk++;
			ek++;

			int del_vised_N = 0;
			for (int n = 0; n <= i; n++)		//刪去visited資料
			{
				del_vised_N = 0;
				for (int o = 0; o <= i; o++)
				{
					if (outnode[o] != "" && swedge[n] != "" && swedge[n].find_first_of(outnode[o]) != string::npos)// 	//把兩點都visited的邊及其權重刪去 
					{
						del_vised_N += 1;
						if (del_vised_N == 2)
						{
							swedge[n] = "";				//刪邊
							sweight[n] = 19999999999;			//刪權重

						}
					}
					
				}
			}//FINISH 刪visited
			/*			//////////////////////////////  TESTING  ////////////////////////////////////////
			for (int n = 0; n < nump; n++){
				int convertdata = static_cast<int>(sweight[n]);	//size_t -> int
				string tmpS;
				tmpS = to_string(convertdata);
				opnum = tmpS.c_str();
				aDC.DrawText(opnum, CRect(0, 20 + m*(n * 16), 500, 500), 0);
				//
				//			opnum = (temB[m].substr(0,2)).c_str();

				//opnum = outweight[m].c_str();
				//			aDC.DrawText(opnum, CRect(0, 20+(m * 16), 500, 500), 0);
			}
*/			//////////////////////////////////////////////////////////////////////////////////
			//-------------------------------------------------------------------------------------------------
		}
		for (int m = 0; m <= i+1; m++){								//輸出NODE
			opnum = outnode[m].c_str();
			aDC.DrawText(opnum, CRect((m * 50),10, 500, 500), 0);
		}
		for (int m = 0; m < nump-1; m++){							//輸出箭頭
			string arrow = "→";
			opp = arrow.c_str();
			aDC.DrawText(opp, CRect(((m + 0.5) * 50), 10, 500, 500), 0);
		}
		//------------------------------------------------------------------------------------------------------
		int IIX = 100, IIY = 100;
		int	II[2][50];	//圈內英文字所在的坐標[0][]=x ; [1][]=y
		string temp;
		for (int i = 0; i < nump; i++)			//設點+圈的坐標
		{
			II[0][i] = IIX + 15;
			II[1][i] = IIY + 15;

			if (!((i + 3) % 3))
			{
				IIX += 90;
				IIY += 60;
			}
			else if (!((i + 2) % 3))
			{
				IIX += 90;
				IIY -= 60;
			}
			else if (!((i + 1) % 6)){
				IIX -= 180;
				IIY += 90;
			}
			else if (!((i + 1) % 3)){
				IIX -= 140;
				IIY += 140;
			}
		}
		//-----------------------------------------------------------------
		CPen penRED(PS_SOLID, 2, RGB(255, 0, 0));
		CPen penBLACK(PS_SOLID, 1, RGB(0, 0, 0));
		CPen * oldPen = aDC.SelectObject(&penRED);
		for (int k = 0; k < nump; k++)			//畫線
		{
			for (int i = 0; i < nump; i++)
			{
				for (int j = 0; j < nump; j++)
				{
					if (outedge[k].find(outnode[i]) == 0 && outedge[k].find(outnode[j])==1)
					{
						aDC.MoveTo(II[0][i], II[1][i]);
						aDC.LineTo(II[0][j], II[1][j]);
						//aDC.MoveTo(((II[0][i] + II[0][j]) / 2)+10, ((II[1][i] + II[1][j]) / 2)+10);		//移到線的中點的上面,畫權重
						opnum = outweight[k].c_str();
						aDC.DrawText(opnum, CRect(((((II[0][i] + II[0][j]) / 2)+II[0][i])/2) -5, ((((II[1][i] + II[1][j]) / 2)+II[1][i])/2) + 7,(k+1)*500,(k+1)*500),0);
						break;
					}

				}

			}
		}
		//--------------------------------------------------------------------
		oldPen = aDC.SelectObject(&penBLACK);
		IIX = 100, IIY = 100;
		for (int i = 0; i < nump; i++)			//畫圈&字母
		{

			temp = outnode[i].substr(0, 1);
			op1 = temp.c_str();
			aDC.Ellipse(IIX, IIY, IIX + 30, IIY + 30);
			aDC.DrawText(op1, CRect(IIX + 10, IIY + 8, IIX + 40, IIY + 40), 0);
			II[0][i] = IIX + 15;
			II[1][i] = IIY + 15;

			if (!((i + 3) % 3))
			{
				IIX += 90;
				IIY += 60;
			}
			else if (!((i + 2) % 3))
			{
				IIX += 90;
				IIY -= 60;
			}
			else if (!((i + 1) % 6)){
				IIX -= 180;
				IIY += 90;
			}
			else if (!((i + 1) % 3)){
				IIX -= 140;
				IIY += 140;
			}
		}

	}
}
	

