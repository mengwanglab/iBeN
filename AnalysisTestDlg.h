// AnalysisTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "NiSlide.h"
#include "NiGraph.h"
#include "NiButton.h"
#include "NiNumEdit.h"
//}}AFX_INCLUDES

#if !defined(AFX_ANALYSISTESTDLG_H__A477866D_2523_4985_A710_76B6CFA0232C__INCLUDED_)
#define AFX_ANALYSISTESTDLG_H__A477866D_2523_4985_A710_76B6CFA0232C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\DAO\IBBDaoDatabase.h"
#include ".\AVI\AviProcess.h"
#include ".\FeatureAlogrithm\Features.h"

/////////////////////////////////////////////////////////////////////////////
// CAnalysisTestDlg dialog

#define WM_ANALYSIS_PROGRESS    (WM_USER+200)    //��������������
#define WM_PLAYBACK_PROGRESS    (WM_USER+201)    //�طŽ���������
#define WM_MESSAGE              (WM_USER+202)    //������ʾEDIT�����
#define WM_GET_TIME             (WM_USER+203)    //��ȡ������ʱ
#define WM_CHOOSE_HEAD          (WM_USER+204)    //�����˹�ѡ��ͷβ�ĶԻ���
#define WM_EDIT_DATABASE        (WM_USER+205)    //�޸����ݿ⣬����������������

class CAnalysisTestDlg : public CDialog
{
// Construction
public:
	CAnalysisTestDlg(CWnd* pParent = NULL);	// standard constructor

	CString ChuLiPerAviFile(CString aviFile);
	void InsertItem(CString ids, CString name);
	void InitialList();

	void FitScreenSize(CWnd *p);
	//void AddData();
	
// Dialog Data
	//{{AFX_DATA(CAnalysisTestDlg)
	enum { IDD = IDD_ANALYSISTEST_DIALOG };
	CButton	m_ctrStaticList;
	CButton	m_ctrStaticCtrl;
	CButton	m_ctrStaticSchedule;
	CEdit	m_ctrEditMessage;
	CButton	m_btnProcessFrameZone;
	CButton	m_previewBtn;
	CStatic	m_Screen;
	CListCtrl	m_FileNameList;
	CNiSlide	m_NiSlide;
	CNiSlide	m_NiProgress;
	CNiGraph	m_NiTrace;
	CNiGraph	m_NiHistogram;
	CNiNumEdit	m_NiPreEditNum;
	CNiNumEdit	m_NiBeginFrame;
	CNiNumEdit	m_NiEndFrame;
	CString	m_strMessage;
	BOOL	m_CheckHistogram;
	BOOL  m_ChooseForStepOne;
	//}}AFX_DATA

	CIBBDaoDatabase m_mydatabase;
	CAviProcess myAvi;
	StrRecName  myFileListData;//avi�ļ�������Ϣ�����ݽӿ�


	long	m_frameNum;
    int nItem;     //List�е����;
	int AviIndex;  //Avi�ļ����
	BOOL m_MatchClient;

	long exSetToWndRectEx(HANDLE hBoard, HWND hWnd, long lMode);

	int SortColumn;    //�˶�������Ϊ�б�������׼��
	bool Bool_OrderAsc;

	void DrawHistogram();
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void InitSkin ();
	CString GetAppPath ();
	
	// Generated message map functions
	//{{AFX_MSG(CAnalysisTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonSingle();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);   //add
	afx_msg void OnSizing( UINT nSide, LPRECT lpRect );	//add
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonStop();
	afx_msg void OnClickListFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButDelFile();
	afx_msg void OnButRefreash();
	afx_msg void OnButReview();
	afx_msg void OnClose();
	afx_msg void OnButReviewPause();
	afx_msg void OnButDelAll();
	afx_msg void OnButReviewStop();
	afx_msg void OnPointerValueChangedCwslidePlayback(long Pointer, VARIANT FAR* Value);
	afx_msg void OnPointerValueChangedCwslideProgress(long Pointer, VARIANT FAR* Value);
	afx_msg void OnButPreviewSign();
	afx_msg void OnIncDecButtonClickedCwnumeditPreFramenum(BOOL IncButton);
	afx_msg void OnButReviewReverse();
	afx_msg void OnButProcessFrames();
	afx_msg void OnButProcessProperty();
	afx_msg void OnButDelBufferAvi();
	afx_msg void OnButBatch();
	afx_msg void OnButSaveBmp();
	afx_msg void OnCheckHistogram();
	afx_msg void OnButGetData();
	afx_msg void OnButSaveAvi();
	afx_msg void OnButSpecial1();
	afx_msg void OnButSpecial2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnPlayBackProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAnalysisProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProgressMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTimeMessage(WPARAM wParam,LPARAM lParam);
	
	afx_msg LRESULT OnGetHeadMessage(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnEditDatabase(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChooseAlgorithm();
	afx_msg void OnEnChangeEditUpLevel();
	afx_msg void OnStnClickedImage();
	afx_msg void OnBnClickedButHeadTail();
	afx_msg void OnEnChangeEditCcdScale7();
};


//���ݵ���
void AddData();
BOOL GetDefaultXlsFileName(CString& sExcelFile);
void CreatToAccess(CString moveName);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSISTESTDLG_H__A477866D_2523_4985_A710_76B6CFA0232C__INCLUDED_)

//
