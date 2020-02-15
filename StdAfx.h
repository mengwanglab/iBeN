// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__AAB16CD4_CC42_4E1A_BBE4_D858A48619D9__INCLUDED_)
#define AFX_STDAFX_H__AAB16CD4_CC42_4E1A_BBE4_D858A48619D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

#include <afxdao.h>         //����DAO���ݿ�֧��
#include <afxdb.h>
#include <odbcinst.h>

#include "DataPropety.h"

#include <afxtempl.h> //CArray��Ҫ��ͷ�ļ�

#endif // _AFX_NO_AFXCMN_SUPPORT

#include ".\OK_C30A\Okapi32.h" //����OK_C30A�ɼ���SDK��

//OpenCV add by haining 2008.12.3
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "cvaux.h"

#define IMAGE_NEED_TO_CAPTURE 9000 //������ɿɴ����movie֡��
//#define iTmpH 480  //������ͼ��ĸ�
//#define iTmpS 640  //������ͼ��Ŀ�
//2009.4.23
#define MaxMove 400.0 //����400um/sΪworm�ļ����˶�����

#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996)
#pragma warning(disable : 4995)


//{{AFX Measurement Studio
#include "NiIncludes.h"
//}}AFX Measurement Studio
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


extern HANDLE hBoard;                  //�ɼ������
extern HWND   hWnd;					//Ӧ�ó��򴰿ھ��
extern long   lHeight;
extern long   lStride;
extern long   lStride_ch3;
extern long   lStrideRed;
extern long   lSpecialHeight;
extern long   lSpecialStride;
extern long   lSpecStrideRed;

extern long lIndex;
extern BOOL bActive;
extern BOOL bPreview;
extern long		lScrnOffset;			//�ɼ�����ƫ��
extern short		sampwidth, sampheight;	//�ɼ����ڿ�ȡ��߶�
extern DWORD threadID_1;
extern DWORD threadID_2;
extern DWORD threadID_3;
extern DWORD threadID_4;
extern DWORD threadID_5_new;
extern SYSTEMTIME sysTimeBegin;
extern SYSTEMTIME sysTimeEnd;
extern long lSysTime;

extern BOOL bFlagGoOn;

extern CDaoDatabase g_db;			//���ݿ�
extern CDaoRecordset g_RecSet;		//��¼��
extern CString g_strFileName;

extern int g_iFlagSpecial;

//extern char *g_strErrMes;

extern int g_iBodyBendsFilter;

extern double g_dCCDScale;
//2009.3.31
extern int g_iAreaUpLevel;
extern int g_iAreaDownLevel;
//2009.9.3
extern int g_iReadBuffer;

extern BLOCKINFO g_blk;
extern DWORD g_iSizeImage;


//add by haining 2008.12.3
//OpenCV ����
extern IplImage* g_cvImg;
extern IplImage* g_cvSrc;
extern IplImage* g_cvDst;
//2009-3-30
extern IplImage* g_cvBin;
//2009-4-8
extern IplImage* g_cvSavImg;
//
extern IplImage* g_cvColorImg;
extern IplImage* g_cvThinImg;

//Add by haining 2009.3.30
extern CvMat* cvPFrameMat;
extern CvMat* cvPFrMat;
extern CvMat* cvPBkMat;
//add by haining 2009.4.8
extern CvVideoWriter* g_cvSavVideo;


extern int g_iRunningFlag;
extern double g_dMaxMove;

extern int g_iMaxSpeed;
extern int g_iRoamToDwell;

extern float g_fBinningFlag;
extern int g_iMultiOtsuLevel;
extern int g_iMultiOtsuThNum;

extern int g_iImageFlag;
extern CString g_strImgWindowName;

//2010.6.10 temp Gaussian Background
extern IplImage* g_pFrame;   
extern IplImage* g_pFrImg; 
extern IplImage* g_pBkImg; 
extern CvGaussBGModel* g_bg_model;

extern BOOL g_bAEndBEnd;
extern int g_iSpineControlPoints;

extern IplImage* g_pImgBigObeject;
extern double g_dWormLength;
extern double g_dWormWidth;
extern double g_dWormWidthAdd;
extern double g_dWormPerim;
extern double g_dWormPerimAdd;
extern CvPoint g_cvPCentroid;
extern int g_iCntAendAbnormal;
#endif // !defined(AFX_STDAFX_H__AAB16CD4_CC42_4E1A_BBE4_D858A48619D9__INCLUDED_)
