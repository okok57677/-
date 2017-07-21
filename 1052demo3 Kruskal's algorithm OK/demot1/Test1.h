#pragma once


// CTest1 dialog

class CTest1 : public CDialog
{
	DECLARE_DYNAMIC(CTest1)

public:
	CTest1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTest1();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	float DialogF1;
//	float DialogF2;
//	afx_msg void OnEnChangeEdit2();

	CString DialogSTR1;
	CString DialogSTR2;
//	CString DialogSTR3;


	afx_msg void OnEnChangeEdit1();

	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
//	int DialogBU1;
//	int DialogBU2;

};
