// DrawTool.cpp: implementation of the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "DrawTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CDrawTool::CDrawTool()
{
	m_nIndex = 1;
}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CDrawTool::~CDrawTool()
{
}
/***********************************************************************************
*	インデックス設定
***********************************************************************************/
void CDrawTool::SetIndex(int nIndex)
{
	m_nIndex = nIndex;
}
/***********************************************************************************
*	line
***********************************************************************************/
void CDrawTool::Line(CDC *pDC,int nX1,int nY1,int nX2,int nY2,int nW,int nColor)
{
	if(nW < 1 )return;

	CPen *pOldPen;
	CPen pen1(PS_SOLID,nW,nColor);				//ﾍﾟﾝ色

	pOldPen=pDC->SelectObject(&pen1);

	pDC->MoveTo(nX1,nY1);
	pDC->LineTo(nX2,nY2);
	
	pDC->SelectObject(pOldPen);
}
/***********************************************************************************
*	box
***********************************************************************************/
void CDrawTool::Box(CDC *pDC,int x1,int y1,int x2,int y2,int nW,int nColor)
{
	Line(pDC,x1,y1,x2,y1,nW,nColor);   /* 上 */
	Line(pDC,x1,y1,x1,y2,nW,nColor);   /* 左 */
	Line(pDC,x1,y2,x2,y2,nW,nColor);   /* 下 */
	Line(pDC,x2,y1,x2,y2,nW,nColor);   /* 右 */
}
/***********************************************************************************
*	TextOut
***********************************************************************************/
void CDrawTool::TextOut(CDC *pDC,int x1,int y1,CString str)
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->ExtTextOut(x1,y1,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);
}
/***********************************************************************************
*	円
***********************************************************************************/
void CDrawTool::Circle1(CDC* pDC, const int CX, const int CY, const int x, const int y)
{

	double dx, dy;
	int R;

	if( (CX == x) && (CY == y) ) return;

    if( CX > x ) dx = CX - x;
    else         dx = x - CX;
    if( CY > y ) dy = CY - y;
    else         dy = y - CY;
    R = (int)(sqrt( dx * dx + dy * dy ));
    pDC->Ellipse(CX - R, CY - R, CX + R, CY + R );

}
/***********************************************************************************
*	9分割座標獲得
*	No:1 2 3
*      4 5 6
*      7 8 9
***********************************************************************************/
void CDrawTool::Split9(RECT *pRect,int nNo,int *pnX1,int *pnY1,int *pnX2,int *pnY2)
{
	if(nNo < 1 || nNo > 9)return;

	nNo--;
	*pnX1 = pRect->right/3*(nNo%3);
	*pnY1 = pRect->bottom/3*(nNo/3);

	*pnX2 = *pnX1 + pRect->right/3;
	*pnY2 = *pnY1 + pRect->bottom/3;
}

/***********************************************************************************
*	指定距離と速度から到着時間を求める
*	M:距離m S:スピードkm HH,MM:時分（戻り）
***********************************************************************************/
void CDrawTool::DistanceTime(double M, double S, int *HH, int *MM)
{
	S *= 0.75;
	if(S < 10) S=10;

	int nTotalSec =  (int)(M/1000/S*3600);
	*HH = nTotalSec/3600;
	*MM = (nTotalSec%3600)/60;



/*	double T;

	T = (M/1000)/S;
	*HH = (int)floor(T);
	T = (T - *HH)*60;
	*MM = (int)floor(T);
	T = (T - *MM)*60;
	*SS = (int)T;
*/
}

