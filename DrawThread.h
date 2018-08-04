// DrawThread.h: interface for the CDrawThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWTHREAD_H__0DFC9C29_D18A_4CA1_9232_D2795F4711A7__INCLUDED_)
#define AFX_DRAWTHREAD_H__0DFC9C29_D18A_4CA1_9232_D2795F4711A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VView.h"
//#include "DataBase.h"
#include "Poly.h"
#include "Road.h"
#include "Line.h"
#include "Icon.h"
#include "Text.h"
#include "Dijkstra.h"




class CDrawThread  
{
public:
	CDrawThread(CWnd *pWnd,CRoad *pRoad,CPoly *pPoly,CIcon *pIcon,CText *pText,CLine *pLine,
						 CVView *pVView2,CVView *pVView3);

						 
	virtual ~CDrawThread();

	// �X���b�h�̊J�n
//	void Start(HICON hICONSearch,long lVClientCenterX,long lVClientCenterY,
//				int nMapLevel,int nBkColorV2,double dfClientCenterEW, double dfClientCenterNS,BOOL bScroll,
//				HICON hICONGoal,double dfCurEW,double dfCurNS,int nGPSSpeed);

	void Start(HICON hICONSearch,long *lVClientCenterX,long *lVClientCenterY,
						int *nMapLevel,int *nBkColorV2,double *dfClientCenterEW, double *dfClientCenterNS,
						BOOL bScroll,
						HICON hICONStart,HICON hICONGoal,HICON hICONNode,HICON hICONNextNode,double dfCurEW,double dfCurNS,int *nGPSSpeed,int nCountry,
						CDijkstra *pDijkstra,
						int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf);

	void Stop();	// �X���b�h�̏I��
    CWinThread* m_pThread;	// �X���b�h�I�u�W�F�N�g
//	int m_pThread;	

protected:
   static UINT _cdecl ThreadEntry(LPVOID pParam);	// �X���b�h�J�n�ʒu
   UINT ThreadProc();		// �X���b�h����

   HANDLE m_hEventStop;		// �I���C�x���g

private:
	CWnd *m_pWnd;
	CRoad *m_pRoad;
	CPoly *m_pPoly;
	CIcon *m_pIcon;
	CText *m_pText;
	CLine *m_pLine;
	CVView *m_pVView2;
	CVView *m_pVView3;

	HICON		m_hICONSearch;
	long		*m_lVClientCenterX;
	long		*m_lVClientCenterY;

	int			*m_nMapLevel;
	int			*m_nBkColorV2;
	double		*m_dfClientCenterEW;
	double		*m_dfClientCenterNS;

	BOOL		m_bScroll;
	HICON		m_hICONStart;
	HICON		m_hICONGoal;
	HICON		m_hICONNode;
	HICON		m_hICONNextNode;

	double		m_dfCurEW;
	double		m_dfCurNS;
	int			*m_nGPSSpeed;
	int			m_nCountry;

	CDijkstra	*m_pDijkstra;

	int m_nCircumferenceListCnt;	//���ӌ���ITEM��
	int *m_npCircumferenceListBuf;	//���ӌ���ITEMؽ���̧�ւ��߲��(EW,NS....�̏���)
	CString *m_strpCircumferenceListBuf;//���ӌ���ITEMؽ���̧�ւ��߲��(����)
};

#endif // !defined(AFX_DRAWTHREAD_H__0DFC9C29_D18A_4CA1_9232_D2795F4711A7__INCLUDED_)
