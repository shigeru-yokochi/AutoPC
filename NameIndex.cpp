// NameIndex.cpp: implementation of the CNameIndex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "NameIndex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*****************************************************************************
*	�R���X�g���N�^
*****************************************************************************/
CNameIndex::CNameIndex()
{
	m_nIndexMaxCnt  = 0;
	m_pIndex		= NULL;
}
/*****************************************************************************
*	�f�X�g���N�^
*****************************************************************************/
CNameIndex::~CNameIndex()
{
	m_file.Close();
	if(m_pIndex != NULL)delete [] m_pIndex;

}
/***********************************************************************************
*	�쐬
*	�w��C���f�b�N�X�t�@�C�����\���̓��ɑS�ēǂݍ���
***********************************************************************************/
BOOL CNameIndex::Create(CString strFName)
{
	if(m_pIndex != NULL)return FALSE;

	if(m_file.Open(strFName, CFile::modeRead) == FALSE)return FALSE;
	int nLen = m_file.GetLength();
	m_nIndexMaxCnt =  nLen / sizeof(struct_Index);

	m_pIndex  = new struct_Index[1];
//	file.Read(&m_pIndex[0],nLen);
//	if(file.Read(&m_pIndex[0],m_nIndexMaxCnt*sizeof(struct_Index)) != m_nIndexMaxCnt*sizeof(struct_Index)){
//		file.Close();
//		AfxMessageBox(L"CNameIndex::Create()err");
//		return FALSE;
//	}
//	file.Close();
	return TRUE;
}
/***********************************************************************************
*	�w��R�[�h�̃C���f�b�N�X�ʒu�l��
*	return:�w��L�[�̐擪(-1�͊Y���Ȃ�)
*	*npKeyCnt:�w��L�[�̐�(�߂�)
***********************************************************************************/
int CNameIndex::GetIndexPos(char* cpBuf,int nLen,int *npKeyCnt)
{

	int i,nCmp;
	DWORD dwSearchAreaTop		= 0;
	DWORD dwSearchAreaBottom	= m_nIndexMaxCnt;
	DWORD dwPos;
	BOOL bFlg=FALSE;
//	char tmp[100];

	for(i=1;i<m_nIndexMaxCnt;i++){
//	for(i=1;i<10;i++){
		dwPos = dwSearchAreaBottom - ((dwSearchAreaBottom - dwSearchAreaTop) /2);
		m_file.Seek(dwPos*sizeof(struct_Index),CFile::begin);
		m_file.Read(&m_pIndex[0],sizeof(struct_Index));

		nCmp = memcmp(m_pIndex[0].cpName,cpBuf,nLen);
//		memcpy(tmp,m_pIndex[0].cpName,nLen);tmp[nLen]=0;
//		HlpTRACE(tmp);
//		memcpy(tmp,cpBuf,nLen);tmp[nLen]=0;
//		HlpTRACE(tmp);







		if(nCmp == 0){bFlg=TRUE;break;}
		if(nCmp <  0)dwSearchAreaTop	= dwPos;
		else         dwSearchAreaBottom	= dwPos;
	}

	if(bFlg == FALSE)return -1;


	DWORD dwTopPos = dwPos;				//�擪�ʒu�l��
	for(;;){
		if(dwTopPos == 0)break;
		dwTopPos--;
		m_file.Seek(dwTopPos*sizeof(struct_Index),CFile::begin);
		m_file.Read(&m_pIndex[0],sizeof(struct_Index));
		if(memcmp(&m_pIndex[0],cpBuf,nLen) != 0){
			dwTopPos++;
			break;
		}
	}

	dwPos=0;
	for(i=0;;i++){
		m_file.Seek((dwTopPos+i)*sizeof(struct_Index),CFile::begin);
		m_file.Read(&m_pIndex[0],sizeof(struct_Index));
		if(memcmp(&m_pIndex[0],cpBuf,nLen) != 0)break;
		dwPos++;
		if(dwTopPos+i == (DWORD)m_nIndexMaxCnt)break;
	}

//CString str;
//str.Format(L"%d",dwTopPos);
//HlpTRACE(str);
	*npKeyCnt = dwPos;			//�w��L�[�̐�
//	memcpy(&cpKey16byte[8],&m_pIndex[dwTopPos].NodeID,8);	//NodeID�L�[�i�[
	return (int)dwTopPos;		//�w��L�[�̐擪


}
/***********************************************************************************
*	�w��R�[�h�̃C���f�b�N�X�ʒu�l��
***********************************************************************************/
int CNameIndex::GetBodyPos(int nPos)
{
	m_file.Seek(nPos*sizeof(struct_Index),CFile::begin);
	m_file.Read(&m_pIndex[0],sizeof(struct_Index));
	return m_pIndex[0].nPos;
}
/***********************************************************************************
*	�w��R�[�h�̖��̊l��
***********************************************************************************/
void CNameIndex::GetBodyName(int nPos,char *cpName)
{
	m_file.Seek(nPos*sizeof(struct_Index),CFile::begin);
	m_file.Read(&m_pIndex[0],sizeof(struct_Index));

	memcpy(cpName,m_pIndex[0].cpName,28);

}
