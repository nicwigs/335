
// project1.h : main header file for the project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cproject1App:
// See project1.cpp for the implementation of this class
//


/**
 * Class for project
 */
class Cproject1App : public CWinApp
{
public:
	Cproject1App();


// Overrides
public:

	/**
	* initial instance
	*\return a bool
	*/
	virtual BOOL InitInstance(); 

	/**
	 * exits instance
	 *\return int
	 */
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout(); ///< onAppAout
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; ///< startupinput
	ULONG_PTR gdiplusToken; ///< token
};

extern Cproject1App theApp;
