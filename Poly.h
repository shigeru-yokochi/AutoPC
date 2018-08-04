// Poly.h: interface for the CPoly class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLY_H__9577B024_33C1_11D5_8968_0040CA1F5D30__INCLUDED_)
#define AFX_POLY_H__9577B024_33C1_11D5_8968_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileBodyPoly.h"


class CPoly  
{
public:
	CPoly(CString strDataPath);
	virtual ~CPoly();
	long GetBodyMaxCnt();
	void SetMemRec9(DWORD *dwpCode,int nMapLevel);
	void Clr();						//ÉNÉäÉA
	struct_PolyBody *m_pStructPolyBody;

private:

	CFileBodyPoly fb3;
	CFileBodyPoly fb6;
	CFileBodyPoly fb9;
	int m_nMapLevel;

};

#endif // !defined(AFX_POLY_H__9577B024_33C1_11D5_8968_0040CA1F5D30__INCLUDED_)
