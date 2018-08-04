// DlgInfo.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgInfo.h"
#include "AutoPC.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CDlgInfo::CDlgInfo()
{
	//{{AFX_DATA_INIT(CDlgInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
/****************************************************************************
*  構築
*****************************************************************************/
BOOL CDlgInfo::Create(CWnd * pWnd,int nIndex/*=0*/)
{
	if(GetSafeHwnd() != NULL)return FALSE;					//作成済み
	m_pWnd	= pWnd;
	m_nIndex = nIndex;
    return CDialog::Create(CDlgInfo::IDD);
}
/***********************************************************************************
*	ﾃﾞｰﾀｴｸｽﾁｪﾝｼﾞ
***********************************************************************************/
void CDlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfo)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}
/***********************************************************************************
*	ﾒｯｾｰｼﾞﾏｯﾌﾟ
***********************************************************************************/
BEGIN_MESSAGE_MAP(CDlgInfo, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//ｲﾍﾞﾝﾄ通知
	//{{AFX_MSG_MAP(CDlgInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	ｷｬﾝｾﾙﾎﾞﾀﾝ
***********************************************************************************/
void CDlgInfo::OnCancel() 
{
	if(m_pWnd != NULL){
		m_pWnd->PostMessage(WM_DLG_CLOSE,m_nIndex,0);
		m_pWnd = NULL;
	}
	
//	CDialog::OnCancel();
}
/***********************************************************************************
*	OKﾎﾞﾀﾝ
***********************************************************************************/
void CDlgInfo::OnOK() 
{
//	CDialog::OnOK();
}
/****************************************************************************
*  ｲﾍﾞﾝﾄ通知
*  wParam:ｲﾍﾞﾝﾄ(define.h参照)
*  lParam:いろいろ
*****************************************************************************/
LONG CDlgInfo::OnEvent(UINT wParam, LONG lParam)
{
	switch(wParam){
		case EV_KEY_DOWN:
			HlpKeyDown(lParam);
			break;
	}

	return 0L;
}
/***********************************************************************************
*	キー入力
***********************************************************************************/
void CDlgInfo::HlpKeyDown(int nCode)
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
			break;
		case 38:				//up
			break;
		case 39:				//right
			break;
		case 40:				//down
			break;
		case 13:				//ENT
			break;
		case 47:				//HELP
			break;
		case 113:				//MENU
			break;
		case 27:				//ESC
			OnCancel();
			break;
	}
}
