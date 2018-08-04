// NameBody.cpp: implementation of the CNameBody class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "NameBody.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*****************************************************************************
*	コンストラクタ
*****************************************************************************/
CNameBody::CNameBody()
{
	m_bFileBodyOpen	= FALSE;
	m_pNameBody		= NULL;
//	Clr();
}
/*****************************************************************************
*	デストラクタ
*****************************************************************************/
CNameBody::~CNameBody()
{
	if(m_bFileBodyOpen == TRUE)	m_fileBody.Close();
	if(m_pNameBody != NULL)delete [] m_pNameBody;
}
/***********************************************************************************
*	作成
*	指定インデックスファイルを構造体内に全て読み込む
***********************************************************************************/
BOOL CNameBody::Create(CString strFNameIndex,CString strFNameBody)
{
	if(m_bFileBodyOpen	!= FALSE)return FALSE;


	if(m_FileIndex.Create(strFNameIndex) == FALSE)return FALSE;	//インデックス読み込み
	m_pNameBody = new struct_NameBody;
	
	m_bFileBodyOpen = FALSE;
	if(m_fileBody.Open(strFNameBody, CFile::modeRead) == FALSE){
		return FALSE;
	}
	m_bFileBodyOpen = TRUE;
	return TRUE;
}

/***********************************************************************************
*	指定キーのボディをファイルよりロード
*	*cpBuf 獲得した内容を格納するﾊﾞﾌｧ  strEW,strNS,strName,strInfoCodeのcsv形式
***********************************************************************************/
BOOL CNameBody::Load(char *cpKey,int nKeyLen,char *cpBuf)
{
	int i,nPos,nSeekPos=0;
	char crlf[3] ={0x0d,0x0a,0};
	char tmp[100];

	int nKeyMaxCnt;
	nPos = m_FileIndex.GetIndexPos(cpKey,nKeyLen,&nKeyMaxCnt);
	if(nPos == -1)return FALSE;
//CString str;
TRACE(L"%d[CNameBody]\n",nKeyMaxCnt);
//HlpTRACE(str);
	if(nKeyMaxCnt >100)nKeyMaxCnt=100;		//最大１００件

//----1件目---------
	m_fileBody.Seek(m_FileIndex.GetBodyPos(nPos),CFile::begin);
	m_fileBody.Read(m_pNameBody,sizeof(struct_NameBody));

	cpBuf[0]=0;
	char cpName[30];
	m_FileIndex.GetBodyName(nPos,cpName);
	sprintf(tmp,"%d,%d,%s,%d,",m_pNameBody->nEW,m_pNameBody->nNS,cpName,m_pNameBody->nInfoCode);
	strcat(tmp,crlf);
	strcat(cpBuf,tmp);

//-----２件目以降
	for(i=1;i<nKeyMaxCnt;i++){		//のこりをread
		m_fileBody.Read(m_pNameBody,sizeof(struct_NameBody));
		m_FileIndex.GetBodyName(nPos+i,cpName);
		sprintf(tmp,"%d,%d,%s,%d,",m_pNameBody->nEW,m_pNameBody->nNS,cpName,m_pNameBody->nInfoCode);
		strcat(tmp,crlf);
		strcat(cpBuf,tmp);
	}

//	*npEW = m_pNameBody->nEW;
//	*npNS = m_pNameBody->nNS;



	return TRUE;
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
//void CNameBody::Clr()
//{
//	m_lBodyMaxCnt = 0;		//TEXT数
//}
