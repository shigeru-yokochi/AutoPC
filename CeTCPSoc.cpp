// CeTCPSoc.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "CeTCPSoc.h"

#include "Define.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*************************************************************************************************
*	�ݽ�׸�
**************************************************************************************************/
CCeTCPSoc::CCeTCPSoc(CWnd * pWnd,int nIndex/*=0*/)
{
	m_pWnd			= pWnd;
	m_nIndex		= nIndex;
}
/*************************************************************************************************
*	�޽�׸�
**************************************************************************************************/
CCeTCPSoc::~CCeTCPSoc()
{
}
/*************************************************************************************************
*	ү����ϯ��
**************************************************************************************************/
#if 0
BEGIN_MESSAGE_MAP(CCeTCPSoc, CCeSocket)
	//{{AFX_MSG_MAP(CCeTCPSoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0
/*************************************************************************************************
*	��M�ʒm
**************************************************************************************************/
void CCeTCPSoc::OnReceive(int nErrorCode) 
{
	TRACE(L"CCeTCPSoc::OnReceive()\n");
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF,m_nIndex);
	
	CCeSocket::OnReceive(nErrorCode);
}

