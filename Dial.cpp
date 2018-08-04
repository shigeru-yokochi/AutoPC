// Dial.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "Dial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CDial::CDial()
{
	m_Brush.CreateSolidBrush(RGB(255,0,0));

	//{{AFX_DATA_INIT(CDial)
	m_strID = _T("");
	m_strDial = _T("");
	//}}AFX_DATA_INIT
}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CDial::~CDial()
{
}
/****************************************************************************
*  構築
*****************************************************************************/
BOOL CDial::Create(CWnd * pWnd,CString *strpID,CString *strpDial,int nIndex/*=0*/)
{
	if(GetSafeHwnd() != NULL)return FALSE;					//作成済み
	m_pWnd		= pWnd;
	m_nIndex	= nIndex;
	m_nPos		= 0;
	m_strpID	= strpID;
	m_strpDial	= strpDial;

	m_strID		= *m_strpID;
	m_strDial	= *m_strpDial;


    return CDialog::Create(CDial::IDD);
}
/***********************************************************************************
*	データエクスチェンジ
***********************************************************************************/
void CDial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDial)
	DDX_Text(pDX, IDC_ST_ID, m_strID);
	DDX_Text(pDX, IDC_ST_DIAL, m_strDial);
	//}}AFX_DATA_MAP
}
/***********************************************************************************
*	ﾒｯｾｰｼﾞﾏｯﾌﾟ
***********************************************************************************/
BEGIN_MESSAGE_MAP(CDial, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//ｲﾍﾞﾝﾄ通知
	//{{AFX_MSG_MAP(CDial)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	タイムアウト
***********************************************************************************/
void CDial::OnTimer(UINT nIDEvent) 
{
	m_strID.TrimRight();
	m_strID += " ";

	m_strDial.TrimRight();
	m_strDial += " ";

	CDialog::OnTimer(nIDEvent);
}
/****************************************************************************
*  初期処理
*****************************************************************************/
BOOL CDial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strID		= *m_strpID;
	m_strDial   = *m_strpDial;
	m_strID += " ";
	m_strDial += " ";



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/****************************************************************************
*  ｲﾍﾞﾝﾄ通知
*  wParam:ｲﾍﾞﾝﾄ(define.h参照)
*  lParam:いろいろ
*****************************************************************************/
LONG CDial::OnEvent(UINT wParam, LONG lParam)
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
*	コントロール背景色変更
***********************************************************************************/
HBRUSH CDial::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	CWnd *pWndBtn;
	switch(m_nPos){
		case  0:pWndBtn = GetDlgItem(IDC_BTN_ID);break;
		case  1:pWndBtn = GetDlgItem(IDC_BTN_DIAL);break;
		case  2:pWndBtn = GetDlgItem(IDC_BTN_SAVE);break;
		default:return hbr;
	}
	if(*pWndBtn == *pWnd)return m_Brush;

	return hbr;
}

/***********************************************************************************
*	Cancelﾎﾞﾀﾝ
***********************************************************************************/
void CDial::OnCancel() 
{
	OnOK();	
//	CDialog::OnCancel();
}
/***********************************************************************************
*	OKﾎﾞﾀﾝ
***********************************************************************************/
void CDial::OnOK() 
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
void CDial::HlpKeyDown(int nCode)
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
			if(m_nPos == 0){
				if(m_strID.GetLength() > 9)break;
				HlpDown(&m_strID);
			}
			if(m_nPos == 1){
				if(m_strDial.GetLength() > 20)break;
				HlpDown(&m_strDial);
			}
			break;
		case 38:				//up
			if(m_nPos <=0)break;
			HlpRedrawWindow(m_nPos);
			m_nPos--;
			HlpRedrawWindow(m_nPos);
			break;
		case 39:				//right
			if(m_nPos == 0){
				if(m_strDial.GetLength() > 20)break;
				if(m_strID.GetLength() > 9)break;
				HlpUp(&m_strID);
			}
			if(m_nPos == 1){
				HlpUp(&m_strDial);
			}
			break;
		case 40:				//down
			if(m_nPos >=2)break;
			HlpRedrawWindow(m_nPos);
			m_nPos++;
			HlpRedrawWindow(m_nPos);
			break;
		case 13:				//ENT
			if(HlpEnter() == FALSE)break;
			m_strID.TrimRight();
			m_strDial.TrimRight();
			*m_strpID	= m_strID;
			*m_strpDial = m_strDial;
			OnOK();
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
void CDial::HlpRedrawWindow(int nPos)
{
	switch(m_nPos){
		case  0:GetDlgItem(IDC_BTN_ID)->RedrawWindow();break;
		case  1:GetDlgItem(IDC_BTN_DIAL)->RedrawWindow();break;
		case  2:GetDlgItem(IDC_BTN_SAVE)->RedrawWindow();break;
	}
}
/***********************************************************************************
*	ENT入力
***********************************************************************************/
BOOL CDial::HlpEnter()
{
	switch(m_nPos){
		case  0:
			KillTimer(TO_NENT_CHAR);		//clr
			m_strID = "";
			UpdateData(FALSE);
			return FALSE;
		case  1:
			KillTimer(TO_NENT_CHAR);		//clr
			m_strDial = "";
			UpdateData(FALSE);
			return FALSE;
		case  2:
//			m_pWnd->PostMessage(WM_EVENT,EV_ROUTE);	//クリア
			break;
	}
	return TRUE;

}
/***********************************************************************************
*	UP
***********************************************************************************/
void CDial::HlpUp(CString *strp) 
{
	KillTimer(TO_NENT_CHAR);

	int nLen = strp->GetLength();

	if(nLen < 1){
//		m_strID = "A";
		*strp = "0";
	}
	else{
		TCHAR c = strp->GetAt(nLen-1);
		c = HlpGetNextChar(c);
		strp->SetAt(nLen-1,c); 
	}


//	SetDlgItemText(IDC_ST_ID,m_strID);
	UpdateData(FALSE);
	SetTimer(TO_NENT_CHAR,TO_VAL_NENT_CHAR,NULL);

}
/***********************************************************************************
*	DOWN
***********************************************************************************/
void CDial::HlpDown(CString *strp) 
{
	KillTimer(TO_NENT_CHAR);

	int nLen = strp->GetLength();
	if(nLen < 1){
//		m_strID = "Z";
		*strp = "9";
	}
	else{
		TCHAR c = strp->GetAt(nLen-1);
		c = HlpGetNextChar(c,FALSE);
		strp->SetAt(nLen-1,c); 
	}

//	SetDlgItemText(IDC_ST_ID,m_strID);
	UpdateData(FALSE);
	SetTimer(TO_NENT_CHAR,TO_VAL_NENT_CHAR,NULL);
}

/***********************************************************************************
*	
***********************************************************************************/
TCHAR CDial::HlpGetNextChar(TCHAR c,BOOL bInc/*=TRUE*/)
{
	if(bInc == TRUE){
//		if(c == 'Z' || c == ' ')return 'A';
		if(c == '9' || c == ' ')return '0';
		c++;
	}
	else{
//		if(c == 'A' || c == ' ')return 'Z';
		if(c == '0' || c == ' ')return '9';
		c--;
	}
	return c;
}

