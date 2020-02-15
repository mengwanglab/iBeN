// stdafx.cpp : source file that includes just the standard includes
//	AnalysisTest.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


//ȫ�ֱ���
HANDLE hBoard;                  //�ɼ������
HWND   hWnd;					//Ӧ�ó��򴰿ھ��

long lIndex=-1;
long    lHeight=0;
long    lStride=0;
long    lStride_ch3=0;
long    lStrideRed=0;

long    lSpecialHeight = 0;
long    lSpecialStride = 0;
long    lSpecStrideRed = 0;
  
BOOL bActive=0;
BOOL bPreview=0; //Ԥ���������ñ�־��0Ϊ�رգ�1Ϊ����
long		lScrnOffset=0;			//�ɼ�����ƫ��
short		sampwidth=0, sampheight=0;	//�ɼ����ڿ�ȡ��߶�
DWORD threadID_1;
DWORD threadID_2;
DWORD threadID_3;
DWORD threadID_4;
DWORD threadID_5_new;
SYSTEMTIME sysTimeBegin;
SYSTEMTIME sysTimeEnd;
long lSysTime;

BOOL bFlagGoOn = FALSE;//�����˹�ʶ��ͷβʱ����ͣ�����߳���

CDaoDatabase g_db;					//���ݿ�
CDaoRecordset g_RecSet(&g_db);		//��¼��
CString g_strFileName;//��������ʱ����ǰ�����ļ���ȫ·��

int g_iFlagSpecial = 0;//��������Ĳ����־��1��ʾbinary����2��ʾskeleton����

//char *g_strErrMes; //������Ϣ��д����ʾ����

//У������
int g_iBodyBendsFilter;//bodybends�˲�������

//CCD����
double g_dCCDScale;
int g_iReadBuffer;
//2009.3.31
int g_iAreaUpLevel;
int g_iAreaDownLevel;

//add by haining 2008.12.2
//����ͼ��ָ��
BLOCKINFO	g_blk;	
DWORD g_iSizeImage = 0;


//add by haining 2008.12.3
//OpenCV ����
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
CvMat* cvPFrameMat = NULL;//����ȥ�����㷨
CvMat* cvPFrMat = NULL;
CvMat* cvPBkMat = NULL;

CvVideoWriter* g_cvSavVideo = NULL;

//add by haining 2009.4.8
int g_iRunningFlag = 0; //������ʱ���߳���ֹ�ж�
//add by haining 2009.4.23 ȫ�����õĲ���
double g_dMaxMove = 0; //��֡��worm����ƶ����룬��λum�����������ֵ������������

//2009.9
int g_iMaxSpeed = 400; //�ٶ�������˶�����400um/s
int g_iRoamToDwell = 50; // ����roam��dwell���ж���׼Ϊ�Ƕȸı�50��

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
//��ʼ����˹���ģ�Ͳ���
CvGaussBGModel* g_bg_model=NULL;

//2010.9
BOOL g_bAEndBEnd = FALSE;

int g_iSpineControlPoints = 20; //���Ƶ����Ŀ

//2011.1.12
IplImage* g_pImgBigObeject = NULL;
double g_dWormLength = 0.0;
double g_dWormWidth = 0.0;
double g_dWormWidthAdd = 0.0;
double g_dWormPerim = 0.0;
double g_dWormPerimAdd = 0.0;
CvPoint g_cvPCentroid;
int g_iCntAendAbnormal = 0;