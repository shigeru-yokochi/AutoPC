// Tool.h: CTool クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOL_H__0B67B1B2_AE1B_11D4_869F_005004618BB0__INCLUDED_)
#define AFX_TOOL_H__0B67B1B2_AE1B_11D4_869F_005004618BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LOW_WORD	0
#define HIGH_WORD	1

class CTool  
{
public:
	CTool();
	virtual ~CTool();
	
	double	DegSin(double f);
	double	DegCos(double f);
	double	PointToMeter(const double E1, const double N1, const double E2, const double N2);
	long	PointToMeter(const long E1, const long N1, const long E2, const long N2);

	CString	RealToStr(const double Num);
	double	StrToExtended(const CString S);
    char*	CStringToChar(CString Str);
    char*	CStringToChar2(CString Str);
	StrToIntDef(const CString S, const int n);
	void UnderSplit(CString str,CString* strpInt,CString* strpUnder);
	void Under5Cut(double *val);
	void SetDwHighLow(DWORD* dw,WORD w,int HighLow);
	WORD GetDwHighLow(DWORD dw,int HighLow);


//private:
	double m_dfGpsEOff, m_dfGpsNOff, m_dfGpsDeg;
	char m_s[1024];


};

#endif // !defined(AFX_TOOL_H__0B67B1B2_AE1B_11D4_869F_005004618BB0__INCLUDED_)
