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
	void PaintGrid();			//�O���b�h�`��
	void PaintCenter();			//���S�\��
	void PaintLog(int nX,int nY);//�O�Փ_�`��
	void PaintClr(int nColor);	//�h��Ԃ�
	BOOL GetRec9(CRoad *pRoad,CLine *pLine,CIcon *pIcon,CPoly *pPoly,
						CText *pText,DWORD *dwpCode,DWORD *dwpCode2,int nMapLevel);
//	void PaintRoad(double dfEW,double dfNS,CRoad *pRoad,int nMapLevel);	//���H�`��
	void PaintRoad(CRoad *pRoad,int nMapLevel,CDC *pDCMapMach);		//���H�`��
	void PaintLine(CLine *pLine);				//line�`��
	void PaintRoute(int nGPSSpeed,CDC *pDCMapMach,
		CDijkstra *pDijkstra,
		HICON hIconStart,HICON hIconGoal,HICON hIconNode,HICON hIconNextNode);							//���[�g�������ʕ`��
	void PaintIcon(CIcon* pIcon,int nMapLevel);//�A�C�R���`��
	void PaintSearchIcon(HICON hIcon,int nMapLevel,
		double dfEW,double dfNS,
		int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf);//���ӌ������ʃA�C�R���`��

	void PaintPoly(CPoly* pPoly);				//�|���S���`��
	void PaintText(CText* pText);				//TEXT�`��
	CString m_strDistance;	//�c�苗��
	CString m_strTime;		//�c�莞��

private:
	CWnd		*m_pWnd;		//�e�E�B���h�E
	HWND		m_hWnd;			//�e����޳�������
	int			m_nIndex;

	CDC			m_dc;			//���z���DC
    CBitmap		m_bm;			//���z����ޯ�ϯ��
	CRect		m_RECTVView;	//���z��ʃT�C�Y

	CDrawTool	m_DrawTool;
	double		dfRoadFact[10];		//���H���{��
	int			m_nRankColor[13];	//���H�����N�F

	HANDLE		m_hDrawThread;      //�`��گ�������

	double		m_dfSaveMeter;

	#define		VVIEW_PEN_WIDTH_MAX	50 
	#define		VVIEW_PEN_COLOR_MAX	13 
	CPen		m_Pen[VVIEW_PEN_WIDTH_MAX][VVIEW_PEN_COLOR_MAX];
	CPen		m_PenMapMach;
	CPen		m_PenRoute;
	CPen		m_PenRouteMapMach;



};

#endif // !defined(AFX_VVIEW_H__1384D213_24D1_11D5_895A_0040CA1F5D30__INCLUDED_)
