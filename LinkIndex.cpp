// LinkIndex.cpp: implementation of the CLinkIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "LinkIndex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CLinkIndex::CLinkIndex()
{
	m_nIndexMaxCnt  = 0;
	m_pIndex		= NULL;
	m_pBody			= NULL;
	m_pFileBody		= NULL;
}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CLinkIndex::~CLinkIndex()
{
	if(m_pIndex != NULL)delete [] m_pIndex;
	if(m_pBody != NULL)delete [] m_pBody;

	if(m_pFileBody	!= NULL){
		m_pFileBody->Close();
		delete m_pFileBody;
	}

}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
*	Body用のファイルもオープンする
***********************************************************************************/
BOOL CLinkIndex::Create(CString strPath)
{
	if(m_pIndex != NULL)return FALSE;

	CFile file;
	if(file.Open(strPath + DEF_LINK_IDX_FILE, CFile::modeRead |CFile::shareExclusive) == FALSE)return FALSE;
	int nLen = file.GetLength();

	m_nIndexMaxCnt =  nLen / sizeof(struct_Index);
	m_pIndex  = new struct_Index[m_nIndexMaxCnt];
	if(file.Read(&m_pIndex[0],nLen) != (DWORD)nLen){
		file.Close();
		TRACE(L"CLinkIndex::Create()err");
		return FALSE;
	}

	file.Close();

	m_pFileBody = new CFile;
	if(m_pFileBody->Open(strPath + DEF_LINK_DAT_FILE, CFile::modeRead |CFile::shareExclusive) == FALSE)return FALSE;	//Body


	return TRUE;
}
/***********************************************************************************
*	指定コードのインデックス位置獲得
*	return -1はNG
***********************************************************************************/
//int CLinkIndex::GetIndexPos(int nCode)
int CLinkIndex::GetIndexPos(int nEW1,int nNS1,int nEW2,int nNS2,int *npBlkCnt)

{
	*npBlkCnt=0;

	int i,nCmp;
	DWORD dwSearchAreaTop		= 0;
	DWORD dwSearchAreaBottom	= m_nIndexMaxCnt;
	DWORD dwPos;
	char tmp1[100],tmp2[100];

	sprintf(tmp1,"%u%u%u%u",nEW1,nNS1,nEW2,nNS2);
	int nLen = strlen(tmp1);
	for(i=1;;i++){
		dwPos = dwSearchAreaBottom - ((dwSearchAreaBottom - dwSearchAreaTop) /2);


		sprintf(tmp2,"%u%u%u%u",m_pIndex[dwPos].nEW1,m_pIndex[dwPos].nNS1,m_pIndex[dwPos].nEW2,m_pIndex[dwPos].nNS2);
		nCmp = memcmp(tmp1,tmp2,nLen);

		if(nCmp == 0)break;
		if(nCmp >  0)dwSearchAreaTop	= dwPos;
		else         dwSearchAreaBottom	= dwPos;
	
		if(i == 100){
			return -1;			//検索をあきらめる（NG）
		}

	}
	
	*npBlkCnt = m_pIndex[dwPos].nBlkCnt;
	return m_pIndex[dwPos].nPos;
}



/***********************************************************************************
*	Body獲得
***********************************************************************************/
BOOL CLinkIndex::GetBody(int nPos,int nBlkCnt)
{
	if(m_pBody != NULL)delete [] m_pBody;

	m_pBody = new struct_Body[nBlkCnt];


//GetPosition 


	m_pFileBody->Seek(nPos,CFile::begin);
	int nLen = sizeof(struct_Body)*nBlkCnt;
	if(m_pFileBody->Read(m_pBody,nLen) != (DWORD)nLen){
		TRACE(L"CLinkIndex::GetBody()err");
		return FALSE;
	}


	return TRUE;



}
