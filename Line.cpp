// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//***********************************************************************************
//*	コンストラクタ
//***********************************************************************************
CLine::CLine(CString strDataPath)
{
	fb3.Create(FB_LINE,strDataPath+FILE_IDX_LINE3,strDataPath+FILE_DAT_LINE3);
	fb6.Create(FB_LINE,strDataPath+FILE_IDX_LINE6,strDataPath+FILE_DAT_LINE6);
	fb9.Create(FB_LINE,strDataPath+FILE_IDX_LINE9,strDataPath+FILE_DAT_LINE9);

}
//***********************************************************************************
//*	デストラクタ
//***********************************************************************************
CLine::~CLine()
{
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
void CLine::Clr()
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
void CLine::SetMemRec9(DWORD *dwpCode,int nMapLevel)
{
	m_nMapLevel = nMapLevel;
	Clr();

	switch(m_nMapLevel){
		case 3:
			m_pStructLineBody	= fb3.m_pLineBody;
			fb3.SetMemRec9(dwpCode);
			break;
		case 6:
			m_pStructLineBody	= fb6.m_pLineBody;
			fb6.SetMemRec9(dwpCode);
			break;
		case 9:
			m_pStructLineBody	= fb9.m_pLineBody;
			fb9.SetMemRec9(dwpCode);
			break;
	}

}
/***********************************************************************************
*	ボディ数獲得
***********************************************************************************/
long CLine::GetBodyMaxCnt()
{
	switch(m_nMapLevel){
		case 3:	return fb3.m_lBodyMaxCnt;
		case 6:	return fb6.m_lBodyMaxCnt;
		case 9:	return fb9.m_lBodyMaxCnt;
	}
	return 0;
}
