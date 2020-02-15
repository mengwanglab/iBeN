#if !defined(AFX_MANEAGELIST_H__7462F13F_7994_4441_9E8B_DE5B829178A4__INCLUDED_)
#define AFX_MANEAGELIST_H__7462F13F_7994_4441_9E8B_DE5B829178A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManeageList.h : header file
//

//Add Dialog head file
#include "AnalysisTestDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CManeageList window

class CManeageList : public CListCtrl
{
// Construction
public:
	CManeageList();
// Attributes
public:

	CAnalysisTestDlg   *dlg; //ListCtrl控件所处的窗口类的指针

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManeageList)
	//}}AFX_VIRTUAL

// Implementation
public:

	static int CALLBACK ItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort);
	void ClickCol_Sort(NM_LISTVIEW* pNMListViewTmp);
	BOOL InitList();
	virtual ~CManeageList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CManeageList)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANEAGELIST_H__7462F13F_7994_4441_9E8B_DE5B829178A4__INCLUDED_)
