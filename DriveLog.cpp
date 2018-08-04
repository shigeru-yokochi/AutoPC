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
*	コンストラクタ
*****************************************************************************/
CDriveLog::CDriveLog()
{
	m_nSetPos=0;
	m_strDataPath = "";
//	nStepWaitCnt = 0;

	m_pEN = new StructEN[LOG_MAX];
}
/*****************************************************************************
*	デストラクタ
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
*	データパス設定
*****************************************************************************/
void CDriveLog::SetDataPath(CString strDataPath)
{
	m_strDataPath = strDataPath;
	HlpFileRead();

}
/*****************************************************************************
*	ｸﾘｱ
*****************************************************************************/
void CDriveLog::Clr()
{
	m_nSetPos=0;

	CFileStatus rStatus;
	if(CFile::GetStatus(m_strDataPath+FILE_DRAIVE_LOG, rStatus) == FALSE)return;;
	CFile::Remove(m_strDataPath+FILE_DRAIVE_LOG);		//log clr
}
/*****************************************************************************
*	軌跡点設定
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
		memcpy(&m_pEN[0],&m_pEN[m_nSetPos],	sizeof(struct_EN)*m_nSetPos);		//後半半分を前半に移動
	}

	m_pEN[m_nSetPos].dwEW = dwEW;
	m_pEN[m_nSetPos].dwNS = dwNS;

	m_nSetPos++;
//	nStepWaitCnt=0;


}

/*****************************************************************************
*	設定数獲得
*****************************************************************************/
int CDriveLog::GetMaxCnt()
{
	return m_nSetPos;
}
/***********************************************************************************
*	ファイル読み込み
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
*	ファイル書き込み
*********************************************************************************/
void CDriveLog::HlpFileWrite()
{
//#ifdef DATA_CDROM
//	m_nSetPos=0;
//	return;
//#endif

	CFile file;

	if(file.Open(m_strDataPath+FILE_DRAIVE_LOG, CFile::modeCreate |CFile::modeNoTruncate| CFile::modeWrite) == FALSE)return;

	file.Close();								//削除するために一旦閉じる
	file.Remove(m_strDataPath+FILE_DRAIVE_LOG);	//削除してから書き込む
	if(file.Open(m_strDataPath+FILE_DRAIVE_LOG, CFile::modeCreate |CFile::modeNoTruncate| CFile::modeWrite) == FALSE)return;

	file.Write(m_pEN,sizeof(StructEN)*m_nSetPos);
	file.Close();
	m_nSetPos=0;

}
