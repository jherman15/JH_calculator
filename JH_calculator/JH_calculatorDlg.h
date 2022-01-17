
// JH_calculatorDlg.h : header file
//

#pragma once


// CJHcalculatorDlg dialog
class CJHcalculatorDlg : public CDialogEx
{
// Construction
public:
	CJHcalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JH_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	double num0, num1;
	long double result, resultDec;
	long long int resultBin, resultHex, resultOct;					//jh: copy of result to be used in conversion
	int op;
	bool changeNum, equPressed;
	CString str1, str2;
	CString Edit_window;
	

	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMply();
	afx_msg void OnBnClickedButtonDiv();

	afx_msg void OnBnClickedButtonEqu();

	afx_msg void OnBnClickedButtonBin();
	afx_msg void OnBnClickedButtonOct();
	afx_msg void OnBnClickedButtonHex();
	afx_msg void OnBnClickedButtonDec();
	afx_msg void OnBnClickedButtonClr();
};
