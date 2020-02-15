// AnalysisTest.h : main header file for the ANALYSISTEST application
//

#if !defined(AFX_ANALYSISTEST_H__CAF8BB35_F188_43A3_AF6A_E0DDB98B2934__INCLUDED_)
#define AFX_ANALYSISTEST_H__CAF8BB35_F188_43A3_AF6A_E0DDB98B2934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnalysisTestApp:
// See AnalysisTest.cpp for the implementation of this class
//

class CAnalysisTestApp : public CWinApp
{
public:
	CAnalysisTestApp();

	HMODULE m_hModule;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnalysisTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CAnalysisTestApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSISTEST_H__CAF8BB35_F188_43A3_AF6A_E0DDB98B2934__INCLUDED_)
