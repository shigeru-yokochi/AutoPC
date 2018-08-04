// AutoPCView.cpp : implementation of the CAutoPCView class
//

#include "stdafx.h"
#include "AutoPC.h"


#include "AutoPCDoc.h"
#include "AutoPCView.h"


#include "NameBody.h"
#include "DlgSearch.h"
#include "DlgMyMap.h"
#include "DlgSystem.h"
#include "DlgCircumference.h"


#include <AFXPRIV.H >


//UINT MyThreadProc(LPVOID pParam);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
IMPLEMENT_DYNCREATE(CAutoPCView, CView)

//STRUCT_THREAD_DRAW_V2 structThreadDrawV2;
//int __cdecl	g_V2DrawThreadMain(STRUCT_THREAD_DRAW_V2 *p);			//V2�`��X���b�h���C��
//BOOL	g_bV2DrawThreadMainRun = FALSE;

//extern STRUCT_THREAD_DRAW_V2 structThreadDrawV2;
//extern BOOL	g_bV2DrawThreadMainRun;


/***********************************************************************************
*	�ݽ�׸�
***********************************************************************************/
CAutoPCView::CAutoPCView()
{
//	m_bV2AutoDrawTimer = FALSE;

	
	m_bDemo				= TRUE;
//	m_pTRACE			= new CTrace;
//	m_pDlgWait			= new CDlgWait;
	m_pDlgInfo			= new CDlgInfo;
	m_pDriveLog			= new CDriveLog;


//	m_nMapLevel			= 8;
	m_nBkColor			= DEFAULT_BACKCOLOR;		//�w�i�F
//	m_dfClientCenterEW	= 127.0;					//����ʒ��S�o�x
//	m_dfClientCenterNS	= 37.5;						//����ʒ��S�ܓx
//	m_dfClientCenterEW	= 126.79609;				//����ʒ��S�o�x
//	m_dfClientCenterNS	= 37.63578;					//����ʒ��S�ܓx
//	m_dfClientCenterEW	= 126.92978;				//����ʒ��S�o�x
//	m_dfClientCenterNS	= 37.49653;					//����ʒ��S�ܓx
//	m_dfClientCenterEW	= 126.98599;				//����ʒ��S�o�x
//	m_dfClientCenterNS	= 37.55895;					//����ʒ��S�ܓx

//---���ϐ��ǂݏo���@�J�n�ܓx�o�x�A�A���O���A�}�b�v���x���AID,Dial,���[�g�ݒ�L��
//	HlpLoadENV(&m_dfClientCenterEW,&m_dfClientCenterNS,
//		&m_nStartAngle,&m_nMapLevel,&m_strID,&m_strDial,&m_nRouteOnOff);

	m_nMapMachOffset	= 0;
	m_dfMapMachOffsetEW = 0;
	m_dfMapMachOffsetNS = 0;
//	m_nMapMachAngle		= 0;

	m_bKeyUP			= TRUE;
	m_bDemoRun			= FALSE;

m_nTestCnt = 1;

	m_pThread			= NULL;						//V2�`��X���b�h
	m_pComm				= NULL;
	m_nDriveLogWriteCnt	= 0;
	m_nKeyInSleepCnt	= 0;
	m_bAutoZoomIn		= FALSE;
	m_bChgMapTimer		= FALSE;
	m_nSaveMapLevel		= 8;						//100m
	m_bAppExit			= FALSE;
	m_bWaitThreadStart  = FALSE;
	m_bReceiveGPS		= FALSE;
	m_nStatus			= 1;					//�}�g���N�X�������
	m_strWaitDlgMsg		= "";
	m_bOnline			= FALSE;	//��ײ݃t���O
	m_dfChkGPS_EW		= 0.0;
	m_dfChkGPS_NS		= 0.0;
	m_nChkGPSChkFlg		= 0;

	m_bInitOK			= FALSE;
	m_nSendIDCnt		= 0;		//ID���M�Ǘ��J�E���^

	m_dfRouteStartEW	= m_dfClientCenterEW;	//���[�g�����ʒu�蓮�ݒ�l	
	m_dfRouteStartNS	= m_dfClientCenterNS;

	m_bRas	= FALSE;
	dfSaveGPSEW = 0;
//	m_nLastDistance		= -1;		//�c�苗��
	m_nDistanceTMP		= 0;		//�c�苗��
	m_nNextDistance		= 0;		//��ɰ�ނ܂ł̋����iɰ�ފԁj
//	m_nSaveLastDistance = -1;		//�c�苗��(�ۑ��p)

//	m_nThreadDeleteWatchCnt=0;//�گ�ޏI���Ď��J�E���^(�w��l�ɒB�����ꍇ�ͽگ�ނ������I������B)
	m_p232cReceiveBuf	= new char[COM_RECEIVE_BUF_SIZE];
	m_pSoc = NULL;

	m_nMenuStatusRoute		= 1;	//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j

	m_nCountry = -1;			//���ݒ�
//	m_bScaleUp				= FALSE;
	m_nCircumferenceListCnt = 0;	//���ӌ���ITEM��
	m_npCircumferenceListBuf = NULL;
	m_strpCircumferenceListBuf = NULL;
	m_nNearNode = -1;				//��ԋ߂��m�[�h�ԍ�
	m_bRerouteTimer = FALSE;		//reroute�N����ώ��s����׸�
	m_nPassNode = -1;			//�ʉߍς݃m�[�h
	m_nSave100mPos=-1;			//100m��O�ʉ�pos(�O��ʂ����ʒu)


}
/***********************************************************************************
*	�޽�׸�
***********************************************************************************/
CAutoPCView::~CAutoPCView()
{
	delete m_pRoad;
	delete m_pIcon;
	delete m_pText;
	delete m_pPoly;
	delete m_pLine;

//	delete m_pDlgMenu;
//	delete m_pDlgWait;
	delete m_pDlgInfo;
	delete m_pDriveLog;
//	delete m_pDB;
//	delete m_pRS;
	delete m_pGPS;
//	delete m_pTRACE;
//	delete m_pSearch2;
	delete m_pSearchID;
//	delete m_pMapLevel;
//	delete m_pRoute;
	delete m_pDial;
	delete m_pRasEntry;

	delete m_pThread;

	delete [] m_p232cReceiveBuf;
	if(m_npCircumferenceListBuf != NULL)delete [] m_npCircumferenceListBuf;
	if(m_strpCircumferenceListBuf != NULL)delete [] m_strpCircumferenceListBuf;

}
/***********************************************************************************
*	ү����ϯ��
***********************************************************************************/
BEGIN_MESSAGE_MAP(CAutoPCView, CView)
	ON_MESSAGE(WM_DLG_CLOSE, CAutoPCView::OnDlgClose)
	ON_MESSAGE(WM_EVENT, CAutoPCView::OnEvent)
	//{{AFX_MSG_MAP(CAutoPCView)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(ID_DEMO_START, OnDemoStart)
	ON_COMMAND(ID_DEMO_STOP, OnDemoStop)
	ON_COMMAND(ID_ROUTE_SEARCH, OnRouteSearch)
	ON_COMMAND(ID_ROUTE_CLR, OnRouteClr)
	ON_COMMAND(ID_ROUTE_START, OnRouteStart)
	ON_COMMAND(ID_ROUTE_END, OnRouteEnd)
	ON_UPDATE_COMMAND_UI(ID_ROUTE_START, OnUpdateRouteStart)
	ON_UPDATE_COMMAND_UI(ID_ROUTE_SEARCH, OnUpdateRouteSearch)
	ON_UPDATE_COMMAND_UI(ID_ROUTE_END, OnUpdateRouteEnd)
	ON_UPDATE_COMMAND_UI(ID_ROUTE_CLR, OnUpdateRouteClr)
	ON_COMMAND(ID_THIS_PLACE, OnThisPlace)
	ON_COMMAND(ID_ROUTE_RE_SEARCH, OnRouteReSearch)
	ON_COMMAND(ID_MYMAP_SET, OnMymapSet)
	ON_COMMAND(ID_MYMAP_GET, OnMymapGet)
	ON_UPDATE_COMMAND_UI(ID_ROUTE_RE_SEARCH, OnUpdateRouteReSearch)
	ON_UPDATE_COMMAND_UI(ID_DEMO_START, OnUpdateDemoStart)
	ON_UPDATE_COMMAND_UI(ID_DEMO_STOP, OnUpdateDemoStop)
	ON_COMMAND(ID_SEARCH_STRUCT, OnSearchStruct)
	ON_COMMAND(ID_SYSTEM, OnSystem)
	ON_COMMAND(ID_SEARCH_CIR, OnSearchCir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	���ޯ�ޗp
***********************************************************************************/
#ifdef _DEBUG
void CAutoPCView::AssertValid() const
{
	CView::AssertValid();
}
void CAutoPCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CAutoPCDoc* CAutoPCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoPCDoc)));
	return (CAutoPCDoc*)m_pDocument;
}
#endif //_DEBUG


/***********************************************************************************
*	��������
***********************************************************************************/
void CAutoPCView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	SetTimer(TO_INIT,TO_VAL_INIT,NULL);				//�N�������҂����
	PostMessage(WM_EVENT,EV_INIT);
}
/***********************************************************************************
*	��������
***********************************************************************************/
void CAutoPCView::HlpInit() 
{
	SetFileFolder();							//������ɍ������t�@�C���t�H���_����ݒ�
	m_pDriveLog->SetDataPath(m_strDataPath);	//�f�[�^�p�X���ݒ�

//---���ϐ��ǂݏo���@�J�n�ܓx�o�x�A�A���O���A�}�b�v���x���AID,Dial,���[�g�ݒ�L��,�V�X�e�����ݒ�l
	HlpLoadENV(&m_dfClientCenterEW,&m_dfClientCenterNS,
		&m_nStartAngle,&m_nMapLevel,&m_strID,&m_strDial,&m_nRouteOnOff);



	m_Dijkstra.LoadNodePoint(m_strDataPath);				//���[�g�����m�[�h�ʒu��񃍁[�h
	m_Dijkstra.LoadNodeLink(m_strDataPath);					//���[�g�����m�[�h�ԋO�Տ�񃍁[�h
	m_Dijkstra.LoadOneWay(m_strDataPath);					//���[�g��������ʍs�f�[�^���[�h




//#ifdef _DEBUG
//	DebugBreak();
//#endif
//--------��ԃt���O������---------------------------------------------------
	int i;
	for(i=0;i<ST_ITEM_MAX;i++){
		m_bMainStatus[i] = FALSE;
	}
//-----DEBUG�p--------------------------------------------------------------------
	SetMainStatus(ST_ROUTE_NODE_VIEW,	FALSE);//���[�g�����m�[�h�\��(debug�p)
	SetMainStatus(ST_GPS_TRACE,			FALSE);//GPS���g���[�X(debug�p)
//	SetMainStatus(ST_SAVE_ROUTE_DATA,	FALSE);//���[�g�����f�[�^�ۑ�(debug�p)
//	SetMainStatus(ST_SET_ROUTE_DATA,	FALSE);//���[�g�����f�[�^�ݒ�(debug�p)


//---------------------------------------------------------------------------
	SetMainStatus(ST_SCROLL,			FALSE);//�X�N���[�����[�h
//----------------TRACE�L��---------------------------------------------
//	m_bTRACE = TRUE;
//	m_pDriveLog->SetTrace(m_pTRACE);
//	m_VView2.SetTRACE(m_pTRACE);
//-----------------------------------------------------------------
//	m_pSearch2			= new CSearch2(&m_strSearchMsg2,&m_dfClientCenterEW,&m_dfClientCenterNS);
	m_pSearchID			= new CSearchID(&m_StructSearchID);
//	m_pMapLevel			= new CMapLevel(m_pTRACE);
//	m_pRoute			= new CRoute(m_pTRACE);
	m_pDial				= new CDial();
	m_pRasEntry			= new CRasEntry();
//	m_pDlgMenu			= new CDlgMenu(m_pTRACE);
	m_pGPS				= new CGPS(1,m_nCountry);
	m_pRoad				= new CRoad(m_strDataPath);	//���H�\�z
	m_pIcon				= new CIcon(m_strDataPath);	//�A�C�R���\�z
	m_pText				= new CText(m_strDataPath);	//�e�L�X�g�\�z
	m_pPoly				= new CPoly(m_strDataPath);	//�|���S���\�z
	m_pLine				= new CLine(m_strDataPath);	//LINE�\�z

	//------�`��گ�޸׽�\�z------------------------
	m_pThread = new CDrawThread(this,m_pRoad,m_pPoly,m_pIcon,m_pText,m_pLine,
									&m_VView2,&m_VView3);

//	m_pRS = new CRouteSearch(m_pTRACE);

//#ifdef DATA_SQL
//	int nErr = m_pRS->Init();
//	if(nErr < 0){					//������
//		CString str;
//		str.Format(_T("DB INIT ERR[%d]"),nErr);
//		MessageBox(str);
//		GetOwner()->PostMessage(WM_EVENT,EV_APP_EXIT);
//		return;
//	}
//#endif

//	m_pDB	= new CDataBase();
//#ifdef DATA_SQL
//	int nErr = m_pDB->Init();
///	if(nErr < 0){					//������
//		CString str;
//		str.Format(_T("DB INIT ERR[%d]"),nErr);
//		MessageBox(L"map data not found.");
//		GetOwner()->PostMessage(WM_EVENT,EV_APP_EXIT);
//		return;
//	}
//#endif

//-------------�A�C�R���S���ǂݍ���----------------------------------------------
	m_pIcon->LoadIconAll();

	m_hCarIcon		= AfxGetApp()->LoadIcon(IDI_DEFAULT);
	m_hGPS_NON_Icon	= AfxGetApp()->LoadIcon(IDI_GPS_NON);
	m_hGPS_2D_Icon	= AfxGetApp()->LoadIcon(IDI_GPS_2D);
	m_hGPS_3D_Icon	= AfxGetApp()->LoadIcon(IDI_GPS_3D);
	m_hSearch_Icon	= AfxGetApp()->LoadIcon(IDI_SEARCH);
	m_hCross_Icon	= AfxGetApp()->LoadIcon(IDI_CROSS);
	m_hArow_Icon	= AfxGetApp()->LoadIcon(IDI_AROW);
	m_hMap01_Icon	= AfxGetApp()->LoadIcon(IDI_MAP01);
	m_hMap02_Icon	= AfxGetApp()->LoadIcon(IDI_MAP02);
	m_hMap03_Icon	= AfxGetApp()->LoadIcon(IDI_MAP03);
	m_hMap04_Icon	= AfxGetApp()->LoadIcon(IDI_MAP04);
	m_hMap05_Icon	= AfxGetApp()->LoadIcon(IDI_MAP05);
	m_hMap06_Icon	= AfxGetApp()->LoadIcon(IDI_MAP06);
	m_hMap07_Icon	= AfxGetApp()->LoadIcon(IDI_MAP07);
	m_hMap08_Icon	= AfxGetApp()->LoadIcon(IDI_MAP08);
	m_hMap09_Icon	= AfxGetApp()->LoadIcon(IDI_MAP09);
	m_hMap10_Icon	= AfxGetApp()->LoadIcon(IDI_MAP10);
	m_hGoal_Icon	= AfxGetApp()->LoadIcon(IDI_GOAL);
	m_hPoint_Icon	= AfxGetApp()->LoadIcon(IDI_POINT);
	m_hNode_Icon	= AfxGetApp()->LoadIcon(IDI_NODE);
	m_hNextNode_Icon= AfxGetApp()->LoadIcon(IDI_NEXT_NODE);

	m_hDemo_Icon	= AfxGetApp()->LoadIcon(IDI_DEMO);
	m_hSound_Icon= AfxGetApp()->LoadIcon(IDI_SOUND);
//	m_hDistance2_Icon= AfxGetApp()->LoadIcon(IDI_DISTANCE2);
	m_hOnline_Icon	= AfxGetApp()->LoadIcon(IDI_ONLINE);
	m_hOffline_Icon	= AfxGetApp()->LoadIcon(IDI_OFFLINE);
	m_hDirection_Icon[0] = AfxGetApp()->LoadIcon(IDI_DIRECTION_N);
	m_hDirection_Icon[1] = AfxGetApp()->LoadIcon(IDI_DIRECTION_NE);
	m_hDirection_Icon[2] = AfxGetApp()->LoadIcon(IDI_DIRECTION_E);
	m_hDirection_Icon[3] = AfxGetApp()->LoadIcon(IDI_DIRECTION_SE);
	m_hDirection_Icon[4] = AfxGetApp()->LoadIcon(IDI_DIRECTION_S);
	m_hDirection_Icon[5] = AfxGetApp()->LoadIcon(IDI_DIRECTION_SW);
	m_hDirection_Icon[6] = AfxGetApp()->LoadIcon(IDI_DIRECTION_W);
	m_hDirection_Icon[7] = AfxGetApp()->LoadIcon(IDI_DIRECTION_NW);

//-------------��ʍ쐬----------------------------------------------
	GetClientRect(&m_RECTClient);						//����ʻ��ފl��
//m_RECTClient.top = 0;
//m_RECTClient.left = 0;
//m_RECTClient.right = 400;
//m_RECTClient.bottom = 234;


	m_POClientCenter.x = m_RECTClient.right /2;			//����ʒ��S
	m_POClientCenter.y = m_RECTClient.bottom /2;

//	HlpSetCenterOffsetCar();							//���S����̎��ԕ\���I�t�Z�b�g�ݒ�
m_nClientCenterOffsetCar=0;//�I�t�Z�b�g�Ȃ�

	m_RECTVview = m_RECTClient;							//���z��ʻ���
//	m_RECTVview.right*=2;
//	m_RECTVview.bottom*=3;
	m_RECTVview.right*=2;
	m_RECTVview.bottom*=2;

	m_POClientCenter_V1.x = m_RECTVview.right  / 2;		//���z��ʒ��S���W
	m_POClientCenter_V1.y = m_RECTVview.bottom / 2;


	m_POClientScrollMax.x = (m_RECTVview.right  - m_RECTClient.right)/2;	//���z��ʂP���۰قł��黲��x
	m_POClientScrollMax.y = (m_RECTVview.bottom - m_RECTClient.bottom)/2;	//���z��ʂP���۰قł��黲��y

	m_POClientScrollMaxV2Draw = m_POClientScrollMax;	//����ʃX�N���[��V2�`��v���T�C�Y
//	m_POClientScrollMaxV2Draw.x /=2;
//	m_POClientScrollMaxV2Draw.y /=2;
//	m_POClientScrollMaxV2Draw.x /=4;
//	m_POClientScrollMaxV2Draw.y /=4;
	m_POClientScrollMaxV2Draw.x /=6;
	m_POClientScrollMaxV2Draw.y /=6;

	m_VView0.Create(this,m_hWnd,m_RECTVview,0);			//V0�쐬
	m_VView1.Create(this,m_hWnd,m_RECTVview,1);			//V1�쐬
	m_VView2.Create(this,m_hWnd,m_RECTVview,2);			//V2�쐬
	m_VView3.Create(this,m_hWnd,m_RECTVview,3);			//V3�쐬	�}�b�v�}�b�`�pV2�ƃy�A
	m_VView4.Create(this,m_hWnd,m_RECTVview,4);			//V4�쐬	�}�b�v�}�b�`�pV1�ƃy�A

	m_VView2.SetAngle(m_nStartAngle);					//�A���O���ݒ�

//-------------���z��ʕ`��----------------------------------------------
	if(m_nRouteOnOff == 1){
//		HlpSetRouteData(m_strDataPath+FILE_ROUTE);			//���[�g�����f�[�^�ݒ�
//m_nRouteOnOff=1;
	}
	else{
		HlpVPaint();
	}
//-------------�Ď���Ͻ���----------------------------------------------
	if(SetTimer(TO_CYCLE_1,TO_VAL_CYCLE_1,NULL) != TO_CYCLE_1){		//��������1
		MessageBox(L"TO_CYCLE_1 Timer err");
	}
	
//	if(SetTimer(TO_GPS_DRAW,TO_VAL_GPS_DRAW,NULL) != TO_GPS_DRAW){		//GPS�f�[�^�`��
//		MessageBox(L"TO_GPS_DRAW Timer err");
//	}
//	if(SetTimer(TO_WATCH_KEY,TO_VAL_WATCH_KEY,NULL) != TO_WATCH_KEY){	//�L�[���͊Ď����
//		MessageBox(L"TO_WATCH_KEY Timer err");
//	}

//	m_Ras.SetTrace(m_pTRACE);

//#ifdef AUTO_PC
//	SendMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n
	PostMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n
//#endif
//	HlpWaitDlg(FALSE);

	if(m_zEnv[3] == 0)	m_Dijkstra.SetSound(TRUE);			//�����ē��L���ݒ�
	else				m_Dijkstra.SetSound(FALSE);
}
/***********************************************************************************
*	��ض��ނ��windows�f�B���N�g���փR�s�[
***********************************************************************************/
void CAutoPCView::HlpMemCard2Windows(CString strFname)
{
	CFile file1,file2;
	char buf[1024];
	int n, i,nLen;

	if(file1.Open(CString(L"\\��� ����\\") + strFname, CFile::modeRead) == FALSE)	return;
	if(file2.Open(CString(L"\\WINDOWS\\") + strFname, CFile::modeCreate | CFile::modeWrite) == FALSE){file1.Close();return;}
	nLen = file1.GetLength();
	for(i=1;;){
		if((n=file1.Read(buf,1024)) <= 0)break;
		file2.Write(buf,n);
	}
	file1.Close();
	file2.Close();
}

/***********************************************************************************
*	�I����
***********************************************************************************/
void CAutoPCView::OnDestroy() 
{
//	if(m_pThread->m_pThread != NULL){
//		HlpTRACE(L"�X���b�h���s���ɂ��I���ł��܂���B");
//		return; //�X���b�h���s��
//	}


	HlpRs232cStop();


	if(m_pSoc != NULL){
		delete m_pSoc;
		m_pSoc = NULL;
	}

//	m_DB.Close();			//���R�[�h�Z�b�g�I�u�W�F�N�g�̃C���^�[�t�F�[�X���

//	KillTimer(TO_V2AUTODRAW);
//	KillTimer(TO_DEMO_RUN);
//	KillTimer(TO_GPS_DRAW);
//	KillTimer(TO_THREAD);
	m_VView0.GetDC()->DeleteDC();
	m_VView1.GetDC()->DeleteDC();
	m_VView2.GetDC()->DeleteDC();
	m_VView3.GetDC()->DeleteDC();
	m_VView4.GetDC()->DeleteDC();

	DestroyIcon(m_hCarIcon);
	DestroyIcon(m_hGPS_NON_Icon);
	DestroyIcon(m_hGPS_2D_Icon);
	DestroyIcon(m_hGPS_3D_Icon);
	DestroyIcon(m_hSearch_Icon);
	DestroyIcon(m_hCross_Icon);
	DestroyIcon(m_hArow_Icon);
	DestroyIcon(m_hMap01_Icon);
	DestroyIcon(m_hMap02_Icon);
	DestroyIcon(m_hMap03_Icon);
	DestroyIcon(m_hMap04_Icon);
	DestroyIcon(m_hMap05_Icon);
	DestroyIcon(m_hMap06_Icon);
	DestroyIcon(m_hMap07_Icon);
	DestroyIcon(m_hMap08_Icon);
	DestroyIcon(m_hMap09_Icon);
	DestroyIcon(m_hMap10_Icon);
	DestroyIcon(m_hGoal_Icon);
	DestroyIcon(m_hPoint_Icon);
	DestroyIcon(m_hNode_Icon);
	DestroyIcon(m_hNextNode_Icon);
	DestroyIcon(m_hDemo_Icon);
	DestroyIcon(m_hSound_Icon);
//	DestroyIcon(m_hDistance2_Icon);
	DestroyIcon(m_hOnline_Icon);
	DestroyIcon(m_hOffline_Icon);

	int i;
	for(i=0;i<8;i++){
		DestroyIcon(m_hDirection_Icon[i]);
	}



	CView::OnDestroy();

}
/***********************************************************************************
*	��ѱ�Ēʒm
***********************************************************************************/
void CAutoPCView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent){
		case TO_CYCLE_1:			//��������1
			PostMessage(WM_EVENT, EV_RECEIVE_NOTIFI);
			break;
//		case TO_WATCH_KEY:			//�L�[���͑҂�
//			PostMessage(WM_EVENT, EV_T7_TO);
//			break;
		case TO_WAIT_THEAD_START:	//�X���b�h�`��҂����
			PostMessage(WM_EVENT, EV_T9_TO);
			break;
//		case TO_GPS_DRAW:		//GPS�f�[�^�`��
//			PostMessage(WM_EVENT, EV_RECEIVE_NOTIFI);
//			break;
//		case TO_APP_EXIT:		//�I���҂����
//			PostMessage(WM_EVENT,EV_APP_EXIT);
//			break;
		case TO_DEMO_RUN:		//�f�����s
			PostMessage(WM_EVENT,EV_STEP_DEMO);
			break;
//		case TO_THREAD:			//�X���b�h�I���Ď����
//			PostMessage(WM_EVENT, EV_T4_TO);
//			break;
//		case TO_AUTO_ZOOM://�I�[�g�X�P�[���I�����
//			PostMessage(WM_EVENT, EV_T6_TO);
//			break;			
		case TO_WAIT_DLG_AUTO_CLOSE:	//WAITDLG�����N���[�Y���
			PostMessage(WM_EVENT, EV_T8_TO);
			break;
		case TO_INIT:					//�N�������҂����
			KillTimer(TO_INIT);
#ifdef AUTO_PC
//	PostMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n
#endif
			m_bInitOK = TRUE;
			break;
		case TO_RAS_CONNECT_CHK:		//RAS�ڑ��Ď�
			if(m_bRas == TRUE){
				if(m_Ras.ChkConnected() == FALSE){
					m_Ras.Close();
					m_bOnline = FALSE;
					m_bRas = FALSE;
					KillTimer(TO_RAS_CONNECT_CHK);
				}
			}
			else{
				KillTimer(TO_RAS_CONNECT_CHK);
			}
			break;

		case TO_REROUTE:		//�ٰċ��Ď����
			m_bRerouteTimer = FALSE;		//reroute�N����ώ��s����׸�
			KillTimer(TO_REROUTE);
			if(m_zEnv[2] == 0){
				OnRouteReSearch();							//�I�[�g�����[�g�ݒ�
			}

			break;
	}

	CView::OnTimer(nIDEvent);
}

/****************************************************************************
*  DLG�۰�ޒʒm
*  wParam:DLG���ޯ��
*  lParam:���낢��
*****************************************************************************/
LONG CAutoPCView::OnDlgClose(UINT wParam, LONG lParam)
{
	CWnd * pWnd;
	switch(wParam){
//		case IDX_DLG_MENU		:pWnd = m_pDlgMenu;		break;
//		case IDX_DLG_WAIT		:pWnd = m_pDlgWait;		break;
		case IDX_DLG_INFO		:pWnd = m_pDlgInfo;		break;
//		case IDX_DLG_TRACE		:pWnd = m_pTRACE;		break;
//		case IDX_DLG_SEARCH2	:pWnd = m_pSearch2;		break;
		case IDX_DLG_SEARCH_ID	:pWnd = m_pSearchID;	break;
//		case IDX_DLG_MAP_LEVEL	:pWnd = m_pMapLevel;	break;
//		case IDX_DLG_ROUTE		:pWnd = m_pRoute;		break;
		case IDX_DLG_DIAL		:pWnd = m_pDial;		break;
		case IDX_DLG_RAS_ENTRY	:pWnd = m_pRasEntry;	break;

		default:return 0L;
	}

	if(pWnd->GetSafeHwnd() == 0)return 0L;			//DLG�͊J���Ă��Ȃ�
	pWnd->DestroyWindow();
	return 0L;
}


/***********************************************************************************
*	�`��
*	�����ł͎���ʂ̕\���������Ȃ�
***********************************************************************************/
void CAutoPCView::OnDraw(CDC* pDC)
{
//	CAutoPCDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	HlpReDraw();
}
/***********************************************************************************
*	���z��ʕ`��
***********************************************************************************/
BOOL CAutoPCView::HlpVPaint()
{
	if(m_bWaitThreadStart == TRUE){			//�`��҂���
		HlpTRACE(L"Now wait thread start.");
		return FALSE;	
	}

	if(HlpV2DrawThreadCreate() == FALSE){//V2�`��X���b�h�J�n
		m_bWaitThreadStart = TRUE;
		if(SetTimer(TO_WAIT_THEAD_START,TO_VAL_WAIT_THEAD_START,NULL) != TO_WAIT_THEAD_START){
			HlpTRACE(L"TO_WAIT_THEAD_START Timer err");
		}
		return FALSE;					
	}
	HlpReDraw();								//�ĕ`��
	m_POClientScrollSave = m_POClientScroll;	//����ʃX�N���[���ʕۑ�

	return TRUE;
}
/***********************************************************************************
*	���z��ʕ`��
***********************************************************************************/
void CAutoPCView::HlpVPaint3()
{
//	HlpTRACE(L"Drawing V2 OK");

//	m_VView2.PaintGrid();								//�O���b�h

	HlpGetDriveLog();									//�O�Օ\���i�t�@�C������j
	m_VView1.Copy(m_VView2.GetDC());//V1�`��(V2��V1�ɺ�߰)
	if(GetMainStatus(ST_SCROLL) == FALSE){	//�X�N���[�����[�h
		m_VView4.Copy(m_VView3.GetDC());//V4�`��(V3��V4�ɺ�߰)
	}
//---------------V2�Ɠ����ɂ���-----------------------------------------------------
	m_VView1.SetAngle(m_nSaveAngle);	//V1�̃A���O���ݒ�
	m_VView1.SetCenter(m_POClientCenter_V1.x,m_POClientCenter_V1.y);	//�Z���^�[���W�ݒ�
	m_VView1.SetBase(m_dfClientCenterSaveEW,m_dfClientCenterSaveNS);			//�x�[�X���W�ݒ�
	m_VView1.SetFact(m_nMapLevel);
//---------------����ʃX�N���[����------------------------
	m_POClientScroll	-= m_POClientScrollSave;


//m_VView1.Copy(m_VView4.GetDC());//V1�`��(V4��V1�ɺ�߰)debug�p

	HlpReDraw();					//�ĕ`��

//	if(GetMainStatus(ST_SCROLL) == TRUE){//�X�N���[�����[�h
//		HlpWaitDlg(FALSE);
//	}


}
/***********************************************************************************
*	V2�`��X���b�h�J�n
***********************************************************************************/
BOOL CAutoPCView::HlpV2DrawThreadCreate()
{
	if(m_pThread->m_pThread != NULL){
		HlpTRACE(L"Useed Thread");
		return FALSE;
	}
	m_nGPSSpeed = m_pGPS->GetSpeed();								//GPS���x


	m_dfClientCenterSaveEW = m_dfClientCenterEW;					//�ۑ�
	m_dfClientCenterSaveNS = m_dfClientCenterNS;
	m_nSaveAngle = m_VView2.GetAngle();




//------------------------------�گ�ފJ�n-------------------------------------------------------
	double dfEW,dfNS;
	m_pGPS->GetENPoint(&dfEW,&dfNS);				//GPS��M�ʒu
//	HlpGetCurEN(&dfEW,&dfNS);						//�J�[�\���ʒu�̈ܓx�o�l��(�f�o�b�O�p)
	m_pThread->Start(m_hSearch_Icon,&m_POClientCenter_V1.x,&m_POClientCenter_V1.y,
						&m_nMapLevel,&m_nBkColor,&m_dfClientCenterEW, &m_dfClientCenterNS,
						m_bMainStatus[ST_SCROLL],
						m_hPoint_Icon,m_hGoal_Icon,m_hNode_Icon,m_hNextNode_Icon,dfEW,dfNS,&m_nGPSSpeed,m_nCountry,
						&m_Dijkstra,
						m_nCircumferenceListCnt,m_npCircumferenceListBuf,m_strpCircumferenceListBuf);


	return TRUE;
}
/***********************************************************************************
*	V2�`��X���b�h�I��
***********************************************************************************/
BOOL CAutoPCView::HlpV2DrawThreadDelete(BOOL bForce/*=FALSE*/)
{
	if(bForce == FALSE && m_pThread->m_pThread == NULL)return FALSE;

	m_pThread->Stop();					//�گ�ޒ�~


//	m_pThread->m_pThread = NULL;

//	HlpTRACE(L"End Thread");

	m_bKeyUP = TRUE;

	HlpVPaint3();
	return TRUE;
}
/***********************************************************************************
*	���z���0������ʂɺ�߰(�]����OnDraw�ɑ���)
***********************************************************************************/
void CAutoPCView::HlpReDraw()
{
	if(m_bInitOK == FALSE){			//�N�������҂�
		HlpDispInit();
		return;			
	}
	HlpV0Draw();					//V0�`��

//-----------�`��(������Ȃ��悤��BitBlt�̂�)-------------------------------------------------
	CDC *pDC;
	pDC=GetDC();

	pDC->BitBlt(0,0,m_RECTClient.right,m_RECTClient.bottom,
		m_VView0.GetDC(),
		0,
		0,
		SRCCOPY);

	ReleaseDC(pDC);
	m_bKeyUP = FALSE;


	//--------ϯ��ϯ��̾�Ċl��----------------------------------------
	if(GetMainStatus(ST_SCROLL) == FALSE){

		double dfEW,dfNS;
		HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��
		dfEW -= m_dfSaveGPSEW;//�}�b�v�}�b�`�I�t�Z�b�g
		dfNS -= m_dfSaveGPSNS;//�}�b�v�}�b�`�I�t�Z�b�g
		if(fabs(dfEW) < 0.001 && fabs(dfNS) < 0.001){
			m_dfMapMachOffsetEW = dfEW;
			m_dfMapMachOffsetNS = dfNS;
		}
	}



}
/***********************************************************************************
*	���z���0���쐬
***********************************************************************************/
void CAutoPCView::HlpV0Draw()
{
	BOOL bScroll = GetMainStatus(ST_SCROLL);
	CString str;
	int nLastDistance;
int aaa=0;
m_nMapMachOffset = 0;		//debug�p

//-----------�}�b�v�}�b�`-------------------------------------------------
	if(m_zEnv[0] == 0){		
//		m_nMapMachOffset = HlpMapMach();
		m_POClientScroll.x += HlpMapMach();

	}
//	else{
//		m_VView2.SetAngle(90);					//�A���O���Œ�
//	}
//-----------v0�`��-------------------------------------------------
	m_VView0.GetDC()->BitBlt(0,0,m_RECTClient.right,m_RECTClient.bottom,
		m_VView1.GetDC(),
//		m_POClientCenter_V1.x - m_POClientCenter.x + m_POClientScroll.x + m_nMapMachOffset,
		m_POClientCenter_V1.x - m_POClientCenter.x + m_POClientScroll.x,
		m_POClientCenter_V1.y - m_POClientCenter.y + m_POClientScroll.y - m_nClientCenterOffsetCar,
		SRCCOPY);
//------------------ICON-------------------------
	HICON hIcon;

	if(bScroll== FALSE)	hIcon = m_hCarIcon;
	else				hIcon = m_hCross_Icon;
	//------����--------------------------------
	m_VView0.GetDC()->DrawIcon(
		m_POClientCenter.x-16,
		m_POClientCenter.y+m_nClientCenterOffsetCar-16,
		hIcon);


//	if(bScroll== FALSE || (bScroll== TRUE && m_bKeyUP == TRUE)){		//�L�[���͂Ȃ���Ă���
		//------GPS���--------------------------------
		if(bScroll == TRUE){
			hIcon = m_hArow_Icon;	
		}
		else{
			if(m_bReceiveGPS == FALSE){
				hIcon = m_hGPS_NON_Icon;
			}
			else{
				switch(m_pGPS->GetStatus()){
					case 4:hIcon = m_hGPS_3D_Icon;break;
					case 2:hIcon = m_hGPS_2D_Icon;break;
					default: hIcon = m_hGPS_NON_Icon;break;
				}
			}
		}
		m_VView0.GetDC()->DrawIcon(
			m_RECTClient.right-40,
			m_RECTClient.top,
			hIcon);
		//------�k�ڕ\��--------------------------------
		switch(m_nMapLevel){
			case 1:  hIcon = m_hMap01_Icon;break;
			case 2:  hIcon = m_hMap02_Icon;break;
			case 3:  hIcon = m_hMap03_Icon;break;
			case 4:  hIcon = m_hMap04_Icon;break;
			case 5:  hIcon = m_hMap05_Icon;break;
			case 6:  hIcon = m_hMap06_Icon;break;
			case 7:  hIcon = m_hMap07_Icon;break;
			case 8:  hIcon = m_hMap08_Icon;break;
			case 9:  hIcon = m_hMap09_Icon;break;
			case 10: hIcon = m_hMap10_Icon;break;
			default:hIcon = NULL;break;
		}

		if(hIcon != NULL){
			m_VView0.GetDC()->DrawIcon(
				m_RECTClient.right-40,
				m_RECTClient.top+30,
				hIcon);
		}
		//------ONLINE��--------------------------------
		if(m_bOnline == TRUE){
			m_VView0.GetDC()->DrawIcon(
				m_RECTClient.right-40,
				m_RECTClient.top+60,
				m_hOnline_Icon);
		}
		else{
			m_VView0.GetDC()->DrawIcon(
				m_RECTClient.right-40,
				m_RECTClient.top+60,
				m_hOffline_Icon);
		}
		//------DEMO��--------------------------------
		if(m_bDemoRun == TRUE){
			m_VView0.GetDC()->DrawIcon(
				m_RECTClient.right-40,
				m_RECTClient.top,
				m_hDemo_Icon);
		}
		//------���p--------------------------------
//		m_VView0.GetDC()->DrawIcon(
//			m_RECTClient.left+10,
//			m_RECTClient.top+10,
//			m_hDirection_Icon[HlpGetDrectionPos()]);			//���p
//---------���̑�-------------------------


		m_VView2.DrawSituation(m_VView0.GetDC());									//�R���p�X�\��
		if(bScroll== FALSE){
			HlpSetDriveLog();												//�O�Փ_�\��
		}
//CString str;
//str.Format(L"%dkm/h",m_pGPS->GetSpeed());
//m_DrawTool.TextOut(m_VView0.GetDC(),m_RECTClient.left+10,m_RECTClient.top+90,str);



//---------�c�苗����\��---------------------------------------------
		if(m_nPassNode != -1){				//�ʉߍς݃m�[�h
			CDC memDC;
			CBitmap bmp;
			bmp.LoadBitmap(IDB_DISTANCE);
			BITMAP BitMap;
			bmp.GetBitmap(&BitMap);
			memDC.CreateCompatibleDC(m_VView0.GetDC());
			memDC.SelectObject(&bmp);
			m_VView0.GetDC()->BitBlt(0,253,BitMap.bmWidth,BitMap.bmHeight,&memDC,0,0,SRCCOPY);
			memDC.DeleteDC();

			nLastDistance =  m_Dijkstra.GetLasDistance(m_nNodeTracePos);

			str.Format(L"%0.1lfkm",(double)(nLastDistance)/1000);
			m_DrawTool.TextOut(m_VView0.GetDC(),180,253,str);

			int nHH,nMM;

			m_DrawTool.DistanceTime((double)nLastDistance, (double)m_pGPS->GetSpeed(),&nHH,&nMM);	//�w�苗���Ƒ��x����\�z�������Ԃ����߂�
			str.Format(L"%dmin",nHH*60+nMM);
			m_DrawTool.TextOut(m_VView0.GetDC(),118,253,str);

			int nTurnPos;
			switch(HlpGetTurnCourse(m_NextTurn)){			//��]�����l��
				case  DEF_LEFT_LITTLE:	nTurnPos=7;break;
				case  DEF_RIGHT_LITTLE:	nTurnPos=1;break;
				case  DEF_LEFT:			nTurnPos=6;break;
				case  DEF_RIGHT:		nTurnPos=2;break;
				default:				nTurnPos=0;break;
			}
			str.Format(L"%dm",m_NextTurnDistance);
			m_DrawTool.TextOut(m_VView0.GetDC(),30,253,str);

			//�����Đ�����
			if(m_b100m == TRUE){
				m_VView0.GetDC()->DrawIcon(
					m_RECTClient.left,
					m_RECTClient.bottom-32,
					m_hSound_Icon);
			}

			//�E���ܕ���
			m_VView0.GetDC()->DrawIcon(
				m_RECTClient.left+10,
				m_RECTClient.bottom-32,
				m_hDirection_Icon[nTurnPos]);



		}


//#ifdef _DEBUG
//if(m_Dijkstra.m_nNodeTraceCnt > 2){		//���[�g�L�莞
//	if(m_nNearNode != -1){					//��ԋ߂��m�[�h�ԍ�
//		str.Format(L"%d->%dm",m_nNearNode,m_nNextDistance);
//		m_DrawTool.TextOut(m_VView0.GetDC(),10,253,str);
//	}
//}
//#endif


//#ifdef _DEBUG
//if(m_Dijkstra.m_nNodeTraceCnt > 2){		//���[�g�L�莞
//	if(m_nPassNode != -1){			//�ʉߍς݃m�[�h
//		CString str2,str3;
//		switch(HlpGetTurnCourse(m_NextTurn)){			//��]�����l��
//			case  DEF_LEFT_LITTLE:str2 = L"��⍶";break;
//			case  DEF_RIGHT_LITTLE:str2 = L"���E";break;
//			case  DEF_LEFT:str2 = L"��";break;
//			case  DEF_RIGHT:str2 = L"�E";break;
//			default:  str2 = L"���i";break;
//		}
//		if(m_b100m == FALSE)str3 = L"";
//		else                str3 = L"��";
////		str.Format(L"%d->%d %d��%dm,%s",m_nPassNode,m_nNextNode,
///		m_NextTurn,m_NextTurnDistance,str2);
//		str.Format(L"%0.1lfkm %s %s",
//			(double)(m_NextTurnDistance)/1000,str2,str3);
//		m_DrawTool.TextOut(m_VView0.GetDC(),10,253,str);
//	}
////}
////#endif


}
/***********************************************************************************
*	�������
***********************************************************************************/
void CAutoPCView::HlpDispInit()
{
	HlpDispInitBMP(0,0,IDB_INIT);
	if(m_nCountry == -1)return;	//���ݒ蒆

	if(m_nCountry == COUNTRY_USA)HlpDispInitBMP(120,200,IDB_INIT_USA);
	else						 HlpDispInitBMP(120,200,IDB_INIT_KOREA);
}
/***********************************************************************************
*	�������bmp�\��
***********************************************************************************/
void CAutoPCView::HlpDispInitBMP(int nX,int nY,int nID)
{
	CDC *pDC;
	pDC=GetDC();

	CDC memDC;
	CBitmap bmp;

	bmp.LoadBitmap(nID);
	
	BITMAP BitMap;
	bmp.GetBitmap(&BitMap);

	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&bmp);
//	pDC->BitBlt(60,90,BitMap.bmWidth,BitMap.bmHeight,&memDC,0,0,SRCCOPY);
	pDC->BitBlt(nX,nY,BitMap.bmWidth,BitMap.bmHeight,&memDC,0,0,SRCCOPY);

	memDC.DeleteDC();
	ReleaseDC(pDC);



}

/***********************************************************************************
*	�O�Փ_�\��
*	���Ԉʒu��\������
***********************************************************************************/
void CAutoPCView::HlpSetDriveLog()
{
//	if(m_nDriveLogWriteCnt != 0)return;
//	//--------���Ԉʒu----------------------------------------------------
//	int nX = m_POClientCenter_V1.x+ m_POClientScroll.x + m_nMapMachOffset;	
//	int nY = m_POClientCenter_V1.y+ m_POClientScroll.y;
//	m_VView1.PaintLog(nX,nY);		//�\��

	m_nDriveLogWriteCnt++;
	if(m_nDriveLogWriteCnt != STEP_WAIT_CNT)return;
	//--------���Ԉʒu----------------------------------------------------
	int nX = m_POClientCenter_V1.x+ m_POClientScroll.x + m_nMapMachOffset;	
	int nY = m_POClientCenter_V1.y+ m_POClientScroll.y;
	m_VView1.PaintLog(nX,nY);		//�\��
	//--------�o�^----------------------------------------------------
	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);							//�J�[�\���ʒu�̈ܓx�o�x�l��
	m_pDriveLog->SetPoint((DWORD)(dfEW*DEF_CONVERT),
					    (DWORD)(dfNS*DEF_CONVERT));		//�O�Փo�^
	m_nDriveLogWriteCnt=0;
}
/***********************************************************************************
*	�O�Փ_�\��
*	�t�@�C������ǂݏo���\������
***********************************************************************************/
void CAutoPCView::HlpGetDriveLog()
{
//	if(m_pDriveLog->FileReadPoint() == FALSE)return;	//�O�Փ_�ǂݏo��(�t�@�C������)
	int nMaxCnt = m_pDriveLog->GetMaxCnt();			//�ݒ萔�l��

	int i;
	POINT po;
	for(i=0;i<nMaxCnt;i++){
		po = m_VView2.ImagePoint(m_pDriveLog->m_pEN[i].dwEW,
								 m_pDriveLog->m_pEN[i].dwNS);

		if(po.x < 0 || po.y < 0)continue;
		if(po.x > m_RECTVview.right || po.y > m_RECTVview.bottom)continue;

		m_VView2.PaintLog(po.x,po.y);		//�\��
	}
}
/***********************************************************************************
*	�J�[�\���ʒu�̈ܓx�o�l��
***********************************************************************************/
void CAutoPCView::HlpGetCurEN(double *dfpEW,double *dfpNS)
{
	//--------���Ԉʒu----------------------------------------------------
	int nX = m_POClientCenter_V1.x+ m_POClientScroll.x + m_nMapMachOffset;	
	int nY = m_POClientCenter_V1.y+ m_POClientScroll.y;
	m_VView1.GetENPoint(nX,nY,dfpEW,dfpNS);
}


/***********************************************************************************
*	���[�g�����ʒu�蓮�ݒ�l	
***********************************************************************************/
void CAutoPCView::HlpSetRouteStartEN()
{
//	double dfEW,dfNS;
	HlpGetCurEN(&m_dfRouteStartEW,&m_dfRouteStartNS);		//�J�[�\���ʒu�̈ܓx�o�l��
//	HlpWaitDlg(TRUE,L"Route starting point set!");
//	HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose

	CString str;
	str.Format(L"%0.5lf,%0.5lf",m_dfRouteStartEW,m_dfRouteStartNS);
	HlpTRACE(str);

}
/***********************************************************************************
*	�����͎�
***********************************************************************************/
void CAutoPCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

//HlpTRACE(nChar);
//	if(m_pDlgInfo->GetSafeHwnd() != 0){	//DlgInfo�I�[�v����
//		m_pDlgInfo->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}



//	if(m_pSearch->GetSafeHwnd() != 0){	//������ʃI�[�v����
//		m_pSearch->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}

//	if(m_pSearchID->GetSafeHwnd() != 0){	//ID������ʃI�[�v����
//		m_pSearchID->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}

//	if(m_pSearch2->GetSafeHwnd() != 0){	//ٰČ�����ʃI�[�v����
//		m_pSearch2->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}



//	if(m_pDial->GetSafeHwnd() != 0){	//DIAL��ʃI�[�v����
//		m_pDial->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}

//	if(m_pRasEntry->GetSafeHwnd() != 0){	//DIAL��ʃI�[�v����
//		m_pRasEntry->PostMessage(WM_EVENT,EV_KEY_DOWN,nChar);
//		goto TAG_EXIT;
//	}


	switch(nChar){
//		case 0x31:				//F1
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,1);
//			}
//			break;
//		case 0x32:				//F2
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,2);
//			}
//			break;
//		case 0x33:				//F3
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,3);
//			}
//			break;
//		case 0x34:				//F4
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,4);
//			}
//			break;
//		case 0x35:				//F5
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,5);
//			}
//			break;
//		case 0x36:				//F6
//			if(m_pDlgMenu->GetSafeHwnd() != 0){
//				m_pDlgMenu->PostMessage(WM_EVENT,EV_FUNCKEY,6);
//			}
//			break;
		case 37:				//left
			if(HlpCurScrollChk() == FALSE)break;
			HlpCurScroll(-10,0);
			break;
		case 38:				//up
			if(HlpCurScrollChk() == FALSE)break;
			HlpCurScroll(0,-10);
			break;
		case 39:				//right
			if(HlpCurScrollChk() == FALSE)break;
			HlpCurScroll(10,0);
			break;
		case 40:				//down
			if(HlpCurScrollChk() == FALSE)break;
			HlpCurScroll(0,10);
			break;
//		case 0x30:				//ENT
//			HlpSetRouteStartEN();					//���[�g�����ʒu�蓮�ݒ�l	
	

//			if(m_pSearch->GetDispIconMax() > 0){	//���ӌ�������
//				HlpClickSearchIcon();			//���ӌ����A�C�R���N���b�N
//			}
//			break;
//		case 47:				//HELP
//			break;
//		case 0x20:				//MENU
//			if(m_pDlgMenu->GetSafeHwnd() == 0){
//				SetMainStatus(ST_SCROLL,TRUE);	//�X�N���[�����[�h	ON
//				m_bKeyUP = TRUE;
//				HlpReDraw();					//�ĕ`��
//				m_pDlgMenu->Create(this,&m_strWaitDlgMsg,IDX_DLG_MENU);
//			}
//			break;
//		case 27:				//ESC
//			if(m_pDlgMenu->GetSafeHwnd() != 0){	//���j���[���J���Ă���
//				m_pDlgMenu->DestroyWindow();	//���j���[�N���[�Y
//				break;
//			}
//			SetMainStatus(ST_SCROLL,FALSE);		//�X�N���[�����[�hOFF
//			break;


	}
//	HlpReDraw();
//TAG_EXIT:

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
//***********************************************************************************
//*�@key up
//***********************************************************************************
void CAutoPCView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	m_nDriveLogWriteCnt=0;
	m_bKeyUP = TRUE;
	HlpReDraw();
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


//***********************************************************************************
//*	�J�[�\���X�N���[��CHK
//***********************************************************************************
BOOL CAutoPCView::HlpCurScrollChk()
{
//--------�X���b�h�`�撆�̓L�[���͏�����x������------------------
	if(m_pThread->m_pThread != NULL){
		if(m_nKeyInSleepCnt < 3){
			m_nKeyInSleepCnt++;
			return FALSE;
		}
		m_nKeyInSleepCnt=0;
	}
	return TRUE;
}

//***********************************************************************************
//*	�J�[�\���X�N���[��
//***********************************************************************************
void CAutoPCView::HlpCurScroll(int nX,int nY)
{

//	MSG message;

//	if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)){
//		::TranslateMessage(&message);
//		::DispatchMessage(&message);
//	}

	if(HlpChkReDraw(m_poClick) == FALSE)return;
//	HlpTRACE(L"Scroll");
//	if(GetMainStatus(ST_WAIT) == TRUE)return;//WAIT DLG�\����
	SetMainStatus(ST_SCROLL,TRUE);	//�X�N���[�����[�h ON
//	if(m_pThread->m_pThread != NULL)return;	//�X���b�h�g�p������


	m_poClick.x = 	m_POClientCenter.x + nX;
	m_poClick.y = 	m_POClientCenter.y + nY;

	HlpScroll(m_poClick);		
//	PostMessage(WM_EVENT,EV_SCROLL);	//��ʃX�N���[��
}
//***********************************************************************************
//*	�}�E�X���N���b�N
//***********************************************************************************
void CAutoPCView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(nFlags & MK_LBUTTON == MK_LBUTTON){
		SetMainStatus(ST_SCROLL,TRUE);	//�X�N���[�����[�h ON
		m_poClick = point;
		HlpScroll(m_poClick);
//		PostMessage(WM_EVENT,EV_SCROLL);	//��ʃX�N���[��

//		double dfEW,dfNS;
//		HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��
//		TRACE(L"%0.5lf %0.5lf\n",dfEW,dfNS);


	}
//------------------------------------------------------------
	CView::OnLButtonDown(nFlags, point);
}


//***********************************************************************************
//*	��ʃX�N���[��
//***********************************************************************************
void CAutoPCView::HlpScroll(CPoint point,int nAngle/*=0xffff*/)
{
//	if(point.x < 0)point.x=0;
//	if(point.x > m_RECTClient.right)point.x=m_RECTClient.right;
//	if(point.y < 0)point.y=0;
//	if(point.y > m_RECTClient.bottom)point.y=m_RECTClient.bottom;

	POINT poView,poVView;
	int nReDrawAngle = REDRAW_ANGLE;

	poView.x = point.x + m_POClientScroll.x;
	poView.y = point.y + m_POClientScroll.y;
	HlpZConv(&m_dfClientCenterEW,&m_dfClientCenterNS,&poView,&poVView);	//���W�ϊ�(�����->���z���->�o�x�ܓx)

	if(HlpChkDrawV(poVView) == TRUE){			//���z��ʕ`��K�v������
	//-------------V2����`��--------------------------------------
		if(nAngle != 0xffff){
			m_VView2.SetAngle(nAngle);
		}
//		if(m_pSearch->ChkSearchCode() == TRUE){		//�����R�[�h�ݒ茟��
//			PostMessage(WM_EVENT,EV_SOC_CONNECT,SOC_REQ_G1_G2);
//		}
		HlpVPaint();
	}
	//-------------V����ʂ̂ݕ`��--------------------------------------
	else{
		if(m_pThread->m_pThread == NULL && nAngle != 0xffff){
			if(m_pGPS->GetSpeed() < 20)nReDrawAngle = 90;	//20km/h����
			if(m_VView2.ChkAngle(nAngle,nReDrawAngle) == FALSE){
				m_VView2.SetAngle(nAngle);
				HlpVPaint();
//				m_nMapMachOffset = 0;
				return;
			}
		}
		if(HlpChkReDraw(point) == FALSE)return;//����ʕ`��\����
		m_POClientScroll.x += point.x - m_POClientCenter.x;
		m_POClientScroll.y += point.y - m_POClientCenter.y;
		HlpReDraw();
	}





}
//***********************************************************************************
//*	���ӌ����A�C�R���N���b�N
//***********************************************************************************
void CAutoPCView::HlpClickSearchIcon()
{
/*	double dfEW,dfNS;
	int nIconNo;

	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��
	nIconNo = m_pSearch->ClickIcon(dfEW,dfNS);
	if(nIconNo == -1)return;


	if(m_pDlgInfo->GetSafeHwnd() == 0){
		m_pDlgInfo->Create(this,IDX_DLG_INFO);
		m_pDlgInfo->SetWindowText(m_pSearch->m_strIconName[nIconNo]);
		m_pDlgInfo->m_Edit.SetWindowText(m_pSearch->m_strIconMemo[nIconNo]);

	}
*/

//	else{	
//		m_pDlgInfo->DestroyWindow();
//	}


}
//***********************************************************************************
//*	����ʕ`��\����
//***********************************************************************************
BOOL CAutoPCView::HlpChkReDraw(CPoint point)
{
	if(m_POClientScroll.x + point.x - m_POClientCenter.x  > m_POClientScrollMax.x)goto TAG_FALSE;
	if(m_POClientScroll.y + point.y - m_POClientCenter.y  > m_POClientScrollMax.y + m_nClientCenterOffsetCar)goto TAG_FALSE;;
	if(m_POClientScroll.x + point.x - m_POClientCenter.x  < -m_POClientScrollMax.x)goto TAG_FALSE;;
	if(m_POClientScroll.y + point.y - m_POClientCenter.y  < -m_POClientScrollMax.y + m_nClientCenterOffsetCar)goto TAG_FALSE;;


	return TRUE;
TAG_FALSE:

	if(m_pThread->m_pThread == NULL)return TRUE;

//	if(GetMainStatus(ST_SCROLL) == TRUE){//�X�N���[�����[�h
//		HlpWaitDlg(TRUE);
//	}
//	HlpTRACE(L"Desable Draw");

	return FALSE;
}
//***********************************************************************************
//*	���z��ʕ`��K�v������
//***********************************************************************************
BOOL CAutoPCView::HlpChkDrawV(CPoint poVView)
{
	if(m_pThread->m_pThread != NULL)return FALSE;	//�X���b�h�g�p������
//	if(m_pDB->GetThreadUse() == TRUE)return FALSE;	//�X���b�h�g�p������





	if( poVView.x > m_POClientCenter_V1.x + m_POClientScrollMaxV2Draw.x ||		//���z��ʒ��S���X�N���[���ő吔�𒴂��Ă���
		poVView.y > m_POClientCenter_V1.y + m_POClientScrollMaxV2Draw.y ||
		poVView.x < m_POClientCenter_V1.x - m_POClientScrollMaxV2Draw.x ||
		poVView.y < m_POClientCenter_V1.y - m_POClientScrollMaxV2Draw.y + m_nClientCenterOffsetCar){
		return TRUE;
	}



	return FALSE;

}


//***********************************************************************************
//*	RS232C�J�n
//***********************************************************************************
void CAutoPCView::HlpRs232cStart()
{
	if(m_pComm != NULL)return;
//	m_bRs232cDraw = FALSE;										//RS232C���R�[�h�`��t���O
//	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)


	m_pComm = new CCeCommMgr(this);
	if(m_pComm->OpenComm(L"COM1:") == FALSE)goto TAG_EXIT;//1,2,3,5 OK
//	int i;
//	CString str;
//	for(i=2;i<=9;i++){
//		if(i == 5)continue;
//		str.Format(L"COM%d:",i);
//		if(m_pComm->OpenComm(str) == FALSE)continue;
//		HlpTRACE(str);
//		break;
//	}
//	if(i==10){
//		goto TAG_EXIT;
//	}

	if(m_pComm->StartComm() == FALSE)goto TAG_EXIT;
//	if(m_pDlgMenu->GetSafeHwnd() != 0){
//		m_pDlgMenu->PostMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n�ʒm
//	}
//	 HlpTRACE(L"GPS Receive start.");
	return;
TAG_EXIT:
#ifdef _DEBUG
	TRACE(L"Rs232c Init err.");
#else
	MessageBox(L"Rs232c Init err.");
#endif
}
//***********************************************************************************
//*	RS232C��~
//***********************************************************************************
void CAutoPCView::HlpRs232cStop()
{
	if(m_pComm == NULL)return;
	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

//	m_bRs232cDraw = FALSE;										//RS232C���R�[�h�`��t���O
	m_pComm->CloseComm();
	delete m_pComm;
	m_pComm = NULL;
//	if(m_pDlgMenu->GetSafeHwnd() != 0){
//		m_pDlgMenu->PostMessage(WM_EVENT,EV_GPS_RECEIVE_STOP);	//GPS��M��~�ʒm
//	}
//	HlpTRACE(L"GPS Receive stop.");
}
//***********************************************************************************
//*	RS232C��M
//***********************************************************************************
BOOL CAutoPCView::HlpRs232cReceive()
{
	int I,nChk;

	int Size = m_pComm->GetRecieveData(m_p232cReceiveBuf);

//CString str;
//str.Format(L"%d",Size);
//HlpTRACE(str);

	if(Size == 0)return FALSE;
//	if(GetMainStatus(ST_SCROLL) == TRUE)return FALSE;		//�X�N���[�����[�h	ON

//	for( I = 0; I < Size; ++I) {
	for( I = 0; I < Size; I++) {
		nChk = m_pGPS->ChkDecodeData(m_p232cReceiveBuf[I]);	//GPS�f�[�^�f�R�[�h����
		if(nChk == GPS_CONTINUE)continue;
		if(nChk == GPS_DECODE_OK){
			m_pGPS->DecodeGps1(m_pComm);
			m_pGPS->ReceiveCount = 0;
			memset(m_pGPS->ReceiveBuff, 0, BUF_SIZE);
			continue;
		}
		m_pGPS->ReceiveBuff[m_pGPS->ReceiveCount] = m_p232cReceiveBuf[I];
		++(m_pGPS->ReceiveCount);
		if( m_pGPS->ReceiveCount >= BUF_SIZE ) {
			m_pGPS->ReceiveCount = 0;
			memset(m_pGPS->ReceiveBuff, 0, BUF_SIZE);
		}
	}


//	m_bRs232cDraw = TRUE;										//RS232C���R�[�h�`��t���O
	return TRUE;
}
//***********************************************************************************
//*	RS232C���R�[�h��M�I�̕`��
//***********************************************************************************
void CAutoPCView::HlpRs232cDraw()
{
//	if(m_bRs232cDraw == FALSE)return;					//RS232C���R�[�h�`��t���O

	CString str;
	DOUBLE dfEW,dfNS;

	m_pGPS->GetENPoint(&dfEW,&dfNS);
	m_dfSaveGPSEW = dfEW;
	m_dfSaveGPSNS = dfNS;
	dfEW += m_dfMapMachOffsetEW;//�}�b�v�}�b�`�I�t�Z�b�g
	dfNS += m_dfMapMachOffsetNS;//�}�b�v�}�b�`�I�t�Z�b�g

//	m_dfMapMachOffsetEW = dfEW;//�}�b�v�}�b�`�I�t�Z�b�g
//	m_dfMapMachOffsetNS = dfNS;//�}�b�v�}�b�`�I�t�Z�b�g



//	dfEW += m_dfMapMachOffsetEW;//�}�b�v�}�b�`�I�t�Z�b�g
//	dfNS += m_dfMapMachOffsetNS;//�}�b�v�}�b�`�I�t�Z�b�g

//	if(dfSaveGPSEW == dfEW){						//�O���M�ʒu�Ɣ�r
//		m_bReceiveGPS = FALSE;
//		HlpReDraw();
//		HlpTRACE(L"No changed GPS.");
//		return;
//	}
//	dfSaveGPSEW = dfEW;

//	if(HlpChkGPSReceiveEWNS(dfEW,dfNS) == FALSE)return;		//GPS��M�ʒu�Ó�������
	HlpAutoDemo(dfEW,dfNS,m_pGPS->GetAngle());


//--------�}�b�v�}�b�`�I�t�Z�b�g�ݒ�-----------------------------------
//	DOUBLE dfEW2,dfNS2;
//	if(m_nMapMachOffset != 0){
//		HlpGetCurEN(&dfEW2,&dfNS2);		//�J�[�\���ʒu�̈ܓx�o�l��
//		m_dfMapMachOffsetEW = dfEW2 - dfEW;
//		m_dfMapMachOffsetNS = dfNS2 - dfNS;
//	}
//	else{
//		m_dfMapMachOffsetEW = 0;
//		m_dfMapMachOffsetNS = 0;
//	}
//TRACE(L"%0.10lf %0.10lf\n",m_dfMapMachOffsetEW,m_dfMapMachOffsetNS);


//	if(GetMainStatus(ST_GPS_TRACE) == TRUE){		//GPS���g���[�X(debug�p)
//m_pGPS->GetStatus(&str);									//��Ԋl��
//TRACE(str);
//	}
//	m_bRs232cDraw = FALSE;										//RS232C���R�[�h�`��t���O

}
/***********************************************************************************
*	GPS��M�ʒu�Ó�������
***********************************************************************************/
/*BOOL CAutoPCView::HlpChkGPSReceiveEWNS(double dfEW,double dfNS)
{
	if(m_dfChkGPS_EW == 0){			//�������
		m_dfChkGPS_EW = dfEW;
		m_dfChkGPS_NS = dfNS;
		m_nChkGPSChkFlg=0;
		return TRUE;
	}

	double dfChkVal = 0.0001;			//�����͈�

	if( (m_dfChkGPS_EW + dfChkVal) < dfEW ||
		(m_dfChkGPS_EW - dfChkVal) > dfEW ||
		(m_dfChkGPS_NS + dfChkVal) < dfNS ||
		(m_dfChkGPS_NS - dfChkVal) > dfNS){

		m_nChkGPSChkFlg++;				//�Y���ΏۃJ�E���g
		if(m_nChkGPSChkFlg > 3){		//3��͂�������OK�Ƃ���
			m_nChkGPSChkFlg=0;
			m_dfChkGPS_EW = dfEW;
			m_dfChkGPS_NS = dfNS;
			return TRUE;
		}
		HlpTRACE(L"HlpChkGPSReceiveEWNS");
		return FALSE;
	}

	m_dfChkGPS_EW = dfEW;
	m_dfChkGPS_NS = dfNS;
	m_nChkGPSChkFlg=0;
	return TRUE;		//OK

}
*/
/***********************************************************************************
*	�����f�����s
***********************************************************************************/
void CAutoPCView::HlpAutoDemo(double dfEW,double dfNS,int nAngle)
{
	int bScaleUp=FALSE;		//���ٱ���

//----------���[�g�֘A--------------------------
	int nEW = (int)(dfEW * DEF_CONVERT);
	int nNS = (int)(dfNS * DEF_CONVERT);

//	m_Dijkstra.PlaySound700(nEW,nNS);	//�����Đ�(700m��O)
//	int nVal = m_Dijkstra.PlaySound100(nEW,nNS);	//�����Đ�(100m��O)

//	m_nLastDistance = m_Dijkstra.GetLastDistance(nEW,nNS);	//�c�苗���l��

	//��ԋ߂����[�g��m�[�h�ԍ��l��
//	m_nNearNode = m_Dijkstra.GetNearNode2(nEW,nNS,&m_nDistanceTMP,&m_nNextDistance);


	//���[�g��̒ʉ߃m�[�h�l��
	int nPassNode,nNextNode,nNodeTracePos,n100mPos;
	nNodeTracePos = m_Dijkstra.GetPassNode(nEW,nNS,&nPassNode,&nNextNode,&m_NextTurn,
							&m_NextTurnDistance,&m_b100m,&n100mPos);
	if(nNodeTracePos != -1){
		m_nPassNode = nPassNode;		//�ʉߍς݃m�[�h
		m_nNextNode = nNextNode;		//���m�[�h
		m_nNodeTracePos = nNodeTracePos;//�m�[�h���z��ʒu
		if(m_NextTurnDistance == 0){	//�Ōオ�����̏ꍇ
			m_NextTurnDistance = m_Dijkstra.GetLasDistance(m_nNodeTracePos);
		}
	}

//-------------�����Đ�--------------------------------------------
	if(m_b100m == TRUE){
		if(m_nSave100mPos !=  n100mPos){			//100m��O�ʉ�pos(�O��ʂ����ʒu)
			m_nSave100mPos =  n100mPos;
			bScaleUp=TRUE;							//���ٱ���
			switch(HlpGetTurnCourse(m_NextTurn)){
				case  DEF_LEFT_LITTLE:	m_Dijkstra.WavPlay(WAV_LITTLE_LEFT);break;//��⍶
				case  DEF_RIGHT_LITTLE:	m_Dijkstra.WavPlay(WAV_LITTLE_RIGHT);break;//���E
				case  DEF_LEFT:			m_Dijkstra.WavPlay(WAV_LEFT);break;//��
				case  DEF_RIGHT:		m_Dijkstra.WavPlay(WAV_RIGHT);break;//�E
				case  DEF_STRAIGHT:		m_Dijkstra.WavPlay(WAV_END);break;//�S�[���n�_
			}
		}
		else{
			m_b100m = FALSE;	//�O��ʂ���
		}
	}


	//-------------------------------�I�[�g�X�P�[���A�b�v------------------------
	if(m_zEnv[1] == 0){
		if(bScaleUp == TRUE){
//			m_nEWScaleUpPoint = nEW;
//			m_nNSScaleUpPoint = nNS;
			if(m_nMapLevel < 9){
				m_nSaveMapLevel = m_nMapLevel;
				m_nMapLevel=9;	//50m
				HlpVPaint();
			}
		}
		else{
//			if(m_nSaveMapLevel != -1 && m_NextTurnDistance > 300){			//���E���܂܂ł���300m�ȏ゠��down����
			if(HlpScaleUpPoint(nEW,nNS) == TRUE){
				if(m_nMapLevel != m_nSaveMapLevel){
					m_nMapLevel=m_nSaveMapLevel;
					m_nSaveMapLevel = -1;
					HlpVPaint();
				}
			}
		}
	}




//----------���[�g�֘A�����܂�--------------------------



	if(GetMainStatus(ST_SCROLL) == TRUE)return;		//�X�N���[�����[�h	ON

	CPoint poView,poVView;
	double dfDummy1,dfDummy2;
	poView =  m_VView1.BMPPosition(dfEW,dfNS,m_VView1.GetAngle());


//TRACE(L"%0.5lf %0.5lf %d %d\n",dfEW,dfNS,poView.x,poView.x);
	poView += (m_POClientCenter - m_POClientScroll);
	HlpZConv(&dfDummy1,&dfDummy2,&poView,&poVView);	//���W�ϊ�(�����->���z���->�o�x�ܓx)
	HlpScroll(poView,nAngle);
}
/***********************************************************************************
*	�X�P�[���_�E���|�C���g����
*	m_NextTurnDistance���R�O�Om���z���Ă���100m��������TRUE
***********************************************************************************/
BOOL CAutoPCView::HlpScaleUpPoint(int nEW,int nNS)
{
	if(m_nSaveMapLevel == -1)return FALSE;

	if(m_nEWScaleUpPoint == -1 && m_NextTurnDistance > 300){
		m_nEWScaleUpPoint = nEW;
		m_nNSScaleUpPoint = nNS;
		return FALSE;
	}

	if(m_nEWScaleUpPoint == -1)return FALSE;


	int nDistance = (int)m_Tool.PointToMeter(
						(double)m_nEWScaleUpPoint/DEF_CONVERT,
						(double)m_nNSScaleUpPoint/DEF_CONVERT,
						(double)nEW/DEF_CONVERT,
						(double)nNS/DEF_CONVERT);

	if(nDistance > 100){
		m_nEWScaleUpPoint = -1;
		m_nNSScaleUpPoint = -1;
		return TRUE;			//100m�ȏ�z������OK
	}
	return FALSE;
}
/***********************************************************************************
*	��]�����l��
***********************************************************************************/
int CAutoPCView::HlpGetTurnCourse(int nAngle)
{
	BOOL bLeft=FALSE;
	if(nAngle < 0){
		bLeft=TRUE;
		nAngle = abs(nAngle);
	}

	if(nAngle < DEF_WAV_STRAIGHT)	return DEF_STRAIGHT;		//���i
	if(nAngle < DEF_WAV_LITTLE_TURN){
		if(bLeft == TRUE)			return DEF_LEFT_LITTLE;		//��⍶
		else						return DEF_RIGHT_LITTLE;	//���E
	}
	


//	if(nAngle < DEF_WAV_TURN){
		if(bLeft == TRUE)			return DEF_LEFT;			//��
		else						return DEF_RIGHT;			//�E
//	}

//	return DEF_STRAIGHT;										//�s���͒��i�ɂ���
}
/***********************************************************************************
*	���W�ϊ�
*	dfEW:�o�x dfNS:�ܓx poView:����� poVView:���z���
***********************************************************************************/
void CAutoPCView::HlpZConv(double *dfpEW,double *dfpNS,POINT *popView,POINT *popVView)
{
						//�����->���z���->�o�x�ܓx

//	popVView->x  = popView->x + m_POClientCenter.x;
//	popVView->y  = popView->y + m_POClientCenter.y;
	popVView->x  = popView->x + m_POClientScrollMax.x;
	popVView->y  = popView->y + m_POClientScrollMax.y;
	m_VView1.GetENPoint(popVView->x, popVView->y,dfpEW,dfpNS);
}
/***********************************************************************************
*	�}�b�v�}�b�`���W�l��
***********************************************************************************/
int CAutoPCView::HlpMapMach()
{
	if(GetMainStatus(ST_RUN)	== FALSE)return 0;	//�ʏ푖�s��		OFF
	if(GetMainStatus(ST_SCROLL) == TRUE)return 0;	//�X�N���[�����[�h	ON

	CDC *pDC = m_VView4.GetDC();
	int nRet=0;
	//--------���Ԉʒu----------------------------------------------------
	int nX = m_POClientCenter_V1.x+ m_POClientScroll.x;	
	int nY = m_POClientCenter_V1.y+ m_POClientScroll.y;

	int i,nChkVal;

	switch(m_nMapLevel){
		case 10:nChkVal = 100;break;
		case  9:nChkVal =  50;break;
		case  8:nChkVal =  25;break;
		case  7:nChkVal =  10;break;
		case  6:nChkVal =   5;break;
		default:nChkVal =   3;break;
	}
	//--------���[�g�������莞-------------------------------------------
	if(m_Dijkstra.m_nNodeTraceCnt > 2){
//		nChkVal*=2;									//���[�g�ݒ莞�ɂ͋��͂ɂ���
		for(i=0;i<nChkVal;i++){
			if(pDC->GetPixel(nX   +i,nY) == COLOR_ROUTE_MAPMACH){
				if(m_bRerouteTimer == TRUE){
					KillTimer(TO_REROUTE);		//�ٰċ��Ď����
					m_bRerouteTimer=FALSE;
				}
				return  i;
			}
			if(nX-i < 0)break;
			if(pDC->GetPixel(nX   -i,nY) == COLOR_ROUTE_MAPMACH){
				if(m_bRerouteTimer == TRUE){
					KillTimer(TO_REROUTE);		//�ٰċ��Ď����
					m_bRerouteTimer=FALSE;
				}
				return 0-i;
			}
		}
		if(m_bRerouteTimer == FALSE){
			m_bRerouteTimer=TRUE;
			SetTimer(TO_REROUTE,TO_VAL_REROUTE,NULL);		//�ٰċ��Ď����
		}
	}

	//-------�ʏ�----------------------------------------------------
	for(i=0;i<nChkVal;i++){
		if(pDC->GetPixel(nX   +i,nY) == COLOR_MAPMACH)return i;
		if(nX-i < 0)return 0;
		if(pDC->GetPixel(nX   -i,nY) == COLOR_MAPMACH)return 0-i;
	}
	return 0;
}

/****************************************************************************
*  ��ײݎ��̏���
*****************************************************************************/
void CAutoPCView::HlpConnectOffline(int nSocReqType)
{
	char tmp[100];
	int nLen;

	switch(nSocReqType){
		case SOC_REQ_SEARCH2_G2:			//�{�݌���
//			wcscpy((TCHAR*)tmp,m_strSearchMsg2.GetBuffer(100));
//			m_strSearchMsg2.ReleaseBuffer();
//HlpTRACE(m_strSearchMsg2);
//HlpTRACE(tmp);


			strcpy(tmp,m_Tool.CStringToChar(m_strSearchMsg2));
//			nLen = m_strSearchMsg2.GetLength();
//HlpTRACE(tmp);

//			strcpy(tmp,CStringToChar2(m_strSearchMsg2));
//			CStringToChar2(m_strSearchMsg2,tmp);
			nLen = strlen(tmp);
//HlpTRACE(tmp);

//			tmp[nLen]=0;
			HlpOfflineSSearch(tmp,nLen);
			break;
		case SOC_REQ_SEARCH2_ROUTE:			//���[�g����(Strat point is GPS.)
			break;
		case SOC_REQ_SEARCH2_ROUTE_USER:	//���[�g����(Strat point is user.)
			break;
		case SOC_REQ_REROUTE:				//�����[�g����
			break;
	}

}

//(******************************************************************************)
char* CAutoPCView::CStringToChar2(CString Str,char *m_s)
{
	int  n, i, j;
	UINT C;
//	static char m_s[1024];
	CString strTmp;

HlpTRACE(Str);
	n = Str.GetLength();
	for(j = i = 0; i < n; i++) {
		C = Str.GetAt(i);
strTmp.Format(L"%x",C);
HlpTRACE(strTmp);

//TCHAR tC;
//WORD w,t;
//LPWSTR w;


		if( C > 255 ) {
//			C = htons(C);
//			C = ntohs(C);
//			memcpy(&m_s[j],&C,2);j+=2;
			m_s[j] = (char)(C >> 8);   ++j;
			m_s[j] = (char)(C & 0xff); ++j;


//			LPWSTR lpwstr;
//			LPSTR lpsz = W2A(lpwstr);

	
//			LPSTR lpsz = &m_s[0];
//			LPWSTR  X = A2W(lpsz);


			
		} else {
			m_s[j] = (char)C; ++j;
		}
	}
	m_s[j] = 0;
	return &m_s[0];
}


/***********************************************************************************
*	��ײݎ{�݌���
***********************************************************************************/
//void CAutoPCView::HlpOfflineSSearch(TCHAR *cpKey,int nKeyLen)
void CAutoPCView::HlpOfflineSSearch(char *cpKey,int nKeyLen)
{
//	CNameBody *pNameBody = new CNameBody;
//	int nEW,nNS;

//	int i;
//	char tmp[10];
//	tmp[1]=0;
//	for(i=0;i<nKeyLen;i++){
//		sprintf(tmp,"0x%02x",cpKey[i]);
//		HlpTRACE(tmp);
//	}
//	CString str;
//	str.Format(L"len:%d",nKeyLen);
//	HlpTRACE(str);




//	if(pNameBody->Create(FILE_IDX_NAME,FILE_DAT_NAME) == FALSE){
//		m_pSearch2->SetDispG2Max(0);
//		m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
//		HlpWaitDlg(TRUE,L"No data.");
//		HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
//		delete pNameBody;
//		return;				//NG
//	}

//CString str;
//str.Format(L"%s %d",(CString)cpKey,nKeyLen);
//HlpTRACE(str);
//	if(pNameBody->Load(cpKey,nKeyLen,m_SocBuf) == FALSE){		//m_SocBuf��offline�ł͎g�p���Ȃ��̂ŗ��p
//		m_pSearch2->SetDispG2Max(0);
//		m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
//		HlpWaitDlg(TRUE,L"No data.");
//		HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
//		delete pNameBody;
//		return;				//NG
//	}
//	delete pNameBody;


//----------dlg���ɕ\��--------------------------------
//	m_pSearch2->SetG2(m_SocBuf,strlen(m_SocBuf));	//m_SocBuf��offline�ł͎g�p���Ȃ��̂ŗ��p
//	m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
//	m_VView2.SetAngle(90);					//�A���O���ݒ�
}
/***********************************************************************************
*	Soc Connent and Send
***********************************************************************************/
void CAutoPCView::HlpSocConnectAndSend(int nSocReqType)
{
	char buf[1024];
	CString str;
	CString strIP;
	int nPort,nLen;
	BOOL bFlg = FALSE;

	if(m_pSoc != NULL){
		HlpTRACE(L"Soc use");
		return;
	}

//--------------�\�z-------------------------------------------
	m_pSoc = new CUlp(this);
	if(m_pSoc->Create(0) == FALSE){
		HlpTRACE(_T("Create err"));
		goto TAG_ERR;
	}
//------------------connect----------------------------
	switch(nSocReqType){
		case SOC_REQ_G1:
		case SOC_REQ_G2:
		case SOC_REQ_G1_G2:
		case SOC_REQ_SEARCH2_G2:
			strIP = SEARCH1_SAVER_IP;
			nPort = SEARCH1_SAVER_PORT;
			break;
		case SOC_REQ_SEARCH2_ROUTE:			//���[�g����
		case SOC_REQ_SEARCH2_ROUTE_USER:	//���[�g����
		case SOC_REQ_REROUTE:				//�����[�g����
			strIP = SEARCH2_SAVER_IP;
			nPort = SEARCH2_SAVER_PORT;
			break;
		case SOC_SEND_ID:
		case SOC_REQ_SEARCH_ID:
			strIP = SEARCH_ID_SAVER_IP;
			nPort = SEARCH_ID_SAVER_PORT;
			break;
	}

	if(m_pSoc->Connect(strIP,nPort) == FALSE){
		str.Format(L"Connect err[%s:%d]",strIP,nPort);
		HlpTRACE(str);
		goto TAG_ERR;
	}
//------------------send----------------------------------------------
	switch(nSocReqType){
		case SOC_REQ_G1:
			strcpy(buf,"select * from G1");
			nLen = strlen(buf);
			break;
		case SOC_REQ_G2:
			str.Format(L"select G2,Name from G2 where G1 = '%s'",m_strSearchMsg);
			strcpy(buf,m_Tool.CStringToChar(str));
			nLen = strlen(buf);
			break;
//		case SOC_REQ_G1_G2:
//			if(HlpSocConnectAndSendG1G2(&str) == FALSE){
//				m_pSoc->Close();
//				delete m_pSoc;
//				m_pSoc = NULL;
//				return;
//			}
//			strcpy(buf,m_Tool.CStringToChar(str));
//			nLen = strlen(buf);
//			break;
		case SOC_REQ_SEARCH2_G2:
//			HlpTRACE(m_strSearchMsg2);
			str.Format(L"select top 10 ew,ns,Name from POI where NAME like '%s%%' order by name",m_strSearchMsg2);
//			str = L"select top 10 ew,ns,Name from POI where NAME like 'A%' order by name";
			strcpy(buf,m_Tool.CStringToChar(str));
			nLen = strlen(buf);
			break;
		case SOC_REQ_SEARCH2_ROUTE:
//			HlpWaitDlg(TRUE);
			nLen = HlpMakeRouteSetData(buf,0);	//���[�g�����f�[�^�l���p�f�[�^�쐬(GPS�n�_)
			break;
		case SOC_REQ_SEARCH2_ROUTE_USER:
//			HlpWaitDlg(TRUE);
			nLen = HlpMakeRouteSetData(buf,1);	//���[�g�����f�[�^�l���p�f�[�^�쐬(User�n�_)
			break;
		case SOC_REQ_REROUTE:
//			HlpWaitDlg(TRUE);
			nLen = HlpMakeRouteSetData(buf,2);	//�����[�g�����f�[�^�l���p�f�[�^�쐬
			break;
		case SOC_SEND_ID:							//ID���M
			nLen = sizeof(struct_SearchID);
			memcpy(buf,&m_StructSearchID,nLen);
			bFlg = TRUE;
			break;
		case SOC_REQ_SEARCH_ID:						//ID�ʒu�l��
			nLen = sizeof(struct_SearchID);
			memcpy(buf,&m_StructSearchID,nLen);
//			HlpWaitDlg(TRUE);
			break;
		default:
			return;
//			str.Format(L"select count(*) from POI where NAME like '%s%'",m_strSearchMsg);");


	}

	m_pSoc->Send(buf,nLen,bFlg);

//		CString str2;
//		str.Format("%s",buf);
//		HlpTRACE(str);


	m_nSocReceiveSize=0;
	m_bSocReceiveFault = FALSE;
	if(bFlg == FALSE)	strcpy(m_SocBuf,ULP_NO_RECEIVE);				//����M���
	else                strcpy(m_SocBuf,ULP_NO_RSP);					//�����d���Ȃ���

//	HlpWaitDlg(TRUE);


	HlpTRACE(_T("Connect&Send OK"));
	return;
//---------------------err ����----------------------------------------
TAG_ERR:;
	delete m_pSoc;
	m_pSoc = NULL;

	if(nSocReqType == SOC_SEND_ID)return;		//ID���M��
	
//	HlpWaitDlg(FALSE);
//	HlpWaitDlg(TRUE,L"Can't connected.");
//	HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
}
/***********************************************************************************
*	���[�g�����f�[�^�l���p�f�[�^�쐬
*	nType:  0:���[�g����(Strat point is GPS.)
*			1:���[�g����(Strat point is user.)
*			2:�����[�g����
***********************************************************************************/
int CAutoPCView::HlpMakeRouteSetData(char *cpBuf,int nType)
{
	CCommon comm;
	CString str;
	double dfGPSEW,dfGPSNS;



	switch(nType){
		case 0:
			m_pGPS->GetENPoint(&dfGPSEW,&dfGPSNS);						//GPS���W(�n�_)
			HlpGetCurEN(&m_dfRouteEW,&m_dfRouteNS);						//�J�[�\���ʒu���W(�I�_)
			break;
		case 1:
			dfGPSEW = m_dfRouteStartEW;									//���[�U��`�ʒu(�n�_)
			dfGPSNS = m_dfRouteStartNS;
			HlpGetCurEN(&m_dfRouteEW,&m_dfRouteNS);						//�J�[�\���ʒu���W(�I�_)
			break;
		case 2:
			m_pGPS->GetENPoint(&dfGPSEW,&dfGPSNS);						//GPS���W(�n�_�̂ݕύX)
			break;
		default:
			return 0;
	}
	


//	if(bReRoute == FALSE){
//		HlpGetCurEN(&m_dfRouteEW,&m_dfRouteNS);				//�J�[�\���ʒu���W
//	}

	str.Format(L"%s,%s,%s,%s",
		comm.RealToStr2(dfGPSEW),
		comm.RealToStr2(dfGPSNS),
		comm.RealToStr2(m_dfRouteEW),
		comm.RealToStr2(m_dfRouteNS));

	strcpy(cpBuf,m_Tool.CStringToChar(str));
	return strlen(cpBuf);
}
/***********************************************************************************
*	Soc Receive and Close
***********************************************************************************/
/*void CAutoPCView::HlpSocReceiveAndClose()
{
	CFile file;


//	HlpWaitDlg(FALSE);

	if(strcmp(m_SocBuf,ULP_NO_RSP) == 0){		//�����d���Ȃ���
		return;
	}



	switch(m_nSocReqType){
		case SOC_REQ_G1:
			m_pSearch->SetG1(m_SocBuf,m_nSocReceiveSize);
			m_pSearch->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
			break;
		case SOC_REQ_G2:
			m_pSearch->SetG2(m_SocBuf,m_nSocReceiveSize);
			m_pSearch->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
			break;
		case SOC_REQ_G1_G2:
			if(strcmp(m_SocBuf,ULP_NO_DATA) == 0){
				HlpTRACE(L"Not found.");
				m_pSearch->SetDispIconMax(0);
//				HlpWaitDlg(FALSE);
//				HlpWaitDlg(TRUE,L"Not found.");
//				HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
				break;
			}
			m_pSearch->SetDispIconPoint(m_SocBuf,m_nSocReceiveSize);
			m_pSearch->DestroyWindow();			//�N���[�Y
			HlpVPaint();
//			HlpWaitDlg(FALSE);
//			HlpWaitDlg(TRUE,L"Now setting.");
//			HlpWaitDlgAutoClose(5000);		//WaitDlgAutoClose
			break;
		case SOC_REQ_SEARCH2_G2:
			if(strcmp(m_SocBuf,ULP_NO_DATA) == 0){
				HlpTRACE(L"Not found.");
				m_pSearch2->SetDispG2Max(0);
				m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
			}
			else{
				m_pSearch2->SetG2(m_SocBuf,m_nSocReceiveSize);
				m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
			}
			break;
		//------------------------------------------------------------------------------------
		case SOC_REQ_SEARCH2_ROUTE:						//���[�g�ݒ�
		case SOC_REQ_SEARCH2_ROUTE_USER:				//���[�g�ݒ�
		case SOC_REQ_REROUTE:							//�����[�g����
//			if(GetMainStatus(ST_SAVE_ROUTE_DATA) == TRUE){		//���[�g�����f�[�^�ۑ�(debug�p)
//				HlpSaveRouteData(m_SocBuf,m_nSocReceiveSize);	//���[�g�����f�[�^�ۑ�
//			}


//			if(m_pSearch2->SetRoute(m_SocBuf) == FALSE)break;

//			if(file.Open(m_strDataPath+FILE_ROUTE, CFile::modeCreate | CFile::modeWrite) == FALSE)break;	//���[�g�f�[�^���t�@�C���ɏ�������
//			file.Write(m_SocBuf,m_nSocReceiveSize);
//			file.Close();

//			m_nRouteOnOff=1;
//			if(HlpSetRouteData(m_strDataPath+FILE_ROUTE) == FALSE){			//���[�g�����f�[�^�ݒ�
//				MessageBox(L"HlpSetRouteData() err");
//			}
//			HlpVPaint();		//V2����`��
//			HlpWaitDlg(FALSE);
			break;
		//------------------------------------------------------------------------------------
		case SOC_REQ_SEARCH_ID:
			memcpy(&m_StructSearchID,m_SocBuf,sizeof(struct_SearchID));
			if(m_StructSearchID.cType != SEARCH_ID_TYPE_RSPOK){
//				HlpWaitDlg(FALSE);
//				HlpWaitDlg(TRUE,L"ID not found.");
//				HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
				break;
			}
			SetMainStatus(ST_SCROLL,TRUE);		//�X�N���[�����[�h
//			HlpWaitDlg(TRUE);
//			HlpWaitDlgAutoClose(3000);			//WaitDlgAutoClose
			m_dfClientCenterEW =  (double)(m_StructSearchID.dwEW) / DEF_CONVERT;
			m_dfClientCenterNS =  (double)(m_StructSearchID.dwNS) / DEF_CONVERT;
			HlpVPaint();	//�l��ID�ʒu�ֈړ�
//			HlpWaitDlgAutoClose(1000);			//WaitDlgAutoClose
			break;


		default:
			break;
	}
}
*/
/***********************************************************************************
*	���[�g�����f�[�^�ۑ�
***********************************************************************************/
//void CAutoPCView::HlpSaveRouteData(char *cpBuf,int nLen)
//{
//	CFile file;
//	if(file.Open(L"\\Storage Card\\RouteData.dat", CFile::modeCreate | CFile::modeWrite) == FALSE)return;
//	file.Write(cpBuf,nLen);
//	file.Close();
//}
/***********************************************************************************
*	���ӌ����|�C���g���l��
***********************************************************************************/
/*BOOL CAutoPCView::HlpSocConnectAndSendG1G2(CString *strpSQL)
{
	CString strG1Code,strG2Code;
	if(m_pSearch->GetG1G2Code(&strG1Code,&strG2Code) == FALSE)return FALSE;

	double	XS, YS, XE, YE;
	CString S1, S2, S3, S4;
	m_VView2.GetDispArea2(m_dfClientCenterEW,m_dfClientCenterNS,&XS, &YS, &XE, &YE);
	S1 = m_VView2.RealToStr2(XS);
	S2 = m_VView2.RealToStr2(XE);
	S3 = m_VView2.RealToStr2(YS);
	S4 = m_VView2.RealToStr2(YE);
	strpSQL->Format(L"select EW,NS,Name,Memo from POI where (EW between %s and %s) and (NS between %s and %s) and (G1='%s') and (G2='%s')",
		S1, S2, S3, S4, strG1Code, strG2Code);

	return TRUE;
}
*/
/***********************************************************************************
*	��ԃt���O�ݒ�
***********************************************************************************/
void CAutoPCView::SetMainStatus(int nType,BOOL bVal)
{
	m_bMainStatus[nType] = bVal;


//	CString str;
//	switch(nType){
//		case ST_RUN:str.Format(L"�ʏ푖�s�� %d",bVal);break;
//		case ST_SCROLL:str.Format(L"�X�N���[�����[�h %d",bVal);break;
//		default:return;
//	}
//	HlpTRACE(str);
}
/***********************************************************************************
*	��ԃt���O�l��
***********************************************************************************/
BOOL CAutoPCView::GetMainStatus(int nType)
{
	return m_bMainStatus[nType];
}


/***********************************************************************************
*	WAITDLG�\��
***********************************************************************************/
//void CAutoPCView::HlpWaitDlg(BOOL bMode,CString strMsg/*=""*/)
//{
/*	if(strMsg == "") strMsg = m_strWaitDlgMsg;
	

	if(bMode == TRUE){
		SetMainStatus(ST_WAIT,TRUE);
		if(strMsg == "")m_pDlgWait->m_stMsg = L"Please Wait...";
		else						m_pDlgWait->m_stMsg = strMsg;

		if(m_pDlgWait->GetSafeHwnd() == 0){
			m_pDlgWait->Create(this,IDX_DLG_WAIT);
		}
		else{
//			m_pDlgWait->UpdateData(FALSE);
		}
	}
	else{
		SetMainStatus(ST_WAIT,FALSE);
		if(m_pDlgWait->GetSafeHwnd() != 0){
			m_pDlgWait->DestroyWindow();
//			PostMessage(WM_DLG_CLOSE,IDX_DLG_WAIT);
		}
	}

	m_strWaitDlgMsg="";
}
*/
/***********************************************************************************
*	WAITDLG�����N���[�Y�ݒ�
***********************************************************************************/
//void CAutoPCView::HlpWaitDlgAutoClose(int nMSec)
//{
//	if(SetTimer(TO_WAIT_DLG_AUTO_CLOSE,nMSec,NULL) != TO_WAIT_DLG_AUTO_CLOSE){
//		HlpTRACE("TO_WAIT_DLG_AUTO_CLOSE Timer err");
//	}
//}

/****************************************************************************
*  ������ɍ������t�@�C���t�H���_����ݒ�
*****************************************************************************/
BOOL CAutoPCView::SetFileFolder()
{
	CFile file;
	m_strDataPath = DATA_PATH_1ST;
	if(file.Open(m_strDataPath+FILE_IDX_ROAD9, CFile::modeRead) != FALSE){
		file.Close();
		return TRUE;
	}


	m_strDataPath = DATA_PATH_2ND;
	if(file.Open(m_strDataPath+FILE_IDX_ROAD9, CFile::modeRead) != FALSE){
		file.Close();
		return TRUE;
	}


	m_strDataPath = DATA_PATH_3RD;
	if(file.Open(m_strDataPath+FILE_IDX_ROAD9, CFile::modeRead) != FALSE){
		file.Close();
		return TRUE;
	}

	m_strDataPath = "";
	return FALSE;
}
/***********************************************************************************
*	���݂̊��ϐ��ۑ�
***********************************************************************************/
void CAutoPCView::HlpSaveENV()
{
//#ifdef DATA_CDROM
//	return;
//#endif

//	if(m_bDemoRun == TRUE)return;		//demo��


	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��
//	m_pGPS->GetENPoint(&dfEW,&dfNS);

//	if(dfEW < 126 || dfEW > 128)return;
//	if(dfNS < 36  || dfNS > 38)return;

	m_nStartAngle = m_VView2.GetAngle();	//�A���O���l��

	CString str;
	char cpBuf[100],tmp[100];
	memcpy(&cpBuf[0],&dfEW,8);
	memcpy(&cpBuf[8],&dfNS,8);
	memcpy(&cpBuf[16],&m_nStartAngle,4);
	memcpy(&cpBuf[20],&m_nMapLevel,4);

	memset(tmp,0,10);
	memcpy(tmp,m_Tool.CStringToChar(m_strID),m_strID.GetLength());
	memcpy(&cpBuf[24],tmp,10);
	memset(tmp,0,20);
	memcpy(tmp,m_Tool.CStringToChar(m_strDial),m_strDial.GetLength());
	memcpy(&cpBuf[34],tmp,20);
	memcpy(&cpBuf[54],&m_nRouteOnOff,4);
	memcpy(&cpBuf[58],m_zEnv,4);


	CFile file;
	if(file.Open(m_strDataPath+FILE_START_EN, CFile::modeCreate | CFile::modeWrite) == FALSE)return;
	file.Write(cpBuf,62);
	file.Close();

}
/***********************************************************************************
*	�ۑ��ς݂̊��ϐ��ǂݏo��
***********************************************************************************/
void CAutoPCView::HlpLoadENV(double *dfpEW,double *dfpNS,int *npAngle,int *npMapLevel,
							 CString *strpID,CString *strpDial,int *npRoute)
{
	CFile file;
	char cpBuf[100],tmp[100];

	HlpSetDefaultEWNS(dfpEW,dfpNS);			//�ܓx�o�x�����l�ݒ�
	*npAngle = 90;
	*npMapLevel = 8;
	*strpID		= "";
	*strpDial	= "";
	*npRoute	= 0;		//0:���[�g�ݒ�Ȃ� 1:���[�g�ݒ肠��

	if(file.Open(m_strDataPath+FILE_START_EN, CFile::modeRead) == FALSE)	return; //NG
	if(file.Read(cpBuf,62) != 62){
		file.Close();
		return;		//NG
	}
	file.Close();
	memcpy(dfpEW,&cpBuf[0],8);
	memcpy(dfpNS,&cpBuf[8],8);
	memcpy(npAngle,&cpBuf[16],4);
	memcpy(npMapLevel,&cpBuf[20],4);
	memcpy(tmp,&cpBuf[24],10);
	tmp[10]=0;
//	strpID->Format(L"%s",tmp);
	*strpID = tmp;
	memcpy(tmp,&cpBuf[34],20);
	tmp[20]=0;
//	strpDial->Format(L"%s",tmp);
	*strpDial = tmp;
	memcpy(npRoute,&cpBuf[54],4);
	memcpy(m_zEnv,&cpBuf[58],4);

}
/***********************************************************************************
*	�ܓx�o�x�����l�ݒ�
***********************************************************************************/
void CAutoPCView::HlpSetDefaultEWNS(double *dfpEW,double *dfpNS)
{
	CFile file;
	int nEW;

	*dfpEW = 0.0;
	*dfpNS = 0.0;

	if(file.Open(m_strDataPath+FILE_DAT_ROAD9, CFile::modeRead) == FALSE)	return; //NG
	if(file.Read(&nEW,4) != 4){
		file.Close();
		return;
	}
	
	file.Close();

	if(nEW < 0){
		m_nCountry = COUNTRY_USA;
		*dfpEW = DEFAULT_START_EW_USA;
		*dfpNS = DEFAULT_START_NS_USA;
	}
	else{
		m_nCountry = COUNTRY_KOREA;
		*dfpEW = DEFAULT_START_EW_KOREA;
		*dfpNS = DEFAULT_START_NS_KOREA;
	}
}
/***********************************************************************************
*	���S����̎��ԕ\���I�t�Z�b�g�ݒ�
*	nType 0:�ʏ� 1:UP�X�N���[���� 2:DOWN�X�N���[����
***********************************************************************************/
void CAutoPCView::HlpSetCenterOffsetCar(int nType/*=0*/)
{
	switch(nType){
		case 1:
			m_nClientCenterOffsetCar = -m_RECTClient.bottom /2;	//���S����̎��ԕ\���I�t�Z�b�g
			break;
		case 2:
			m_nClientCenterOffsetCar = m_RECTClient.bottom /2;	//���S����̎��ԕ\���I�t�Z�b�g
			break;
		default:
			m_nClientCenterOffsetCar = m_RECTClient.bottom /4;	//���S����̎��ԕ\���I�t�Z�b�g
			break;
	}
}
/***********************************************************************************
*	ID���M
***********************************************************************************/
void CAutoPCView::HlpSendID()
{
	if(m_bOnline == FALSE)return;
	if(m_bReceiveGPS == FALSE)return;
	if(m_pSoc != NULL)return;

	m_nSendIDCnt++;
	if(m_nSendIDCnt < 60)return;
	m_nSendIDCnt=0;

	if(m_strID == "")return;		//���ݒ�

	//ID���M
	double dfEW,dfNS;
	m_StructSearchID.cType = 1;//1:set 2:get 3:rspOK 4:rspNG
	strcpy((char*)(&m_StructSearchID.cID[0]),m_Tool.CStringToChar(m_strID));
	m_pGPS->GetENPoint(&dfEW,&dfNS);						//GPS���W
	m_StructSearchID.dwEW = (DWORD)(dfEW*DEF_CONVERT);
	m_StructSearchID.dwNS = (DWORD)(dfNS*DEF_CONVERT);

	PostMessage(WM_EVENT,EV_SOC_CONNECT,SOC_SEND_ID);//ID���M
}
/***********************************************************************************
*	TRACE
***********************************************************************************/
//void CAutoPCView::HlpTRACE(CString str)
//{
//	if(m_bTRACE == FALSE)return;
//	m_pTRACE->Trace(str + L"[view]");
//}
/***********************************************************************************
*	TRACE
***********************************************************************************/
void CAutoPCView::HlpTRACE(int nVal)
{
	CString str;
	str.Format(L"%d",nVal);
	HlpTRACE(str);
}

/****************************************************************************
*  TRACE��MSG���M
*   level 0:�ʒm 1:�x�� 2:�װ
*****************************************************************************/
void CAutoPCView::HlpTRACE(CString str,int level /* =0 */)
{
//	if(m_bTRACE == FALSE)return;
	CString msg;

	switch(level){
		case 1:msg=L"+++ ";break;
		case 2:msg=L"*** ";break;
		case 3:msg=L">>> ";break;
		default:msg=L"--- ";break;
	}
	TRACE(msg + str + L"[view]");
}




/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
*****************************************************************************/
LONG CAutoPCView::OnEvent(UINT wParam, LONG lParam)
{
	CString str;
	switch(wParam){
		case EV_SET_DIAL:								//�����1
			str.Format(L"mtx %d 1",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E1();return 0;
				case 2:HlpS2E1();return 0;
				case 3:HlpS3E1();return 0;
			}
			break;
		case EV_INIT:								//�����2
			str.Format(L"mtx %d 2",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E2();return 0;
				case 2:HlpS2E2();return 0;
				case 3:HlpS3E2();return 0;
			}
			break;
		case EV_RECEIVE_NOTIFI:					//�����3
//			str.Format(L"mtx %d 3",m_nStatus);
//			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E3();return 0;
				case 2:HlpS2E3();return 0;
				case 3:HlpS3E3();return 0;
			}
			break;
//		case EV_ROUTE:						//�����4
//			str.Format(L"mtx %d 4",m_nStatus);
//			HlpTRACE(str);
//			switch(m_nStatus){
//				case 1:HlpS1E4();return 0;
//				case 2:HlpS2E4();return 0;
//				case 3:HlpS3E4();return 0;
//			}
//			break;
		case EV_VVIEW4:						//�����5
			str.Format(L"mtx %d 5",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E5();return 0;
				case 2:HlpS2E5();return 0;
				case 3:HlpS3E5();return 0;
			}
			break;
		case EV_BAKCOLOR:						//�����6
			str.Format(L"mtx %d 6",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E6();return 0;
				case 2:HlpS2E6();return 0;
				case 3:HlpS3E6();return 0;
			}
			break;
		case EV_THREAD_END:						//�����7
			str.Format(L"mtx %d 7",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E7();return 0;
				case 2:HlpS2E7();return 0;
				case 3:HlpS3E7();return 0;
			}
			break;
		case EV_SEARCH:						//�����8
			str.Format(L"mtx %d 8",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E8();return 0;
				case 2:HlpS2E8();return 0;
				case 3:HlpS3E8();return 0;
			}
			break;
		case EV_SEARCH2:							//�����9
			str.Format(L"mtx %d 9",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E9();return 0;
				case 2:HlpS2E9();return 0;
				case 3:HlpS3E9();return 0;
			}
			break;
		case EV_SEARCH_ID:						//�����10
			str.Format(L"mtx %d 10",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E10();return 0;
				case 2:HlpS2E10();return 0;
				case 3:HlpS3E10();return 0;
			}
			break;
		case EV_JUMP_EWNS:				//�����11
			str.Format(L"mtx %d 11",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E11();return 0;
				case 2:HlpS2E11();return 0;
				case 3:HlpS3E11();return 0;
			}
			break;
		case EV_MAP_LEVEL:						//�����12
			str.Format(L"mtx %d 12",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E12(int(lParam));return 0;
				case 2:HlpS2E12();return 0;
				case 3:HlpS3E12();return 0;
			}
			break;
		case EV_MAP_LEVEL_FORCE:							//�����13
			str.Format(L"mtx %d 13",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E13(int(lParam));return 0;
				case 2:HlpS2E13();return 0;
				case 3:HlpS3E13();return 0;
			}
			break;
		case EV_GPS_RECEIVE_START:							//�����14
			str.Format(L"mtx %d 14",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E14();return 0;
				case 2:HlpS2E14();return 0;
				case 3:HlpS3E14();return 0;
			}
			break;
		case EV_GPS_RECEIVE_STOP:							//�����15
			str.Format(L"mtx %d 15",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E15();return 0;
				case 2:HlpS2E15();return 0;
				case 3:HlpS3E15();return 0;
			}
			break;
		case EV_SOC_CONNECT:							//�����16
			str.Format(L"mtx %d 16",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E16((int)lParam);return 0;
				case 2:HlpS2E16();return 0;
				case 3:HlpS3E16();return 0;
			}
			break;
		case EV_SOC_RECEIVE_NOTIF:						//�����17
//			str.Format(L"mtx %d 17",m_nStatus);
//			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E17();return 0;
				case 2:HlpS2E17();return 0;
				case 3:HlpS3E17();return 0;
			}
		case EV_SOC_CLOSE:						//�����18
			str.Format(L"mtx %d 18",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E18();return 0;
				case 2:HlpS2E18();return 0;
				case 3:HlpS3E18();return 0;
			}
			break;
		case EV_APP_EXIT:							//�����19
			str.Format(L"mtx %d 19",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E19();return 0;
				case 2:HlpS2E19();return 0;
				case 3:HlpS3E19();return 0;
			}
			break;
		case EV_START_DEMO:						//�����20
			str.Format(L"mtx %d 20",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E20();return 0;
				case 2:HlpS2E20();return 0;
				case 3:HlpS3E20();return 0;
			}
			break;
		case EV_STEP_DEMO:					//�����21
			str.Format(L"mtx %d 21",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E21();return 0;
				case 2:HlpS2E21();return 0;
				case 3:HlpS3E21();return 0;
			}
			break;
//		case EV_STOP_DEMO:					//�����22
//			str.Format(L"mtx %d 22",m_nStatus);
//			HlpTRACE(str);
//			switch(m_nStatus){
//				case 1:HlpS1E22();return 0;
//				case 2:HlpS2E22();return 0;
//				case 3:HlpS3E22();return 0;
//			}
			break;
		case EV_TRCAE_DLG:					//�����23
			str.Format(L"mtx %d 23",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E23();return 0;
				case 2:HlpS2E23();return 0;
				case 3:HlpS3E23();return 0;
			}
			break;
		case EV_WAIT_ENABLE:					//�����24
			str.Format(L"mtx %d 24",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E24();return 0;
				case 2:HlpS2E24();return 0;
				case 3:HlpS3E24();return 0;
			}
			break;
		case EV_WAIT_DISABLE:					//�����25
			str.Format(L"mtx %d 25",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E25((int)lParam);return 0;
				case 2:HlpS2E25();return 0;
				case 3:HlpS3E25();return 0;
			}
			break;
		case EV_LOG_CLR:					//�����26
			str.Format(L"mtx %d 26",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E26();return 0;
				case 2:HlpS2E26();return 0;
				case 3:HlpS3E26();return 0;
			}
			break;
		case EV_TEST:					//�����27
			str.Format(L"mtx %d 27",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E27();return 0;
				case 2:HlpS2E27();return 0;
				case 3:HlpS3E27();return 0;
			}
			break;
		case EV_RAS:					//�����28
			str.Format(L"mtx %d 28",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E28((int)lParam);return 0;
				case 2:HlpS2E28();return 0;
				case 3:HlpS3E28();return 0;
			}
			break;
		case EV_MENU_CLOSE:					//�����29
			str.Format(L"mtx %d 29",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E29();return 0;
				case 2:HlpS2E29();return 0;
				case 3:HlpS3E29();return 0;
			}
			break;

		case EV_T1_TO:							//�����101
//			str.Format(L"mtx %d 101",m_nStatus);
//			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E101();return 0;
				case 2:HlpS2E101();return 0;
				case 3:HlpS3E101();return 0;
			}
			break;
		case EV_T2_TO:							//�����102
			str.Format(L"mtx %d 102",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E102();return 0;
				case 2:HlpS2E102();return 0;
				case 3:HlpS3E102();return 0;
			}
			break;
		case EV_T3_TO:							//�����103
			str.Format(L"mtx %d 103",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E103();return 0;
				case 2:HlpS2E103();return 0;
				case 3:HlpS3E103();return 0;
			}
			break;
		case EV_T4_TO:							//�����104
			str.Format(L"mtx %d 104",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E104();return 0;
				case 2:HlpS2E104();return 0;
				case 3:HlpS3E104();return 0;
			}
			break;
		case EV_T5_TO:							//�����105
			str.Format(L"mtx %d 105",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E105();return 0;
				case 2:HlpS2E105();return 0;
				case 3:HlpS3E105();return 0;
			}
			break;
		case EV_T6_TO:							//�����106
			str.Format(L"mtx %d 106",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E106();return 0;
				case 2:HlpS2E106();return 0;
				case 3:HlpS3E106();return 0;
			}
			break;
		case EV_T7_TO:							//�����107
			str.Format(L"mtx %d 107",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E107();return 0;
				case 2:HlpS2E107();return 0;
				case 3:HlpS3E107();return 0;
			}
			break;
		case EV_T8_TO:							//�����108
			str.Format(L"mtx %d 108",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E108();return 0;
				case 2:HlpS2E108();return 0;
				case 3:HlpS3E108();return 0;
			}
			break;
		case EV_T9_TO:							//�����109
			str.Format(L"mtx %d 109",m_nStatus);
			HlpTRACE(str);
			switch(m_nStatus){
				case 1:HlpS1E109();return 0;
				case 2:HlpS2E109();return 0;
				case 3:HlpS3E109();return 0;
			}
			break;


		default:
			str.Format(L"mtx %d [%d] This event not defined.",m_nStatus,wParam);
			HlpTRACE(str,TRACE_WARNING);
			break;
	}
	return 0L;
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E1()
{
	if(m_pDial->GetSafeHwnd() == 0){
		m_pDial->Create(this,&m_strID,&m_strDial,IDX_DLG_DIAL);
		return;
	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E2()
{
	HlpInit();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E3()
{
	KillTimer(TO_CYCLE_1);		//��������1

//	if(GetMainStatus(ST_SCROLL) == TRUE)goto TAG_EXIT;//�X�N���[�����[�h	ON

	if(HlpRs232cReceive() == FALSE){
		m_bReceiveGPS = FALSE;
		HlpReDraw();
		goto TAG_EXIT;
	}

	if(GetMainStatus(ST_SCROLL) == TRUE)goto TAG_EXIT;//�X�N���[�����[�h	ON

	m_bReceiveGPS = TRUE;
	HlpRs232cDraw();

TAG_EXIT:

//	if(m_pSearch2->GetSafeHwnd() == 0){		//�J���Ă��Ȃ�
//		SetFocus();				//�����͊Ď�
//	}

	if(SetTimer(TO_CYCLE_1,TO_VAL_CYCLE_1,NULL) != TO_CYCLE_1){		//��������1
		MessageBox(L"TO_CYCLE_1 Timer err");
	}


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E4()
{
//	if(m_pRoute->GetSafeHwnd() == 0){
//		BOOL b=FALSE;
//		if(m_nRouteOnOff == 1)b = TRUE;
//		m_pRoute->Create(this,b,IDX_DLG_ROUTE);
//		return;
//	}

//	HlpWaitDlg(TRUE);
//	m_pSearch2->AllClr();		//�ݒ�f�[�^�N���A
//	m_nRouteOnOff=0;
//	HlpVPaint();				//V2����`��
//	HlpWaitDlg(FALSE);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E5()
{
	if(GetMainStatus(ST_MAPMACH_VIEW) == TRUE){//�}�b�v�}�b�`��ʕ\��(debug�p)
		SetMainStatus(ST_MAPMACH_VIEW,FALSE);
	}
	else{
		SetMainStatus(ST_MAPMACH_VIEW,TRUE);
	}
	HlpVPaint();				//V2����`��
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E6()
{
	if(m_nBkColor == DEFAULT_BACKCOLOR){
		m_nBkColor = RGB(0,0,0);
	}
	else{
		m_nBkColor = DEFAULT_BACKCOLOR;
	}
	HlpVPaint();				//V2����`��
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E7()
{
	if(HlpV2DrawThreadDelete() == TRUE){
//		m_nThreadDeleteWatchCnt=0;//�گ�ޏI���Ď��J�E���^(�w��l�ɒB�����ꍇ�ͽگ�ނ������I������B)
//		KillTimer(TO_THREAD);
//		HlpVPaint3();
	}

}	
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E8()
{
	if(m_bOnline == FALSE){
//		HlpWaitDlg(TRUE,L"Offline is no support.");
//		HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
		return;
	}

//	if(m_pSearch->GetSafeHwnd() != 0)return;
//	m_pSearch->Create(this,IDX_DLG_SEARCH);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E9()
{
//	if(m_pSearch2->GetSafeHwnd() != 0)return;
//	m_pSearch2->Create(this,IDX_DLG_SEARCH2);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E10()
{
	if(m_bOnline == FALSE){
//		HlpWaitDlg(TRUE,L"Offline is no support.");
//		HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
		return;
	}

	if(m_pSearchID->GetSafeHwnd() != 0)return;
	m_pSearchID->Create(this,IDX_DLG_SEARCH_ID);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E11()
{
//	HlpWaitDlg(TRUE);
//	HlpWaitDlgAutoClose(3000);		//WaitDlgAutoClose

	SetMainStatus(ST_SCROLL,TRUE);//�X�N���[�����[�h
	HlpVPaint();				//V2����`��
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E12(int nMapLevel)
{
	if(nMapLevel == 0){		//ZOOM OUT
		if(m_nMapLevel < 3)return;
		m_nMapLevel--;
	}
	else{
		if(m_nMapLevel > 9)return;
		m_nMapLevel++;
	}

	
//	if(m_pMapLevel->GetSafeHwnd() == 0){
//		m_pMapLevel->Create(m_nMapLevel-2,this,IDX_DLG_MAP_LEVEL);
//		return;
//	}
//	if(m_nMapLevel == nMapLevel)return;
//	HlpWaitDlg(TRUE);
//	HlpWaitDlgAutoClose(5000);		//WaitDlgAutoClose
//	m_nMapLevel = nMapLevel;
	HlpVPaint();


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E13(int nMapLevel)
{
	m_nMapLevel = nMapLevel;
	HlpVPaint();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E14()
{
	SetMainStatus(ST_RUN,TRUE);	//�ʏ푖�s�� ON
//	if(m_pSearch2->m_nNodeCntMax > 0){
//		m_pSearch2->SetInfo(m_pSearch2->m_nNodeCntMax,FALSE);	//�m�[�h�f�[�^���g�p�ݒ�
//	}
	HlpRs232cStart();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E15()
{
	SetMainStatus(ST_RUN,FALSE);//�ʏ푖�s�� OFF
	HlpRs232cStop();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E16(int nSocReqType)
{
	if(m_bOnline == FALSE){
		HlpConnectOffline(nSocReqType);		//��ײݎ��̏���
		return;
	}

//------------online---------------------------------------
	m_nSocReqType = nSocReqType;
	HlpSocConnectAndSend(m_nSocReqType);
}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E17()
{
	int n = m_pSoc->Receive((char*)(&m_SocBuf[m_nSocReceiveSize]),BUF_SIZE);
	m_nSocReceiveSize += n;
	if(m_nSocReceiveSize > BUF_SIZE - 2000){
		HlpTRACE(L"Receive buff full");
		m_nSocReceiveSize=0;
		m_bSocReceiveFault = TRUE;
	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E18()
{
	m_pSoc->Close();
	delete m_pSoc;
	m_pSoc = NULL;
//	HlpTRACE(L"Soc Close OK");
//	if(m_bSocReceiveFault == TRUE)return;
//	HlpSocReceiveAndClose();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E19()
{
//	HlpWaitDlg(TRUE,L"Shutdown....Please Wait.");
/*	if(m_pThread->m_pThread != NULL){
		HlpTRACE(L"Useed Thread");
		if(m_bAppExit == FALSE){
			if(SetTimer(TO_APP_EXIT,TO_VAL_APP_EXIT,NULL) != TO_APP_EXIT){
				HlpTRACE(L"TO_APP_EXIT Timer err");
			}				
			m_bAppExit = TRUE;
		}
		return;
	}

	if(m_pComm != NULL){
		if(m_bAppExit == FALSE){
			SetTimer(TO_APP_EXIT,TO_VAL_APP_EXIT,NULL);
			m_bAppExit = TRUE;
		}
		m_pComm->CloseComm();
	}
*/

/*
	if(m_pComm != NULL){
		m_pComm->CloseComm();				//232c�۰��
	}
	m_pThread->Stop();					//�`��گ�ޒ�~

	HlpSaveENV();						//���݂̊��ϐ��ۑ�
	GetOwner()->PostMessage(WM_EVENT,EV_APP_EXIT);
*/
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E20()
{
	m_Dijkstra.WabPlayInit();		//�m�[�hturn���������ē��ς݃t���O������(���ē�)

	SetMainStatus(ST_SCROLL,FALSE);						//�X�N���[�����[�hOFF
	m_nTestCnt = 1;
	if(SetTimer(TO_DEMO_RUN,TO_VAL_DEMO_RUN,NULL) != TO_DEMO_RUN){
		HlpTRACE("TO_DEMO_RUN Timer err");
	}
//	if(m_pSearch2->m_nNodeCntMax > 0){
//		m_pSearch2->SetInfo(m_pSearch2->m_nNodeCntMax,FALSE);	//�m�[�h�f�[�^���g�p�ݒ�
//	}
#ifdef AUTO_PC
	SetMainStatus(ST_RUN,FALSE);						//�ʏ푖�s�� OFF
//	if(GetMainStatus(ST_RUN) == FALSE){
//		HlpWaitDlg(TRUE,L"Demo Initialing...");
//	}
	HlpRs232cStop();
#endif
	if(GetMainStatus(ST_RUN) == FALSE){
//		HlpSetRouteData(m_strDataPath+DEMO_FILE_ROUTE);				//���[�g�����f�[�^�ݒ�
		HlpTRACE(_T("start demo"));
		m_bDemoRun = TRUE;
//		HlpWaitDlg(FALSE);
	}
	SetMainStatus(ST_RUN,TRUE);							//�ʏ푖�s�� ON
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E21()
{
	int nRet = m_pGPS->Test(m_strDataPath,m_nTestCnt);
	if(nRet == -1){
		KillTimer(TO_DEMO_RUN);
		m_nTestCnt=1;
		if(m_bDemo ==  TRUE){
			HlpTRACE(_T("restart demo"));
//			HlpSetRouteData(m_strDataPath+DEMO_FILE_ROUTE,TRUE);		//���[�g�����f�[�^�N���A
			SetMainStatus(ST_RUN,FALSE);
			PostMessage(WM_EVENT,EV_START_DEMO);	//�ċN��

//OnRouteReSearch();							//�����[�g�ݒ�

		}
		else{
//			HlpWaitDlg(TRUE,L"Demo Exiting...");
			HlpTRACE(_T("end demo"));
			m_bDemoRun = FALSE;
//			HlpSetRouteData(m_strDataPath+DEMO_FILE_ROUTE,TRUE);				//���[�g�����f�[�^�N���A
			SetMainStatus(ST_RUN,FALSE);
			m_bDemo = TRUE;
#ifdef AUTO_PC
//			SendMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n
			PostMessage(WM_EVENT,EV_GPS_RECEIVE_START);	//GPS��M�J�n
//			HlpWaitDlg(FALSE);
#endif
		}
		return;
	}

	double dfEW,dfNS;
	m_nTestCnt=2;
	if(nRet == 1){
		m_pGPS->GetENPoint(&dfEW,&dfNS);
		HlpAutoDemo(dfEW,dfNS,m_pGPS->GetAngle());
	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E22()
{
//	m_bDemo = FALSE;
//	PostMessage(WM_EVENT,EV_START_DEMO);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E23()
{
//	if(m_pTRACE->GetSafeHwnd() == 0){
//		m_pTRACE->Create(this,IDX_DLG_TRACE);
//		return;
//	}
//	m_pTRACE->SetFocus();
//	if(m_pTRACE->GetSafeHwnd() == 0)break;			//DLG�͊J���Ă��Ȃ�
//	m_pTRACE->DestroyWindow();

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E24()
{
//	HlpWaitDlg(TRUE);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E25(int nVal)
{
	if(nVal == 0){
//		HlpWaitDlg(FALSE);
	}
	else{
//		HlpWaitDlgAutoClose(nVal);		//WaitDlgAutoClose
	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E26()
{
//	HlpWaitDlg(TRUE,L"Log Clear.");
//	HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
	m_pDriveLog->Clr();
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E27()
{
	HlpTRACE(L"-------Start test----------");


	HlpTRACE(L"-------End test----------");

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E28(int nEntryPos)
{
	if(nEntryPos == -1){				//�G���g���I�����
		if(m_pRasEntry->GetSafeHwnd() == 0){
			m_pRasEntry->Create(this,&m_strRasEntryName,IDX_DLG_RAS_ENTRY);
			return;
		}
		return;
	}



	if(m_bRas == TRUE){
//		HlpWaitDlg(TRUE,L"Disconnect.");
//		HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
		m_Ras.Close();
		m_bOnline = FALSE;
		m_bRas = FALSE;
		return;
	}

//	TCHAR EntryName[20] = RAS_NEWENTRY;
//	TCHAR PhoneNo[20]   = RAS_PHONENO;
//	TCHAR UserName[20]	= RAS_USERNAME;
//	TCHAR Password[20]	= RAS_PASSWORD;
//	TCHAR Password[20]	= L"";


//	HlpWaitDlg(TRUE,L"Dialing... " + m_strDial);
//	if(m_Ras.NewEntry(EntryName,m_strDial,UserName,Password) == FALSE){
//		Sleep(500);
//		if(m_Ras.NewEntry(EntryName,m_strDial,UserName,Password) == FALSE){
//			HlpWaitDlg(FALSE);
//			HlpWaitDlg(TRUE,L"NewEntry err");
//			HlpWaitDlgAutoClose(1000);		//WaitDlgAutoClose
//			return;
//		}
//	}

	if(m_Ras.Connect(m_hWnd,m_strRasEntryName) == FALSE){
//		HlpWaitDlg(FALSE);
//		HlpWaitDlg(TRUE,L"Can't connected.");
//		HlpWaitDlgAutoClose(1000);			//WaitDlgAutoClose
		return;

	}
	m_bRas = TRUE;
	m_bOnline = TRUE;
	SetTimer(TO_RAS_CONNECT_CHK,TO_VAL_RAS_CONNECT_CHK,NULL);

//	HlpWaitDlg(FALSE);
//	HlpWaitDlg(TRUE,L"connected.");
//	HlpWaitDlgAutoClose(1000);			//WaitDlgAutoClose


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E29()
{
//	if(m_pDlgMenu->GetSafeHwnd() != 0){	//���j���[���J���Ă���
//		m_pDlgMenu->DestroyWindow();	//���j���[�N���[�Y
//	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E101()
{
//	KillTimer(TO_CYCLE_1);		//��������1
//	HlpSendID();				//ID���M
//	PostMessage(WM_EVENT, EV_RECEIVE_NOTIFI);//GPS�f�[�^�`��
//	SetFocus();				//�����͊Ď�
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E102(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E103(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E104(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
//{
//	if(g_bV2DrawThreadMainRun == TRUE){	//���쒆
//		m_nThreadDeleteWatchCnt++;//�گ�ޏI���Ď��J�E���^(�w��l�ɒB�����ꍇ�ͽگ�ނ������I������B)
//		if(m_nThreadDeleteWatchCnt < 20)	return;
//		HlpTRACE(L"ThreadDeleteWatchCnt over.",TRACE_WARNING);
//	}

//	if(HlpV2DrawThreadDelete() == TRUE){
//		m_nThreadDeleteWatchCnt=0;//�گ�ޏI���Ď��J�E���^(�w��l�ɒB�����ꍇ�ͽگ�ނ������I������B)
//		KillTimer(TO_THREAD);
//		HlpVPaint3();
//	}
//}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E105(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E106()
{
//	KillTimer(TO_AUTO_ZOOM);
//	HlpAutoZoom(3);//�������A
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E107(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E108()
{
	KillTimer(TO_WAIT_DLG_AUTO_CLOSE);
//	HlpWaitDlg(FALSE);
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS1E109()
{
	if(m_pThread->m_pThread != NULL){
		HlpTRACE(L"Now wait thread start.");
		return;
	}
	KillTimer(TO_WAIT_THEAD_START);
	m_bWaitThreadStart = FALSE;	//�`��҂��� ����
	HlpVPaint();				//V2����`��
}


/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E1(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E2(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E3(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E4(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E5(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E6(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E7(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E8(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E9(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E10(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E11(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E12(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E13(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E14(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E15(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E16(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E17(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E18(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E19(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E20(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E21(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E22(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E23(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E24(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E25(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E26(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E27(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E28(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E29(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E101(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E102(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E103(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E104(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E105(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E106(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E107(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E108(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS2E109(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}



/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E1(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E2(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E3(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E4(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E5(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E6(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E7(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E8(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E9(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E10(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E11(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E12(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E13(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E14(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E15(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E16(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E17(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E18(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E19(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E20(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E21(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E22(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E23(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E24(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E25(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E26(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E27(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E28(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E29(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E101(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E102(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E103(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E104(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E105(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E106(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E107(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E108(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CAutoPCView::HlpS3E109(){HlpTRACE("This MTX not PASS.",TRACE_ERR);}


void CAutoPCView::OnZoomIn() 
{
HlpS1E12(1);
	
}

void CAutoPCView::OnZoomOut() 
{
HlpS1E12(0);
	
}

/***************************************************************************************
*	��ӊJ�n�{�^��
***************************************************************************************/
void CAutoPCView::OnDemoStart() 
{
	if(HlpDemoData() == FALSE)return;			//���[�g�`��O�Ղ���f���p��GPS��M�f�[�^�쐬 
	PostMessage(WM_EVENT,EV_START_DEMO);
	m_nMenuStatusRoute				= 4;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
}
/***************************************************************************************
*	��Ӓ�~�{�^��
***************************************************************************************/
void CAutoPCView::OnDemoStop() 
{
	m_bDemo = FALSE;
	PostMessage(WM_EVENT,EV_START_DEMO);
	m_nMenuStatusRoute				= 3;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
}


/***************************************************************************************
*	���[�g�`��O�Ղ���f���p��GPS��M�f�[�^�쐬
***************************************************************************************/
BOOL CAutoPCView::HlpDemoData()
{
	if(m_Dijkstra.m_nNodeTraceCnt < 3)return FALSE;		//���[�g���ݒ�

	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	MSG message;


	char tmp[1024];
	double dfEW1,dfNS1;
	double dfEW2,dfNS2;
	int i,ii,iii,nAngle=0,nCnt=0;
	CFile file;
	CTool tool;
	CCommon comm;

	if(file.Open(m_strDataPath+DEMO_FILE_GPS, CFile::modeCreate | CFile::modeWrite) == FALSE)return FALSE;	//demoGPS�f�[�^���t�@�C���ɏ�������

	for(i=0;i<m_Dijkstra.m_nNodeTraceCnt-1;i++){
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)){
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}

//		if(m_Dijkstra.m_nNodeTraceCnt < 3)continue;
		if(m_Dijkstra.GetNodeLink(i) == FALSE)break;//�w��m�[�h�ԋO�Տ��l��

		for(ii=1;ii<m_Dijkstra.m_nBlkCnt;ii++){

			dfEW1 = ((double)(m_Dijkstra.m_pNodeLinkBody[ii-1].nEW)) / DEF_CONVERT;	//���̈ʒu����
			dfNS1 = ((double)(m_Dijkstra.m_pNodeLinkBody[ii-1].nNS)) / DEF_CONVERT;
			dfEW2 = ((double)(m_Dijkstra.m_pNodeLinkBody[ii].nEW)) / DEF_CONVERT;	//�����܂�
			dfNS2 = ((double)(m_Dijkstra.m_pNodeLinkBody[ii].nNS)) / DEF_CONVERT;
			nAngle = comm.PointToGpsAngle(dfEW1,dfNS1,dfEW2,dfNS2);//EW1,NS1����_��EW2,NS2�����̂f�o�r�p�x�����߂�B
			nCnt   = comm.DecodeLine(dfEW1,dfNS1,dfEW2,dfNS2);//�����Q�_�Ԃ̈ܓx�o�x���������������W�i�ܓx�o�x�j�����߂� 50km/h�Œ�

			for(iii=0;iii<nCnt;iii++){
				m_pGPS->MakeGPSDataImage(tmp,comm.DemoEW[iii],comm.DemoNS[iii],50,nAngle);			//GPS�t�H�[�}�b�g�쐬
				file.Write(tmp,strlen(tmp));
			}
		}
	}
	file.Close();
	return TRUE;

/*	if(m_Dijkstra.m_nNodeTraceCnt < 3)return FALSE;		//���[�g���ݒ�

	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	MSG message;


	char tmp[1024];
	double dfEW,dfNS,dfSaveEW=0,dfSaveNS=0;
	int i,ii,iii,nAngle=0,nCnt=0;
	CFile file;
	CTool tool;
	CCommon comm;

	if(file.Open(m_strDataPath+DEMO_FILE_GPS, CFile::modeCreate | CFile::modeWrite) == FALSE)return FALSE;	//demoGPS�f�[�^���t�@�C���ɏ�������

	for(i=0;i<m_Dijkstra.m_nNodeTraceCnt-1;i++){
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE)){
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}

//		if(m_Dijkstra.m_nNodeTraceCnt < 3)continue;
		if(m_Dijkstra.GetNodeLink(i) == FALSE)break;//�w��m�[�h�ԋO�Տ��l��

		for(ii=0;ii<m_Dijkstra.m_nBlkCnt;ii++){

			dfEW = ((double)(m_Dijkstra.m_pNodeLinkBody[ii].nEW)) / DEF_CONVERT;	//���̈ʒu����
			dfNS = ((double)(m_Dijkstra.m_pNodeLinkBody[ii].nNS)) / DEF_CONVERT;

			if(dfSaveEW != 0){									//������ԕ��쐬
				if(dfSaveEW != dfEW && dfSaveNS != dfNS){		//����Ă�����
					nAngle = comm.PointToGpsAngle(dfSaveEW,dfSaveNS,dfEW,dfNS);//EW0,NS0����_��EW1,NS1�����̂f�o�r�p�x�����߂�B
				}
				nCnt = comm.DecodeLine(dfSaveEW,dfSaveNS,dfEW,dfNS);//�����Q�_�Ԃ̈ܓx�o�x���������������W�i�ܓx�o�x�j�����߂� 50km/h�Œ�
			}

			for(iii=0;iii<nCnt;iii++){
				m_pGPS->MakeGPSDataImage(tmp,comm.DemoEW[iii],comm.DemoNS[iii],50,nAngle);			//GPS�t�H�[�}�b�g�쐬
				file.Write(tmp,strlen(tmp));
			}

			dfSaveEW = dfEW;
			dfSaveNS = dfNS;

		}
	}
	file.Close();
	return TRUE;
*/
}
/***************************************************************************************
*	���[�g�ݒ�{�^��
***************************************************************************************/
void CAutoPCView::OnRouteSearch() 
{
	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	int nConnectMax;
	m_Dijkstra.Load(m_strDataPath,&nConnectMax,m_nCountry);				//���[�h
	if(m_Dijkstra.Dijkstra(nConnectMax) == FALSE)goto TAG_ERR;			//�S�m�[�h�̍ŒZ��Ԋl��

	m_Dijkstra.GetResultNodeList(m_Dijkstra.m_nStartNode);				//�w��m�[�h�ƂO�m�[�h�Ƃ̍ŒZ�ڑ��m�[�h���X�g�쐬
	m_Dijkstra.MakeDistanceList();										//�e�m�[�h����̎c�苗�����X�g�ݒ�
	m_Dijkstra.MakeNodeTurnSide();										//�m�[�hturn�����ݒ�
	m_Dijkstra.MakeInfoPointList();										//�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�
	m_nMenuStatusRoute				= 3;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
	m_nPassNode = -1;			//�ʉߍς݃m�[�h
	m_nSave100mPos=-1;			//100m��O�ʉ�pos(�O��ʂ����ʒu)
	m_nSaveMapLevel=-1;
	m_nEWScaleUpPoint = -1;		//�X�P�[���_�E���|�C���g����p
	m_nNSScaleUpPoint = -1;

	HlpVPaint();		//V2����`��
	m_Dijkstra.SetStatus(DIJKSTRA_ST_ROUTE);

//	SetTimer(TO_REROUTE,TO_VAL_REROUTE,NULL);		//�ٰċ��Ď����
	return;
TAG_ERR:;
	TRACE(L"RouteSearch err");
}
/***************************************************************************************
*	�����[�g�{�^��
***************************************************************************************/
void CAutoPCView::OnRouteReSearch() 
{
	if(GetMainStatus(ST_SCROLL) == TRUE)return;				//�X�N���[�����[�h

	m_Dijkstra.WavPlay(WAV_ROUTE_OUT);						//���[�g�͂���

	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��
//	m_pGPS->GetENPoint(&dfEW,&dfNS);//GPS��M�ʒu�̈ܓx�o�l��
	m_Dijkstra.m_nStartNode = m_Dijkstra.GetNearNode((int)(dfEW*DEF_CONVERT),
							(int)(dfNS*DEF_CONVERT));//�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l�����ĊJ�n�m�[�h�ݒ�

//	m_Dijkstra.m_nNodeTraceCnt = 1;
	m_Dijkstra.m_nNodeTrace[0] = m_Dijkstra.m_nStartNode;		//�J�n�m�[�h;

	m_Dijkstra.GetResultNodeList(m_Dijkstra.m_nStartNode);				//�w��m�[�h�ƂO�m�[�h�Ƃ̍ŒZ�ڑ��m�[�h���X�g�쐬
	m_Dijkstra.MakeDistanceList();										//�e�m�[�h����̎c�苗�����X�g�ݒ�
	m_Dijkstra.MakeNodeTurnSide();										//�m�[�hturn�����ݒ�
	m_Dijkstra.MakeInfoPointList();										//�e�m�[�h�̃C���t�H���[�V������񃊃X�g�ݒ�
	m_nPassNode = -1;			//�ʉߍς݃m�[�h
	m_nSave100mPos=-1;			//100m��O�ʉ�pos(�O��ʂ����ʒu)
	m_nSaveMapLevel=-1;
	m_nEWScaleUpPoint = -1;		//�X�P�[���_�E���|�C���g����p
	m_nNSScaleUpPoint = -1;


	HlpVPaint();		//V2����`��
	m_Dijkstra.SetStatus(DIJKSTRA_ST_ROUTE);

}
/***************************************************************************************
*	���[�g�N���A�{�^��
***************************************************************************************/
void CAutoPCView::OnRouteClr() 
{
	if(m_bRerouteTimer == TRUE){
		KillTimer(TO_REROUTE);		//�ٰċ��Ď����
		m_bRerouteTimer=FALSE;
	}

	m_Dijkstra.m_nNodeTraceCnt		 = 0;
//	m_nLastDistance					= -1;		//�c�苗��
	m_nDistanceTMP					= 0;		//�c�苗��
//	m_Dijkstra.m_nNextNodeEW		= 0;		//���m�[�h
//	m_Dijkstra.m_nNextNodeNS		= 0;
	m_Dijkstra.m_nStartNode			= 0;
	m_Dijkstra.m_nEndNode			= 0;
	m_nMenuStatusRoute				= 1;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
	m_nPassNode = -1;			//�ʉߍς݃m�[�h
	m_nSave100mPos=-1;			//100m��O�ʉ�pos(�O��ʂ����ʒu)
	m_nSaveMapLevel=-1;

	HlpVPaint();		//V2����`��
	m_Dijkstra.SetStatus(DIJKSTRA_ST_CLR);
}
/***************************************************************************************
*	���[�g�J�n�ʒu
***************************************************************************************/
void CAutoPCView::OnRouteStart() 
{
	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��

	m_Dijkstra.m_nStartNode = m_Dijkstra.GetNearNode((int)(dfEW*DEF_CONVERT),
							(int)(dfNS*DEF_CONVERT));//�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l�����ĊJ�n�m�[�h�ݒ�

	m_Dijkstra.m_nNodeTraceCnt = 1;
	m_Dijkstra.m_nNodeTrace[0] = m_Dijkstra.m_nStartNode;		//�J�n�m�[�h;
	HlpVPaint();		//V2����`��


	if(m_Dijkstra.m_nEndNode	!= 0)m_nMenuStatusRoute=2;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
	

//	m_Dijkstra.SetStatus(DIJKSTRA_ST_SET_START);
}
/***************************************************************************************
*	���[�g�I���ʒu
***************************************************************************************/
void CAutoPCView::OnRouteEnd() 
{
	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��

	m_Dijkstra.m_nEndNode = m_Dijkstra.GetNearNode((int)(dfEW*DEF_CONVERT),
							(int)(dfNS*DEF_CONVERT));//�w��ܓx�o�x�ɋ߂��m�[�h�ԍ��l�����ĊJ�n�m�[�h�ݒ�

	m_Dijkstra.m_nNodeTraceCnt = 2;
	m_Dijkstra.m_nNodeTrace[1] = m_Dijkstra.m_nEndNode;		//�I���m�[�h;
	HlpVPaint();		//V2����`��

	if(m_Dijkstra.m_nStartNode	!= 0)m_nMenuStatusRoute=2;//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j
//	m_Dijkstra.SetStatus(DIJKSTRA_ST_SET_END);
}
/***************************************************************************************
*	���݈ʒu�iGPS��M��ԁj
***************************************************************************************/
void CAutoPCView::OnThisPlace() 
{
	SetMainStatus(ST_SCROLL,FALSE);	//�X�N���[�����[�h OFF
}


/***************************************************************************************
*	���j���[�C�l�[�u��/�f�B�Z�[�u����Ԋl��
***************************************************************************************/
BOOL CAutoPCView::HlpMenuEnable(int nMenuType,int nMenuNo)
{
	if(nMenuType == DEF_MENU_ROUTE){
		switch(nMenuNo){
			case DEF_MENU_ROUTE_START:
			case DEF_MENU_ROUTE_STOP:
				if(m_nMenuStatusRoute < 3)return TRUE;
				break;
			case DEF_MENU_ROUTING:
				if(m_nMenuStatusRoute == 2)return TRUE;
				break;
			case DEF_MENU_REROUTING:
				if(m_nMenuStatusRoute == 3)return TRUE;
				break;
			case DEF_MENU_ROUTE_CLR:
				if(m_nMenuStatusRoute == 2 || m_nMenuStatusRoute == 3)return TRUE;
				break;
			case DEF_MENU_START_DEMO:
				if(m_nMenuStatusRoute == 3)return TRUE;
				break;
			case DEF_MENU_STOP_DEMO:
				if(m_nMenuStatusRoute == 4)return TRUE;
				break;
		}
	}

	return FALSE;
}

/***************************************************************************************
*	���[�g�J�n�ʒu�C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateRouteStart(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_ROUTE_START));}
/***************************************************************************************
*	���[�g�I���ʒu�C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateRouteEnd(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_ROUTE_STOP));}
/***************************************************************************************
*	���[�g�ݒ�{�^���C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateRouteSearch(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_ROUTING));}
/***************************************************************************************
*	�����[�g�ݒ�{�^���C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateRouteReSearch(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_REROUTING));}
/***************************************************************************************
*	���[�g�N���A�{�^���C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateRouteClr(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_ROUTE_CLR));}
/***************************************************************************************
*	�f���J�n�{�^���C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateDemoStart(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_START_DEMO));} 
/***************************************************************************************
*	�f���I���{�^���C�l�[�u��/�f�B�Z�[�u��
***************************************************************************************/
void CAutoPCView::OnUpdateDemoStop(CCmdUI* pCmdUI){pCmdUI->Enable(HlpMenuEnable(DEF_MENU_ROUTE,DEF_MENU_STOP_DEMO));}





/***************************************************************************************
*	�����{�^���i�����j
***************************************************************************************/
void CAutoPCView::OnSearchStruct() 
{
	CDlgSearch dlg(m_strDataPath);
	dlg.DoModal();	

	int nEW,nNS;
	dlg.GetEWNS(&nEW,&nNS);					//�I������
	if(nEW == 0)return;

	SetMainStatus(ST_SCROLL,			TRUE);//�X�N���[�����[�h
	m_dfClientCenterEW = (double)(nEW)/DEF_CONVERT;
	m_dfClientCenterNS = (double)(nNS)/DEF_CONVERT;
	HlpVPaint();		//V2����`��
}
/***************************************************************************************
*	�����{�^���i���ӌ����j
***************************************************************************************/
void CAutoPCView::OnSearchCir() 
{
	CDlgCircumference dlg(m_strDataPath);
	dlg.DoModal();
	if(dlg.m_nRetCode == 0)return;					//0:cancel 1:stop 2:start
	if(dlg.m_nRetCode == 1){						//0:cancel 1:stop 2:start
		m_nCircumferenceListCnt = 0;
		if(m_npCircumferenceListBuf != NULL)delete [] m_npCircumferenceListBuf;
		m_npCircumferenceListBuf = NULL;
		if(m_strpCircumferenceListBuf != NULL)delete [] m_strpCircumferenceListBuf;
		m_strpCircumferenceListBuf = NULL;
		HlpVPaint();		//V2����`��
		return;
	}

	
	m_nCircumferenceListCnt = dlg.GetCircumferenceItemCntMax();//���ӌ���ITEM�����l��
	if(m_npCircumferenceListBuf != NULL)delete [] m_npCircumferenceListBuf;
	m_npCircumferenceListBuf = new int[m_nCircumferenceListCnt*2];

	if(m_strpCircumferenceListBuf != NULL)delete [] m_strpCircumferenceListBuf;
	m_strpCircumferenceListBuf = new CString[m_nCircumferenceListCnt];

	dlg.SetCircumferenceItem(m_npCircumferenceListBuf,m_strpCircumferenceListBuf);			//���ӌ���ITEM�S�Ă̈ܓx�o�x�Ɩ��̂��o�b�t�@�Ɋi�[

	HlpVPaint();		//V2����`��
}
/***************************************************************************************
*	MyMap�{�^���i�o�^�j
***************************************************************************************/
void CAutoPCView::OnMymapSet() 
{
	CDlgMyMap dlg(0,m_strDataPath);

	double dfEW,dfNS;
	HlpGetCurEN(&dfEW,&dfNS);		//�J�[�\���ʒu�̈ܓx�o�l��

	dlg.m_nEW = (int)(dfEW*DEF_CONVERT);
	dlg.m_nNS = (int)(dfNS*DEF_CONVERT);

	dlg.DoModal();	
}
/***************************************************************************************
*	MyMap�{�^���i�l���j
***************************************************************************************/
void CAutoPCView::OnMymapGet() 
{
	CDlgMyMap dlg(1,m_strDataPath);
	if(dlg.DoModal() != IDOK)return;

	SetMainStatus(ST_SCROLL,			TRUE);//�X�N���[�����[�h
	m_dfClientCenterEW = (double)(dlg.m_nEW)/DEF_CONVERT;
	m_dfClientCenterNS = (double)(dlg.m_nNS)/DEF_CONVERT;
	HlpVPaint();		//V2����`��

}
/***************************************************************************************
*	system�{�^��
***************************************************************************************/
void CAutoPCView::OnSystem() 
{
	CDlgSystem dlg(m_nCountry,m_pGPS,m_zEnv);

	int nRet = dlg.DoModal();

	if(m_zEnv[3] == 0)	m_Dijkstra.SetSound(TRUE);			//�����ē��L���ݒ�
	else				m_Dijkstra.SetSound(FALSE);
	if(nRet != IDOK)return;

	#ifdef _DEBUG
	TRACE(L"�I���m�F");
	#else
	if(MessageBox(L"EXIT",L"Power ICNS",MB_YESNO|MB_ICONQUESTION) == IDNO)return;
	#endif

	HlpSaveENV();						//���݂̊��ϐ��ۑ�
	GetOwner()->PostMessage(WM_EVENT,EV_APP_EXIT);			//�I��
}
