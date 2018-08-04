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

#define 	DIJKSTRA_ST_CLR				0			//�N���A���(���)
#define 	DIJKSTRA_ST_SET_START		1			//�J�n�ʒu�ݒ���
#define 	DIJKSTRA_ST_SET_END			2			//�I���ʒu�ݒ���
#define 	DIJKSTRA_ST_ROUTE			3			//���[�g�ݒ���

#define		DIJKSTRA_NODE_TRACE_MAX		1000		//���[�g��̃m�[�h�ő吔
#define		DEF_CHK_EWNS_AREA_EW		1000		//�ʒu����͈́i�傫���قǔ���G���A���L���Ȃ�j
#define		DEF_CHK_EWNS_AREA_NS		20000		//�ʒu����͈́i�傫���قǔ���G���A���L���Ȃ�j

#define		DEF_NODE_PASS_AREA			2000		//�m�[�h��ʉߔ���i�傫���قǔ���G���A���L���Ȃ�j

class CDijkstra  
{
public:
	CDijkstra();
	virtual ~CDijkstra();
	void Load(CString strPath,int *npConnectMax,int nCountry);
	BOOL Dijkstra(int m);							//�S�m�[�h�̍ŒZ��Ԋl��
	void  GetResultNodeList(int nNode);				//�w��m�[�h�ƂO�m�[�h�Ƃ̍ŒZ�ڑ��m�[�h���X�g�쐬
	void  MakeDistanceList();						//�e�m�[�h����̎c�苗�����X�g�ݒ�
	void  MakeInfoPointList();						//�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�
	void MakeNodeTurnSide();						//�m�[�hturn�����ݒ�
	void WabPlayInit();								//�m�[�hturn���������ē��ς݃t���O������(���ē�)
	void SetStatus(int nStatus);					//�ݒ��Ԃ�ݒ肷��
	int  GetStatus();								//�ݒ��Ԃ��l������
//	BOOL ChkRouteOut(int nEW,int nNS);				//���[�g�͂��ꌟ��
//	void PlaySound700(int nEW,int nNS);				//�����Đ�(700m��O)
//	int PlaySound100(int nEW,int nNS);				//�����Đ�(100m��O)
//	int  GetLastDistance(int nEW,int nNS);			//�c�苗���l��
	void SetSound(BOOL bMode);						//�����ē��L���ݒ�
	void WavPlay(CString strFname);					//waw�Đ�
	BOOL HlpChkNodeInfo(int nFromNode,int nToNode);//����ʍs�̏ꍇ�͖����ɂ���

	int m_nNodeTraceCnt;							//�������ʃ��[�g�̃m�[�h��
	int m_nNodeTrace[DIJKSTRA_NODE_TRACE_MAX];		//�������ʃ��[�g�̃m�[�h�i�[�o�b�t�@

	BOOL LoadNodePoint(CString strPath);	//�m�[�h�ʒu��񃍁[�h
	BOOL LoadOneWay(CString strPath);			//����ʍs�f�[�^���[�h
	BOOL LoadNodeLink(CString strPath);		//�m�[�h�ԋO�Տ�񃍁[�h
	BOOL GetNodeLink(int nTraceListPose);	//�w��m�[�h�ԋO�Տ��l��
	int GetNearNode(int nEW,int nNS);		//�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l��
	int GetNearNode2(int nEW,int nNS,int *npLastDistance,int *npNextDistance);//��ԋ߂����[�g��m�[�h�ԍ��l��

	int GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,		//���[�g��̒ʉ߃m�[�h�l��
						   int *npNextTurn,int *npNextTurnDistance,
						   BOOL *bp100m,int *np100mPos);
	int GetLasDistance(int nNodeTracePos);			//�c�苗���l��(�m�[�h�ԒP��)

	int GetPassNode(int nEW,int nNS,int *npPassNode,int *npNextNode,int *npNextTurn,int *npNextTurnDistance);		//���[�g��̒ʉ߃m�[�h�l��
	int GetNodeDistance(int nFromNodeTracePos,int nToNodeTracePos);//�w��ԋ����l��
	int GetNodeDistance(int nEW,int nNS,int nNodeTracePos);//�w��nNodeTracePos�܂ł̋����l��

	int m_nBlkCnt;							//�m�[�h�ԋO�Տ��body��
	struct_Body *m_pNodeLinkBody;			//�m�[�h�ԋO�Տ��body�f�[�^�ւ̃|�C���^


	int m_nEW[DEF_NODE_MAX];			//�m�[�h�ʒu���
	int m_nNS[DEF_NODE_MAX];			//�m�[�h�ʒu���
	int m_nDistance[DEF_NODE_MAX];		//�I�_�܂ł̎c�苗��
	int m_nEW100m[DEF_NODE_MAX];		//100m��O�ʒu
	int m_nNS100m[DEF_NODE_MAX];
//	int m_nEW700m[DEF_NODE_MAX];		//700m��O�ʒu
//	int m_nNS700m[DEF_NODE_MAX];
	int m_nTurnSide[DEF_NODE_MAX];		//�m�[�hturn����
	BOOL m_bWavPlay700[DEF_NODE_MAX];	//�m�[�hturn����700m��O�����ē��ς݃t���O
	BOOL m_bWavPlay100[DEF_NODE_MAX];	//�m�[�hturn����100m��O�����ē��ς݃t���O
	CLinkIndex m_LinkIndex;				//Link.idx


	int m_nNodeMax;						//�m�[�h��
	int m_nStartNode;					//�J�n�m�[�h
	int m_nEndNode;						//�I���m�[�h

//	int m_nNextNodeEW;					//���m�[�h�ʒu
//	int m_nNextNodeNS;					//���m�[�h�ʒu
//	int m_nNearCnt;						//�אڃm�[�h��
//	int m_nNearNodeEW[100];				//�אڃm�[�h�ʒu
//	int m_nNearNodeNS[100];


private:

//	int nNodeTotal;					//�m�[�h���v��
//	int nConnectTotal;				//�ڑ����v��

	
	int m_nStatus;					//�ݒ���

	struct DIJKSTRA{	//�_�C�N�X�g���@�����p�\����
		int nDistance;				//�ڑ��ԋ���(m)
		int nFromNode;				//�ڑ����m�[�h�ԍ�(0�`)
		int nToNode;				//�ڑ���m�[�h�ԍ�(0�`)
	};//12byte



	#define N DEF_NODE_MAX         //�m�[�h�ő吔
	#define M DEF_NODE_CONNECT_MAX	//�ڑ��ő吔
	#define ZERO 0.0001		//�ۂߌ덷�̋��e�l
	struct edge{			//�\����edge�̒�`
		float d;
//		int d;				//�ڑ��ԋ���(m)
		int end1;			//�ڑ����m�[�h�ԍ�(0�`)
		int	end2;			//�ڑ���m�[�h�ԍ�(0�`)

	};
	struct value{          /* �\����value�̒�` */
		float d;
		int node;
	};
	struct cell{           /* �\����cell�̒�` */
		int adj;
		int edge;
		struct cell *next;
	};

	struct	edge *E;			//�ŒZ�H��T
	struct	edge *T;			//�ڑ����X�gE
	float	*dstar;				//�m�[�h�ւ̍ŒZ�H��
	
	BOOL m_bSound;				//�����ē��L��

	struct OneWayNode{			//����ʍs���R�[�h�\��
	    int nFromNode;
	    int nToNode;
	};

#define NODEINFO_MAX	8
	struct NodeInfo{           /* ɰ�ޏ���` */
		int nConnectNodeNo[NODEINFO_MAX];	//�ő�8ɰ�ސڑ��\ -1�͖���`
//		BYTE cAtr[8];			//In-Out ��` 1���ʍs�\ �Wbitx8byt����`
	};
	struct	NodeInfo m_NodeInfo[DEF_NODE_MAX];	//ɰ�ޏ���`


	/* �֐��̐錾 */
//	void dijkstra(struct edge *E, struct edge *T, float *d,  int n, int m);
	int dijkstra(int n, int m);
	void deletemin(struct value *A, int *loc, int n,struct value *pMin);
	void downmin(int i, struct value *A, int *loc, int n);
	void insert(struct value dj, struct value *A, int *loc,  int n); 
	void upmin(int i, struct value *A, int *loc, int n);
	void swap(int i, int j, struct value *A, int *loc);

	int HlpGetConnectNode(int nTragetNode);	//�w��m�[�h�̐ڑ����m�[�h���l��
	void HlpChg0Node(int nConnectMax);		//�w��m�[�h(�I���m�[�h)�ƂO�m�[�h�����ւ���
	void HlpMakeInfoPointListSub(int nVal);	//�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�sub


	struct structNode1{			//�m�[�h�ʒu���
		int nNode;				//���g�p
		int nEW;
		int nNS;
	};


//	void HlpGetNearNodeSub(int nEWNS,int *npEWNS,int *npNearList,int nListCntMax);	//�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l��sub1
};

#endif // !defined(AFX_DIJKSTRA_H__DF87B3C7_86D5_4E49_B024_8DA3A05B4C16__INCLUDED_)
