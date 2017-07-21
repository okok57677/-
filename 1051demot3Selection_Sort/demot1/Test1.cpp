// Test1.cpp : implementation file
//
#include "iostream"
#include "stdafx.h"
#include "demot1.h"
#include "Test1.h"
#include "afxdialogex.h"

#include <cstring>
#include <string>
#include <vector>
using namespace std;
#define _SCL_SECURE_NO_WARNINGS



// CTest1 dialog

IMPLEMENT_DYNAMIC(CTest1, CDialog)

CTest1::CTest1(CWnd* pParent /*=NULL*/)
	: CDialog(CTest1::IDD, pParent)
	, DialogINT(0)
	, DialogSTR(_T(""))
{

}

CTest1::~CTest1()
{
}

void CTest1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DialogSTR);
}


BEGIN_MESSAGE_MAP(CTest1, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CTest1::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTest1::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CTest1::OnBnClickedOk)
END_MESSAGE_MAP()


// CTest1 message handlers


void CTest1::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTest1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CWnd* input = static_cast<CWnd*>(GetDlgItem(IDC_EDIT1));	//INPUT
	CWnd* output = static_cast<CWnd*>(GetDlgItem(IDC_EDIT2));	//OUTPUT

	CString inp, op;
	string a;
	//vector<string> b;
	input->GetWindowText(inp);		//讀值

	int n = inp.GetLength();		// 字串長度
	for (int i = 0; i < n; i++)		// CString --> string
			a += inp[i];

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

	output->SetWindowText(op);
	
}


void CTest1::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}
