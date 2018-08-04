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
*	�R���X�g���N�^
*****************************************************************************/
CFileIndex::CFileIndex()
{
	m_nIndexMaxCnt  = 0;
	m_pIndex		= NULL;

}
/*****************************************************************************
*	�f�X�g���N�^
*****************************************************************************/
CFileIndex::~CFileIndex()
{
	if(m_pIndex != NULL)delete [] m_pIndex;

}
/***********************************************************************************
*	�쐬
*	�w��C���f�b�N�X�t�@�C�����\���̓��ɑS�ēǂݍ���
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
*	�w��R�[�h�̃C���f�b�N�X�ʒu�l��
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
