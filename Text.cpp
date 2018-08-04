// Text.cpp: implementation of the CText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CText::CText(CString strDataPath)
{

	int nVal,nMaxCnt=0;

	fb1.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT1,strDataPath+FILE_DAT_TEXT1,&nVal);nMaxCnt+=nVal;
	fb2.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT2,strDataPath+FILE_DAT_TEXT2,&nVal);nMaxCnt+=nVal;
	fb3.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT3,strDataPath+FILE_DAT_TEXT3,&nVal);nMaxCnt+=nVal;
	fb4.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT4,strDataPath+FILE_DAT_TEXT4,&nVal);nMaxCnt+=nVal;
	fb5.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT5,strDataPath+FILE_DAT_TEXT5,&nVal);nMaxCnt+=nVal;
	fb6.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT6,strDataPath+FILE_DAT_TEXT6,&nVal);nMaxCnt+=nVal;
	fb7.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT7,strDataPath+FILE_DAT_TEXT7,&nVal);nMaxCnt+=nVal;
	fb8.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT8,strDataPath+FILE_DAT_TEXT8,&nVal);nMaxCnt+=nVal;
	fb9.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT9,strDataPath+FILE_DAT_TEXT9,&nVal);nMaxCnt+=nVal;
	fb10.Create(FB_TEXT,strDataPath+FILE_IDX_TEXT10,strDataPath+FILE_DAT_TEXT10,&nVal);nMaxCnt+=nVal;

}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CText::~CText()
{
}
/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CText::SetMemRec9(DWORD *dwpCode,int nMapLevel)
{
	m_nMapLevel = nMapLevel;

	Clr();
	switch(m_nMapLevel){
		case 1:
			m_pStructTextBody	= fb1.m_pTextBody;
			fb1.SetMemRec9(dwpCode);
			break;
		case 2:
			m_pStructTextBody	= fb2.m_pTextBody;
			fb2.SetMemRec9(dwpCode);
			break;
		case 3:
			m_pStructTextBody	= fb3.m_pTextBody;
			fb3.SetMemRec9(dwpCode);
			break;
		case 4:
			m_pStructTextBody	= fb4.m_pTextBody;
			fb4.SetMemRec9(dwpCode);
			break;
		case 5:
			m_pStructTextBody	= fb5.m_pTextBody;
			fb5.SetMemRec9(dwpCode);
			break;
		case 6:
			m_pStructTextBody	= fb6.m_pTextBody;
			fb6.SetMemRec9(dwpCode);
			break;
		case 7:
			m_pStructTextBody	= fb7.m_pTextBody;
			fb7.SetMemRec9(dwpCode);
			break;
		case 8:
			m_pStructTextBody	= fb8.m_pTextBody;
			fb8.SetMemRec9(dwpCode);
			break;
		case 9:
			m_pStructTextBody	= fb9.m_pTextBody;
			fb9.SetMemRec9(dwpCode);
			break;
		case 10:
			m_pStructTextBody	= fb10.m_pTextBody;
			fb10.SetMemRec9(dwpCode);
			break;

	}

}
/***********************************************************************************
*	ボディ数獲得
***********************************************************************************/
long CText::GetBodyMaxCnt()
{
	switch(m_nMapLevel){
		case 1:	return fb1.m_lBodyMaxCnt;
		case 2:	return fb2.m_lBodyMaxCnt;
		case 3:	return fb3.m_lBodyMaxCnt;
		case 4:	return fb4.m_lBodyMaxCnt;
		case 5:	return fb4.m_lBodyMaxCnt;
		case 6:	return fb6.m_lBodyMaxCnt;
		case 7:	return fb7.m_lBodyMaxCnt;
		case 8:	return fb8.m_lBodyMaxCnt;
		case 9:	return fb9.m_lBodyMaxCnt;
		case 10:return fb10.m_lBodyMaxCnt;

	}
	return 0;
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
void CText::Clr()
{
	switch(m_nMapLevel){
		case 1:	fb1.Clr();break;
		case 2:	fb2.Clr();break;
		case 3:	fb3.Clr();break;
		case 4:	fb4.Clr();break;
		case 5:	fb5.Clr();break;
		case 6:	fb6.Clr();break;
		case 7:	fb7.Clr();break;
		case 8:	fb8.Clr();break;
		case 9:	fb9.Clr();break;
		case 10:fb10.Clr();break;

	}
}
