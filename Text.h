// Text.h: interface for the CText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXT_H__B5C1C546_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_)
#define AFX_TEXT_H__B5C1C546_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Common.h"
#include "FileBody.h"


class CText  
{
public:
	CText(CString strDataPath);
	virtual ~CText();
	void Clr();						//ÉNÉäÉA
	void SetMemRec9(DWORD *dwpCode,int nMapLevel);
	long GetBodyMaxCnt();
	struct_TextBody *m_pStructTextBody;
private:
	int m_nMapLevel;
	CFileBody fb1;
	CFileBody fb2;
	CFileBody fb3;
	CFileBody fb4;
	CFileBody fb5;
	CFileBody fb6;
	CFileBody fb7;
	CFileBody fb8;
	CFileBody fb9;
	CFileBody fb10;

};

#endif // !defined(AFX_TEXT_H__B5C1C546_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_)
