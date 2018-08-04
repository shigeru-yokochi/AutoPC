// NameBody.h: interface for the CNameBody class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAMEBODY_H__B031BA98_8E07_4C89_93F0_FBA7745E8E9D__INCLUDED_)
#define AFX_NAMEBODY_H__B031BA98_8E07_4C89_93F0_FBA7745E8E9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NameIndex.h"

//--------------NAMEファイルボディレコード構造体---------
struct StructNameBody{
	int   nEW;
	int   nNS;
	int	  nInfoCode;
};
typedef StructNameBody struct_NameBody;

class CNameBody  
{
public:
	CNameBody();
	virtual ~CNameBody();
	BOOL Create(CString strFNameIndex,CString strFNameBody);
//	void Clr();
	BOOL Load(char *cpKey,int nKeyLen,char *cpBuf);

	struct_NameBody *m_pNameBody;


//	long m_lBodyMaxCnt;

private:
	CNameIndex m_FileIndex;
	BOOL	m_bFileBodyOpen;
	CFile	m_fileBody;
	int		m_nType;

};

#endif // !defined(AFX_NAMEBODY_H__B031BA98_8E07_4C89_93F0_FBA7745E8E9D__INCLUDED_)
