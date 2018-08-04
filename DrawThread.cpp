// DrawThread.cpp: implementation of the CDrawThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "DrawThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//STRUCT_THREAD_DRAW_V2 structThreadDrawV2;
//BOOL	g_bV2DrawThreadMainRun = FALSE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawThread::CDrawThread(CWnd *pWnd,CRoad *pRoad,CPoly *pPoly,CIcon *pIcon,CText *pText,CLine *pLine,
						 CVView *pVView2,CVView *pVView3)


{
	m_pWnd = pWnd;
	m_pRoad = pRoad;
	m_pPoly = pPoly;
	m_pIcon = pIcon;
	m_pText = pText;
	m_pLine = pLine;
	m_pVView2 = pVView2;
	m_pVView3 = pVView3;

    // 終了イベント作成
    m_hEventStop = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    m_pThread = NULL; // スレッドオブジェクトのポインタクリア
//	m_bStop = TRUE;
}

CDrawThread::~CDrawThread()
{

   // 終了イベント破棄
   ::CloseHandle(m_hEventStop);

}





// スレッドの開始
//void CDrawThread::Start(HICON hICONSearch,long lVClientCenterX,long lVClientCenterY,
//						int nMapLevel,int nBkColorV2,double dfClientCenterEW, double dfClientCenterNS,BOOL bScroll,
//						HICON hICONGoal,double dfCurEW,double dfCurNS,int nGPSSpeed)

void CDrawThread::Start(HICON hICONSearch,long *lVClientCenterX,long *lVClientCenterY,
						int *nMapLevel,int *nBkColorV2,double *dfClientCenterEW, double *dfClientCenterNS,
						BOOL bScroll,
						HICON hICONStart,HICON hICONGoal,HICON hICONNode,HICON hICONNextNode,double dfCurEW,double dfCurNS,int *nGPSSpeed,int nCountry,
						CDijkstra *pDijkstra,
						int nCircumferenceListCnt,int *npCircumferenceListBuf,CString *strpCircumferenceListBuf)

{


    if(m_pThread != NULL)return;

	m_hICONSearch = hICONSearch;
	m_lVClientCenterX = lVClientCenterX;
	m_lVClientCenterY = lVClientCenterY;		

	m_nMapLevel			= nMapLevel;
	m_nBkColorV2		= nBkColorV2;
	m_dfClientCenterEW	= dfClientCenterEW;
	m_dfClientCenterNS	= dfClientCenterNS;
	m_bScroll			= bScroll;

	m_hICONStart		= hICONStart;
	m_hICONGoal			= hICONGoal;
	m_hICONNode			= hICONNode;
	m_hICONNextNode		= hICONNextNode;

	m_dfCurEW			= dfCurEW;
	m_dfCurNS			= dfCurNS;
	m_nGPSSpeed			= nGPSSpeed;
	m_nCountry			= nCountry;

	m_pDijkstra			= pDijkstra;

	m_nCircumferenceListCnt = nCircumferenceListCnt;	//周辺検索ITEM数
	m_npCircumferenceListBuf= npCircumferenceListBuf;	//周辺検索ITEMﾘｽﾄﾊﾞﾌｧへのﾎﾟｲﾝﾀ(EW,NS....の順番)
	m_strpCircumferenceListBuf = strpCircumferenceListBuf;//周辺検索ITEMﾘｽﾄﾊﾞﾌｧへのﾎﾟｲﾝﾀ(名称)


//ThreadProc();
//m_pThread = (CWinThread*)1234;
//return;
    // サスペンド状態でスレッドを作成
    m_pThread = ::AfxBeginThread(ThreadEntry, (LPVOID)this,
			THREAD_PRIORITY_NORMAL,
			0, CREATE_SUSPENDED, NULL);
  m_pThread->m_bAutoDelete = FALSE;	// 自動破棄フラグクリア
    m_pThread->ResumeThread();		// サスペンド解除
}


// スレッドの終了
void CDrawThread::Stop(void)
{

   if(m_pThread == NULL)return;
//m_pThread = NULL;
//return;
    ::SetEvent(m_hEventStop);	// 終了イベントセット
   
   // スレッド終了待ち
   if ( ::WaitForSingleObject(m_pThread->m_hThread, 2000)
		   				== WAIT_TIMEOUT )
   {
      // スレッド強制停止
      // (絶対に停止するなら WaitForSingleObjectで INFINITE も可）
      ::TerminateThread(m_pThread->m_hThread, 0xffffffff);
//      AfxMessageBox(L"Thread stoped force");
   }
   
   // スレッドオブジェクト破棄
   delete m_pThread;
   ::ResetEvent(m_hEventStop);	// 終了イベントクリア

   m_pThread = NULL;
}


// スレッド開始位置
UINT _cdecl CDrawThread::ThreadEntry(LPVOID pParam)
{
    CDrawThread* p = (CDrawThread*)pParam;	// 自オブジェクトの取得
    
    return p->ThreadProc();		// スレッド処理
}


// スレッド処理
UINT CDrawThread::ThreadProc()
{
//TAG_START:
//	CWaitCursor a;		//砂時計カーソル表示(廃棄時に元に戻る)

	m_pVView2->PaintClr(*m_nBkColorV2);										//塗りつぶし
	if(m_bScroll == FALSE){
		m_pVView3->PaintClr(RGB(0,0,0));											//塗りつぶし
	}

//	double dfOffset=0.0;
//	if(m_nCountry == COUNTRY_USA)dfOffset = 0.005;							//中心へ表示するための微調整

//---------------GetData-------------------------------------------------------------------------
//	DWORD dwTile[25];
	DWORD dwTile[9];	//3.6.9用
	DWORD dwTile2[9];	//1..10用
	m_pVView2->SetCenter(*m_lVClientCenterX,*m_lVClientCenterY);			//センター座標設定
	m_pVView2->SetBase(*m_dfClientCenterEW,*m_dfClientCenterNS);			//ベース座標設定
	m_pVView2->SetFact(*m_nMapLevel);

	m_pVView2->GetTileNo(*m_nMapLevel,
		*m_dfClientCenterEW,*m_dfClientCenterNS,dwTile,0);			//タイルデータ獲得 3,6,9用
	m_pVView2->GetTileNo(*m_nMapLevel,
		*m_dfClientCenterEW,*m_dfClientCenterNS,dwTile2,1);			//タイルデータ獲得 1..10用

	m_pVView2->GetRec9(m_pRoad,m_pLine,m_pIcon,m_pPoly,
		m_pText,dwTile,dwTile2,*m_nMapLevel);						//9レコード取得

//---------------描画-------------------------------------------------------------------------
//m_pWnd->PostMessage(WM_EVENT,EV_THREAD_END);								//ｽﾚｯﾄﾞ終了通知
//return 0;
	
	m_pVView2->PaintPoly(m_pPoly);											//ポリゴン描画
	if(m_bScroll == FALSE){
		m_pVView2->PaintRoad(m_pRoad,*m_nMapLevel,m_pVView3->GetDC());		//道路描画
	}
	else{
		m_pVView2->PaintRoad(m_pRoad,*m_nMapLevel,NULL);					//道路描画
	}
	m_pVView2->PaintLine(m_pLine);											//Line描画

	m_pVView2->PaintRoute(*m_nGPSSpeed,	m_pVView3->GetDC(),
		m_pDijkstra,
		m_hICONStart,m_hICONGoal,m_hICONNode,m_hICONNextNode);			//ルート検索結果描画


	m_pVView2->PaintText(m_pText);											//text描画
	m_pVView2->PaintIcon(m_pIcon,*m_nMapLevel);							//アイコン描画
	m_pVView2->PaintSearchIcon(m_hICONSearch,
		*m_nMapLevel,m_dfCurEW,m_dfCurNS,
		m_nCircumferenceListCnt,m_npCircumferenceListBuf,m_strpCircumferenceListBuf);				//周辺検索結果アイコン描画


//	g_bV2DrawThreadMainRun = FALSE;


	m_pWnd->PostMessage(WM_EVENT,EV_THREAD_END);								//ｽﾚｯﾄﾞ終了通知
//	m_bStop = TRUE;


    // 終了イベントがセットされるまでループ
//    while ( ::WaitForSingleObject(m_hEventStop, 0) == WAIT_TIMEOUT ){
//		if(m_bStop == FALSE)goto TAG_START;
//		::Sleep (1);
//   }
    return 0;
}

