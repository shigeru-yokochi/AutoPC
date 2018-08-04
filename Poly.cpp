// Poly.cpp: implementation of the CPoly class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Poly.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CPoly::CPoly(CString strDataPath)
{
	fb3.Create(strDataPath+FILE_IDX_POLY3,strDataPath+FILE_RNK_POLY3,strDataPath+FILE_DAT_POLY3);
	fb6.Create(strDataPath+FILE_IDX_POLY6,strDataPath+FILE_RNK_POLY6,strDataPath+FILE_DAT_POLY6);
	fb9.Create(strDataPath+FILE_IDX_POLY9,strDataPath+FILE_RNK_POLY9,strDataPath+FILE_DAT_POLY9);

}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CPoly::~CPoly()
{
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
void CPoly::Clr()
{
	switch(m_nMapLevel){
		case 3:	fb3.Clr();break;
		case 6:	fb6.Clr();break;
		case 9:	fb9.Clr();break;
	}
}
/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CPoly::SetMemRec9(DWORD *dwpCode,int nMapLevel)
{
	m_nMapLevel  = nMapLevel;
	Clr();

	switch(m_nMapLevel){
		case 3:
			m_pStructPolyBody	= fb3.m_pPolyBody;
			fb3.SetMemRec9(dwpCode);
			break;
		case 6:
			m_pStructPolyBody	= fb6.m_pPolyBody;
			fb6.SetMemRec9(dwpCode);
			break;
		case 9:
			m_pStructPolyBody	= fb9.m_pPolyBody;
			fb9.SetMemRec9(dwpCode);
			break;
	}

}
/***********************************************************************************
*	ボディ数獲得
***********************************************************************************/
long CPoly::GetBodyMaxCnt()
{
	switch(m_nMapLevel){
		case 3:	return fb3.m_lBodyMaxCnt;
		case 6:	return fb6.m_lBodyMaxCnt;
		case 9:	return fb9.m_lBodyMaxCnt;
	}
	return 0; 
}

