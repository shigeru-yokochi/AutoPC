// VView.h: interface for the CVView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VVIEW_H__1384D213_24D1_11D5_895A_0040CA1F5D30__INCLUDED_)
#define AFX_VVIEW_H__1384D213_24D1_11D5_895A_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawTool.h"
#include "Road.h"
#include "Line.h"
#include "Common.h"
#include "Icon.h"
#include "Text.h"
#include "Poly.h"
#include "Dijkstra.h"



class CVView   : public CCommon
{
public:
	CVView();
	virtual ~CVView();

	void Create(CWnd *pWnd,HWND hWnd,CRect rect,int nIndex);
	void Copy(CDC *pDC);
	CDC *GetDC();
	void PaintGrid();			//グリッド描画
	void PaintCenter();			//中心表示
	void PaintLog(int nX,int nY);//軌跡点描画
	void PaintClr(int nColor);	//塗りつぶし
	BOOL GetRec9(CRoad *pRoad,CLine *pLine,CIcon *pIcon,CPoly *pPoly,
						CText *pText,DWORD *dwpCode,DWORD *dwpCode2,int nMapLevel);
//	void PaintRoad(double dfEW,double dfNS,CRoad *pRoad,int nMapLevel);	//道路描画
	void PaintRoad(CRoad *pRoad,int nMapLevel,CDC *pDCMapMach);		//道路描画
	void PaintLine(CLine *pLine);				//line描画
	void PaintRoute(int nGPSSpeed,CDC *pDCMapMach,
		CDijkstra *pDijkstra,
		HICON hIconStart,HICON hIconGoal,HICON hIconNode,HICON hIconNextNode);							//ルート検索結果描画
	void PaintIcon(CIcon* pIcon,int nMapLevel);//アイコン描画
	void PaintSearchIcon(HICON hIcon,int nMapLevel,
		double dfEW,double dfNS,
		int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf);//周辺検索結果アイコン描画

	void PaintPoly(CPoly* pPoly);				//ポリゴン描画
	void PaintText(CText* pText);				//TEXT描画
	CString m_strDistance;	//残り距離
	CString m_strTime;		//残り時間

private:
	CWnd		*m_pWnd;		//親ウィンドウ
	HWND		m_hWnd;			//親ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙ
	int			m_nIndex;

	CDC			m_dc;			//仮想画面DC
    CBitmap		m_bm;			//仮想画面ﾋﾞｯﾄﾏｯﾌﾟ
	CRect		m_RECTVView;	//仮想画面サイズ

	CDrawTool	m_DrawTool;
	double		dfRoadFact[10];		//道路幅倍率
	int			m_nRankColor[13];	//道路ランク色

	HANDLE		m_hDrawThread;      //描画ｽﾚｯﾄﾞﾊﾝﾄﾞﾙ

	double		m_dfSaveMeter;

	#define		VVIEW_PEN_WIDTH_MAX	50 
	#define		VVIEW_PEN_COLOR_MAX	13 
	CPen		m_Pen[VVIEW_PEN_WIDTH_MAX][VVIEW_PEN_COLOR_MAX];
	CPen		m_PenMapMach;
	CPen		m_PenRoute;
	CPen		m_PenRouteMapMach;



};

#endif // !defined(AFX_VVIEW_H__1384D213_24D1_11D5_895A_0040CA1F5D30__INCLUDED_)
