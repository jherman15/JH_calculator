
// JH_calculator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// JH_Calculator:
// See JH_calculator.cpp for the implementation of this class
//

class JH_Calculator : public CWinApp
{
public:
	JH_Calculator();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern JH_Calculator theApp;
