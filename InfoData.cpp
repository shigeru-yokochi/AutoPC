// InfoData.cpp: implementation of the CInfoData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "InfoData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CInfoData::CInfoData()
{
	m_nIndexMaxCnt  = 0;
	m_pIndex		= NULL;

}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CInfoData::~CInfoData()
{
	m_file.Close();
	if(m_pIndex != NULL)delete [] m_pIndex;

}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
***********************************************************************************/
BOOL CInfoData::Create(CString strFName)
{
	if(m_pIndex != NULL)return FALSE;

	if(m_file.Open(strFName, CFile::modeRead) == FALSE)return FALSE;
	int nLen = m_file.GetLength();
	m_nIndexMaxCnt =  nLen / sizeof(StructInfoIndex);

	m_pIndex  = new StructInfoIndex[1];
	return TRUE;
}
/***********************************************************************************
*	指定コードのインデックス位置獲得
***********************************************************************************/
int CInfoData::GetIndexPos(int nCode)
{
	int i,nSeekPos;
	DWORD dwSearchAreaTop		= 0;
	DWORD dwSearchAreaBottom	= m_nIndexMaxCnt;
	DWORD dwPos;
	DWORD dwFilePos		= 0;

	for(i=1;i<m_nIndexMaxCnt;i++){
		dwPos = dwSearchAreaBottom - ((dwSearchAreaBottom - dwSearchAreaTop) /2);
		nSeekPos = dwPos*sizeof(StructInfoIndex);

		m_file.Seek(nSeekPos,CFile::begin);
//		m_file.Seek(nSeekPos-dwFilePos,CFile::current);	//こっちの方が遅い
		m_file.Read(&m_pIndex[0],sizeof(StructInfoIndex));
//		dwFilePos = m_file.GetPosition();

		if(m_pIndex[0].nInfoCode == nCode)	return (int)dwPos;
		if(m_pIndex[0].nInfoCode <  nCode)dwSearchAreaTop		= dwPos;
		else                              dwSearchAreaBottom	= dwPos;
	}

	return -1;

}
/***********************************************************************************
*	ボディ獲得
***********************************************************************************/
CString CInfoData::GetBodyString(CString strFName)
{

	CFile file;
	if(file.Open(strFName, CFile::modeRead) == FALSE)return L"No data.";

	char *zpBuf;
	zpBuf =  new char[m_pIndex[0].nBodySize+1];

	file.Seek(m_pIndex[0].nBodyPos,CFile::begin);
	file.Read(zpBuf,m_pIndex[0].nBodySize);
	file.Close();

	zpBuf[m_pIndex[0].nBodySize]=0;
	CString str = zpBuf;
	delete [] zpBuf;
	return str;
}