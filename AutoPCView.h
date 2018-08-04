// AutoPCView.h : interface of the CAutoPCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
#define AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "DlgMenu.h"
//#include "DlgWait.h"
//#include "Trace.h"
//#include "Search.h"
//#include "Search2.h"
#include "SearchID.h"
//#include "MapLevel.h"
//#include "Route.h"
#include "Dial.h"
#include "RasDial.h"
#include "RasEntry.h"



//#include "DataBase.h"
#include "Road.h"
#include "Line.h"
#include "Text.h"

#include "DrawTool.h"
#include "GPS.h"
#include "VView.h"
//#include "TCPSoc.h"
//#include "CeTCPSoc.h"
#include "Ulp.h"
#include "Tool.h"
#include "CeCommMgr.h"
#include "DriveLog.h"
#include "DlgInfo.h"
#include "DrawThread.h"
#include "Dijkstra.h"

//#include "RouteSearch.h"

class CAutoPCView : public CView
{
protected: // create from serialization only
	CAutoPCView();
	DECLARE_DYNCREATE(CAutoPCView)

// Attributes
public:
	CAutoPCDoc* GetDocument();
	void SetMainStatus(int nType,BOOL bVal);	//状態フラグ設定
	BOOL GetMainStatus(int nType);				//状態フラグ獲得

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPCView)
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnDemoStart();
	afx_msg void OnDemoStop();
	afx_msg void OnRouteSearch();
	afx_msg void OnRouteClr();
	afx_msg void OnRouteStart();
	afx_msg void OnRouteEnd();
	afx_msg void OnUpdateRouteStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteClr(CCmdUI* pCmdUI);
	afx_msg void OnThisPlace();
	afx_msg void OnRouteReSearch();
	afx_msg void OnMymapSet();
	afx_msg void OnMymapGet();
	afx_msg void OnUpdateRouteReSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDemoStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDemoStop(CCmdUI* pCmdUI);
	afx_msg void OnSearchStruct();
	afx_msg void OnSystem();
	afx_msg void OnSearchCir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnDlgClose(UINT wParam, LONG lParam);		//ﾀﾞｲｱﾛｸﾞｸﾛｰｽﾞ通知
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);			//イベント

private:
//-------------定数-----------------------------------------
#define	TO_INIT					1			//起動完了待ちﾀｲﾏ
#define	TO_DEMO_RUN				2			//デモ走行
#define TO_RAS_CONNECT_CHK		3			//RAS接続監視
//#define	TO_GPS_DRAW				3			//GPSデータ描画
//#define	TO_THREAD				4			//スレッド終了監視ﾀｲﾏ
//#define	TO_AUTO_ZOOM			6			//オートスケール終了ﾀｲﾏ
//#define	TO_WATCH_KEY			7			//キー入力監視ﾀｲﾏ
#define	TO_WAIT_DLG_AUTO_CLOSE	8			//WAITDLG自動クローズﾀｲﾏ
#define	TO_WAIT_THEAD_START		9			//スレッド描画待ちﾀｲﾏ
#define	TO_CYCLE_1				10			//定周期ﾀｲﾏ1
#define	TO_REROUTE				11			//ﾘﾙｰﾄ許可監視ﾀｲﾏ


#define	TO_VAL_INIT				5000		//起動完了待ちﾀｲﾏ
#define	TO_VAL_DEMO_RUN			1000		//デモ走行
#define TO_VAL_RAS_CONNECT_CHK	2000		//RAS接続監視

//#define	TO_VAL_GPS_DRAW			1000		//GPSデータ描画
//#define	TO_VAL_THREAD			500			//スレッド終了監視ﾀｲﾏ
#define	TO_VAL_AUTO_ZOOM		60000		//オートスケール終了ﾀｲﾏ
//#define	TO_VAL_WATCH_KEY		1000		//キー入力監視ﾀｲﾏ
#define	TO_VAL_WAIT_THEAD_START	1000		//スレッド描画待ちﾀｲﾏ
#define	TO_VAL_CYCLE_1			1000		//定周期ﾀｲﾏ1
#define	TO_VAL_REROUTE			10000		//ﾘﾙｰﾄ許可監視ﾀｲﾏ

//-------------変数-----------------------------------------
	CString m_strDataPath;			//データパス名
	int m_nCountry;					//動作国

	RECT m_RECTClient;				//実画面ｻｲｽﾞ
	RECT m_RECTVview;				//仮想画面ｻｲｽﾞ
	double m_dfClientCenterEW;		//実画面中心経度
	double m_dfClientCenterNS;		//実画面中心緯度
	double m_dfClientCenterSaveEW;	//実画面中心経度保存用
	double m_dfClientCenterSaveNS;	//実画面中心緯度保存用


	CPoint m_POClientCenter;		//実画面中心
	int	 m_nClientCenterOffsetCar;	//中心からの自車表示オフセット
	CPoint m_POClientCenter_V1;		//仮想画面中心
	CPoint m_POClientScrollMax;		//実画面スクロール最大サイズ
	CPoint m_POClientScrollMaxV2Draw;//実画面スクロールV2描画要求サイズ
	CPoint m_POClientScroll;		//実画面スクロール量
	CPoint m_POClientScrollSave;	//実画面スクロール量保存用



	int m_nBkColor;					//背景色
	int m_nXOffset;					//仮想画面
	int m_nYOffset;					//

	int m_nMapLevel;
//	CDlgMenu	*m_pDlgMenu;
//	CDlgWait	*m_pDlgWait;
	CDlgInfo	*m_pDlgInfo;


//	CTrace		*m_pTRACE;
//	CSearch		*m_pSearch;
//	CSearch2	*m_pSearch2;
	CSearchID	*m_pSearchID;
//	CMapLevel	*m_pMapLevel;
//	CRoute		*m_pRoute;
	CDial		*m_pDial;
	CRasEntry	*m_pRasEntry;



	int m_nTestCnt;
//	BOOL m_bRs232cDraw;			//RS232Cレコード描画フラグ
	int m_nMapMachOffset;
	double m_dfMapMachOffsetEW;
	double m_dfMapMachOffsetNS;
	double m_dfSaveGPSEW;
	double m_dfSaveGPSNS;


//	int m_nMapMachAngle;
	int m_nStartAngle;
	BOOL m_bTRACE;
	int	m_nSocReceiveSize;
	BOOL m_bSocReceiveFault;
	int m_nSocReqType;
	CString m_strSearchMsg;
	CString m_strSearchMsg2;
	int m_nSaveAngle;
	BOOL m_bDemo;
	BOOL m_bKeyUP;
	BOOL m_bDemoRun;
	int m_nDriveLogWriteCnt;
	int	m_nKeyInSleepCnt;
	int m_nGPSSpeed;
	BOOL m_bAutoZoomIn;
	BOOL m_bChgMapTimer;
	int m_nSaveMapLevel;
	BOOL m_bAppExit;
	BOOL m_bWaitThreadStart;
	double m_dfRouteEW;				//ルート検索座標
	double m_dfRouteNS;				//ルート検索座標
	BOOL m_bReceiveGPS;				//GPS受信有無

	CString m_strID;
	CString m_strDial;
	CString m_strWaitDlgMsg;
	BOOL m_bOnline;

	double	m_dfChkGPS_EW;
	double	m_dfChkGPS_NS;
	int m_nChkGPSChkFlg;

	BOOL m_bInitOK;
	int m_nRouteOnOff;		//0:ルート設定なし 1:ルート設定あり
	int m_nSendIDCnt;		//ID送信管理カウンタ

	double m_dfRouteStartEW;	//ルート検索位置手動設定値	
	double m_dfRouteStartNS;
	BOOL m_bRas;
	CString m_strRasEntryName;

	double dfSaveGPSEW;		//前回受信位置保存

	int m_nCircumferenceListCnt;			//周辺検索ITEM数
	int *m_npCircumferenceListBuf;			//周辺検索ITEMﾘｽﾄﾊﾞﾌｧへのﾎﾟｲﾝﾀ(EW,NS....の順番)
	CString *m_strpCircumferenceListBuf;	//周辺検索ITEMﾘｽﾄﾊﾞﾌｧへのﾎﾟｲﾝﾀ(名称)



	CDijkstra m_Dijkstra;		//ダイクストラ
//	int m_nLastDistance;		//残り距離
//	int m_nSaveLastDistance;	//残り距離(保存用)

	char m_zEnv[4];				//システム環境設定値　0000 0=ON 1=OFF
								//                    0ﾊﾞｲﾄ目:ﾏｯﾌﾟﾏｯﾁ&ﾍﾃﾞｨﾝｸﾞｱｯﾌﾟ
								//                    1ﾊﾞｲﾄ目:ｵｰﾄｽｹｰﾙﾁｪﾝｼﾞ
								//                    2ﾊﾞｲﾄ目:ｵｰﾄﾘﾙｰﾄ
								//                    3ﾊﾞｲﾄ目:音声案内

	int m_nScaleDownPoint;		//オートスケールアップに対するダウンポイント
//	BOOL m_bScaleUp;			//オートスケール中フラグ
	int m_nNearNode;			//一番近いノード番号
	int m_nDistanceTMP;			//残り距離
	int m_nNextDistance;		//次ﾉｰﾄﾞまでの距離（ﾉｰﾄﾞ間）

	BOOL m_bRerouteTimer;		//reroute起動ﾀｲﾏ実行状態ﾌﾗｸﾞ
	int	m_nPassNode;			//通過済みノード
	int m_nNextNode;			//次ノード
	int m_nNodeTracePos;		//ノード情報配列位置
	int m_NextTurn;				//次右左折ノードの回転角度
	int m_NextTurnDistance;		//次右左折ノードまでの距離
	BOOL m_b100m;				//100m手前通過中
	int m_nSave100mPos;			//100m手前通過pos(前回通った位置)
	int	m_nEWScaleUpPoint;		//スケールダウンポイント判定用
	int	m_nNSScaleUpPoint;

//--------状態フラグ---------------------------------------------------
	BOOL m_bMainStatus[ST_ITEM_MAX];

	
	int m_nMenuStatusRoute;	//メニューイネーブル/ディセーブル状態（ルート関連）

//-------------クラス-----------------------------------------
	CVView	m_VView0;				//実画面(アイコンがちらつかないようにv1->v0)
	CVView	m_VView1;				//実画面<-1(4)<-2(3)
	CVView	m_VView2;
	CVView	m_VView3;				//MapMach用
	CVView	m_VView4;


	CRoad		*m_pRoad;
	CIcon		*m_pIcon;
	CText		*m_pText;
	CPoly		*m_pPoly;
	CLine		*m_pLine;


	CDrawTool	m_DrawTool;
//	CDataBase	*m_pDB;
	CPoint		m_poClick;
	CGPS *m_pGPS;
	CTool m_Tool;

	CDriveLog	*m_pDriveLog;

	CRasDial m_Ras;



//-------------クラスポインタ-----------------------------------------
	CWnd *m_pWndMainFrame;		//メインフレームポインタ
	CUlp *m_pSoc;
	CDrawThread	*m_pThread;
//	CRouteSearch *m_pRS;


//-------------アイコンハンドル-----------------------------------------
	HICON	m_hCarIcon;
	HICON	m_hGPS_NON_Icon;
	HICON	m_hGPS_2D_Icon;
	HICON	m_hGPS_3D_Icon;
	HICON	m_hSearch_Icon;	
	HICON	m_hCross_Icon;	
	HICON	m_hArow_Icon;	
	HICON	m_hMap01_Icon;	
	HICON	m_hMap02_Icon;	
	HICON	m_hMap03_Icon;	
	HICON	m_hMap04_Icon;	
	HICON	m_hMap05_Icon;	
	HICON	m_hMap06_Icon;	
	HICON	m_hMap07_Icon;	
	HICON	m_hMap08_Icon;	
	HICON	m_hMap09_Icon;	
	HICON	m_hMap10_Icon;	
	HICON	m_hGoal_Icon;	
	HICON	m_hPoint_Icon;	
	HICON	m_hNode_Icon;
	HICON	m_hNextNode_Icon;
	
	HICON	m_hDemo_Icon;	
	HICON	m_hSound_Icon;	
//	HICON	m_hDistance2_Icon;	
	HICON	m_hOnline_Icon;	
	HICON	m_hOffline_Icon;
	HICON	m_hDirection_Icon[8];
	




//-------------バファ----------------------------------------------
	char	m_SocBuf[BUF_SIZE];
	char m_cpBufGPSRec[BUF_SIZE];
	char *m_p232cReceiveBuf;
	struct_SearchID m_StructSearchID;	//ID検索構造体
//-------------ペルパ関数-----------------------------------------
	BOOL HlpMenuEnable(int nMenuType,int nMenuNo);	//メニューイネーブル/ディセーブル状態獲得
	BOOL SetFileFolder();							//動作環境に合ったファイルフォルダ名を設定
	void HlpInit();
	void HlpAutoDemo(double dfEW,double dfNS,int nAngle);				//自動デモ走行
	BOOL HlpScaleUpPoint(int nEW,int nNS);			//スケールダウンポイント判定
    BOOL HlpVPaint();								//仮想画面描画
    void HlpVPaint3();								//仮想画面3描画
	void HlpZConv(double *dfpEW,double *dfpNS,POINT *popView,POINT *popVView);	//座標変換
    void HlpReDraw();				//仮想画面を実画面にｺﾋﾟｰ
	void HlpV0Draw();				//仮想画面0を作成
	int HlpMapMach();
	void HlpClickSearchIcon();		//周辺検索アイコンクリック
	void HlpScroll(CPoint point,int nAngle=0xffff);	//画面スクロール
	BOOL HlpChkReDraw(CPoint point);	//実画面描画可能検査
	BOOL HlpChkDrawV(CPoint poVView);//仮想画面描画必要性検査
	void HlpCurScroll(int nX,int nY);
	BOOL HlpCurScrollChk();
	long HlpGetRecords();
	void HlpRs232cStart();		//RS232C開始
	void HlpRs232cStop();		//RS232C停止
	BOOL HlpRs232cReceive();	//RS232C受信
	void HlpRs232cDraw();		//RS232Cレコード受信終の描画

	void HlpSocConnectAndSend(int nSocReqType);
//	void HlpSocReceiveAndClose();
	int  HlpMakeRouteSetData(char *cpBuf,int nType);
//	BOOL HlpSocConnectAndSendG1G2(CString *strpSQL);
	void HlpTRACE(CString str,int level  =0 );
	void HlpTRACE(int nVal);
	void HlpGetCurEN(double *dfpEW,double *dfpNS);		//カーソル位置の緯度経獲得
	void HlpSetRouteStartEN();				// ルート検索位置手動設定値	
	void HlpSetDriveLog();					//軌跡点表示
	void HlpGetDriveLog();					//軌跡点表示

	BOOL HlpV2DrawThreadCreate();				//V2描画スレッド開始
	BOOL HlpV2DrawThreadDelete(BOOL bForce=FALSE);	//V2描画スレッド終了
//	CWinThread	*m_pThread;


	void HlpMemCard2Windows(CString strFname);		//ﾒﾓﾘｶｰﾄﾞよりwindowsディレクトリへコピー
	CCeCommMgr *m_pComm;

//	void HlpWaitDlg(BOOL bMode,CString strMsg="");
//	void HlpWaitDlgAutoClose(int nMSec);			//WAITDLG自動クローズ設定
	void HlpSaveENV();
	void HlpLoadENV(double *dfpEW,double *dfpNS,int *npAngle,int *npMapLevel,
							 CString *strpID,CString *strpDial,int *npRoute);
	void HlpSetDefaultEWNS(double *dfpEW,double *dfpNS);//緯度経度初期値設定
	void HlpSetCenterOffsetCar(int nType=0);
//	void HlpChgMapLevel(int nVal); 
	void HlpConnectOffline(int nSocReqType);		//offline時の処理
	char* CStringToChar2(CString Str,char* m_s);
	void HlpOfflineSSearch(char *cpKey,int nKeyLen);	//ｵﾌﾗｲﾝ施設検索
//	BOOL HlpChkGPSReceiveEWNS(double dfEW,double dfNS);	//GPS受信位置妥当性検査
//t HlpGetDrectionPos();						//方角アイコン変数獲得
	int HlpGetTurnCourse(int nAngle);				//回転方向獲得
	void HlpDispInit();								//初期画面
	void HlpDispInitBMP(int nX,int nY,int nID);		//
	void HlpSendID();								//ID送信
	BOOL HlpDemoData();								//ルート描画軌跡からデモ用のGPS受信データ作成 
//-----------マトリクス関数------------------------------------------------------
	int m_nStatus;												//ﾏﾄﾘｸｽ状態値
	void HlpS1E1();
	void HlpS1E2();
	void HlpS1E3();
	void HlpS1E4();
	void HlpS1E5();
	void HlpS1E6();
	void HlpS1E7();
	void HlpS1E8();
	void HlpS1E9();
	void HlpS1E10();
	void HlpS1E11();
	void HlpS1E12(int nMapLevel);
	void HlpS1E13(int nMapLevel);
	void HlpS1E14();
	void HlpS1E15();
	void HlpS1E16(int nSocReqType);
	void HlpS1E17();
	void HlpS1E18();
	void HlpS1E19();
	void HlpS1E20();
	void HlpS1E21();
	void HlpS1E22();
	void HlpS1E23();
	void HlpS1E24();
	void HlpS1E25(int nVal);
	void HlpS1E26();
	void HlpS1E27();
	void HlpS1E28(int nEntryPos);
	void HlpS1E29();
	void HlpS1E101();
	void HlpS1E102();
	void HlpS1E103();
	void HlpS1E104();
	void HlpS1E105();
	void HlpS1E106();
	void HlpS1E107();
	void HlpS1E108();
	void HlpS1E109();
	void HlpS2E1();
	void HlpS2E2();
	void HlpS2E3();
	void HlpS2E4();
	void HlpS2E5();
	void HlpS2E6();
	void HlpS2E7();
	void HlpS2E8();
	void HlpS2E9();
	void HlpS2E10();
	void HlpS2E11();
	void HlpS2E12();
	void HlpS2E13();
	void HlpS2E14();
	void HlpS2E15();
	void HlpS2E16();
	void HlpS2E17();
	void HlpS2E18();
	void HlpS2E19();
	void HlpS2E20();
	void HlpS2E21();
	void HlpS2E22();
	void HlpS2E23();
	void HlpS2E24();
	void HlpS2E25();
	void HlpS2E26();
	void HlpS2E27();
	void HlpS2E28();
	void HlpS2E29();

	void HlpS2E101();
	void HlpS2E102();
	void HlpS2E103();
	void HlpS2E104();
	void HlpS2E105();
	void HlpS2E106();
	void HlpS2E107();
	void HlpS2E108();
	void HlpS2E109();
	void HlpS3E1();
	void HlpS3E2();
	void HlpS3E3();
	void HlpS3E4();
	void HlpS3E5();
	void HlpS3E6();
	void HlpS3E7();
	void HlpS3E8();
	void HlpS3E9();
	void HlpS3E10();
	void HlpS3E11();
	void HlpS3E12();
	void HlpS3E13();
	void HlpS3E14();
	void HlpS3E15();
	void HlpS3E16();
	void HlpS3E17();
	void HlpS3E18();
	void HlpS3E19();
	void HlpS3E20();
	void HlpS3E21();
	void HlpS3E22();
	void HlpS3E23();
	void HlpS3E24();
	void HlpS3E25();
	void HlpS3E26();
	void HlpS3E27();
	void HlpS3E28();
	void HlpS3E29();

	void HlpS3E101();
	void HlpS3E102();
	void HlpS3E103();
	void HlpS3E104();
	void HlpS3E105();
	void HlpS3E106();
	void HlpS3E107();
	void HlpS3E108();
	void HlpS3E109();


};

#ifndef _DEBUG  // debug version in AutoPCView.cpp
inline CAutoPCDoc* CAutoPCView::GetDocument()
   { return (CAutoPCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
