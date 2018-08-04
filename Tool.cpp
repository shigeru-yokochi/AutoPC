// Tool.cpp: CTool �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Tool.h"
#include "Common.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CTool::CTool()
{
	m_dfGpsEOff = 0.0;
	m_dfGpsNOff = 0.0;
	m_dfGpsDeg	= 0.0;


}

CTool::~CTool()
{

}
#define EarthR 6367467.5
#define RAD    3.141592653589793 / 180.0

//(******************************************************************************)
double CTool::DegSin(double f)
{
//	CCommon commom;
	return sin(f*RAD);
}
//(******************************************************************************)
double CTool::DegCos(double f)
{
//	CCommon commom;
	return cos(f*RAD);
}
//(******************************************************************************)
double CTool::PointToMeter(const double E1, const double N1, const double E2, const double N2)
{
	double R, E, N;

	R = DegCos((fabs(N1)+fabs(N2))/2.0) * EarthR;
	E = DegSin(fabs(E1-E2)) * R;
	N = DegSin(fabs(N1-N2)) * EarthR;

	return sqrt(E*E + N*N);
}
long CTool::PointToMeter(const long E1, const long N1, const long E2, const long N2)
{

//#define Cnv 10000000.0
	double R, E, N;


	R = DegCos((fabs(N1/DEF_CONVERT)+fabs(N2/DEF_CONVERT))/2.0) * EarthR;
	E = DegSin(fabs(E1/DEF_CONVERT-E2/DEF_CONVERT)) * R;
	N = DegSin(fabs(N1/DEF_CONVERT-N2/DEF_CONVERT)) * EarthR;

	return (long)sqrt(E*E + N*N);
}
//(******************************************************************************)
CString CTool::RealToStr(const double Num)
{
	double X;
	WORD Deg, Min, Sec, Perc;
	CString S;

	Deg = (WORD)floor(Num);
	X = Num - Deg;
	Min = (WORD)floor(X*60.0);
	X = X - Min/60.0;
	Sec = (WORD)floor(X*3600.00001);
	X = X - Sec/3600.0;
	Perc = (WORD)(X*360000.0);
	if( Perc >= 100 ) {
		++Sec;
		Perc = 0;
	}
	if( Sec >= 60 ) {
		++Min;
		Sec = 0;
	}
	if( Min >= 60 ) {
		++Deg;
		Min = 0;
	}
	S.Format(L"%3.3d%2.2d%2.2d%2.2d", Deg, Min, Sec, Perc);
	return S;
}
//(******************************************************************************)
double CTool::StrToExtended(CString S)
{
	double E, F;
	int c, n, i;

	F = 0;
	n = S.GetLength();
	c = S.Find('.');
	if( c < 0 ) c = n;
	E = 1.0/10.0;
//	for( i = c+1; i < n; ++i) {
	for( i = c+1; i < n; i++) {
		F += (S.GetAt(i) - '0') * E;
		E /= 10;
	}
	E = 1.0;
	for( i = c-1; i >= 0; --i) {
		F += (S.GetAt(i) - '0') * E;
		E *= 10;
	}
	return F;
}
//(******************************************************************************)
int CTool::StrToIntDef(const CString S, const int n)
{
	int a, E, i, N;
	
	a = 0;
	N = S.GetLength();
	E = 1;
	for( i = N-1; i >= 0; --i) {
		a += (S.GetAt(i) - '0') * E;
		E *= 10;
	}
	return a;
}

/****************************************************************************
*  �������Ə������𕪂���
*  100.00��"100" ".00"�ɂ���
*****************************************************************************/
void CTool::UnderSplit(CString str,CString* strpInt,CString* strpUnder)
{
	int nPos=0,i,nLen = str.GetLength();
	for(i=0;i<nLen;i++){
		if(str.GetAt(i) != '.')continue;
		nPos = i;
		break;
	}

	if(nPos == 0){				//�������Ȃ�
		*strpInt = str;
		*strpUnder = "";
		return;
	}

	*strpInt = str.Left(nPos);
	*strpUnder = str.Mid(nPos+1);
}
/****************************************************************
*   �����_��5���ڐ؂�̂Ăď���4����
****************************************************************/
void CTool::Under5Cut(double *val)
{
	CString str;
	int nLen;

	str.Format(L"%0.5lf",*val);
	nLen = str.GetLength();
	str.SetAt(nLen-1,'0');
	*val = atof(CStringToChar(str));
}
//(******************************************************************************)
char* CTool::CStringToChar(CString Str)
{
	int n, i;
//	char m_s[1024];

	n = Str.GetLength();
	for(i = 0; i < n; i++) {
		m_s[i] = (char)Str.GetAt(i);
	}
	m_s[i] = 0;
	return &m_s[0];
}
//(******************************************************************************)
char* CTool::CStringToChar2(CString Str)
{
	int  n, i, j;
	UINT C;
//	char m_s[1024];

	n = Str.GetLength();
	for(j = i = 0; i < n; i++) {
		C = Str.GetAt(i);
		if( C > 255 ) {
			m_s[j] = (char)(C & 0xff);   ++j;
			m_s[j] = (char)(C >> 8); ++j;
			
		} else {
			m_s[j] = (char)C; ++j;
		}
	}
	m_s[j] = 0;
	return &m_s[0];
}

/****************************************************************************
*  DWORD����ʉ��ʂ�WORD�ɕ����Ēl��ݒ肷��
*	*dw :�ݒ肳���ϐ�
*	w   :�ݒ�l
*	HighLow : LOW_WORD:���ʂɐݒ� HIGH_WORD:��ʂɐݒ� 
*****************************************************************************/
void CTool::SetDwHighLow(DWORD* dw,WORD w,int HighLow)
{
	if(HighLow == LOW_WORD){				
		*(dw) &= 0xffff0000;
		*(dw) |= w&0x0000ffff;
	}
	else{
		*(dw) &= 0x0000ffff;
		*(dw) |= (w<<16)&0xffff0000;
	}
}
/****************************************************************************
*  DWORD����ʉ��ʂ�WORD�ɕ����Ēl���l������
*	dw :�l�������ϐ�
*	return   :�l���l
*	HighLow : LOW_WORD:���ʂ���l�� HIGH_WORD:��ʂ���l��
*****************************************************************************/
WORD CTool::GetDwHighLow(DWORD dw,int HighLow)
{
	if(HighLow == HIGH_WORD)return (WORD)(dw>>16);
	else			        return (WORD)dw;
}


