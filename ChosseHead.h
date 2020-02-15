#if !defined(AFX_CHOSSEHEAD_H__DB8D8A3A_9586_4EE7_AA0B_6709D085C39E__INCLUDED_)
#define AFX_CHOSSEHEAD_H__DB8D8A3A_9586_4EE7_AA0B_6709D085C39E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChosseHead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChosseHead dialog

class CChosseHead : public CDialog
{
// Construction
public:
	CChosseHead(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChosseHead)
	enum { IDD = IDD_DLG_CHOOSE_HEAD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChosseHead)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	
	int iTmpImageNum; //当前Buffer中图像的第几帧
	int iTmpDataNum; //当前处理的movie的总第几帧

protected:

	// Generated message map functions
	//{{AFX_MSG(CChosseHead)
	afx_msg void OnButChooseA();
	afx_msg void OnButChooseB();
	afx_msg void OnButAbort();
	afx_msg void OnButOk();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOSSEHEAD_H__DB8D8A3A_9586_4EE7_AA0B_6709D085C39E__INCLUDED_)
