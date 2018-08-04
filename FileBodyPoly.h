// FileBodyPoly.h: interface for the CFileBodyPoly class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEBODYPOLY_H__D8C55878_0CA8_48FE_BBB8_20A5B88282A0__INCLUDED_)
#define AFX_FILEBODYPOLY_H__D8C55878_0CA8_48FE_BBB8_20A5B88282A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "FileIndex.h"

//--------------POLYランクソート用構造体---------
struct StructPolyRank{
	WORD wRank;
	int nPos;
};
typedef StructPolyRank struct_PolyRank;

//--------------POLYファイルボディレコード構造体---------
struct StructPolyBody{
		char  cName[21];
//		WORD  wHight;
//		WORD  wBS;
		int  wHight;
		int  wBS;
		int   nBColor;
		int   nPColor;
		int   nWidht;
		int   nCount;
		POINT *pPoint;
};
typedef StructPolyBody struct_PolyBody;


class CFileBodyPoly  
{
public:
	CFileBodyPoly();
	virtual ~CFileBodyPoly();
	BOOL Create(CString strFNameIndex,CString strFNameRank,CString strFNameBody);
	void Clr();
	void SetMemRec9(DWORD *dwpCode);



	struct_PolyRank *m_pPolyRank;
	struct_PolyBody *m_pPolyBody;

	POINT			m_PolyBodyPoint[BODY_POLY_MAX][BODY_POLY_POINT_MAX];

	long m_lBodyMaxCnt;

private:
	CFileIndex m_FileIndex;
	BOOL	m_bFileRankOpen;
	BOOL	m_bFileBodyOpen;

	CFile	m_fileRank;
	CFile	m_fileBody;


};

#endif // !defined(AFX_FILEBODYPOLY_H__D8C55878_0CA8_48FE_BBB8_20A5B88282A0__INCLUDED_)
