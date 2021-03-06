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
	void PaintGrid();			//Obh`ζ
	void PaintCenter();			//S\¦
	void PaintLog(int nX,int nY);//OΥ_`ζ
	void PaintClr(int nColor);	//hθΒΤ΅
	BOOL GetRec9(CRoad *pRoad,CLine *pLine,CIcon *pIcon,CPoly *pPoly,
						CText *pText,DWORD *dwpCode,DWORD *dwpCode2,int nMapLevel);
//	void PaintRoad(double dfEW,double dfNS,CRoad *pRoad,int nMapLevel);	//ΉH`ζ
	void PaintRoad(CRoad *pRoad,int nMapLevel,CDC *pDCMapMach);		//ΉH`ζ
	void PaintLine(CLine *pLine);				//line`ζ
	void PaintRoute(int nGPSSpeed,CDC *pDCMapMach,
		CDijkstra *pDijkstra,
		HICON hIconStart,HICON hIconGoal,HICON hIconNode,HICON hIconNextNode);							//[gυΚ`ζ
	void PaintIcon(CIcon* pIcon,int nMapLevel);//ACR`ζ
	void PaintSearchIcon(HICON hIcon,int nMapLevel,
		double dfEW,double dfNS,
		int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf);//όΣυΚACR`ζ

	void PaintPoly(CPoly* pPoly);				//|S`ζ
	void PaintText(CText* pText);				//TEXT`ζ
	CString m_strDistance;	//cθ£
	CString m_strTime;		//cθΤ

private:
	CWnd		*m_pWnd;		//eEBhE
	HWND		m_hWnd;			//e³¨έΔή³ΜΚέΔήΩ
	int			m_nIndex;

	CDC			m_dc;			//ΌzζΚDC
    CBitmap		m_bm;			//ΌzζΚΛή―ΔΟ―Μί
	CRect		m_RECTVView;	//ΌzζΚTCY

	CDrawTool	m_DrawTool;
	double		dfRoadFact[10];		//ΉH{¦
	int			m_nRankColor[13];	//ΉHNF

	HANDLE		m_hDrawThread;      //`ζ½Ϊ―ΔήΚέΔήΩ

	double		m_dfSaveMeter;

	#define		VVIEW_PEN_WIDTH_MAX	50 
	#define		VVIEW_PEN_COLOR_MAX	13 
	CPen		m_Pen[VVIEW_PEN_WIDTH_MAX][VVIEW_PEN_COLOR_MAX];
	CPen		m_PenMapMach;
	CPen		m_PenRoute;
	CPen		m_PenRouteMapMach;



};

#endif // !defined(AFX_VVIEW_H__1384D213_24D1_11D5_895A_0040CA1F5D30__INCLUDED_)
