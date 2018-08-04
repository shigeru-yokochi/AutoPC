// DriveLog.cpp: implementation of the CDriveLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "DriveLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*****************************************************************************
*	�R���X�g���N�^
*****************************************************************************/
CDriveLog::CDriveLog()
{
	m_nSetPos=0;
	m_strDataPath = "";
//	nStepWaitCnt = 0;

	m_pEN = new StructEN[LOG_MAX];
}
/*****************************************************************************
*	�f�X�g���N�^
*****************************************************************************/
CDriveLog::~CDriveLog()
{
//	CFileStatus rStatus;
//	if(CFile::GetStatus(m_strDataPath+FILE_DRAIVE_LOG, rStatus) == TRUE){
//		if(m_nSetPos > 0)FileWritePoint();
//	}
	HlpFileWrite();

	delete [] m_pEN;
}
/*****************************************************************************
*	�f�[�^�p�X�ݒ�
*****************************************************************************/
void CDriveLog::SetDataPath(CString strDataPath)
{
	m_strDataPath = strDataPath;
	HlpFileRead();

}
/*****************************************************************************
*	�ر
*****************************************************************************/
void CDriveLog::Clr()
{
	m_nSetPos=0;

	CFileStatus rStatus;
	if(CFile::GetStatus(m_strDataPath+FILE_DRAIVE_LOG, rStatus) == FALSE)return;;
	CFile::Remove(m_strDataPath+FILE_DRAIVE_LOG);		//log clr
}
/*****************************************************************************
*	�O�Փ_�ݒ�
*****************************************************************************/
void CDriveLog::SetPoint(DWORD dwEW,DWORD dwNS)
{
//return;
//	if(nStepWaitCnt != STEP_WAIT_CNT){
//		nStepWaitCnt++;
//		return;
//	}

	if(m_nSetPos >= LOG_MAX){
		m_nSetPos = LOG_MAX/2;
		memcpy(&m_pEN[0],&m_pEN[m_nSetPos],	sizeof(struct_EN)*m_nSetPos);		//�㔼������O���Ɉړ�
	}

	m_pEN[m_nSetPos].dwEW = dwEW;
	m_pEN[m_nSetPos].dwNS = dwNS;

	m_nSetPos++;
//	nStepWaitCnt=0;


}

/*****************************************************************************
*	�ݒ萔�l��
*****************************************************************************/
int CDriveLog::GetMaxCnt()
{
	return m_nSetPos;
}
/***********************************************************************************
*	�t�@�C���ǂݍ���
*********************************************************************************/
void CDriveLog::HlpFileRead()
{
	m_nSetPos=0;
	CFile file;
	if(file.Open(m_strDataPath+FILE_DRAIVE_LOG, CFile::modeRead |CFile::shareExclusive) == FALSE)return;
	
	m_nSetPos = file.GetLength()/sizeof(StructEN);
	if(m_nSetPos >= LOG_MAX){
		m_nSetPos=LOG_MAX-1;
	}

	UINT nLen = m_nSetPos*sizeof(StructEN);
	if(file.Read(m_pEN,nLen) != nLen){
		TRACE(L"read err[CDriveLog]\n");
	}

	file.Close();
}
/***********************************************************************************
*	�t�@�C����������
*********************************************************************************/
void CDriveLog::HlpFileWrite()
{
//#ifdef DATA_CDROM
//	m_nSetPos=0;
//	return;
//#endif

	CFile file;

	if(file.Open(m_strDataPath+FILE_DRAIVE_LOG, CFile::modeCreate |CFile::modeNoTruncate| CFile::modeWrite) == FALSE)return;

	file.Close();								//�폜���邽�߂Ɉ�U����
	file.Remove(m_strDataPath+FILE_DRAIVE_LOG);	//�폜���Ă��珑������
	if(file.Open(m_strDataPath+FILE_DRAIVE_LOG, CFile::modeCreate |CFile::modeNoTruncate| CFile::modeWrite) == FALSE)return;

	file.Write(m_pEN,sizeof(StructEN)*m_nSetPos);
	file.Close();
	m_nSetPos=0;

}
