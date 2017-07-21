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
	input->GetWindowText(inp);		//Ū��

	int n = inp.GetLength();		// �r�����
	for (int i = 0; i < n; i++)		// CString --> string
			a += inp[i];

	size_t pos = a.find_first_of(" ");		//�R���r�ꤤ�Ů�
	while (pos != string::npos)
	{
		a.erase(pos, 1);
		pos = a.find_first_of(" ", pos + 1);
	}

	n = a.length();		//���]�r�����
	int temp;
	for (int i = 0; i<n; i++)		//�[�J�_�l��(��J��)��op(��X���G)
		op = op + a[i] + ' ';		//���s�[�J�Ů�ܿ�X���G
	op += '\r';		// ���в���̥�,����
	op += '\n';

	for (int i = 0; i<n; i++)			// �Ƨǧ�X��i�p���P
	{
		int min = i;
		for (int j = i + 1; j<n; j++)		// �ѤU��n-i�i��,��X�ثe�̤p��
		{
			if (a[j] < a[min])
				min = j;
		}
		temp = a[min];				// exchange a[i],a[min]
		a[min] = a[i];
		a[i] = temp;

		if (a[min] != a[i])		//�Y���r���洫��
		{
			for (int i = 0; i<n; i++)
				op = op + a[i] + ' ';		//���s�[�J�Ů�ܿ�X���G
			op += '\r';		// ���в���̥�,����
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
