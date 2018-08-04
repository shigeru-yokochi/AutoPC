// Road.h: interface for the CRoad class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROAD_H__A91B87B5_1DC0_11D5_8950_0040CA1F5D30__INCLUDED_)
#define AFX_ROAD_H__A91B87B5_1DC0_11D5_8950_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileBody.h"

#define DATA_BLK_SIZE	18

class CRoad  
{
public:
	CRoad(CString strDataPath);
	virtual ~CRoad();
	void Clr();						//クリア

	void SetMemRec9(DWORD *dwpCode,int nMapLevel);	//９タイル分のデータをファイルよりメモリに設定
	long GetBodyMaxCnt();

	struct_RoadBody *m_pStructRoadBody;

private:

	CFileBody fb3;
	CFileBody fb6;
	CFileBody fb9;
	int m_nMapLevel;









};

#endif // !defined(AFX_ROAD_H__A91B87B5_1DC0_11D5_8950_0040CA1F5D30__INCLUDED_)
