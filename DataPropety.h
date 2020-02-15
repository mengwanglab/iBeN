// DataPropety.h: interface for the CDataPropety class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPROPETY_H__8FEF3A0F_5920_4DAA_A4B0_0BE0E3FDF988__INCLUDED_)
#define AFX_DATAPROPETY_H__8FEF3A0F_5920_4DAA_A4B0_0BE0E3FDF988__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataPropety  
{
public:
	CDataPropety(	/*CString name,    //表相名字
	CString kind,    //数剧类型
	int *lpt,      
	float *lpf,
    int p*/);

	virtual ~CDataPropety();
public:
	CString Name;    //表相名字
	CString Kind;    //数剧类型
	int *lpint; 
	unsigned char *lpunchar;
	char *lpchar;
	float *lpfloat;
	double *lpdouble;
    int propety;     // 1表示单个数 ， 2表示多个数
};

#endif // !defined(AFX_DATAPROPETY_H__8FEF3A0F_5920_4DAA_A4B0_0BE0E3FDF988__INCLUDED_)
