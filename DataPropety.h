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
	CDataPropety(	/*CString name,    //��������
	CString kind,    //��������
	int *lpt,      
	float *lpf,
    int p*/);

	virtual ~CDataPropety();
public:
	CString Name;    //��������
	CString Kind;    //��������
	int *lpint; 
	unsigned char *lpunchar;
	char *lpchar;
	float *lpfloat;
	double *lpdouble;
    int propety;     // 1��ʾ������ �� 2��ʾ�����
};

#endif // !defined(AFX_DATAPROPETY_H__8FEF3A0F_5920_4DAA_A4B0_0BE0E3FDF988__INCLUDED_)
