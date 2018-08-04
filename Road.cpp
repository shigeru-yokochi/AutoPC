// Road.cpp: implementation of the CRoad class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Road.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//***********************************************************************************
//*	コンストラクタ
//***********************************************************************************
CRoad::CRoad(CString strDataPath)
{

	fb3.Create(FB_ROAD,strDataPath+FILE_IDX_ROAD3,strDataPath+FILE_DAT_ROAD3);
	fb6.Create(FB_ROAD,strDataPath+FILE_IDX_ROAD6,strDataPath+FILE_DAT_ROAD6);
	fb9.Create(FB_ROAD,strDataPath+FILE_IDX_ROAD9,strDataPath+FILE_DAT_ROAD9);
}
//***********************************************************************************
//*	デストラクタ
//***********************************************************************************
CRoad::~CRoad()
{
}

//***********************************************************************************
//*	クリア
//***********************************************************************************
void CRoad::Clr()
{
	switch(m_nMapLevel){
		case 3:	fb3.Clr();break;
		case 6:	fb6.Clr();break;
		case 9:	fb9.Clr();break;
	}
}
int _cdecl compare(const void *elem1,const void *elem2);
//***********************************************************************************
//*	ソート
//***********************************************************************************
int _cdecl compare(const void *elem1,const void *elem2)
{
	char *a,*b;
	a = (char*)(elem1);
	b = (char*)(elem2);
	a+=17;
	b+=17;

	char aa,bb;
	aa = *a&0x7f;
	bb = *b&0x7f;


//	return memcmp(*(char**)(elem1)+17),*(char**)(elem2+17),1);
//	return memcmp( * ( char** ) arg1, * ( char** ) arg2 );
	return memcmp(&aa,&bb,1);//最上位をマスク（一方通行用）

}




/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CRoad::SetMemRec9(DWORD *dwpCode,int nMapLevel)
{
	m_nMapLevel = nMapLevel;
	Clr();

	switch(m_nMapLevel){
		case 3:
			m_pStructRoadBody	= fb3.m_pRoadBody;
			fb3.SetMemRec9(dwpCode);
			qsort((void*)(m_pStructRoadBody),fb3.m_lBodyMaxCnt,DATA_BLK_SIZE,compare);
			break;
		case 6:
			m_pStructRoadBody	= fb6.m_pRoadBody;
			fb6.SetMemRec9(dwpCode);
			qsort((void*)(m_pStructRoadBody),fb6.m_lBodyMaxCnt,DATA_BLK_SIZE,compare);
			break;
		case 9:
			m_pStructRoadBody	= fb9.m_pRoadBody;
			fb9.SetMemRec9(dwpCode);
			qsort((void*)(m_pStructRoadBody),fb9.m_lBodyMaxCnt,DATA_BLK_SIZE,compare);
			break;
	}

}
/***********************************************************************************
*	ボディ数獲得
***********************************************************************************/
long CRoad::GetBodyMaxCnt()
{
	switch(m_nMapLevel){
		case 3:	return fb3.m_lBodyMaxCnt;
		case 6:	return fb6.m_lBodyMaxCnt;
		case 9:	return fb9.m_lBodyMaxCnt;
	}
	return 0;
}
