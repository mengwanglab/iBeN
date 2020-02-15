// ChosseHead.cpp : implementation file
//

#include "stdafx.h"
#include "AnalysisTest.h"
#include "ChosseHead.h"
#include "AnalysisTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChosseHead dialog
extern CFeatures myElegansFeatures;
extern ElegansData structEData;//数据接口

CChosseHead::CChosseHead(CWnd* pParent /*=NULL*/)
	: CDialog(CChosseHead::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChosseHead)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	iTmpDataNum = 0;
	iTmpImageNum = 0;
}


void CChosseHead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChosseHead)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChosseHead, CDialog)
	//{{AFX_MSG_MAP(CChosseHead)
	ON_BN_CLICKED(IDC_BUT_CHOOSE_A, OnButChooseA)
	ON_BN_CLICKED(IDC_BUT_CHOOSE_B, OnButChooseB)
	ON_BN_CLICKED(IDC_BUT_ABORT, OnButAbort)
	ON_BN_CLICKED(IDC_BUT_OK, OnButOk)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChosseHead message handlers

//=================================================================
//Name: OnButChooseA
//Func: 选择A端作为头部
//Editor: haining
//Parameter: 
//Return Value: 
//Date: 2007-10-29
//History: 
//=================================================================
void CChosseHead::OnButChooseA() 
{
	// TODO: Add your control notification handler code here
	structEData.Key_H[iTmpDataNum] = 1;//选择A端是头
	unsigned char *lpTmp = new unsigned char[lHeight*lStride];
	memset(lpTmp,0,lHeight*lStride*sizeof(unsigned char));
	memcpy(lpTmp,structEData.lpbuf,lHeight*lStride*sizeof(unsigned char));
	
	if (lHeight > 800 && lStride > 600) 
	{
		//特殊处理 若图像大于800*600，则缩小1/4显示
		myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
		myElegansFeatures.ShowNewHeadExtraction_Half(structEData.lpHalf,(int)(lHeight*0.5),(int)(lStride*0.5),iTmpDataNum);
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
	{
		myElegansFeatures.ShowNewHeadExtraction(structEData.lpbuf,lHeight,lStride,iTmpDataNum);
		okConvertRect(hBoard,SCREEN,0,BUFFER,iTmpImageNum,1);
	}
	//okConvertRect(hBoard,SCREEN,0,BUFFER,iTmpImageNum,1);
	memcpy(structEData.lpbuf,lpTmp,lHeight*lStride);
	delete [] lpTmp;
	lpTmp = NULL;
}

//=================================================================
//Name: OnButChooseB
//Func: 选择B端作为头部
//Editor: haining
//Parameter: 
//Return Value: 
//Date: 2007-10-29
//History: 
//=================================================================
void CChosseHead::OnButChooseB() 
{
	// TODO: Add your control notification handler code here
	structEData.Key_H[iTmpDataNum] = 2;//选择B端是头
	unsigned char *lpTmp = new unsigned char[lHeight*lStride];
	memset(lpTmp,0,lHeight*lStride);
	memcpy(lpTmp,structEData.lpbuf,lHeight*lStride);
	
	if (lHeight > 800 && lStride > 600) 
	{
		//特殊处理 若图像大于800*600，则缩小1/4显示
		myElegansFeatures.MemCopyHalf(structEData.lpbuf,structEData.lpHalf,lHeight,lStride);
		myElegansFeatures.ShowNewHeadExtraction_Half(structEData.lpHalf,(int)(lHeight*0.5),(int)(lStride*0.5),iTmpDataNum);
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
	{
		myElegansFeatures.ShowNewHeadExtraction(structEData.lpbuf,lHeight,lStride,iTmpDataNum);
		okConvertRect(hBoard,SCREEN,0,BUFFER,iTmpImageNum,1);
	}
	//okConvertRect(hBoard,SCREEN,0,BUFFER,iTmpImageNum,1);
	
	memcpy(structEData.lpbuf,lpTmp,lHeight*lStride);
	delete [] lpTmp;
	lpTmp = NULL;
}

//=================================================================
//Name: OnButAbort
//Func: 放弃，将这一帧置为不可用
//Editor: haining
//Parameter: 
//Return Value: 
//Date: 2007-10-29
//History: 
//=================================================================
void CChosseHead::OnButAbort() 
{
	// TODO: Add your control notification handler code here
	structEData.IsUseful[iTmpDataNum] = 0;//放弃这一帧
}

void CChosseHead::OnButOk() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CChosseHead::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}
