// DlgSystem.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/**************************************************************************
*	コンストラクタ
**************************************************************************/
CDlgSystem::CDlgSystem(int nCountry,CGPS *pGPS,char *pzEnv,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSystem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nCountry		= nCountry;
	m_pzEnv			= pzEnv;
	m_pGPS			= pGPS;
	m_pST1			= NULL;
	m_pST2			= NULL;
	m_pST3			= NULL;
	m_pST4			= NULL;
	m_pST5			= NULL;
	m_pBT1			= NULL;
	m_pBT2			= NULL;
	m_pBT3			= NULL;
	m_pBT4			= NULL;
	m_pCB1			= NULL;
	m_pCB2			= NULL;
	m_pCB3			= NULL;
	m_pCB4			= NULL;

	m_nStatus		= 1;

}
/**************************************************************************
*	デストラクタ
**************************************************************************/
CDlgSystem::~CDlgSystem()
{
	HlpDeleteCtl();		//コントロール廃棄
}
/**************************************************************************
*	データエクスチェンジ
**************************************************************************/
void CDlgSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSystem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
/**************************************************************************
*	メッセージマップ
**************************************************************************/
BEGIN_MESSAGE_MAP(CDlgSystem, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//ｲﾍﾞﾝﾄ通知
	ON_BN_CLICKED(101,OnBtn1)						//m_pBT1クリック
	ON_BN_CLICKED(102,OnBtn2)						//m_pBT2クリック
	ON_BN_CLICKED(103,OnBtn3)						//m_pBT3クリック
	ON_BN_CLICKED(104,OnBtn4)						//m_pBT4クリック
	//{{AFX_MSG_MAP(CDlgSystem)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*************************************************************************
*	タイムアウト
**************************************************************************/
void CDlgSystem::OnTimer(UINT nIDEvent) 
{
	if(m_nStatus == 2){//gps
		HlpDispGPSInfo();
	}
	
	CDialog::OnTimer(nIDEvent);
}
/*************************************************************************
*	初期距離
**************************************************************************/
BOOL CDlgSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PostMessage(WM_EVENT,EV_1);		//コントロール構築要求
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/**************************************************************************
*	OKボタン（今はなし）
**************************************************************************/
void CDlgSystem::OnOK() 
{
//	CDialog::OnOK();
}
/**************************************************************************
*	cancelボタン（今はなし）
**************************************************************************/
void CDlgSystem::OnCancel() 
{
//	CDialog::OnCancel();
}
/**************************************************************************
*	ｷｬﾝｾﾙボタン
**************************************************************************/
void CDlgSystem::HlpCancel() 
{
	CDialog::OnCancel();
}
/**************************************************************************
*	OKボタン
**************************************************************************/
void CDlgSystem::HlpOK() 
{
	CDialog::OnOK();
}
/**************************************************************************
*	コントロール廃棄
**************************************************************************/
void CDlgSystem::HlpDeleteCtl()
{
	if(m_pST1 != NULL){	delete m_pST1;	m_pST1=NULL;}
	if(m_pST2 != NULL){	delete m_pST2;	m_pST2=NULL;}
	if(m_pST3 != NULL){	delete m_pST3;	m_pST3=NULL;}
	if(m_pST4 != NULL){	delete m_pST4;	m_pST4=NULL;}
	if(m_pST5 != NULL){	delete m_pST5;	m_pST5=NULL;}
	if(m_pBT1 != NULL){delete m_pBT1;	m_pBT1=NULL;}
	if(m_pBT2 != NULL){delete m_pBT2;	m_pBT2=NULL;}
	if(m_pBT3 != NULL){delete m_pBT3;	m_pBT3=NULL;}
	if(m_pBT4 != NULL){delete m_pBT4;	m_pBT4=NULL;}
	if(m_pCB1 != NULL){delete m_pCB1;	m_pCB1=NULL;}
	if(m_pCB2 != NULL){delete m_pCB2;	m_pCB2=NULL;}
	if(m_pCB3 != NULL){delete m_pCB3;	m_pCB3=NULL;}
	if(m_pCB4 != NULL){delete m_pCB4;	m_pCB4=NULL;}
}
/****************************************************************************
*  m_pBTクリック
*****************************************************************************/
void CDlgSystem::OnBtn1(){PostMessage(WM_EVENT,EV_2,1);}		//ﾎﾞﾀﾝ1通知
/****************************************************************************
*  m_pBTクリック
*****************************************************************************/
void CDlgSystem::OnBtn2(){PostMessage(WM_EVENT,EV_2,2);}		//ﾎﾞﾀﾝ2通知
/****************************************************************************
*  m_pBTクリック
*****************************************************************************/
void CDlgSystem::OnBtn3(){PostMessage(WM_EVENT,EV_2,3);}		//ﾎﾞﾀﾝ3通知
/****************************************************************************
*  m_pBTクリック
*****************************************************************************/
void CDlgSystem::OnBtn4(){PostMessage(WM_EVENT,EV_2,4);}		//ﾎﾞﾀﾝ4通知

/****************************************************************************
*  ｲﾍﾞﾝﾄ通知
*  wParam:ｲﾍﾞﾝﾄ(define.h参照)
*  lParam:いろいろ
*****************************************************************************/
LONG CDlgSystem::OnEvent(UINT wParam, LONG lParam)
{
	CString str;
	switch(wParam){
		case EV_1:						//ｲﾍﾞﾝﾄ1
			TRACE(L"ﾏﾄﾘｸｽ %d 1 [CDlgSystem]",m_nStatus);
			if(m_nStatus == 1){HlpS1E1();break;}
			if(m_nStatus == 2){HlpS2E1();break;}
			if(m_nStatus == 3){HlpS3E1();break;}
			if(m_nStatus == 4){HlpS4E1();break;}
			break;
		case EV_2:						//ｲﾍﾞﾝﾄ2
			TRACE(L"ﾏﾄﾘｸｽ %d 2 [CDlgSystem]",m_nStatus);
			if(m_nStatus == 1){HlpS1E2(int(lParam));break;}
			if(m_nStatus == 2){HlpS2E2(int(lParam));break;}
			if(m_nStatus == 3){HlpS3E2(int(lParam));break;}
			if(m_nStatus == 4){HlpS4E2(int(lParam));break;}
			break;
		default:
			TRACE(L"*** ﾏﾄﾘｸｽ %d [%d]このｲﾍﾞﾝﾄは未定義[CDlgSystem]",m_nStatus,wParam);
			break;
	}

	return 0L;
}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS1E1()
{
	HlpDeleteCtl();		//コントロール廃棄

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select function type.",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,30,150,50), this, 1);

	m_pBT1 = new CButton;
	m_pBT1->Create(L"info GPS", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,70,220,90), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"environment", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,110,220,130), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"exit CNS", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,150,220,170), this, 103);

	m_pBT4 = new CButton;
	m_pBT4->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,190,220,210), this, 104);
	

	CString str;
	if(m_nCountry == COUNTRY_USA)	str.Format(L"Power ICNS %s \nCopyright 2002 evriware Co.,Ltd.",DEF_VERSION);
	else							str.Format(L"Power ICNS %s \nCopyright 2002-2009 \nAdvanced Brain Corporation.",DEF_VERSION);
	m_pST2 = new CStatic;
	m_pST2->Create(str,  SS_LEFT |
					WS_CHILD | WS_VISIBLE
//					, CRect(20,230,220,270), this, 1);
					, CRect(20,210,280,270), this, 1);

}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS1E2(int nBTNo)
{
	if(nBTNo == 1){
		//gps
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 2;
	}	

	if(nBTNo == 2){
		//env
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 3;
	}	


	if(nBTNo == 3){
		//exit
		HlpOK();
	}	

	if(nBTNo == 4){
		//cancel
		HlpCancel();
	}	
}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS2E1()
{
	HlpDeleteCtl();		//コントロール廃棄

	m_pST1 = new CStatic;
	m_pST1->Create(L"EW:",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,30,150,50), this, 1);

	m_pST2 = new CStatic;
	m_pST2->Create(L"NS:",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,70,150,90), this, 1);

	m_pST3 = new CStatic;
	m_pST3->Create(L"status:",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,110,150,130), this, 1);


	m_pST4 = new CStatic;
	m_pST4->Create(L"speed:",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,150,150,170), this, 1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"ok", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,190,220,210), this, 101);
	
	SetTimer(1,1000,NULL);

}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS2E2(int nBTNo)
{
	if(nBTNo == 1){
		//ok
		KillTimer(1);
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 1;
	}	

}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS3E1()
{
	HlpDeleteCtl();		//コントロール廃棄

	m_pST1 = new CStatic;
	m_pST1->Create(L"enviromennt",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,30,150,50), this, 1);





	m_pST2 = new CStatic;
	m_pST2->Create(L"Map matching",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,70,150,100), this, 1);

	m_pCB1 = new CComboBox;
	m_pCB1->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP |WS_VSCROLL |WS_BORDER|CBS_AUTOHSCROLL |CBS_DROPDOWNLIST
					, CRect(160,70,220,130), this, 1);
	m_pCB1->AddString(L"ON");
	m_pCB1->AddString(L"OFF");
	m_pCB1->SetCurSel(m_pzEnv[0]);



	m_pST3 = new CStatic;
	m_pST3->Create(L"Auto scale change",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,110,150,130), this, 1);

	m_pCB2 = new CComboBox;
	m_pCB2->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP |WS_VSCROLL |WS_BORDER|CBS_AUTOHSCROLL |CBS_DROPDOWNLIST
					, CRect(160,110,220,170), this, 1);
	m_pCB2->AddString(L"ON");
	m_pCB2->AddString(L"OFF");
	m_pCB2->SetCurSel(m_pzEnv[1]);



	m_pST4 = new CStatic;
	m_pST4->Create(L"Auto reroute",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,150,150,170), this, 1);


	m_pCB3 = new CComboBox;
	m_pCB3->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP |WS_VSCROLL |WS_BORDER|CBS_AUTOHSCROLL |CBS_DROPDOWNLIST
					, CRect(160,150,220,210), this, 1);
	m_pCB3->AddString(L"ON");
	m_pCB3->AddString(L"OFF");
	m_pCB3->SetCurSel(m_pzEnv[2]);



	m_pST5 = new CStatic;
	m_pST5->Create(L"voice guidance",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,190,150,210), this, 1);

	m_pCB4 = new CComboBox;
	m_pCB4->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP |WS_VSCROLL |WS_BORDER|CBS_AUTOHSCROLL |CBS_DROPDOWNLIST
					, CRect(160,190,220,250), this, 1);
	m_pCB4->AddString(L"ON");
	m_pCB4->AddString(L"OFF");
	m_pCB4->SetCurSel(m_pzEnv[3]);




	m_pBT1 = new CButton;
	m_pBT1->Create(L"ok", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(160,230,220,250), this, 101);

}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS3E2(int nBTNo)
{
	if(nBTNo == 1){
		//ok
		m_pzEnv[0] = m_pCB1->GetCurSel();
		m_pzEnv[1] = m_pCB2->GetCurSel();
		m_pzEnv[2] = m_pCB3->GetCurSel();
		m_pzEnv[3] = m_pCB4->GetCurSel();
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 1;
	}	
}
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS4E1()
{
	
}	
/****************************************************************************
*  ﾏﾄﾘｸｽ関数
*****************************************************************************/
void CDlgSystem::HlpS4E2(int nBTNo)
{

}



/****************************************************************************
*  GPS情報表示
*****************************************************************************/
void CDlgSystem::HlpDispGPSInfo()
{
	CString str;

	double dfEW,dfNS;
	m_pGPS->GetENPoint(&dfEW,&dfNS);
	//EW
	str.Format(L"EW: %3.10lf",dfEW);
	m_pST1->SetWindowText(str);
	//NS
	str.Format(L"NS: %3.10lf",dfNS);
	m_pST2->SetWindowText(str);
	//status
	switch(m_pGPS->GetStatus()){
	case 2:str = L"status: 2D";break;
	case 4:str = L"status: 3D";break;
	default:str = L"status: non";break;
	}
	m_pST3->SetWindowText(str);
	//speed
	str.Format(L"speed: %3dkm/h", m_pGPS->GetSpeed());
	m_pST4->SetWindowText(str);
}

