// AnalysisTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnalysisTest.h"
#include "AnalysisTestDlg.h"
#include <stdlib.h>
#include <windows.h>
#include <afxwin.h>
#include "ManeageList.h"
#include ".\DAO\IBBDaoDatabase.h"
#include ".\AVI\AviProcess.h"
#include ".\FeatureAlogrithm\Features.h"
#include ".\FeatureAlogrithm\Pretreatment.h"
#include "ChosseHead.h"
#include <afxtempl.h>
#include <assert.h>

//#define   _CRT_SECURE_NO_DEPRECATE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE hThread1;
HANDLE hThread2;
HANDLE hThread3;
HANDLE hThread4;

HANDLE hThread5;

CFeatures myElegansFeatures;
CArray<CDataPropety,CDataPropety> dpArray;
ElegansData structEData;



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisTestDlg dialog

CAnalysisTestDlg::CAnalysisTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalysisTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnalysisTestDlg)
	m_strMessage = _T("");
	m_CheckHistogram = FALSE;
	m_ChooseForStepOne = TRUE; 
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnalysisTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalysisTestDlg)
	DDX_Control(pDX, IDC_STATIC_LIST, m_ctrStaticList);
	DDX_Control(pDX, IDC_STATIC_CTRL, m_ctrStaticCtrl);
	DDX_Control(pDX, IDC_STATIC_SCHEDULE, m_ctrStaticSchedule);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_ctrEditMessage);
	DDX_Control(pDX, IDC_BUT_PROCESS_FRAMES, m_btnProcessFrameZone);
	DDX_Control(pDX, IDC_BUT_PREVIEW_SIGN, m_previewBtn);
	DDX_Control(pDX, IDC_IMAGE, m_Screen);
	DDX_Control(pDX, IDC_LIST_FILE, m_FileNameList);
	DDX_Control(pDX, IDC_CWSLIDE_PLAYBACK, m_NiSlide);
	DDX_Control(pDX, IDC_CWSLIDE_PROGRESS, m_NiProgress);
	DDX_Control(pDX, IDC_CWGRAPH_TRACE, m_NiTrace);
	DDX_Control(pDX, IDC_CWGRAPH_HISTOGRAM, m_NiHistogram);
	DDX_Control(pDX, IDC_CWNUMEDIT_PRE_FRAMENUM, m_NiPreEditNum);
	DDX_Control(pDX, IDC_CWNUMEDIT_BEGIN, m_NiBeginFrame);
	DDX_Control(pDX, IDC_CWNUMEDIT_END, m_NiEndFrame);
	DDX_Text(pDX, IDC_EDIT_MESSAGE, m_strMessage);
	DDX_Check(pDX, IDC_CHECK_HISTOGRAM, m_CheckHistogram);
	DDX_Check(pDX,IDC_CHOOSE_ALGORITHM,m_ChooseForStepOne);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnalysisTestDlg, CDialog)
	//{{AFX_MSG_MAP(CAnalysisTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUT_SINGLE, OnButtonSingle)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_MOVING()  //add
	ON_WM_SIZING()  //add
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUT_STOP, OnButtonStop)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FILE, OnClickListFile)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FILE, OnColumnclickListFile)
	ON_BN_CLICKED(IDC_BUT_DEL_FILE, OnButDelFile)
	ON_BN_CLICKED(IDC_BUT_REFREASH, OnButRefreash)
	ON_BN_CLICKED(IDC_BUT_REVIEW, OnButReview)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUT_REVIEW_PAUSE, OnButReviewPause)
	ON_BN_CLICKED(IDC_BUT_DEL_ALL, OnButDelAll)
	ON_BN_CLICKED(IDC_BUT_REVIEW_STOP, OnButReviewStop)
	ON_BN_CLICKED(IDC_BUT_PREVIEW_SIGN, OnButPreviewSign)
	ON_BN_CLICKED(IDC_BUT_REVIEW_REVERSE, OnButReviewReverse)
	ON_BN_CLICKED(IDC_BUT_PROCESS_FRAMES, OnButProcessFrames)
	ON_BN_CLICKED(IDC_BUT_PROCESS_PROPERTY, OnButProcessProperty)
	ON_BN_CLICKED(IDC_BUT_DEL_BUFFER_AVI, OnButDelBufferAvi)
	ON_BN_CLICKED(IDC_BUT_BATCH, OnButBatch)
	ON_BN_CLICKED(IDC_BUT_SAVE_BMP, OnButSaveBmp)
	ON_BN_CLICKED(IDC_CHECK_HISTOGRAM, OnCheckHistogram)
	ON_BN_CLICKED(IDC_CHOOSE_ALGORITHM,OnChooseAlgorithm)
	ON_BN_CLICKED(IDC_BUT_GET_DATA, OnButGetData)
	ON_BN_CLICKED(IDC_BUT_SAVE_AVI, OnButSaveAvi)
	ON_BN_CLICKED(IDC_BUT_SPECIAL_1, OnButSpecial1)
	ON_BN_CLICKED(IDC_BUT_SPECIAL_2, OnButSpecial2)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_PLAYBACK_PROGRESS,OnPlayBackProgress)
	ON_MESSAGE(WM_PLAYBACK_PROGRESS,OnAnalysisProgress)
	ON_MESSAGE(WM_MESSAGE,OnProgressMessage)
	ON_MESSAGE(WM_GET_TIME,OnGetTimeMessage)
	
	ON_MESSAGE(WM_CHOOSE_HEAD,OnGetHeadMessage)
	ON_MESSAGE(WM_EDIT_DATABASE,OnEditDatabase)
	ON_BN_CLICKED(IDC_CHOOSE_ALGORITHM, &CAnalysisTestDlg::OnChooseAlgorithm)
	ON_EN_CHANGE(IDC_EDIT_UP_LEVEL, &CAnalysisTestDlg::OnEnChangeEditUpLevel)
	ON_STN_CLICKED(IDC_IMAGE, &CAnalysisTestDlg::OnStnClickedImage)
	ON_BN_CLICKED(IDC_BUT_HEAD_TAIL, &CAnalysisTestDlg::OnBnClickedButHeadTail)
	ON_EN_CHANGE(IDC_EDIT_CCD_SCALE7, &CAnalysisTestDlg::OnEnChangeEditCcdScale7)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisTestDlg message handlers

CAnalysisTestDlg* gDlg;

DWORD WINAPI NewProcessProc_iNemo(
						 LPVOID lpParameter   // thread data
						 );


DWORD WINAPI ProcessProc(
	LPVOID lpParameter   // thread data
);


DWORD WINAPI ReviewProc(
	LPVOID lpParameter   // thread data
);

DWORD WINAPI SpecialProcessProc(
	LPVOID lpParameter   // thread data
);   

//
DWORD WINAPI UnCompressProc(
	LPVOID lpParameter   //thread data
);


BOOL CAnalysisTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	InitSkin ();

	g_iAreaUpLevel = 190000;
	g_iAreaDownLevel = 8000;
	SetDlgItemText(IDC_EDIT_UP_LEVEL,"190000");
	SetDlgItemText(IDC_EDIT_DOWN_LEVEL,"8000");
	g_dCCDScale = 4.3;
	SetDlgItemText(IDC_EDIT_CCD_SCALE,"4.3");
	//Add 2009.9.3
	g_iReadBuffer = 100;
	SetDlgItemText(IDC_EDIT_BUFFER,"100");

	//2010.8.4
	SetDlgItemText(IDC_EDIT_PERI_HIGH,"700");
	SetDlgItemText(IDC_EDIT_PERI_LOW,"200");
	SetDlgItemText(IDC_EDIT_AREA_HIGH,"5000");
	SetDlgItemText(IDC_EDIT_AREA_LOW,"1000");

	SetDlgItemText(IDC_EDIT_BINNING,"0.5");
	CString str0804;
	GetDlgItemText(IDC_EDIT_BINNING, str0804);
	g_fBinningFlag = atof(str0804);
	SetDlgItemText(IDC_EDIT_MULTIOTSU_LEVEL,"4");
	SetDlgItemText(IDC_EDIT_MULTIOTSU_THNUM,"2");

	LOGFONT lf; 
	CFont font;
	memset(&lf,0,sizeof(LOGFONT));
	lf.lfHeight=18;
	lf.lfWeight=FW_SEMIBOLD;
	lf.lfEscapement=0;
	lf.lfCharSet=DEFAULT_CHARSET;
	strcpy(lf.lfFaceName,"Verdana");
	font.DeleteObject();
	font.CreateFontIndirect(&lf);
	m_ctrEditMessage.SetFont(&font,TRUE);
	m_ctrStaticList.SetFont(&font,TRUE);
	m_ctrStaticSchedule.SetFont(&font,TRUE);
	m_ctrStaticCtrl.SetFont(&font,TRUE);

//////////////////////////////////////////////////////////////////////////
	hWnd=this->GetSafeHwnd(); 
	gDlg=(CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();
	

	long lIndex=-1;
	hBoard=okOpenBoard(&lIndex);
	okSetCaptureParam(hBoard,CAPTURE_CLIPMODE,0);
	okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
	okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//

	
	short heightTemp;
	long strideTemp;
	CRect   rect;            // 
	SetRect(&rect,0,0,640,480);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
	m_Screen.GetWindowRect(&rect); 
	m_Screen.MoveWindow(0,0,640,480); 


	CRect rect_1;
   	GetDlgItem(IDC_CWSLIDE_PLAYBACK)->GetWindowRect(&rect_1);       
	ScreenToClient(&rect_1);
	int x = 0;
	int y = rect_1.top;
	int width=480; 
	int height = rect_1.Height();		  
	GetDlgItem(IDC_CWSLIDE_PLAYBACK)->SetWindowPos(NULL,x,y,width,height,SWP_SHOWWINDOW); 
	
	CManeageList cList;
	cList.InitList();

	AfxGetModuleState()->m_dwVersion=0x0601; 

	m_mydatabase.FindDB("FileList_database.mdb");
	m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");
	m_mydatabase.DisplayData("SELECT * FROM [data]",&m_FileNameList);
	m_mydatabase.CloseDB();

	char tmpFileName[256]="\0";
	sprintf(tmpFileName,"E:\\Worm Data");	
	DWORD dwAttr = GetFileAttributes(tmpFileName);
	if(dwAttr == 0xFFFFFFFF)   
		CreateDirectory(tmpFileName,NULL);

	GetDlgItem(IDC_BUT_SAVE_BMP)->EnableWindow(FALSE);
//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//add by haining 2008.12.2
	ZeroMemory(&g_blk,sizeof(BLOCKINFO));

	

	//FitScreenSize(this);
	//FitScreenSize(GetDlgItem(IDC_CWSLIDE_PLAYBACK));
	FitScreenSize(GetDlgItem(IDC_CWSLIDE_PLAYBACK));
	//CenterWindow();
	

	//ShowWindow(SW_SHOWMAXIMIZED);
	
	////////////////////////////////////////////////////////////////////////// 
	const char* opencv_libraries = 0;
	const char* addon_modules = 0;
	cvGetModuleInfo( 0, &opencv_libraries,&addon_modules );
	printf( "OpenCV: %s\r\nAdd-on Modules: %s\r\n.", opencv_libraries, addon_modules); 
	int iOptimizedNum = cvUseOptimized(1);
    //////////////////////////////////////////////////////////////////////////


	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CAnalysisTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnalysisTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAnalysisTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


/*

*/
//--demo to set current capture rect on screen. mode=0: left-top, 1:centerize
long CAnalysisTestDlg::exSetToWndRectEx(HANDLE hBoard, HWND hWnd, long lMode)
{
	long	lSize;
	RECT	rect;
	
	if (!IsWindow(hWnd)) 
		return FALSE;
	
	if (IsIconic()) 
	{
		return FALSE;//
	}

	//get client rect
	GetClientRect(&rect);
	okSetToWndRect(hBoard, hWnd);	
	
	if (lMode == 1)  //set to center
	{
		short	width,height;
		//get available rect size
		//lSize=okSetVideoParam(hBoard,VIDEO_AVAILRECTSIZE,-1);
		//or set to expected size
		//sampwidth=LOWORD(lSize);
		//sampheight=HIWORD(lSize);
		if (okGetCaptureStatus(hBoard, 0))  //capturing
		{
			width = sampwidth;
			height = sampheight;
		}
		else  //frozen status
		{
			width = 800;//(short)lpbi->biWidth;
			height = 600;//(short)lpbi->biHeight;
		}
		if (rect.right > width)
			rect.left = (rect.right - width )/2;//& (~0x3);
		if ((rect.bottom) > height)
			rect.top = (rect.bottom - height )/2;
	}
	
	//make offset x,y
	lSize = MAKELONG(rect.left, rect.top);
	rect.right = rect.left + min(800, rect.right);
	rect.bottom = rect.top + min(600, rect.bottom);
	
	//map to absolute screen rect
	//::MapWindowPoints(hWnd, HWND_DESKTOP, (LPPOINT)&rect, 2);
	MapWindowPoints((CWnd*)HWND_DESKTOP,(LPPOINT)&rect,2);
	
	if (m_MatchClient == 0) //need not to match client rect
		okSetTargetRect(hBoard, SCREEN, &rect);
	
	return lSize;
	
}

void CAnalysisTestDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
	InvalidateRect(NULL,TRUE);	
}


void CAnalysisTestDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	// TODO: Add your message handler code here
	lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
	InvalidateRect(NULL,TRUE);
}

void CAnalysisTestDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
//	CFrameWnd::OnSizing(fwSide, pRect);
	lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
	InvalidateRect(NULL,TRUE);
}

void CAnalysisTestDlg::OnMoving(UINT fwSide, LPRECT pRect) 
{
//	CFrameWnd::OnMoving(fwSide, pRect);
	lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
	InvalidateRect(NULL,FALSE);
}

void CAnalysisTestDlg::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	if(bActive == 1) 
	{//need to pause capturing 
		okStopCapture(hBoard);
		InvalidateRect(NULL,TRUE);
	}
}

void CAnalysisTestDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void CAnalysisTestDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CString path;
	CString first;   
	char *file = new char[3000];   
	memset(file,0,3000);//
	int   count = 0;   
	DWORD   MAXFILE = 3000*sizeof(char);   //3000   is   the   max   
	
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_HIDEREADONLY,
		"avi文件(*.avi)|*.avi|",this);   
	fileDialog.m_ofn.lpstrFile = file; 
    fileDialog.m_ofn.nMaxFile = MAXFILE;
 

	CString   str;   
	SYSTEMTIME  time;   
	::GetLocalTime   (&time);   
	str.Format   ("%d-%d-%d %d:%d:%d   ",time.wYear   ,time.wMonth   ,time.wDay   ,time.wHour   ,time.wMinute   ,time.wSecond   );   

	StrRecName myRecName;

	//
	CString strTmp;
	int iTmpIndex = 0;
	int iTmpLen = 0;
	
	if(fileDialog.DoModal()==IDOK)     
	{   
		POSITION   position;   
		position=fileDialog.GetStartPosition();   
		first=fileDialog.GetNextPathName(position);   

		//////////////////////////////////////////////////////////////////////////
		myAvi.ReadAviInfo(first);//
		myRecName.str_1 = "X";


		iTmpLen = myAvi.myAviInfo.strFileName.GetLength();
		iTmpIndex = myAvi.myAviInfo.strFileName.ReverseFind( '\\' );
		strTmp = myAvi.myAviInfo.strFileName.Right(iTmpLen-iTmpIndex-1);
		//

		myRecName.str_2.Format("%s",strTmp);
		myRecName.str_3.Format("%d",myAvi.myAviInfo.iTotalFrames);
		myRecName.str_4.Format("%d*%d",myAvi.myAviInfo.iWidth,myAvi.myAviInfo.iHeight);		
		myRecName.str_5.Format("%s",str);
		myRecName.str_6 = "";
		myRecName.str_7.Format("%s",myAvi.myAviInfo.strFileName);
		myRecName.str_8.Format("%f",myAvi.myAviInfo.fRate);

	
		m_mydatabase.FindDB("FileList_database.mdb");
		m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");//
		m_mydatabase.AddOneRecord(&myRecName);
		m_mydatabase.CloseDB();
		//////////////////////////////////////////////////////////////////////////

		while(position!=0)   
		{   
			count++;   
			path=fileDialog.GetNextPathName(position);   

			//////////////////////////////////////////////////////////////////////////
			myAvi.ReadAviInfo(path);//
			myRecName.str_1 = "X";
			

			iTmpLen = myAvi.myAviInfo.strFileName.GetLength();
			iTmpIndex = myAvi.myAviInfo.strFileName.ReverseFind( '\\' );
			strTmp = myAvi.myAviInfo.strFileName.Right(iTmpLen-iTmpIndex-1);
			//
			
			myRecName.str_2.Format("%s",strTmp);
			myRecName.str_3.Format("%d",myAvi.myAviInfo.iTotalFrames);

			myRecName.str_4.Format("%d*%d",myAvi.myAviInfo.iWidth,myAvi.myAviInfo.iHeight);	
			myRecName.str_5.Format("%s",str);
			myRecName.str_6 = "";
			myRecName.str_7.Format("%s",myAvi.myAviInfo.strFileName);
			myRecName.str_8.Format("%f",myAvi.myAviInfo.fRate);
			m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");
			m_mydatabase.AddOneRecord(&myRecName);
			m_mydatabase.CloseDB();
			//////////////////////////////////////////////////////////////////////////
   
		}   
		

	    m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");
		m_mydatabase.DisplayData("SELECT * FROM [data]",&m_FileNameList);
		m_mydatabase.CloseDB();
	}
	delete [] file;
}

void CAnalysisTestDlg::OnClickListFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	int iItem = -1;

    if((iItem = m_FileNameList.GetNextItem(-1, LVNI_SELECTED)) != -1)
	{
		myFileListData.strID=m_FileNameList.GetItemText(iItem,0);	
		myFileListData.str_1=m_FileNameList.GetItemText(iItem,8);
		myFileListData.str_2=m_FileNameList.GetItemText(iItem,2);
		myFileListData.str_3=m_FileNameList.GetItemText(iItem,3);
		myFileListData.str_4=m_FileNameList.GetItemText(iItem,4);
		myFileListData.str_5=m_FileNameList.GetItemText(iItem,5);
		myFileListData.str_6=m_FileNameList.GetItemText(iItem,6);
		myFileListData.str_7=m_FileNameList.GetItemText(iItem,7);
		myFileListData.str_8=m_FileNameList.GetItemText(iItem,1);


		m_NiSlide.Axis.Maximum = atoi(myFileListData.str_3);
	}
	else
	{
		myFileListData.strID="";
		myFileListData.str_1="";
		myFileListData.str_2="";
		myFileListData.str_3="";
		myFileListData.str_4="";
		myFileListData.str_5="";
		myFileListData.str_6="";
		myFileListData.str_7="";
		myFileListData.str_8="";
	}
	
	*pResult = 0;
}

void CAnalysisTestDlg::OnColumnclickListFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	
	CManeageList cList;
	cList.ClickCol_Sort(pNMListView);
	
	*pResult = 0;
}


void CAnalysisTestDlg::OnButDelFile() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "")
	{
		MessageBox("没有选择要删除的记录！",NULL,MB_OK);
		return;
	}
	else
	{
		CString strtmp = "索引";
		m_mydatabase.DelOneRecord(strtmp,myFileListData.strID,"FileList_database.mdb");
		

		m_mydatabase.FindDB("FileList_database.mdb");
		m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");//[data]
		m_mydatabase.RefreshIndex();
		m_mydatabase.CloseDB();
		
		//
		m_mydatabase.FindDB("FileList_database.mdb");
		m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");//[data]
		m_mydatabase.DisplayData("SELECT * FROM [data]",&m_FileNameList);
		m_mydatabase.CloseDB();
	}	
}


void CAnalysisTestDlg::OnButDelAll() 
{
	// TODO: Add your control notification handler code here
	
}

//
void CAnalysisTestDlg::OnButRefreash() 
{
	// TODO: Add your control notification handler code here
	m_mydatabase.FindDB("FileList_database.mdb");
	m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");//
	m_mydatabase.RefreshIndex();
	m_mydatabase.CloseDB();
	
	m_mydatabase.FindDB("FileList_database.mdb");
	m_mydatabase.ConnectDB("SELECT * FROM [data]","FileList_database.mdb");//
	m_mydatabase.DisplayData("SELECT * FROM [data]",&m_FileNameList);
	m_mydatabase.CloseDB();
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////



void CAnalysisTestDlg::OnButtonSingle() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "" || myFileListData.str_1 == "已处理")
	{
		MessageBox("没有选择要分析的记录！or 选择的记录已处理!",NULL,MB_OK);
		return;
	}
	else
	{		
		CString strSetCCDScale = "";
		GetDlgItemText(IDC_EDIT_CCD_SCALE,strSetCCDScale);
		g_dCCDScale = atof(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_UP_LEVEL,strSetCCDScale);
		g_iAreaUpLevel = atoi(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_DOWN_LEVEL,strSetCCDScale);
		g_iAreaDownLevel = atoi(strSetCCDScale);
		//add 2009.9.3
		GetDlgItemText(IDC_EDIT_BUFFER,strSetCCDScale);
		g_iReadBuffer = atoi(strSetCCDScale);

		if (g_dCCDScale == 0)
		{
			MessageBox("请设置CCD的参数后，重新点击step two!",NULL,MB_OK);
			return;
		}

		StrRecName* RecPARAM = new StrRecName;
		RecPARAM = &myFileListData;
		RecPARAM->iFlag = 0; //
		if (RecPARAM->bCount == FALSE)
		{
			RecPARAM->iCountA = 0;
			RecPARAM->iCountB = 0;
		}

		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,TRUE);

		GetLocalTime(&sysTimeBegin);
		lSysTime = GetTickCount();

		g_iRunningFlag = 100;
		hThread1 = CreateThread(NULL,0,ProcessProc,(LPVOID)RecPARAM,0,&threadID_1);
	}
}

DWORD WINAPI ProcessProc(LPVOID lpParameter)
{
	LPBYTE		lpLinear;
	DWORD		dwSize;
	
	
	CString strTmpFileName = ((StrRecName*)lpParameter)->str_7;

	CString strTmpID = ((StrRecName*)lpParameter)->strID;//
	//
	CString strTmpNameOnly = ((StrRecName*)lpParameter)->str_2;
	strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,strTmpNameOnly.GetLength()-4));
	CString strTmpPathOnly = ((StrRecName*)lpParameter)->str_7; 
	g_strFileName = strTmpPathOnly;
	strTmpPathOnly.Format("%s",strTmpPathOnly.Mid(0,((StrRecName*)lpParameter)->str_7.GetLength()-((StrRecName*)lpParameter)->str_2.GetLength()));

	
	
	CString strTmpTotalFrames = ((StrRecName*)lpParameter)->str_3;//
	int     iTmpFlag = ((StrRecName*)lpParameter)->iFlag;//
	int iNum = 0;
	int iBeginNum = 0;
	int iEndNum = 0;
	int iTotalFrames = atoi(strTmpTotalFrames);
	if (((StrRecName*)lpParameter)->bCount == TRUE)
	{
		iBeginNum = ((StrRecName*)lpParameter)->iCountA; //
		iEndNum   =	((StrRecName*)lpParameter)->iCountB; //	
		iTotalFrames = iEndNum -iBeginNum; //
		iNum = iBeginNum;
	}

	CString strTmpRate = ((StrRecName*)lpParameter)->str_8;//
	float fRate = atof(strTmpRate);


	//SaveFileName 2008.12.7
	CString strLocation = "";
	int iLocaBegin = 0; 	
	int iLocaEnd = 0;
	DWORD dwAttr;
	char chTmpFileName[256] = "\0";
	
	char fileName[256] = "\0";	 
	char edgeFileName[256] = "\0";
	char chSaveFileName[256] = "\0";
	int i = 0;
	int iTotalLeft=iTotalFrames;
	
	int iReadTimes = 0;
	CString strMessageBegin = "Begin To Process\r\n";
	CString strMessageLoad = "okLoadImageFile...\r\n";
	CString strMessageSave = "Saving Image...\r\n";
	CString strMessageSaveResults = "Please press the 'Save Results' button to acquire .mdb file.\r\n";
	CString strMessageEnd = "Congratulations!";
	char chTmpBinaryFile[256] = "\0";//
	char chTmpThinningFile[256] = "\0";//
	char chTmpSkeletonFile[256] = "\0";//
	char chTmpEdgeFile[256] = "\0";//
	CString strTmp;

	// 
	okStopCapture(hBoard);

	//
	short heightTemp;
	long strideTemp;
	CRect   rect;        // 
	int iReadBuffer = 0; //
	iReadBuffer = g_iReadBuffer;

	
	//
	int iAVIStride = 0,iAVIHeight = 0;
	CString strTmpSize = ((StrRecName*)lpParameter)->str_4;//
	CString strTmpStride,strTmpHeight;
	int iTmpGet = strTmpSize.Find('*');
	strTmpStride = strTmpSize.Left(iTmpGet);
	int iTmpLength = strTmpSize.GetLength();
	strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
	iAVIStride = atoi(strTmpStride);
	iAVIHeight = atoi(strTmpHeight);
	assert(iAVIStride != 0);//
	assert(iAVIHeight != 0);

	SetRect(&rect,0,0,iAVIStride,iAVIHeight);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
	
	if (iAVIStride > 800 && iAVIHeight >600)
	{
		SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
	}
	else
	{
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
	}

	char chStageFileName[255]="\0";
	int iIsErr;

	int *spp_iStatMemory = NULL;
	float *spp_fStatMemory = NULL;

	// Add by haining 2008.12.4	
	SYSTEMTIME currenttime;
	int m_itmpId = 0;
	int iChuli = 0;
	CAnalysisTestDlg* dlg;
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();
	//int nRetCode=0;
	int nTmpIndex = 0;


	//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	BOOL bWhile = TRUE;
	while (bWhile == TRUE)
	{
		if (bActive == 1)
		{
			if (iTmpFlag == 100)
			{
				//
			}
			else
			{
				//
				structEData.nImgOfProc=iTotalFrames;//
				myElegansFeatures.InitStructData(iAVIHeight,iAVIStride);
				myElegansFeatures.DoPretreatment.InitData(iAVIHeight,iAVIStride);
				myElegansFeatures.InitDataOfMove();
				
				//structEData.nImgOfProc=iTotalFrames;//
				
				//
				dpArray.RemoveAll();
				AddData();
										
				//2008.12.7
				sprintf(chStageFileName,"%s,mpg4.txt",strTmpFileName);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,iBeginNum,iEndNum);
				}
				else
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,0,iTotalFrames);
				}
				
				if (iIsErr == 1)
				{
					////g_strErrMes.Format("Can not find or open XY-stage coordinates!!!\r\n");
					memset(chTmpMsg,0,255*sizeof(char));
					sprintf(chTmpMsg,_T("Can not find or open XY-stage coordinates!!!\r\n\0"));
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}
				else if(iIsErr == -1)
				{
					return -1;
				}
				
				////g_strErrMes.Format("XY stage's coordinates is successfully reloaded!\r\n");
				sprintf(chTmpMsg,_T("XY stage's coordinates is successfully reloaded!\r\n\0"));
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				
				//
				////g_strErrMes.Format("像素与实际空间的换算比例是1个像素对应 %5f!\r\n",g_dCCDScale);
				sprintf(chTmpMsg,_T("像素与实际空间的换算比例是1个像素对应 %5f!\r\n\0"), g_dCCDScale);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);

				//VS-802B CCD
				//dCCD = 6.0;//um
				//dMagnification = 4.0 * 0.63;
				//g_dCCDScale = dCCD / dMagnification;				
				//AM1531 CCD
				//double dCCD = 6.45;//um
				//double dMagnification = 4.0 * 0.5;
				//g_dCCDScale = dCCD / dMagnification;				
				//g_dCCDScale = 6.32911;//um
				
				//
				structEData.fTime = (float)(1.0/fRate);
				structEData.structfRate = fRate;
				//Add by haining 2009.4.23
				g_dMaxMove = MaxMove * structEData.fTime;

				if (iTotalFrames != 0 && fRate != 0)
				{
					//Assume the largest Bodybends is 30 times/min;
					if (fRate <= 8.5)
					{
						g_iBodyBendsFilter = (int)((fRate * 60.0)/60.0);
					}
					else if (fRate > 8.5) 
					{
						g_iBodyBendsFilter = 2 + (int)((fRate * 60.0)/60.0);
					}		
				}

				
				if (spp_iStatMemory == NULL && spp_fStatMemory == NULL)
				{
					spp_iStatMemory = new int[iTotalFrames];//
					memset(spp_iStatMemory,0,iTotalFrames*sizeof(int));							
					spp_fStatMemory = new float[iTotalFrames];//
					memset(spp_fStatMemory,0,iTotalFrames*sizeof(float));
				}
				else
				{
					sprintf(chTmpMsg,_T("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n"));
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}
				
				GetLocalTime(&currenttime);
				nTmpIndex = 0;



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//2009.8.12
				//
				int iTemp814 = 0;
				for (iTemp814=1; iTemp814 < iTotalFrames; iTemp814++)
				{
					double iDeltaX = (double)(structEData.flatx[iTemp814] - structEData.flatx[iTemp814 - 1]);
					double iDeltaY = (double)(structEData.flaty[iTemp814] - structEData.flaty[iTemp814 -1]);
					if (iDeltaX != 0 || iDeltaY != 0)
					{
						structEData.IsUseful[iTemp814 - 1] = 0;
						structEData.IsUseful[iTemp814] = 0;
					}
				}

//2010.4.12 
				int iTemp412 = 0;
				for (iTemp412 = 1; iTemp412 < iTotalFrames; iTemp412++)
				{
					if (structEData.IsUseful[iTemp412] == 1)
					{
						if (structEData.IsUseful[iTemp412+1] == 0 || structEData.IsUseful[iTemp412+2] == 0 || structEData.IsUseful[iTemp412+3] == 0)
						{
							structEData.IsUseful[iTemp412] = 0;
						}
					}
				}

// 2009.8.12
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//single
				sprintf(chTmpMsg,strMessageBegin);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				iTotalLeft=iTotalFrames;
				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				iNum = 0;
				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
				}				
				
				// 
				sprintf(chSaveFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chSaveFileName);//
				if(dwAttr == 0xFFFFFFFF)   //
					CreateDirectory(chSaveFileName,NULL);

				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					
					sprintf(fileName,"%s%s.avi",strTmpPathOnly,strTmpNameOnly);
					//step one 
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Binary.avi",chSaveFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
				{
					sprintf(fileName,"%s%s.avi",strTmpPathOnly,strTmpNameOnly);
					//step one 
					sprintf(chSaveFileName,"%s\\%s-all-8Binary.avi",chSaveFileName,strTmpNameOnly);
				}

				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);
				g_strFileName = fileName;

				//////////////////////////////////////////////////////////////////////////
				//try opencv read avi
				//CvCapture* cap;
				//cap = cvCreateFileCapture(fileName);
				//cvQueryFrame(cap);



				


			   //////////////////////////////////////////////////////////////////////////

				if (gDlg->m_ChooseForStepOne == TRUE )
				{
					//
					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
					okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStride = lStride_ch3 / 3;
					lStride = (long)(lStride * g_fBinningFlag);
					lHeight = (long)(lHeight * g_fBinningFlag);
					cvPFrameMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
					cvPFrMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
					cvPBkMat = cvCreateMat(lHeight, lStride, CV_32FC1);
				}


				CTime day;
				day=CTime::GetCurrentTime();
				int filehour,filemin,filesec;
				filehour = day.GetHour();//hh
				filemin=day.GetMinute();//mm
				filesec=day.GetSecond();//ss
				g_strImgWindowName.Format("Image-%s(%02d:%02d:%02d)",strTmpNameOnly,filehour,filemin,filesec);

				//tmp 2009-4-8
				//Save the results in the form of AVI movie
				g_cvSavImg = cvCreateImage(cvSize(lStride,lHeight),8,1);
				g_cvColorImg = cvCreateImage(cvSize(lStride,lHeight),8,3);
				//cvZero(g_cvColorImg);??
				cvSet(g_cvColorImg,cvScalarAll(0),0);
				cvZero(g_cvSavImg);
				g_cvSavVideo = cvCreateAVIWriter(chSaveFileName, -1, (double)fRate , cvSize(lStride,lHeight) , 1);
				for(;;)
				{
					if (iTotalLeft <= 0 || bActive == 0)
					{	
						okStopCapture(hBoard);
						InvalidateRect(NULL,NULL,TRUE);
						iNum = 0;
						break;
					}
					if (iTotalLeft >= iReadBuffer) 
					{
						iTotalLeft = iTotalLeft-iReadBuffer;
						// 
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	
						
						//////////////////////////////////////////////////////////////////////////
						// 一
						for(i=0;i<iReadBuffer;i++)
						{
							//
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
							lStrideRed = lStride_ch3 / 3;
							lStride = lStrideRed;
							
							lStride = (long)(lStride * g_fBinningFlag);
							lHeight = (long)(lHeight * g_fBinningFlag);
							
							//
							myElegansFeatures.SpecialExtraction_3channel(structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);

							cvWriteToAVI(g_cvSavVideo,g_cvColorImg);

							iNum+=1;
							
							//
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
						//
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
						//	,BUFFER,0,iReadBuffer);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						memset(lpLinear, 255, dwSize);
						
						iReadTimes += 1;
					}
					if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
					{
						//
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);
						
						//////////////////////////////////////////////////////////////////////////
						// 二
						for(i=0;i<iTotalLeft;i++)
						{
							//
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
							lStrideRed = lStride_ch3 / 3;
							lStride = lStrideRed;
							
							lStride = (long)(lStride * g_fBinningFlag);
							lHeight = (long)(lHeight * g_fBinningFlag);

							//
							myElegansFeatures.SpecialExtraction_3channel(structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);

							cvWriteToAVI(g_cvSavVideo,g_cvColorImg);
							iNum+=1;
							
							//
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}							

						//
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
						//	,BUFFER,0,iTotalLeft);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						memset(lpLinear, 255, dwSize);

						iReadTimes += 1;
						iTotalLeft = 0;
					}
				}//

				cvReleaseVideoWriter(&g_cvSavVideo);
				
				//
				::PostMessage(hWnd,WM_GET_TIME,0,0);
				bActive = 0;
				iNum = 0;  
				
/*
				sprintf(chTmpMsg,_T("Congratulations!"));
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

				if (structEData.path != NULL)
					myElegansFeatures.DestroyStructData();//
*/


				if (cvPFrameMat != NULL)
				{
					//
					cvReleaseMat(&cvPFrameMat);
					cvReleaseMat(&cvPFrMat);
					cvReleaseMat(&cvPBkMat);	
				}
				
				if (g_cvSavImg != NULL && g_cvColorImg != NULL)
				{
					//release saving image
					cvReleaseImage(&g_cvSavImg);
					cvReleaseImage(&g_cvColorImg);
					g_cvSavImg = NULL;
					g_cvColorImg = NULL;
				}


				bActive = 1;
				iTotalLeft=iTotalFrames;
				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				iNum = 0;
		
				sprintf(chTmpMsg,_T("Invalid frames algorithm is acting...\r\n"));
				////g_strErrMes.Format("Invalid frames algorithm is acting...\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				memcpy(spp_iStatMemory,structEData.iWormAera,iTotalFrames*sizeof(int));
				myElegansFeatures.StatBubbleSort(spp_iStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_iStatMemory,iTotalFrames);
				
				int iCompare = 0;
				double dJudge = 0;
				int iNanCnt = 0;//
				char chErr[256]="/0";
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.iWormAera[iNum]));
					
					dJudge = 0.4 * myElegansFeatures.STDATA[3];
					
					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUsefulImage[iNum] = 0;
						}
					}   
					else if(structEData.IsUseful[iNum] == 0)
					{
						structEData.IsUsefulImage[iNum] =0;
					}
				}//
				

				memcpy(spp_fStatMemory,structEData.Slength,iTotalFrames*sizeof(float));
				myElegansFeatures.StatBubbleSort(spp_fStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_fStatMemory,iTotalFrames);
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.Slength[iNum]));
					
					dJudge = 0.4 * myElegansFeatures.STDATA[3];
					
					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUsefulImage[iNum] = 0;
							iNanCnt += 1;
						}
					}
					else if(structEData.IsUseful[iNum] == 0)
					{
						structEData.IsUsefulImage[iNum] = 0;
						iNanCnt += 1;//
					}                    
				}//
				
				structEData.InvFraRat = (float)iNanCnt / (float)iTotalFrames;
				//
				sprintf(chTmpMsg,_T("总共%d帧，有效帧%d,丢弃%d帧!\r\n"),iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				////g_strErrMes.Format("总共%d帧，有效帧%d,丢弃%d帧!\r\n",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				if ( structEData.InvFraRat >= 0.3 && iNanCnt != 0)
				{
					sprintf(chErr,"总共%d帧，有效帧%d,丢弃%d帧，丢帧超30%请放弃此数据!",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
					AfxMessageBox(chErr,NULL,MB_OK);
					//
					::PostMessage(hWnd,WM_GET_TIME,0,0);
					bActive = 0;
					iNum = 0;  
					okStopCapture(hBoard);
					InvalidateRect(NULL,NULL,TRUE);
					delete [] spp_iStatMemory;
					delete [] spp_fStatMemory;
					spp_iStatMemory = NULL;
					spp_fStatMemory = NULL;
					myElegansFeatures.DestroyStructData();
					return -1; //
				}//	
			

				structEData.ed_faFrameDetail[0] = (float)iTotalFrames;//
				structEData.ed_faFrameDetail[1] = (float)iTotalFrames-iNanCnt;
				structEData.ed_faFrameDetail[2] = (float)structEData.InvFraRat;//
				structEData.ed_faFrameDetail[3] = (float)structEData.structfRate;//
				structEData.ed_faFrameDetail[4] = (float)lStride  * (int)(1/g_fBinningFlag);//
				structEData.ed_faFrameDetail[5] = (float)lHeight * (int)(1/g_fBinningFlag);

				//
				g_iFlagSpecial = 3;
				g_iFlagSpecial = 4;
				


				//////////////////////////////////////////////////////////////////////////
				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
				}				
				sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chTmpFileName);//
				if(dwAttr == 0xFFFFFFFF)   //
					CreateDirectory(chTmpFileName,NULL);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					//step one 
					//sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
					//
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
				{
					//step one 
					//sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
					sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
					//
					sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
				}
				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);
				g_strFileName = fileName;

				if (g_iFlagSpecial == 4)
				{
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;
					//int nRetCode=0;

					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);	
					structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStrideRed = lStride_ch3 /3;
					lStride = lStrideRed;

					lStride = (long)(lStride * g_fBinningFlag);
					lHeight = (long)(lHeight * g_fBinningFlag);

					
					myElegansFeatures.HeadAndTailExtraction(fileName,lHeight,lStride);


				}//if (g_iFlagSpecial == 4)
				//////////////////////////////////////////////////////////////////////////

				g_iFlagSpecial = 5;

				sprintf(chTmpMsg,_T("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n"));
				////g_strErrMes.Format("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
//④Feature Extraction
				if (g_iFlagSpecial == 5)
				{

					//////////////////////////////////////////////////////////////////////////
					//
					iNum = 0;
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0) 
						{
							myElegansFeatures.GetSampleSkeleton(iNum);
						}
					}
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// Locomotion
					iNum = 0;
					for(iNum=1;iNum<iTotalFrames;iNum++)
					{
						//edit 2009.8.15
						myElegansFeatures.GetParaExtraction(iNum);
						if (structEData.IsUseful[iNum] != 0) 
						{
							
						}
						else
						{
							structEData.m_iTimeCnt01s += 1;
							structEData.m_iTimeCnt02s += 1;
							structEData.m_iTimeCnt05s += 1;
							structEData.m_iTimeCnt10s += 1;
							structEData.m_iTimeCnt30s += 1;
							structEData.m_iTimeCnt60s += 1;
						}

					}
					myElegansFeatures.StatParaOfMove();
					// end of 'Locomotion'
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					//
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							structEData.AREA[iNum] = (structEData.iWormAera[iNum] *g_dCCDScale*g_dCCDScale) / 1000000.0;//mm^2 
							structEData.BODYSIZE[iNum] = (structEData.dianECnt[iNum] * g_dCCDScale) / 1000.0;  //mm
							//structEData.BODYWIDTH[iNum] = 0;  
							structEData.BODYLENGTH[iNum] = (structEData.Slength[iNum] *g_dCCDScale) / 1000.0;//mm
						}
					}
					
					int iVaCount = 0;
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							//
							structEData.AREA_VALID[iVaCount] = structEData.iWormAera[iNum];
							structEData.BODYLENGTH_VALID[iVaCount] = structEData.Slength[iNum];
							structEData.BODYSIZE_VALID[iVaCount] = structEData.dianECnt[iNum];
							iVaCount++;
						}
					}
					//					
					myElegansFeatures.StatBubbleSort(structEData.AREA_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.AREA_VALID,iVaCount);
					structEData.AREA_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.000001;//mm^2
					
					myElegansFeatures.StatBubbleSort(structEData.BODYLENGTH_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYLENGTH_VALID,iVaCount);
					structEData.BODYLENGTH_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm
					
					myElegansFeatures.StatBubbleSort(structEData.BODYSIZE_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYSIZE_VALID,iVaCount);
					structEData.BODYSIZE_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm
					// end of
					//////////////////////////////////////////////////////////////////////////

					for(iNum=1;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] == 0)
						{
							structEData.ed_dpBodywaveStride[iNum]  = -1;
							structEData.ed_dpBodywaveHeight[iNum] = -1;
						}
						else 
						{
							double d1 = 0., d2 = 0., dtmp = 0.;
							int iNumPre = iNum;
							for (;;)
							{
								// find prior waveStride which is useful;
								iNumPre = iNumPre - 1;
								if (structEData.ed_dpBodywaveStride[iNumPre] != -1 ) break;								
							}

							// 
							d1 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveStride[iNumPre]);
							d2 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveHeight[iNumPre]);
							if (d1 > d2)
							{
								// exchange the wave stride and height;
								dtmp = structEData.ed_dpBodywaveStride[iNum];  
								structEData.ed_dpBodywaveStride[iNum] = structEData.ed_dpBodywaveHeight[iNum];  
								structEData.ed_dpBodywaveHeight[iNum] = dtmp;
								if (structEData.ed_dpBodywaveHeight != 0)
								{
									structEData.ed_dpBodywaveSToH[iNum] = 
										structEData.ed_dpBodywaveStride[iNum] / structEData.ed_dpBodywaveHeight[iNum];
								}
							}

							// Normalize the wave by the worm's length
							structEData.ed_dpBodywaveHeightNormal[iNum] = 
								structEData.ed_dpBodywaveHeight[iNum] / (1000 * structEData.BODYLENGTH_3M);
							structEData.ed_dpBodywaveStrideNormal[iNum] = 
								structEData.ed_dpBodywaveStride[iNum] / (1000 *structEData.BODYLENGTH_3M);
						}
					}

					//2009.4.24
					int iUseNumTmp = 0; //
					double *dWaveStride = new double[structEData.nImgOfProc*sizeof(double)];
					double *dWaveHeight = new double[structEData.nImgOfProc*sizeof(double)];
					memset(dWaveStride,0,structEData.nImgOfProc*sizeof(double));
					memset(dWaveHeight,0,structEData.nImgOfProc*sizeof(double));
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							dWaveStride[iUseNumTmp] = structEData.ed_dpBodywaveStrideNormal[iNum];
							dWaveHeight[iUseNumTmp] = structEData.ed_dpBodywaveHeightNormal[iNum];
							structEData.ed_xTime[iUseNumTmp] = structEData.fTime * iNum;
							iUseNumTmp += 1;
						}
					}
					memcpy(structEData.ed_dpBodywaveStrideNormal, dWaveStride, structEData.nImgOfProc*sizeof(double));
					memcpy(structEData.ed_dpBodywaveHeightNormal, dWaveHeight, structEData.nImgOfProc*sizeof(double));

					//
					myElegansFeatures.StatBubbleSort(dWaveHeight,iUseNumTmp);
					myElegansFeatures.StatTPM(dWaveHeight,iUseNumTmp);
					structEData.ed_dpBodywaveHeightNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveHeightNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveHeightNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					myElegansFeatures.StatBubbleSort(dWaveStride,iUseNumTmp);					
					myElegansFeatures.StatTPM(dWaveStride,iUseNumTmp);
					structEData.ed_dpBodywaveStrideNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveStrideNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveStrideNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					delete [] dWaveHeight;
					delete [] dWaveStride;
					dWaveHeight = NULL;
					dWaveStride = NULL;
					//
					//////////////////////////////////////////////////////////////////////////

				}			

//Modified by 2009.9.4

				//////////////////////////////////////////////////////////////////////////
				//Create Save File name and path 2009.4.24
				g_iFlagSpecial = 8;
				if (g_iFlagSpecial == 6)
				{
					iLocaBegin = strTmpPathOnly.Find('\\',4);
					iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
					strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
					if (strLocation == "")
					{
						strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
					}				
					sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
					dwAttr = GetFileAttributes(chTmpFileName);//
					if(dwAttr == 0xFFFFFFFF)   //
						CreateDirectory(chTmpFileName,NULL);


					if (((StrRecName*)lpParameter)->bCount == TRUE)
					{
						//step one 
						//sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
						//
						sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					}
					else
					{
						//step one 
						//sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
						sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
						//
						sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
					}


					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					g_strFileName = fileName;

					bActive = 1;
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;

					//Save the results in the form of AVI movie
					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
					okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStride = lStride_ch3 /3;
					lStrideRed = lStride;
					g_cvSavImg = cvCreateImage(cvSize(lStride,lHeight),8,3);
					g_cvColorImg = cvCreateImage(cvSize(lStride,lHeight),8,3);

					cvSet(g_cvColorImg,cvScalarAll(0),0);
					//cvZero(g_cvSavImg);
					cvSet(g_cvSavImg,cvScalarAll(0),0);
					CvVideoWriter* cvSavVideoFinal; 
					cvSavVideoFinal = cvCreateAVIWriter(chSaveFileName,0, (double)fRate , cvSize(lStride,lHeight) ,1);
					for(;;)
					{
						if (iTotalLeft <= 0 || bActive == 0)
						{	
							okStopCapture(hBoard);
							InvalidateRect(NULL,NULL,TRUE);
							iNum = 0;
							break;
						}
						if (iTotalLeft >= iReadBuffer) 
						{
							iTotalLeft = iTotalLeft-iReadBuffer;
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	

							//////////////////////////////////////////////////////////////////////////
							// 一
							for(i=0;i<iReadBuffer;i++)
							{
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
								lStrideRed = lStride_ch3 /3;
								lStride = lStrideRed;

								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(cvSavVideoFinal,g_cvSavImg);
								iNum+=1;

								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}
							
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
							//	,BUFFER,0,iReadBuffer);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
						}
						if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						{
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);

							//////////////////////////////////////////////////////////////////////////
							// 二
							for(i=0;i<iTotalLeft;i++)
							{
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
								lStrideRed = lStride_ch3 /3;
								lStride = lStrideRed;

								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(cvSavVideoFinal,g_cvSavImg);
								iNum+=1;

								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}							

							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
							//	,BUFFER,0,iTotalLeft);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
							iTotalLeft = 0;
						}
					}
				
					//Sleep(500);
					cvReleaseVideoWriter(&cvSavVideoFinal);
					if (g_cvSavImg != NULL && g_cvColorImg != NULL)
					{
						//release saving image
						cvReleaseImage(&g_cvSavImg);
						cvReleaseImage(&g_cvColorImg);
						g_cvSavImg = NULL;
						g_cvColorImg = NULL;
					}
				}			
				//////////////////////////////////////////////////////////////////////////


				okStopCapture(hBoard);
				InvalidateRect(NULL,NULL,TRUE);
				bWhile = FALSE;
				
				sprintf(chTmpMsg,_T("Congratulations!"));
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

				//if (structEData.path != NULL)
				//	myElegansFeatures.DestroyStructData();//

			} // end -- else
		} //end -- if (bActive == 1)
	} //end -- while (bWhile == TRUE) 


	delete [] chTmpMsg;
	chTmpMsg = NULL;
	return 0;
}

DWORD WINAPI ReviewProc(LPVOID lpParameter)
{


//	WaitForSingleObject(hThread2,10);
	CString strTmpID = ((StrRecName*)lpParameter)->strID;

	//
	CString strTmpNameOnly = ((StrRecName*)lpParameter)->str_2;
	strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,strTmpNameOnly.GetLength()-4));
	//
	CString strTmpFileName = ((StrRecName*)lpParameter)->str_7;
	CString strTmpTotalFrames = ((StrRecName*)lpParameter)->str_3;
	int     iTmpReverseFlag = ((StrRecName*)lpParameter)->iFlag;
	
	char fileName[256] = "\0";
	//int iTotalFrames = atoi(strTmpTotalFrames);
	int i = 0;
	int iNum = 0;//((StrRecName*)lpParameter)->iCountA; //
	int iBeginNum = 0;
	int iEndNum = 0;
	int iTotalFrames = atoi(strTmpTotalFrames);
	if (((StrRecName*)lpParameter)->bCount == TRUE)
	{
		iBeginNum = ((StrRecName*)lpParameter)->iCountA; //
		iEndNum   =	((StrRecName*)lpParameter)->iCountB; //	
		iTotalFrames = iEndNum -iBeginNum; //
		iNum = iBeginNum;
	}
	int iTotalLeft=iTotalFrames;
	int iReadBuffer = 0; //
	iReadBuffer = g_iReadBuffer;
	
	CString strMessageLoad = "正在读取硬盘文件...\r\n";
	
	//
	okStopCapture(hBoard);
	sprintf(fileName,strTmpFileName);

	//640x480
	short heightTemp;
	long strideTemp;
	CRect   rect;        // 
	//
	int iAVIStride = 0,iAVIHeight = 0;
	CString strTmpSize = ((StrRecName*)lpParameter)->str_4;//
	CString strTmpStride,strTmpHeight;
	int iTmpGet = strTmpSize.Find('*');
	strTmpStride = strTmpSize.Left(iTmpGet);
	int iTmpLength = strTmpSize.GetLength();
	strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
	iAVIStride = atoi(strTmpStride);
	iAVIHeight = atoi(strTmpHeight);
	assert(iAVIStride != 0);//
	assert(iAVIHeight != 0);
	
	SetRect(&rect,0,0,iAVIStride,iAVIHeight);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
	
	myElegansFeatures.InitStructData(iAVIHeight,iAVIStride);

	if (iAVIStride > 800 && iAVIHeight >600)
	{
		SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
	}
	else
	{
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
	}

	okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
	okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//
	
	//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	while (TRUE)
	{
		if (bActive == 1)
		{
			if (iTmpReverseFlag == 100)
			{

			}
			else
			{
				//
				for(;;)
				{
					if (iTotalLeft <= 0 || bActive == 0)
					{	
						okStopCapture(hBoard);
						InvalidateRect(NULL,NULL,TRUE);
						iNum = 0;
						break;
					}
					if (iTotalLeft >= iReadBuffer) 
					{
						iTotalLeft = iTotalLeft-iReadBuffer;
						//memset(chTmpMsg, 0, 255*sizeof(char));
						//sprintf(chTmpMsg, _T("zhengzai!\r\n"));
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);

			
						for(i=0;i<iReadBuffer;i++)
						{
							Sleep(15);
							if (!IsIconic(hWnd))
							{
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								if (lHeight > 800 && lStride > 600) 
								{
									myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
									//get image to app buffer from tgt
									g_blk.lpBits = structEData.lpHalf;			
									g_blk.iWidth = (short)(lStride*0.5);
									g_blk.iHeight = (short)(lHeight*0.5); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStride * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
								}
								else
									okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
							}
							iNum+=1;
					
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
					}
					if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
					{
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);
						
						for(i=0;i<iTotalLeft;i++)
						{
							Sleep(15);
							if (!IsIconic(hWnd))
							{
							
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								if (lHeight > 800 && lStride > 600) 
								{
									//特殊处理 若图像大于800*600，则缩小1/4显示
									myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
									//get image to app buffer from tgt
									g_blk.lpBits = structEData.lpHalf;			
									g_blk.iWidth = (short)(lStride*0.5);
									g_blk.iHeight = (short)(lHeight*0.5); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStride * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
								}
								else
									okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
							}
							iNum+=1;
							// 发送自定义消息，使进度条得以更新；
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
						iTotalLeft = 0;
					}
				}
			}			

			bActive = 0;
			iNum = 0;  
			okStopCapture(hBoard);
			InvalidateRect(NULL,NULL,TRUE);
		}
	}
	
	if (structEData.path != NULL)
		myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
	okStopCapture(hBoard);
	InvalidateRect(NULL,NULL,TRUE);

	delete [] chTmpMsg;
	chTmpMsg = NULL;
	return 0;
}

//分析处理线程 和 回放记录线程
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//回放记录 模块

//开始回放，若没有选中任一记录，则从记录1开始回放至最后一个记录
void CAnalysisTestDlg::OnButReview() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "")
	{
		MessageBox("没有选择要回放的记录！",NULL,MB_OK);
		return;
	}
	else
	{
		StrRecName* RecPARAM = new StrRecName;
		RecPARAM = &myFileListData;
		RecPARAM->iFlag = 0; //备用标志用于回放时，0代表正向回放，100代表逆向回放
		RecPARAM->iCountA = m_NiPreEditNum.GetValue();
		hThread2 = CreateThread(NULL,0,ReviewProc,(LPVOID)RecPARAM,0,&threadID_2);
		//CloseHandle(hThread2);
		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,FALSE);
	}
}



void CAnalysisTestDlg::OnButReviewStop() 
{
	// TODO: Add your control notification handler code here
	bActive = 0;
	
	okStopCapture(hBoard);
	InvalidateRect(NULL,FALSE);
	//	TerminateThread(hThread1,GetExitCodeThread(hThread1,&threadID));
	//clear buffer 0
	LPBYTE	 lpLinear;
	DWORD	 dwSize;	
	//okGetAvailBuffer(&lpLinear,&dwSize);
	okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);
	memset(lpLinear, 255, dwSize);
	
	::TerminateThread(hThread2,GetExitCodeThread(hThread2,&threadID_2));
	CloseHandle(hThread2);
	m_NiPreEditNum.SetValue(0);
	m_NiSlide.SetValue(0);

	if (structEData.path != NULL)
		myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
	ZeroMemory(&g_blk,sizeof(BLOCKINFO));

	m_strMessage = "";
	UpdateData(FALSE);
}

void CAnalysisTestDlg::OnButPreviewSign() 
{
	// TODO: Add your control notification handler code here
	CString s;
	m_previewBtn.GetWindowText(s);
	if(s == "Preview Off")
	{
		m_NiPreEditNum.SetValue(0);
		m_NiSlide.SetValue(0);
		m_previewBtn.SetWindowText("Preview is On");
		bPreview = 1;
		GetDlgItem(IDC_BUT_SAVE_BMP)->EnableWindow(TRUE);
	}
	else
	{
		m_previewBtn.SetWindowText("Preview Off");
		bPreview = 0;
		GetDlgItem(IDC_BUT_SAVE_BMP)->EnableWindow(FALSE);
	}
}

//逆向回放记录
void CAnalysisTestDlg::OnButReviewReverse() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "")
	{
		MessageBox("Please select a movie！",NULL,MB_OK);
		return;
	}
	else
	{
		StrRecName* RecPARAM = new StrRecName;
		RecPARAM = &myFileListData;
		RecPARAM->iFlag =100;
		hThread2 = CreateThread(NULL,0,ReviewProc,(LPVOID)RecPARAM,0,&threadID_2);
		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,FALSE);
	}
}

//在回放时导出一帧BMP,保存为8bit位图
void CAnalysisTestDlg::OnButSaveBmp() 
{
	// TODO: Add your control notification handler code here
	char fileName[256] = "\0";
	//
	CString strTmpNameOnly="";
	CString strTmpPathOnly="";
	strTmpNameOnly += myFileListData.str_2;
	strTmpPathOnly += myFileListData.str_7;

    okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
	okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//设置SCREEN为8位

	if (myFileListData.strID != "" && bPreview == 1) 
	{
		strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,myFileListData.str_2.GetLength()-4));
		strTmpPathOnly.Format("%s",strTmpPathOnly.Mid(0,myFileListData.str_7.GetLength()-myFileListData.str_2.GetLength()));
		sprintf(fileName,myFileListData.str_7);		
		okLoadImageFile(hBoard,fileName,m_NiPreEditNum.GetValue(),SCREEN,0,1);//直接读取当前帧到SCREEN
		LPARAM lpNo = MAKELONG(1,1);
		okConvertRect(hBoard,BUFFER,0,SCREEN,0,lpNo);//通过设置转换参数，将当前帧转为8bit到BUFFER
		int i = m_NiPreEditNum.GetValue();
		sprintf(fileName,"%s%s-[%d].BMP",strTmpPathOnly,strTmpNameOnly,i);
		okSaveImageFile(hBoard,fileName,0,BUFFER,0,1);
		MessageBox("当前帧图像已保存到选定记录的路径下！！！",NULL,MB_OK);
	}	
}

//回放记录 模块
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//自定义消息响应 模块

LRESULT CAnalysisTestDlg::OnEditDatabase(WPARAM wParam,LPARAM lParam)
{
	CString mID;
	int iID = wParam;
	mID.Format("%d",iID);
	CString *strState = (CString *) lParam;
	CString strTmpSQL = "";
	COleVariant var_state;
	//连接数据库并显示记录
	CIBBDaoDatabase dbTmp;
	dbTmp.FindDB("FileList_database.mdb");						
	strTmpSQL.Format("%s%s","SELECT * FROM [data] WHERE 索引=",mID);
	dbTmp.ConnectDB(strTmpSQL,"FileList_database.mdb");//[data]指数据库中表的名称
	//写入数据库前的类型转换
	var_state=COleVariant(*strState,VT_BSTRT);						
	//调用DAO基类的编辑函数
	dbTmp.RecSet->Edit();						
	//注意Edit的时候不能再次重写关键字段，如索引,否则会产生Assert错误；
	dbTmp.RecSet->SetFieldValue("状态",var_state);						
	dbTmp.RecSet->Update();		
	//dbTmp.DisplayData("SELECT * FROM [data]",&m_FileNameList);
	dbTmp.CloseDB();

	return 0;
}

//头尾人工识别对话框
LRESULT CAnalysisTestDlg::OnGetHeadMessage(WPARAM wParam, LPARAM lParam)
{
	CChosseHead dlgHead(this);
	dlgHead.iTmpImageNum = (int)wParam;
	dlgHead.iTmpDataNum = (int)lParam;
	int nRetCode=dlgHead.DoModal(); //显示线虫头部选择对话框
	bFlagGoOn = TRUE;

	return 0;
}

//分析进度条更新
LRESULT CAnalysisTestDlg::OnAnalysisProgress(WPARAM wParam, LPARAM lParam)
{
	m_NiProgress.Value+=1;//刷新进度条

	return 0;
}

//回放进度条更新
LRESULT CAnalysisTestDlg::OnPlayBackProgress(WPARAM wParam, LPARAM lParam)
{
	int iTmp=wParam;
	m_NiSlide.SetValue(iTmp);//刷新进度条
	m_NiPreEditNum.SetValue(iTmp);

	return 0;
}

//任务进度提示更新
LRESULT CAnalysisTestDlg::OnProgressMessage(WPARAM wParam, LPARAM lParam)
{
	//CString *strTmp = (CString *)lParam;
	char *chtmp = new char[255*sizeof(char)];
	memset(chtmp,0,255*sizeof(char));
	chtmp = (char *) lParam;
	long x=0;
	//x = m_strMessage.GetLength();
	//Edit by haining 2008.12.3
	//CString的长度是有限制的，MSDN里是INT_MAX=2147483647，但实际操作中不明确
	//if (x<= 20000) //2147483647
	//if(x <= 5000) //减少大小，尝试是否能减少出错的可能？？2009.4.24
	//{
		//::TerminateThread(hThread3,GetExitCodeThread(hThread3,&threadID_3));
		//CloseHandle(hThread3);
		//MessageBox("haha",MB_OK);
		m_strMessage += chtmp;
		UpdateData(FALSE);
		m_ctrEditMessage.LineScroll(m_ctrEditMessage.GetLineCount(),0);
//	}
/*
	else
	{
		m_strMessage = "";
		CString strxxx;
		strxxx.Format("信息字符数超过20000个character");
		m_strMessage += strxxx;
		UpdateData(FALSE);
		m_ctrEditMessage.LineScroll(m_ctrEditMessage.GetLineCount(),0);
	}
*/
	
	//SetWindowText(m_strMessage);
    
	return 0;
}

//获取分析耗时
LRESULT CAnalysisTestDlg::OnGetTimeMessage(WPARAM wParam,LPARAM lParam)
{
	//int x = wParam;

	lSysTime = GetTickCount() - lSysTime;
	GetLocalTime(&sysTimeEnd);
	//获取当前系统日期和时间
	CString   str;
	long lTmpOne = sysTimeBegin.wHour * 3600 +  sysTimeBegin.wMinute * 60 + sysTimeBegin.wSecond;
	long lTmpTwo = sysTimeEnd.wHour * 3600 +  sysTimeEnd.wMinute * 60 + sysTimeEnd.wSecond;
	
	str.Format("分析耗时 %ds\r\n",lTmpTwo - lTmpOne); 
	m_strMessage += str;

	str.Format("%d ms\r\n",lSysTime);
	m_strMessage += str;
	UpdateData(FALSE);
	
	return 0;
}
//自定义消息响应 模块
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//分析处理 模块

//帧数设置，即从第几帧分析到第几帧
void CAnalysisTestDlg::OnButProcessFrames() 
{
	// TODO: Add your control notification handler code here
	CString s;
	m_btnProcessFrameZone.GetWindowText(s);
	if(s == "Select Frm")
	{
		m_NiPreEditNum.SetValue(0);
		m_NiSlide.SetValue(0);
		m_btnProcessFrameZone.SetWindowText("Frm Set");
		myFileListData.bCount = TRUE;
		myFileListData.iCountA = m_NiBeginFrame.Value;
		myFileListData.iCountB = m_NiEndFrame.Value;
		m_NiSlide.SetValue(m_NiBeginFrame.Value);
	}
	else
	{
		m_btnProcessFrameZone.SetWindowText("Select Frm");
		myFileListData.bCount = FALSE;
	}
	
}

//分析属性设置
void CAnalysisTestDlg::OnButProcessProperty() 
{
	// TODO: Add your control notification handler code here
	
}

//删除缓存数据
void CAnalysisTestDlg::OnButDelBufferAvi() 
{
	// TODO: Add your control notification handler code here
	
}

//批量分析
void CAnalysisTestDlg::OnButBatch() 
{
	// TODO: Add your control notification handler code here
	
}

//停止分析
void CAnalysisTestDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	bActive = 0;

	okStopCapture(hBoard);
	InvalidateRect(NULL,FALSE);
	//	TerminateThread(hThread1,GetExitCodeThread(hThread1,&threadID));
	//clear buffer 0
	LPBYTE	 lpLinear;
	DWORD	 dwSize;
	
	//okGetAvailBuffer(&lpLinear,&dwSize);
	okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);
	memset(lpLinear, 255, dwSize);

	if (g_iRunningFlag == 100)
	{

		if (g_iImageFlag != 0)
		{
			//add by haining 2010.3.10
			//消除bug-----stop操作后，重新single分析时没有中间图像处理结果回显
			cvDestroyWindow( g_strImgWindowName ); // 销毁窗口
			g_iImageFlag = 0;
		}


		g_iRunningFlag = 0;

		if(hThread1 != NULL)
		{
			::TerminateThread(hThread1,GetExitCodeThread(hThread1,&threadID_1));
			CloseHandle(hThread1);
			hThread1 = NULL;
		}


		if(hThread3 != NULL)
		{
			//扩展特殊功能分析
			::TerminateThread(hThread3,GetExitCodeThread(hThread3,&threadID_3));
			CloseHandle(hThread3);
			hThread3 = NULL;
		}

		if(hThread4 != NULL)
		{
			::TerminateThread(hThread4,GetExitCodeThread(hThread4,&threadID_4));
			CloseHandle(hThread4);
			hThread4 = NULL;
		}

		if(hThread5 != NULL)
		{
			::TerminateThread(hThread5,GetExitCodeThread(hThread5,&threadID_5_new));
			CloseHandle(hThread5);
			hThread5 = NULL;
		}
	}


	m_NiBeginFrame.SetValue(0);
	m_NiEndFrame.SetValue(0);

	m_strMessage = "";

	//每处理完一个数据，释放占用内存
	if (structEData.path != NULL)
	{
		myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
	}
	if (myElegansFeatures.DoPretreatment.C != NULL)
	{
		myElegansFeatures.DoPretreatment.DestroyData();
	}
	if (myElegansFeatures.DoParadistill.m_hAglRate != NULL)
	{
		myElegansFeatures.DestroyDataOfMove();	
	}
	
	ZeroMemory(&g_blk,sizeof(BLOCKINFO));





	m_NiPreEditNum.SetValue(0);
	m_NiSlide.SetValue(0);
	UpdateData(FALSE);
}

//分析处理 模块
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//NI控件 模块

BEGIN_EVENTSINK_MAP(CAnalysisTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CAnalysisTestDlg)
	ON_EVENT(CAnalysisTestDlg, IDC_CWSLIDE_PLAYBACK, 1 /* PointerValueChanged */, OnPointerValueChangedCwslidePlayback, VTS_I4 VTS_PVARIANT)
	ON_EVENT(CAnalysisTestDlg, IDC_CWSLIDE_PROGRESS, 1 /* PointerValueChanged */, OnPointerValueChangedCwslideProgress, VTS_I4 VTS_PVARIANT)
	ON_EVENT(CAnalysisTestDlg, IDC_CWNUMEDIT_PRE_FRAMENUM, 2 /* IncDecButtonClicked */, OnIncDecButtonClickedCwnumeditPreFramenum, VTS_BOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//浏览滑块响应
void CAnalysisTestDlg::OnPointerValueChangedCwslidePlayback(long Pointer, VARIANT FAR* Value) 
{
	// TODO: Add your control notification handler code here
//	char fileName[256] = "\0";
	//	if (myFileListData.strID != "" && bPreview == 1) 
	//	{
	//		sprintf(fileName,myFileListData.str_7);
	//		okLoadImageFile(hBoard,fileName,m_NiSlide.Value,BUFFER,0,1);
	//		okConvertRect(hBoard,SCREEN,0,BUFFER,0,1);
	//	}
	//	m_NiPreEditNum.SetValue(m_NiSlide.Value);	
	//	m_NiSlide.Refresh();
	
	m_NiPreEditNum.SetValue(m_NiSlide.Value);
	char fileName[256] = "\0";
	CRect rect;
	if (myFileListData.strID != "" && bPreview == 1) 
	{
		sprintf(fileName,myFileListData.str_7);
		okLoadImageFile(hBoard,fileName,m_NiSlide.Value,BUFFER,0,1);
	
		// 获取缓存中的图像数据保存地址；
		structEData.lpbuf =NULL;
		structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride);
		lStrideRed = lStride;
		myElegansFeatures.JustGetHistogram(structEData.lpbuf,lHeight,lStride);

		// Edit by haining 2008.12.2 for lagre data processing
		if (lHeight > 600 && lStride > 800)
		{
			myElegansFeatures.InitStructData(lHeight,lStride);
			//特殊处理 若图像大于800*600，则缩小1/4显示
			myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
			//get image to app buffer from tgt
			g_blk.lpBits = structEData.lpHalf;			
			g_blk.iWidth = (short)(lStride*0.5);
			g_blk.iHeight = (short)(lHeight*0.5); //to invert y
			g_blk.iBitCount = 8;
			g_iSizeImage = lStride * lHeight;
			g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
			g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
			okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
			myElegansFeatures.DestroyStructData();
		}
		else
		{
			okConvertRect(hBoard,SCREEN,0,BUFFER,0,1);
		}

		//if (gDlg->m_CheckHistogram==TRUE)
		//{
		//	DrawHistogram();			
		//}		
	}
}

void CAnalysisTestDlg::OnPointerValueChangedCwslideProgress(long Pointer, VARIANT FAR* Value) 
{
	// TODO: Add your control notification handler code here
	m_NiProgress.Refresh();
}


void CAnalysisTestDlg::OnIncDecButtonClickedCwnumeditPreFramenum(BOOL IncButton) 
{
	// TODO: Add your control notification handler code here
//	if (IncButton ==0)
//		m_NiPreEditNum.Value -= 1;
//	else
//		m_NiPreEditNum.Value += 1;
	m_NiSlide.SetValue(m_NiPreEditNum.Value);
}

//NI控件 模块
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////



//退出程序时的安全操作
void CAnalysisTestDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//退出确认
	
	
	//退出时检测数据库是否已关闭
	if (m_mydatabase.IsOpen() != 0)
	{
		m_mydatabase.CloseDB();
	}
	
	CDialog::OnClose();
}


void CAnalysisTestDlg::OnCheckHistogram() 
{
	// TODO: Add your control notification handler code here
	if (m_CheckHistogram== TRUE)
	{
		m_CheckHistogram=FALSE;
	}
	else if(m_CheckHistogram == FALSE)
	{
		m_CheckHistogram=TRUE;
	}
}

void CAnalysisTestDlg::DrawHistogram()
{
	
	//TRACE("Draw histogram!");
	//m_NiHistogram.ClearData();
	//m_NiHistogram.Plots.RemoveAll();
	//m_NiHistogram.Plots.Add();
	
	
	int i=0;
	for(i=0;i<255;i++)
		m_NiHistogram.ChartXY(i,structEData.iHist[i]);
	//m_NiHistogram.Refresh();
}

void CAnalysisTestDlg::OnButGetData() 
{
	// TODO: Add your control notification handler code here
	//导出参数
	//char xx[255] = "\0";
	
	//sprintf(xx,"%s",g_strFileName);
		//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	////g_strErrMes.Format("Saving Data...\r\nPlease wait for about 30 seconds.\r\n");
	sprintf(chTmpMsg,_T("Saving Data...\r\nPlease wait for about 30 seconds.\r\n"));
	SendMessage(WM_MESSAGE,0,(LPARAM)chTmpMsg);
	
	CreatToAccess(g_strFileName);			
	g_RecSet.Close();			
	g_db.Close();

	sprintf(chTmpMsg,_T("Congratulations!!!\r\n"));
	//g_strErrMes.Format("Congratulations!!!\r\n");
	SendMessage(WM_MESSAGE,0,(LPARAM)chTmpMsg);

	//每处理完一个数据，释放占用内存
	if (structEData.path != NULL)
	{
		myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
	}
	if (myElegansFeatures.DoPretreatment.C != NULL)
	{
		myElegansFeatures.DoPretreatment.DestroyData();
	}
	if (myElegansFeatures.DoParadistill.m_hAglRate != NULL)
	{
		myElegansFeatures.DestroyDataOfMove();	
	}	

	delete [] chTmpMsg;
	chTmpMsg = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////导出Access数据表的接口 Begin/////////////////////////////////////

//=================================================================
//Name: AddData
//Func: 添加导出Access数据库的参数
//Editor: haining
//Parameter: 
//Return Value: 
//Date: 2007-10-29
//History: 
//=================================================================
void AddData()
{
	CDataPropety dp;
	dp.Name = "Num";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = structEData.Numcount;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
    dp.propety = 2;
    dpArray.Add(dp);

	//////////////////////////////////////////////////////////////////////////
	//保存数据的数据属性、帧属性和实验属性
	dp.Name = "Data_Name";
	dp.Kind = "char";
	dp.lpunchar = NULL;
	dp.lpchar = structEData.ed_chDataName;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);
	
	dp.Name = "Strain_Name";
	dp.Kind = "char";
	dp.lpunchar = NULL;
	dp.lpchar = structEData.ed_chStrainName;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Person_Name";
	dp.Kind = "char";
	dp.lpunchar = NULL;
	dp.lpchar = structEData.ed_chPersonName;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Analysis_Version";
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = &structEData.ed_daDataDetail[0];
    dp.propety = 1;
    dpArray.Add(dp);
	
	dp.Name = "Capture_Date_and_Time";
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = &structEData.ed_daDataDetail[1];
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Analysis_Date_and_Time";
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = &structEData.ed_daDataDetail[2];
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "CCD_Type";
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = &structEData.ed_daDataDetail[3];
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Microscope";
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = &structEData.ed_daDataDetail[4];
    dp.propety = 1;
    dpArray.Add(dp);
	
	dp.Name = "Tempreture";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[0];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Wet";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[1];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);
	
	dp.Name = "With_or_No_Food";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[2];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Magnification";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[3];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Tube_Lens";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[4];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Unit_Cell";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faExperimentDetail[5];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Total_Frames";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[0];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Valid_Frames";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[1];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Invalid_Percent";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[2];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Frame_Rate";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[3];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Frame_Stride";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[4];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Frame_Height";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;
	dp.lpfloat = &structEData.ed_faFrameDetail[5];
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//数据信息 Begin
	dp.Name = "Is_Data_Useful";
	dp.Kind = "int";//改为int，使数据库中存储为数字格式,而非文字，下面有类似情况
	dp.lpunchar = structEData.IsUseful;
	dp.lpchar = NULL;
    dp.lpint = NULL;//(int *)structEData.IsUseful;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
    dp.propety = 2;
    dpArray.Add(dp);

	dp.Name = "Invalid_Frame_Rate";//丢帧率
	dp.Kind = "float";//改为int，使数据库中存储为数字格式,而非文字，下面有类似情况
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = NULL;//(int *)structEData.IsUseful;
	dp.lpfloat = &structEData.InvFraRat;
	dp.lpdouble = NULL;
    dp.propety = 1;
    dpArray.Add(dp);

	dp.Name = "Is_Stage_Moving";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = structEData.m_IsFlatMv;
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
    dp.propety = 2;
    dpArray.Add(dp);

	dp.Name = "Stage_Coordinate_X";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.flatx;
	dp.lpdouble = NULL;//(double *)structEData.flatx;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Stage_Coordinate_Y";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.flaty;
	dp.lpdouble = NULL;//(double *)structEData.flaty;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Curl_Circle";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
    dp.lpint = structEData.nOfCir;
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
    dp.propety = 2;
    dpArray.Add(dp);

	//数据信息 End
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//基本特征参数 Begin
	dp.Name = "AreaOriginal_pix";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.iWormAera;
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "WidthOriginal_pix";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.iWormWidth;
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "LengthOriginal_pix";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.Slength;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "AREAmm2";	//mm^2;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.AREA_3M;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "AREASort_pix";	//mm^2;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.AREA_VALID;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYSIZEmm";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.BODYSIZE_3M;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "BODYSIZESort_pix";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYSIZE_VALID;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYLENGTHmm";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.BODYLENGTH_3M;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "BODYLENGTHSort_pix";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYLENGTH_VALID;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYWIDTH_um";	//um;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYWIDTH;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "AREA_mm2_old";	//mm^2;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.AREA;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYSIZE_mm_old";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYSIZE;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYLENGTH_mm_old";	//mm;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYLENGTH;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BODYWIDTH_um_old";	//um;
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.BODYWIDTH;
	dp.propety = 2;
	dpArray.Add(dp);
	//基本特征参数 End
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//角度弯曲参数 2008.8.19
//////////////////////////////////////////////////////////////////////////
//夹角
	dp.Name = "Body_Angle_1";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[0];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_Angle_2";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[1];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_3";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[2];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_4";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[3];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_5";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[4];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_6";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[5];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_7";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[6];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_8";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[7];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_9";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[8];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body_Angle_10";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLE[9];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

//////////////////////////////////////////////////////////////////////////
//对边a的边长
	dp.Name = "Body_A_1";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[0];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_2";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[1];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_3";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[2];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_4";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[3];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_5";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[4];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_6";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[5];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_7";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[6];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_8";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[7];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_9";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[8];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_A_10";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ALENGTH[9];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

//////////////////////////////////////////////////////////////////////////
//距离
	dp.Name = "Body_ANGHIGH_1";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[0];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_2";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[1];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_3";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[2];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_4";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[3];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_5";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[4];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_6";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[5];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_7";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[6];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_8";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[7];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_9";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[8];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGHIGH_10";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGHIGH[9];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

//////////////////////////////////////////////////////////////////////////
//比率
	dp.Name = "Body_ANGLETOA_1";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[0];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_2";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[1];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_3";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[2];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_4";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[3];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_5";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[4];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_6";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[5];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_7";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[6];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_8";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[7];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_9";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[8];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Body_ANGLETOA_10";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.ANGLETOA[9];
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	//头尾相关参数 Begin
	dp.Name = "Head_X";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.Head_Out[0];
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "Head_Y";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.Head_Out[1];
	dp.lpfloat = NULL;
    dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "End_X";
	dp.Kind = "int";
	dp.lpint = structEData.End_Out[0];
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "End_Y";
	dp.Kind = "int";
	dp.lpint = structEData.End_Out[1];
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Head_Width";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.HeadWith;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Tail_Width";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.TailWith;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "A_endWith";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.A_endWith;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "B_endWith";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpfloat = structEData.B_endWith;
	dp.lpdouble = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	//头尾相关参数 End
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//运动特征参数 Begin
	dp.Name = "AngBodybends";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpfloat = structEData.AngBodybends;
	dp.lpdouble = NULL;
	dp.lpint = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "FrameOfBend";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
	dp.lpint = structEData.FrameOfBend;
	dp.propety = 2;
	dpArray.Add(dp);

	//2008.12.16 改为直接导出每分钟的次数 float型
	dp.Name = "BodyBends";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpfloat = &structEData.BodyBendsHead;
	dp.lpdouble = NULL;
	dp.lpint = NULL;
	dp.propety = 1;
	dpArray.Add(dp);
	   
	dp.Name = "BodyBendsBody";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
	dp.lpint = &structEData.BodyBendsBody;
	dp.propety = 1;
	dpArray.Add(dp);
	   
	dp.Name = "BodyBendsTail";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpfloat = NULL;
	dp.lpdouble = NULL;
	dp.lpint = &structEData.BodyBendsTail;
	dp.propety = 1;
	dpArray.Add(dp);
	   	   
	dp.Name = "Old_MomentarySpeed";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.CMVSPAC;//旧的，错误的质心的瞬时速率
	dp.propety = 2;
	dpArray.Add(dp);
	  
	//newfCMVSPAC
	dp.Name = "New_MomentarySpeed";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.newfCMVSPAC;//新的，质心的瞬时速率
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "DELTA_X_STAGEum";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_X_STAGE;//相邻两帧stage的变化量,um
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "DELTA_Y_STAGEum";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_Y_STAGE;//相邻两帧stage的变化量,um
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "DELTA_X_IMAGE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_X_IMAGE;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "DELTA_Y_IMAGE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_Y_IMAGE;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "DELTA_X_REAL";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_X_REAL;
	dp.propety = 2;
	dpArray.Add(dp);


	dp.Name = "DELTA_Y_REAL";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.DELTA_Y_REAL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "TOTMOVE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.TOTMOVE;//总爬行距离
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "RADIUS";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.RADIUS;//运动半径
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "AVERSPEED";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.AVERSPEED;//总平均速率
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "CentroidX";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.centroidX;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "CentroidY";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.centroidY;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);
	   	   
	dp.Name = "cvCentroidX";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.ed_iCvCentroidX;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "cvCentroidY";
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.ed_iCvCentroidY;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "CGLBDIR";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.CGLBDIR;
	dp.propety = 1;
	dpArray.Add(dp);
		   
	dp.Name = "CREALDIR";	//"实时运动方向";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.CREALDIR;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyMove1s";	//"1s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.VELOCITY01s;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "BodyTrack_X_1s";	//"1s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.X_REAL_01s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyTrack_Y_1s";	//"1s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.Y_REAL_01s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body1s_ANGLE_CHANGE";	//"ANGLE CHANGE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.ANGLE_CHANGE01s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyMove2s";	//"2s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.VELOCITY02s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyMove5s";	//"5s移动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.VELOCITY05s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyTrack_X_5s";	//"5s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.X_REAL_05s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "BodyTrack_Y_5s";	//"5s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.Y_REAL_05s;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Body5s_ANGLE_CHANGE";	//"ANGLE CHANGE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.ANGLE_CHANGE05s;
	dp.propety = 2;
	dpArray.Add(dp);
	   
// 	dp.Name = "BodyMove10s";	//"10s移动平均值";
// 	dp.Kind = "float";
// 	dp.lpunchar = NULL;
// 	dp.lpchar = NULL;
// 	dp.lpint = NULL;
// 	dp.lpdouble = NULL;
// 	dp.lpfloat = structEData.VELOCITY10s;
// 	dp.propety = 2;
// 	dpArray.Add(dp);
// 	   
// 	dp.Name = "BodyMove30s";	//"30s移动平均值";
// 	dp.Kind = "float";
// 	dp.lpunchar = NULL;
// 	dp.lpchar = NULL;
// 	dp.lpint = NULL;
// 	dp.lpdouble = NULL;
// 	dp.lpfloat = structEData.VELOCITY30s;
// 	dp.propety = 2;
// 	dpArray.Add(dp);
// 
// 	dp.Name = "BodyMove60s";	//"30s移动平均值";
// 	dp.Kind = "float";
// 	dp.lpunchar = NULL;
// 	dp.lpchar = NULL;
// 	dp.lpint = NULL;
// 	dp.lpdouble = NULL;
// 	dp.lpfloat = structEData.VELOCITY60s;
// 	dp.propety = 2;
// 	dpArray.Add(dp);


	//////////////////////////////////////////////////////////////////////////
	//ROAM和DWELL时间
	dp.Name = "Time_ROAM_01s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.ROAM_TIME_01s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Time_DWELL_01s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.DWELL_TIME_01s;
	dp.propety = 1;
	dpArray.Add(dp);


	dp.Name = "Time_ROAM_05s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.ROAM_TIME_05s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Time_DWELL_05s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.DWELL_TIME_05s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Percent_ROAM_01s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.ROAM_PERCENT_01s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Percent_DWELL_01s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.DWELL_PERCENT_01s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Percent_ROAM_05s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.ROAM_PERCENT_05s;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Percent_DWELL_05s";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.DWELL_PERCENT_05s;
	dp.propety = 1;
	dpArray.Add(dp);
	//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//暂时没有使用的运动参数
	dp.Name = "HMVSPAC";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HMVSPAC;
	dp.propety = 2;
	dpArray.Add(dp);
	
	dp.Name = "TMVSPAC";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TMVSPAC;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "HWAV60S";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.HWAV60S;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "TWAV60S";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.TWAV60S;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "HTMVRATE";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.HTMVRATE;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "HDHFTOTMV";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.HDHFTOTMV;
	dp.propety = 1;
	dpArray.Add(dp);
	
	dp.Name = "TLHFTOTMV";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = &structEData.TLHFTOTMV;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "HeadMove005s";	//"0.5s头部局部运动平均值"; 
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMVHFS;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "HeadMove10s";	//"10s头部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMV10S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "HeadMove20s";	//"20s头部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMV20S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "HeadMove30s";	//"30s头部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMV30S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "HeadMove40s";	//"40s头部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMV40S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "HeadMove50s";	//"50s头部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.HDMV50S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove005s";	//"0.5s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMVHFS;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove10s";	//"10s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMV10S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove20s";	//"20s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMV20S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove30s";	//"30s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMV30S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove40s";	//"40s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMV40S;
	dp.propety = 2;
	dpArray.Add(dp);
	   
	dp.Name = "TailMove50s";	//"50s尾部局部运动平均值";
	dp.Kind = "float";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = NULL;
	dp.lpfloat = structEData.TLMV50S;
	dp.propety = 2;
	dpArray.Add(dp);
//暂时没有使用的运动参数 End
//////////////////////////////////////////////////////////////////////////

	//运动特征参数 End
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//2008.12.16 Bodywave 参数 单位um
	dp.Name = "Bodywave_Length";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveStride;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Height";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveHeight;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	// 2009.4.24
	dp.Name = "Bodywave_Length_Normalized";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveStrideNormal;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Height_Normalized";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveHeightNormal;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "X_Time";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_xTime;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Angle";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveAngle;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Ratio";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dpBodywaveSToH;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Length_25";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveStrideNormal_25;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Length_75";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveStrideNormal_75;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Length_3M";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveStrideNormal_3M;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Height_25";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveHeightNormal_25;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Height_75";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveHeightNormal_75;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Bodywave_Height_3M";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dpBodywaveHeightNormal_3M;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Forward and Backward
	dp.Name = "Locomotion_status";	
	dp.Kind = "int";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = structEData.ed_iLocomotionStatus;
	dp.lpdouble = NULL;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "dDisNow";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dDisNow;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "dDisPre";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = structEData.ed_dDisPre;
	dp.lpfloat = NULL;
	dp.propety = 2;
	dpArray.Add(dp);

	dp.Name = "Forward_Velocity";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dMFCV;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Forward_Time";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dForewardTime;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Backward_Velocity";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dMBCV;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Backward_Time";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dBackwardTime;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);

	dp.Name = "Holding_Time";	
	dp.Kind = "double";
	dp.lpunchar = NULL;
	dp.lpchar = NULL;
	dp.lpint = NULL;
	dp.lpdouble = &structEData.ed_dHoldingTime;
	dp.lpfloat = NULL;
	dp.propety = 1;
	dpArray.Add(dp);
	//////////////////////////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
//Name: GetDefaultXlsFileName
//Func: 获得默认的文件名
//Editor: mengxiao 
//Parameter: CString& sExcelFile
//Return Value: BOOL
//Date: 2007-3
///////////////////////////////////////////////////////////////////////////////
BOOL GetDefaultXlsFileName(CString& sExcelFile)
{
	///默认文件名：yyyymmddhhmmss.xls
	CString timeStr;
	CTime day;
	day=CTime::GetCurrentTime();
	int filenameday,filenamemonth,filenameyear,filehour,filemin,filesec;
	filenameday=day.GetDay();//dd
	filenamemonth=day.GetMonth();//mm月份
	filenameyear=day.GetYear();//yyyy
	filehour=day.GetHour();//hh
	filemin=day.GetMinute();//mm分钟
	filesec=day.GetSecond();//ss
	timeStr.Format("%04d%02d%02d%02d%02d%02d",filenameyear,filenamemonth,filenameday,filehour,filemin,filesec);
	
	sExcelFile = timeStr;
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//Name: CreatToAccess()
//Func: 创建access文件
//Editor: mengxiao 
//Parameter: 
//Return Value: None
//Date: 2007-4-7
//History: Edit by haining 2007-11-8
///////////////////////////////////////////////////////////////////////////////
void CreatToAccess(CString moveName)
{
	int i = 0;
	int j = 0;
	CString sqlstr;
	CString SqlCmd;
	CString SqlCmdH;
	CString sPath;
	CString lpszFile;
	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer ();
	int nPos;
	nPos=sPath.ReverseFind ('\\');
	sPath=sPath.Left (nPos);
	CString strTmp_1;
	GetDefaultXlsFileName(strTmp_1);

	//////////////////////////////////////////////////////////////////////////
	//2008.12.16 ÁÙÊ±¼ÓÈëµÄ£¬±£´æ·ÖÎöÊ±¼ä
	//×¢ÒâintÐÍ
	structEData.ed_daDataDetail[2] = atof(strTmp_1.Mid(0,12));
	//////////////////////////////////////////////////////////////////////////


	//lpszFile = sPath + "\\" + moveName + lpszFile + ".mdb";
	lpszFile.Format("%s%s.mdb",moveName,strTmp_1);

	CFileFind  fFind;
	BOOL bSuccess;
	bSuccess=fFind.FindFile(lpszFile);

	fFind.Close ();
	if (bSuccess)
	{
		DeleteFile(lpszFile);
		AfxMessageBox("发现已有数据库，已将其删除!");
		bSuccess = 0;
	}
	//是否已有创建好的Demo.mdb文件，没有则创建它
	if(!bSuccess)
	{
		AfxGetModuleState()->m_dwVersion = 0x0601; //¸Ä°æ±¾
		g_db.Create(lpszFile);
		CString sqlstr;
		CString SqlCmd;
		CString SqlCmdH;
		//ÔÚÕâÀï´´½¨±íÏà,Ãû×Ö²»ÒªºÍ¹Ø¼ü×ÖÒ»Ñù

		SqlCmd = "CREATE TABLE DemoTable(Num int constraint PKName PRIMARY KEY)";
		g_db.Execute(SqlCmd);
		//AfxMessageBox(SqlCmd);

		for(i=1;i<=dpArray.GetUpperBound();i++)
		{
			SqlCmd = "alter table DemoTable add " + dpArray.GetAt(i).Name + " "
				+ dpArray.GetAt(i).Kind;
			//AfxMessageBox(SqlCmd);
			g_db.Execute(SqlCmd);
		}

		char name[255] = "\0";
		char value[255] = "\0";
		CDataPropety* pt=(CDataPropety*) dpArray.GetData();

		for(i=0;i<structEData.nImgOfProc;i++)
		{	
			//´ò¿ªÒÑ´´½¨µÄÊý¾Ý±í
			g_RecSet.Open(dbOpenDynaset,"SELECT * FROM [DemoTable]");
			g_RecSet.AddNew();
			sprintf(value,"%d",i);//dpArray.GetAt(0).lpint[i](Ö¡ÊýÖ±½ÓÊ¹ÓÃi£¬ÒÔÇ°µÄ×ö·¨»áµ¼ÖÂÖ÷¹Ø¼ü×ÖÖØ¸´)
			g_RecSet.SetFieldValue("Num",value);
			for(j=1;j<=dpArray.GetUpperBound();j++,pt++)
			{                
				if(dpArray.GetAt(j).propety == 2)
				{
					if ( dpArray.GetAt(j).lpunchar != NULL )
					{
						sprintf(name,"%s",dpArray.GetAt(j).Name);

						//³ö´í´¦Àí2008.12.14 add by haining
						if(_isnan(dpArray.GetAt(j).lpunchar[i]) != 0 )
						{
							dpArray.GetAt(j).lpunchar[i] = 0;
							//g_strErrMes.Format("Êý¾Ýµ¼ÈëÖÐ%s.%dÖ¡³ö´í£¬±»ÖÃ0.\r\n",name,i);
							//::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)&g_strErrMes);
							//Sleep(100);
						}

						sprintf(value,"%d",(int)(dpArray.GetAt(j).lpunchar[i]));                        
						g_RecSet.SetFieldValue(name,value);							
					}
					else if ( dpArray.GetAt(j).lpchar != NULL )
					{
						sprintf(name,"%s",dpArray.GetAt(j).Name);
						//³ö´í´¦Àí
						if(_isnan(dpArray.GetAt(j).lpchar[i]) != 0 )
						{
							dpArray.GetAt(j).lpchar[i] = 0;
							//g_strErrMes.Format("Êý¾Ýµ¼ÈëÖÐ%s.%dÖ¡³ö´í£¬±»ÖÃ0.\r\n",name,i);
							//::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)&g_strErrMes);
							//Sleep(100);
						}
						sprintf(value,"%s",(char)(dpArray.GetAt(j).lpchar));                        
						g_RecSet.SetFieldValue(name,value);							
					}
					else if ( dpArray.GetAt(j).lpint != NULL )
					{
						sprintf(name,"%s",dpArray.GetAt(j).Name);
						//³ö´í´¦Àí
						if(_isnan(dpArray.GetAt(j).lpint[i]) != 0 )
						{
							dpArray.GetAt(j).lpint[i] = 0;
							//g_strErrMes.Format("Êý¾Ýµ¼ÈëÖÐ%s.%dÖ¡³ö´í£¬±»ÖÃ0.\r\n",name,i);
							//::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)&g_strErrMes);
							//Sleep(100);
						}

						sprintf(value,"%d",(int)(dpArray.GetAt(j).lpint[i]));

						g_RecSet.SetFieldValue(name,value);							
					}
					else if( dpArray.GetAt(j).lpfloat != NULL )
					{     
						sprintf(name,"%s",dpArray.GetAt(j).Name);
						//³ö´í´¦Àí
						if(_isnan(dpArray.GetAt(j).lpfloat[i]) != 0 )
						{
							dpArray.GetAt(j).lpfloat[i] = 0;
							//g_strErrMes.Format("Êý¾Ýµ¼ÈëÖÐ%s.%dÖ¡³ö´í£¬±»ÖÃ0.\r\n",name,i);
							//::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)&g_strErrMes);
							//Sleep(100);
						}
						sprintf(value,"%f",(dpArray.GetAt(j).lpfloat[i]));

						g_RecSet.SetFieldValue(name,value);							
					}
					else if(dpArray.GetAt(j).lpdouble != NULL)
					{
						sprintf(name,"%s",dpArray.GetAt(j).Name);
						//³ö´í´¦Àí
						if(_isnan(dpArray.GetAt(j).lpdouble[i]) != 0 )
						{
							dpArray.GetAt(j).lpdouble[i] = 0;
							//g_strErrMes.Format("Êý¾Ýµ¼ÈëÖÐ%s.%dÖ¡³ö´í£¬±»ÖÃ0.\r\n",name,i);
							//::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)&g_strErrMes);
							//Sleep(100);
						}

						sprintf(value,"%f",(dpArray.GetAt(j).lpdouble[i]));

						g_RecSet.SetFieldValue(name,value);
					}
				}
				else
				{
					if( i==0 )
					{					
						if ( dpArray.GetAt(j).lpunchar != NULL )
						{
							sprintf(value,"%d",dpArray.GetAt(j).lpunchar[i]);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);							
						}
						else if ( dpArray.GetAt(j).lpchar != NULL )
						{
							sprintf(value,"%s",dpArray.GetAt(j).lpchar);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);							
						}
						else if ( dpArray.GetAt(j).lpint != NULL )
						{							
							sprintf(value,"%d",dpArray.GetAt(j).lpint[i]);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);							
						}
						else if( dpArray.GetAt(j).lpfloat != NULL )
						{                         
							sprintf(value,"%f",dpArray.GetAt(j).lpfloat[i]);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);	
						}
						else if(dpArray.GetAt(j).lpdouble != NULL)
						{
							sprintf(value,"%f",dpArray.GetAt(j).lpdouble[i]);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);
						}
					}
					else
					{					
						if ( dpArray.GetAt(j).lpunchar != NULL )
						{
							sprintf(value,"%d",0);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);							
						}
						else if ( dpArray.GetAt(j).lpchar != NULL )
						{
							sprintf(value,"%d",0);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);							
						}
						else if ( dpArray.GetAt(j).lpint != NULL )
						{                            
							sprintf(value,"%d",0);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);						
						}
						else if( dpArray.GetAt(j).lpfloat != NULL )
						{                           
							sprintf(value,"%f",0.0);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);											
						}
						else if(dpArray.GetAt(j).lpdouble != NULL)
						{
							sprintf(value,"%f",0.0);
							sprintf(name,"%s",dpArray.GetAt(j).Name);
							g_RecSet.SetFieldValue(name,value);
						}
					}
				}					
			}//end for j

			g_RecSet.Update();
			g_RecSet.Close();

		}//end for i

		AfxMessageBox("Success! Access Database is created");
	}
	else
	{
		AfxMessageBox("Find and Delete the old database!");
	}


//     int i = 0;
// 	int j = 0;
//     CString sqlstr;
//     CString SqlCmd;
//     CString SqlCmdH;
// 	CString sPath;
//     CString lpszFile;
// 	GetModuleFileName(NULL,sPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
// 	sPath.ReleaseBuffer ();
// 	int nPos;
// 	nPos=sPath.ReverseFind ('\\');
// 	sPath=sPath.Left (nPos);
// 	CString strTmp_1;
// 	GetDefaultXlsFileName(strTmp_1);
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	//2008.12.16 临时加入的，保存分析时间
// 	//注意int型
// 	structEData.ed_daDataDetail[2] = atof(strTmp_1.Mid(0,12));
// 	//////////////////////////////////////////////////////////////////////////
// 	
// 
// 	//lpszFile = sPath + "\\" + moveName + lpszFile + ".mdb";
// 	lpszFile.Format("%s%s.mdb",moveName,strTmp_1);
// 	
// 	CFileFind  fFind;
// 	BOOL bSuccess;
// 	bSuccess=fFind.FindFile(lpszFile);
// 	
// 	fFind.Close ();
// 	if (bSuccess)
// 	{
// 		DeleteFile(lpszFile);
// 		AfxMessageBox("发现已有数据库，已将其删除!");
// 		bSuccess = 0;
// 	}
//     //是否已有创建好的Demo.mdb文件，没有则创建它
// 	if(!bSuccess)
// 	{
//         AfxGetModuleState()->m_dwVersion = 0x0601; //改版本
// 		g_db.Create(lpszFile);
//         CString sqlstr;
// 		CString SqlCmd;
//         CString SqlCmdH;
// 		//在这里创建表相,名字不要和关键字一样
// 		
// 		SqlCmd = "CREATE TABLE DemoTable(Num int constraint PKName PRIMARY KEY)";
//         g_db.Execute(SqlCmd);
// 		//AfxMessageBox(SqlCmd);
// 		
//         for(i=1;i<=dpArray.GetUpperBound();i++)
// 		{
//             SqlCmd = "alter table DemoTable add " + dpArray.GetAt(i).Name + " "
// 				+ dpArray.GetAt(i).Kind;
// 			//AfxMessageBox(SqlCmd);
//             g_db.Execute(SqlCmd);
// 		}
// 
// 	   char name[255] = "\0";
// 	   char value[255] = "\0";
// 		CDataPropety* pt=(CDataPropety*) dpArray.GetData();
// 		
//         for(i=0;i<structEData.nImgOfProc;i++)
// 		{	
// 			//打开已创建的数据表
// 			g_RecSet.Open(dbOpenDynaset,"SELECT * FROM [DemoTable]");
// 			g_RecSet.AddNew();
// 			sprintf(value,"%d",i);//dpArray.GetAt(0).lpint[i](帧数直接使用i，以前的做法会导致主关键字重复)
// 			g_RecSet.SetFieldValue("Num",value);
//             for(j=1;j<=dpArray.GetUpperBound();j++,pt++)
// 			{                
// 				if(dpArray.GetAt(j).propety == 2)
// 				{
// 					if ( dpArray.GetAt(j).lpunchar != NULL )
// 					{
// 						sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						
// 						//出错处理2008.12.14 add by haining
// 						if(_isnan(dpArray.GetAt(j).lpunchar[i]) != 0 )
// 						{
// /*
// 							dpArray.GetAt(j).lpunchar[i] = 0;
// 							////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 							sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"), name , i);
// 							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 							Sleep(100);
// */
// 
// 						}
// 
//                         sprintf(value,"%d",(int)(dpArray.GetAt(j).lpunchar[i]));                        
// 						g_RecSet.SetFieldValue(name,value);							
// 					}
// 					else if ( dpArray.GetAt(j).lpchar != NULL )
// 					{
// 						sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						//出错处理
// 						if(_isnan(dpArray.GetAt(j).lpchar[i]) != 0 )
// 						{
// /*
// 							dpArray.GetAt(j).lpchar[i] = 0;
// 							////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 							sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"), name, i);
// 							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 							Sleep(100);
// */
// 						}
//                         sprintf(value,"%s",(char)(dpArray.GetAt(j).lpchar));                        
// 						g_RecSet.SetFieldValue(name,value);							
// 					}
// 					else if ( dpArray.GetAt(j).lpint != NULL )
// 					{
// 						sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						//出错处理
// 						if(_isnan(dpArray.GetAt(j).lpint[i]) != 0 )
// 						{
// /*
// 							dpArray.GetAt(j).lpint[i] = 0;
// 							sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 							//g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 							Sleep(100);*/
// 
// 						}
// 
//                         sprintf(value,"%d",(int)(dpArray.GetAt(j).lpint[i]));
//                         
// 						g_RecSet.SetFieldValue(name,value);							
// 					}
//                     else if( dpArray.GetAt(j).lpfloat != NULL )
// 					{     
// 						sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						//出错处理
// 						if(_isnan(dpArray.GetAt(j).lpfloat[i]) != 0 )
// 						{
// /*
// 							dpArray.GetAt(j).lpfloat[i] = 0;
// 							//g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 							sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 							Sleep(100);*/
// 
// 						}
// 					    sprintf(value,"%f",(dpArray.GetAt(j).lpfloat[i]));
//                         
// 					    g_RecSet.SetFieldValue(name,value);							
// 					}
// 					else if(dpArray.GetAt(j).lpdouble != NULL)
// 					{
// 						sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						//出错处理
// 						if(_isnan(dpArray.GetAt(j).lpdouble[i]) != 0 )
// 						{
// /*
// 							dpArray.GetAt(j).lpdouble[i] = 0;
// 							sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 							////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 							Sleep(100);*/
// 
// 						}
// 
// 						sprintf(value,"%f",(dpArray.GetAt(j).lpdouble[i]));
//                         
// 						g_RecSet.SetFieldValue(name,value);
// 					}
// 				}
// 				else
// 				{
// 					if( i==0 )
// 					{					
// 						if ( dpArray.GetAt(j).lpunchar != NULL )
// 						{
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							//出错处理
// 							if(_isnan(dpArray.GetAt(j).lpunchar[i]) != 0 )
// 							{
// /*
// 								dpArray.GetAt(j).lpunchar[i] = 0;
// 								sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 								////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 								Sleep(100);*/
// 
// 							}
// 							sprintf(value,"%d",dpArray.GetAt(j).lpunchar[i]);
// 							
// 							g_RecSet.SetFieldValue(name,value);							
// 						}
// 						else if ( dpArray.GetAt(j).lpchar != NULL )
// 						{
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							//出错处理
// 							if(_isnan(dpArray.GetAt(j).lpchar[i]) != 0 )
// 							{
// /*
// 								dpArray.GetAt(j).lpchar[i] = 0;
// 								sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 								////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 								Sleep(100);*/
// 
// 							}
// 							sprintf(value,"%s",dpArray.GetAt(j).lpchar);//?????[i]
// 							
// 							g_RecSet.SetFieldValue(name,value);							
// 						}
// 						else if ( dpArray.GetAt(j).lpint != NULL )
// 						{		
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							//出错处理
// 							if(_isnan(dpArray.GetAt(j).lpint[i]) != 0 )
// 							{
// /*
// 								dpArray.GetAt(j).lpint[i]= 0;
// 								sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 								////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 								Sleep(100);*/
// 
// 							}
// 							sprintf(value,"%d",dpArray.GetAt(j).lpint[i]);
// 							
// 							g_RecSet.SetFieldValue(name,value);							
// 						}
// 						else if( dpArray.GetAt(j).lpfloat != NULL )
// 						{                         
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							//出错处理
// 							if(_isnan(dpArray.GetAt(j).lpfloat[i]) != 0 )
// 							{
// /*
// 								dpArray.GetAt(j).lpfloat[i]= 0;
// 								sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 								////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 								Sleep(100);*/
// 
// 							}
// 						    sprintf(value,"%f",dpArray.GetAt(j).lpfloat[i]);
// 						    
// 						    g_RecSet.SetFieldValue(name,value);	
// 						}
// 						else if(dpArray.GetAt(j).lpdouble != NULL)
// 						{
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							//出错处理
// 							if(_isnan(dpArray.GetAt(j).lpdouble[i]) != 0 )
// 							{
// /*
// 								dpArray.GetAt(j).lpdouble[i]= 0;
// 								sprintf(chTmpMsg,_T("数据导入中%s.%d帧出错，被置0.\r\n"),name,i);
// 								////g_strErrMes.Format("数据导入中%s.%d帧出错，被置0.\r\n",name,i);
// 								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
// 								Sleep(100);*/
// 
// 							}
// 							sprintf(value,"%f",dpArray.GetAt(j).lpdouble[i]);
// 							
// 							g_RecSet.SetFieldValue(name,value);
// 						}
// 					}
// 					else
// 					{					
// 						if ( dpArray.GetAt(j).lpunchar != NULL )
// 						{
// 							sprintf(value,"%d",0);
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							g_RecSet.SetFieldValue(name,value);							
// 						}
// 						else if ( dpArray.GetAt(j).lpchar != NULL )
// 						{
// 							sprintf(value,"%d",0);
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							g_RecSet.SetFieldValue(name,value);							
// 						}
// 						else if ( dpArray.GetAt(j).lpint != NULL )
// 						{                            
// 							sprintf(value,"%d",0);
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							g_RecSet.SetFieldValue(name,value);						
// 						}
// 						else if( dpArray.GetAt(j).lpfloat != NULL )
// 						{                           
// 						    sprintf(value,"%f",0.0);
// 						    sprintf(name,"%s",dpArray.GetAt(j).Name);
// 						    g_RecSet.SetFieldValue(name,value);											
// 						}
// 						else if(dpArray.GetAt(j).lpdouble != NULL)
// 						{
// 							sprintf(value,"%f",0.0);
// 							sprintf(name,"%s",dpArray.GetAt(j).Name);
// 							g_RecSet.SetFieldValue(name,value);
// 						}
// 					}
// 				}					
// 			}//end for j
// 
//             g_RecSet.Update();
// 			g_RecSet.Close();
// 
// 		}//end for i
// 		
// 		AfxMessageBox("Access文件写入成功！");
// 	}
// 	else
// 	{
// 		AfxMessageBox("发现已有数据库，无法删除!");
// 	}
}
//======================================end=================================================
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////导出Access数据表的接口 End//////////////////////////////////////

// 将压缩avi文件转换格式为未压缩avi文件，从而可被ImageJ的avireader读取
void CAnalysisTestDlg::OnButSaveAvi() 
{
	// TODO: Add your control notification handler code here
	StrRecName* RecPARAM = new StrRecName;
	if (m_CheckHistogram == TRUE)
	{
		//批量解压缩
		myFileListData.strID=m_FileNameList.GetItemText(0,0);	
		myFileListData.str_1=m_FileNameList.GetItemText(0,8);
		myFileListData.str_2=m_FileNameList.GetItemText(0,2);
		myFileListData.str_3=m_FileNameList.GetItemText(0,3);
		myFileListData.str_4=m_FileNameList.GetItemText(0,4);
		myFileListData.str_5=m_FileNameList.GetItemText(0,5);
		myFileListData.str_6=m_FileNameList.GetItemText(0,6);
		myFileListData.str_7=m_FileNameList.GetItemText(0,7);
		myFileListData.str_8=m_FileNameList.GetItemText(0,1);
		
		m_NiSlide.Axis.Maximum = atoi(myFileListData.str_3);
		RecPARAM = &myFileListData;		


		RecPARAM->iFlag = 100;
		if (RecPARAM->bCount == FALSE)
		{
			RecPARAM->iCountA = 0;
			RecPARAM->iCountB = 0;
		}
		
		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,TRUE);
		
		GetLocalTime(&sysTimeBegin);
		lSysTime = GetTickCount();
		
		g_iRunningFlag = 100;//100表示有处理进程在运行，0表示没有
		//开启分析线程
		hThread4 = CreateThread(NULL,0,UnCompressProc,(LPVOID)RecPARAM,0,&threadID_4);
	}
	else
	{
		//单个解压缩
		RecPARAM->iFlag = 0;
		if (myFileListData.strID == "" || myFileListData.str_1 == "已处理")
		{
			MessageBox("没有选择要分析的记录！or 选择的记录已处理!",NULL,MB_OK);
			return;
		}
		else
		{		
			RecPARAM = &myFileListData;			
			//RecPARAM->iFlag = 0; //备用标志在分析处理时，0代表单个文件分析，100代表批量分析
			if (RecPARAM->bCount == FALSE)
			{
				RecPARAM->iCountA = 0;
				RecPARAM->iCountB = 0;
			}
			
			bActive = 1;
			lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
			InvalidateRect(NULL,TRUE);
			
			GetLocalTime(&sysTimeBegin);
			lSysTime = GetTickCount();
			
			g_iRunningFlag = 100;//100表示有处理进程在运行，0表示没有
			//开启分析线程
			hThread4 = CreateThread(NULL,0,UnCompressProc,(LPVOID)RecPARAM,0,&threadID_4);
		}
	}


}


//扩展功能面板，解压缩线程
DWORD WINAPI UnCompressProc(LPVOID lpParameter)
{
	CString strTmpID = ((StrRecName*)lpParameter)->strID;//记录ID号
	// 记录名，仅名称(单个分析传递记录名)
	CString strTmpNameOnly = ((StrRecName*)lpParameter)->str_2;
	strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,strTmpNameOnly.GetLength()-4));
	//
	CString strTmpPathOnly = ((StrRecName*)lpParameter)->str_7; 
	strTmpPathOnly.Format("%s",strTmpPathOnly.Mid(0,((StrRecName*)lpParameter)->str_7.GetLength()-((StrRecName*)lpParameter)->str_2.GetLength()));
	
	//记录路径名(单个分析传递记录名路径)
	CString strTmpFileName = ((StrRecName*)lpParameter)->str_7;	
	CString strTmpTotalFrames = ((StrRecName*)lpParameter)->str_3;//记录的总帧数
	int     iTmpFlag = ((StrRecName*)lpParameter)->iFlag;//单个分析 or 批量分析
	int iNum = 0;
	int iBeginNum = 0;
	int iEndNum = 0;
	int iTotalFrames = atoi(strTmpTotalFrames);
	if (((StrRecName*)lpParameter)->bCount == TRUE)
	{
		iBeginNum = ((StrRecName*)lpParameter)->iCountA; //LoadImage开始load的帧数
		iEndNum   =	((StrRecName*)lpParameter)->iCountB; //LoadImage结束load的帧数	
		iTotalFrames = iEndNum -iBeginNum; //需要读取处理的总帧数
		iNum = iBeginNum;
	}

	CString strTmpRate = ((StrRecName*)lpParameter)->str_8;//记录的帧率
	float fRate = atof(strTmpRate);

	char fileName[256] = "\0";	 
	char chSaveFileName[256] = "\0";
	int iTotalUncom = iTotalFrames;
	int iTotalLeft = iTotalUncom;//总共读取的帧数
	int iReadBuffer=0;//缓存大小
	int iReadTimes = 0;	
	int nRetCode=0;
	int i = 0;
	bActive = 1;

	// 设置采集卡
	okStopCapture(hBoard);
    okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
	okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//设置SCREEN为8位
	
	//改变缓存大小设置，取代默认的640x480
	short heightTemp;
	long strideTemp;
	CRect   rect;        // 根据图像大小设置BUFFER大小	
	//从str_4中提取当前处理图像的宽和高，并进行设置
	int iAVIStride = 0,iAVIHeight = 0;
	CString strTmpSize = ((StrRecName*)lpParameter)->str_4;//提取图像大小
	CString strTmpStride,strTmpHeight;
	int iTmpGet = strTmpSize.Find('*');
	strTmpStride = strTmpSize.Left(iTmpGet);
	int iTmpLength = strTmpSize.GetLength();
	strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
	iAVIStride = atoi(strTmpStride);
	iAVIHeight = atoi(strTmpHeight);
	assert(iAVIStride != 0);//防止为0
	assert(iAVIHeight != 0);
	SetRect(&rect,0,0,iAVIStride,iAVIHeight);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
	
	if (iAVIStride > 800 && iAVIHeight >600)
	{
		SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
	}
	else
	{
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
	}
	lHeight = iAVIHeight;
	lStride = iAVIStride;
	
	
	CString strMessageLoad = "okLoadImageFile...\r\n";
	CString strMessageBegin ="Begin\r\n";
	CString strMessageSave = "Saving...\r\n";
	CString strMessageEnd = "Congratulations!\r\n";
	
	sprintf(fileName,((StrRecName*)lpParameter)->str_7);
	//LoadFileName
	char beginFileName[256] = "\0";
	char midFileName[256] = "\0";
	char endFileName[256] = "\0";
	sprintf(beginFileName,"%s,beg",fileName);
	sprintf(midFileName,"%s,con",fileName);
	sprintf(endFileName,"%s,end",fileName);

	//SaveFileName 2008.12.7
	CString strLocation = "";
	int iLocaBegin = 0; 	
	int iLocaEnd = 0;
	DWORD dwAttr;
	char chTmpFileName[256] = "\0";

	// 批量处理需要的变量	
	//char chTmpFileName[256]="\0";
	SYSTEMTIME *currenttime;
	currenttime = new SYSTEMTIME;
	int m_itmpId = 0;
	int iChuli = 0;
	CAnalysisTestDlg* dlg;
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();

	LPBYTE		lpLinear;
	DWORD		dwSize;


	//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	BOOL bWhile = TRUE;
	while (bWhile == TRUE)
	{
		if (bActive == 1)
		{
			if (iTmpFlag == 100)
			{
				//批量分析
				int end = 0;
				CString StateNow = "";
				CString sql = "";
				CString strFilenameAviNow = "";
				end = dlg->m_FileNameList.GetItemCount();
				for(iChuli=0;iChuli<end;iChuli++)
				{
					////g_strErrMes.Format("In Progress...The No.%d is being performed.\r\n",iChuli+1);
					sprintf(chTmpMsg,_T("In Progress...The No.%d is being performed.\r\n"), iChuli+1);
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
					Sleep(100);
					StateNow.Format("%s",dlg->m_FileNameList.GetItemText( iChuli , 8 ));
					if(StateNow == "X")
					{
						strFilenameAviNow = dlg->m_FileNameList.GetItemText( iChuli , 7 );
						StateNow.Format("Processing...");
						dlg->m_FileNameList.SetItemText( iChuli, 8, "Processing...");
						dlg->m_FileNameList.UpdateWindow();
						//AfxMessageBox(strFilenameAviNow);
						
			//////////////////////////////////////////////////////////////////////////
			//参数设置
						strTmpNameOnly.Format("%s",dlg->m_FileNameList.GetItemText( iChuli , 2 ).Mid(0,dlg->m_FileNameList.GetItemText( iChuli , 2 ).GetLength()-4));
						strTmpPathOnly.Format("%s",strFilenameAviNow.Mid(0,strFilenameAviNow.GetLength()
							-dlg->m_FileNameList.GetItemText( iChuli , 2 ).GetLength()));						//记录路径名
						strTmpFileName = strFilenameAviNow;	
						strTmpTotalFrames = dlg->m_FileNameList.GetItemText( iChuli , 3 );//记录的总帧数
						iNum = 0;
						iBeginNum = 0;
						iEndNum = 0;
						iTotalFrames = atoi(strTmpTotalFrames);
						if (((StrRecName*)lpParameter)->bCount == TRUE)
						{
							iBeginNum = ((StrRecName*)lpParameter)->iCountA; //LoadImage开始load的帧数
							iEndNum   =	((StrRecName*)lpParameter)->iCountB; //LoadImage结束load的帧数	
							iTotalFrames = iEndNum -iBeginNum; //需要读取处理的总帧数
							iNum = iBeginNum;
						}
						
						iTotalUncom = iTotalFrames;
						iTotalLeft = iTotalUncom;//总共读取的帧数
						iReadBuffer=100;//缓存大小
						iReadTimes = 0;	
						nRetCode=0;
						i = 0;
						
						// 设置采集卡
						okStopCapture(hBoard);
						okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
						okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//设置SCREEN为8位
						
						//改变缓存大小设置，取代默认的640x480
						// 根据图像大小设置BUFFER大小	
						//从str_4中提取当前处理图像的宽和高，并进行设置
						iAVIStride = 0;
						iAVIHeight = 0;
						strTmpSize = dlg->m_FileNameList.GetItemText( iChuli , 4 );//提取图像大小
						iTmpGet = strTmpSize.Find('*');
						strTmpStride = strTmpSize.Left(iTmpGet);
						iTmpLength = strTmpSize.GetLength();
						strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
						iAVIStride = atoi(strTmpStride);
						iAVIHeight = atoi(strTmpHeight);
						assert(iAVIStride != 0);//防止为0
						assert(iAVIHeight != 0);
						SetRect(&rect,0,0,iAVIStride,iAVIHeight);
						okSetTargetRect(hBoard,BUFFER,&rect);
						okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
						
						if (iAVIStride > 800 && iAVIHeight >600)
						{
							SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
							gDlg->m_Screen.GetWindowRect(&rect); 
							gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
						}
						else
						{
							gDlg->m_Screen.GetWindowRect(&rect); 
							gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
						}
						lHeight = iAVIHeight;
						lStride = iAVIStride;
												
						sprintf(fileName,dlg->m_FileNameList.GetItemText( iChuli , 7 ));
						//LoadFileName
						sprintf(beginFileName,"%s,beg",fileName);
						sprintf(midFileName,"%s,con",fileName);
						sprintf(endFileName,"%s,end",fileName);

						
						//Create Save File name and path 2008.12.7
						iLocaBegin = strTmpPathOnly.Find('\\',4);
						iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
						strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
						if (strLocation == "")
						{
							strLocation.Format("%d-%d",currenttime->wHour,currenttime->wMinute);
						}				
						sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
						dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
						if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
							CreateDirectory(chTmpFileName,NULL);				
						if (((StrRecName*)lpParameter)->bCount == TRUE)
						{
							sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						}
						else
							sprintf(chSaveFileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
						if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
							DeleteFile(chSaveFileName);
			//////////////////////////////////////////////////////////////////////////
						
			//////////////////////////////////////////////////////////////////////////
			//处理
						okLoadImageFile(hBoard,beginFileName,0,BUFFER,0,0);
						GetLocalTime(currenttime);						
						iReadTimes = 0;	
						myElegansFeatures.InitStructData(lStride,lHeight); //bug delete 2009.4.20此处lstridered=0，需用lstride作为变量
						for(;;)
						{
							if (iTotalLeft <= 0 || bActive == 0)
							{	
								okLoadImageFile(hBoard,endFileName,0,BUFFER,0,0);
								okStopCapture(hBoard);
								::InvalidateRect(NULL,NULL,TRUE);
								iNum = 0;
								break;
							}
							if (iTotalLeft >= iReadBuffer) 
							{
								iTotalLeft = iTotalLeft-iReadBuffer;
								sprintf(chTmpMsg,strMessageLoad);
								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
								
								okLoadImageFile(hBoard,midFileName,iNum,BUFFER,0,iReadBuffer);	
								
								// 
								for(i=0;i<iReadBuffer;i++)
								{
									// 获取缓存中的图像数据保存地址；
									structEData.lpbuf =NULL;
									structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
									lStrideRed = lStride/3;
									//okConvertRect(hBoard,SCREEN,0,BUFFER,i,0);
									
									myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
									if (!::IsIconic(hWnd))
									{
										if (lHeight > 800 && lStride > 600) 
										{
											//特殊处理 若图像大于800*600，则缩小1/4显示
											myElegansFeatures.MemCopyHalf(structEData.lpRedBuf,structEData.lpHalf,lHeight,lStrideRed);
											//get image to app buffer from tgt
											g_blk.lpBits = structEData.lpHalf;			
											g_blk.iWidth = (short)(lStrideRed*0.5);
											g_blk.iHeight = (short)(lHeight*0.5); //to invert y
											g_blk.iBitCount = 8;
											g_iSizeImage = lStrideRed * lHeight;
											g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
											g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
											okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
										}
										else
											okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
									}
									
									g_blk.lpBits = structEData.lpRedBuf;			
									g_blk.iWidth = (short)(lStrideRed);
									g_blk.iHeight = (short)(lHeight); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStrideRed * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okSaveImageFile(hBoard,chSaveFileName,iNum,(TARGET)&g_blk,0,1);
									
									iNum+=1;
									
									// 发送自定义消息，使进度条更新；
									::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
								}
								sprintf(chTmpMsg,strMessageSave);
								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

								//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iReadBuffer);
								okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
								ZeroMemory(lpLinear,dwSize);
								iReadTimes += 1;
							}							
							if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
							{
								sprintf(chTmpMsg,strMessageLoad);
								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
								
								okLoadImageFile(hBoard,midFileName,iNum,BUFFER,0,iTotalLeft);
								
								// 
								for(i=0;i<iTotalLeft;i++)
								{
									// 获取缓存中的图像数据保存地址；
									structEData.lpbuf =NULL;
									structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
									lStrideRed = lStride/3;
									//okConvertRect(hBoard,SCREEN,0,BUFFER,i,0);
									
									myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
									if (!::IsIconic(hWnd))
									{
										if (lHeight > 800 && lStride > 600) 
										{
											//特殊处理 若图像大于800*600，则缩小1/4显示
											myElegansFeatures.MemCopyHalf(structEData.lpRedBuf,structEData.lpHalf,lHeight,lStrideRed);
											//get image to app buffer from tgt
											g_blk.lpBits = structEData.lpHalf;			
											g_blk.iWidth = (short)(lStrideRed*0.5);
											g_blk.iHeight = (short)(lHeight*0.5); //to invert y
											g_blk.iBitCount = 8;
											g_iSizeImage = lStrideRed * lHeight;
											g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
											g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
											okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
										}
										else
											okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
									}
									
									g_blk.lpBits = structEData.lpRedBuf;			
									g_blk.iWidth = (short)(lStrideRed);
									g_blk.iHeight = (short)(lHeight); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStrideRed * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okSaveImageFile(hBoard,chSaveFileName,iNum,(TARGET)&g_blk,0,1);

									iNum+=1;
									
									// 发送自定义消息，使进度条更新；
									::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
								}
								sprintf(chTmpMsg,strMessageSave);
								::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
								
								//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iTotalLeft);
								okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
								ZeroMemory(lpLinear,dwSize);
								iReadTimes += 1;
								iTotalLeft = 0;
							}//end if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						}//End for(;;)
						
						if (structEData.lpPath != NULL)
						{
							myElegansFeatures.DestroyStructData();
						}
						
						// 发送自定义消息，得到分析耗用时间；
						::PostMessage(hWnd,WM_GET_TIME,0,0);
						sprintf(chTmpMsg,strMessageEnd);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

						iNum = 0;  
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						ZeroMemory(lpLinear,dwSize);
						okStopCapture(hBoard);
						InvalidateRect(NULL,NULL,TRUE);
			//////////////////////////////////////////////////////////////////////////
			
						StateNow.Format("O");
						UpdateWindow(hWnd);
						m_itmpId = atoi(dlg->m_FileNameList.GetItemText(iChuli,0));
						dlg->m_FileNameList.SetItemText( iChuli, 8, StateNow );
						dlg->m_FileNameList.UpdateWindow();
						::PostMessage(hWnd,WM_EDIT_DATABASE,m_itmpId,(LPARAM)&StateNow);
						Sleep(100);//打开数据库比较慢，程序会先执行后面的程序,所以要独占CPU
						sprintf(chTmpMsg,_T("第%d个数据提取完成!\r\n%s 共提取%d帧，数据存放在相同路径下\r\n\r\n"),iChuli+1,strFilenameAviNow,iTotalFrames);
						////g_strErrMes.Format("第%d个数据提取完成!\r\n%s 共提取%d帧，数据存放在相同路径下\r\n\r\n",iChuli+1,strFilenameAviNow,iTotalFrames);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(100);
						dlg->m_FileNameList.UpdateWindow();
					}	
					else
					{
						sprintf(chTmpMsg,_T("\r\nNo.%d has been processed.\r\n"),iChuli+1);
						////g_strErrMes.Format("\r\nNo.%d has been processed.\r\n",iChuli+1);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(100);
					}
				}//End of for(iChuli=0;iChuli<end;iChuli++)

				sprintf(chTmpMsg,_T("\r\nComplished!!!\r\n%d movies have been processed totally.\r\n"),end);
				////g_strErrMes.Format("\r\nComplished!!!\r\n%d movies have been processed totally.\r\n",end);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				bActive = 0;
				bWhile=FALSE;
			}
			else
			{
//单个分析-解压缩
				okLoadImageFile(hBoard,beginFileName,0,BUFFER,0,0);
				GetLocalTime(currenttime);

				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime->wHour,currenttime->wMinute);
				}				
				sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
				if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
					CreateDirectory(chTmpFileName,NULL);				
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
					sprintf(chSaveFileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);

				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
				lStrideRed = lStride/3;
				myElegansFeatures.InitStructData(lStrideRed,lHeight);

/*
				//Save the results in the form of AVI movie
				g_cvSavImg = cvCreateImage(cvSize(lStrideRed,lHeight),8,1);
				g_cvColorImg = cvCreateImage(cvSize(lStrideRed,lHeight),8,3);

				cvSet(g_cvColorImg,cvScalarAll(0),0);
				memset(g_cvSavImg->imageData,0,lStrideRed*lHeight*sizeof(char));
				g_cvSavVideo = cvCreateAVIWriter(chSaveFileName,-1, (double)fRate , cvSize(lStrideRed,lHeight) ,0);
*/
				for(;;)
				{
					if (iTotalLeft <= 0 || bActive == 0)
					{	
						okLoadImageFile(hBoard,endFileName,0,BUFFER,0,0);
						okStopCapture(hBoard);
						::InvalidateRect(NULL,NULL,TRUE);
						iNum = 0;
						break;
					}
					if (iTotalLeft >= iReadBuffer) 
					{
						iTotalLeft = iTotalLeft-iReadBuffer;
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						okLoadImageFile(hBoard,midFileName,iNum,BUFFER,0,iReadBuffer);	
						
						// 
						for(i=0;i<iReadBuffer;i++)
						{
							// 获取缓存中的图像数据保存地址；
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
							lStrideRed = lStride/3;
							//okConvertRect(hBoard,SCREEN,0,BUFFER,i,0);
							
							myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
							if (!::IsIconic(hWnd))
							{
								if (lHeight > 800 && lStride > 600) 
								{
									//特殊处理 若图像大于800*600，则缩小1/4显示
									myElegansFeatures.MemCopyHalf(structEData.lpRedBuf,structEData.lpHalf,lHeight,lStrideRed);
									//get image to app buffer from tgt
									g_blk.lpBits = structEData.lpHalf;			
									g_blk.iWidth = (short)(lStrideRed*0.5);
									g_blk.iHeight = (short)(lHeight*0.5); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStrideRed * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
								}
								else
									okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
							}
							

							g_blk.lpBits = structEData.lpRedBuf;			
							g_blk.iWidth = (short)(lStrideRed);
							g_blk.iHeight = (short)(lHeight); //to invert y
							g_blk.iBitCount = 8;
							g_iSizeImage = lStrideRed * lHeight;
							g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
							g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
							okSaveImageFile(hBoard,chSaveFileName,iNum,(TARGET)&g_blk,0,1);

/*
							//从OK的BUFFER中拷贝当前帧数据
							memcpy(g_cvSavImg->imageData,structEData.lpRedBuf,lStrideRed*lHeight*sizeof(char));	
							cvWriteToAVI(g_cvSavVideo,g_cvSavImg);
*/
							iNum+=1;
							
							// 发送自定义消息，使进度条更新；
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
					 	//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iReadBuffer);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						ZeroMemory(lpLinear,dwSize);
						iReadTimes += 1;
					}
					
					if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
					{
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						okLoadImageFile(hBoard,midFileName,iNum,BUFFER,0,iTotalLeft);
						
						// 
						for(i=0;i<iTotalLeft;i++)
						{
							// 获取缓存中的图像数据保存地址；
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
							lStrideRed = lStride/3;
							//okConvertRect(hBoard,SCREEN,0,BUFFER,i,0);
							
							myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
							if (!::IsIconic(hWnd))
							{
								if (lHeight > 800 && lStride > 600) 
								{
									//特殊处理 若图像大于800*600，则缩小1/4显示
									myElegansFeatures.MemCopyHalf(structEData.lpRedBuf,structEData.lpHalf,lHeight,lStrideRed);
									//get image to app buffer from tgt
									g_blk.lpBits = structEData.lpHalf;			
									g_blk.iWidth = (short)(lStrideRed*0.5);
									g_blk.iHeight = (short)(lHeight*0.5); //to invert y
									g_blk.iBitCount = 8;
									g_iSizeImage = lStrideRed * lHeight;
									g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
									g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
									okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
								}
								else
									okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
							}


							g_blk.lpBits = structEData.lpRedBuf;			
							g_blk.iWidth = (short)(lStrideRed);
							g_blk.iHeight = (short)(lHeight); //to invert y
							g_blk.iBitCount = 8;
							g_iSizeImage = lStrideRed * lHeight;
							g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
							g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
							okSaveImageFile(hBoard,chSaveFileName,iNum,(TARGET)&g_blk,0,1);

/*							
							//从OK的BUFFER中拷贝当前帧数据
							memcpy(g_cvSavImg->imageData,structEData.lpRedBuf,lStrideRed*lHeight*sizeof(char));	
							cvWriteToAVI(g_cvSavVideo,g_cvSavImg);
*/
							iNum+=1;
							
							// 发送自定义消息，使进度条更新；
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
						
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						
						//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iTotalLeft);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						ZeroMemory(lpLinear,dwSize);
						iReadTimes += 1;
						iTotalLeft = 0;
					}//end if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
				}//End for(;;)

/*
				cvReleaseVideoWriter(&g_cvSavVideo);
				if (g_cvSavImg != NULL && g_cvColorImg != NULL)
				{
					//release saving image
					cvReleaseImage(&g_cvSavImg);
					cvReleaseImage(&g_cvColorImg);
					g_cvSavImg = NULL;
					g_cvColorImg = NULL;
				}
*/
				// 发送自定义消息，得到分析耗用时间；
				::PostMessage(hWnd,WM_GET_TIME,0,0);
				sprintf(chTmpMsg,strMessageEnd);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);


				if (structEData.lpPath != NULL)
				{
					myElegansFeatures.DestroyStructData();
				}
				
				bActive = 0;
				iNum = 0;  
				okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
				ZeroMemory(lpLinear,dwSize);
				okStopCapture(hBoard);
				InvalidateRect(NULL,NULL,TRUE);
			}
			bWhile = FALSE;	
		}//End if (bActive == 1)
	}//End while

	delete [] chTmpMsg;
	chTmpMsg = NULL;
	return 0;
}


//扩展功能面板，启动“特殊分析1”线程
void CAnalysisTestDlg::OnButSpecial1() 
{
	// TODO: Add your control notification handler code here
	StrRecName* RecPARAM = new StrRecName;
	if (m_CheckHistogram == TRUE)
	{
		//批量“特殊分析1”
		myFileListData.strID=m_FileNameList.GetItemText(0,0);	
		myFileListData.str_1=m_FileNameList.GetItemText(0,8);
		myFileListData.str_2=m_FileNameList.GetItemText(0,2);
		myFileListData.str_3=m_FileNameList.GetItemText(0,3);
		myFileListData.str_4=m_FileNameList.GetItemText(0,4);
		myFileListData.str_5=m_FileNameList.GetItemText(0,5);
		myFileListData.str_6=m_FileNameList.GetItemText(0,6);
		myFileListData.str_7=m_FileNameList.GetItemText(0,7);
		myFileListData.str_8=m_FileNameList.GetItemText(0,1);
		
		m_NiSlide.Axis.Maximum = atoi(myFileListData.str_3);
		RecPARAM = &myFileListData;			
		
		RecPARAM->iFlag = 100;
		if (RecPARAM->bCount == FALSE)
		{
			RecPARAM->iCountA = 0;
			RecPARAM->iCountB = 0;
		}
		
		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,TRUE);
		
		GetLocalTime(&sysTimeBegin);
		lSysTime = GetTickCount();
		g_iFlagSpecial = 1;//表示特殊分析的第一步

		g_iRunningFlag = 100;//100表示有处理进程在运行，0表示没有
		//开启分析线程
		hThread3 = CreateThread(NULL,0,SpecialProcessProc,(LPVOID)RecPARAM,0,&threadID_3);
	}
	else
	{
		//单个“特殊分析1”
		RecPARAM->iFlag = 0;
		if (myFileListData.strID == "" || myFileListData.str_1 == "已处理")
		{
			MessageBox("没有选择要分析的记录！or 选择的记录已处理!",NULL,MB_OK);
			return;
		}
		else
		{		
			StrRecName* tmpRecPARAM = new StrRecName;
			tmpRecPARAM = &myFileListData;
			tmpRecPARAM->iFlag = 0; //备用标志在分析处理时，0代表单个文件分析，100代表批量分析
			if (tmpRecPARAM->bCount == FALSE)
			{
				tmpRecPARAM->iCountA = 0;
				tmpRecPARAM->iCountB = 0;
			}
			
			bActive = 1;
			lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
			InvalidateRect(NULL,TRUE);
			
			GetLocalTime(&sysTimeBegin);
			lSysTime = GetTickCount();
			
			g_iFlagSpecial = 1;//表示特殊分析的第一步

			g_iRunningFlag = 100;//100表示有处理进程在运行，0表示没有
			//开启分析线程
			hThread3 = CreateThread(NULL,0,SpecialProcessProc,(LPVOID)tmpRecPARAM,0,&threadID_3);
			// Modified at 2009.4.22
			//在v2.4.15alpha版本前，此处有一个bug：tmpRecPARAM写成了RecPARAM！！
			//从而导致step one处理会报错！
			//这个bug提醒了局部变量的重要性！原本因为RecPARAM是一个全局变量，所以这里变量写错了也没有被编译器发现
		}
	}
}


//扩展功能面板，分析线程
DWORD WINAPI SpecialProcessProc(LPVOID lpParameter)
{
	//LPBYTE		lpLinear;
	//DWORD		dwSize;	
	CString strTmpID = ((StrRecName*)lpParameter)->strID;//记录ID号
	// 记录名，仅名称(单个分析传递记录名)
	CString strTmpNameOnly = ((StrRecName*)lpParameter)->str_2;
	strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,strTmpNameOnly.GetLength()-4));
	CString strTmpPathOnly = ((StrRecName*)lpParameter)->str_7; 
	strTmpPathOnly.Format("%s",strTmpPathOnly.Mid(0,((StrRecName*)lpParameter)->str_7.GetLength()-((StrRecName*)lpParameter)->str_2.GetLength()));

	//记录路径名(单个分析传递记录名路径)
	CString strTmpFileName = ((StrRecName*)lpParameter)->str_7;
	
	CString strTmpTotalFrames = ((StrRecName*)lpParameter)->str_3;//记录的总帧数
	int     iTmpFlag = ((StrRecName*)lpParameter)->iFlag;//单个分析 or 批量分析
	int iNum = 0;
	int iBeginNum = 0;
	int iEndNum = 0;
	int iTotalFrames = atoi(strTmpTotalFrames);
	if (((StrRecName*)lpParameter)->bCount == TRUE)
	{
		iBeginNum = ((StrRecName*)lpParameter)->iCountA; //LoadImage开始load的帧数
		iEndNum   =	((StrRecName*)lpParameter)->iCountB; //LoadImage结束load的帧数	
		iTotalFrames = iEndNum -iBeginNum; //需要读取处理的总帧数
		iNum = iBeginNum;
	}

	CString strTmpRate = ((StrRecName*)lpParameter)->str_8;//记录的帧率
	float fRate = atof(strTmpRate);


	LPBYTE		lpLinear;
	DWORD		dwSize;	

	//SaveFileName 2008.12.7
	CString strLocation = "";
	int iLocaBegin = 0; 	
	int iLocaEnd = 0;
	DWORD dwAttr;
	char chTmpFileName[256] = "\0";
	
	char fileName[256] = "\0";	 
	char edgeFileName[256] = "\0";
	char chSaveFileName[256] = "\0";
	int i = 0;
	int iTotalLeft=iTotalFrames;
	
	int iReadTimes = 0;
	CString strMessageBegin = "Begin To Process\r\n\0";
	CString strMessageLoad = "okLoadImageFile...\r\n\0";
	CString strMessageSave = "Saving Image...\r\n\0";
	CString strMessageSaveResults = "Please press the 'Save Results' button to acquire .mdb file.\r\n\0";
	CString strMessageEnd = "Congratulations!\0";
	char chTmpBinaryFile[256] = "\0";//缓存二值化图像
	char chTmpThinningFile[256] = "\0";//缓存细化图像
	char chTmpSkeletonFile[256] = "\0";//缓存骨架图像
	char chTmpEdgeFile[256] = "\0";//边缘图像
	CString strTmp;

	// 停止采集卡
	okStopCapture(hBoard);

	//改变缓存大小设置，取代默认的640x480
	short heightTemp;
	long strideTemp;
	CRect   rect;        // 根据图像大小设置BUFFER大小
	int iReadBuffer = 0; //缓存帧数设置
	//iReadBuffer = 500;

	
	//从str_4中提取当前处理图像的宽和高，并进行设置
	int iAVIStride = 0,iAVIHeight = 0;
	CString strTmpSize = ((StrRecName*)lpParameter)->str_4;//提取图像大小
	CString strTmpStride,strTmpHeight;
	int iTmpGet = strTmpSize.Find('*');
	strTmpStride = strTmpSize.Left(iTmpGet);
	int iTmpLength = strTmpSize.GetLength();
	strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
	iAVIStride = atoi(strTmpStride);
	iAVIHeight = atoi(strTmpHeight);
	assert(iAVIStride != 0);//防止为0
	assert(iAVIHeight != 0);

	SetRect(&rect,0,0,iAVIStride,iAVIHeight);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);
	
	if (iAVIStride > 800 && iAVIHeight >600)
	{
		SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
	}
	else
	{
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
	}

	char chStageFileName[255]="\0";
	int iIsErr;
	//double dCCD = 0;//um
	//double dMagnification = 0;

	//CFile testfile;//测试待处理文件是否存在并可以正常打开

	int *spp_iStatMemory = NULL;
	float *spp_fStatMemory = NULL;

	// Add by haining 2008.12.4批量处理需要的变量	
	SYSTEMTIME currenttime;
	int m_itmpId = 0;
	int iChuli = 0;
	CAnalysisTestDlg* dlg;
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();
	int nRetCode=0;
	int nTmpIndex = 0;

	//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	BOOL bWhile = TRUE;
	while (bWhile == TRUE)
	{
		if (bActive == 1)
		{
			if (iTmpFlag == 100)
			{
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

				//批量分析
				//Add by haining 2008.12.4
				int end = 0;
				CString StateNow = "";
				CString sql = "";
				CString strFilenameAviNow = "";
				end = dlg->m_FileNameList.GetItemCount();
				for(iChuli=0;iChuli<end;iChuli++)
				{
					sprintf(chTmpMsg,_T("In Progress...The No.%d is being performed.\r\n"),iChuli+1);
					////g_strErrMes.Format("In Progress...The No.%d is being performed.\r\n",iChuli+1);
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
					Sleep(30);
					StateNow.Format("%s",dlg->m_FileNameList.GetItemText( iChuli , 8 ));
					if(StateNow == "X")
					{
						strFilenameAviNow = dlg->m_FileNameList.GetItemText( iChuli , 7 );
						StateNow.Format("Processing...");
						dlg->m_FileNameList.SetItemText( iChuli, 8, "Processing...");
						dlg->m_FileNameList.UpdateWindow();
						//AfxMessageBox(strFilenameAviNow);
						
			//////////////////////////////////////////////////////////////////////////
			//参数设置
						strTmpNameOnly.Format("%s",dlg->m_FileNameList.GetItemText( iChuli , 2 ).Mid(0,dlg->m_FileNameList.GetItemText( iChuli , 2 ).GetLength()-4));
						strTmpPathOnly.Format("%s",strFilenameAviNow.Mid(0,strFilenameAviNow.GetLength()
							-dlg->m_FileNameList.GetItemText( iChuli , 2 ).GetLength()));
						//记录路径名
						strTmpFileName = strFilenameAviNow;	
						strTmpTotalFrames = dlg->m_FileNameList.GetItemText( iChuli , 3 );//记录的总帧数
						iNum = 0;
						iBeginNum = 0;
						iEndNum = 0;
						iTotalFrames = atoi(strTmpTotalFrames);
						if (((StrRecName*)lpParameter)->bCount == TRUE)
						{
							iBeginNum = ((StrRecName*)lpParameter)->iCountA; //LoadImage开始load的帧数
							iEndNum   =	((StrRecName*)lpParameter)->iCountB; //LoadImage结束load的帧数	
							iTotalFrames = iEndNum -iBeginNum; //需要读取处理的总帧数
							iNum = iBeginNum;
						}
						
						iTotalLeft = iTotalFrames;//总共读取的帧数
						iReadBuffer=300;//缓存大小
						iReadTimes = 0;	
						nRetCode=0;
						i = 0;
						
						// 设置采集卡
						okStopCapture(hBoard);
						okSetCaptureParam(hBoard,CAPTURE_BUFRGBFORMAT,FORM_GRAY8);
						okSetCaptureParam(hBoard,CAPTURE_SCRRGBFORMAT,FORM_GRAY8);//设置SCREEN为8位
						
						//改变缓存大小设置，取代默认的640x480
						// 根据图像大小设置BUFFER大小	
						//从str_4中提取当前处理图像的宽和高，并进行设置
						iAVIStride = 0;
						iAVIHeight = 0;
						strTmpSize = dlg->m_FileNameList.GetItemText( iChuli , 4 );//提取图像大小
						iTmpGet = strTmpSize.Find('*');
						strTmpStride = strTmpSize.Left(iTmpGet);
						iTmpLength = strTmpSize.GetLength();
						strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
						iAVIStride = atoi(strTmpStride);
						iAVIHeight = atoi(strTmpHeight);
						assert(iAVIStride != 0);//防止为0
						assert(iAVIHeight != 0);

						SetRect(&rect,0,0,iAVIStride,iAVIHeight);
						okSetTargetRect(hBoard,BUFFER,&rect);
						okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);						
						if (iAVIStride > 800 && iAVIHeight >600)
						{
							SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
							gDlg->m_Screen.GetWindowRect(&rect); 
							gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
						}
						else
						{
							gDlg->m_Screen.GetWindowRect(&rect); 
							gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
						}

						lHeight = iAVIHeight;
						lStride = iAVIStride;
						
			//////////////////////////////////////////////////////////////////////////
			//分析线程中的文件名初始化
						//原始文件路径
						sprintf(fileName,strTmpFileName);
						GetLocalTime(&currenttime);
						sprintf(chTmpFileName,"E:\\Worm Data\\%s-%d%d",
							strTmpNameOnly,currenttime.wHour,currenttime.wMinute);						
						//创建一个新的文件夹路径
						dwAttr = GetFileAttributes(chTmpFileName);
						if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
							CreateDirectory(chTmpFileName,NULL);						
						//二值化中间数据 路径
						sprintf(chTmpBinaryFile,"%s\\%s",chTmpFileName,strTmpNameOnly);//B 表示Binary
						//细化中间数据 路径
						sprintf(chTmpThinningFile,"%s\\T%s",chTmpFileName,strTmpNameOnly);//T 表示Thin
						//骨架中间数据 路径
						sprintf(chTmpSkeletonFile,"%s\\S%s",chTmpFileName,strTmpNameOnly);//S 表示Skeleton
						//边缘数据 路径
						sprintf(chTmpEdgeFile,"%s\\E%s",chTmpFileName,strTmpNameOnly);//E 表示edge
					
						g_strFileName = fileName;						
						nTmpIndex = 0;
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//分析线程中的变量初始化
						//初始化structEData中的相关变量
						structEData.nImgOfProc=iTotalFrames;//获得此次要处理的帧数
						myElegansFeatures.InitStructData(iAVIHeight,iAVIStride);
						myElegansFeatures.DoPretreatment.InitData(iAVIHeight,iAVIStride);
						myElegansFeatures.InitDataOfMove();	
						//参数导出预备
						dpArray.RemoveAll();
						AddData();						
						//读入X-Y stage coordinates信息到flatx，flaty；
						sprintf(chStageFileName,"%s,mpg4.txt",strTmpFileName);
						if (((StrRecName*)lpParameter)->bCount == TRUE)
						{
							iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,iBeginNum,iEndNum);
						}
						else
						{
							iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,0,iTotalFrames);
						}
						
						if (iIsErr == 1)
						{
							sprintf(chTmpMsg,_T("Can not find or open XY-stage coordinates!!!\r\n"));
							////g_strErrMes.Format("Can not find or open XY-stage coordinates!!!\r\n");
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						}
						else if(iIsErr == -1)
						{
							return -1;
						}					
						sprintf(chTmpMsg,_T("XY stage's coordinates is successfully reloaded!\r\n"));
						////g_strErrMes.Format("XY stage's coordinates is successfully reloaded!\r\n");
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(200);
						
						//读取放大倍数，得到换算比例尺
						sprintf(chTmpMsg,_T("像素与实际空间的比例是1个像素对应 %5fum!\r\n"),g_dCCDScale);
						////g_strErrMes.Format("像素与实际空间的比例是1个像素对应 %5fum!\r\n",g_dCCDScale);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(100);
						//VS-802B CCD + Leica MZ16
						//dCCD = 6.0;//um
						//dMagnification = 4.0 * 0.63;
						//g_dCCDScale = dCCD / dMagnification;
						
						//AM1531 CCD
						//double dCCD = 6.45;//um
						//double dMagnification = 4.0 * 0.5;
						//g_dCCDScale = dCCD / dMagnification;
						
						//葛茜版本
						//g_dCCDScale = 6.32911;//um
						
						//两帧间隔时间
						structEData.fTime = (float)(1.0/fRate);
						structEData.structfRate = fRate;
						//Add by haining 2009.4.23
						//计算两帧间隔时间后，计算得虫体两帧最大运动距离（以速率500um/s计算）
						g_dMaxMove = MaxMove * structEData.fTime;
						
						//进入分析前，根据目前数据特征，计算校正参数
						if (iTotalFrames != 0 && fRate != 0)
						{
							//Assume the largest Bodybends is 30 times/min;
							if (fRate <= 8.5)
							{
								g_iBodyBendsFilter = (int)((fRate * 60.0)/60.0);
							}
							else if (fRate > 8.5) 
							{
								g_iBodyBendsFilter = 2 + (int)((fRate * 60.0)/60.0);
							}		
						}						
					
						if (spp_iStatMemory == NULL && spp_fStatMemory == NULL)
						{
							spp_iStatMemory = new int[iTotalFrames];//计算统计值时的临时变量
							memset(spp_iStatMemory,0,iTotalFrames*sizeof(int));							
							spp_fStatMemory = new float[iTotalFrames];//计算统计值时的临时变量
							memset(spp_fStatMemory,0,iTotalFrames*sizeof(float));
						}
						else
						{
							sprintf(chTmpMsg,_T("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n"));
							////g_strErrMes.Format("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n");
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						}
			//////////////////////////////////////////////////////////////////////////
			//处理
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//特征分析1,g_iFlagSpecial = 1
						if (g_iFlagSpecial == 1)
						{
							sprintf(chTmpMsg,strMessageBegin);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
							//Sleep(100);
							iTotalLeft=iTotalFrames;
							//注意：直接处理原始avi数据时，由于是三个通道的数据，所以每帧640*480*900K
							//则只能去buffer为500帧——450MB；
							//若1024*1024的图像，则只能设置200帧——600MB；
							iReadBuffer = g_iReadBuffer;
							iReadTimes = 0;	
							iNum = 0;

							//Create Save File name and path 2008.12.7
							iLocaBegin = strTmpPathOnly.Find('\\',4);
							iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
							strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
							if (strLocation == "")
							{
								strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
							}				
							sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
							dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
							if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
								CreateDirectory(chTmpFileName,NULL);
							if (((StrRecName*)lpParameter)->bCount == TRUE)
							{
								//step one 读取来自Uncompress的数据
								sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
								//step one 保存的处理结果
								sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Binary.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
							}
							else
							{
								//step one 读取来自Uncompress的数据
								sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
								//step one 保存的处理结果
								sprintf(chSaveFileName,"%s\\%s-all-8Binary.avi",chTmpFileName,strTmpNameOnly);
							}
							//if(strnicmp(strrchr(fileName,'.'),".avi",4))
							//	AfxMessageBox("找不到待处理的文件!");
							if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
								DeleteFile(chSaveFileName);
							g_strFileName = fileName;
							
							if (gDlg->m_ChooseForStepOne == TRUE )
							{
								//若选择RunningAvg算法，则进行初始化
								okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
								okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								cvPFrameMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
								cvPFrMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
								cvPBkMat = cvCreateMat(lHeight, lStride, CV_32FC1);
							}

							for(;;)
							{
								if (iTotalLeft <= 0 || bActive == 0)
								{	
									okStopCapture(hBoard);
									InvalidateRect(NULL,NULL,TRUE);
									iNum = 0;
									break;
								}
								if (iTotalLeft >= iReadBuffer) 
								{
									iTotalLeft = iTotalLeft-iReadBuffer;
									// 发送自定义消息
									sprintf(chTmpMsg,strMessageLoad);
									::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
									okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	
									
									//////////////////////////////////////////////////////////////////////////
									// 一
									for(i=0;i<iReadBuffer;i++)
									{
										// 获取缓存中的图像数据保存地址；
										structEData.lpbuf =NULL;
										structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
										lStrideRed = lStride;
										
										//特殊处理 根据情况定制设计 二
										//特殊分析1(清理二值图像)
										//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
										//2008.12.6 step one直接处理单通道8bit灰度图像
										//2009.3.31
										if (gDlg->m_ChooseForStepOne == TRUE )
										{
											//RunningAvg
											myElegansFeatures.SpecialExtractionRunningAvg(structEData.lpbuf,lHeight,lStrideRed,iNum);
										}
										else if (gDlg->m_ChooseForStepOne == FALSE)
										{
											//原有OTSU算法
											myElegansFeatures.SpecialExtraction(structEData.lpbuf,lHeight,lStrideRed,iNum);
										}
										
										
										if (!IsIconic(hWnd))
										{
											if (lHeight > 800 && lStride > 600) 
											{
												//特殊处理 若图像大于800*600，则缩小1/4显示
												//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
												myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStrideRed);
												//get image to app buffer from tgt
												g_blk.lpBits = structEData.lpHalf;			
												g_blk.iWidth = (short)(lStride*0.5);
												g_blk.iHeight = (short)(lHeight*0.5); //to invert y
												g_blk.iBitCount = 8;
												g_iSizeImage = lStride * lHeight;
												g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
												g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
												okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
												//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
											}
											else
											{
												//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
												okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
											}
										}
										iNum+=1;
										
										// 发送自定义消息，使进度条更新；
										::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
									}
									// 发送自定义消息,正在存储
									sprintf(chTmpMsg,strMessageSave);
									::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

									okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
										,BUFFER,0,iReadBuffer);
									okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
									memset(lpLinear, 255, dwSize);
									
									iReadTimes += 1;
								}
								if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
								{
									// 发送自定义消息
									sprintf(chTmpMsg,strMessageLoad);
									::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
									
									okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);
									
									//////////////////////////////////////////////////////////////////////////
									// 二
									for(i=0;i<iTotalLeft;i++)
									{
										// 获取缓存中的图像数据保存地址；
										structEData.lpbuf =NULL;
										structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
										lStrideRed = lStride;
										
										//特殊处理 根据情况定制设计 二
										//特殊分析1(清理二值图像)
										//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
										//2008.12.6 step one直接处理单通道8bit灰度图像
										//2009.3.31
										if (gDlg->m_ChooseForStepOne == TRUE )
										{
											//RunningAvg
											myElegansFeatures.SpecialExtractionRunningAvg(structEData.lpbuf,lHeight,lStrideRed,iNum);
										}
										else if (gDlg->m_ChooseForStepOne == FALSE)
										{
											//原有OTSU算法
											myElegansFeatures.SpecialExtraction(structEData.lpbuf,lHeight,lStrideRed,iNum);
										}
										
										
										if (!IsIconic(hWnd))
										{
											if (lHeight > 800 && lStride > 600) 
											{
												//特殊处理 若图像大于800*600，则缩小1/4显示
												//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
												myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStrideRed);
												//get image to app buffer from tgt
												g_blk.lpBits = structEData.lpHalf;			
												g_blk.iWidth = (short)(lStride*0.5);
												g_blk.iHeight = (short)(lHeight*0.5); //to invert y
												g_blk.iBitCount = 8;
												g_iSizeImage = lStride * lHeight;
												g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
												g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
												okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
												//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
											}
											else
											{
												//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
												okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
											}
										}
										iNum+=1;
										
										// 发送自定义消息，使进度条更新；
										::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
									}							

									// 发送自定义消息,正在存储
									sprintf(chTmpMsg,strMessageSave);
									::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
									
									okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
										,BUFFER,0,iTotalLeft);
									okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
									memset(lpLinear, 255, dwSize);

									iReadTimes += 1;
									iTotalLeft = 0;
								}
							}//特征分析1结束
							// 发送自定义消息，得到分析耗用时间；
							::PostMessage(hWnd,WM_GET_TIME,0,0);							
							iNum = 0;  							

							if (cvPFrameMat != NULL)
							{
								//释放用于动态背景滤除的矩阵
								cvReleaseMat(&cvPFrameMat);
								cvReleaseMat(&cvPFrMat);
								cvReleaseMat(&cvPBkMat);	
							}

							sprintf(chTmpMsg,strMessageEnd);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
							
							okStopCapture(hBoard);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);
							InvalidateRect(NULL,NULL,TRUE);
						}//if (g_iFlagSpecial == 1)
                   //////////////////////////////////////////////////////////////////////////
			
						StateNow.Format("O");
						UpdateWindow(hWnd);
						m_itmpId = atoi(dlg->m_FileNameList.GetItemText(iChuli,0));
						dlg->m_FileNameList.SetItemText( iChuli, 8, StateNow );
						dlg->m_FileNameList.UpdateWindow();
						::PostMessage(hWnd,WM_EDIT_DATABASE,m_itmpId,(LPARAM)&StateNow);
						Sleep(100);//打开数据库比较慢，程序会先执行后面的程序,所以要独占CPU
						sprintf(chTmpMsg,_T("第%d个数据提取完成!\r\n%s 共提取%d帧，数据存放在相同路径下\r\n\r\n"),iChuli+1,strFilenameAviNow,iTotalFrames);
						////g_strErrMes.Format("第%d个数据提取完成!\r\n%s 共提取%d帧，数据存放在相同路径下\r\n\r\n",iChuli+1,strFilenameAviNow,iTotalFrames);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(100);
						dlg->m_FileNameList.UpdateWindow();
					}	
					else
					{
						sprintf(chTmpMsg,_T("\r\nNo.%d has been processed.\r\n"),iChuli+1);
						////g_strErrMes.Format("\r\nNo.%d has been processed.\r\n",iChuli+1);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						Sleep(100);
					}


					//每处理完一个数据，释放占用内存
					if (structEData.path != NULL)
					{
						myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
					}
					if (myElegansFeatures.DoPretreatment.C != NULL)
					{
						myElegansFeatures.DoPretreatment.DestroyData();
					}
					if (myElegansFeatures.DoParadistill.m_hAglRate != NULL)
					{
						myElegansFeatures.DestroyDataOfMove();	
					}	
					

					if (spp_iStatMemory != NULL)
					{
						delete [] spp_iStatMemory;
						spp_iStatMemory = NULL;
					}
					if (spp_fStatMemory != NULL)
					{
						delete [] spp_fStatMemory;
						spp_fStatMemory = NULL;
					}
				}//End of for(iChuli=0;iChuli<end;iChuli++)

				sprintf(chTmpMsg,_T("\r\nComplished!!!\r\n%d movies have been processed totally.\r\n"),end);
				////g_strErrMes.Format("\r\nComplished!!!\r\n%d movies have been processed totally.\r\n",end);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
				memset(lpLinear, 255, dwSize);
				InvalidateRect(NULL,NULL,TRUE);
				bActive = 0;
				bWhile=FALSE;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
			} //end of Batch Process
			else
			{
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

	//单个分析
	//单个分析
	//单个分析
	//单个分析
	//单个分析
				//初始化structEData中的相关变量
				structEData.nImgOfProc=iTotalFrames;//获得此次要处理的帧数
				myElegansFeatures.InitStructData(iAVIHeight,iAVIStride);
				myElegansFeatures.DoPretreatment.InitData(iAVIHeight,iAVIStride);
				myElegansFeatures.InitDataOfMove();
				
				//structEData.nImgOfProc=iTotalFrames;//获得此次要处理的帧数
				
				//参数导出预备
				dpArray.RemoveAll();
				AddData();
										
				//2008.12.7
				//坐标信息的文件名直接是原始数据名+,mpg4.txt；
				//坐标信息文件还是放在原始数据文件夹
				//读入X-Y stage coordinates信息到flatx，flaty；
				sprintf(chStageFileName,"%s,mpg4.txt",strTmpFileName);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,iBeginNum,iEndNum);
				}
				else
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,0,iTotalFrames);
				}
				
				if (iIsErr == 1)
				{
					sprintf(chTmpMsg,_T("Can not find or open XY-stage coordinates!!!\r\n\0"));
					////g_strErrMes.Format("Can not find or open XY-stage coordinates!!!\r\n");
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}
				else if(iIsErr == -1)
				{
					return -1;
				}
				
				sprintf(chTmpMsg,_T("XY stage's coordinates is successfully reloaded!\r\n\0"));
				////g_strErrMes.Format("XY stage's coordinates is successfully reloaded!\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				
				//读取放大倍数，得到换算比例尺
				sprintf(chTmpMsg,_T("像素与实际空间的换算比例是1个像素对应 %5f!\r\n\0"),g_dCCDScale);
				////g_strErrMes.Format("像素与实际空间的换算比例是1个像素对应 %5f!\r\n",g_dCCDScale);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);

				//VS-802B CCD
				//dCCD = 6.0;//um
				//dMagnification = 4.0 * 0.63;
				//g_dCCDScale = dCCD / dMagnification;				
				//AM1531 CCD
				//double dCCD = 6.45;//um
				//double dMagnification = 4.0 * 0.5;
				//g_dCCDScale = dCCD / dMagnification;				
				//葛茜版本
				//g_dCCDScale = 6.32911;//um
				
				//两帧间隔时间
				structEData.fTime = (float)(1.0/fRate);
				structEData.structfRate = fRate;
				//Add by haining 2009.4.23
				//计算两帧间隔时间后，计算得虫体两帧最大运动距离（以速率500um/s计算）
				g_dMaxMove = MaxMove * structEData.fTime;
				
				//进入分析前，根据目前数据特征，计算校正参数
				if (iTotalFrames != 0 && fRate != 0)
				{
					//Assume the largest Bodybends is 30 times/min;
					if (fRate <= 8.5)
					{
						g_iBodyBendsFilter = (int)((fRate * 60.0)/60.0);
					}
					else if (fRate > 8.5) 
					{
						g_iBodyBendsFilter = 2 + (int)((fRate * 60.0)/60.0);
					}		
				}

				
				if (spp_iStatMemory == NULL && spp_fStatMemory == NULL)
				{
					spp_iStatMemory = new int[iTotalFrames];//计算统计值时的临时变量
					memset(spp_iStatMemory,0,iTotalFrames*sizeof(int));							
					spp_fStatMemory = new float[iTotalFrames];//计算统计值时的临时变量
					memset(spp_fStatMemory,0,iTotalFrames*sizeof(float));
				}
				else
				{
					sprintf(chTmpMsg,_T("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n"));
					////g_strErrMes.Format("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n");
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}
				
				GetLocalTime(&currenttime);
/*
				sprintf(chTmpFileName,"E:\\Worm Data\\%s-%d%d",
					strTmpNameOnly,currenttime.wHour,currenttime.wMinute);				
				//创建一个新的文件夹路径
				dwAttr = GetFileAttributes(chTmpFileName);
				if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
					CreateDirectory(chTmpFileName,NULL);		
				//二值化中间数据 路径
				sprintf(chTmpBinaryFile,"%s\\%s",chTmpFileName,strTmpNameOnly);//B 表示Binary
				//细化中间数据 路径
				sprintf(chTmpThinningFile,"%s\\T%s",chTmpFileName,strTmpNameOnly);//T 表示Thin
				//骨架中间数据 路径
				sprintf(chTmpSkeletonFile,"%s\\S%s",chTmpFileName,strTmpNameOnly);//S 表示Skeleton
				//边缘数据 路径
				sprintf(chTmpEdgeFile,"%s\\E%s",chTmpFileName,strTmpNameOnly);//E 表示edge
				//原始文件路径
				sprintf(fileName,strTmpFileName);

				g_strFileName = strTmpFileName;
*/
				nTmpIndex = 0;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//单个分析
//特征分析1,g_iFlagSpecial = 1
				if (g_iFlagSpecial == 1)
				{

					sprintf(chTmpMsg,strMessageBegin);
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;
					//Create Save File name and path 2008.12.7
					iLocaBegin = strTmpPathOnly.Find('\\',4);
					iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
					strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
					if (strLocation == "")
					{
						strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
					}				
					sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
					dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
					if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
						CreateDirectory(chTmpFileName,NULL);
					if (((StrRecName*)lpParameter)->bCount == TRUE)
					{
						//step one 读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						//step one 保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Binary.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					}
					else
					{
						//step one 读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
						//step one 保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-all-8Binary.avi",chTmpFileName,strTmpNameOnly);
					}
					//if(strnicmp(strrchr(fileName,'.'),".avi",4))
					//	AfxMessageBox("找不到待处理的文件!");
					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					g_strFileName = fileName;

/*
					sprintf(chSaveFileName,"%s.avi",chTmpBinaryFile);
					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					
*/
					if (gDlg->m_ChooseForStepOne == TRUE )
					{
						//若选择RunningAvg算法，则进行初始化
						okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
						okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
						cvPFrameMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
						cvPFrMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
						cvPBkMat = cvCreateMat(lHeight, lStride, CV_32FC1);
					}

					for(;;)
					{
						if (iTotalLeft <= 0 || bActive == 0)
						{	
							okStopCapture(hBoard);
							InvalidateRect(NULL,NULL,TRUE);
							iNum = 0;
							break;
						}
						if (iTotalLeft >= iReadBuffer) 
						{
							iTotalLeft = iTotalLeft-iReadBuffer;
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	
							
							//////////////////////////////////////////////////////////////////////////
							// 一
							for(i=0;i<iReadBuffer;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								//特殊处理 根据情况定制设计 二
								//特殊分析1(清理二值图像)
								//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
								//2008.12.6 step one直接处理单通道8bit灰度图像
								//2009.3.31
								if (gDlg->m_ChooseForStepOne == TRUE )
								{
									//RunningAvg
									myElegansFeatures.SpecialExtractionRunningAvg(structEData.lpbuf,lHeight,lStrideRed,iNum);
								}
								else if (gDlg->m_ChooseForStepOne == FALSE)
								{
									//原有OTSU算法
									myElegansFeatures.SpecialExtraction(structEData.lpbuf,lHeight,lStrideRed,iNum);
								}
								
								
								if (!IsIconic(hWnd))
								{
									if (lHeight > 800 && lStride > 600) 
									{
										//特殊处理 若图像大于800*600，则缩小1/4显示
										//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
										myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStrideRed);
										//get image to app buffer from tgt
										g_blk.lpBits = structEData.lpHalf;			
										g_blk.iWidth = (short)(lStride*0.5);
										g_blk.iHeight = (short)(lHeight*0.5); //to invert y
										g_blk.iBitCount = 8;
										g_iSizeImage = lStride * lHeight;
										g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
										g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
										okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
										//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
									}
									else
									{
										//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
										okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
									}
								}
								iNum+=1;
								
								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}
							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iReadBuffer);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							//memset(lpLinear, 255, dwSize);


							ZeroMemory(lpLinear, dwSize);
							//InvalidateRect(NULL, NULL, FALSE);
							okStopCapture(hBoard);
							
							iReadTimes += 1;
						}
						if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						{
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);
							
							//////////////////////////////////////////////////////////////////////////
							// 二
							for(i=0;i<iTotalLeft;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								//特殊处理 根据情况定制设计 二
								//特殊分析1(清理二值图像)
								//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
								//2008.12.6 step one直接处理单通道8bit灰度图像
								//2009.3.31
								if (gDlg->m_ChooseForStepOne == TRUE )
								{
									//RunningAvg
									myElegansFeatures.SpecialExtractionRunningAvg(structEData.lpbuf,lHeight,lStrideRed,iNum);
								}
								else if (gDlg->m_ChooseForStepOne == FALSE)
								{
									//原有OTSU算法
									myElegansFeatures.SpecialExtraction(structEData.lpbuf,lHeight,lStrideRed,iNum);
								}
								
								if (!IsIconic(hWnd))
								{
									if (lHeight > 800 && lStride > 600) 
									{
										//特殊处理 若图像大于800*600，则缩小1/4显示
										//myElegansFeatures.GetRed(structEData.lpbuf,structEData.lpRedBuf,lHeight,lStrideRed);
										myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStrideRed);
										//get image to app buffer from tgt
										g_blk.lpBits = structEData.lpHalf;			
										g_blk.iWidth = (short)(lStride*0.5);
										g_blk.iHeight = (short)(lHeight*0.5); //to invert y
										g_blk.iBitCount = 8;
										g_iSizeImage = lStride * lHeight;
										g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
										g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
										okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
										//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
									}
									else
									{
										//myElegansFeatures.BackToRGB(structEData.lpRedBuf,lHeight,lStrideRed);
										okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
									}
								}
								iNum+=1;
								
								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}							

							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer,BUFFER,0,iTotalLeft);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							//memset(lpLinear, 255, dwSize);
							ZeroMemory(lpLinear,dwSize);
							okStopCapture(hBoard);

							iReadTimes += 1;
							iTotalLeft = 0;
						}
					}//特征分析1结束
					// 发送自定义消息，得到分析耗用时间；
					::PostMessage(hWnd,WM_GET_TIME,0,0);
					bActive = 0;
					iNum = 0;  
					
					if (structEData.path != NULL)
						myElegansFeatures.DestroyStructData();//销毁structEData的相关变量

					if (cvPFrameMat != NULL)
					{
						//释放用于动态背景滤除的矩阵
						cvReleaseMat(&cvPFrameMat);
						cvReleaseMat(&cvPFrMat);
						cvReleaseMat(&cvPBkMat);	
					}

					//chTmpMsg = "\0";
					sprintf(chTmpMsg,"End");
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

					okStopCapture(hBoard);
					InvalidateRect(NULL,NULL,TRUE);
					bWhile = FALSE;
					return 0;
				}//if (g_iFlagSpecial == 1)
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


	sprintf(chTmpMsg,strMessageBegin);
	::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
//①读入skeleton，计算长度，进行丢帧率检测和失效帧标记
				if(g_iFlagSpecial == 2)
				{
					//sprintf(fileName,"%s8%s-all.avi_B.avi",strTmpPathOnly,strTmpNameOnly);
					//sprintf(fileName,"%s_B.avi",strTmpFileName);


					//Create Save File name and path 2008.12.7
					iLocaBegin = strTmpPathOnly.Find('\\',4);
					iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
					strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
					if (strLocation == "")
					{
						strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
					}				
					//
					sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
					dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
					if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
						CreateDirectory(chTmpFileName,NULL);
					if (((StrRecName*)lpParameter)->bCount == TRUE)
					{
						//step one 读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-[%d-%d]-8Binary.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						//step one 保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					}
					else
					{
						//step one 读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-all-8Binary.avi",chTmpFileName,strTmpNameOnly);
						//step one 保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
					}
					//if(strnicmp(strrchr(fileName,'.'),".avi",4))
					//	AfxMessageBox("找不到待处理的文件!");
					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					g_strFileName = fileName;
					
					//////////////////////////////////////////////////////////////////////////
					//保存数据属性 和 实验属性
					sprintf(structEData.ed_chDataName,strTmpNameOnly);//文件名
                    sprintf(structEData.ed_chStrainName,"unc7-674");//种系名
					sprintf(structEData.ed_chPersonName,"GEQIAN");//实验员的名字
					
					structEData.ed_daDataDetail[0] = 244.; //Analysis version
					structEData.ed_daDataDetail[1] = 20081218.; //Capture Time
					structEData.ed_daDataDetail[3] = 802.; //CCD type
					structEData.ed_daDataDetail[4] = 8.;

					structEData.ed_faExperimentDetail[0] = (float)20.1;//tempreture
					structEData.ed_faExperimentDetail[1] = (float)55.1;//wet
					structEData.ed_faExperimentDetail[2] = 0;//with food 100,no food 0;
					structEData.ed_faExperimentDetail[3] = 4;//Magnification
					structEData.ed_faExperimentDetail[4] = (float)0.5;//tube lens
					structEData.ed_faExperimentDetail[5] = (float)6.0;//Unit cell um
					//////////////////////////////////////////////////////////////////////////
					

/*
					if ( 0 == testfile.Open(fileName,CFile::modeRead,NULL)) 
					{
						g_strErrMes.Format("Can not find the source avi file. The process is aborted.");
						AfxMessageBox(g_strErrMes);
						myElegansFeatures.DestroyStructData();//销毁structEData的相关变量
						return 0;
					}
					testfile.Close();
					
*/
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;
					int iNumPre = 0;
					//处理
					for(;;)
					{
						if (iTotalLeft <= 0 || bActive == 0)
						{	
							okStopCapture(hBoard);
							InvalidateRect(NULL,NULL,TRUE);
							iNum = 0;
							break;
						}
						if (iTotalLeft >= iReadBuffer) 
						{
							iTotalLeft = iTotalLeft-iReadBuffer;
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
							
							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	
							
							//////////////////////////////////////////////////////////////////////////
							// 一
							for(i=0;i<iReadBuffer;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								
								//特殊处理 根据情况定制设计 一
								//得到skeleton骨架,保存到lppath指向的内存中
								//2008.12.9 先判断当前帧是否有效，有效才处理，无效则pass
								if(structEData.IsUseful[iNum] == 1)
									myElegansFeatures.SpecialExtraction_2(structEData.lpbuf,lHeight,lStride,iNum);
								
								//2008.12.9 先判断当前帧是否有效，有效才处理，无效则pass
								//读入并存储edge图像								
								if(structEData.IsUseful[iNum] == 1)
								{
									myElegansFeatures.SpecialExtraction_1(structEData.lpbuf,lHeight,lStride,iNum,iNumPre);
									iNumPre = iNum;
								}
								
								
								if (!IsIconic(hWnd))
								{
									if (lHeight > 800 && lStride > 600) 
									{
										//特殊处理 若图像大于800*600，则缩小1/4显示
										myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
										//get image to app buffer from tgt
										g_blk.lpBits = structEData.lpHalf;			
										g_blk.iWidth = (short)(lStride*0.5);
										g_blk.iHeight = (short)(lHeight*0.5); //to invert y
										g_blk.iBitCount = 8;
										g_iSizeImage = lStride * lHeight;
										g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
										g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
										okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
									}
									else
										okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
								}
								iNum+=1;
								
								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}
							//sprintf(chSaveFileName,"%s_%d.AVI",chTmpEdgeFile,iReadTimes);
							//if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
							//	DeleteFile(chSaveFileName);
							//okSaveImageFile(hBoard,chSaveFileName,0,BUFFER,0,iReadBuffer);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);
							iReadTimes += 1;
						}
						if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						{
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);
							
							//////////////////////////////////////////////////////////////////////////
							// 二
							for(i=0;i<iTotalLeft;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;
								
								//特殊处理 根据情况定制设计 二
								//得到skeleton骨架,保存到lppath指向的内存中
								//2008.12.9 先判断当前帧是否有效，有效才处理，无效则pass
								if(structEData.IsUseful[iNum] == 1)
									myElegansFeatures.SpecialExtraction_2(structEData.lpbuf,lHeight,lStride,iNum);
								
								//2008.12.9 先判断当前帧是否有效，有效才处理，无效则pass
								//读入并存储edge图像
								if(structEData.IsUseful[iNum] == 1)
								{
									myElegansFeatures.SpecialExtraction_1(structEData.lpbuf,lHeight,lStride,iNum,iNumPre);
									iNumPre = iNum;
								}
								
								
								if (!IsIconic(hWnd))
								{
									if (lHeight > 800 && lStride > 600) 
									{
										//特殊处理 若图像大于800*600，则缩小1/4显示
										myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
										//get image to app buffer from tgt
										g_blk.lpBits = structEData.lpHalf;			
										g_blk.iWidth = (short)(lStride*0.5);
										g_blk.iHeight = (short)(lHeight*0.5); //to invert y
										g_blk.iBitCount = 8;
										g_iSizeImage = lStride * lHeight;
										g_blk.lBlockStep = LOWORD(g_iSizeImage); //must be set
										g_blk.iHiStep = HIWORD(g_iSizeImage); //must be set
										okConvertRect(hBoard,SCREEN,0,(TARGET)&g_blk,0,1);
									}
									else
										okConvertRect(hBoard,SCREEN,0,BUFFER,i,1);
								}
								iNum+=1;
								
								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							} // end of for
							//sprintf(chSaveFileName,"%s_%d.AVI",chTmpEdgeFile,iReadTimes);
							//if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
							//	DeleteFile(chSaveFileName);
							//okSaveImageFile(hBoard,chSaveFileName,0,BUFFER,0,iTotalLeft);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);
							iReadTimes += 1;
							iTotalLeft = 0;
						}
					}//处理结束
				}//if(g_iFlagSpecial == 2)
				//扫描一遍后，开始失效帧判定算法
				//当g_iFlagSpecial等于1时，则直接进入失效帧判断
				iTotalLeft=iTotalFrames;
				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				iNum = 0;
				
				sprintf(chTmpMsg,_T("Invalid frames algorithm is acting...\r\n"));
				////g_strErrMes.Format("Invalid frames algorithm is acting...\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				//当binary和skeleton之后，进行IsUseful判断
				//通过面积三次均值TPM比较来判断图像的有效性
				memcpy(spp_iStatMemory,structEData.iWormAera,iTotalFrames*sizeof(int));
				myElegansFeatures.StatBubbleSort(spp_iStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_iStatMemory,iTotalFrames);
				
				int iCompare = 0;
				double dJudge = 0;
				int iNanCnt = 0;//无效帧计数
				char chErr[256]="/0";
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//TPM与每一帧进行比较，超出波动幅度则视为无效帧
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.iWormAera[iNum]));
					
					//波动幅度设置为20%；
					//2009.4.30改为30% 考虑到Area改变较大
					dJudge = 0.3 * myElegansFeatures.STDATA[3];
					
					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUseful[iNum] = 0;
						}
					}                    
				}//
				
				//加强判断
				//通过长度三次均值比较来判断图像的有效性
				memcpy(spp_fStatMemory,structEData.Slength,iTotalFrames*sizeof(float));
				myElegansFeatures.StatBubbleSort(spp_fStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_fStatMemory,iTotalFrames);
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//avg与每一帧进行比较，超出波动幅度则视为无效帧
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.Slength[iNum]));
					
					//波动幅度设置为20%；
					//2009.4.30改为30%
					dJudge = 0.3 * myElegansFeatures.STDATA[3];
					
					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUseful[iNum] = 0;
							iNanCnt += 1;
						}
					}
					else
					{
						iNanCnt += 1;//若IsUseful已经为不可用即==0，则仍需将iNanCnt计数器加1
					}                    
				}//
				
				structEData.InvFraRat = (float)iNanCnt / (float)iTotalFrames;
				//
				sprintf(chTmpMsg,_T("总共%d帧，有效帧%d,丢弃%d帧!\r\n"),iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				////g_strErrMes.Format("总共%d帧，有效帧%d,丢弃%d帧!\r\n",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				if ( structEData.InvFraRat >= 0.3 && iNanCnt != 0)
				{
					sprintf(chErr,"总共%d帧，有效帧%d,丢弃%d帧，丢帧超30%请放弃此数据!",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
					AfxMessageBox(chErr,NULL,MB_OK);
					// 发送自定义消息，得到分析耗用时间；
					::PostMessage(hWnd,WM_GET_TIME,0,0);
					bActive = 0;
					iNum = 0;  
					okStopCapture(hBoard);
					InvalidateRect(NULL,NULL,TRUE);
					delete [] spp_iStatMemory;
					delete [] spp_fStatMemory;
					spp_iStatMemory = NULL;
					spp_fStatMemory = NULL;
					myElegansFeatures.DestroyStructData();
					return -1; //丢帧率超过30%，则不做参数提取，直接返回
				}//IsUseful判断结束	
				
				//保存帧属性 2008.12.16
				structEData.ed_faFrameDetail[0] = (float)iTotalFrames;//总帧数
				structEData.ed_faFrameDetail[1] = (float)iTotalFrames-iNanCnt;//有效帧
				structEData.ed_faFrameDetail[2] = (float)structEData.InvFraRat;//有效帧率
				structEData.ed_faFrameDetail[3] = (float)structEData.structfRate;//avi帧率
				structEData.ed_faFrameDetail[4] = (float)lStride;//图像宽
				structEData.ed_faFrameDetail[5] = (float)lHeight;//图像高

				//步骤1成功，则置标志位为3,进入下一步
				g_iFlagSpecial = 3;
				g_iFlagSpecial = 4;
				

//③头尾识别
				//////////////////////////////////////////////////////////////////////////
				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
				}				
				sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
				if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
					CreateDirectory(chTmpFileName,NULL);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					//step one 读取来自Uncompress的数据
					sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					//step one 保存的处理结果
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
				{
					//step one 读取来自Uncompress的数据
					sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
					//step one 保存的处理结果
					sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
				}
				//if(strnicmp(strrchr(fileName,'.'),".avi",4))
				//	AfxMessageBox("找不到待处理的文件!");
				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);
				g_strFileName = fileName;

				if (g_iFlagSpecial == 4)
				{
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;
					//int nRetCode=0;

					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);	
					structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride);
					lStrideRed = lStride;
					//头尾识别自动处理
					myElegansFeatures.HeadAndTailExtraction(fileName,lHeight,lStride);


				}//if (g_iFlagSpecial == 4)
				//头尾识别结束
				//////////////////////////////////////////////////////////////////////////

				//步骤3成功，则置标志位为5,进入下一步
				g_iFlagSpecial = 5;

				sprintf(chTmpMsg,_T("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n"));
				////g_strErrMes.Format("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
//④Feature Extraction
//读入skeleton进行处理，利用头尾标记后的数据进行参数提取
				//当步骤标志位为5时，才进行参数的计算
				if (g_iFlagSpecial == 5)
				{

					//////////////////////////////////////////////////////////////////////////
					//
					iNum = 0;
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0) 
						{
							myElegansFeatures.GetSampleSkeleton(iNum);
						}
					}
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// Locomotion 参数
					iNum = 0;
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						
						if (structEData.IsUseful[iNum] != 0) 
						{
							myElegansFeatures.GetParaExtraction(iNum);
						}
						else
						{
							structEData.m_iTimeCnt01s += 1;
							structEData.m_iTimeCnt02s += 1;
							structEData.m_iTimeCnt05s += 1;
							structEData.m_iTimeCnt10s += 1;
							structEData.m_iTimeCnt30s += 1;
							structEData.m_iTimeCnt60s += 1;
						}

					}
					myElegansFeatures.StatParaOfMove();
					// end of 'Locomotion 参数'
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// 形态学参数
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							structEData.AREA[iNum] = (structEData.iWormAera[iNum] *g_dCCDScale*g_dCCDScale) / 1000000.0;//mm^2 
							structEData.BODYSIZE[iNum] = (structEData.dianECnt[iNum] * g_dCCDScale) / 1000.0;  //mm
							//structEData.BODYWIDTH[iNum] = 0;  
							structEData.BODYLENGTH[iNum] = (structEData.Slength[iNum] *g_dCCDScale) / 1000.0;//mm
						}
					}
					
					int iVaCount = 0;
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							//筛掉无效帧的正常值
							structEData.AREA_VALID[iVaCount] = structEData.iWormAera[iNum];
							structEData.BODYLENGTH_VALID[iVaCount] = structEData.Slength[iNum];
							structEData.BODYSIZE_VALID[iVaCount] = structEData.dianECnt[iNum];
							iVaCount++;
						}
					}
					//计算三均值					
					myElegansFeatures.StatBubbleSort(structEData.AREA_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.AREA_VALID,iVaCount);
					structEData.AREA_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.000001;//换算为mm^2
					
					myElegansFeatures.StatBubbleSort(structEData.BODYLENGTH_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYLENGTH_VALID,iVaCount);
					structEData.BODYLENGTH_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm
					
					myElegansFeatures.StatBubbleSort(structEData.BODYSIZE_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYSIZE_VALID,iVaCount);
					structEData.BODYSIZE_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm
					// end of '形态学 参数'
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// Wave参数
					//add by 2008.12.16
					//modified by 2009.4.24
					//modified by 2009.5.2 先计算Wave参数，以便得到正确的box参数，提供给Locomotion::GlbMv::Forward and Backward
					//根据前后幅度变化值不会突变，修正最佳匹配矩形框的方向
					for(iNum=1;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] == 0)
						{
							structEData.ed_dpBodywaveStride[iNum]  = -1;
							structEData.ed_dpBodywaveHeight[iNum] = -1;
						}
						else 
						{
							double d1 = 0., d2 = 0., dtmp = 0.;
							int iNumPre = iNum;
							for (;;)
							{
								// find prior waveStride which is useful;
								iNumPre = iNumPre - 1;
								if (structEData.ed_dpBodywaveStride[iNumPre] != -1 ) break;								
							}

							// 相邻两帧的宽度不会出现太大变化
							d1 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveStride[iNumPre]);
							d2 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveHeight[iNumPre]);
							if (d1 > d2)
							{
								// exchange the wave stride and height;
								dtmp = structEData.ed_dpBodywaveStride[iNum];  
								structEData.ed_dpBodywaveStride[iNum] = structEData.ed_dpBodywaveHeight[iNum];  
								structEData.ed_dpBodywaveHeight[iNum] = dtmp;
								if (structEData.ed_dpBodywaveHeight != 0)
								{
									structEData.ed_dpBodywaveSToH[iNum] = 
										structEData.ed_dpBodywaveStride[iNum] / structEData.ed_dpBodywaveHeight[iNum];
								}
							}

							// Normalize the wave by the worm's length
							// 单位 微米/ (1000 * 毫米)
							structEData.ed_dpBodywaveHeightNormal[iNum] = 
								structEData.ed_dpBodywaveHeight[iNum] / (1000 * structEData.BODYLENGTH_3M);
							structEData.ed_dpBodywaveStrideNormal[iNum] = 
								structEData.ed_dpBodywaveStride[iNum] / (1000 *structEData.BODYLENGTH_3M);
						}
					}

					//2009.4.24
					// 得到有效的参数，可直接用于画图
					int iUseNumTmp = 0; //
					double *dWaveStride = new double[structEData.nImgOfProc*sizeof(double)];
					double *dWaveHeight = new double[structEData.nImgOfProc*sizeof(double)];
					memset(dWaveStride,0,structEData.nImgOfProc*sizeof(double));
					memset(dWaveHeight,0,structEData.nImgOfProc*sizeof(double));
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							dWaveStride[iUseNumTmp] = structEData.ed_dpBodywaveStrideNormal[iNum];
							dWaveHeight[iUseNumTmp] = structEData.ed_dpBodywaveHeightNormal[iNum];
							structEData.ed_xTime[iUseNumTmp] = structEData.fTime * iNum;
							iUseNumTmp += 1;
						}
					}
					memcpy(structEData.ed_dpBodywaveStrideNormal, dWaveStride, structEData.nImgOfProc*sizeof(double));
					memcpy(structEData.ed_dpBodywaveHeightNormal, dWaveHeight, structEData.nImgOfProc*sizeof(double));

					// 统计上下四分位数和三均值
					myElegansFeatures.StatBubbleSort(dWaveHeight,iUseNumTmp);
					myElegansFeatures.StatTPM(dWaveHeight,iUseNumTmp);
					structEData.ed_dpBodywaveHeightNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveHeightNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveHeightNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					myElegansFeatures.StatBubbleSort(dWaveStride,iUseNumTmp);					
					myElegansFeatures.StatTPM(dWaveStride,iUseNumTmp);
					structEData.ed_dpBodywaveStrideNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveStrideNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveStrideNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					delete [] dWaveHeight;
					delete [] dWaveStride;
					dWaveHeight = NULL;
					dWaveStride = NULL;
					// end of 'wave 参数'
					//////////////////////////////////////////////////////////////////////////

				}
				//参数提取结束			
				
				//////////////////////////////////////////////////////////////////////////
				//算法验证
				//Create Save File name and path 2009.4.24
				g_iFlagSpecial = 6;
				if (g_iFlagSpecial == 6)
				{
					iLocaBegin = strTmpPathOnly.Find('\\',4);
					iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
					strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
					if (strLocation == "")
					{
						strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
					}				
					sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
					dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
					if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
						CreateDirectory(chTmpFileName,NULL);
					if (((StrRecName*)lpParameter)->bCount == TRUE)
					{
						//step one 读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						//step one 保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					}
					else
					{
						//读取来自Uncompress的数据
						sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
						//保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
					}
					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					g_strFileName = fileName;

					bActive = 1;
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;

					//Save the results in the form of AVI movie
					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
					okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride);
					g_cvSavImg = cvCreateImage(cvSize(lStride,lHeight),8,3);
					g_cvColorImg = cvCreateImage(cvSize(lStride,lHeight),8,3);

					cvSet(g_cvColorImg,cvScalarAll(0),0);
					//cvZero(g_cvSavImg);
					cvSet(g_cvSavImg,cvScalarAll(0),0);
					//CV_FOURCC('X','V','I','D') ?? 压缩存储的结果会丢帧，最后2-3帧莫名消失？？
					g_cvSavVideo = cvCreateAVIWriter(chSaveFileName,CV_FOURCC('X','V','I','D'), (double)fRate , cvSize(lStride,lHeight) ,1);
					for(;;)
					{
						if (iTotalLeft <= 0 || bActive == 0)
						{	
							okStopCapture(hBoard);
							InvalidateRect(NULL,NULL,TRUE);
							iNum = 0;
							break;
						}
						if (iTotalLeft >= iReadBuffer) 
						{
							iTotalLeft = iTotalLeft-iReadBuffer;
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	

							//////////////////////////////////////////////////////////////////////////
							// 一
							for(i=0;i<iReadBuffer;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;

								//特殊处理 根据情况定制设计 一
								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(g_cvSavVideo,g_cvSavImg);
								iNum+=1;

								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}
							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
								,BUFFER,0,iReadBuffer);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
						}
						if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						{
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);

							//////////////////////////////////////////////////////////////////////////
							// 二
							for(i=0;i<iTotalLeft;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride);
								lStrideRed = lStride;

								//特殊处理 根据情况定制设计 二
								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(g_cvSavVideo,g_cvSavImg);
								iNum+=1;

								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}							

							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
								,BUFFER,0,iTotalLeft);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
							iTotalLeft = 0;
						}
					}//结束
				
					//Sleep(500);
					cvReleaseVideoWriter(&g_cvSavVideo);
					if (g_cvSavImg != NULL && g_cvColorImg != NULL)
					{
						//release saving image
						cvReleaseImage(&g_cvSavImg);
						cvReleaseImage(&g_cvColorImg);
						g_cvSavImg = NULL;
						g_cvColorImg = NULL;
					}
				}
				// 算法验证结束
				//////////////////////////////////////////////////////////////////////////

			}//特殊分析结束
			
			// 发送自定义消息，得到分析耗用时间；
			::PostMessage(hWnd,WM_GET_TIME,0,0);
			bActive = 0;
			iNum = 0;  
			sprintf(chTmpMsg,strMessageSaveResults);
			::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
			okStopCapture(hBoard);
			InvalidateRect(NULL,NULL,TRUE);
		}
		bWhile = FALSE;
	}
	
	if (spp_iStatMemory != NULL)
	{
		delete [] spp_iStatMemory;
		spp_iStatMemory = NULL;
	}
	if (spp_fStatMemory != NULL)
	{
		delete [] spp_fStatMemory;
		spp_fStatMemory = NULL;
	}

	delete [] chTmpMsg;
	chTmpMsg = NULL;
	return 0;
}

void CAnalysisTestDlg::OnButSpecial2() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "" || myFileListData.str_1 == "已处理")
	{
		MessageBox("没有选择要分析的记录！or 选择的记录已处理!",NULL,MB_OK);
		return;
	}
	else
	{		
		CString strSetCCDScale = "";
		GetDlgItemText(IDC_EDIT_CCD_SCALE,strSetCCDScale);
		g_dCCDScale = atof(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_UP_LEVEL,strSetCCDScale);
		g_iAreaUpLevel = atoi(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_DOWN_LEVEL,strSetCCDScale);
		g_iAreaDownLevel = atoi(strSetCCDScale);
		//add 2009.9.3
		GetDlgItemText(IDC_EDIT_BUFFER,strSetCCDScale);
		g_iReadBuffer = atoi(strSetCCDScale);

		if (g_dCCDScale == 0)
		{
			MessageBox("请设置CCD的参数后，重新点击step two!",NULL,MB_OK);
			return;
		}

		StrRecName* RecPARAM = new StrRecName;
		RecPARAM = &myFileListData;
		RecPARAM->iFlag = 0; //备用标志在分析处理时，0代表单个文件分析，100代表批量分析
		if (RecPARAM->bCount == FALSE)
		{
			RecPARAM->iCountA = 0;
			RecPARAM->iCountB = 0;
		}		

		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,TRUE);
		
		GetLocalTime(&sysTimeBegin);
		lSysTime = GetTickCount();
		
		g_iFlagSpecial = 2;//表示特殊分析的第二步
		g_iRunningFlag = 100;//100表示有处理进程在运行，0表示没有
		//开启分析线程
		hThread3 = CreateThread(NULL,0,SpecialProcessProc,(LPVOID)RecPARAM,0,&threadID_3);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//界面美化 模块 开始
HBRUSH CAnalysisTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	HBRUSH B;
	switch(nCtlColor) 
	{
	case CTLCOLOR_STATIC:
		pDC->SetTextColor(RGB(0,100,255));//字体色
		pDC->SetBkColor(RGB(238,238,238));//字体背景色******
		B = CreateSolidBrush(RGB(238,238,238)); //背景色
		hbr = B;
		break;
	case CTLCOLOR_LISTBOX:
		pDC->SetTextColor(RGB(0,100,255));//字体色
		pDC->SetBkColor(RGB(238,238,238));//字体背景色******
		B = CreateSolidBrush(RGB(238,238,238)); //背景色
		hbr = B;
		break;
	case CTLCOLOR_BTN:
		pDC->SetTextColor(RGB(0,0,255));//字体色
		pDC->SetBkColor(RGB(211,225,239));//字体背景色******
		B = CreateSolidBrush(RGB(211,225,239)); //背景色
		hbr = B;
		break;
	case  CTLCOLOR_EDIT:
		//pDC->SetTextColor(RGB(0,100,255));//字体色
		//pDC->SetBkColor(RGB(238,238,238));//字体背景色******
		//B = CreateSolidBrush(RGB(238,238,238)); //背景色
		//hbr = B;
		// EDIT Control用CTLCOLOR_EDIT无效
		break;
	default:
		break;
	}
	
	//Edit控件只能用此种方式修改颜色，maybe是VC6.0的bug
	if (pWnd->GetDlgCtrlID()== IDC_EDIT_MESSAGE) 
	{
		pDC->SetTextColor(RGB(255,100,0));//字体色
		pDC->SetBkColor(RGB(230,235,245));//字体背景色******
		B = CreateSolidBrush(RGB(230,235,245)); //背景色
		hbr = B;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

typedef int ( CALLBACK * FUNC ) ( PCHAR );
void CAnalysisTestDlg::InitSkin ()
{
	CHAR szName [ MAX_PATH ];
	CString strName = GetAppPath () + "skins\\Longhorn Style-BLUE.skn";
	FUNC pFunc = ( FUNC ) GetProcAddress ( theApp.m_hModule, "LoadSkin" );
	strcpy ( szName, strName );
	pFunc ( szName );
}

CString CAnalysisTestDlg::GetAppPath ()
{
	CString strPath;
	
	CHAR szPath [ MAX_PATH + 1 ];
	if ( GetModuleFileName ( NULL, szPath, MAX_PATH ) )
	{
		strPath = szPath;
		
		int nPos = strPath.ReverseFind ( '\\' );
		
		if ( nPos >= 0 ) strPath = strPath.Left ( nPos + 1 );
	}
	
	return strPath;
}


///////////////////////////////////////////////////////////
//Func: 根据分辨率和系统字体调整控件位置与大小
//Parameter: CWnd *p (需要调整的控件的句柄)
//Return Value: None
//Date: 2004-3-30
///////////////////////////////////////////////////////////
void CAnalysisTestDlg::FitScreenSize(CWnd *p)
{
	//根据显示器分辨率调整控件位置与大小
	int cx=GetSystemMetrics(SM_CXSCREEN);    //得到当前显示分辨率
	int cy=GetSystemMetrics(SM_CYSCREEN);
	
	CRect rect;
   	p->GetWindowRect(&rect);       //得到控件的屏幕坐标
	ScreenToClient(&rect);
	
    
    //调整控件大小	
	int x=rect.left*cx/1280;
	int y=rect.top*cy/1024;
	int width=rect.Width()*cx/1280;
	int height=rect.Height()*cy/1024;	
		  
	p->SetWindowPos(NULL,x,y,width,height,SWP_SHOWWINDOW); 
	
		
	//根据系统字体大小(dpi)调整控件位置与大小
	CDC *pDC=GetDC();
	int FontSize=pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	
	CRect rect1;
   	p->GetWindowRect(&rect1);       //得到控件的屏幕坐标
	ScreenToClient(&rect1);
	
	//调整控件大小	
	int x1=rect1.left*120/FontSize;
	int y1=rect1.top*120/FontSize;
	int width1=rect1.Width()*120/FontSize;
	int height1=rect1.Height()*120/FontSize;	
		  
	p->SetWindowPos(NULL,x1,y1,width1,height1,SWP_SHOWWINDOW);	
} 
//界面美化 模块 结束
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

//Add by haining 2009-3-31
void CAnalysisTestDlg::OnChooseAlgorithm()
{
	// TODO: Add your control notification handler code here
	if (m_ChooseForStepOne== TRUE)
	{
		m_ChooseForStepOne=FALSE;
	}
	else if(m_ChooseForStepOne == FALSE)
	{
		m_ChooseForStepOne=TRUE;
	}
}

void CAnalysisTestDlg::OnEnChangeEditUpLevel()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}













//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//新的处理流程
//原有的暂停回放Button
//2010.5
//此键改为新的detection and tracking算法流程，是iNemo tracking system的基础
void CAnalysisTestDlg::OnButReviewPause() 
{
	// TODO: Add your control notification handler code here
	if (myFileListData.strID == "" || myFileListData.str_1 == "已处理")
	{
		MessageBox("没有选择要分析的记录！or 选择的记录已处理!",NULL,MB_OK);
		return;
	}
	else
	{		
		CString strSetCCDScale = "";
		GetDlgItemText(IDC_EDIT_CCD_SCALE,strSetCCDScale);
		g_dCCDScale = atof(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_UP_LEVEL,strSetCCDScale);
		g_iAreaUpLevel = atoi(strSetCCDScale);
		GetDlgItemText(IDC_EDIT_DOWN_LEVEL,strSetCCDScale);
		g_iAreaDownLevel = atoi(strSetCCDScale);
		//add 2009.9.3
		GetDlgItemText(IDC_EDIT_BUFFER,strSetCCDScale);
		g_iReadBuffer = atoi(strSetCCDScale);

		//add 2010.8.4
		CString str0804;
		GetDlgItemText(IDC_EDIT_BINNING, str0804);
		g_fBinningFlag = atof(str0804);
		g_iMultiOtsuLevel = GetDlgItemInt(IDC_EDIT_MULTIOTSU_LEVEL);
		g_iMultiOtsuThNum = GetDlgItemInt(IDC_EDIT_MULTIOTSU_THNUM);


		if (g_dCCDScale == 0)
		{
			MessageBox("请设置CCD的参数后，重新点击step two!",NULL,MB_OK);
			return;
		}

		StrRecName* RecPARAM = new StrRecName;
		RecPARAM = &myFileListData;
		RecPARAM->iFlag = 0; //备用标志在分析处理时，0代表单个文件分析，100代表批量分析
		if (RecPARAM->bCount == FALSE)
		{
			RecPARAM->iCountA = 0;
			RecPARAM->iCountB = 0;
		}

		bActive = 1;
		lScrnOffset = exSetToWndRectEx(hBoard, hWnd, 0);
		InvalidateRect(NULL,TRUE);

		GetLocalTime(&sysTimeBegin);
		lSysTime = GetTickCount();

		g_iRunningFlag = 100;
		//开启分析线程
		hThread5 = CreateThread(NULL,0,NewProcessProc_iNemo,(LPVOID)RecPARAM,0,&threadID_5_new);
	}
}

// 2010.5 new
// 直接读入ok卡采集的原始数据,3通道数据
DWORD WINAPI NewProcessProc_iNemo(LPVOID lpParameter)
{
	LPBYTE		lpLinear;
	DWORD		dwSize;

	//记录路径名(单个分析传递记录名路径)
	CString strTmpFileName = ((StrRecName*)lpParameter)->str_7;

	CString strTmpID = ((StrRecName*)lpParameter)->strID;//记录ID号
	// 记录名，仅名称(单个分析传递记录名)
	CString strTmpNameOnly = ((StrRecName*)lpParameter)->str_2;
	strTmpNameOnly.Format("%s",strTmpNameOnly.Mid(0,strTmpNameOnly.GetLength()-4));
	CString strTmpPathOnly = ((StrRecName*)lpParameter)->str_7; 
	g_strFileName = strTmpPathOnly;
	strTmpPathOnly.Format("%s",strTmpPathOnly.Mid(0,((StrRecName*)lpParameter)->str_7.GetLength()-((StrRecName*)lpParameter)->str_2.GetLength()));



	CString strTmpTotalFrames = ((StrRecName*)lpParameter)->str_3;//记录的总帧数
	int     iTmpFlag = ((StrRecName*)lpParameter)->iFlag;//单个分析 or 批量分析
	int iNum = 0;
	int iBeginNum = 0;
	int iEndNum = 0;
	int iTotalFrames = atoi(strTmpTotalFrames);
	if (((StrRecName*)lpParameter)->bCount == TRUE)
	{
		iBeginNum = ((StrRecName*)lpParameter)->iCountA; //LoadImage开始load的帧数
		iEndNum   =	((StrRecName*)lpParameter)->iCountB; //LoadImage结束load的帧数	
		iTotalFrames = iEndNum -iBeginNum; //需要读取处理的总帧数
		iNum = iBeginNum;
	}

	CString strTmpRate = ((StrRecName*)lpParameter)->str_8;//记录的帧率
	float fRate = atof(strTmpRate);


	//SaveFileName 2008.12.7
	CString strLocation = "";
	int iLocaBegin = 0; 	
	int iLocaEnd = 0;
	DWORD dwAttr;
	char chTmpFileName[256] = "\0";

	char fileName[256] = "\0";	 
	char edgeFileName[256] = "\0";
	char chSaveFileName[256] = "\0";
	int i = 0;
	int iTotalLeft=iTotalFrames;

	int iReadTimes = 0;
	CString strMessageBegin = "Begin To Process\r\n";
	CString strMessageLoad = "okLoadImageFile...\r\n";
	CString strMessageSave = "Saving Image...\r\n";
	CString strMessageSaveResults = "Please press the 'Save Results' button to acquire .mdb file.\r\n";
	CString strMessageEnd = "Congratulations!";
	char chTmpBinaryFile[256] = "\0";//缓存二值化图像
	char chTmpThinningFile[256] = "\0";//缓存细化图像
	char chTmpSkeletonFile[256] = "\0";//缓存骨架图像
	char chTmpEdgeFile[256] = "\0";//边缘图像
	CString strTmp;

	// 停止采集卡
	okStopCapture(hBoard);

	//改变缓存大小设置，取代默认的640x480
	short heightTemp;
	long strideTemp;
	CRect   rect;        // 根据图像大小设置BUFFER大小
	int iReadBuffer = 0; //缓存帧数设置
	iReadBuffer = g_iReadBuffer;


	//从str_4中提取当前处理图像的宽和高，并进行设置
	int iAVIStride = 0,iAVIHeight = 0;
	CString strTmpSize = ((StrRecName*)lpParameter)->str_4;//提取图像大小
	CString strTmpStride,strTmpHeight;
	int iTmpGet = strTmpSize.Find('*');
	strTmpStride = strTmpSize.Left(iTmpGet);
	int iTmpLength = strTmpSize.GetLength();
	strTmpHeight = strTmpSize.Right(iTmpLength - iTmpGet - 1);
	iAVIStride = atoi(strTmpStride);
	iAVIHeight = atoi(strTmpHeight);
	assert(iAVIStride != 0);//防止为0
	assert(iAVIHeight != 0);

	SetRect(&rect,0,0,iAVIStride,iAVIHeight);
	okSetTargetRect(hBoard,BUFFER,&rect);
	okGetTargetInfo(hBoard,BUFFER,0,NULL,&heightTemp,&strideTemp);

	if (iAVIStride > 800 && iAVIHeight >600)
	{
		SetRect(&rect,0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5));
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,(int)(iAVIStride*0.5),(int)(iAVIHeight*0.5)); 
	}
	else
	{
		gDlg->m_Screen.GetWindowRect(&rect); 
		gDlg->m_Screen.MoveWindow(0,0,iAVIStride,iAVIHeight); 
	}

	char chStageFileName[255]="\0";
	int iIsErr;

	int *spp_iStatMemory = NULL;
	float *spp_fStatMemory = NULL;

	// Add by haining 2008.12.4批量处理需要的变量	
	SYSTEMTIME currenttime;
	int m_itmpId = 0;
	int iChuli = 0;
	CAnalysisTestDlg* dlg;
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();
	//int nRetCode=0;
	int nTmpIndex = 0;


	//Add 2009.7.13
	char* chTmpMsg = new char[255];
	memset(chTmpMsg,0,sizeof(char)*255);

	BOOL bWhile = TRUE;
	while (bWhile == TRUE)
	{
		if (bActive == 1)
		{
			if (iTmpFlag == 100)
			{
				//
			}
			else
			{

				structEData.nImgOfProc=iTotalFrames;//
				myElegansFeatures.InitStructData(iAVIHeight,iAVIStride);
				myElegansFeatures.DoPretreatment.InitData(iAVIHeight,iAVIStride);
				myElegansFeatures.InitDataOfMove();


				//
				dpArray.RemoveAll();
				AddData();

				//2008.12.7
				sprintf(chStageFileName,"%s,mpg4.txt",strTmpFileName);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,iBeginNum,iEndNum);
				}
				else
				{
					iIsErr = myElegansFeatures.ReadF_XYInfo(chStageFileName,0,iTotalFrames);
				}

				if (iIsErr == 1)
				{
					////g_strErrMes.Format("Can not find or open XY-stage coordinates!!!\r\n");
					memset(chTmpMsg,0,255*sizeof(char));
					sprintf(chTmpMsg,_T("Can not find or open XY-stage coordinates!!!\r\n\0"));
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}
				else if(iIsErr == -1)
				{
					return -1;
				}

				////g_strErrMes.Format("XY stage's coordinates is successfully reloaded!\r\n");
				sprintf(chTmpMsg,_T("XY stage's coordinates is successfully reloaded!\r\n\0"));
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);

				sprintf(chTmpMsg,_T("像素与实际空间的换算比例是1个像素对应 %5f!\r\n\0"), g_dCCDScale);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);



				
				structEData.fTime = (float)(1.0/fRate);
				structEData.structfRate = fRate;
				g_dMaxMove = MaxMove * structEData.fTime;

				if (iTotalFrames != 0 && fRate != 0)
				{
					//Assume the largest Bodybends is 30 times/min;
					if (fRate <= 8.5)
					{
						g_iBodyBendsFilter = (int)((fRate * 60.0)/60.0);
					}
					else if (fRate > 8.5) 
					{
						g_iBodyBendsFilter = 2 + (int)((fRate * 60.0)/60.0);
					}		
				}


				if (spp_iStatMemory == NULL && spp_fStatMemory == NULL)
				{
					spp_iStatMemory = new int[iTotalFrames];//
					memset(spp_iStatMemory,0,iTotalFrames*sizeof(int));							
					spp_fStatMemory = new float[iTotalFrames];//
					memset(spp_fStatMemory,0,iTotalFrames*sizeof(float));
				}
				else
				{
					sprintf(chTmpMsg,_T("spp_iStatMemory和spp_fStatMemory没有成功分配!\r\n"));
					::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				}

				GetLocalTime(&currenttime);
				nTmpIndex = 0;



				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////
				//2009.8.12
				//
				int iTemp814 = 0;
				for (iTemp814=1; iTemp814 < iTotalFrames; iTemp814++)
				{
					double iDeltaX = (double)(structEData.flatx[iTemp814] - structEData.flatx[iTemp814 - 1]);
					double iDeltaY = (double)(structEData.flaty[iTemp814] - structEData.flaty[iTemp814 -1]);
					if (iDeltaX != 0 || iDeltaY != 0)
					{
						structEData.IsUseful[iTemp814 - 1] = 0;
						structEData.IsUseful[iTemp814] = 0;
					}
				}

				int iTemp412 = 0;
				for (iTemp412 = 1; iTemp412 < iTotalFrames; iTemp412++)
				{
					if (structEData.IsUseful[iTemp412] == 1)
					{
						if (structEData.IsUseful[iTemp412+1] == 0 || structEData.IsUseful[iTemp412+2] == 0 || structEData.IsUseful[iTemp412+3] == 0)
						{
							structEData.IsUseful[iTemp412] = 0;
						}
					}
				}
			
				sprintf(chTmpMsg,strMessageBegin);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				iTotalLeft=iTotalFrames;
				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				iNum = 0;
				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
				}				


				sprintf(chSaveFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chSaveFileName);//
				if(dwAttr == 0xFFFFFFFF)   //
					CreateDirectory(chSaveFileName,NULL);

				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{

					sprintf(fileName,"%s%s.avi",strTmpPathOnly,strTmpNameOnly);
					//step one
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Binary.avi",chSaveFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
				{
					sprintf(fileName,"%s%s.avi",strTmpPathOnly,strTmpNameOnly);
					//step one 保存的处理结果
					sprintf(chSaveFileName,"%s\\%s-all-8Binary.avi",chSaveFileName,strTmpNameOnly);
				}

				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);
				g_strFileName = fileName;



				if (gDlg->m_ChooseForStepOne == TRUE )
				{
					//若选择RunningAvg算法，则进行初始化
					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
					okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStride = lStride_ch3 / 3;
					cvPFrameMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
					cvPFrMat = cvCreateMat(lHeight, lStride, CV_32FC1);	
					cvPBkMat = cvCreateMat(lHeight, lStride, CV_32FC1);
				}

				//here is a bug !!!

				//2010.3.10 添加中间结果回显的opencv窗口名字
				//CString strImgWindowName;
				CTime day;
				day=CTime::GetCurrentTime();
				int filehour,filemin,filesec;
				filehour = day.GetHour();//hh
				filemin=day.GetMinute();//mm分钟
				filesec=day.GetSecond();//ss
				g_strImgWindowName.Format("Image-%s(%02d:%02d:%02d)",strTmpNameOnly,filehour,filemin,filesec);

				//tmp 2009-4-8
				//Save the results in the form of AVI movie
				g_cvSavImg = cvCreateImage(cvSize(lStride,lHeight),8,1);
				g_cvColorImg = cvCreateImage(cvSize(lStride*g_fBinningFlag,lHeight*g_fBinningFlag),8,3);

				//2011.1.12
				g_pImgBigObeject = cvCreateImage(cvSize(lStride*g_fBinningFlag,lHeight*g_fBinningFlag),8,1);
				cvZero(g_pImgBigObeject);

				//cvZero(g_cvColorImg);??
				cvSet(g_cvColorImg,cvScalarAll(0),0);
				cvZero(g_cvSavImg);
				g_cvSavVideo = cvCreateAVIWriter(chSaveFileName, -1, (double)fRate , cvSize(lStride*g_fBinningFlag,lHeight*g_fBinningFlag) , 1);

				//
				g_pFrame = cvCreateImage(cvSize(lStride,lHeight),8,1);
				g_pFrImg = cvCreateImage(cvSize(lStride,lHeight),8,1);
				g_pBkImg = cvCreateImage(cvSize(lStride,lHeight),8,1);
				cvZero(g_pFrame);
				cvZero(g_pFrImg);
				cvZero(g_pBkImg);
				g_bg_model = NULL;

				for(;;)
				{
					if (iTotalLeft <= 0 || bActive == 0)
					{	
						okStopCapture(hBoard);
						InvalidateRect(NULL,NULL,TRUE);
						iNum = 0;
						break;
					}
					if (iTotalLeft >= iReadBuffer) 
					{
						iTotalLeft = iTotalLeft-iReadBuffer;
						// 发送自定义消息
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	

						//////////////////////////////////////////////////////////////////////////
						// 一
						for(i=0;i<iReadBuffer;i++)
						{
							// 获取缓存中的图像数据保存地址；
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
							lStrideRed = lStride_ch3 / 3;
							lStride = lStrideRed;

							//特殊处理 根据情况定制设计 
							myElegansFeatures.Detection_3channel(structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);

							cvWriteToAVI(g_cvSavVideo,g_cvColorImg);

							iNum+=1;

							// 发送自定义消息，使进度条更新；
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}
						// 发送自定义消息,正在存储
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
						//	,BUFFER,0,iReadBuffer);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						memset(lpLinear, 255, dwSize);

						iReadTimes += 1;
					}
					if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
					{
						// 发送自定义消息
						sprintf(chTmpMsg,strMessageLoad);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
						okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);

						//////////////////////////////////////////////////////////////////////////
						// 二
						for(i=0;i<iTotalLeft;i++)
						{
							// 获取缓存中的图像数据保存地址；
							structEData.lpbuf =NULL;
							structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
							lStrideRed = lStride_ch3 / 3;
							lStride = lStrideRed;

							//特殊处理 根据情况定制设计 二
							myElegansFeatures.Detection_3channel(structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);

							cvWriteToAVI(g_cvSavVideo,g_cvColorImg);
							iNum+=1;

							// 发送自定义消息，使进度条更新；
							::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
						}							

						// 发送自定义消息,正在存储
						sprintf(chTmpMsg,strMessageSave);
						::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

						//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
						//	,BUFFER,0,iTotalLeft);
						okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
						memset(lpLinear, 255, dwSize);

						iReadTimes += 1;
						iTotalLeft = 0;
					}
				}//end -- for(;;) 特征分析1结束

				cvReleaseVideoWriter(&g_cvSavVideo);

				// 发送自定义消息，得到分析耗用时间；
				::PostMessage(hWnd,WM_GET_TIME,0,0);
				bActive = 0;
				iNum = 0;  


				if (cvPFrameMat != NULL)
				{
					//释放用于动态背景滤除的矩阵
					cvReleaseMat(&cvPFrameMat);
					cvReleaseMat(&cvPFrMat);
					cvReleaseMat(&cvPBkMat);	
				}

				if (g_cvSavImg != NULL && g_cvColorImg != NULL)
				{
					//release saving image
					cvReleaseImage(&g_cvSavImg);
					cvReleaseImage(&g_cvColorImg);
					g_cvSavImg = NULL;
					g_cvColorImg = NULL;

					cvReleaseImage(&g_pImgBigObeject);
					g_pImgBigObeject = NULL;
				}
				
				if (g_pFrImg != NULL)
				{
					//释放高斯模型参数占用内存   
					cvReleaseBGStatModel((CvBGStatModel**)&g_bg_model);
					cvReleaseImage(&g_pFrImg); 
					cvReleaseImage(&g_pBkImg);   
					cvReleaseImage(&g_pFrame);  
					g_pFrame = NULL;
					g_pFrImg = NULL;
					g_pBkImg = NULL;
				}
 
				//cvReleaseCapture(&g_pCapture);   


				bActive = 1;
				//扫描一遍后，开始失效帧判定算法
				//当g_iFlagSpecial等于1时，则直接进入失效帧判断
				iTotalLeft=iTotalFrames;
				iReadBuffer = g_iReadBuffer;
				iReadTimes = 0;	
				iNum = 0;

				sprintf(chTmpMsg,_T("Invalid frames algorithm is acting...\r\n"));
				////g_strErrMes.Format("Invalid frames algorithm is acting...\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				//当binary和skeleton之后，进行IsUseful判断
				//通过面积三次均值TPM比较来判断图像的有效性
				memcpy(spp_iStatMemory,structEData.iWormAera,iTotalFrames*sizeof(int));
				myElegansFeatures.StatBubbleSort(spp_iStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_iStatMemory,iTotalFrames);

				int iCompare = 0;
				double dJudge = 0;
				int iNanCnt = 0;//无效帧计数
				char chErr[256]="/0";
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//TPM与每一帧进行比较，超出波动幅度则视为无效帧
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.iWormAera[iNum]));

					//波动幅度设置为20%；
					//2009.4.30改为30% 考虑到Area改变较大
					//2009.8.14改为40%, 计算平均大小时本应去掉stage move造成的影响，但简单解决则扩大波动幅度
					dJudge = 0.4 * myElegansFeatures.STDATA[3];

					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUsefulImage[iNum] = 0;
						}
					}   
					else if(structEData.IsUseful[iNum] == 0)
					{
						structEData.IsUsefulImage[iNum] =0;
					}
				}//

				//加强判断
				//通过长度三次均值比较来判断图像的有效性
				memcpy(spp_fStatMemory,structEData.Slength,iTotalFrames*sizeof(float));
				myElegansFeatures.StatBubbleSort(spp_fStatMemory,iTotalFrames);
				myElegansFeatures.StatTPM(spp_fStatMemory,iTotalFrames);
				for(iNum=0;iNum<iTotalFrames;iNum++)
				{
					//avg与每一帧进行比较，超出波动幅度则视为无效帧
					iCompare = abs((int)(myElegansFeatures.STDATA[3] - structEData.Slength[iNum]));

					//波动幅度设置为20%；
					//2009.4.30改为30%
					//2009.8.14改为40%, 计算平均大小时本应去掉stage move造成的影响，但简单解决则扩大波动幅度
					dJudge = 0.4 * myElegansFeatures.STDATA[3];

					if (structEData.IsUseful[iNum] == 1) 
					{
						if ((iCompare - dJudge) > 0)
						{
							structEData.IsUsefulImage[iNum] = 0;
							iNanCnt += 1;
						}
					}
					else if(structEData.IsUseful[iNum] == 0)
					{
						structEData.IsUsefulImage[iNum] = 0;
						iNanCnt += 1;//若IsUseful已经为不可用即==0，则仍需将iNanCnt计数器加1
					}                    
				}//

				structEData.InvFraRat = (float)iNanCnt / (float)iTotalFrames;
				//
				sprintf(chTmpMsg,_T("总共%d帧，有效帧%d,丢弃%d帧!\r\n"),iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				////g_strErrMes.Format("总共%d帧，有效帧%d,丢弃%d帧!\r\n",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				if ( structEData.InvFraRat >= 0.3 && iNanCnt != 0)
				{
					sprintf(chErr,"总共%d帧，有效帧%d,丢弃%d帧，丢帧超30%请放弃此数据!",iTotalFrames,iTotalFrames-iNanCnt,iNanCnt);
					AfxMessageBox(chErr,NULL,MB_OK);
					// 发送自定义消息，得到分析耗用时间；
					::PostMessage(hWnd,WM_GET_TIME,0,0);
					bActive = 0;
					iNum = 0;  
					okStopCapture(hBoard);
					InvalidateRect(NULL,NULL,TRUE);
					delete [] spp_iStatMemory;
					delete [] spp_fStatMemory;
					spp_iStatMemory = NULL;
					spp_fStatMemory = NULL;
					myElegansFeatures.DestroyStructData();
					return -1; //丢帧率超过30%，则不做参数提取，直接返回
				}//IsUseful判断结束	

				//保存帧属性 2008.12.16
				structEData.ed_faFrameDetail[0] = (float)iTotalFrames;//总帧数
				structEData.ed_faFrameDetail[1] = (float)iTotalFrames-iNanCnt;//有效帧
				structEData.ed_faFrameDetail[2] = (float)structEData.InvFraRat;//有效帧率
				structEData.ed_faFrameDetail[3] = (float)structEData.structfRate;//avi帧率
				structEData.ed_faFrameDetail[4] = (float)lStride  * (int)(1/g_fBinningFlag);//图像宽
				structEData.ed_faFrameDetail[5] = (float)lHeight * (int)(1/g_fBinningFlag);//图像高

				//步骤1成功，则置标志位为3,进入下一步
				g_iFlagSpecial = 3;
				//g_iFlagSpecial = 4;


				//③头尾识别
				//////////////////////////////////////////////////////////////////////////
				//Create Save File name and path 2008.12.7
				iLocaBegin = strTmpPathOnly.Find('\\',4);
				iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
				strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
				if (strLocation == "")
				{
					strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
				}				
				sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
				dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
				if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
					CreateDirectory(chTmpFileName,NULL);
				if (((StrRecName*)lpParameter)->bCount == TRUE)
				{
					//step one 读取来自Uncompress的数据
					//sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
					//保存的处理结果
					sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
				}
				else
				{
					//step one 读取来自Uncompress的数据
					//sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
					sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
					//保存的处理结果
					sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
				}
				//if(strnicmp(strrchr(fileName,'.'),".avi",4))
				//	AfxMessageBox("找不到待处理的文件!");
				if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
					DeleteFile(chSaveFileName);
				g_strFileName = fileName;

				if (g_iFlagSpecial == 4)
				{
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;
					//int nRetCode=0;

					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);	
					structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStrideRed = lStride_ch3 /3;
					lStride = lStrideRed;

					lStride = (long)(lStride * g_fBinningFlag);
					lHeight = (long)(lHeight * g_fBinningFlag);

					//头尾识别自动处理
					myElegansFeatures.HeadAndTailExtraction(fileName,lHeight,lStride);


				}//if (g_iFlagSpecial == 4)
				//头尾识别结束
				//////////////////////////////////////////////////////////////////////////

				//步骤3成功，则置标志位为5,进入下一步
				g_iFlagSpecial = 5;

				sprintf(chTmpMsg,_T("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n"));
				////g_strErrMes.Format("Worms behavior characters are in progress...\r\nPlease wait...It may take a few seconds.\r\n");
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);
				Sleep(100);
				//④Feature Extraction
				//读入skeleton进行处理，利用头尾标记后的数据进行参数提取
				//当步骤标志位为5时，才进行参数的计算
				if (g_iFlagSpecial == 5)
				{

					//////////////////////////////////////////////////////////////////////////
					//
					iNum = 0;
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0) 
						{
							myElegansFeatures.GetSampleSkeleton(iNum);
						}
					}
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// Locomotion 参数
					iNum = 0;
					for(iNum=1;iNum<iTotalFrames;iNum++)
					{
						//edit 2009.8.15
						myElegansFeatures.GetParaExtraction(iNum);
						if (structEData.IsUseful[iNum] != 0) 
						{

						}
						else
						{
							structEData.m_iTimeCnt01s += 1;
							structEData.m_iTimeCnt02s += 1;
							structEData.m_iTimeCnt05s += 1;
							structEData.m_iTimeCnt10s += 1;
							structEData.m_iTimeCnt30s += 1;
							structEData.m_iTimeCnt60s += 1;
						}

					}
					myElegansFeatures.StatParaOfMove();
					// end of 'Locomotion 参数'
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// 形态学参数
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							structEData.AREA[iNum] = (structEData.iWormAera[iNum] *g_dCCDScale*g_dCCDScale) / 1000000.0;//mm^2 
							structEData.BODYSIZE[iNum] = (structEData.dianECnt[iNum] * g_dCCDScale) / 1000.0;  //mm
							//structEData.BODYWIDTH[iNum] = 0;  
							structEData.BODYLENGTH[iNum] = (structEData.Slength[iNum] *g_dCCDScale) / 1000.0;//mm
						}
					}

					int iVaCount = 0;
					for(iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							//筛掉无效帧的正常值
							structEData.AREA_VALID[iVaCount] = structEData.iWormAera[iNum];
							structEData.BODYLENGTH_VALID[iVaCount] = structEData.Slength[iNum];
							structEData.BODYSIZE_VALID[iVaCount] = structEData.dianECnt[iNum];
							iVaCount++;
						}
					}
					//计算三均值					
					myElegansFeatures.StatBubbleSort(structEData.AREA_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.AREA_VALID,iVaCount);
					structEData.AREA_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.000001;//换算为mm^2

					myElegansFeatures.StatBubbleSort(structEData.BODYLENGTH_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYLENGTH_VALID,iVaCount);
					structEData.BODYLENGTH_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm

					myElegansFeatures.StatBubbleSort(structEData.BODYSIZE_VALID,iVaCount);
					myElegansFeatures.StatTPM(structEData.BODYSIZE_VALID,iVaCount);
					structEData.BODYSIZE_3M = g_dCCDScale * myElegansFeatures.STDATA[3] * 0.001;//mm
					// end of '形态学 参数'
					//////////////////////////////////////////////////////////////////////////

					//////////////////////////////////////////////////////////////////////////
					// Wave参数
					//add by 2008.12.16
					//modified by 2009.4.24
					//modified by 2009.5.2 先计算Wave参数，以便得到正确的box参数，提供给Locomotion::GlbMv::Forward and Backward
					//根据前后幅度变化值不会突变，修正最佳匹配矩形框的方向
					for(iNum=1;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] == 0)
						{
							structEData.ed_dpBodywaveStride[iNum]  = -1;
							structEData.ed_dpBodywaveHeight[iNum] = -1;
						}
						else 
						{
							double d1 = 0., d2 = 0., dtmp = 0.;
							int iNumPre = iNum;
							for (;;)
							{
								// find prior waveStride which is useful;
								iNumPre = iNumPre - 1;
								if (structEData.ed_dpBodywaveStride[iNumPre] != -1 ) break;								
							}

							// 相邻两帧的宽度不会出现太大变化
							d1 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveStride[iNumPre]);
							d2 = fabs(structEData.ed_dpBodywaveStride[iNum] - structEData.ed_dpBodywaveHeight[iNumPre]);
							if (d1 > d2)
							{
								// exchange the wave stride and height;
								dtmp = structEData.ed_dpBodywaveStride[iNum];  
								structEData.ed_dpBodywaveStride[iNum] = structEData.ed_dpBodywaveHeight[iNum];  
								structEData.ed_dpBodywaveHeight[iNum] = dtmp;
								if (structEData.ed_dpBodywaveHeight != 0)
								{
									structEData.ed_dpBodywaveSToH[iNum] = 
										structEData.ed_dpBodywaveStride[iNum] / structEData.ed_dpBodywaveHeight[iNum];
								}
							}

							// Normalize the wave by the worm's length
							// 单位 微米/ (1000 * 毫米)
							structEData.ed_dpBodywaveHeightNormal[iNum] = 
								structEData.ed_dpBodywaveHeight[iNum] / (1000 * structEData.BODYLENGTH_3M);
							structEData.ed_dpBodywaveStrideNormal[iNum] = 
								structEData.ed_dpBodywaveStride[iNum] / (1000 *structEData.BODYLENGTH_3M);
						}
					}

					//2009.4.24
					// 得到有效的参数，可直接用于画图
					int iUseNumTmp = 0; //
					double *dWaveStride = new double[structEData.nImgOfProc*sizeof(double)];
					double *dWaveHeight = new double[structEData.nImgOfProc*sizeof(double)];
					memset(dWaveStride,0,structEData.nImgOfProc*sizeof(double));
					memset(dWaveHeight,0,structEData.nImgOfProc*sizeof(double));
					for (iNum=0;iNum<iTotalFrames;iNum++)
					{
						if (structEData.IsUseful[iNum] != 0)
						{
							dWaveStride[iUseNumTmp] = structEData.ed_dpBodywaveStrideNormal[iNum];
							dWaveHeight[iUseNumTmp] = structEData.ed_dpBodywaveHeightNormal[iNum];
							structEData.ed_xTime[iUseNumTmp] = structEData.fTime * iNum;
							iUseNumTmp += 1;
						}
					}
					memcpy(structEData.ed_dpBodywaveStrideNormal, dWaveStride, structEData.nImgOfProc*sizeof(double));
					memcpy(structEData.ed_dpBodywaveHeightNormal, dWaveHeight, structEData.nImgOfProc*sizeof(double));

					// 统计上下四分位数和三均值
					myElegansFeatures.StatBubbleSort(dWaveHeight,iUseNumTmp);
					myElegansFeatures.StatTPM(dWaveHeight,iUseNumTmp);
					structEData.ed_dpBodywaveHeightNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveHeightNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveHeightNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					myElegansFeatures.StatBubbleSort(dWaveStride,iUseNumTmp);					
					myElegansFeatures.StatTPM(dWaveStride,iUseNumTmp);
					structEData.ed_dpBodywaveStrideNormal_25 = myElegansFeatures.STDATA[2]; //down 4
					structEData.ed_dpBodywaveStrideNormal_75 = myElegansFeatures.STDATA[1]; //up 4
					structEData.ed_dpBodywaveStrideNormal_3M = myElegansFeatures.STDATA[3]; //3 Mean

					delete [] dWaveHeight;
					delete [] dWaveStride;
					dWaveHeight = NULL;
					dWaveStride = NULL;
					// end of 'wave 参数'
					//////////////////////////////////////////////////////////////////////////

				}
				//参数提取结束			

				//Modified by 2009.9.4
				//为提高处理速度，屏蔽最后的算法验证movie show步骤；

				//////////////////////////////////////////////////////////////////////////
				//算法验证
				//Create Save File name and path 2009.4.24
				g_iFlagSpecial = 8;
				if (g_iFlagSpecial == 6)
				{
					iLocaBegin = strTmpPathOnly.Find('\\',4);
					iLocaEnd = strTmpPathOnly.Find( '\\' ,iLocaBegin+1);
					strLocation= strTmpPathOnly.Mid(iLocaBegin+1,iLocaEnd - iLocaBegin-1);
					if (strLocation == "")
					{
						strLocation.Format("%d-%d",currenttime.wHour,currenttime.wMinute);
					}				
					sprintf(chTmpFileName,"E:\\Worm Data\\%s",strLocation);								
					dwAttr = GetFileAttributes(chTmpFileName);//创建一个新的文件夹路径
					if(dwAttr == 0xFFFFFFFF)   //若文件夹不存在
						CreateDirectory(chTmpFileName,NULL);



					if (((StrRecName*)lpParameter)->bCount == TRUE)
					{
						//step one 读取来自Uncompress的数据
						//sprintf(fileName,"%s\\%s-[%d-%d]-8Gray.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
						sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
						//保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-[%d-%d]-8Final.avi",chTmpFileName,strTmpNameOnly,iBeginNum,iEndNum);
					}
					else
					{
						//step one 读取来自Uncompress的数据
						//sprintf(fileName,"%s\\%s-all-8Gray.avi",chTmpFileName,strTmpNameOnly);
						sprintf(fileName,"%s\\%s.avi",strTmpPathOnly,strTmpNameOnly);
						//保存的处理结果
						sprintf(chSaveFileName,"%s\\%s-all-8Final.avi",chTmpFileName,strTmpNameOnly);
					}


					if(!strnicmp(strrchr(chSaveFileName,'.'),".avi",4))
						DeleteFile(chSaveFileName);
					g_strFileName = fileName;

					bActive = 1;
					iTotalLeft=iTotalFrames;
					iReadBuffer = g_iReadBuffer;
					iReadTimes = 0;	
					iNum = 0;

					//Save the results in the form of AVI movie
					okLoadImageFile(hBoard,fileName,0,BUFFER,0,1);
					okGetTargetInfo(hBoard,BUFFER,0,NULL,(short *)&lHeight,&lStride_ch3);
					lStride = lStride_ch3 /3;
					lStrideRed = lStride;
					g_cvSavImg = cvCreateImage(cvSize(lStride,lHeight),8,3);
					g_cvColorImg = cvCreateImage(cvSize(lStride,lHeight),8,3);

					cvSet(g_cvColorImg,cvScalarAll(0),0);
					//cvZero(g_cvSavImg);
					cvSet(g_cvSavImg,cvScalarAll(0),0);
					//CV_FOURCC('X','V','I','D') ?? 压缩存储的结果会丢帧，最后2-3帧莫名消失？？
					CvVideoWriter* cvSavVideoFinal; 
					cvSavVideoFinal = cvCreateAVIWriter(chSaveFileName,0, (double)fRate , cvSize(lStride,lHeight) ,1);
					for(;;)
					{
						if (iTotalLeft <= 0 || bActive == 0)
						{	
							okStopCapture(hBoard);
							InvalidateRect(NULL,NULL,TRUE);
							iNum = 0;
							break;
						}
						if (iTotalLeft >= iReadBuffer) 
						{
							iTotalLeft = iTotalLeft-iReadBuffer;
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iReadBuffer);	

							//////////////////////////////////////////////////////////////////////////
							// 一
							for(i=0;i<iReadBuffer;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
								lStrideRed = lStride_ch3 /3;
								lStride = lStrideRed;

								//特殊处理 根据情况定制设计 一
								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(cvSavVideoFinal,g_cvSavImg);
								iNum+=1;

								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}
							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
							//	,BUFFER,0,iReadBuffer);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
						}
						if (iTotalLeft < iReadBuffer && iTotalLeft > 0) 
						{
							// 发送自定义消息
							sprintf(chTmpMsg,strMessageLoad);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							okLoadImageFile(hBoard,fileName,iNum,BUFFER,0,iTotalLeft);

							//////////////////////////////////////////////////////////////////////////
							// 二
							for(i=0;i<iTotalLeft;i++)
							{
								// 获取缓存中的图像数据保存地址；
								structEData.lpbuf =NULL;
								structEData.lpbuf=(LPBYTE)okGetTargetInfo(hBoard,BUFFER,i,NULL,(short *)&lHeight,&lStride_ch3);
								lStrideRed = lStride_ch3 /3;
								lStride = lStrideRed;

								//特殊处理 根据情况定制设计 二
								myElegansFeatures.SpecialExtraction_Show(g_cvSavImg,structEData.lpbuf,lHeight,lStride,iNum,iTotalFrames);
								cvWriteToAVI(cvSavVideoFinal,g_cvSavImg);
								iNum+=1;

								// 发送自定义消息，使进度条更新；
								::PostMessage(hWnd,WM_PLAYBACK_PROGRESS,iNum,0);
							}							

							// 发送自定义消息,正在存储
							sprintf(chTmpMsg,strMessageSave);
							::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

							//okSaveImageFile(hBoard,chSaveFileName,iReadTimes*iReadBuffer
							//	,BUFFER,0,iTotalLeft);
							okGetBufferSize(hBoard,(void **)&lpLinear,&dwSize);
							memset(lpLinear, 255, dwSize);

							iReadTimes += 1;
							iTotalLeft = 0;
						}
					}//结束

					//Sleep(500);
					cvReleaseVideoWriter(&cvSavVideoFinal);
					if (g_cvSavImg != NULL && g_cvColorImg != NULL)
					{
						//release saving image
						cvReleaseImage(&g_cvSavImg);
						cvReleaseImage(&g_cvColorImg);
						g_cvSavImg = NULL;
						g_cvColorImg = NULL;
					}
				}
				// 算法验证结束
				//////////////////////////////////////////////////////////////////////////


				okStopCapture(hBoard);
				InvalidateRect(NULL,NULL,TRUE);
				bWhile = FALSE;

				sprintf(chTmpMsg,_T("Congratulations!"));
				::PostMessage(hWnd,WM_MESSAGE,0,(LPARAM)chTmpMsg);

				//if (structEData.path != NULL)
				//	myElegansFeatures.DestroyStructData();//销毁structEData的相关变量

			} // end -- else 单个分析
		} //end -- if (bActive == 1)
	} //end -- while (bWhile == TRUE) 


	delete [] chTmpMsg;
	chTmpMsg = NULL;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CAnalysisTestDlg::OnStnClickedImage()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CAnalysisTestDlg::OnBnClickedButHeadTail()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_bAEndBEnd == TRUE)
	{
		g_bAEndBEnd = FALSE;
	}
	else
		g_bAEndBEnd = TRUE;
}

void CAnalysisTestDlg::OnEnChangeEditCcdScale7()
{

}
