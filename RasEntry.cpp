// RasEntry.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "RasEntry.h"
#include <ras.h>
#include <raserror.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/***********************************************************************************
*	�ݽ�׸�
***********************************************************************************/
CRasEntry::CRasEntry()
{
	//{{AFX_DATA_INIT(CRasEntry)
	//}}AFX_DATA_INIT
}
/***********************************************************************************
*	�޽�׸�
***********************************************************************************/
CRasEntry::~CRasEntry()
{
}
/****************************************************************************
*  �\�z
*****************************************************************************/
BOOL CRasEntry::Create(CWnd * pWnd,CString *pstrEntryName,int nIndex/*=0*/)
{
	if(GetSafeHwnd() != NULL)return FALSE;					//�쐬�ς�
	m_pWnd	= pWnd;
	m_nIndex = nIndex;
	m_pstrEntryName = pstrEntryName;

    return CDialog::Create(CRasEntry::IDD);
}

/***********************************************************************************
*	�f�[�^�G�N�X�`�F���W
***********************************************************************************/
void CRasEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRasEntry)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}
/***********************************************************************************
*	ү����ϯ��
***********************************************************************************/
BEGIN_MESSAGE_MAP(CRasEntry, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//����Ēʒm
	//{{AFX_MSG_MAP(CRasEntry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	��������
***********************************************************************************/
BOOL CRasEntry::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_nPos=0;
	if(HlpGetEntry() == 0){
		m_List1.SetCurSel(m_nPos);
	}

//	m_List1.AddString(L"1");
//	m_List1.AddString(L"2");
//	m_List1.AddString(L"3");
//	m_nPosMax=3;

	
//	m_List1.SetCurSel(m_nPos);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/***********************************************************************************
*	OK����
***********************************************************************************/
void CRasEntry::OnOK() 
{
	if(m_pWnd != NULL){
		m_pWnd->PostMessage(WM_DLG_CLOSE,m_nIndex,0);
		m_pWnd = NULL;
	}


//	CDialog::OnOK();
}
/***********************************************************************************
*	Cancel����
***********************************************************************************/
void CRasEntry::OnCancel() 
{
	OnOK();	
//	CDialog::OnCancel();
}
/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
*****************************************************************************/
LONG CRasEntry::OnEvent(UINT wParam, LONG lParam)
{
	switch(wParam){
		case EV_KEY_DOWN:
			HlpKeyDown(lParam);
			break;
		case EV_INIT:					//��������
			break;
//		case EV_SOC_RECEIVE_NOTIF:			//��M�ʒm(�ݒ芮���ʒm)
//			m_pWnd->PostMessage(WM_EVENT,EV_WAIT_DISABLE,0);
//			m_stG1.SetWindowText(m_strG1[m_nG1Cnt]);
//			HlpSetList();				//���X�g�{�b�N�X�\��
//			HlpDisCntG1();
//			break;
//		case ULP_NO_RECEIVE:
//			OnOK();
//			break;
	}

	return 0L;
}
/***********************************************************************************
*	���X�g�{�b�N�X�\��
***********************************************************************************/
/*void CRasEntry::HlpSetList()
{
	int i;

	m_List1.ResetContent();		//all clr
	if(m_bListG1 == TRUE){
		for(i=0;i<m_nG1CntMax;i++){
			m_List1.AddString(m_strG1[i]);
		}
	}
	else{
		for(i=0;i<m_nG2CntMax;i++){
			m_List1.AddString(m_strG2[i]);
		}
	}
}
*/
/***********************************************************************************
*	�L�[����
***********************************************************************************/
void CRasEntry::HlpKeyDown(int nCode)
{
	CString str;

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
			if(m_nPos <= 0)break;
			m_nPos--;
			m_List1.SetCurSel(m_nPos);
			break;
		case 39:				//right
			break;
		case 40:				//down
			if(m_nPos >= m_nPosMax-1)break;
			m_nPos++;
			m_List1.SetCurSel(m_nPos);
			break;
		case 13:				//ENT
			if(m_nPosMax > 0){
				m_List1.GetText(m_nPos,str);
				*m_pstrEntryName = str;
				m_pWnd->PostMessage(WM_EVENT,EV_RAS,0);	//Connect
			}
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
*	RAS�G���g�����o
***********************************************************************************/
int CRasEntry::HlpGetEntry()
{
	RASENTRYNAME renDmy,*pRen;
	DWORD dw,dwSize,dwEntries,dwResult;

	dwSize=sizeof(RASENTRYNAME);
	renDmy.dwSize=sizeof(RASENTRYNAME);
	dwResult=::RasEnumEntries(NULL,NULL,&renDmy,&dwSize,&dwEntries);

	if(!dwEntries)
	{
		TRACE(L"No entry.\n");
		return -1;
	}

	if(dwResult && dwResult!=ERROR_BUFFER_TOO_SMALL)
	{
		TRACE(L"GetEntry()err-2\n");
		return -2;
	}

	pRen=new RASENTRYNAME[dwEntries];
	pRen[0].dwSize=sizeof(RASENTRYNAME);
	dwResult=::RasEnumEntries(NULL,NULL,pRen,&dwSize,&dwEntries);
	
	if(dwResult)
	{
		delete [] pRen;
		TRACE(L"GetEntry()err-3\n");
		return -3;
	}

	m_nPosMax=0;
	CString str;
	for(dw=0;dw<dwEntries;dw++){				//�G���g���ꗗ�\��
		str.Format(L"%s",pRen[dw].szEntryName);
		m_List1.AddString(str);
		m_nPosMax++;
//		HlpTRACE(str);
	}

	delete [] pRen;

	return 0;
}



