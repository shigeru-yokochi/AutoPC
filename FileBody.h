// FileBody.h: interface for the CFileBody class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEBODY_H__05554B10_7294_421F_8876_C9C53D651161__INCLUDED_)
#define AFX_FILEBODY_H__05554B10_7294_421F_8876_C9C53D651161__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileIndex.h"

#define FB_ROAD	1
#define FB_ICON	2
#define FB_TEXT	3
#define FB_LINE	4




//--------------ROADファイルボディレコード構造体---------
struct StructRoadBody{
	DWORD dwEW1;
	DWORD dwNS1;
	DWORD dwEW2;
	DWORD dwNS2;
	BYTE cWidth;
	BYTE cRank;
};
typedef StructRoadBody struct_RoadBody;
//--------------ICONファイルボディレコード構造体---------
struct StructIconBody{
	int   nEW;
	int   nNS;
	int   nIcon;
	int   nInfoCode;
//	char  cName[51];
	char  cDisp1[21];
	char  cDisp2[21];
	char  cG1G2[5];
};
typedef StructIconBody struct_IconBody;
//--------------TEXTファイルボディレコード構造体---------
struct StructTextBody{
	int   nEW;
	int   nNS;
	int	  nFontColor;
//	int   nFontSize;
	BYTE   nFontSize;
	BYTE  cnItaric;		//0!:斜体
	BYTE  cnBold;		//1!:太字
	char  cFontName[31];
	char  cName[51];
};
typedef StructTextBody struct_TextBody;
//--------------LINEファイルボディレコード構造体---------
struct StructLineBody{
	int   nEW1;
	int   nNS1;
	int   nEW2;
	int   nNS2;
	int	  nColor;
	BYTE  cWidth;
	BYTE  cStyle;
};
typedef StructLineBody struct_LineBody;



class CFileBody  
{
public:
	CFileBody();
	virtual ~CFileBody();
	BOOL Create(int nType,CString strFNameIndex,CString strFNameBody,int *npMaxCnt=NULL);
	void Clr();
	void SetMemRec9(DWORD *dwpCode);

	struct_RoadBody *m_pRoadBody;
	struct_IconBody *m_pIconBody;
	struct_TextBody *m_pTextBody;
	struct_LineBody *m_pLineBody;


	long m_lBodyMaxCnt;
	int	m_nBodyFullLength;
	CString m_strFNameBody;
private:
	CFileIndex m_FileIndex;
	BOOL	m_bFileBodyOpen;
	CFile	m_fileBody;
	int		m_nType;
};

#endif // !defined(AFX_FILEBODY_H__05554B10_7294_421F_8876_C9C53D651161__INCLUDED_)
