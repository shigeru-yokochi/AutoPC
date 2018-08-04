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
*	�ݽ�׸�
***********************************************************************************/
CDlgInfo::CDlgInfo()
{
	//{{AFX_DATA_INIT(CDlgInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
/****************************************************************************
*  �\�z
*****************************************************************************/
BOOL CDlgInfo::Create(CWnd * pWnd,int nIndex/*=0*/)
{
	if(GetSafeHwnd() != NULL)return FALSE;					//�쐬�ς�
	m_pWnd	= pWnd;
	m_nIndex = nIndex;
    return CDialog::Create(CDlgInfo::IDD);
}
/***********************************************************************************
*	�ް������ݼ�
***********************************************************************************/
void CDlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInfo)
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}
/***********************************************************************************
*	ү����ϯ��
***********************************************************************************/
BEGIN_MESSAGE_MAP(CDlgInfo, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//����Ēʒm
	//{{AFX_MSG_MAP(CDlgInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	��ݾ�����
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
*	OK����
***********************************************************************************/
void CDlgInfo::OnOK() 
{
//	CDialog::OnOK();
}
/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
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
*	�L�[����
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
