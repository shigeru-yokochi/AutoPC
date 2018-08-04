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

    // �I���C�x���g�쐬
    m_hEventStop = ::CreateEvent(NULL, TRUE, FALSE, NULL);

    m_pThread = NULL; // �X���b�h�I�u�W�F�N�g�̃|�C���^�N���A
//	m_bStop = TRUE;
}

CDrawThread::~CDrawThread()
{

   // �I���C�x���g�j��
   ::CloseHandle(m_hEventStop);

}





// �X���b�h�̊J�n
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

	m_nCircumferenceListCnt = nCircumferenceListCnt;	//���ӌ���ITEM��
	m_npCircumferenceListBuf= npCircumferenceListBuf;	//���ӌ���ITEMؽ���̧�ւ��߲��(EW,NS....�̏���)
	m_strpCircumferenceListBuf = strpCircumferenceListBuf;//���ӌ���ITEMؽ���̧�ւ��߲��(����)


//ThreadProc();
//m_pThread = (CWinThread*)1234;
//return;
    // �T�X�y���h��ԂŃX���b�h���쐬
    m_pThread = ::AfxBeginThread(ThreadEntry, (LPVOID)this,
			THREAD_PRIORITY_NORMAL,
			0, CREATE_SUSPENDED, NULL);
  m_pThread->m_bAutoDelete = FALSE;	// �����j���t���O�N���A
    m_pThread->ResumeThread();		// �T�X�y���h����
}


// �X���b�h�̏I��
void CDrawThread::Stop(void)
{

   if(m_pThread == NULL)return;
//m_pThread = NULL;
//return;
    ::SetEvent(m_hEventStop);	// �I���C�x���g�Z�b�g
   
   // �X���b�h�I���҂�
   if ( ::WaitForSingleObject(m_pThread->m_hThread, 2000)
		   				== WAIT_TIMEOUT )
   {
      // �X���b�h������~
      // (��΂ɒ�~����Ȃ� WaitForSingleObject�� INFINITE ���j
      ::TerminateThread(m_pThread->m_hThread, 0xffffffff);
//      AfxMessageBox(L"Thread stoped force");
   }
   
   // �X���b�h�I�u�W�F�N�g�j��
   delete m_pThread;
   ::ResetEvent(m_hEventStop);	// �I���C�x���g�N���A

   m_pThread = NULL;
}


// �X���b�h�J�n�ʒu
UINT _cdecl CDrawThread::ThreadEntry(LPVOID pParam)
{
    CDrawThread* p = (CDrawThread*)pParam;	// ���I�u�W�F�N�g�̎擾
    
    return p->ThreadProc();		// �X���b�h����
}


// �X���b�h����
UINT CDrawThread::ThreadProc()
{
//TAG_START:
//	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	m_pVView2->PaintClr(*m_nBkColorV2);										//�h��Ԃ�
	if(m_bScroll == FALSE){
		m_pVView3->PaintClr(RGB(0,0,0));											//�h��Ԃ�
	}

//	double dfOffset=0.0;
//	if(m_nCountry == COUNTRY_USA)dfOffset = 0.005;							//���S�֕\�����邽�߂̔�����

//---------------GetData-------------------------------------------------------------------------
//	DWORD dwTile[25];
	DWORD dwTile[9];	//3.6.9�p
	DWORD dwTile2[9];	//1..10�p
	m_pVView2->SetCenter(*m_lVClientCenterX,*m_lVClientCenterY);			//�Z���^�[���W�ݒ�
	m_pVView2->SetBase(*m_dfClientCenterEW,*m_dfClientCenterNS);			//�x�[�X���W�ݒ�
	m_pVView2->SetFact(*m_nMapLevel);

	m_pVView2->GetTileNo(*m_nMapLevel,
		*m_dfClientCenterEW,*m_dfClientCenterNS,dwTile,0);			//�^�C���f�[�^�l�� 3,6,9�p
	m_pVView2->GetTileNo(*m_nMapLevel,
		*m_dfClientCenterEW,*m_dfClientCenterNS,dwTile2,1);			//�^�C���f�[�^�l�� 1..10�p

	m_pVView2->GetRec9(m_pRoad,m_pLine,m_pIcon,m_pPoly,
		m_pText,dwTile,dwTile2,*m_nMapLevel);						//9���R�[�h�擾

//---------------�`��-------------------------------------------------------------------------
//m_pWnd->PostMessage(WM_EVENT,EV_THREAD_END);								//�گ�ޏI���ʒm
//return 0;
	
	m_pVView2->PaintPoly(m_pPoly);											//�|���S���`��
	if(m_bScroll == FALSE){
		m_pVView2->PaintRoad(m_pRoad,*m_nMapLevel,m_pVView3->GetDC());		//���H�`��
	}
	else{
		m_pVView2->PaintRoad(m_pRoad,*m_nMapLevel,NULL);					//���H�`��
	}
	m_pVView2->PaintLine(m_pLine);											//Line�`��

	m_pVView2->PaintRoute(*m_nGPSSpeed,	m_pVView3->GetDC(),
		m_pDijkstra,
		m_hICONStart,m_hICONGoal,m_hICONNode,m_hICONNextNode);			//���[�g�������ʕ`��


	m_pVView2->PaintText(m_pText);											//text�`��
	m_pVView2->PaintIcon(m_pIcon,*m_nMapLevel);							//�A�C�R���`��
	m_pVView2->PaintSearchIcon(m_hICONSearch,
		*m_nMapLevel,m_dfCurEW,m_dfCurNS,
		m_nCircumferenceListCnt,m_npCircumferenceListBuf,m_strpCircumferenceListBuf);				//���ӌ������ʃA�C�R���`��


//	g_bV2DrawThreadMainRun = FALSE;


	m_pWnd->PostMessage(WM_EVENT,EV_THREAD_END);								//�گ�ޏI���ʒm
//	m_bStop = TRUE;


    // �I���C�x���g���Z�b�g�����܂Ń��[�v
//    while ( ::WaitForSingleObject(m_hEventStop, 0) == WAIT_TIMEOUT ){
//		if(m_bStop == FALSE)goto TAG_START;
//		::Sleep (1);
//   }
    return 0;
}

