// FileBody.cpp: implementation of the CFileBody class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "FileBody.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CFileBody::CFileBody()
{
	m_bFileBodyOpen	= FALSE;
	m_nBodyFullLength = 0;
	m_pRoadBody		= NULL;
	m_pIconBody		= NULL;
	m_pTextBody		= NULL;
	m_pLineBody		= NULL;
	Clr();
}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CFileBody::~CFileBody()
{
	if(m_bFileBodyOpen == TRUE)	m_fileBody.Close();
	if(m_pRoadBody != NULL)delete [] m_pRoadBody;
	if(m_pIconBody != NULL)delete [] m_pIconBody;
	if(m_pTextBody != NULL)delete [] m_pTextBody;
	if(m_pLineBody != NULL)delete [] m_pLineBody;
}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
*	nType :FB_ROAD FB_ICON FB_TEXT FB_LINE
***********************************************************************************/
BOOL CFileBody::Create(int nType,CString strFNameIndex,CString strFNameBody,int *npMaxCnt/*=NULL*/)
{
	if(m_bFileBodyOpen	!= FALSE)return FALSE;


	m_strFNameBody = strFNameBody;
	m_nType		= nType;

	if(m_FileIndex.Create(strFNameIndex) == FALSE)return FALSE;	//インデックス読み込み


	switch(m_nType){
		case FB_ROAD:m_pRoadBody = new struct_RoadBody[BODY_ROAD_MAX+1];break;
		case FB_ICON:m_pIconBody = new struct_IconBody[BODY_ICON_MAX+1];break;
		case FB_TEXT:m_pTextBody = new struct_TextBody[BODY_TEXT_MAX+1];break;
		case FB_LINE:m_pLineBody = new struct_LineBody[BODY_LINE_MAX+1];break;

		default:return FALSE;
	}
	
	m_bFileBodyOpen = FALSE;
	if(m_fileBody.Open(m_strFNameBody, CFile::modeRead |CFile::shareExclusive) != FALSE){
		m_nBodyFullLength = m_fileBody.GetLength();
		m_bFileBodyOpen = TRUE;
//m_fileBody.Close();
	}
	else{
		TRACE(L"CFileBody::Create()err");
	}

	if(npMaxCnt != NULL){
		*npMaxCnt = m_FileIndex.m_nIndexMaxCnt;
	}
	return TRUE;
}

/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CFileBody::SetMemRec9(DWORD *dwpCode)
{
	int i,nPos,nSeekPos=0,nBodyCnt,nTypeSize,nBodyMaxCnt;
	m_lBodyMaxCnt=0;
	CString str;

	switch(m_nType){
		case FB_ROAD:
			nTypeSize = sizeof(struct_RoadBody);
			nBodyMaxCnt = BODY_ROAD_MAX;
			str = L"road";
			break;
		case FB_ICON:
			nTypeSize = sizeof(struct_IconBody);
			nBodyMaxCnt = BODY_ICON_MAX;
			str = L"icon";
			break;
		case FB_TEXT:
			nTypeSize = sizeof(struct_TextBody);
			nBodyMaxCnt = BODY_TEXT_MAX;
			str = L"text";
			break;
		case FB_LINE:
			nTypeSize = sizeof(struct_LineBody);
			nBodyMaxCnt = BODY_LINE_MAX;
			str = L"line";
			break;
		default:return;
	}

//	int nCurrentPos,nSeekVal;


	for(i=0;i<9;i++){
//	for(i=0;i<25;i++){
		nPos = m_FileIndex.GetIndexPos(dwpCode[i]);
		if(nPos == -1)continue;

//		nCurrentPos = m_fileBody.GetPosition();
//		nSeekVal = m_FileIndex.m_pIndex[nPos].nPos - nCurrentPos;
//		if(nSeekVal+nCurrentPos < 0 ||
//			nSeekVal > m_nBodyFullLength - m_FileIndex.m_pIndex[nPos].nSize){
//			AfxMessageBox(L"CFileBody::SetMemRec9()err");
//		}
//		m_fileBody.Seek(nSeekVal,CFile::current);


		m_fileBody.Seek(m_FileIndex.m_pIndex[nPos].nPos,CFile::begin);


		nBodyCnt = m_FileIndex.m_pIndex[nPos].nSize/nTypeSize;
		if(m_lBodyMaxCnt + nBodyCnt >= nBodyMaxCnt){
			TRACE(L"****** Over ******[CFileBody]\n");
			break;
		}


		switch(m_nType){
			case FB_ROAD:m_fileBody.Read(&m_pRoadBody[m_lBodyMaxCnt],m_FileIndex.m_pIndex[nPos].nSize);break;
			case FB_ICON:m_fileBody.Read(&m_pIconBody[m_lBodyMaxCnt],m_FileIndex.m_pIndex[nPos].nSize);break;
			case FB_TEXT:m_fileBody.Read(&m_pTextBody[m_lBodyMaxCnt],m_FileIndex.m_pIndex[nPos].nSize);break;
			case FB_LINE:m_fileBody.Read(&m_pLineBody[m_lBodyMaxCnt],m_FileIndex.m_pIndex[nPos].nSize);break;
		}

		m_lBodyMaxCnt += nBodyCnt;
	}

	TRACE(L"%s:%d[CFileBody]\n",str,m_lBodyMaxCnt);
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
void CFileBody::Clr()
{
	m_lBodyMaxCnt = 0;		//TEXT数
}
