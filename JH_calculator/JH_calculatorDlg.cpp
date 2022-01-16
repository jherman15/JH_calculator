
// JH_calculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "JH_calculator.h"
#include "JH_calculatorDlg.h"
#include "afxdialogex.h"
#include <bitset> //jh: convert to binary
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJHcalculatorDlg dialog



CJHcalculatorDlg::CJHcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JH_CALCULATOR_DIALOG, pParent)
	, Edit_window(_T(""))
{
	num0 = num1 = 0;
	str1 = _T("");
	str2 = _T("");

	changeNum = true;
	equ_pressed = false;
	op = 0;
	result = 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJHcalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Edit_window);
}

BEGIN_MESSAGE_MAP(CJHcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON0, &CJHcalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON1, &CJHcalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CJHcalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CJHcalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CJHcalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CJHcalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CJHcalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CJHcalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CJHcalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CJHcalculatorDlg::OnBnClickedButton9)
	
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CJHcalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CJHcalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MPLY, &CJHcalculatorDlg::OnBnClickedButtonMply)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CJHcalculatorDlg::OnBnClickedButtonDiv)

	ON_BN_CLICKED(IDC_BUTTON_EQU, &CJHcalculatorDlg::OnBnClickedButtonEqu)


	ON_BN_CLICKED(IDC_BUTTON_BIN, &CJHcalculatorDlg::OnBnClickedButtonBin)
	ON_BN_CLICKED(IDC_BUTTON_OCT, &CJHcalculatorDlg::OnBnClickedButtonOct)
	ON_BN_CLICKED(IDC_BUTTON_HEX, &CJHcalculatorDlg::OnBnClickedButtonHex)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CJHcalculatorDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_CLR, &CJHcalculatorDlg::OnBnClickedButtonClr)
END_MESSAGE_MAP()


// CJHcalculatorDlg message handlers

BOOL CJHcalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJHcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJHcalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.

HCURSOR CJHcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CJHcalculatorDlg::OnBnClickedButton0()
{
	if (changeNum == true)
	{
		str1 += _T("0");	//add 0 on the end of string 1
		Edit_window = str1;
	}
	else
	{
		str2 += _T("0");	//add 0 on the end of string 2
		Edit_window = str2;
	}

	UpdateData(FALSE);

}


void CJHcalculatorDlg::OnBnClickedButton1()
{
	if (changeNum == true)
	{
		str1 += _T("1");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("1");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton2()
{
	if (changeNum == true)
	{
		str1 += _T("2");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("2");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton3()
{
	if (changeNum == true)
	{
		str1 += _T("3");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("3");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton4()
{
	if (changeNum == true)
	{
		str1 += _T("4");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("4");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton5()
{
	if (changeNum == true)
	{
		str1 += _T("5");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("5");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton6()
{
	if (changeNum == true)
	{
		str1 += _T("6");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("6");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton7()
{
	if (changeNum == true)
	{
		str1 += _T("7");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("7");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton8()
{
	if (changeNum == true)
	{
		str1 += _T("8");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("8");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}


void CJHcalculatorDlg::OnBnClickedButton9()
{
	if (changeNum == true)
	{
		str1 += _T("9");
		Edit_window = str1;
	}
	else
	{
		str2 += _T("9");
		Edit_window = str2;
	}

	UpdateData(FALSE);
}






void CJHcalculatorDlg::OnBnClickedButtonPlus()
{
	if (Edit_window != _T(""))				//jh: if edit window is not empty
	{
		//if (equ_pressed = false)
		//{
			num1 = _ttof(Edit_window);		//jh: convert string to numerical value (num1)
			changeNum = !changeNum;			//jh: num1 to num2 or num2 to num1				//jh: changeNum to false		//dok
			Edit_window = _T("");			
			op = 1;							//jh: set operation to 1
			equ_pressed = true;																								//dok
		//}
		//else
		//{
		//	OnBnClickedButtonEqu();
		//}
	}
}


void CJHcalculatorDlg::OnBnClickedButtonMinus()
{
	if (Edit_window != _T(""))
	{
		num1 = _ttof(Edit_window);
		changeNum = !changeNum;
		Edit_window = _T("");
		op = 2;
	}
}


void CJHcalculatorDlg::OnBnClickedButtonMply()
{
	if (Edit_window != _T(""))
	{
		num1 = _ttof(Edit_window);
		changeNum = !changeNum;
		Edit_window = _T("");
		op = 3;
	}
}


void CJHcalculatorDlg::OnBnClickedButtonDiv()
{
	if (Edit_window != _T(""))
	{
		num1 = _ttof(Edit_window);
		changeNum = !changeNum;
		Edit_window = _T("");
		op = 4;
	}
}


void CJHcalculatorDlg::OnBnClickedButtonEqu()
{
	if (Edit_window != _T(""))
	{
		num0 = _ttof(Edit_window);			//jh: convert string to numerical value (num0)
		changeNum = !changeNum;				
		Edit_window = _T("");				//jh: clear the edit window
	}

	if (op == 1)
	{
		result = num1 + num0;
	}
	if (op == 2)
	{
		result = num1 - num0;
	}
	if (op == 3)
	{
		result = num1 * num0;
	}
	if (op == 4)
	{
		result = num1 / num0;
	}
	else
	{
		result = result;
	}

	Edit_window.Format(_T("%.3f"), result);				//jh: convert the result from string to float
	UpdateData(FALSE);
	str1 = _T("");										//jh: clear string (str1)
	str2 = _T("");										//jh: clear string (str2)
	equ_pressed = true;

	if (result > 9000000000000000)						//jh: this value is close to 2^53, which is approx. the maximum value
	{
		Edit_window = "Max number is 9*10^15 (DEC)";
		UpdateData(FALSE);
	}
}

long long int CJHcalculatorDlg::BinAlgorithm(long long int number)
{
	number = _ttof(Edit_window);
	std::string binary;
	binary = std::bitset<32>(number).to_string();			//jh: max 32-bit numbers
	Edit_window = binary.c_str();							//jh: conversion to CString (in order to display the result)
	UpdateData(FALSE);
	return number;
}

void CJHcalculatorDlg::OnBnClickedButtonBin()
{
	if (changeNum == true)
	{
		BinAlgorithm(num1);
	}
	else
	{
		BinAlgorithm(result);
	}
	
	if (result < 0)
	{
		Edit_window = "Negative numbers not supported";		//jh: conversion only for positive numbers
		UpdateData(FALSE);
	}

	if (result > 65535)
	{
		Edit_window = "Max number for BIN is 65535 (DEC)";
		UpdateData(FALSE);
	}


}



void CJHcalculatorDlg::OnBnClickedButtonOct()
{
	num1 = _ttof(Edit_window);

	long long int oct = 0;									//jh: octal number
	long long int rem;										//jh: division's remainder
	result_ = num1;										//jh: result variable copy

	for (long long int i = 1; result_ > 0; i = i * 10)
	{
		rem = result_ % 8;									//jh: remainder of dividing by 8
		result_ = result_ / 8;
		oct += (rem * i);									//jh: algorithm for getting octal number
	}

	Edit_window.Format(_T("%lld"), oct);					//jh: conversion of oct variable type (long long int) to CString
	UpdateData(FALSE);

	if (result_ < 0)
	{
		Edit_window = "Negative numbers not supported";		//jh: conversion only for positive numbers
		UpdateData(FALSE);
	}

	if (result > 9000000000000000)
	{
		Edit_window = "Max number is 9*10^15 (DEC)";
		UpdateData(FALSE);
	}

	Edit_window = "";										//jh: clear the edit window
}


void CJHcalculatorDlg::OnBnClickedButtonHex()
{
	num1 = _ttof(Edit_window);

	result_ = result;										//jh: result_ equals result to be used in conversion
	std::string hexNum = "";								//jh: variable to store hex number string

	int i = 0;												//jh: counter for hexadecimal number array

	while (result_ != 0)
	{
		int rem = 0;										//jh: temporary variable to store remainder
		rem = result_ % 16;

		if (rem < 10)
		{
			hexNum = char(rem + 48) + hexNum;
			i++;
		}
		else 
		{
			hexNum = char(rem + 55) + hexNum;
			i++;
		}

		result_ = result_ / 16;
	}

	if (hexNum == "")
	{
		Edit_window = "0";									// dla pustego q, na ekranie wyswietlana jest wartosc 0
		UpdateData(FALSE);
	}
	else
	{
		Edit_window = hexNum.c_str(); // konwersja typu string na cstring
		UpdateData(FALSE);
	}


	if (result_ < 0)
	{
		Edit_window = "Negative numbers not supported";
		UpdateData(FALSE);
	}

	if (result > 9000000000000000)
	{
		Edit_window = "Max number is 9*10^15 (DEC)";
		UpdateData(FALSE);
	}

	Edit_window = "";
}


void CJHcalculatorDlg::OnBnClickedButtonDec()
{
	num1 = _ttof(Edit_window);

	Edit_window.Format(_T("%.3f"), result); // przedstawienie zmiennej zawierajacej wynik dzialania w typie cstring
	UpdateData(FALSE);

	if (result > 9000000000000000)
	{
		Edit_window = "Max number is 9*10^15 (DEC)";
		UpdateData(FALSE);
	}
}


void CJHcalculatorDlg::OnBnClickedButtonClr()
{
	Edit_window = "";
	str1 = "";
	str2 = "";
	UpdateData(FALSE);
}
