// stdafx.cpp : source file that includes just the standard includes
//	AnalysisTest.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


//全局变量
HANDLE hBoard;                  //采集卡句柄
HWND   hWnd;					//应用程序窗口句柄

long lIndex=-1;
long    lHeight=0;
long    lStride=0;
long    lStride_ch3=0;
long    lStrideRed=0;

long    lSpecialHeight = 0;
long    lSpecialStride = 0;
long    lSpecStrideRed = 0;
  
BOOL bActive=0;
BOOL bPreview=0; //预览功能启用标志，0为关闭，1为开启
long		lScrnOffset=0;			//采集窗口偏移
short		sampwidth=0, sampheight=0;	//采集窗口宽度、高度
DWORD threadID_1;
DWORD threadID_2;
DWORD threadID_3;
DWORD threadID_4;
DWORD threadID_5_new;
SYSTEMTIME sysTimeBegin;
SYSTEMTIME sysTimeEnd;
long lSysTime;

BOOL bFlagGoOn = FALSE;//用于人工识别头尾时，暂停分析线程用

CDaoDatabase g_db;					//数据库
CDaoRecordset g_RecSet(&g_db);		//记录集
CString g_strFileName;//单个分析时，当前数据文件的全路径

int g_iFlagSpecial = 0;//特殊分析的步骤标志，1表示binary处理，2表示skeleton处理

//char *g_strErrMes; //错误消息，写入提示区域

//校正参数
int g_iBodyBendsFilter;//bodybends滤波器参数

//CCD参数
double g_dCCDScale;
int g_iReadBuffer;
//2009.3.31
int g_iAreaUpLevel;
int g_iAreaDownLevel;

//add by haining 2008.12.2
//用于图像指针
BLOCKINFO	g_blk;	
DWORD g_iSizeImage = 0;


//add by haining 2008.12.3
//OpenCV 处理
IplImage* g_cvImg;
IplImage* g_cvSrc;
IplImage* g_cvDst;
//2009.3.30
IplImage* g_cvBin;
//2009.4.8 create for saving results
IplImage* g_cvSavImg = NULL;

//2009.3.25
IplImage* g_cvColorImg = NULL;
//2009.3.28
IplImage* g_cvThinImg = NULL;

//Add by haining 2009.3.30
CvMat* cvPFrameMat = NULL;//用于去背景算法
CvMat* cvPFrMat = NULL;
CvMat* cvPBkMat = NULL;

CvVideoWriter* g_cvSavVideo = NULL;

//add by haining 2009.4.8
int g_iRunningFlag = 0; //用于临时的线程终止判断
//add by haining 2009.4.23 全局设置的参数
double g_dMaxMove = 0; //两帧间worm最大移动距离，单位um，若超出这个值，需另作处理

//2009.9
int g_iMaxSpeed = 400; //假定的最大运动速率400um/s
int g_iRoamToDwell = 50; // 设置roam和dwell的判定标准为角度改变50度

//2009.9.21
float g_fBinningFlag =0.5; //
int g_iMultiOtsuLevel = 4;
int g_iMultiOtsuThNum = 2;

//2010.3.11
int g_iImageFlag = 0;
CString g_strImgWindowName="";


//2010.6.10 temp Gaussian Background
IplImage* g_pFrame = NULL;   
IplImage* g_pFrImg = NULL; 
IplImage* g_pBkImg = NULL; 
//初始化高斯混合模型参数
CvGaussBGModel* g_bg_model=NULL;

//2010.9
BOOL g_bAEndBEnd = FALSE;

int g_iSpineControlPoints = 20; //控制点的数目

//2011.1.12
IplImage* g_pImgBigObeject = NULL;
double g_dWormLength = 0.0;
double g_dWormWidth = 0.0;
double g_dWormWidthAdd = 0.0;
double g_dWormPerim = 0.0;
double g_dWormPerimAdd = 0.0;
CvPoint g_cvPCentroid;
int g_iCntAendAbnormal = 0;