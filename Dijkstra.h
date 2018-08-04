// Dijkstra.h: interface for the CDijkstra class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIJKSTRA_H__DF87B3C7_86D5_4E49_B024_8DA3A05B4C16__INCLUDED_)
#define AFX_DIJKSTRA_H__DF87B3C7_86D5_4E49_B024_8DA3A05B4C16__INCLUDED_


#include "LinkIndex.h"
#include "Common.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define 	DIJKSTRA_ST_CLR				0			//クリア状態(状態)
#define 	DIJKSTRA_ST_SET_START		1			//開始位置設定状態
#define 	DIJKSTRA_ST_SET_END			2			//終了位置設定状態
#define 	DIJKSTRA_ST_ROUTE			3			//ルート設定状態

#define		DIJKSTRA_NODE_TRACE_MAX		1000		//ルート上のノード最大数
#define		DEF_CHK_EWNS_AREA_EW		1000		//位置判定範囲（大きいほど判定エリアが広くなる）
#define		DEF_CHK_EWNS_AREA_NS		20000		//位置判定範囲（大きいほど判定エリアが広くなる）

#define		DEF_NODE_PASS_AREA			2000		//ノード上通過判定（大きいほど判定エリアが広くなる）

class CDijkstra  
{
public:
	CDijkstra();
	virtual ~CDijkstra();
	void Load(CString strPath,int *npConnectMax,int nCountry);
	BOOL Dijkstra(int m);							//全ノードの最短区間獲得
	void  GetResultNodeList(int nNode);				//指定ノードと０ノードとの最短接続ノードリスト作成
	void  MakeDistanceList();						//各ノードからの残り距離リスト設定
	void  MakeInfoPointList();						//各ノードのインフォメーション情報リスト設定
	void MakeNodeTurnSide();						//ノードturn方向設定
	void WabPlayInit();								//ノードturn方向音声案内済みフラグ初期化(未案内)
	void SetStatus(int nStatus);					//設定状態を設定する
	int  GetStatus();								//設定状態を獲得する
//	BOOL ChkRouteOut(int nEW,int nNS);				//ルートはずれ検査
//	void PlaySound700(int nEW,int nNS);				//音声再生(700m手前)
//	int PlaySound100(int nEW,int nNS);				//音声再生(100m手前)
//	int  GetLastDistance(int nEW,int nNS);			//残り距離獲得
	void SetSound(BOOL bMode);						//音声案内有無設定
	void WavPlay(CString strFname);					//waw再生
	BOOL HlpChkNodeInfo(int nFromNode,int nToNode);//一方通行の場合は無効にする

	int m_nNodeTraceCnt;							//検索結果ルートのノード数
	int m_nNodeTrace[DIJKSTRA_NODE_TRACE_MAX];		//検索結果ルートのノード格納バッファ

	BOOL LoadNodePoint(CString strPath);	//ノード位置情報ロード
	BOOL LoadOneWay(CString strPath);			//一方通行データロード
	BOOL LoadNodeLink(CString strPath);		//ノード間軌跡情報ロード
	BOOL GetNodeLink(int nTraceListPose);	//指定ノード間軌跡情報獲得
	int GetNearNode(int nEW,int nNS);		//指定緯度経度に近いノード番号獲得
	int GetNearNode2(int nEW,int nNS,int *npLastDistance,int *npNextDistance);//一番近いルート上ノード番号獲得

	int GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,		//ルート上の通過ノード獲得
						   int *npNextTurn,int *npNextTurnDistance,
						   BOOL *bp100m,int *np100mPos);
	int GetLasDistance(int nNodeTracePos);			//残り距離獲得(ノード間単位)

	int GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,int *npNextTurn,int *npNextTurnDistance);		//ルート上の通過ノード獲得
	int GetNodeDistance(int nFromNodeTracePos,int nToNodeTracePos);//指定間距離獲得
	int GetNodeDistance(int nEW,int nNS,int nNodeTracePos);//指定nNodeTracePosまでの距離獲得

	int m_nBlkCnt;							//ノード間軌跡情報body数
	struct_Body *m_pNodeLinkBody;			//ノード間軌跡情報bodyデータへのポインタ


	int m_nEW[DEF_NODE_MAX];			//ノード位置情報
	int m_nNS[DEF_NODE_MAX];			//ノード位置情報
	int m_nDistance[DEF_NODE_MAX];		//終点までの残り距離
	int m_nEW100m[DEF_NODE_MAX];		//100m手前位置
	int m_nNS100m[DEF_NODE_MAX];
//	int m_nEW700m[DEF_NODE_MAX];		//700m手前位置
//	int m_nNS700m[DEF_NODE_MAX];
	int m_nTurnSide[DEF_NODE_MAX];		//ノードturn方向
	BOOL m_bWavPlay700[DEF_NODE_MAX];	//ノードturn方向700m手前音声案内済みフラグ
	BOOL m_bWavPlay100[DEF_NODE_MAX];	//ノードturn方向100m手前音声案内済みフラグ
	CLinkIndex m_LinkIndex;				//Link.idx


	int m_nNodeMax;						//ノード数
	int m_nStartNode;					//開始ノード
	int m_nEndNode;						//終了ノード

//	int m_nNextNodeEW;					//次ノード位置
//	int m_nNextNodeNS;					//次ノード位置
//	int m_nNearCnt;						//隣接ノード数
//	int m_nNearNodeEW[100];				//隣接ノード位置
//	int m_nNearNodeNS[100];


private:

//	int nNodeTotal;					//ノード合計数
//	int nConnectTotal;				//接続合計数

	
	int m_nStatus;					//設定状態

	struct DIJKSTRA{	//ダイクストラ法検索用構造体
		int nDistance;				//接続間距離(m)
		int nFromNode;				//接続元ノード番号(0～)
		int nToNode;				//接続先ノード番号(0～)
	};//12byte



	#define N DEF_NODE_MAX         //ノード最大数
	#define M DEF_NODE_CONNECT_MAX	//接続最大数
	#define ZERO 0.0001		//丸め誤差の許容値
	struct edge{			//構造体edgeの定義
		float d;
//		int d;				//接続間距離(m)
		int end1;			//接続元ノード番号(0～)
		int	end2;			//接続先ノード番号(0～)

	};
	struct value{          /* 構造体valueの定義 */
		float d;
		int node;
	};
	struct cell{           /* 構造体cellの定義 */
		int adj;
		int edge;
		struct cell *next;
	};

	struct	edge *E;			//最短路木T
	struct	edge *T;			//接続リストE
	float	*dstar;				//ノードへの最短路長
	
	BOOL m_bSound;				//音声案内有無

	struct OneWayNode{			//一方通行レコード構造
	    int nFromNode;
	    int nToNode;
	};

#define NODEINFO_MAX	8
	struct NodeInfo{           /* ﾉｰﾄﾞ情報定義 */
		int nConnectNodeNo[NODEINFO_MAX];	//最大8ﾉｰﾄﾞ接続可能 -1は未定義
//		BYTE cAtr[8];			//In-Out 定義 1が通行可能 ８bitx8byt分定義
	};
	struct	NodeInfo m_NodeInfo[DEF_NODE_MAX];	//ﾉｰﾄﾞ情報定義


	/* 関数の宣言 */
//	void dijkstra(struct edge *E, struct edge *T, float *d,  int n, int m);
	int dijkstra(int n, int m);
	void deletemin(struct value *A, int *loc, int n,struct value *pMin);
	void downmin(int i, struct value *A, int *loc, int n);
	void insert(struct value dj, struct value *A, int *loc,  int n); 
	void upmin(int i, struct value *A, int *loc, int n);
	void swap(int i, int j, struct value *A, int *loc);

	int HlpGetConnectNode(int nTragetNode);	//指定ノードの接続元ノードを獲得
	void HlpChg0Node(int nConnectMax);		//指定ノード(終了ノード)と０ノードを入れ替える
	void HlpMakeInfoPointListSub(int nVal);	//各ノードのインフォメーション情報リスト設定sub


	struct structNode1{			//ノード位置情報
		int nNode;				//未使用
		int nEW;
		int nNS;
	};


//	void HlpGetNearNodeSub(int nEWNS,int *npEWNS,int *npNearList,int nListCntMax);	//指定緯度経度に近いノード番号獲得sub1
};

#endif // !defined(AFX_DIJKSTRA_H__DF87B3C7_86D5_4E49_B024_8DA3A05B4C16__INCLUDED_)
