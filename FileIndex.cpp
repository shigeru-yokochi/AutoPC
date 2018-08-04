// FileIndex.cpp: implementation of the CFileIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "FileIndex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CFileIndex::CFileIndex()
{
	m_nIndexMaxCnt  = 0;
	m_pIndex		= NULL;

}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CFileIndex::~CFileIndex()
{
	if(m_pIndex != NULL)delete [] m_pIndex;

}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
***********************************************************************************/
BOOL CFileIndex::Create(CString strFName)
{
	if(m_pIndex != NULL)return FALSE;

	CFile file;
	if(file.Open(strFName, CFile::modeRead |CFile::shareExclusive) == FALSE)return FALSE;
	int nLen = file.GetLength();

	m_nIndexMaxCnt =  nLen / sizeof(struct_Index);
	m_pIndex  = new struct_Index[m_nIndexMaxCnt];
	if(file.Read(&m_pIndex[0],nLen) != (DWORD)nLen){
		file.Close();
		TRACE(L"CFileIndex::Create()err");
		return FALSE;
	}

	file.Close();
	return TRUE;
}
/***********************************************************************************
*	指定コードのインデックス位置獲得
***********************************************************************************/
int CFileIndex::GetIndexPos(int nCode)
{
	int i;
	DWORD dwSearchAreaTop		= 0;
	DWORD dwSearchAreaBottom	= m_nIndexMaxCnt;
	DWORD dwPos;

	for(i=1;i<m_nIndexMaxCnt;i++){
		dwPos = dwSearchAreaBottom - ((dwSearchAreaBottom - dwSearchAreaTop) /2);
		if(m_pIndex[dwPos].nCode == nCode)	return (int)dwPos;
		if(m_pIndex[dwPos].nCode <  nCode)dwSearchAreaTop		= dwPos;
		else                              dwSearchAreaBottom	= dwPos;
	}

	return -1;

}
