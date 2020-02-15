// ManeageList.cpp : implementation file
//

#include "stdafx.h"
#include "AnalysisTest.h"
#include "ManeageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CManeageList

CManeageList::CManeageList()
{
	//初始化
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd(); //与对话框接口，dlg指针指向ListCtrl所在对话框
}

CManeageList::~CManeageList()
{

}


BEGIN_MESSAGE_MAP(CManeageList, CListCtrl)
	//{{AFX_MSG_MAP(CManeageList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManeageList message handlers


BOOL CManeageList::InitList()
{
	DWORD listStyle;
	//设置风格
	listStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | 
		        LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE |
				LVS_EX_UNDERLINECOLD;
    dlg->m_FileNameList.SetExtendedStyle(listStyle);
	//设置列名
    dlg->m_FileNameList.InsertColumn(0,"索引",LVCFMT_LEFT,20);
	dlg->m_FileNameList.InsertColumn(1,"帧率",LVCFMT_LEFT,60);
	//dlg->m_FileNameList.InsertColumn(1,"状态",LVCFMT_LEFT,50);
	dlg->m_FileNameList.InsertColumn(2,"文件名称",LVCFMT_LEFT,300);
	dlg->m_FileNameList.InsertColumn(3,"帧数",LVCFMT_LEFT,65);
	dlg->m_FileNameList.InsertColumn(4,"图像大小",LVCFMT_LEFT,120);
	dlg->m_FileNameList.InsertColumn(5,"加载时间",LVCFMT_LEFT,220);
	dlg->m_FileNameList.InsertColumn(6,"分析耗时",LVCFMT_LEFT,100);
	dlg->m_FileNameList.InsertColumn(7,"文件路径",LVCFMT_LEFT,200);
	//dlg->m_FileNameList.InsertColumn(8,"帧率",LVCFMT_LEFT,50);
	dlg->m_FileNameList.InsertColumn(8,"状态",LVCFMT_LEFT,120);
	
	dlg->m_FileNameList.DeleteAllItems();
	
	//修改CListCtrl的背景颜色 2008.10.21
	dlg->m_FileNameList.SetBkColor(RGB(230,235,245));
	dlg->m_FileNameList.SetTextBkColor(RGB(230,235,245));
	
	//修改CListCtrl的字体 2008.10.21
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
	dlg->m_FileNameList.SetFont(&font,TRUE);


	return TRUE;
}

void CManeageList::ClickCol_Sort(NM_LISTVIEW* pNMListViewTmp)
{
	if(pNMListViewTmp->iSubItem==dlg->SortColumn)
		dlg->Bool_OrderAsc=!dlg->Bool_OrderAsc;
	else
	{
		dlg->Bool_OrderAsc=TRUE;
		dlg->SortColumn=pNMListViewTmp->iSubItem;
	}	
	
	int count=dlg->m_FileNameList.GetItemCount();
	for(int i=0;i<count;i++)
		dlg->m_FileNameList.SetItemData(i,i);	
	
	dlg->m_FileNameList.SortItems(ItemCompare,(DWORD)&dlg->m_FileNameList);
}

///////////////////////////////////////////////////////////
//Func: 排序的CALLBACK函数.比较列表中的两个值.收到SortItems传递过来的CListCtrl指针
//Parameter: None
//Return Value: None
//Date: 2004-3-24
///////////////////////////////////////////////////////////
int CALLBACK CManeageList::ItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CListCtrl *pListCtrl=(CListCtrl*)lParamSort;     //传递ListCtrl的指针
	//	CPollView *pData=(CPollView*)(pListCtrl->GetParent());   //得到页面DATA的指针
	CAnalysisTestDlg *tmpDlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd();	
	
	CString item1,item2;
	int result;
	
	int FirstData=-1,SecondData=-1;
	LVFINDINFO FindInfo; 
    FindInfo.flags=LVFI_PARAM; 
	
	FindInfo.lParam=lParam1;
	FirstData=pListCtrl->FindItem(&FindInfo);
	item1=pListCtrl->GetItemText(FirstData,tmpDlg->SortColumn);
	
	FindInfo.lParam=lParam2;
	SecondData=pListCtrl->FindItem(&FindInfo);
	item2=pListCtrl->GetItemText(SecondData,tmpDlg->SortColumn);
	
	if((tmpDlg->SortColumn==0) || (tmpDlg->SortColumn==3))   //对索引和年龄排序
	{
		int intItem1=atol(item1); 
		int intItem2=atol(item2);
		
		if(intItem1==intItem2)
			result=0;
		else
			result=(intItem1<intItem2)?-1:1;
	}
	else if(tmpDlg->SortColumn==4)   //对日期排序
	{
		CString item1_Y,item1_M,item1_D,item2_Y,item2_M,item2_D;
		int n=0;
		
		//分离出item1的年,月,日
		int item1_Len=item1.GetLength();
		n=item1.ReverseFind('-');
		item1_D=item1.Right(item1_Len-n-1);  //得到日期
		item1=item1.Left(n);                 //去掉日期
		n=item1.ReverseFind('-');
		item1_Y=item1.Left(n);
		item1_Len=item1.GetLength();
		item1_M=item1.Right(item1_Len-n-1); //得到日期
		
		int intItem1_Y=atoi(item1_Y);
		int intItem1_M=atoi(item1_M);
		int intItem1_D=atoi(item1_D);
		
		//分离出item2的年,月,日
		int item2_Len=item2.GetLength();
		n=item2.ReverseFind('-');
		item2_D=item2.Right(item2_Len-n-1);  //得到日期
		item2=item2.Left(n);                 //去掉日期
		n=item2.ReverseFind('-');
		item2_Y=item2.Left(n);
		item2_Len=item2.GetLength();
		item2_M=item2.Right(item2_Len-n-1); //得到日期
		
		int intItem2_Y=atoi(item2_Y);
		int intItem2_M=atoi(item2_M);
		int intItem2_D=atoi(item2_D);
		
		//依次判断年,月,日
		if(intItem1_Y==intItem2_Y)
		{
			if(intItem1_M==intItem2_M)
			{
				if(intItem1_D==intItem2_D)
					result=0;
				else
					result=(intItem1_D<intItem2_D)?-1:1;
			}
			else
				result=(intItem1_M<intItem2_M)?-1:1;
		}
		else
			result=(intItem1_Y<intItem2_Y)?-1:1;
	}
	
	else               //对姓名和性别排序
		result=item1.Compare(item2);
	
	
	if(tmpDlg->Bool_OrderAsc)
		return result;
	else
		return result*(-1);
}
