// SearchID.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "SearchID.h"
#include "Tool.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CSearchID::CSearchID(struct_SearchID *pStructSearchID)
{
	m_pStructSearchID = pStructSearchID;
	//{{AFX_DATA_INIT(CSearchID)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Brush.CreateSolidBrush(RGB(255,0,0));
}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CSearchID::~CSearchID()
{
}
/****************************************************************************
*  構築
*****************************************************************************/
BOOL CSearchID::Create(CWnd * pWnd,int nIndex/*=0*/)
{
	if(GetSafeHwnd() != NULL)return FALSE;					//作成済み
	m_pWnd		= pWnd;
	m_nIndex	= nIndex;
	m_nPos		= 0;

    return CDialog::Create(CSearchID::IDD);
}
/***********************************************************************************
*	データエクスチェンジ
***********************************************************************************/
void CSearchID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchID)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
/***********************************************************************************
*	ﾒｯｾｰｼﾞﾏｯﾌﾟ
***********************************************************************************/
BEGIN_MESSAGE_MAP(CSearchID, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//ｲﾍﾞﾝﾄ通知
	//{{AFX_MSG_MAP(CSearchID)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/****************************************************************************
*  ｲﾍﾞﾝﾄ通知
*  wParam:ｲﾍﾞﾝﾄ(define.h参照)
*  lParam:いろいろ
*****************************************************************************/
LONG CSearchID::OnEvent(UINT wParam, LONG lParam)
{
	switch(wParam){
//		case EV_INIT:					//初期処理
//			break;
		case EV_KEY_DOWN:
			HlpKeyDown(lParam);
			break;
//		case EV_RECEIVE_NOTIFI:			//受信通知(設定完了通知)
//			m_stG2.SetWindowText(m_strG2[m_nG2Cnt]);
//			HlpDisCntG2();
//			break;			
	}

	return 0L;
}
/***********************************************************************************
*	初期処理
***********************************************************************************/
BOOL CSearchID::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/***********************************************************************************
*	コントロール背景色変更
***********************************************************************************/
HBRUSH CSearchID::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

//	if(nCtlColor == CTLCOLOR_BTN){

	CWnd *pWndBtn;
	switch(m_nPos){
		case  0:pWndBtn = GetDlgItem(IDC_BTN_1);break;
		case  1:pWndBtn = GetDlgItem(IDC_BTN_2);break;
		case  2:pWndBtn = GetDlgItem(IDC_BTN_3);break;
		case  3:pWndBtn = GetDlgItem(IDC_BTN_4);break;
		case  4:pWndBtn = GetDlgItem(IDC_BTN_5);break;
		case  5:pWndBtn = GetDlgItem(IDC_BTN_6);break;
		case  6:pWndBtn = GetDlgItem(IDC_BTN_7);break;
		case  7:pWndBtn = GetDlgItem(IDC_BTN_8);break;
		case  8:pWndBtn = GetDlgItem(IDC_BTN_9);break;
		case  9:pWndBtn = GetDlgItem(IDC_BTN_0);break;
		case 10:pWndBtn = GetDlgItem(IDC_BTN_DEL);break;
		case 11:pWndBtn = GetDlgItem(IDC_BTN_OK);break;
		default:return hbr;
	}
	if(*pWndBtn == *pWnd)return m_Brush;
	
	return hbr;
	
}


/***********************************************************************************
*	Cancelﾎﾞﾀﾝ
***********************************************************************************/
void CSearchID::OnCancel() 
{
	OnOK();	
//	CDialog::OnCancel();
}
/***********************************************************************************
*	OKﾎﾞﾀﾝ
***********************************************************************************/
void CSearchID::OnOK() 
{
	if(m_pWnd != NULL){
		m_pWnd->PostMessage(WM_DLG_CLOSE,m_nIndex,0);
		m_pWnd = NULL;
	}
//	CDialog::OnOK();
}
/***********************************************************************************
*	キー入力
***********************************************************************************/
void CSearchID::HlpKeyDown(int nCode)
{
	switch(nCode){
		case 119:				//F1
			break;
		case 120:				//F2
			break;
		case 121:				//F3
			break;
		case 122:				//F4
			break;
		case 123:				//F5
			break;
		case 124:				//F6
			break;
		case 37:				//left
			if(m_nPos <=0)break;
			HlpRedrawWindow(m_nPos);
			m_nPos--;
			HlpRedrawWindow(m_nPos);
			break;
		case 38:				//up
			break;
		case 39:				//right
			if(m_nPos >=11)break;
			HlpRedrawWindow(m_nPos);
			m_nPos++;
			HlpRedrawWindow(m_nPos);
			break;
		case 40:				//down
			break;
		case 13:				//ENT
			HlpEnter();
			break;
		case 47:				//HELP
			break;
		case 113:				//MENU
			break;
		case 27:				//ESC
			OnOK();
			break;
	}
}




/***********************************************************************************
*	ボタン再描画
***********************************************************************************/
void CSearchID::HlpRedrawWindow(int nPos)
{
	switch(m_nPos){
		case  0:GetDlgItem(IDC_BTN_1)->RedrawWindow();;break;
		case  1:GetDlgItem(IDC_BTN_2)->RedrawWindow();;break;
		case  2:GetDlgItem(IDC_BTN_3)->RedrawWindow();;break;
		case  3:GetDlgItem(IDC_BTN_4)->RedrawWindow();;break;
		case  4:GetDlgItem(IDC_BTN_5)->RedrawWindow();;break;
		case  5:GetDlgItem(IDC_BTN_6)->RedrawWindow();;break;
		case  6:GetDlgItem(IDC_BTN_7)->RedrawWindow();;break;
		case  7:GetDlgItem(IDC_BTN_8)->RedrawWindow();;break;
		case  8:GetDlgItem(IDC_BTN_9)->RedrawWindow();;break;
		case  9:GetDlgItem(IDC_BTN_0)->RedrawWindow();;break;
		case 10:GetDlgItem(IDC_BTN_DEL)->RedrawWindow();;break;
		case 11:GetDlgItem(IDC_BTN_OK)->RedrawWindow();;break;
	}
}
/***********************************************************************************
*	ENT入力
***********************************************************************************/
void CSearchID::HlpEnter(void)
{
	CString str;
	GetDlgItem(IDC_ED_ID)->GetWindowText(str);
	int nLen = str.GetLength();

	if(m_nPos < 10 && nLen >= 10)return;	//最大１０byte

	switch(m_nPos){
		case  0:str += L"1";break;
		case  1:str += L"2";break;
		case  2:str += L"3";break;
		case  3:str += L"4";break;
		case  4:str += L"5";break;
		case  5:str += L"6";break;
		case  6:str += L"7";break;
		case  7:str += L"8";break;
		case  8:str += L"9";break;
		case  9:str += L"0";break;
		case 10:
			if(nLen <= 0)return;
			str = str.Left(nLen-1);
			break;
		case 11:
			if(nLen < 1)return;
			HlpGetData();
			m_pWnd->PostMessage(WM_EVENT,EV_SOC_CONNECT,SOC_REQ_SEARCH_ID);
			OnOK();
			return;
		default:return;
	}

	GetDlgItem(IDC_ED_ID)->SetWindowText(str);
	

}

/***********************************************************************************
*	データ獲得
***********************************************************************************/
void CSearchID::HlpGetData(void)
{
	CTool tool;

	m_pStructSearchID->cType	= SEARCH_ID_TYPE_GET;		//1:set 2:get 3:rspOK 4:rspNG
	CString str;
	GetDlgItem(IDC_ED_ID)->GetWindowText(str);	//ID
	strcpy((char*)m_pStructSearchID->cID,tool.CStringToChar(str));
	m_pStructSearchID->dwEW = 0;				//don't care
	m_pStructSearchID->dwNS = 0;				//don't care


	//----------test用---------------
//	m_pStructSearchID->dwEW =	 (DWORD)(DEFAULT_START_EW * DEF_CONVERT);
//	m_pStructSearchID->dwNS =	 (DWORD)(DEFAULT_START_NS * DEF_CONVERT);
//	m_pStructSearchID->dwEW =	 (DWORD)(126.81683 * DEF_CONVERT);
//	m_pStructSearchID->dwNS =	 (DWORD)(37.58411 * DEF_CONVERT);


}

