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
	, DialogSTR1(_T(""))
	, DialogSTR2(_T(""))
	, DialogSTR3(_T(""))

//	, DialogBU1(false)
//	, DialogBU2(false)

{

}

CTest1::~CTest1()
{
}

void CTest1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, DialogSTR1);
	DDX_Text(pDX, IDC_EDIT2, DialogSTR2);
	DDX_Text(pDX, IDC_EDIT3, DialogSTR3);
//	DDX_Radio(pDX, IDC_RADIO1, DialogBU1);
//	DDX_Radio(pDX, IDC_RADIO2, DialogBU2);
}


BEGIN_MESSAGE_MAP(CTest1, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CTest1::OnEnChangeEdit1)
	//ON_EN_CHANGE(IDC_EDIT2, &CTest1::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT2, &CTest1::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CTest1::OnEnChangeEdit3)
//	ON_BN_CLICKED(IDC_RADIO1, &CTest1::OnBnClickedRadio1)
//	ON_BN_CLICKED(IDC_RADIO2, &CTest1::OnBnClickedRadio2)
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




void CTest1::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTest1::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTest1::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void CTest1::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}
