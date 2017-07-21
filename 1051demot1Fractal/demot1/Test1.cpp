// Test1.cpp : implementation file
//

#include "stdafx.h"
#include "demot1.h"
#include "Test1.h"
#include "afxdialogex.h"


// CTest1 dialog

IMPLEMENT_DYNAMIC(CTest1, CDialog)

CTest1::CTest1(CWnd* pParent /*=NULL*/)
	: CDialog(CTest1::IDD, pParent)
	, DialogINT(0)
{

}

CTest1::~CTest1()
{
}

void CTest1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DialogINT);
}


BEGIN_MESSAGE_MAP(CTest1, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CTest1::OnEnChangeEdit1)
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
