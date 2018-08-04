// DlgCircumference.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgCircumference.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/**************************************************************************
*	�R���X�g���N�^
**************************************************************************/
CDlgCircumference::CDlgCircumference(CString strDataPath,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCircumference::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCircumference)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strDataPath	= strDataPath;
	m_pST1			= NULL;
	m_pST2			= NULL;
	m_pED1			= NULL;
	m_pED2			= NULL;
	m_pBT1			= NULL;
	m_pBT2			= NULL;
	m_pBT3			= NULL;
	m_pBT4			= NULL;
	m_pLB1			= NULL;
	m_strED1		= "";
	m_strED2		= "";
	m_nStatus		= 1;

	m_strCircumferenceFile ="";
}
/**************************************************************************
*	�f�X�g���N�^
**************************************************************************/
CDlgCircumference::~CDlgCircumference()
{
	HlpDeleteCtl();		//�R���g���[���p��
}
/**************************************************************************
*	�f�[�^�G�N�X�`�F���W
**************************************************************************/
void CDlgCircumference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCircumference)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
/**************************************************************************
*	���b�Z�[�W�}�b�v
**************************************************************************/
BEGIN_MESSAGE_MAP(CDlgCircumference, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//����Ēʒm
	ON_BN_CLICKED(101,OnBtn1)						//m_pBT1�N���b�N
	ON_BN_CLICKED(102,OnBtn2)						//m_pBT2�N���b�N
	ON_BN_CLICKED(103,OnBtn3)						//m_pBT3�N���b�N
	ON_BN_CLICKED(104,OnBtn4)						//m_pBT4�N���b�N
	//{{AFX_MSG_MAP(CDlgCircumference)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*************************************************************************
*	��������
**************************************************************************/
BOOL CDlgCircumference::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PostMessage(WM_EVENT,EV_1);		//�R���g���[���\�z�v��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/**************************************************************************
*	�L�����Z���{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgCircumference::OnCancel() 
{
//	CDialog::OnCancel();
}
/**************************************************************************
*	OK�{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgCircumference::OnOK() 
{
//	CDialog::OnOK();
}
/**************************************************************************
*	��ݾك{�^��
**************************************************************************/
void CDlgCircumference::HlpCancel() 
{
	CDialog::OnCancel();
}
/**************************************************************************
*	OK�{�^��
**************************************************************************/
void CDlgCircumference::HlpOK() 
{
	m_nRetCode=2;
	CDialog::OnOK();
}
/**************************************************************************
*	�R���g���[���p��
**************************************************************************/
void CDlgCircumference::HlpDeleteCtl()
{
	if(m_pST1 != NULL){	delete m_pST1;	m_pST1=NULL;}
	if(m_pST2 != NULL){	delete m_pST2;	m_pST2=NULL;}
	if(m_pED1 != NULL){	delete m_pED1;	m_pED1=NULL;}
	if(m_pED2 != NULL){	delete m_pED2;	m_pED2=NULL;}
	if(m_pBT1 != NULL){delete m_pBT1;	m_pBT1=NULL;}
	if(m_pBT2 != NULL){delete m_pBT2;	m_pBT2=NULL;}
	if(m_pBT3 != NULL){delete m_pBT3;	m_pBT3=NULL;}
	if(m_pBT4 != NULL){delete m_pBT4;	m_pBT4=NULL;}
	if(m_pLB1 != NULL){delete m_pLB1;	m_pLB1=NULL;}
}
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgCircumference::OnBtn1(){PostMessage(WM_EVENT,EV_2,1);}		//����1�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgCircumference::OnBtn2(){PostMessage(WM_EVENT,EV_2,2);}		//����2�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgCircumference::OnBtn3(){PostMessage(WM_EVENT,EV_2,3);}		//����3�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgCircumference::OnBtn4(){PostMessage(WM_EVENT,EV_2,4);}		//����4�ʒm

/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
*****************************************************************************/
LONG CDlgCircumference::OnEvent(UINT wParam, LONG lParam)
{
	CString str;
	switch(wParam){
		case EV_1:						//�����1
			TRACE(L"��ظ� %d 1 [CDlgCircumference]",m_nStatus);
			if(m_nStatus == 1){HlpS1E1();break;}
			if(m_nStatus == 2){HlpS2E1();break;}
			if(m_nStatus == 3){HlpS3E1();break;}
			break;
		case EV_2:						//�����2
			TRACE(L"��ظ� %d 2 [CDlgCircumference]",m_nStatus);
			if(m_nStatus == 1){HlpS1E2((int)(lParam));break;}
			if(m_nStatus == 2){HlpS2E2((int)(lParam));break;}
			if(m_nStatus == 3){HlpS3E2((int)(lParam));break;}
			break;
		default:
			TRACE(L"*** ��ظ� %d [%d]���̲���Ă͖���`[CDlgCircumference]",m_nStatus,wParam);
			break;
	}

	return 0L;
}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS1E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select function type.",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,30,150,50), this, 1);

	m_pBT1 = new CButton;
	m_pBT1->Create(L"select item and start", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,70,220,90), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"stop", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,110,220,130), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,190,220,210), this, 103);
	

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS1E2(int nBTNo)
{
	if(nBTNo == 1){
		//start
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 2;
	}	

	if(nBTNo == 2){
		m_nRetCode = 1;
		HlpCancel();
		//stop
	}


	if(nBTNo == 3){
		//cancel
		m_nRetCode = 0;
		HlpCancel();
	}	
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS2E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select group1",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	
	m_pLB1 = new CListBox;
	m_pLB1->Create(
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER | WS_VSCROLL 
					, CRect(10,40,230,210), this, 1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,70,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"next", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);

	m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,FILE_CATEGORY_G1,1);	//�J�e�S���t�@�C�� ���eLB�\��
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS2E2(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 1;

	}
	if(nBTNo == 2){	//next
		//���J�e�S���t�@�C�����l��
		m_strNextFile = m_CategoryLB.GetCategoryNextFile(m_strDataPath,m_pLB1,FILE_CATEGORY_G1);
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 3;
	}

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS3E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select group2",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	
	m_pLB1 = new CListBox;
	m_pLB1->Create(
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER | WS_VSCROLL 
					, CRect(10,40,230,210), this, 1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,70,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"start", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);

	m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,m_strNextFile,1);	//�J�e�S���t�@�C�� ���eLB�\��
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgCircumference::HlpS3E2(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 2;

	}
	if(nBTNo == 2){	//start
		//���J�e�S���t�@�C�����l��
		m_strCircumferenceFile = m_strNextFile.Left(2) +  
			m_CategoryLB.GetCategoryNextFile(m_strDataPath,m_pLB1,m_strNextFile);
		HlpOK();
	}
}

/****************************************************************************
*  ���ӌ���ITEM�����l��
*****************************************************************************/
int CDlgCircumference::GetCircumferenceItemCntMax()
{
	int nCntMax = m_CategoryLB.GetCircumferenceItemCntMax(m_strDataPath,m_strCircumferenceFile);
	return nCntMax;


//	CFile file;
//	if(file.Open(m_strDataPath + FILE_CATEGORY_FOLDER + L"\\02\\" + m_strCircumferenceFile, CFile::modeRead) == FALSE)return 0;
//	int nCntMax = file.GetLength()/m_CategoryLB.GetStructCategoryFileSize();
//	file.Close();
//	return nCntMax;
}
/****************************************************************************
*  ���ӌ���ITEM�S�Ă̈ܓx�o�x�Ɩ��̂��o�b�t�@�Ɋi�[
*	�ܓx�o�x��EW,NS,EW,NS....�̏��Ŋi�[����
*****************************************************************************/
void CDlgCircumference::SetCircumferenceItem(int *npBuf,CString *strpName)
{
	m_CategoryLB.SetCircumferenceItem(npBuf,strpName,m_strDataPath , m_strCircumferenceFile);



}


