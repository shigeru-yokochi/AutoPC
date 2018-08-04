// VView.cpp: implementation of the CVView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "VView.h"
#include "Tool.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CVView::CVView()
{
//-------------道路幅倍率--------------------------------
	dfRoadFact[0]	= 1;			//MapLevel 1
	dfRoadFact[1]	= 0.5;			//MapLevel 2
	dfRoadFact[2]	= 1;			//MapLevel 3
	dfRoadFact[3]	= 2;			//MapLevel 4
	dfRoadFact[4]	= 1;			//MapLevel 5
	dfRoadFact[5]	= 1;			//MapLevel 6
	dfRoadFact[6]	= 2;			//MapLevel 7
	dfRoadFact[7]	= 0.5;			//MapLevel 8
	dfRoadFact[8]	= 1;			//MapLevel 9
	dfRoadFact[9]	= 2;			//MapLevel 10
//-------------道路ランク色--------------------------------
	m_nRankColor[0] = RGB(190,124,124);		//細道
	m_nRankColor[1] = RGB(100,100,100);		//一般道
	m_nRankColor[2] = RGB(55,153,200);		//幹線
	m_nRankColor[3] = RGB(0xff,0x00,0x00);	//高速
	m_nRankColor[4] = RGB(128,128,128);		//	
	m_nRankColor[5] = RGB(128,128,128);		//	
	m_nRankColor[6] = RGB(128,128,128);		//	
	m_nRankColor[7] = RGB(0x80,0x80,0x80);	//
	m_nRankColor[8] = RGB(255,128,0);		//橋
	m_nRankColor[9] = RGB(0,240,60);		//トンネル

	m_nRankColor[10] = RGB(0xb0,0xb0,0xb0);	//橋(内側)
	m_nRankColor[11] = RGB(0x80,0x80,0x80);	//トンネル(内側)
	m_nRankColor[12] = RGB(255,255,255);	//内側



//-------------pen--------------------------------
	int i,ii;
	for(i=0;i<VVIEW_PEN_WIDTH_MAX;i++){
		for(ii=0;ii<VVIEW_PEN_COLOR_MAX;ii++){
			m_Pen[i][ii].CreatePen(PS_SOLID,i+1,m_nRankColor[ii]);
		}
	}

	m_PenMapMach.CreatePen(PS_SOLID,4,COLOR_MAPMACH);				//マップマッチ用
	m_PenRoute.CreatePen(PS_SOLID,6,RGB(0,255,255));				//ルート用（シアン)
	m_PenRouteMapMach.CreatePen(PS_SOLID,6,COLOR_ROUTE_MAPMACH);		//マップマッチルート用


}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CVView::~CVView()
{
}

/***********************************************************************************
*	仮想画面作成
*	rect:仮想画面ｻｲｽﾞ
***********************************************************************************/
void CVView::Create(CWnd *pWnd,HWND hWnd,CRect rect,int nIndex)
{
	m_pWnd = pWnd;
	m_hWnd = hWnd;								//親ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙ
	m_nIndex = nIndex;

	m_DrawTool.SetIndex(nIndex);

	CDC *pDC;
	m_RECTVView = rect;
//	CBrush brush,*pOldBrush;
	pDC=pWnd->GetDC();
	m_dc.CreateCompatibleDC(pDC);
	m_bm.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	m_dc.SelectObject(&m_bm);
//	brush.CreateSolidBrush(RGB(0xd0,0xe0,0xe0));		//背景色
//	pOldBrush=m_dc.SelectObject(&brush);
	m_dc.PatBlt(0,0,rect.Width(),rect.Height(),PATCOPY);
//	m_dc.PatBlt(0,0,rect.Width(),rect.Height(),BLACKNESS);

//	m_dc.SelectObject(pOldBrush);
	pWnd->ReleaseDC(pDC);
}
/***********************************************************************************
*	コピー
*	pDC:コピー元
***********************************************************************************/
void CVView::Copy(CDC *pDC)
{
	m_dc.BitBlt(0,0,m_RECTVView.right,m_RECTVView.bottom,
		pDC,
		0,
		0,
		SRCCOPY);
}
/***********************************************************************************
*	DCポインタ獲得
***********************************************************************************/
CDC * CVView::GetDC()
{
	return &m_dc;
}
/***********************************************************************************
*	グリッド描画
***********************************************************************************/
void CVView::PaintGrid()
{
	int i,nX1,nY1,nX2,nY2;

	for(i=1;i<=9;i++){
		m_DrawTool.Split9(&m_RECTVView,i,&nX1,&nY1,&nX2,&nY2);	//9分割座標獲得 
		m_DrawTool.Box(&m_dc,nX1,nY1,nX2,nY2,2,RGB(255,0,0));
	}
}
/***********************************************************************************
*	中心表示
***********************************************************************************/
void CVView::PaintCenter()
{
	m_DrawTool.Box(&m_dc,
		m_RECTVView.right/2-4,
		m_RECTVView.bottom/2-4,
		m_RECTVView.right/2+4,
		m_RECTVView.bottom/2+4,
		2,
		RGB(255,0,0));

}
/***********************************************************************************
*	軌跡点描画
***********************************************************************************/
void CVView::PaintLog(int nX,int nY)
{
//	m_DrawTool.Box(&m_dc,nX-1,nY-1,nX+1,nY+1,
//		2,
//		RGB(255,0,255));


	CPen *pOldPen;
	CPen pen1(PS_SOLID,2,RGB(255,0,255));				//ﾍﾟﾝ色

	pOldPen=m_dc.SelectObject(&pen1);

	m_dc.MoveTo(nX-1,nY-1);//LU
	m_dc.LineTo(nX-1,nY+1);//LD
	m_dc.LineTo(nX+1,nY+1);//RD
	m_dc.LineTo(nX+1,nY-1);//RU
	m_dc.LineTo(nX-1,nY-1);//LU
	
	m_dc.SelectObject(pOldPen);


}
/***********************************************************************************
*	塗りつぶし
***********************************************************************************/
void CVView::PaintClr(int nColor)
{
//	m_dc.PatBlt(0,0,m_RECTVView.Width(),m_RECTVView.Height(),BLACKNESS);

	CBrush brush,*pOldBrush;
	brush.CreateSolidBrush(nColor);		//背景色
	pOldBrush=m_dc.SelectObject(&brush);
	m_dc.PatBlt(0,0,m_RECTVView.Width(),m_RECTVView.Height(),PATCOPY);
	m_dc.SelectObject(pOldBrush);
}
/***********************************************************************************
*	9レコード取得
*	ICON,TEXTはmap level　1..10 その他は3,6,9
*	*dwpCpde:3,6,9用 *dwpCpde2:1..10用 
***********************************************************************************/
BOOL CVView::GetRec9(CRoad *pRoad,CLine *pLine,CIcon *pIcon,CPoly *pPoly,
						CText *pText,DWORD *dwpCode,DWORD *dwpCode2,int nMapLevel)
{
	int nMapLevel2 = nMapLevel;

	switch(nMapLevel){
		case 2:		case 3:		case 4:
			nMapLevel = 3;
			break;
		case 5:		case 6:		case 7:
			nMapLevel = 6;
			break;
		default:
			nMapLevel = 9;
			break;
	}


	pRoad->SetMemRec9(dwpCode,nMapLevel);						//道路		3.6.9
	pPoly->SetMemRec9(dwpCode,nMapLevel);						//ポリゴン	3.6.9
	pLine->SetMemRec9(dwpCode,nMapLevel);						//line		3.6.9

	pText->SetMemRec9(dwpCode2,nMapLevel2);						//TEXT		1..10
	pIcon->SetMemRec9(dwpCode2,nMapLevel2);						//ICON		1..10

	return TRUE;

}
/***********************************************************************************
*	道路描画
***********************************************************************************/
//void CVView::PaintRoad(double dfEW,double dfNS,CRoad *pRoad,int nMapLevel)
void CVView::PaintRoad(CRoad *pRoad,int nMapLevel,CDC *pDCMapMach)
{
	if(nMapLevel < 1)nMapLevel=0;
	if(nMapLevel > 10)nMapLevel=10;

	int i,iii,nWidth;
	BYTE bnRank;
	POINT P1, P2;

	int nColor;

//	int nWOffset;
	int nBodyMaxCnt = pRoad->GetBodyMaxCnt();


//	CPen *pOldPen;
//	CPen pen;

	m_dc.SetROP2(R2_COPYPEN);
	for(iii=0;iii<2;iii++){											//外・中で２回描画
//	for(iii=1;iii<2;iii++){											//外・中で２回描画
		for(i=0;i<nBodyMaxCnt;i++){
			nWidth = (int)(dfRoadFact[nMapLevel-1] * pRoad->m_pStructRoadBody[i].cWidth);
//			if(nWidth < 1)continue;
			bnRank = pRoad->m_pStructRoadBody[i].cRank;


			P1 = ImagePoint(pRoad->m_pStructRoadBody[i].dwEW1,
							pRoad->m_pStructRoadBody[i].dwNS1);
			P2 = ImagePoint(pRoad->m_pStructRoadBody[i].dwEW2,
							pRoad->m_pStructRoadBody[i].dwNS2);

//			if(P1.x < 0)P1.x=0;
//			if(P1.x > m_RECTVView.right)P1.x=m_RECTVView.right;
//			if(P1.y < 0)P1.y=0;
//			if(P1.y > m_RECTVView.bottom)P1.y=m_RECTVView.bottom;
//			if(P2.x < 0)P2.x=0;
//			if(P2.x > m_RECTVView.right)P2.x=m_RECTVView.right;
//			if(P2.y < 0)P2.y=0;
//			if(P2.y > m_RECTVView.bottom)P2.y=m_RECTVView.bottom;
			//----------------外----------------------------------------------
			if(iii == 0){
				if(bnRank > 9)bnRank=9;
//				nColor = m_nRankColor[bnRank];
				if(nWidth >VVIEW_PEN_WIDTH_MAX){
					TRACE(L"VVIEW_PEN_WIDTH_MAX over[CVView]\n");
					continue;
				}
				m_dc.SelectObject(&m_Pen[nWidth][bnRank]);
				m_dc.MoveTo(P1.x,P1.y);
				m_dc.LineTo(P2.x,P2.y);
//				pen.DeleteObject();

				if(pDCMapMach == NULL)continue;				//マップマッチ
					if(bnRank != 0){	//VView3
					pDCMapMach->SelectObject(m_PenMapMach);
					pDCMapMach->MoveTo(P1.x,P1.y);
					pDCMapMach->LineTo(P2.x,P2.y);
//					m_DrawTool.Line(pDCMapMach,P1.x,P1.y,P2.x,P2.y,4,COLOR_MAPMACH);
				}
			}
			//----------------中----------------------------------------------
			else{
				nWidth -= 3;
				if(nWidth < 1)continue;

				switch(bnRank){
				case 8:
					nColor = 10;
					m_dc.SetROP2(R2_COPYPEN);
					break;
				case 9:
					nColor = 11;
					m_dc.SetROP2(R2_MERGEPEN);
					break;
				default:
					m_dc.SetROP2(R2_COPYPEN);
					nColor = 12;
					break;
				}



				if(nWidth >VVIEW_PEN_WIDTH_MAX){
					TRACE(L"VVIEW_PEN_WIDTH_MAX over[CVView]\n");
					continue;
				}
				m_dc.SelectObject(&m_Pen[nWidth][nColor]);
				m_dc.MoveTo(P1.x,P1.y);
				m_dc.LineTo(P2.x,P2.y);
//				pen.DeleteObject();

			}
		}
	}
	m_dc.SetROP2(R2_COPYPEN);





}
/***********************************************************************************
*	line描画
***********************************************************************************/
void CVView::PaintLine(CLine *pLine)
{

	int i;
	POINT P1, P2;

	int nBodyMaxCnt = pLine->GetBodyMaxCnt();
	for(i=0;i<nBodyMaxCnt;i++){
//		if(pLine->GetLineInfo(i,&lEW1,&lNS1,&lEW2,&lNS2,&lColor,&bnWidth,&bnStyle) == FALSE)break;//line描画情報獲得
		P1 = ImagePoint(pLine->m_pStructLineBody[i].nEW1,
						pLine->m_pStructLineBody[i].nNS1);
		P2 = ImagePoint(pLine->m_pStructLineBody[i].nEW2,
						pLine->m_pStructLineBody[i].nNS2);


//		if(P1.x < 0)P1.x=0;
//		if(P1.x > m_RECTVView.right)P1.x=m_RECTVView.right;
//		if(P1.y < 0)P1.y=0;
//		if(P1.y > m_RECTVView.bottom)P1.y=m_RECTVView.bottom;
//		if(P2.x < 0)P2.x=0;
//		if(P2.x > m_RECTVView.right)P2.x=m_RECTVView.right;
//		if(P2.y < 0)P2.y=0;
//		if(P2.y > m_RECTVView.bottom)P2.y=m_RECTVView.bottom;
		m_DrawTool.Line(&m_dc,P1.x,P1.y,P2.x,P2.y,
						pLine->m_pStructLineBody[i].cWidth,
						pLine->m_pStructLineBody[i].nColor);
	}


}
/***********************************************************************************
*	ルート検索結果描画
***********************************************************************************/
void CVView::PaintRoute(int nGPSSpeed,CDC *pDCMapMach,
						CDijkstra *pDijkstra,
						HICON hIconStart,HICON hIconGoal,HICON hIconNode,HICON hIconNextNode)
{



	POINT P1, P2;
	int i,ii;

	m_dc.SelectObject(m_PenRoute);
	pDCMapMach->SelectObject(m_PenRouteMapMach);

//------------ルート描画-------------------------------------------
	for(i=0;i<pDijkstra->m_nNodeTraceCnt-1;i++){
		if(pDijkstra->m_nNodeTraceCnt < 3)continue;
		if(pDijkstra->GetNodeLink(i) == FALSE)break;//指定ノード間軌跡情報獲得

		for(ii=0;ii<pDijkstra->m_nBlkCnt-1;ii++){
			P1 = ImagePoint(pDijkstra->m_pNodeLinkBody[ii].nEW,
							pDijkstra->m_pNodeLinkBody[ii].nNS);
			P2 = ImagePoint(pDijkstra->m_pNodeLinkBody[ii+1].nEW,
							pDijkstra->m_pNodeLinkBody[ii+1].nNS);

			m_dc.MoveTo(P1.x,P1.y);
			m_dc.LineTo(P2.x,P2.y);

			pDCMapMach->MoveTo(P1.x,P1.y);
			pDCMapMach->LineTo(P2.x,P2.y);
		}
	}


//-----アイコン描画------------------
	POINT P;
	CString str;
	for(i=0;i<pDijkstra->m_nNodeTraceCnt;i++){
		P = ImagePoint(	pDijkstra->m_nEW[pDijkstra->m_nNodeTrace[i]],
						pDijkstra->m_nNS[pDijkstra->m_nNodeTrace[i]]);


		if(pDijkstra->m_nNodeTraceCnt == 1){
			m_dc.DrawIcon(P.x-16,P.y-16,hIconStart);			//開始アイコン
			break;
		}

//	str.Format(L"%0.1lfkm",(double)(pDijkstra->m_nDistance[i])/1000);
//	str.Format(L"%dm",pDijkstra->m_nDistance[i]);
		if(i == 0){
			m_dc.DrawIcon(P.x-16,P.y-16,hIconStart);			//開始アイコン
//			m_DrawTool.TextOut(&m_dc,P.x-16,P.y-16,str);	//残り距離表示
		}
		else
		if(i == pDijkstra->m_nNodeTraceCnt-1){
			m_dc.DrawIcon(P.x-16,P.y-16,hIconGoal);			//終了アイコン
		}
#ifdef _DEBUG
		else{		//デバッグ用
//			m_dc.DrawIcon(P.x-16,P.y-16,hIconNode);			//ノードアイコン（デバッグ用）
//			str.Format(L"%u",pDijkstra->m_nNodeTrace[i]);
//			m_DrawTool.TextOut(&m_dc,P.x-16,P.y-16,str);	//ノード番号表示

//			str.Format(L"%d",pDijkstra->m_nTurnSide[i]);//ノードturn方向
//			m_DrawTool.TextOut(&m_dc,P.x-16,P.y-16,str);
	
		}
#endif
//-------------700m手前------------------------
//		if(i == 0)continue;
//		P = ImagePoint(	pDijkstra->m_nEW700m[i],
//					pDijkstra->m_nNS700m[i]);
//		m_dc.DrawIcon(P.x-16,P.y-16,hIconNode);						//ノードアイコン（デバッグ用）
//		str.Format(L"[%d]",i);
//		m_DrawTool.TextOut(&m_dc,P.x-16,P.y-16,str);
//-------------100m手前------------------------
//		P = ImagePoint(	pDijkstra->m_nEW100m[i],
//						pDijkstra->m_nNS100m[i]);
//		m_dc.DrawIcon(P.x-16,P.y-16,hIconNode);						//ノードアイコン（デバッグ用）
//		str.Format(L"(%d)",i);
//		m_DrawTool.TextOut(&m_dc,P.x-16,P.y-16,str);
	}

//--------次ノードアイコン表示(デバッグ用)-------------
//#ifdef _DEBUG
//	if(pDijkstra->m_nNextNodeEW != 0){

//		POINT Pend;		//終了位置
//		Pend = ImagePoint(	pDijkstra->m_nEW[pDijkstra->m_nNodeTrace[pDijkstra->m_nNodeTraceCnt-1]],
//						pDijkstra->m_nNS[pDijkstra->m_nNodeTrace[pDijkstra->m_nNodeTraceCnt-1]]);


//		P = ImagePoint(	pDijkstra->m_nNextNodeEW,
//						pDijkstra->m_nNextNodeNS);
//		if(P.x != Pend.x && P.y != Pend.y){	//次ノードが終了で無い場合は描画
//			m_dc.DrawIcon(P.x-16,P.y-16,hIconNextNode);
//		}
//	}
//#endif
}
/***********************************************************************************
*	アイコン描画
***********************************************************************************/
void CVView::PaintIcon(CIcon* pIcon,int nMapLevel)
{
	int i,nIndex;
	CPoint P1;
//	int nOffset = 8,nDispXOffset = 22,nDispYOffset = 6;
	int nOffset = 16,nDispXOffset = 22,nDispYOffset = 14;
	double dfFact = 0.5;

	if(nMapLevel == 10){
		nOffset = 16;
		dfFact = 1;
		nDispXOffset = 22;
		nDispYOffset = 14;
	}

	SIZE size;
	CString str;

	m_dc.SetBkMode(TRANSPARENT);
	int nBodyMaxCnt = pIcon->GetBodyMaxCnt();
	for(i=0;i<nBodyMaxCnt;i++){
//		nIndex = pIcon->GetLoadIconIndex(pIcon->m_strIconName[i]);

//		nIndex = pIcon->GetLoadIconIndex(L"0206.ICO");
		nIndex = pIcon->GetLoadIconIndex(pIcon->m_pStructIconBody[i].nIcon);

		if(nIndex == -1)continue;
//		P1 = ImagePoint(pIcon->m_nEsat[i],pIcon->m_nNorth[i]);
		P1 = ImagePoint(pIcon->m_pStructIconBody[i].nEW,pIcon->m_pStructIconBody[i].nNS);


//		if(P1.x < 0)P1.x=0;
//		if(P1.x > m_RECTVView.right)P1.x=m_RECTVView.right;
//		if(P1.y < 0)P1.y=0;
//		if(P1.y > m_RECTVView.bottom)P1.y=m_RECTVView.bottom;

		if(P1.x < 0)continue;
		if(P1.x > m_RECTVView.right)continue;
		if(P1.y < 0)continue;
		if(P1.y > m_RECTVView.bottom)continue;


		pIcon->DrawIcon(&m_dc,P1.x-nOffset,P1.y-nOffset,nIndex,dfFact);

//		if(nMapLevel == 8)continue;	//テキストは表示しない

		str = pIcon->m_pStructIconBody[i].cDisp1;
		str.TrimRight();
		::GetTextExtentPoint32(m_dc.m_hDC,
							str,
							str.GetLength(),
							&size);

		if(pIcon->m_pStructIconBody[i].cDisp1[0] != 0){
//			m_DrawTool.TextOut(&m_dc,P1.x - size.cx/2,P1.y+nDispYOffset,str);
			m_dc.ExtTextOut(P1.x - size.cx/2,P1.y+nDispYOffset,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);
		}


		str = pIcon->m_pStructIconBody[i].cDisp2;
		str.TrimRight();
		::GetTextExtentPoint32(m_dc.m_hDC,
							str,
							str.GetLength(),
							&size);

		if(pIcon->m_pStructIconBody[i].cDisp2[0] != 0){
//			m_DrawTool.TextOut(&m_dc,P1.x - size.cx/2,P1.y+nDispYOffset+14,str);
			m_dc.ExtTextOut(P1.x - size.cx/2,P1.y+nDispYOffset+14,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);
		}

//		if(pIcon->m_pStructIconBody[i].cDisp1[0] != 0){
//			m_DrawTool.TextOut(&m_dc,P1.x-nDispXOffset,P1.y+nDispYOffset,pIcon->m_pStructIconBody[i].cDisp1);
//		}
//		if(pIcon->m_pStructIconBody[i].cDisp2[0] != 0){
//			m_DrawTool.TextOut(&m_dc,P1.x-nDispXOffset,P1.y+nDispYOffset+14,pIcon->m_pStructIconBody[i].cDisp2);
//		}



//		if(pIcon->m_strDisp1[i] != ""){
//			m_DrawTool.TextOut(&m_dc,P1.x-nDispXOffset,P1.y+nDispYOffset,pIcon->m_strDisp1[i]);
//		}
//		if(pIcon->m_strDisp2[i] != ""){
//			m_DrawTool.TextOut(&m_dc,P1.x-nDispXOffset,P1.y+nDispYOffset+10,pIcon->m_strDisp2[i]);
//		}
	}
}
/***********************************************************************************
*	周辺検索結果アイコン描画
***********************************************************************************/
void CVView::PaintSearchIcon(HICON hIcon,int nMapLevel,
							 double dfEW,double dfNS,
							 int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf)
{
	CTool tool;
	if(nCircumferenceListCnt == 0)return;

	int i;
	CPoint po,P1;
//	int nOffset = 8,nDispXOffset = 22,nDispYOffset = 6;
	int nOffset = 16,nDispXOffset = 22,nDispYOffset = 14;
	double dfFact = 0.5;

	if(nMapLevel == 10){
		nOffset = 16;
		dfFact = 1;
		nDispXOffset = 22;
		nDispYOffset = 14;
	}

	CString str;
	SIZE size;
	int nCnt=0;
	m_dc.SetBkMode(TRANSPARENT);
	for(i=0;i<nCircumferenceListCnt;i++){
//		po = pSearch->GetDispIconEWNS(i);
		po.x = npCircumferenceListBuf[nCnt];nCnt++;
		po.y = npCircumferenceListBuf[nCnt];nCnt++;
		P1 = ImagePoint(po.x,po.y);

		if(P1.x < 0)continue;
		if(P1.x > m_RECTVView.right)continue;
		if(P1.y < 0)continue;
		if(P1.y > m_RECTVView.bottom)continue;



		m_dc.DrawIcon(P1.x-nOffset,P1.y-nOffset,hIcon);


//		str = pSearch->m_strIconName[i];
		str = strpCircumferenceListBuf[i];
		str.TrimRight();
		::GetTextExtentPoint32(m_dc.m_hDC,
							str,
							str.GetLength(),
							&size);

//		m_DrawTool.TextOut(&m_dc,P1.x - size.cx/2,P1.y+10,str);
		m_dc.ExtTextOut(P1.x - size.cx/2,P1.y+10,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);


		if(dfEW != 0){
			str.Format(L"%dm",tool.PointToMeter((long)(dfEW*DEF_CONVERT),(long)(dfNS*DEF_CONVERT), po.x, po.y));
			::GetTextExtentPoint32(m_dc.m_hDC,
							str,
							str.GetLength(),
							&size);
			m_dc.ExtTextOut(P1.x - size.cx/2,P1.y+24,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);
		}
	}
}

/***********************************************************************************
*	ポリゴン描画
***********************************************************************************/
void CVView::PaintPoly(CPoly* pPoly)
{
	int i,ii;

	CPen *pNewPen,*pOldPen;
	CBrush *pNewBrush,*pOldBrush;
	POINT P1;

	int nBodyMaxCnt = pPoly->GetBodyMaxCnt();

	for(i = 0; i < nBodyMaxCnt;i++){
		pNewPen = new CPen;
		pNewPen->CreatePen(PS_SOLID,pPoly->m_pStructPolyBody[i].nWidht,
									pPoly->m_pStructPolyBody[i].nPColor);

		pNewBrush = new CBrush;
		pNewBrush->CreateSolidBrush(pPoly->m_pStructPolyBody[i].nBColor);

		pOldPen=m_dc.SelectObject(pNewPen);
		pOldBrush=m_dc.SelectObject(pNewBrush);

		for(ii=0;ii<pPoly->m_pStructPolyBody[i].nCount;ii++){
			P1  = ImagePoint(pPoly->m_pStructPolyBody[i].pPoint[ii].x,pPoly->m_pStructPolyBody[i].pPoint[ii].y);
//			if(P1.x < 0)P1.x=0;
//			if(P1.x > m_RECTVView.right)P1.x=m_RECTVView.right;
//			if(P1.y < 0)P1.y=0;
//			if(P1.y > m_RECTVView.bottom)P1.y=m_RECTVView.bottom;
			pPoly->m_pStructPolyBody[i].pPoint[ii] = P1;

//			pPoly->m_pStructPolyBody[i].pPoint[ii] = ImagePoint(pPoly->m_pStructPolyBody[i].pPoint[ii].x,
//																pPoly->m_pStructPolyBody[i].pPoint[ii].y);
		}


		m_dc.Polygon(pPoly->m_pStructPolyBody[i].pPoint, pPoly->m_pStructPolyBody[i].nCount);


		m_dc.SelectObject(pOldPen);
		m_dc.SelectObject(pOldBrush);
		delete pNewPen;
		delete pNewBrush;

	}
}
/***********************************************************************************
*	Text描画
***********************************************************************************/
void CVView::PaintText(CText* pText)
{
	int i;
	CPoint P1;
//#ifdef AUTO_PC
//	CFont	NewFont;
//	CFont	*pOldFont;
//#endif
	int nWeight;
	BOOL bItalic;
	COLORREF oldColor = m_dc.GetTextColor();
	CSize size;
	CString str;

	m_dc.SetBkMode(TRANSPARENT);
	int nBodyMaxCnt = pText->GetBodyMaxCnt();
	for(i=0;i<nBodyMaxCnt;i++){
		if(pText->m_pStructTextBody[i].cnBold == 0)	nWeight= FW_NORMAL;
		else										nWeight= FW_BOLD;

		if(pText->m_pStructTextBody[i].cnItaric == 0)bItalic= FALSE;
		else										bItalic= TRUE;
//#ifdef AUTO_PC
//		NewFont.CreateFont(pText->m_pStructTextBody[i].nFontSize, 0, 0, 0,
//					nWeight,
//					bItalic,
//					FALSE, 0, 
//					SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, 
//					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
////					FF_ROMAN, L"ＭＳ ゴシック");
//					FF_ROMAN, CString(pText->m_pStructTextBody[i].cFontName));
//		pOldFont=m_dc.SelectObject(&NewFont);
//#endif
		P1 = ImagePoint(pText->m_pStructTextBody[i].nEW,
						pText->m_pStructTextBody[i].nNS);


		

		str = pText->m_pStructTextBody[i].cName;
		str.TrimRight();
		::GetTextExtentPoint32(m_dc.m_hDC,
							str,
							str.GetLength(),
							&size);




//		P1.x -= (strlen(pText->m_pStructTextBody[i].cName)/2*10);		//センタリング
//		if(P1.x < 0)continue;
//		P1.y -= 4;
//		if(P1.y < 0)continue;

		P1.x -= (size.cx/2);
		if(P1.x < 0)continue;
		if(P1.x > m_RECTVView.right)continue;
		P1.y -= (size.cy/2);
		if(P1.y < 0)continue;
		if(P1.x > m_RECTVView.bottom)continue;


//		m_dc.SetTextColor(RGB(255,255,255));
//		m_DrawTool.TextOut(&m_dc,P1.x + 2,P1.y + 2,pText->m_pStructTextBody[i].cName);

		m_dc.SetTextColor(pText->m_pStructTextBody[i].nFontColor);
//		m_dc.SetTextColor(RGB(0,0,255));
//		m_DrawTool.TextOut(&m_dc,P1.x,P1.y,str);
		m_dc.ExtTextOut(P1.x,P1.y,ETO_OPAQUE,NULL,str,str.GetLength(),NULL);
		

//#ifdef AUTO_PC
//		m_dc.SelectObject(pOldFont);
//#endif
	}

	m_dc.SetTextColor(oldColor);
}


