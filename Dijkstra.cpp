// Dijkstra.cpp: implementation of the CDijkstra class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Dijkstra.h"
#include "Tool.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/**************************************************************************
*	コンストラクタ
**************************************************************************/
CDijkstra::CDijkstra()
{
	E		= new struct edge[M];
	T		= new struct edge[N-1];
	dstar	= new float[N];

	m_nNodeMax	= 0;		//ノード数
	m_nNodeTraceCnt=0;		//検索結果ルートのノード数
	m_nStartNode=0;			//開始ノード
	m_nEndNode=0;			//終了ノード
	m_nStatus=0;			//設定状態
	m_bSound=TRUE;			//音声案内あり
}
/**************************************************************************
*	デストラクタ
**************************************************************************/
CDijkstra::~CDijkstra()
{
	delete [] E;
	delete [] T;
	delete [] dstar;

}
/**************************************************************************
*	接続リストロード
*	return:接続数
**************************************************************************/
void CDijkstra::Load(CString strPath,int *npConnectMax,int nCountry)
{
//*npConnectMax	= 3;
//return;


	*npConnectMax	= 0;
	int i,m;
	CFile file;
	struct DIJKSTRA m_DIJKSTRA;

	if(file.Open(strPath+ DEF_NODE_CONNECT_FILE, CFile::modeRead) == FALSE){
		TRACE(L"file open err. %s\n",DEF_NODE_CONNECT_FILE);
		return;
	}
	for(i=0;;i++){
		if(file.Read(&m_DIJKSTRA,sizeof(struct DIJKSTRA)) != sizeof(struct DIJKSTRA)){
			break;
		}
		E[i].d		= (float)m_DIJKSTRA.nDistance;
		E[i].end1	= m_DIJKSTRA.nFromNode;
		E[i].end2	= m_DIJKSTRA.nToNode;
	}


	m=i;//接続数
	file.Close();

if(nCountry == COUNTRY_KOREA){
E[m].d		= 200.0;
E[m].end1	= 207;
E[m].end2	= 206;
m++;
}
/*else{
E[m].d		= 2.0;
E[m].end1	= 1;
E[m].end2	= 1080;
m++;

E[m].d		= 2.0;
E[m].end1	= 1;
E[m].end2	= 12951;
m++;

E[m].d		= 2.0;
E[m].end1	= 1;
E[m].end2	= 12977;
m++;
}
*/

	*npConnectMax	= m;	//接続数




//----------接続試験確認用（デバッグ用）------------------------------
//	dijkstra(m_nNodeMax, m);
/*

	int k;
	CString str;
	char crlf[2];crlf[0]=0x0d;crlf[1]=0x0a;
	char tmp[100];
	if(file.Open(L"aaa.txt",CFile::modeCreate | CFile::modeWrite) == 0)return;
	TRACE(L"edges; d  end1  end2 \n");
	for(i=0;i<m; i++){
//		sprintf(tmp,"%05d %f, %d, %d",i, E[i].d, E[i].end1, E[i].end2);
		sprintf(tmp,"%05d , %05d, %05d",i,  E[i].end1, E[i].end2);
		file.Write(tmp,strlen(tmp));
		file.Write(crlf,2);								//ﾌｧｲﾙ書込み
	}
	file.Write("end",3);
	file.Write(crlf,2);
	file.Close();

*/





}

/**************************************************************************
*	指定ノード(終了ノード)と０ノードを入れ替える
*	終了ノード番号を０ノードとしてダイクストラを実施する
**************************************************************************/
void CDijkstra::HlpChg0Node(int nConnectMax)
{
	int i;
	if(m_nEndNode == 0)return;
	
	//Node0を999999にする
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== 0)E[i].end1 = 999999;
		if(E[i].end2	== 0)E[i].end2 = 999999;
	}
	//m_nEndNodeを0にする
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== m_nEndNode)E[i].end1 = 0;
		if(E[i].end2	== m_nEndNode)E[i].end2 = 0;
	}
	//999999をm_EndNodeにする
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== 999999)E[i].end1 = m_nEndNode;
		if(E[i].end2	== 999999)E[i].end2 = m_nEndNode;
	}




	//一方通行
	NodeInfo save;

	//Node0をsaveにする
	memcpy(&save.nConnectNodeNo[0],&m_NodeInfo[0].nConnectNodeNo[0],sizeof(save));

	//m_EndNodeをNode0にする
	memcpy(&m_NodeInfo[m_nEndNode].nConnectNodeNo[0],&save.nConnectNodeNo[0],sizeof(save));

	//Node0をm_EndNodendにする
	memcpy(&m_NodeInfo[0].nConnectNodeNo[0],&m_NodeInfo[m_nEndNode].nConnectNodeNo[0],sizeof(save));


}


/**************************************************************************
*	ダイクストラ
*	m:接続数
**************************************************************************/
BOOL CDijkstra::Dijkstra(int m)
{
	if(m < 1 || m_nNodeMax < 1)return FALSE;

	int nRet;
//---------------test-----------------------------------------------------------------
	//接続リスト作成
/*	m=0;
	E[m].d		= 2.0;		E[m].end1	= 3;	E[m].end2 = 4;	m++;
	E[m].d		= 1.0;		E[m].end1	= 3;	E[m].end2 = 1;	m++;
	E[m].d		= 2.0;		E[m].end1	= 4;	E[m].end2 = 1;	m++;
	E[m].d		= 2.0;		E[m].end1	= 4;	E[m].end2 = 0;	m++;
	E[m].d		= 1.0;		E[m].end1	= 1;	E[m].end2 = 0;	m++;
	E[m].d		= 2.0;		E[m].end1	= 1;	E[m].end2 = 2;	m++;
	m_nNodeMax=5;

	//ノード情報作成
	m_NodeInfo[0].nConnectNodeNo[0] = -1;
	m_NodeInfo[1].nConnectNodeNo[0] = -1;
	m_NodeInfo[2].nConnectNodeNo[0] = -1;
	m_NodeInfo[3].nConnectNodeNo[0] = 1;
	m_NodeInfo[3].nConnectNodeNo[1] = -1;
	m_NodeInfo[4].nConnectNodeNo[0] = -1;
*/

/*	m_NodeInfo[0].nConnectNodeNo[0] = 1;
	m_NodeInfo[0].nConnectNodeNo[1] = 4;
	m_NodeInfo[0].nConnectNodeNo[2] = -1;
	m_NodeInfo[0].cAtr[0] = 0xc0;
	m_NodeInfo[0].cAtr[1] = 0xc0;

	m_NodeInfo[1].nConnectNodeNo[0] = 0;
	m_NodeInfo[1].nConnectNodeNo[1] = 2;
	m_NodeInfo[1].nConnectNodeNo[2] = 3;
	m_NodeInfo[1].nConnectNodeNo[3] = 4;
	m_NodeInfo[1].nConnectNodeNo[4] = -1;
	m_NodeInfo[1].cAtr[0] = 0xb0;
	m_NodeInfo[1].cAtr[1] = 0xf0;
	m_NodeInfo[1].cAtr[2] = 0x20;
	m_NodeInfo[1].cAtr[3] = 0xf0;

	m_NodeInfo[2].nConnectNodeNo[0] = 1;
	m_NodeInfo[2].nConnectNodeNo[1] = -1;
	m_NodeInfo[2].cAtr[0] = 0x80;


	m_NodeInfo[3].nConnectNodeNo[0] = 1;
	m_NodeInfo[3].nConnectNodeNo[1] = 4;
	m_NodeInfo[3].nConnectNodeNo[2] = -1;
	m_NodeInfo[3].cAtr[0] = 0xc0;
	m_NodeInfo[3].cAtr[1] = 0x40;

	m_NodeInfo[4].nConnectNodeNo[0] = 0;
	m_NodeInfo[4].nConnectNodeNo[1] = 1;
	m_NodeInfo[4].nConnectNodeNo[2] = 3;
	m_NodeInfo[4].nConnectNodeNo[3] = -1;
	m_NodeInfo[4].cAtr[0] = 0xe0;
	m_NodeInfo[4].cAtr[1] = 0xe0;
	m_NodeInfo[4].cAtr[2] = 0xe0;
*/

/*	nRet = dijkstra(m_nNodeMax, m);
	int k;
	TRACE(L"Shortest path tree edges\n"); //どことどこが何メートルで繋がっている
	for(k=0; k<m_nNodeMax-1; k++){
		TRACE(L"%05d %f, %d, %d\n",k, T[k].d, T[k].end1, T[k].end2);
		::Sleep(1);
	}

	TRACE(L"Shortest path length\n");	//各ノードから終点までの距離
	for(k=0; k<m_nNodeMax; k++) {
		TRACE(L"node %d: %f\n", k, dstar[k]);
	}





	TRACE(L"接続試験確認用（デバッグ用）\n");
*/

//----------ここまでTEST-----------------------------------------------------------------




	HlpChg0Node(m);			//指定ノード(終了ノード)と０ノードを入れ替える
	nRet = dijkstra(m_nNodeMax, m);
	HlpChg0Node(m);			//指定ノード(終了ノード)と０ノードを入れ替える(戻す)
	if(nRet == -1)return FALSE;

	return TRUE;


}
/**********************************************************************
*	指定ノードと０ノードとの最短接続ノードリスト作成
*	m_nNodeTraceとm_nNodeTraceCntに格納される
**********************************************************************/
void  CDijkstra::GetResultNodeList(int nNode)
{
	m_nNodeTraceCnt=0;
	m_nNodeTrace[m_nNodeTraceCnt] = nNode;		
	m_nNodeTraceCnt++;
	for(;;){
		nNode = HlpGetConnectNode(nNode);	//指定ノードの接続元ノードを獲得
		if(nNode == 0)m_nNodeTrace[m_nNodeTraceCnt] = m_nEndNode;
		else          m_nNodeTrace[m_nNodeTraceCnt] = nNode;
		m_nNodeTraceCnt++;
		if(m_nNodeTraceCnt == DIJKSTRA_NODE_TRACE_MAX){
#ifdef _DEBUG
			TRACE(L"DIJKSTRA_NODE_TRACE_MAX err\n");
#else
			AfxMessageBox(L"DIJKSTRA_NODE_TRACE_MAX err");
#endif
			break;
		}
		if(nNode == 0)break;
	}
}

/**********************************************************************
*	各ノードからの残り距離リスト設定
*	m_nNodeTraceCnt分m_nDistanceに格納される
**********************************************************************/
void  CDijkstra::MakeDistanceList()
{
	int i;

	for(i=0;i<m_nNodeTraceCnt;i++){
		m_nDistance[i] = (int)dstar[m_nNodeTrace[i]];
	}
	m_nDistance[m_nNodeTraceCnt-1] = 0;		//最後は０
}
/**********************************************************************
*	各ノードのインフォメーション情報リスト設定
**********************************************************************/
void  CDijkstra::MakeInfoPointList()
{
	HlpMakeInfoPointListSub(150);	//m_nNodeTraceCnt分m_nEW100mとm_nNS100mに格納される
//	HlpMakeInfoPointListSub(700);	//m_nNodeTraceCnt分m_nEW700mとm_nNS700mに格納される
}
/**********************************************************************
*	各ノードのインフォメーション情報リスト設定sub
*	m_nNodeTraceCnt分m_nEW100mとm_nNS100mに格納される(nVal=100の場合)
*	m_nNodeTraceCnt分m_nEW700mとm_nNS700mに格納される(nVal=700の場合)
**********************************************************************/
void  CDijkstra::HlpMakeInfoPointListSub(int nVal)
{
	if(m_nNodeTraceCnt < 3)return;

	int i,ii,nDistance,nSaveDistance;
	CTool tool;
	POINT po;
	CCommon comm;
	BOOL bOK;

//	if(nVal == 100){		//初期化
		for(i=0;i<m_nNodeTraceCnt;i++){
			m_nEW100m[i] = 0;
			m_nNS100m[i] = 0;
		}
//	}
//	if(nVal == 700){		//初期化
//		for(i=0;i<m_nNodeTraceCnt;i++){
//			m_nEW700m[i] = 0;
//			m_nNS700m[i] = 0;
//		}
//	}

int nTurn;
	for(i=0;i<m_nNodeTraceCnt-1;i++){
		if(GetNodeLink(i) == FALSE)break;//指定ノード間軌跡情報獲得
		nTurn = abs(m_nTurnSide[i+1]);	//回転角度

		nSaveDistance=0;
		bOK=FALSE;
		for(ii=m_nBlkCnt-1;ii>=1;ii--){
			nDistance = tool.PointToMeter(
								(long)m_pNodeLinkBody[ii].nEW,
								(long)m_pNodeLinkBody[ii].nNS,
								(long)m_pNodeLinkBody[ii-1].nEW,
								(long)m_pNodeLinkBody[ii-1].nNS);
			if(nSaveDistance+nDistance < nVal){		//nVal m未満
				nSaveDistance += nDistance;
				continue;
			}
			po = comm.DistancePoint(m_pNodeLinkBody[ii].nEW,
									m_pNodeLinkBody[ii].nNS,
									m_pNodeLinkBody[ii-1].nEW,
									m_pNodeLinkBody[ii-1].nNS,nVal-nSaveDistance);	//直線緯度経度間の指定距離位置獲得
			bOK = TRUE;
		}


//		if(nVal == 100){
			if(nTurn > DEF_WAV_STRAIGHT || i == m_nNodeTraceCnt-2 ){		//右左折時とゴール地点
				if(bOK == TRUE){
					m_nEW100m[i+1] = po.x;	//100m手前位置
					m_nNS100m[i+1] = po.y;
				}
				else{
					m_nEW100m[i+1] = m_nEW[m_nNodeTrace[i]];	//ノード上
					m_nNS100m[i+1] = m_nNS[m_nNodeTrace[i]];
				}
			}
//		}


//		if(nVal == 700){
//			if(nTurn > DEF_WAV_STRAIGHT){
//				if(bOK == TRUE){
//					m_nEW700m[i+1] = po.x;	//700m手前位置
//					m_nNS700m[i+1] = po.y;
//				}
//			}
//		}



	}

}
/**********************************************************************
*	ノードturn方向設定
*	m_nNodeTraceCnt分m_nTurnSideに格納される
**********************************************************************/
void CDijkstra::MakeNodeTurnSide()
{
	if(m_nNodeTraceCnt < 3)return;
	m_nTurnSide[0]=0;					//開始位置は使用しない
	m_nTurnSide[m_nNodeTraceCnt-1]=0;	//終了位置は使用しない

	CCommon comm;
	int i,nEW1,nNS1,nEW2,nNS2,nAngle1,nAngle2,nMoveAngle;
	for(i=1;i<m_nNodeTraceCnt-1;i++){

		if(GetNodeLink(i-1) == FALSE)break;//前のノード間軌跡情報獲得
		if(m_nBlkCnt < 2)continue;

		nEW1 = 	m_pNodeLinkBody[m_nBlkCnt-1].nEW;	//前のノードの最後区間
		nNS1 = 	m_pNodeLinkBody[m_nBlkCnt-1].nNS;
		nEW2 = 	m_pNodeLinkBody[m_nBlkCnt-2].nEW;
		nNS2 = 	m_pNodeLinkBody[m_nBlkCnt-2].nNS;

		nAngle1 = comm.PointToGpsAngle(nEW1,nNS1,nEW2,nNS2);//EW1,NS1を基点にEW2,NS2方向のＧＰＳ角度を求める。



		if(GetNodeLink(i) == FALSE)break;//指定ノード間軌跡情報獲得
		if(m_nBlkCnt < 2)continue;

		nEW1 = 	m_pNodeLinkBody[0].nEW;	//ノードの最初の区間
		nNS1 = 	m_pNodeLinkBody[0].nNS;
		nEW2 = 	m_pNodeLinkBody[1].nEW;
		nNS2 = 	m_pNodeLinkBody[1].nNS;

		nAngle2 = comm.PointToGpsAngle(nEW1,nNS1,nEW2,nNS2);//EW1,NS1を基点にEW2,NS2方向のＧＰＳ角度を求める。

		nMoveAngle = ((nAngle2 - nAngle1)+360)%360 -180;


//TRACE(L"[%d  %d  %d ",nAngle1,nAngle2,nMoveAngle);
//if(nMoveAngle < 0)TRACE(L"左]\n");
//else              TRACE(L"右]\n");
		m_nTurnSide[i] = nMoveAngle;		//変更角度設定(-:左 +:右)
	}


	WabPlayInit();		//ノードturn方向音声案内済みフラグ初期化(未案内)

}
/**********************************************************************
*	ノードturn方向音声案内済みフラグ初期化(未案内)
**********************************************************************/
void  CDijkstra::WabPlayInit()
{
	int i;
	for(i=0;i<m_nNodeTraceCnt;i++){
		m_bWavPlay700[i] = FALSE;		//ノードturn方向700m手前音声案内済みフラグ初期化(未案内)
		m_bWavPlay100[i] = FALSE;		//ノードturn方向100m手前音声案内済みフラグ初期化(未案内)
	}
}
/**********************************************************************
*	指定ノードの接続元ノードを獲得
*	return:接続元ノード番号
**********************************************************************/
int  CDijkstra::HlpGetConnectNode(int nTragetNode)
{
	int i,nCnt=0;
	int nTmp[20];							//１ノードあたりの最大接続数
	for(i=0;i<m_nNodeMax-1;i++){
		if(T[i].end2 == nTragetNode){
			nTmp[nCnt] = T[i].end1;			//接続しているノード番号を格納
			nCnt++;
			continue;
		}

		if(T[i].end1 == nTragetNode){
			nTmp[nCnt] = T[i].end2;			//接続しているノード番号を格納
			nCnt++;
		}

	}
	if(nCnt ==0){
#ifdef _DEBUG
		TRACE(L"HlpGetConnectNode()err");
#else
		AfxMessageBox(L"HlpGetConnectNode()err");
#endif
		return 0;						//NG
	}

	if(nCnt == 1)return nTmp[0];			//接続数は１つだけなので比較なし

	//----複数接続があるため最も短い距離のものを獲得する
	int nPos=0;
	for(i=1;i<nCnt;i++){
		if(dstar[nPos] > dstar[nTmp[i]])nPos = i;
	}
	return nTmp[nPos];
}
/**********************************************************************
*	検索実行（ノードNo.０を始点として検索する）
*  節点数n, 枝数m, 枝集合Eをもつグラフの始点s=0からの最短路木を求める
*	ダイクストラのアルゴリズム; 結果をT（最短路木）とdstar（最短路長）
*	に入れる
*	return　0:正常 -1:異常
**********************************************************************/
int  CDijkstra::dijkstra(int n, int m)
{
	int i, j, k,  u, v1, v2, vadj, nh,nRet=0;

	int *P;	      /* uがPの要素ならP[u]==1、さもなければ0 */
	int *loc;     /* 節点uはヒープのloc[u]番目のセルに格納 */
	int *edge;    /* edge[v]は最短路木におけるvへの枝の候補 */
	P		 = new int[N];
	loc		 = new int[N];
	edge	 = new int[N];
	float du;
	static struct cell *adjlist[N];      /* グラフの隣接リスト */
	struct cell *r, *q, *p;  
	struct value vh, vmin; 
	struct value *heap;       /* (dstar[u], u)のヒープ */
	heap	 = new struct value[N-1];


	P[0]=1;                       /* Pの初期化 */
	for(j=1; j<n; j++) P[j]=0;
	for(j=0; j<n; j++) {adjlist[j]=NULL; loc[j]=-1;}  
                               /* 隣接リストの構成 */

	r = new struct cell[m];
	q = new struct cell[m];
	for(i=0; i<m; i++){
		v1=E[i].end1;
		if(v1 >= N)	TRACE(L"*** ERR\n");
		v2=E[i].end2;    
		if(v2 >= N)	TRACE(L"*** ERR\n");
		r[i].adj=v2;	r[i].edge=i;	r[i].next=adjlist[v1];	adjlist[v1]=&r[i];
		q[i].adj=v1;	q[i].edge=i;	q[i].next=adjlist[v2];	adjlist[v2]=&q[i];
	}
	nh=0;
	u=0;                          /* 節点0から開始 */

	du=0.0; dstar[u]=0.0;
	for(k=0; k<n-1; k++){          /* ダイクストラ法の反復 */
	    p=adjlist[u];              /* uに接続する枝によるヒープの更新（ステップ1(i)) */
	    while(p!=NULL){
			vadj=p->adj;            /* vadjはuに隣接する節点 */
			if(P[vadj]==0){ 
				if(loc[vadj] == -1){  /* vadjをヒープに入れる */
					if(HlpChkNodeInfo(u,vadj) == FALSE)vh.d=99999;	//一方通行、右左折禁止等の場合は無効にする
					else                               vh.d=du+E[p->edge].d;
					vh.node=vadj;
					edge[vadj]=p->edge;
					insert(vh, heap, loc, nh);
					nh++;
				}
				else{           /* すでにヒープにあるvadjの更新 */
					j=loc[vadj];
					if(heap[j].d > du+E[p->edge].d+ZERO){
						heap[j].d=du+E[p->edge].d;
						edge[vadj]=p->edge;
						upmin(j, heap, loc, nh);
					}
				}
			}
			if(p->next == NULL && nh==0){
#ifdef _DEBUG
				TRACE(L"未接続ノード、または重複登録があります\n");
#else
				AfxMessageBox(L"未接続ノード、または重複登録があります");
#endif
				nRet =  -1;
				goto TAG_EXIT;
			}
			p=p->next;
		}//end while
		deletemin(heap, loc, nh,&vmin); /* ステップ1(ii): vminの選択 */
		nh--;             /* u=vmin.nodeをPへ移動 */

		u=vmin.node;
		du=vmin.d;
		P[u]=1; dstar[u]=du;
		T[k]=E[edge[u]];     /* edge[u]を最短路木へ入れる */


	}//end for
TAG_EXIT:
	delete [] P;
	delete [] loc;
	delete [] edge;
	delete [] heap;
//	delete [] vp;
	delete [] r;
	delete [] q;

	return nRet;
}
/**********************************************************************
*	ヒープ A[0] to A[n-1] へ要素 x の挿入.
**********************************************************************/
void CDijkstra::insert(struct value vh, struct value *A, int *loc, int n)
{
 A[n].d=vh.d;
 A[n].node=vh.node;
 loc[A[n].node]=n;
 upmin(n, A, loc, n+1);
}
/**********************************************************************
*	ヒープ A[0] to A[n-1] から min 要素の除去.
**********************************************************************/
void CDijkstra::deletemin(struct value *A, int *loc, int n,struct value *pMin)
{
 struct value min;
 min.d=A[0].d; A[0].d=A[n-1].d;
 min.node=A[0].node; A[0].node=A[n-1].node;
 loc[A[0].node]=0;
 if(n>1) downmin(0, A, loc, n-1);
// return(min);
	memcpy(pMin,&min,sizeof(min));

}
/**********************************************************************
*	要素 A[i] から上へヒープの性質の回復.
**********************************************************************/
void CDijkstra::upmin(int i, struct value *A, int *loc, int n)
{
 int j;
 if(i<0 || i>=n){
#ifdef _DEBUG
    TRACE(L"Illegal element i = %d for n = %d\n", i, n); 
#else
    AfxMessageBox(L"CDijkstra::upmin() Illegal element"); 
#endif
    return;		//NG

   }
 if(i==0) return;
 j=(i+1)/2-1; 
 if(A[j].d>A[i].d)
   {
    swap(i, j, A, loc); 
    upmin(j, A, loc, n);
   }
 return;
}
/**********************************************************************
*	要素 A[i] から下へヒープの性質の回復； 最後の要素はA[n-1].
**********************************************************************/
void CDijkstra::downmin(int i, struct value *A, int *loc, int n)
{
 int j;
 if(i<0 || i>=n) 
   { 
#ifdef _DEBUG
    TRACE(L"Illegal element i = %d for n = %d\n", i, n); 
#else
    AfxMessageBox(L"CDijkstra::downmin() Illegal element"); 
#endif
    return;		//NG
   }
 j=2*i+1;
 if(j>=n) return;
 if(j+1<n && A[j].d > A[j+1].d+ZERO) j=j+1; 
 if(A[j].d < A[i].d-ZERO) 
   {
    swap(i, j, A, loc);
    downmin(j, A, loc, n);
   }
}
/**********************************************************************
*	ヒープAにおける構造体A[i]とA[j]の交換
**********************************************************************/
void CDijkstra::swap(int i, int j, struct value *A, int *loc)
{
	struct value temp;
	temp=A[i]; A[i]=A[j]; A[j]=temp;
	loc[A[i].node]=i; loc[A[j].node]=j;  /* locの更新 */
}
/********************************************************
*	一方通行データロード
********************************************************/
BOOL CDijkstra::LoadOneWay(CString strPath)
{
	int i,ii;
//	for(i=0;i<DEF_NODE_MAX;i++){				//ノード情報テーブル初期化
//		m_NodeInfo[i].nConnectNodeNo[0] = -1;	//未使用状態
//	}

	memset(&m_NodeInfo[0].nConnectNodeNo[0],-1,sizeof(m_NodeInfo));	//未使用状態

	struct OneWayNode a;
	CFile file;

	if(file.Open(strPath+ DEF_ONEWAY_FILE, CFile::modeRead) == FALSE){
		TRACE(L"file open err. %s\n",DEF_ONEWAY_FILE);
		return FALSE;
	}
	for(i=0;;i++){
		if(file.Read(&a,sizeof(struct OneWayNode)) != sizeof(struct OneWayNode)){
			break;
		}
		
		if(DEF_NODE_MAX  <= a.nFromNode){
			TRACE(L"DEF_NODE_MAX over\n");
			continue;
		}

		for(ii=0;ii<NODEINFO_MAX;ii++){
			if(m_NodeInfo[a.nFromNode].nConnectNodeNo[ii] == -1){	//設定位置
				m_NodeInfo[a.nFromNode].nConnectNodeNo[ii] = a.nToNode;//設定
				break;
			}
		}

	}

	file.Close();
	return TRUE;
}
/********************************************************
*	ノード位置情報ロード
********************************************************/
BOOL CDijkstra::LoadNodePoint(CString strPath)
{
	struct structNode1 a;

	int i;
	CFile file;

	if(file.Open(strPath+ DEF_NODE_FILE, CFile::modeRead) == FALSE){
		TRACE(L"file open err. %s\n",DEF_NODE_FILE);
		return FALSE;
	}
	for(i=0;;i++){
		if(file.Read(&a,sizeof(struct structNode1)) != sizeof(struct structNode1)){
			break;
		}
		m_nEW[i]	= a.nEW;
		m_nNS[i]	= a.nNS;
	}

	m_nNodeMax=i;//ノード数
	file.Close();
	return TRUE;
}
/********************************************************
*	ノード間軌跡情報ロード
********************************************************/
BOOL CDijkstra::LoadNodeLink(CString strPath)
{
	return m_LinkIndex.Create(strPath);
}
/********************************************************
*	指定ノード間軌跡情報獲得
********************************************************/
BOOL CDijkstra::GetNodeLink(int nTraceListPose)
{
	int nBodyPos;

	nBodyPos = m_LinkIndex.GetIndexPos(
		m_nEW[m_nNodeTrace[nTraceListPose]],m_nNS[m_nNodeTrace[nTraceListPose]],
		m_nEW[m_nNodeTrace[nTraceListPose+1]],m_nNS[m_nNodeTrace[nTraceListPose+1]],&m_nBlkCnt);

	if(nBodyPos == -1){
//		nBodyPos = m_LinkIndex.GetIndexPos(
//			m_nEW[m_nNodeTrace[nTraceListPose+1]],m_nNS[m_nNodeTrace[nTraceListPose+1]],
//			m_nEW[m_nNodeTrace[nTraceListPose]],m_nNS[m_nNodeTrace[nTraceListPose]],&m_nBlkCnt);	//逆で検索

//			if(nBodyPos == -1){


//#ifdef _DEBUG
				TRACE(L"*******GetNodeLink()err");
//#else
//				AfxMessageBox(L"GetNodeLink()err");
//#endif
				return FALSE;
//			}
	}


	m_LinkIndex.GetBody(nBodyPos,m_nBlkCnt);		//Body獲得
	m_pNodeLinkBody = m_LinkIndex.m_pBody;			//Bodyへのポインタ設定

	return TRUE;
}
/********************************************************
*	指定緯度経度に近いノード番号獲得
********************************************************/
int CDijkstra::GetNearNode(int nEW,int nNS)
{
	CTool tool;
	int i,nValSave=99999999,nVal,nPos=0;
	for(i=0;i<m_nNodeMax-1;i++){
		nVal = tool.PointToMeter((long)m_nEW[i],(long)m_nNS[i],(long)nEW,(long)nNS);
		if(nValSave > nVal){
			nValSave = nVal;
			nPos=i;
		}
	}

	return nPos;
}

/********************************************************
*	設定状態を設定する
********************************************************/
void CDijkstra::SetStatus(int nStatus)
{
	m_nStatus =  nStatus;					//設定状態
}
/********************************************************
*	設定状態を獲得する
********************************************************/
int CDijkstra::GetStatus()
{
	return m_nStatus;
}

/********************************************************
*	ルートはずれ検査
*	(予定する次ノード以外のノードを通過したら)
********************************************************/
/*BOOL CDijkstra::ChkRouteOut(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return TRUE;
//--------現在と次ノード位置獲得------------------------------------------
//	m_nNextNodeEW=0;
//	m_nNextNodeNS=0;

	int i,nNodeEW=0,nNodeNS=0,nNextNodeNo,nNextNodeEW,nNextNodeNS;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay700[i] == TRUE)continue;		//ノードturn方向音声案内済み(通過ずみ)
		if(m_bWavPlay100[i] == TRUE)continue;		//ノードturn方向音声案内済み(通過ずみ)

		nNextNodeNo	  = m_nNodeTrace[i];
		nNextNodeEW = m_nEW[nNextNodeNo];
		nNextNodeNS = m_nNS[nNextNodeNo];
		nNodeEW = m_nEW[m_nNodeTrace[i-1]];
		nNodeNS = m_nNS[m_nNodeTrace[i-1]];
		break;
	}

//	if(m_nNextNodeEW == 0)return TRUE;						//設定なし


//--------次ノードに隣接するノード数と位置獲得------------------------------------------
	if(nNextNodeEW != m_nNextNodeEW || nNextNodeNS != m_nNextNodeNS){	//前回と違っていたら
		m_nNextNodeEW = nNextNodeEW;
		m_nNextNodeNS = nNextNodeNS;
		CTool tool;
		m_nNearCnt=0;
		for(i=0;i<m_nNodeMax-1;i++){
//			if(T[i].end1 != nNextNodeNo && T[i].end2 != nNextNodeNo)continue;
			if(tool.PointToMeter((long)m_nEW[i],(long)m_nNS[i],(long)m_nNextNodeEW,(long)m_nNextNodeNS) > 3000)continue;	//3000m以上はなれている
			m_nNearNodeEW[m_nNearCnt] = m_nEW[i];		//隣接ノード位置設定
			m_nNearNodeNS[m_nNearCnt] = m_nNS[i];
			m_nNearCnt++;								//隣接ノード数設定
			if(m_nNearCnt == 100)break;				//これ以上設定不可能
		}
	}
//--------ルートはずれ検査------------------------------------------
	int ii;
	for(i=0;i<m_nNearCnt;i++){
//TRACE(L"%d %d\n",m_nNearNodeEW[i]-nEW,m_nNearNodeNS[i]-nNS);
		if(abs(m_nNearNodeEW[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue;
		if(abs(m_nNearNodeNS[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue;

		for(ii=0;ii<m_nNearCnt;ii++){
			if(m_nNearNodeEW[ii] == nNodeEW && m_nNearNodeNS[ii] == nNodeNS)return TRUE;	//次ノード
		}

//		WavPlay(WAV_ROUTE_OUT);						//ルートはずれ
		return FALSE;
	}


	return TRUE;
}
*/
/********************************************************
*	音声再生(700m手前)
********************************************************/
/*void CDijkstra::PlaySound700(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return;

	int i;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay700[i] == TRUE)continue;	//ノードturn方向音声案内済み
//		nVal = abs(m_nEW700m[i]-nEW + m_nNS700m[i]-nNS); 	//100m手前位置
//		if(nVal > 1000)continue;
		if(abs(m_nEW700m[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue; 	//700m手前位置
		if(abs(m_nNS700m[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue; 	//700m手前位置

		m_bWavPlay700[i] = TRUE;				//ノードturn方向音声案内済み
		//ノードturn方向
		if(i == m_nNodeTraceCnt-1){continue;}	//終了はない
		if(m_nTurnSide[i] > 0){	//右
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT)WavPlay(WAV_STRAIGHT_700);	//直進
			else if(m_nTurnSide[i] < DEF_WAV_LITTLE_TURN)WavPlay(WAV_LITTLE_RIGHT_700);	//やや右
			else WavPlay(WAV_RIGHT_700);	//右
		}
		else{					//左
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT)WavPlay(WAV_STRAIGHT_700);	//直進
			else if(m_nTurnSide[i] > -DEF_WAV_LITTLE_TURN)WavPlay(WAV_LITTLE_LEFT_700);	//やや左
			else WavPlay(WAV_LEFT_700);	//左
		}
	}
}
*/
/********************************************************
*	音声再生(100m手前)
*	return -1:再生なし 0:再生 1:再生なし(直進ﾉｰﾄﾞ)
********************************************************/
/*int CDijkstra::PlaySound100(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return -1;

	int i;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay100[i] == TRUE)continue;	//ノードturn方向音声案内済み
//		nVal = abs(m_nEW100m[i]-nEW + m_nNS100m[i]-nNS); 	//100m手前位置
//		if(nVal > 1000)continue;
//TRACE(L"[[[[[%d  %d\n",m_nEW100m[i]-nEW,m_nNS100m[i]-nNS);

		if(abs(m_nEW100m[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue; 	//100m手前位置
		if(abs(m_nNS100m[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue; 	//100m手前位置


		m_bWavPlay100[i] = TRUE;				//ノードturn方向音声案内済み
		m_bWavPlay700[i] = TRUE;				//ノードturn方向音声案内済み

		//ノードturn方向
		if(i == m_nNodeTraceCnt-1){WavPlay(WAV_END);continue;}	//終了

		if(m_nTurnSide[i] > 0){	//右
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT){
				return 1;			
//				WavPlay(WAV_STRAIGHT);	//直進
			}
			else if(m_nTurnSide[i] < DEF_WAV_LITTLE_TURN){
				WavPlay(WAV_LITTLE_RIGHT);	//やや右
			}
			else{
				WavPlay(WAV_RIGHT);	//右
			}
		}
		else{					//左
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT){
				return 1;			
//				WavPlay(WAV_STRAIGHT);	//直進
			}
			else if(m_nTurnSide[i] > -DEF_WAV_LITTLE_TURN){
				WavPlay(WAV_LITTLE_LEFT);	//やや左
			}
			else{
				WavPlay(WAV_LEFT);	//左
			}
		}
	}

	return 0;
}
*/
/***********************************************************************************
*	waw再生
***********************************************************************************/
void CDijkstra::WavPlay(CString strFname)
{
	if(m_bSound == FALSE)return;
	if(m_nNodeTraceCnt < 3)return;

#ifdef _DEBUG
	return;
#endif

	int nCnt = 1,nRepCnt = 1;
	strFname.Format(L"\\WINDOWS\\%s",strFname);

	MSG message;

	if(::sndPlaySound(strFname,SND_ASYNC | SND_NOSTOP) == FALSE)return;
	for(;;){
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)){
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
		if(nCnt == nRepCnt)break;
		if(::sndPlaySound(strFname,SND_ASYNC | SND_NOSTOP) == FALSE)continue;
		nCnt++;
	}

}
/********************************************************
*	残り距離獲得
*	return 残り距離(m) 未設定時は-1	
********************************************************/
//int CDijkstra::GetLastDistance(int nEW,int nNS)
//{
//	if(m_nNodeTraceCnt < 3)return -1;

//	CTool tool;
//	int i;
//	for(i=1;i<m_nNodeTraceCnt;i++){
//		if(m_bWavPlay100[i] == TRUE)continue;	//ノードturn方向音声案内済み

//		return m_nDistance[i] + (int)tool.PointToMeter(
//			                          (double)m_nEW[m_nNodeTrace[i]]/DEF_CONVERT,
//									  (double)m_nNS[m_nNodeTrace[i]]/DEF_CONVERT,
//									  (double)nEW/DEF_CONVERT,
//									  (double)nNS/DEF_CONVERT);

//	}

//	return 0;
//}

/********************************************************
*	ルート上の通過ノード獲得
*	return -1:ノード上でない 0..m_nNodeTraceCnt
*	(戻り)
*	*npPassNode:通過ノード番号
*	*npNextNode:通過ノードの次ノード番号
*	*npNextTurn:次右左折方向
*	*npNextTurnDistance:次右左折までの距離
*	*bp100m:右左折ノード100m手前通過中ﾌﾗｸﾞ(ノード間が100mない場合は最大距離上)
*	*np100mPos:右左折ノード100m手前通過中時のm_nNodeTraceCnt番号
********************************************************/
int CDijkstra::GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,
						   int *npNextTurn,int *npNextTurnDistance,
						   BOOL *bp100m,int *np100mPos)
{
	*bp100m = FALSE;
	if(m_nNodeTraceCnt < 3)return -1;
	int n1,n2,n3,n4,n;
	int i,ii;
	for(i=0;i<m_nNodeTraceCnt;i++){		//0～だと開始位置も含む
		n = m_nNodeTrace[i];
		n1 = abs(m_nEW[n] - nEW); 
		n2 = abs(m_nNS[n] - nNS); 

		if(m_nEW100m[i+1] != 0){	//100m手前位置
			n3 = abs(m_nEW100m[i+1] - nEW); 
			n4 = abs(m_nNS100m[i+1] - nNS); 
			if(n3 <= DEF_NODE_PASS_AREA && n4 <= DEF_NODE_PASS_AREA){
				*bp100m = TRUE;
				*np100mPos=i+1;
			}
		}

		if(n1 > DEF_NODE_PASS_AREA || n2 > DEF_NODE_PASS_AREA)continue;		//ノード上通過判定
		//---------次の右左折方向----------------------------
		*npNextTurn = 0;		//判定不能(直進)
		*npNextTurnDistance = 0;//判定不能
		if(i != m_nNodeTraceCnt-1)	*npNextTurn = m_nTurnSide[i+1];
		for(ii=i+1;ii<m_nNodeTraceCnt;ii++){
			if(m_nTurnSide[ii] < DEF_WAV_STRAIGHT  && 
			   m_nTurnSide[ii] > -DEF_WAV_STRAIGHT){//直進
				continue;
			}
			*npNextTurn = m_nTurnSide[ii];
			*npNextTurnDistance = m_nDistance[i] - m_nDistance[ii];		//次の右左折ﾉｰﾄﾞまでの距離
			break;
		}
		//-----------------------------------------------------
		*npPassNode = m_nNodeTrace[i];		//ノード上通過
		if(i != m_nNodeTraceCnt-1)*npNextNode = m_nNodeTrace[i+1];	//次ノード
		else                      *npNextNode=-1;					//判定不能
		return i;
	}
	return -1;//ノード上でない
}
/********************************************************
*	残り距離獲得(ノード間単位)
********************************************************/
int CDijkstra::GetLasDistance(int nNodeTracePos)
{
	return m_nDistance[nNodeTracePos];
}
/********************************************************
*	指定ノード間距離獲得
********************************************************/
int CDijkstra::GetNodeDistance(int nFromNodeTracePos,int nToNodeTracePos)
{
	return  m_nDistance[nFromNodeTracePos] - m_nDistance[nToNodeTracePos];
}
/********************************************************
*	指定nNodeTracePosまでの距離獲得
********************************************************/
int CDijkstra::GetNodeDistance(int nEW,int nNS,int nNodeTracePos)
{
	if(nNodeTracePos >= m_nNodeTraceCnt)return 0;

	CTool tool;
	return  (int)tool.PointToMeter(
						(double)m_nEW[m_nNodeTrace[nNodeTracePos]]/DEF_CONVERT,
						(double)m_nNS[m_nNodeTrace[nNodeTracePos]]/DEF_CONVERT,
						(double)nEW/DEF_CONVERT,
						(double)nNS/DEF_CONVERT);
}


/********************************************************
*	一番近いルート上ノード番号獲得
*   *npLastDistance:残り距離(戻り)
*   *npNextDistance:次ﾉｰﾄﾞまでの距離（ﾉｰﾄﾞ間）(戻り)
*	return ノード番号 -1の場合は該当なし
********************************************************/
int CDijkstra::GetNearNode2(int nEW,int nNS,int *npLastDistance,int *npNextDistance)
{
	if(m_nNodeTraceCnt < 3)return -1;

	BOOL bStraight=FALSE;
	CTool tool;
	int i,nNode=-1,nVal=9999999,nSaveVal;
	for(i=1;i<m_nNodeTraceCnt;i++){

		nSaveVal = (int)tool.PointToMeter(
						(double)m_nEW[m_nNodeTrace[i]]/DEF_CONVERT,
						(double)m_nNS[m_nNodeTrace[i]]/DEF_CONVERT,
						(double)nEW/DEF_CONVERT,
						(double)nNS/DEF_CONVERT);
		if(nSaveVal < nVal){
			nVal = nSaveVal;
			nNode = i;
		}

	}


//	if(m_nTurnSide[nNode] > 0){	//右
//		if(m_nTurnSide[nNode] < DEF_WAV_STRAIGHT){//直進
//			bStraight=TRUE;
//		}
//	}
//	else if(m_nTurnSide[nNode] > -DEF_WAV_STRAIGHT){//直進
//		bStraight=TRUE;
//	}


	*npLastDistance = m_nDistance[nNode];		//残り距離

	*npNextDistance = m_nDistance[nNode] - m_nDistance[nNode+1];		//次ﾉｰﾄﾞまでの距離
//	*bpStraight		= bStraight;				//直進時か？

	
	int nCnt=0;
	for(i=nNode;i<m_nNodeTraceCnt;i++){		//直進がどこまで続くか？
		if(m_nTurnSide[i] > 0){	//右
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT){//直進
				nCnt++;
				continue;
			}
		}
		else{						//左
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT){//直進
				nCnt++;
				continue;
			}
		}
		break;
	}
	if(nCnt > 1){
		*npNextDistance = m_nDistance[nNode] - m_nDistance[nNode+1+nCnt];		//次の右左折ﾉｰﾄﾞまでの距離
	}




	return m_nNodeTrace[nNode];
}
/********************************************************
*	音声案内有無設定
********************************************************/
void CDijkstra::SetSound(BOOL bMode)
{
	m_bSound = bMode;
}
/********************************************************
*	一方通行、右左折禁止等の場合は無効にする
*	return TRUE:無効にしない FALSE:無効にする
********************************************************/
BOOL CDijkstra::HlpChkNodeInfo(int nFromNode,int nToNode)
{
//一方通行のみ対応

	int i;
	for(i=0;i<NODEINFO_MAX;i++){
		if(m_NodeInfo[nFromNode].nConnectNodeNo[i] == -1)return TRUE;
		if(m_NodeInfo[nFromNode].nConnectNodeNo[i] == nToNode){
			return FALSE;
		}
	}
	return TRUE;
/*
	BYTE cVal=0x80;
	int i,NodeOutPos=-1,NodeInPos=-1;
	for(i=0;i<8;i++){
		if(m_NodeInfo[nChkNode].nConnectNodeNo[i] == -1)return TRUE;
		if(m_NodeInfo[nChkNode].nConnectNodeNo[i] == nNodeOut)NodeOutPos = i;
		if(m_NodeInfo[nChkNode].nConnectNodeNo[i] == nNodeIn)NodeInPos = i;
		if(NodeOutPos != -1 && NodeInPos != -1)goto TAG_NEXT;
	}
	return TRUE;
TAG_NEXT:
	cVal >>= NodeInPos;
	if((m_NodeInfo[nChkNode].cAtr[NodeOutPos] & cVal) == cVal)return TRUE;
	return FALSE;
*/
}

