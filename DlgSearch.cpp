// DlgSearch.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgSearch.h"
#include "NameBody.h"
#include "InfoData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************************************************
*	�R���X�g���N�^
**************************************************************************/
CDlgSearch::CDlgSearch(CString strDataPath,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_strDataPath	= strDataPath;
	m_pST1			= NULL;
	m_pST2			= NULL;
	m_pED1			= NULL;
	m_pBT1			= NULL;
	m_pBT2			= NULL;
	m_pBT3			= NULL;
	m_pBT4			= NULL;
	m_pLB1			= NULL;
	m_strED1		= "";
	m_nStatus		= 0;
	m_nEW			= 0;
	m_nNS			= 0;

}
/**************************************************************************
*	�f�X�g���N�^
**************************************************************************/
CDlgSearch::~CDlgSearch()
{
	HlpDeleteCtl();		//�R���g���[���p��
}
/**************************************************************************
*	�f�[�^�G�N�X�`�F���W
**************************************************************************/
void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
/**************************************************************************
*	���b�Z�[�W�}�b�v
**************************************************************************/
BEGIN_MESSAGE_MAP(CDlgSearch, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//����Ēʒm
	ON_BN_CLICKED(101,OnBtn1)						//m_pBT1�N���b�N
	ON_BN_CLICKED(102,OnBtn2)						//m_pBT2�N���b�N
	ON_BN_CLICKED(103,OnBtn3)						//m_pBT3�N���b�N
	ON_BN_CLICKED(104,OnBtn4)						//m_pBT4�N���b�N
	//{{AFX_MSG_MAP(CDlgSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*************************************************************************
*	��������
**************************************************************************/
BOOL CDlgSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PostMessage(WM_EVENT,EV_1);		//�R���g���[���\�z�v��


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/**************************************************************************
*	OK�{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgSearch::OnOK() 
{
//	CDialog::OnOK();
}
/**************************************************************************
*	�L�����Z���{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgSearch::OnCancel() 
{
//	CDialog::OnCancel();
}
/**************************************************************************
*	��ݾك{�^��
**************************************************************************/
void CDlgSearch::HlpCancel() 
{
	CDialog::OnCancel();
}
/**************************************************************************
*	OK�{�^��
**************************************************************************/
void CDlgSearch::HlpOK() 
{
	CDialog::OnOK();
}

/**************************************************************************
*	�R���g���[���p��
**************************************************************************/
void CDlgSearch::HlpDeleteCtl()
{
	if(m_pST1 != NULL){	delete m_pST1;	m_pST1=NULL;}
	if(m_pST2 != NULL){	delete m_pST2;	m_pST2=NULL;}
	if(m_pED1 != NULL){	delete m_pED1;	m_pED1=NULL;}
	if(m_pBT1 != NULL){delete m_pBT1;	m_pBT1=NULL;}
	if(m_pBT2 != NULL){delete m_pBT2;	m_pBT2=NULL;}
	if(m_pBT3 != NULL){delete m_pBT3;	m_pBT3=NULL;}
	if(m_pBT4 != NULL){delete m_pBT4;	m_pBT4=NULL;}
	if(m_pLB1 != NULL){delete m_pLB1;	m_pLB1=NULL;}
}
/**************************************************************************
*	�I������
**************************************************************************/
void CDlgSearch::GetEWNS(int *npEW,int *npNS)
{
	*npEW = m_nEW;
	*npNS  = m_nNS;
}
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgSearch::OnBtn1(){PostMessage(WM_EVENT,EV_3,1);}		//����1�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgSearch::OnBtn2(){PostMessage(WM_EVENT,EV_3,2);}		//����2�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgSearch::OnBtn3(){PostMessage(WM_EVENT,EV_3,3);}		//����3�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgSearch::OnBtn4(){PostMessage(WM_EVENT,EV_3,4);}		//����4�ʒm
/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
*****************************************************************************/
LONG CDlgSearch::OnEvent(UINT wParam, LONG lParam)
{
	CString str;
	switch(wParam){
		case EV_1:						//�����1
			TRACE(L"��ظ� %d 1 [CDlgSearch]",m_nStatus);
			if(m_nStatus == 0){HlpS0E1();break;}
			if(m_nStatus == 1){HlpS1E1();break;}
			if(m_nStatus == 2){HlpS2E1();break;}
			if(m_nStatus == 3){HlpS3E1();break;}
			if(m_nStatus == 4){HlpS4E1();break;}
			if(m_nStatus == 5){HlpS5E1();break;}
			if(m_nStatus == 6){HlpS6E1();break;}
			if(m_nStatus == 7){HlpS7E1(int(lParam));break;}
			break;
		case EV_2:						//�����2
			TRACE(L"��ظ� %d 2 [CDlgSearch]",m_nStatus);
			if(m_nStatus == 0){HlpS0E2();break;}
			if(m_nStatus == 1){HlpS1E2();break;}
			if(m_nStatus == 2){HlpS2E2();break;}
			if(m_nStatus == 3){HlpS3E2();break;}
			if(m_nStatus == 4){HlpS4E2();break;}
			if(m_nStatus == 5){HlpS5E2();break;}
			if(m_nStatus == 6){HlpS6E2();break;}
			if(m_nStatus == 7){HlpS7E2();break;}
			break;
		case EV_3:						//�����3
			TRACE(L"��ظ� %d 3 [CDlgSearch]",m_nStatus);
			if(m_nStatus == 0){HlpS0E3(int(lParam));break;}
			if(m_nStatus == 1){HlpS1E3(int(lParam));break;}
			if(m_nStatus == 2){HlpS2E3(int(lParam));break;}
			if(m_nStatus == 3){HlpS3E3(int(lParam));break;}
			if(m_nStatus == 4){HlpS4E3(int(lParam));break;}
			if(m_nStatus == 5){HlpS5E3(int(lParam));break;}
			if(m_nStatus == 6){HlpS6E3(int(lParam));break;}
			if(m_nStatus == 7){HlpS7E3(int(lParam));break;}
			break;
		case EV_4:						//�����4
			TRACE(L"��ظ� %d 4 [CDlgSearch]",m_nStatus);
			if(m_nStatus == 0){HlpS0E4();break;}
			if(m_nStatus == 1){HlpS1E4();break;}
			if(m_nStatus == 2){HlpS2E4();break;}
			if(m_nStatus == 3){HlpS3E4();break;}
			if(m_nStatus == 4){HlpS4E4();break;}
			if(m_nStatus == 5){HlpS5E4();break;}
			if(m_nStatus == 6){HlpS6E4();break;}
			if(m_nStatus == 7){HlpS7E4();break;}
			break;

		default:
			TRACE(L"*** ��ظ� %d [%d]���̲���Ă͖���`[CDlgSearch]",m_nStatus,wParam);
			break;
	}

	return 0L;
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS0E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select search type.",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,10,150,30), this, 1);

	m_pBT1 = new CButton;
	m_pBT1->Create(L"name", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,70,220,90), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"address", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,110,220,130), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"category", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,150,220,170), this, 103);

	m_pBT4 = new CButton;
	m_pBT4->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,190,220,210), this, 104);

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS0E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS0E3(int nBTNo)
{
	if(nBTNo == 1){		//name
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 1;
	}	


	if(nBTNo == 2){		//address
		PostMessage(WM_EVENT,EV_1);
		m_nType = TYPE_ADDRESS;
		m_nStatus		= 3;
	}	

	if(nBTNo == 3){		//category
		PostMessage(WM_EVENT,EV_1);
		m_nType = TYPE_CATEGORY;
		m_nStatus		= 3;
	}	


	if(nBTNo == 4){
		HlpCancel();
	}	


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS0E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS1E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Input search name.",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,10,150,30), this, 1);

	m_pED1 = new CEdit;
//	m_pED1->Create(ES_WANTRETURN |ES_UPPERCASE |
	m_pED1->Create(ES_WANTRETURN |
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(20,40,220,60), this, 1);
	m_pED1->SetWindowText(m_strED1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,70,110,90), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"search", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(130,70,220,90), this, 102);

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS1E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS1E3(int nBTNo)
{
	if(nBTNo == 1){
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 0;
	}

	if(nBTNo == 2){
		m_pED1->GetWindowText(m_strED1);
		if(m_strED1 == "")return;

		TRACE(m_strED1);
		HlpDeleteCtl();				//�R���g���[���p��
		PostMessage(WM_EVENT,EV_1);	//�R���g���[���\�z�v��
		m_nStatus		= 6;
	}
}	
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS1E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS2E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select group4",  SS_LEFT |
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
	m_pBT2->Create(L"info", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"map", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,220,230,240), this, 103);


	m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,m_strGroupFile[3],2,&m_nGetInfoCode[0]);	//�J�e�S���t�@�C�� ���eLB�\��


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS2E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS2E3(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 5;
	}

	if(nBTNo == 2){
		//info
		if(m_CategoryLB.GetEWNS(m_strDataPath,m_pLB1,m_strGroupFile[3],&m_nEW,&m_nNS) == FALSE)return;		//���ݑI�����Ă���A�C�e���̈ܓx�o�x���l��
		PostMessage(WM_EVENT,EV_1,m_pLB1->GetCurSel());
		m_nSaveStatus   = 2;
		m_nStatus		= 7;
	}		

	if(nBTNo == 3){
		//map
		if(m_CategoryLB.GetEWNS(m_strDataPath,m_pLB1,m_strGroupFile[3],&m_nEW,&m_nNS) == FALSE)return;		//���ݑI�����Ă���A�C�e���̈ܓx�o�x���l��
		HlpOK();
	}		

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS2E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS3E1()
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

	if(m_nType == TYPE_ADDRESS)	HlpDispAdrData(FILE_ADR_FILE_TOP);			//�Z�������t�@�C�� ���eLB�\��
	else						m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,FILE_CATEGORY_AREA,0);	//�J�e�S���t�@�C�� ���eLB�\��
	
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS3E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS3E3(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 0;
	}

	if(nBTNo == 2){
		//next
		int nPos = m_pLB1->GetCurSel();
		if(nPos < 0)return;
		CString str;
		m_pLB1->GetText(nPos,str);
		if(m_nType == TYPE_ADDRESS){
			m_strGroupFile[1] = str.Left(6);		//�擪�U�o�C�g���t�@�C�����ɂ���
			m_strGroupFile[1] += L".dat";
		}
		else{
			//�I�������J�e�S���n��R�[�h�l��
			m_strCategoryAreaCode = m_CategoryLB.GetCategorySelectAreaCode(m_strDataPath,m_pLB1,FILE_CATEGORY_AREA);
			m_strGroupFile[1] = FILE_CATEGORY_G1;	//�啪�ވꗗ
		}

		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 4;
	}

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS3E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS4E1()
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
	m_pBT2->Create(L"next", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);


	if(m_nType == TYPE_ADDRESS)	HlpDispAdrData(m_strGroupFile[1]);			//�Z�������t�@�C�� ���eLB�\��
	else						m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,m_strGroupFile[1],1);	//�J�e�S���t�@�C�� ���eLB�\��

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS4E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS4E3(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 3;
	}

	if(nBTNo == 2){
		//next
		int nPos = m_pLB1->GetCurSel();
		if(nPos < 0)return;

		if(m_nType == TYPE_ADDRESS){
			int nLen = m_strGroupFile[1].GetLength();
			CString str = m_strGroupFile[1].Left(nLen -3);	//xxxx.dat��dat������
			m_strGroupFile[2] = str;
			m_pLB1->GetText(nPos,str);
			m_strGroupFile[2] += str.Left(10);		//�擪10�o�C�g���t�@�C�����ɂ���
			m_strGroupFile[2] += L".dat";
		}
		else{
			//���J�e�S���t�@�C�����l��
			m_strGroupFile[2] = m_CategoryLB.GetCategoryNextFile(m_strDataPath,m_pLB1,FILE_CATEGORY_G1);
		}
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 5;

	}

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS4E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS5E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Select group3",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	
	m_pLB1 = new CListBox;
	m_pLB1->Create(
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER | WS_VSCROLL 
					, CRect(10,40,230,210), this, 1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,70,240), this, 101);

	CString str;
	if(m_nType == TYPE_ADDRESS)	str = L"map";
	else						str = L"next";

	m_pBT2 = new CButton;
	m_pBT2->Create(str, WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);

	if(m_nType == TYPE_ADDRESS)	HlpDispAdrData(m_strGroupFile[2]);			//�Z�������t�@�C�� ���eLB�\��
	else						m_CategoryLB.DispCategoryData(m_strDataPath,m_pLB1,m_strGroupFile[2],1);	//�J�e�S���t�@�C�� ���eLB�\��

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS5E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS5E3(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 4;
	}

	int nPos = m_pLB1->GetCurSel();
	if(nBTNo == 2){
		if(m_nType == TYPE_ADDRESS){//map
			struct_address_file adr;
			CFile file;
			if(file.Open(m_strDataPath + FILE_ADR_FOLDER + m_strGroupFile[2], CFile::modeRead) == FALSE){
				m_pLB1->AddString(L"No data");	
				return;
			}
			file.Seek(nPos*sizeof(adr),CFile::begin);
			file.Read(&adr,sizeof(adr));
			file.Close();
			m_nEW = adr.nEW;
			m_nNS = adr.nNS;
			HlpOK();
		}
		else{//next
			//���J�e�S���t�@�C�����l��
			m_strGroupFile[3] = m_strCategoryAreaCode  + "\\" 
				+ m_strGroupFile[2].Left(2) +  
				m_CategoryLB.GetCategoryNextFile(m_strDataPath,m_pLB1,m_strGroupFile[2]);
			PostMessage(WM_EVENT,EV_1);
			m_nStatus		= 2;
		}
	}	
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS5E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS6E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(m_strED1,  SS_LEFT |
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
	m_pBT2->Create(L"info", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(85,220,155,240), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"map", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,220,230,240), this, 103);


	HlpOfflineSSearch();	//�������ʕ\��

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS6E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS6E3(int nBTNo)
{

	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= 1;
	}

	m_nSavePos = m_pLB1->GetCurSel();

	char buf[128];
	WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetEW[m_nSavePos]), -1, buf, 128,NULL, NULL);
	m_nEW = atoi(buf);
	WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetNS[m_nSavePos]), -1, buf, 128,NULL, NULL);
	m_nNS = atoi(buf);


	if(nBTNo == 2){
		//info
		PostMessage(WM_EVENT,EV_1,m_nSavePos);
		m_nSaveStatus   = 6;
		m_nStatus		= 7;
	}

	if(nBTNo == 3){
		//map
//		char buf[128];
//		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetEW[m_nSavePos]), -1, buf, 128,NULL, NULL);
//		m_nEW = atoi(buf);
//		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetNS[m_nSavePos]), -1, buf, 128,NULL, NULL);
//		m_nNS = atoi(buf);

		HlpOK();
	}
	
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS6E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS7E1(int nPos)
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	m_pST2 = new CStatic;
	m_pST2->Create(L"info",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,50,150,70), this, 1);

	m_pED1 = new CEdit;
	m_pED1->Create(ES_WANTRETURN |ES_UPPERCASE | ES_MULTILINE  |
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(10,80,230,210), this, 1);

	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,80,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"map", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(90,220,160,240), this, 102);



	m_pED1->SetWindowText(HlpGetInfoText(m_nGetInfoCode[nPos]));		//InfoText�\��


}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS7E2(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS7E3(int nBTNo)
{
	if(nBTNo == 1){
		//bak
		PostMessage(WM_EVENT,EV_1);
		m_nStatus		= m_nSaveStatus;		//6�܂���2
	}

	if(nBTNo == 2){
		//map
//		char buf[128];
//		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetEW[m_nSavePos]), -1, buf, 128,NULL, NULL);
//		m_nEW = atoi(buf);
//		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strGetNS[m_nSavePos]), -1, buf, 128,NULL, NULL);
//		m_nNS = atoi(buf);
		HlpOK();
	}

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgSearch::HlpS7E4(){TRACE(L"*** ������ظ��͒ʉ߂��Ȃ��͂�");}




/***********************************************************************************
*	��ײݎ{�݌���
***********************************************************************************/
void CDlgSearch::HlpOfflineSSearch()
{
	CWaitCursor a;		//�����v�J�[�\���\��(�p�����Ɍ��ɖ߂�)

	char buf[128];
	memset(buf, 0, sizeof(buf));//�iWideCharToMultiByte��NULL�I�[���Ă���΂���Ȃ��j
	WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strED1), -1, buf, 128,NULL, NULL);

	char *cpKey = &buf[0];
	//int nKeyLen = m_strED1.GetLength();//�����P�����łP���Ԃ邩�炾��
	int nKeyLen = strlen(buf);


	CNameBody *pNameBody = new CNameBody;

	if(pNameBody->Create(m_strDataPath+FILE_IDX_NAME,m_strDataPath+FILE_DAT_NAME) == FALSE){
		m_pLB1->AddString(L"No data.");
		delete pNameBody;
		return;				//NG
	}

	if(pNameBody->Load(cpKey,nKeyLen,m_Buf) == FALSE){
		m_pLB1->AddString(L"No data.");
		delete pNameBody;
		return;				//NG
	}
	delete pNameBody;



//------------------------------------------------------------------------------

	char tmp[100];
	int i,nPos=0;
	int nFlg=0;

	m_nGetCnt		=0;
	m_nGetCntMax		=0;

	int nLen = strlen(m_Buf);
	for(i=0;i<nLen;i++){
		if(m_Buf[i] == 0x0d || m_Buf[i] == 0x0a)continue;
		tmp[nPos]=m_Buf[i];
		if(tmp[nPos] == 0x2c){
			tmp[nPos] = 0;
			nPos=0;
			if(m_nGetCntMax >= SEARCH_STRING_MAX){
				TRACE(L"SEARCH_STRING_MAX over\n");
				break;
			}
			if(nFlg == 0){		//1�t�B�[���h��Get		EW
				m_strGetEW[m_nGetCnt] = tmp;
				nFlg=1;
				continue;

			}
			if(nFlg == 1){		//2�t�B�[���h��Get		NS
				m_strGetNS[m_nGetCnt] = tmp;
				nFlg=2;
				continue;
			}
			if(nFlg == 2){		//3�t�B�[���h��Get		NAME
//				m_strGetName[m_nGetCnt] = tmp;
//				m_pLB1->AddString(m_strGetName[m_nGetCnt]);	
				m_pLB1->AddString((CString)tmp);	
				nFlg=3;
				continue;
			}

			if(nFlg == 3){		//3�t�B�[���h��Get		INFOCODE
				m_nGetInfoCode[m_nGetCnt] = atoi(tmp);
				//�ŏI�t�B�[���h����
				nFlg=0;
				m_nGetCnt++;
				m_nGetCntMax = m_nGetCnt;
				continue;
			}
		}
		nPos++;
	}
//	m_nG1Cnt=0;
	m_pLB1->SetCurSel(0);



//----------dlg���ɕ\��--------------------------------
//	m_pSearch2->SetG2(m_SocBuf,strlen(m_SocBuf));	//m_SocBuf��offline�ł͎g�p���Ȃ��̂ŗ��p
//	m_pSearch2->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF);
//	m_VView2.SetAngle(90);					//�A���O���ݒ�
}

/***********************************************************************************
*	�Z�������t�@�C�� ���eLB�\��
***********************************************************************************/
void CDlgSearch::HlpDispAdrData(CString strFname)
{
	CFile file;
	int nPos=0;
	struct_address_file adr;

	if(file.Open(m_strDataPath + FILE_ADR_FOLDER + strFname, CFile::modeRead) == FALSE){
		m_pLB1->AddString(L"No data");	
		return;
	}

	for(;;){
		if(file.Read(&adr,sizeof(adr)) != sizeof(adr))break;
		CString str = adr.zName;
		m_pLB1->AddString(str);	
		nPos++;
		if(nPos == 100){
			m_pLB1->AddString(L"No display over count 100.");	
			break;
		}
	}

	file.Close();

	if(nPos > 0){
		m_pLB1->SetCurSel(0);
	}
}
/***********************************************************************************
*	INFOTEXT�\��
***********************************************************************************/
CString CDlgSearch::HlpGetInfoText(int nInfoCode)
{
	CInfoData InfoData;
	InfoData.Create(m_strDataPath + FILE_INFO_IDX);
	if(InfoData.GetIndexPos(nInfoCode) == -1)return L"No data.";

	return(InfoData.GetBodyString(m_strDataPath + FILE_INFO_DAT));
}