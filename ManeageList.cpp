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
	//��ʼ��
	dlg = (CAnalysisTestDlg*)AfxGetApp()->GetMainWnd(); //��Ի���ӿڣ�dlgָ��ָ��ListCtrl���ڶԻ���
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
	//���÷��
	listStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | 
		        LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE |
				LVS_EX_UNDERLINECOLD;
    dlg->m_FileNameList.SetExtendedStyle(listStyle);
	//��������
    dlg->m_FileNameList.InsertColumn(0,"����",LVCFMT_LEFT,20);
	dlg->m_FileNameList.InsertColumn(1,"֡��",LVCFMT_LEFT,60);
	//dlg->m_FileNameList.InsertColumn(1,"״̬",LVCFMT_LEFT,50);
	dlg->m_FileNameList.InsertColumn(2,"�ļ�����",LVCFMT_LEFT,300);
	dlg->m_FileNameList.InsertColumn(3,"֡��",LVCFMT_LEFT,65);
	dlg->m_FileNameList.InsertColumn(4,"ͼ���С",LVCFMT_LEFT,120);
	dlg->m_FileNameList.InsertColumn(5,"����ʱ��",LVCFMT_LEFT,220);
	dlg->m_FileNameList.InsertColumn(6,"������ʱ",LVCFMT_LEFT,100);
	dlg->m_FileNameList.InsertColumn(7,"�ļ�·��",LVCFMT_LEFT,200);
	//dlg->m_FileNameList.InsertColumn(8,"֡��",LVCFMT_LEFT,50);
	dlg->m_FileNameList.InsertColumn(8,"״̬",LVCFMT_LEFT,120);
	
	dlg->m_FileNameList.DeleteAllItems();
	
	//�޸�CListCtrl�ı�����ɫ 2008.10.21
	dlg->m_FileNameList.SetBkColor(RGB(230,235,245));
	dlg->m_FileNameList.SetTextBkColor(RGB(230,235,245));
	
	//�޸�CListCtrl������ 2008.10.21
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
//Func: �����CALLBACK����.�Ƚ��б��е�����ֵ.�յ�SortItems���ݹ�����CListCtrlָ��
//Parameter: None
//Return Value: None
//Date: 2004-3-24
///////////////////////////////////////////////////////////
int CALLBACK CManeageList::ItemCompare(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
	CListCtrl *pListCtrl=(CListCtrl*)lParamSort;     //����ListCtrl��ָ��
	//	CPollView *pData=(CPollView*)(pListCtrl->GetParent());   //�õ�ҳ��DATA��ָ��
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
	
	if((tmpDlg->SortColumn==0) || (tmpDlg->SortColumn==3))   //����������������
	{
		int intItem1=atol(item1); 
		int intItem2=atol(item2);
		
		if(intItem1==intItem2)
			result=0;
		else
			result=(intItem1<intItem2)?-1:1;
	}
	else if(tmpDlg->SortColumn==4)   //����������
	{
		CString item1_Y,item1_M,item1_D,item2_Y,item2_M,item2_D;
		int n=0;
		
		//�����item1����,��,��
		int item1_Len=item1.GetLength();
		n=item1.ReverseFind('-');
		item1_D=item1.Right(item1_Len-n-1);  //�õ�����
		item1=item1.Left(n);                 //ȥ������
		n=item1.ReverseFind('-');
		item1_Y=item1.Left(n);
		item1_Len=item1.GetLength();
		item1_M=item1.Right(item1_Len-n-1); //�õ�����
		
		int intItem1_Y=atoi(item1_Y);
		int intItem1_M=atoi(item1_M);
		int intItem1_D=atoi(item1_D);
		
		//�����item2����,��,��
		int item2_Len=item2.GetLength();
		n=item2.ReverseFind('-');
		item2_D=item2.Right(item2_Len-n-1);  //�õ�����
		item2=item2.Left(n);                 //ȥ������
		n=item2.ReverseFind('-');
		item2_Y=item2.Left(n);
		item2_Len=item2.GetLength();
		item2_M=item2.Right(item2_Len-n-1); //�õ�����
		
		int intItem2_Y=atoi(item2_Y);
		int intItem2_M=atoi(item2_M);
		int intItem2_D=atoi(item2_D);
		
		//�����ж���,��,��
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
	
	else               //���������Ա�����
		result=item1.Compare(item2);
	
	
	if(tmpDlg->Bool_OrderAsc)
		return result;
	else
		return result*(-1);
}
