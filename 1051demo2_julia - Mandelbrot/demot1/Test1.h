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

	CString DialogCS;
	afx_msg void OnEnChangeEdit1();

};
