// FileBodyPoly.cpp: implementation of the CFileBodyPoly class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "FileBodyPoly.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CFileBodyPoly::CFileBodyPoly()
{
	m_bFileRankOpen	= FALSE;
	m_bFileBodyOpen	= FALSE;
	m_pPolyBody		= NULL;
	m_pPolyRank		= NULL;

//	int i;
//	for(i=0;i<BODY_POLY_MAX;i++){
//		m_pPolyBodyPoint[i] = NULL;
//	}

	m_lBodyMaxCnt = 0;		//BODY数

}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CFileBodyPoly::~CFileBodyPoly()
{
	Clr();

	if(m_bFileRankOpen == TRUE)	m_fileRank.Close();
	if(m_bFileBodyOpen == TRUE)	m_fileBody.Close();
	if(m_pPolyBody != NULL)delete [] m_pPolyBody;
	if(m_pPolyRank != NULL)delete [] m_pPolyRank;
}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
***********************************************************************************/
BOOL CFileBodyPoly::Create(CString strFNameIndex,CString strFNameRank,CString strFNameBody)
{
	if(m_bFileRankOpen	!= FALSE)return FALSE;
	if(m_bFileBodyOpen	!= FALSE)return FALSE;

	if(m_FileIndex.Create(strFNameIndex) == FALSE)return FALSE;	//インデックス読み込み

	
//-----------RANK---------------------------------------------------
	m_pPolyRank = new struct_PolyRank[BODY_POLY_MAX+1];		//BODY_POLY_MAXと同数
	m_bFileRankOpen = FALSE;
	if(m_fileRank.Open(strFNameRank, CFile::modeRead |CFile::shareExclusive) != FALSE){
		m_bFileRankOpen = TRUE;
	}

//-----------BODY---------------------------------------------------
	m_pPolyBody = new struct_PolyBody[BODY_POLY_MAX];
	m_bFileBodyOpen = FALSE;
	if(m_fileBody.Open(strFNameBody, CFile::modeRead |CFile::shareExclusive) != FALSE){
		m_bFileBodyOpen = TRUE;
	}


	return TRUE;
}

int _cdecl compare2(const void *elem1,const void *elem2);
//***********************************************************************************
//*	ソート
//***********************************************************************************
int _cdecl compare2(const void *elem1,const void *elem2)
{
	return memcmp(elem1,elem2,2);	//ランクをソート

}
/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CFileBodyPoly::SetMemRec9(DWORD *dwpCode)
{
	int i,nPos,nSeekPos=0,nBodyCnt,nTypeSize,nBodyMaxCnt;
	m_lBodyMaxCnt=0;
	CString str;

	//---------------RANK構造体設定---------------------------------
	nTypeSize = sizeof(struct_PolyRank);
	nBodyMaxCnt = BODY_POLY_MAX;

	for(i=0;i<9;i++){
//	for(i=0;i<25;i++){
		nPos = m_FileIndex.GetIndexPos(dwpCode[i]);
		if(nPos == -1)continue;

//		m_fileRank.Seek(m_FileIndex.m_pIndex[nPos].nPos-m_fileRank.GetPosition(),
//			CFile::current);

		m_fileRank.Seek(m_FileIndex.m_pIndex[nPos].nPos,CFile::begin);


		nBodyCnt = m_FileIndex.m_pIndex[nPos].nSize/nTypeSize;
		if(m_lBodyMaxCnt + nBodyCnt >= nBodyMaxCnt){
			TRACE(L"****** Over ******[CFileBodyPoly]\n");
			break;
		}

		m_fileRank.Read(&m_pPolyRank[m_lBodyMaxCnt],m_FileIndex.m_pIndex[nPos].nSize);

		m_lBodyMaxCnt += nBodyCnt;
	}

	//----------------sort-----------------------
	qsort((void*)(m_pPolyRank),m_lBodyMaxCnt,nTypeSize,compare2);

//m_lBodyMaxCnt=2;
	//---------------BODY構造体設定---------------------------------
	for(i=0;i<m_lBodyMaxCnt;i++){
//		m_fileBody.Seek(m_pPolyRank[i].nPos-m_fileBody.GetPosition(),
//			CFile::current);

		m_fileBody.Seek(m_pPolyRank[i].nPos,CFile::begin);

		m_fileBody.Read(&m_pPolyBody[i],sizeof(struct_PolyBody) -4);	//-4はcountまで
		
//str.Format(L"%d %d %d %d",
//		m_pPolyBody[i].cName,
//		m_pPolyBody[i].wHight,
//		m_pPolyBody[i].wBS,
//		m_pPolyBody[i].nBColor,
//		m_pPolyBody[i].nPColor,
//		m_pPolyBody[i].nWidht,
//		m_pPolyBody[i].nCount);
//HlpTRACE(str);


//		m_pPolyBodyPoint[i] = new POINT[m_pPolyBody[i].nCount];
//		m_fileBody.Read(&m_pPolyBodyPoint[i],sizeof(POINT)*m_pPolyBody[i].nCount);
//		m_pPolyBody[i].pPoint = m_pPolyBodyPoint[i];
//		m_pPolyBodyPoint[i] = new POINT[m_pPolyBody[i].nCount];

		if(m_pPolyBody[i].nCount > BODY_POLY_POINT_MAX){
			TRACE(L"****** Over Point ******[CFileBodyPoly]\n");
			m_pPolyBody[i].nCount = BODY_POLY_POINT_MAX;
		}
		m_fileBody.Read(&m_PolyBodyPoint[i][0],sizeof(POINT)*m_pPolyBody[i].nCount);
		m_pPolyBody[i].pPoint = &m_PolyBodyPoint[i][0];
	}

	TRACE(L"poly:%d[CFileBodyPoly]\n",m_lBodyMaxCnt);
}



//***********************************************************************************
//*	クリア
//***********************************************************************************
void CFileBodyPoly::Clr()
{
//	int i;
//	for(i=0;i<BODY_POLY_MAX;i++){
//		if(m_pPolyBodyPoint[i] == NULL)break;
//		delete [] m_pPolyBodyPoint[i];
//		m_pPolyBodyPoint[i] = NULL;
//	}


	m_lBodyMaxCnt = 0;		//BODY数
}
