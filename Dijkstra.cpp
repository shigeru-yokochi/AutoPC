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
*	�R���X�g���N�^
**************************************************************************/
CDijkstra::CDijkstra()
{
	E		= new struct edge[M];
	T		= new struct edge[N-1];
	dstar	= new float[N];

	m_nNodeMax	= 0;		//�m�[�h��
	m_nNodeTraceCnt=0;		//�������ʃ��[�g�̃m�[�h��
	m_nStartNode=0;			//�J�n�m�[�h
	m_nEndNode=0;			//�I���m�[�h
	m_nStatus=0;			//�ݒ���
	m_bSound=TRUE;			//�����ē�����
}
/**************************************************************************
*	�f�X�g���N�^
**************************************************************************/
CDijkstra::~CDijkstra()
{
	delete [] E;
	delete [] T;
	delete [] dstar;

}
/**************************************************************************
*	�ڑ����X�g���[�h
*	return:�ڑ���
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


	m=i;//�ڑ���
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

	*npConnectMax	= m;	//�ڑ���




//----------�ڑ������m�F�p�i�f�o�b�O�p�j------------------------------
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
		file.Write(crlf,2);								//̧�ُ�����
	}
	file.Write("end",3);
	file.Write(crlf,2);
	file.Close();

*/





}

/**************************************************************************
*	�w��m�[�h(�I���m�[�h)�ƂO�m�[�h�����ւ���
*	�I���m�[�h�ԍ����O�m�[�h�Ƃ��ă_�C�N�X�g�������{����
**************************************************************************/
void CDijkstra::HlpChg0Node(int nConnectMax)
{
	int i;
	if(m_nEndNode == 0)return;
	
	//Node0��999999�ɂ���
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== 0)E[i].end1 = 999999;
		if(E[i].end2	== 0)E[i].end2 = 999999;
	}
	//m_nEndNode��0�ɂ���
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== m_nEndNode)E[i].end1 = 0;
		if(E[i].end2	== m_nEndNode)E[i].end2 = 0;
	}
	//999999��m_EndNode�ɂ���
	for(i=0;i<nConnectMax;i++){
		if(E[i].end1	== 999999)E[i].end1 = m_nEndNode;
		if(E[i].end2	== 999999)E[i].end2 = m_nEndNode;
	}




	//����ʍs
	NodeInfo save;

	//Node0��save�ɂ���
	memcpy(&save.nConnectNodeNo[0],&m_NodeInfo[0].nConnectNodeNo[0],sizeof(save));

	//m_EndNode��Node0�ɂ���
	memcpy(&m_NodeInfo[m_nEndNode].nConnectNodeNo[0],&save.nConnectNodeNo[0],sizeof(save));

	//Node0��m_EndNodend�ɂ���
	memcpy(&m_NodeInfo[0].nConnectNodeNo[0],&m_NodeInfo[m_nEndNode].nConnectNodeNo[0],sizeof(save));


}


/**************************************************************************
*	�_�C�N�X�g��
*	m:�ڑ���
**************************************************************************/
BOOL CDijkstra::Dijkstra(int m)
{
	if(m < 1 || m_nNodeMax < 1)return FALSE;

	int nRet;
//---------------test-----------------------------------------------------------------
	//�ڑ����X�g�쐬
/*	m=0;
	E[m].d		= 2.0;		E[m].end1	= 3;	E[m].end2 = 4;	m++;
	E[m].d		= 1.0;		E[m].end1	= 3;	E[m].end2 = 1;	m++;
	E[m].d		= 2.0;		E[m].end1	= 4;	E[m].end2 = 1;	m++;
	E[m].d		= 2.0;		E[m].end1	= 4;	E[m].end2 = 0;	m++;
	E[m].d		= 1.0;		E[m].end1	= 1;	E[m].end2 = 0;	m++;
	E[m].d		= 2.0;		E[m].end1	= 1;	E[m].end2 = 2;	m++;
	m_nNodeMax=5;

	//�m�[�h���쐬
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
	TRACE(L"Shortest path tree edges\n"); //�ǂ��Ƃǂ��������[�g���Ōq�����Ă���
	for(k=0; k<m_nNodeMax-1; k++){
		TRACE(L"%05d %f, %d, %d\n",k, T[k].d, T[k].end1, T[k].end2);
		::Sleep(1);
	}

	TRACE(L"Shortest path length\n");	//�e�m�[�h����I�_�܂ł̋���
	for(k=0; k<m_nNodeMax; k++) {
		TRACE(L"node %d: %f\n", k, dstar[k]);
	}





	TRACE(L"�ڑ������m�F�p�i�f�o�b�O�p�j\n");
*/

//----------�����܂�TEST-----------------------------------------------------------------




	HlpChg0Node(m);			//�w��m�[�h(�I���m�[�h)�ƂO�m�[�h�����ւ���
	nRet = dijkstra(m_nNodeMax, m);
	HlpChg0Node(m);			//�w��m�[�h(�I���m�[�h)�ƂO�m�[�h�����ւ���(�߂�)
	if(nRet == -1)return FALSE;

	return TRUE;


}
/**********************************************************************
*	�w��m�[�h�ƂO�m�[�h�Ƃ̍ŒZ�ڑ��m�[�h���X�g�쐬
*	m_nNodeTrace��m_nNodeTraceCnt�Ɋi�[�����
**********************************************************************/
void  CDijkstra::GetResultNodeList(int nNode)
{
	m_nNodeTraceCnt=0;
	m_nNodeTrace[m_nNodeTraceCnt] = nNode;		
	m_nNodeTraceCnt++;
	for(;;){
		nNode = HlpGetConnectNode(nNode);	//�w��m�[�h�̐ڑ����m�[�h���l��
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
*	�e�m�[�h����̎c�苗�����X�g�ݒ�
*	m_nNodeTraceCnt��m_nDistance�Ɋi�[�����
**********************************************************************/
void  CDijkstra::MakeDistanceList()
{
	int i;

	for(i=0;i<m_nNodeTraceCnt;i++){
		m_nDistance[i] = (int)dstar[m_nNodeTrace[i]];
	}
	m_nDistance[m_nNodeTraceCnt-1] = 0;		//�Ō�͂O
}
/**********************************************************************
*	�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�
**********************************************************************/
void  CDijkstra::MakeInfoPointList()
{
	HlpMakeInfoPointListSub(150);	//m_nNodeTraceCnt��m_nEW100m��m_nNS100m�Ɋi�[�����
//	HlpMakeInfoPointListSub(700);	//m_nNodeTraceCnt��m_nEW700m��m_nNS700m�Ɋi�[�����
}
/**********************************************************************
*	�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�sub
*	m_nNodeTraceCnt��m_nEW100m��m_nNS100m�Ɋi�[�����(nVal=100�̏ꍇ)
*	m_nNodeTraceCnt��m_nEW700m��m_nNS700m�Ɋi�[�����(nVal=700�̏ꍇ)
**********************************************************************/
void  CDijkstra::HlpMakeInfoPointListSub(int nVal)
{
	if(m_nNodeTraceCnt < 3)return;

	int i,ii,nDistance,nSaveDistance;
	CTool tool;
	POINT po;
	CCommon comm;
	BOOL bOK;

//	if(nVal == 100){		//������
		for(i=0;i<m_nNodeTraceCnt;i++){
			m_nEW100m[i] = 0;
			m_nNS100m[i] = 0;
		}
//	}
//	if(nVal == 700){		//������
//		for(i=0;i<m_nNodeTraceCnt;i++){
//			m_nEW700m[i] = 0;
//			m_nNS700m[i] = 0;
//		}
//	}

int nTurn;
	for(i=0;i<m_nNodeTraceCnt-1;i++){
		if(GetNodeLink(i) == FALSE)break;//�w��m�[�h�ԋO�Տ��l��
		nTurn = abs(m_nTurnSide[i+1]);	//��]�p�x

		nSaveDistance=0;
		bOK=FALSE;
		for(ii=m_nBlkCnt-1;ii>=1;ii--){
			nDistance = tool.PointToMeter(
								(long)m_pNodeLinkBody[ii].nEW,
								(long)m_pNodeLinkBody[ii].nNS,
								(long)m_pNodeLinkBody[ii-1].nEW,
								(long)m_pNodeLinkBody[ii-1].nNS);
			if(nSaveDistance+nDistance < nVal){		//nVal m����
				nSaveDistance += nDistance;
				continue;
			}
			po = comm.DistancePoint(m_pNodeLinkBody[ii].nEW,
									m_pNodeLinkBody[ii].nNS,
									m_pNodeLinkBody[ii-1].nEW,
									m_pNodeLinkBody[ii-1].nNS,nVal-nSaveDistance);	//�����ܓx�o�x�Ԃ̎w�苗���ʒu�l��
			bOK = TRUE;
		}


//		if(nVal == 100){
			if(nTurn > DEF_WAV_STRAIGHT || i == m_nNodeTraceCnt-2 ){		//�E���܎��ƃS�[���n�_
				if(bOK == TRUE){
					m_nEW100m[i+1] = po.x;	//100m��O�ʒu
					m_nNS100m[i+1] = po.y;
				}
				else{
					m_nEW100m[i+1] = m_nEW[m_nNodeTrace[i]];	//�m�[�h��
					m_nNS100m[i+1] = m_nNS[m_nNodeTrace[i]];
				}
			}
//		}


//		if(nVal == 700){
//			if(nTurn > DEF_WAV_STRAIGHT){
//				if(bOK == TRUE){
//					m_nEW700m[i+1] = po.x;	//700m��O�ʒu
//					m_nNS700m[i+1] = po.y;
//				}
//			}
//		}



	}

}
/**********************************************************************
*	�m�[�hturn�����ݒ�
*	m_nNodeTraceCnt��m_nTurnSide�Ɋi�[�����
**********************************************************************/
void CDijkstra::MakeNodeTurnSide()
{
	if(m_nNodeTraceCnt < 3)return;
	m_nTurnSide[0]=0;					//�J�n�ʒu�͎g�p���Ȃ�
	m_nTurnSide[m_nNodeTraceCnt-1]=0;	//�I���ʒu�͎g�p���Ȃ�

	CCommon comm;
	int i,nEW1,nNS1,nEW2,nNS2,nAngle1,nAngle2,nMoveAngle;
	for(i=1;i<m_nNodeTraceCnt-1;i++){

		if(GetNodeLink(i-1) == FALSE)break;//�O�̃m�[�h�ԋO�Տ��l��
		if(m_nBlkCnt < 2)continue;

		nEW1 = 	m_pNodeLinkBody[m_nBlkCnt-1].nEW;	//�O�̃m�[�h�̍Ō���
		nNS1 = 	m_pNodeLinkBody[m_nBlkCnt-1].nNS;
		nEW2 = 	m_pNodeLinkBody[m_nBlkCnt-2].nEW;
		nNS2 = 	m_pNodeLinkBody[m_nBlkCnt-2].nNS;

		nAngle1 = comm.PointToGpsAngle(nEW1,nNS1,nEW2,nNS2);//EW1,NS1����_��EW2,NS2�����̂f�o�r�p�x�����߂�B



		if(GetNodeLink(i) == FALSE)break;//�w��m�[�h�ԋO�Տ��l��
		if(m_nBlkCnt < 2)continue;

		nEW1 = 	m_pNodeLinkBody[0].nEW;	//�m�[�h�̍ŏ��̋��
		nNS1 = 	m_pNodeLinkBody[0].nNS;
		nEW2 = 	m_pNodeLinkBody[1].nEW;
		nNS2 = 	m_pNodeLinkBody[1].nNS;

		nAngle2 = comm.PointToGpsAngle(nEW1,nNS1,nEW2,nNS2);//EW1,NS1����_��EW2,NS2�����̂f�o�r�p�x�����߂�B

		nMoveAngle = ((nAngle2 - nAngle1)+360)%360 -180;


//TRACE(L"[%d  %d  %d ",nAngle1,nAngle2,nMoveAngle);
//if(nMoveAngle < 0)TRACE(L"��]\n");
//else              TRACE(L"�E]\n");
		m_nTurnSide[i] = nMoveAngle;		//�ύX�p�x�ݒ�(-:�� +:�E)
	}


	WabPlayInit();		//�m�[�hturn���������ē��ς݃t���O������(���ē�)

}
/**********************************************************************
*	�m�[�hturn���������ē��ς݃t���O������(���ē�)
**********************************************************************/
void  CDijkstra::WabPlayInit()
{
	int i;
	for(i=0;i<m_nNodeTraceCnt;i++){
		m_bWavPlay700[i] = FALSE;		//�m�[�hturn����700m��O�����ē��ς݃t���O������(���ē�)
		m_bWavPlay100[i] = FALSE;		//�m�[�hturn����100m��O�����ē��ς݃t���O������(���ē�)
	}
}
/**********************************************************************
*	�w��m�[�h�̐ڑ����m�[�h���l��
*	return:�ڑ����m�[�h�ԍ�
**********************************************************************/
int  CDijkstra::HlpGetConnectNode(int nTragetNode)
{
	int i,nCnt=0;
	int nTmp[20];							//�P�m�[�h������̍ő�ڑ���
	for(i=0;i<m_nNodeMax-1;i++){
		if(T[i].end2 == nTragetNode){
			nTmp[nCnt] = T[i].end1;			//�ڑ����Ă���m�[�h�ԍ����i�[
			nCnt++;
			continue;
		}

		if(T[i].end1 == nTragetNode){
			nTmp[nCnt] = T[i].end2;			//�ڑ����Ă���m�[�h�ԍ����i�[
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

	if(nCnt == 1)return nTmp[0];			//�ڑ����͂P�����Ȃ̂Ŕ�r�Ȃ�

	//----�����ڑ������邽�ߍł��Z�������̂��̂��l������
	int nPos=0;
	for(i=1;i<nCnt;i++){
		if(dstar[nPos] > dstar[nTmp[i]])nPos = i;
	}
	return nTmp[nPos];
}
/**********************************************************************
*	�������s�i�m�[�hNo.�O���n�_�Ƃ��Č�������j
*  �ߓ_��n, �}��m, �}�W��E�����O���t�̎n�_s=0����̍ŒZ�H�؂����߂�
*	�_�C�N�X�g���̃A���S���Y��; ���ʂ�T�i�ŒZ�H�؁j��dstar�i�ŒZ�H���j
*	�ɓ����
*	return�@0:���� -1:�ُ�
**********************************************************************/
int  CDijkstra::dijkstra(int n, int m)
{
	int i, j, k,  u, v1, v2, vadj, nh,nRet=0;

	int *P;	      /* u��P�̗v�f�Ȃ�P[u]==1�A�����Ȃ����0 */
	int *loc;     /* �ߓ_u�̓q�[�v��loc[u]�Ԗڂ̃Z���Ɋi�[ */
	int *edge;    /* edge[v]�͍ŒZ�H�؂ɂ�����v�ւ̎}�̌�� */
	P		 = new int[N];
	loc		 = new int[N];
	edge	 = new int[N];
	float du;
	static struct cell *adjlist[N];      /* �O���t�̗אڃ��X�g */
	struct cell *r, *q, *p;  
	struct value vh, vmin; 
	struct value *heap;       /* (dstar[u], u)�̃q�[�v */
	heap	 = new struct value[N-1];


	P[0]=1;                       /* P�̏����� */
	for(j=1; j<n; j++) P[j]=0;
	for(j=0; j<n; j++) {adjlist[j]=NULL; loc[j]=-1;}  
                               /* �אڃ��X�g�̍\�� */

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
	u=0;                          /* �ߓ_0����J�n */

	du=0.0; dstar[u]=0.0;
	for(k=0; k<n-1; k++){          /* �_�C�N�X�g���@�̔��� */
	    p=adjlist[u];              /* u�ɐڑ�����}�ɂ��q�[�v�̍X�V�i�X�e�b�v1(i)) */
	    while(p!=NULL){
			vadj=p->adj;            /* vadj��u�ɗאڂ���ߓ_ */
			if(P[vadj]==0){ 
				if(loc[vadj] == -1){  /* vadj���q�[�v�ɓ���� */
					if(HlpChkNodeInfo(u,vadj) == FALSE)vh.d=99999;	//����ʍs�A�E���܋֎~���̏ꍇ�͖����ɂ���
					else                               vh.d=du+E[p->edge].d;
					vh.node=vadj;
					edge[vadj]=p->edge;
					insert(vh, heap, loc, nh);
					nh++;
				}
				else{           /* ���łɃq�[�v�ɂ���vadj�̍X�V */
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
				TRACE(L"���ڑ��m�[�h�A�܂��͏d���o�^������܂�\n");
#else
				AfxMessageBox(L"���ڑ��m�[�h�A�܂��͏d���o�^������܂�");
#endif
				nRet =  -1;
				goto TAG_EXIT;
			}
			p=p->next;
		}//end while
		deletemin(heap, loc, nh,&vmin); /* �X�e�b�v1(ii): vmin�̑I�� */
		nh--;             /* u=vmin.node��P�ֈړ� */

		u=vmin.node;
		du=vmin.d;
		P[u]=1; dstar[u]=du;
		T[k]=E[edge[u]];     /* edge[u]���ŒZ�H�؂֓���� */


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
*	�q�[�v A[0] to A[n-1] �֗v�f x �̑}��.
**********************************************************************/
void CDijkstra::insert(struct value vh, struct value *A, int *loc, int n)
{
 A[n].d=vh.d;
 A[n].node=vh.node;
 loc[A[n].node]=n;
 upmin(n, A, loc, n+1);
}
/**********************************************************************
*	�q�[�v A[0] to A[n-1] ���� min �v�f�̏���.
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
*	�v�f A[i] �����փq�[�v�̐����̉�.
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
*	�v�f A[i] ���牺�փq�[�v�̐����̉񕜁G �Ō�̗v�f��A[n-1].
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
*	�q�[�vA�ɂ�����\����A[i]��A[j]�̌���
**********************************************************************/
void CDijkstra::swap(int i, int j, struct value *A, int *loc)
{
	struct value temp;
	temp=A[i]; A[i]=A[j]; A[j]=temp;
	loc[A[i].node]=i; loc[A[j].node]=j;  /* loc�̍X�V */
}
/********************************************************
*	����ʍs�f�[�^���[�h
********************************************************/
BOOL CDijkstra::LoadOneWay(CString strPath)
{
	int i,ii;
//	for(i=0;i<DEF_NODE_MAX;i++){				//�m�[�h���e�[�u��������
//		m_NodeInfo[i].nConnectNodeNo[0] = -1;	//���g�p���
//	}

	memset(&m_NodeInfo[0].nConnectNodeNo[0],-1,sizeof(m_NodeInfo));	//���g�p���

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
			if(m_NodeInfo[a.nFromNode].nConnectNodeNo[ii] == -1){	//�ݒ�ʒu
				m_NodeInfo[a.nFromNode].nConnectNodeNo[ii] = a.nToNode;//�ݒ�
				break;
			}
		}

	}

	file.Close();
	return TRUE;
}
/********************************************************
*	�m�[�h�ʒu��񃍁[�h
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

	m_nNodeMax=i;//�m�[�h��
	file.Close();
	return TRUE;
}
/********************************************************
*	�m�[�h�ԋO�Տ�񃍁[�h
********************************************************/
BOOL CDijkstra::LoadNodeLink(CString strPath)
{
	return m_LinkIndex.Create(strPath);
}
/********************************************************
*	�w��m�[�h�ԋO�Տ��l��
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
//			m_nEW[m_nNodeTrace[nTraceListPose]],m_nNS[m_nNodeTrace[nTraceListPose]],&m_nBlkCnt);	//�t�Ō���

//			if(nBodyPos == -1){


//#ifdef _DEBUG
				TRACE(L"*******GetNodeLink()err");
//#else
//				AfxMessageBox(L"GetNodeLink()err");
//#endif
				return FALSE;
//			}
	}


	m_LinkIndex.GetBody(nBodyPos,m_nBlkCnt);		//Body�l��
	m_pNodeLinkBody = m_LinkIndex.m_pBody;			//Body�ւ̃|�C���^�ݒ�

	return TRUE;
}
/********************************************************
*	�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l��
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
*	�ݒ��Ԃ�ݒ肷��
********************************************************/
void CDijkstra::SetStatus(int nStatus)
{
	m_nStatus =  nStatus;					//�ݒ���
}
/********************************************************
*	�ݒ��Ԃ��l������
********************************************************/
int CDijkstra::GetStatus()
{
	return m_nStatus;
}

/********************************************************
*	���[�g�͂��ꌟ��
*	(�\�肷�鎟�m�[�h�ȊO�̃m�[�h��ʉ߂�����)
********************************************************/
/*BOOL CDijkstra::ChkRouteOut(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return TRUE;
//--------���݂Ǝ��m�[�h�ʒu�l��------------------------------------------
//	m_nNextNodeEW=0;
//	m_nNextNodeNS=0;

	int i,nNodeEW=0,nNodeNS=0,nNextNodeNo,nNextNodeEW,nNextNodeNS;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay700[i] == TRUE)continue;		//�m�[�hturn���������ē��ς�(�ʉ߂���)
		if(m_bWavPlay100[i] == TRUE)continue;		//�m�[�hturn���������ē��ς�(�ʉ߂���)

		nNextNodeNo	  = m_nNodeTrace[i];
		nNextNodeEW = m_nEW[nNextNodeNo];
		nNextNodeNS = m_nNS[nNextNodeNo];
		nNodeEW = m_nEW[m_nNodeTrace[i-1]];
		nNodeNS = m_nNS[m_nNodeTrace[i-1]];
		break;
	}

//	if(m_nNextNodeEW == 0)return TRUE;						//�ݒ�Ȃ�


//--------���m�[�h�ɗאڂ���m�[�h���ƈʒu�l��------------------------------------------
	if(nNextNodeEW != m_nNextNodeEW || nNextNodeNS != m_nNextNodeNS){	//�O��ƈ���Ă�����
		m_nNextNodeEW = nNextNodeEW;
		m_nNextNodeNS = nNextNodeNS;
		CTool tool;
		m_nNearCnt=0;
		for(i=0;i<m_nNodeMax-1;i++){
//			if(T[i].end1 != nNextNodeNo && T[i].end2 != nNextNodeNo)continue;
			if(tool.PointToMeter((long)m_nEW[i],(long)m_nNS[i],(long)m_nNextNodeEW,(long)m_nNextNodeNS) > 3000)continue;	//3000m�ȏ�͂Ȃ�Ă���
			m_nNearNodeEW[m_nNearCnt] = m_nEW[i];		//�אڃm�[�h�ʒu�ݒ�
			m_nNearNodeNS[m_nNearCnt] = m_nNS[i];
			m_nNearCnt++;								//�אڃm�[�h���ݒ�
			if(m_nNearCnt == 100)break;				//����ȏ�ݒ�s�\
		}
	}
//--------���[�g�͂��ꌟ��------------------------------------------
	int ii;
	for(i=0;i<m_nNearCnt;i++){
//TRACE(L"%d %d\n",m_nNearNodeEW[i]-nEW,m_nNearNodeNS[i]-nNS);
		if(abs(m_nNearNodeEW[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue;
		if(abs(m_nNearNodeNS[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue;

		for(ii=0;ii<m_nNearCnt;ii++){
			if(m_nNearNodeEW[ii] == nNodeEW && m_nNearNodeNS[ii] == nNodeNS)return TRUE;	//���m�[�h
		}

//		WavPlay(WAV_ROUTE_OUT);						//���[�g�͂���
		return FALSE;
	}


	return TRUE;
}
*/
/********************************************************
*	�����Đ�(700m��O)
********************************************************/
/*void CDijkstra::PlaySound700(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return;

	int i;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay700[i] == TRUE)continue;	//�m�[�hturn���������ē��ς�
//		nVal = abs(m_nEW700m[i]-nEW + m_nNS700m[i]-nNS); 	//100m��O�ʒu
//		if(nVal > 1000)continue;
		if(abs(m_nEW700m[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue; 	//700m��O�ʒu
		if(abs(m_nNS700m[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue; 	//700m��O�ʒu

		m_bWavPlay700[i] = TRUE;				//�m�[�hturn���������ē��ς�
		//�m�[�hturn����
		if(i == m_nNodeTraceCnt-1){continue;}	//�I���͂Ȃ�
		if(m_nTurnSide[i] > 0){	//�E
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT)WavPlay(WAV_STRAIGHT_700);	//���i
			else if(m_nTurnSide[i] < DEF_WAV_LITTLE_TURN)WavPlay(WAV_LITTLE_RIGHT_700);	//���E
			else WavPlay(WAV_RIGHT_700);	//�E
		}
		else{					//��
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT)WavPlay(WAV_STRAIGHT_700);	//���i
			else if(m_nTurnSide[i] > -DEF_WAV_LITTLE_TURN)WavPlay(WAV_LITTLE_LEFT_700);	//��⍶
			else WavPlay(WAV_LEFT_700);	//��
		}
	}
}
*/
/********************************************************
*	�����Đ�(100m��O)
*	return -1:�Đ��Ȃ� 0:�Đ� 1:�Đ��Ȃ�(���iɰ��)
********************************************************/
/*int CDijkstra::PlaySound100(int nEW,int nNS)
{
	if(m_nNodeTraceCnt < 3)return -1;

	int i;
	for(i=1;i<m_nNodeTraceCnt;i++){
		if(m_bWavPlay100[i] == TRUE)continue;	//�m�[�hturn���������ē��ς�
//		nVal = abs(m_nEW100m[i]-nEW + m_nNS100m[i]-nNS); 	//100m��O�ʒu
//		if(nVal > 1000)continue;
//TRACE(L"[[[[[%d  %d\n",m_nEW100m[i]-nEW,m_nNS100m[i]-nNS);

		if(abs(m_nEW100m[i]-nEW) > DEF_CHK_EWNS_AREA_EW)continue; 	//100m��O�ʒu
		if(abs(m_nNS100m[i]-nNS) > DEF_CHK_EWNS_AREA_NS)continue; 	//100m��O�ʒu


		m_bWavPlay100[i] = TRUE;				//�m�[�hturn���������ē��ς�
		m_bWavPlay700[i] = TRUE;				//�m�[�hturn���������ē��ς�

		//�m�[�hturn����
		if(i == m_nNodeTraceCnt-1){WavPlay(WAV_END);continue;}	//�I��

		if(m_nTurnSide[i] > 0){	//�E
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT){
				return 1;			
//				WavPlay(WAV_STRAIGHT);	//���i
			}
			else if(m_nTurnSide[i] < DEF_WAV_LITTLE_TURN){
				WavPlay(WAV_LITTLE_RIGHT);	//���E
			}
			else{
				WavPlay(WAV_RIGHT);	//�E
			}
		}
		else{					//��
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT){
				return 1;			
//				WavPlay(WAV_STRAIGHT);	//���i
			}
			else if(m_nTurnSide[i] > -DEF_WAV_LITTLE_TURN){
				WavPlay(WAV_LITTLE_LEFT);	//��⍶
			}
			else{
				WavPlay(WAV_LEFT);	//��
			}
		}
	}

	return 0;
}
*/
/***********************************************************************************
*	waw�Đ�
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
*	�c�苗���l��
*	return �c�苗��(m) ���ݒ莞��-1	
********************************************************/
//int CDijkstra::GetLastDistance(int nEW,int nNS)
//{
//	if(m_nNodeTraceCnt < 3)return -1;

//	CTool tool;
//	int i;
//	for(i=1;i<m_nNodeTraceCnt;i++){
//		if(m_bWavPlay100[i] == TRUE)continue;	//�m�[�hturn���������ē��ς�

//		return m_nDistance[i] + (int)tool.PointToMeter(
//			                          (double)m_nEW[m_nNodeTrace[i]]/DEF_CONVERT,
//									  (double)m_nNS[m_nNodeTrace[i]]/DEF_CONVERT,
//									  (double)nEW/DEF_CONVERT,
//									  (double)nNS/DEF_CONVERT);

//	}

//	return 0;
//}

/********************************************************
*	���[�g��̒ʉ߃m�[�h�l��
*	return -1:�m�[�h��łȂ� 0..m_nNodeTraceCnt
*	(�߂�)
*	*npPassNode:�ʉ߃m�[�h�ԍ�
*	*npNextNode:�ʉ߃m�[�h�̎��m�[�h�ԍ�
*	*npNextTurn:���E���ܕ���
*	*npNextTurnDistance:���E���܂܂ł̋���
*	*bp100m:�E���܃m�[�h100m��O�ʉߒ��׸�(�m�[�h�Ԃ�100m�Ȃ��ꍇ�͍ő勗����)
*	*np100mPos:�E���܃m�[�h100m��O�ʉߒ�����m_nNodeTraceCnt�ԍ�
********************************************************/
int CDijkstra::GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,
						   int *npNextTurn,int *npNextTurnDistance,
						   BOOL *bp100m,int *np100mPos)
{
	*bp100m = FALSE;
	if(m_nNodeTraceCnt < 3)return -1;
	int n1,n2,n3,n4,n;
	int i,ii;
	for(i=0;i<m_nNodeTraceCnt;i++){		//0�`���ƊJ�n�ʒu���܂�
		n = m_nNodeTrace[i];
		n1 = abs(m_nEW[n] - nEW); 
		n2 = abs(m_nNS[n] - nNS); 

		if(m_nEW100m[i+1] != 0){	//100m��O�ʒu
			n3 = abs(m_nEW100m[i+1] - nEW); 
			n4 = abs(m_nNS100m[i+1] - nNS); 
			if(n3 <= DEF_NODE_PASS_AREA && n4 <= DEF_NODE_PASS_AREA){
				*bp100m = TRUE;
				*np100mPos=i+1;
			}
		}

		if(n1 > DEF_NODE_PASS_AREA || n2 > DEF_NODE_PASS_AREA)continue;		//�m�[�h��ʉߔ���
		//---------���̉E���ܕ���----------------------------
		*npNextTurn = 0;		//����s�\(���i)
		*npNextTurnDistance = 0;//����s�\
		if(i != m_nNodeTraceCnt-1)	*npNextTurn = m_nTurnSide[i+1];
		for(ii=i+1;ii<m_nNodeTraceCnt;ii++){
			if(m_nTurnSide[ii] < DEF_WAV_STRAIGHT  && 
			   m_nTurnSide[ii] > -DEF_WAV_STRAIGHT){//���i
				continue;
			}
			*npNextTurn = m_nTurnSide[ii];
			*npNextTurnDistance = m_nDistance[i] - m_nDistance[ii];		//���̉E����ɰ�ނ܂ł̋���
			break;
		}
		//-----------------------------------------------------
		*npPassNode = m_nNodeTrace[i];		//�m�[�h��ʉ�
		if(i != m_nNodeTraceCnt-1)*npNextNode = m_nNodeTrace[i+1];	//���m�[�h
		else                      *npNextNode=-1;					//����s�\
		return i;
	}
	return -1;//�m�[�h��łȂ�
}
/********************************************************
*	�c�苗���l��(�m�[�h�ԒP��)
********************************************************/
int CDijkstra::GetLasDistance(int nNodeTracePos)
{
	return m_nDistance[nNodeTracePos];
}
/********************************************************
*	�w��m�[�h�ԋ����l��
********************************************************/
int CDijkstra::GetNodeDistance(int nFromNodeTracePos,int nToNodeTracePos)
{
	return  m_nDistance[nFromNodeTracePos] - m_nDistance[nToNodeTracePos];
}
/********************************************************
*	�w��nNodeTracePos�܂ł̋����l��
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
*	��ԋ߂����[�g��m�[�h�ԍ��l��
*   *npLastDistance:�c�苗��(�߂�)
*   *npNextDistance:��ɰ�ނ܂ł̋����iɰ�ފԁj(�߂�)
*	return �m�[�h�ԍ� -1�̏ꍇ�͊Y���Ȃ�
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


//	if(m_nTurnSide[nNode] > 0){	//�E
//		if(m_nTurnSide[nNode] < DEF_WAV_STRAIGHT){//���i
//			bStraight=TRUE;
//		}
//	}
//	else if(m_nTurnSide[nNode] > -DEF_WAV_STRAIGHT){//���i
//		bStraight=TRUE;
//	}


	*npLastDistance = m_nDistance[nNode];		//�c�苗��

	*npNextDistance = m_nDistance[nNode] - m_nDistance[nNode+1];		//��ɰ�ނ܂ł̋���
//	*bpStraight		= bStraight;				//���i�����H

	
	int nCnt=0;
	for(i=nNode;i<m_nNodeTraceCnt;i++){		//���i���ǂ��܂ő������H
		if(m_nTurnSide[i] > 0){	//�E
			if(m_nTurnSide[i] < DEF_WAV_STRAIGHT){//���i
				nCnt++;
				continue;
			}
		}
		else{						//��
			if(m_nTurnSide[i] > -DEF_WAV_STRAIGHT){//���i
				nCnt++;
				continue;
			}
		}
		break;
	}
	if(nCnt > 1){
		*npNextDistance = m_nDistance[nNode] - m_nDistance[nNode+1+nCnt];		//���̉E����ɰ�ނ܂ł̋���
	}




	return m_nNodeTrace[nNode];
}
/********************************************************
*	�����ē��L���ݒ�
********************************************************/
void CDijkstra::SetSound(BOOL bMode)
{
	m_bSound = bMode;
}
/********************************************************
*	����ʍs�A�E���܋֎~���̏ꍇ�͖����ɂ���
*	return TRUE:�����ɂ��Ȃ� FALSE:�����ɂ���
********************************************************/
BOOL CDijkstra::HlpChkNodeInfo(int nFromNode,int nToNode)
{
//����ʍs�̂ݑΉ�

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

