// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__B5C1C543_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_)
#define AFX_LINE_H__B5C1C543_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileBody.h"

//#define LINE_DATA_BLK_SIZE	22

class CLine  
{
public:
	CLine(CString strDataPath);
	virtual ~CLine();
	void Clr();						//クリア
	void SetMemRec9(DWORD *dwpCode,int nMapLevel);	//９タイル分のデータをファイルよりメモリに設定
	long GetBodyMaxCnt();

	struct_LineBody *m_pStructLineBody;

private:
	CFileBody fb3;
	CFileBody fb6;
	CFileBody fb9;
	int m_nMapLevel;

};

#endif // !defined(AFX_LINE_H__B5C1C543_4D81_11D5_8619_0040CA1F5FB7__INCLUDED_)
