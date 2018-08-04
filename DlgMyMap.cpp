// DlgMyMap.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgMyMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************************************************
*	�R���X�g���N�^
**************************************************************************/
CDlgMyMap::CDlgMyMap(int nType,CString strDataPath,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMyMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMyMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strDataPath	= strDataPath;
	m_nType			= nType;			//0:set 1:get
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
}
/**************************************************************************
*	�f�X�g���N�^
**************************************************************************/
CDlgMyMap::~CDlgMyMap()
{
	HlpDeleteCtl();		//�R���g���[���p��
}
/**************************************************************************
*	�f�[�^�G�N�X�`�F���W
**************************************************************************/
void CDlgMyMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMyMap)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
/**************************************************************************
*	���b�Z�[�W�}�b�v
**************************************************************************/
BEGIN_MESSAGE_MAP(CDlgMyMap, CDialog)
	ON_MESSAGE(WM_EVENT, OnEvent)					//����Ēʒm
	ON_BN_CLICKED(101,OnBtn1)						//m_pBT1�N���b�N
	ON_BN_CLICKED(102,OnBtn2)						//m_pBT2�N���b�N
	ON_BN_CLICKED(103,OnBtn3)						//m_pBT3�N���b�N
	ON_BN_CLICKED(104,OnBtn4)						//m_pBT4�N���b�N
	//{{AFX_MSG_MAP(CDlgMyMap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*************************************************************************
*	��������
**************************************************************************/
BOOL CDlgMyMap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	PostMessage(WM_EVENT,EV_1);		//�R���g���[���\�z�v��
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/**************************************************************************
*	�L�����Z���{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgMyMap::OnCancel() 
{
//	CDialog::OnCancel();
}
/**************************************************************************
*	OK�{�^���i���͂Ȃ��j
**************************************************************************/
void CDlgMyMap::OnOK() 
{
//	CDialog::OnOK();
}
/**************************************************************************
*	��ݾك{�^��
**************************************************************************/
void CDlgMyMap::HlpCancel() 
{
	CDialog::OnCancel();
}
/**************************************************************************
*	OK�{�^��
**************************************************************************/
void CDlgMyMap::HlpOK() 
{
	CDialog::OnOK();
}
/**************************************************************************
*	�R���g���[���p��
**************************************************************************/
void CDlgMyMap::HlpDeleteCtl()
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
void CDlgMyMap::OnBtn1(){PostMessage(WM_EVENT,EV_2,1);}		//����1�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgMyMap::OnBtn2(){PostMessage(WM_EVENT,EV_2,2);}		//����2�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgMyMap::OnBtn3(){PostMessage(WM_EVENT,EV_2,3);}		//����3�ʒm
/****************************************************************************
*  m_pBT�N���b�N
*****************************************************************************/
void CDlgMyMap::OnBtn4(){PostMessage(WM_EVENT,EV_2,4);}		//����4�ʒm

/****************************************************************************
*  ����Ēʒm
*  wParam:�����(define.h�Q��)
*  lParam:���낢��
*****************************************************************************/
LONG CDlgMyMap::OnEvent(UINT wParam, LONG lParam)
{
	CString str;
	switch(wParam){
		case EV_1:						//�����1
			TRACE(L"��ظ� %d 1 [CDlgMyMap]",m_nStatus);
			if(m_nStatus == 1){HlpS1E1();break;}
			if(m_nStatus == 2){HlpS2E1();break;}
			if(m_nStatus == 3){HlpS3E1();break;}
			if(m_nStatus == 4){HlpS4E1(int(lParam));break;}
			break;
		case EV_2:						//�����2
			TRACE(L"��ظ� %d 2 [CDlgMyMap]",m_nStatus);
			if(m_nStatus == 1){HlpS1E2(int(lParam));break;}
			if(m_nStatus == 2){HlpS2E2(int(lParam));break;}
			if(m_nStatus == 3){HlpS3E2(int(lParam));break;}
			if(m_nStatus == 4){HlpS4E2(int(lParam));break;}
			break;
		default:
			TRACE(L"*** ��ظ� %d [%d]���̲���Ă͖���`[CDlgMyMap]",m_nStatus,wParam);
			break;
	}

	return 0L;
}

/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS1E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Input password.",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,10,150,30), this, 1);

	m_pED1 = new CEdit;
	m_pED1->Create(ES_WANTRETURN |ES_UPPERCASE | ES_PASSWORD |
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(20,40,220,60), this, 1);
	m_pED1->SetWindowText(m_strED1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"cancel", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,70,110,90), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"ok", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(130,70,220,90), this, 102);

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS1E2(int nBTNo)
{
	if(nBTNo == 1){
		HlpCancel();
	}

	if(nBTNo == 2){
		m_pED1->GetWindowText(m_strED1);
		if(m_strED1 != DEF_MAYMAP_PASSWORD){
			#ifdef _DEBUG
				TRACE(L"Password err.");
			#else
				MessageBox(L"Password err.");
			#endif
		}
		else{			//�߽ܰ��OK
			m_strED1 = "";
			PostMessage(WM_EVENT,EV_1);	//�R���g���[���\�z�v��

			if(m_nType == 0) m_nStatus		= 2;		//set
			else             m_nStatus		= 3;		//get
		}

	}
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS2E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"Title",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,10,150,30), this, 1);

	m_pED1 = new CEdit;
	m_pED1->Create(ES_WANTRETURN |ES_UPPERCASE | 
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(20,40,220,60), this, 1);
	m_pED1->SetWindowText(m_strED1);


	m_pST2 = new CStatic;
	m_pST2->Create(L"Memo",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(20,70,150,90), this, 1);

	m_pED2 = new CEdit;
	m_pED2->Create(ES_WANTRETURN |ES_UPPERCASE | ES_MULTILINE  |
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(20,100,220,210), this, 1);
	m_pED2->SetWindowText(m_strED2);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"cancel", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(20,220,110,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"save", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(130,220,220,240), this, 102);

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS2E2(int nBTNo)
{
	if(nBTNo == 1){
		HlpCancel();
	}

	if(nBTNo == 2){
		m_pED1->GetWindowText(m_strED1);
		m_pED2->GetWindowText(m_strED2);
		if(m_strED1 == "")return;
		//---------���ِݒ�-------------
		char buf[128];
		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strED1), -1, buf, 128,NULL, NULL);
		int nLen = strlen(buf);		
		int nLenMax = sizeof(m_structMyMap.zTitle);
		if(nLen > nLenMax-1)nLen = nLenMax-1;
		memset(m_structMyMap.zTitle,0,nLenMax);
		memcpy(m_structMyMap.zTitle,buf,nLen);
		//--------�ܓx�o�x�ݒ�----------
		m_structMyMap.nEW = m_nEW;
		m_structMyMap.nNS = m_nNS;
		//--------memo�ݒ�----------
		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strED2), -1, buf, 128,NULL, NULL);
		nLen = strlen(buf);		
		nLenMax = sizeof(m_structMyMap.zMemo);
		if(nLen > nLenMax-1)nLen = nLenMax-1;
		memset(m_structMyMap.zMemo,0,nLenMax);
		memcpy(m_structMyMap.zMemo,buf,nLen);
		//------------------------------
		HlpWrite();			//�t�@�C���֏�����


		HlpOK();

	}	
}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS3E1()
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"title",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	
	m_pLB1 = new CListBox;
	m_pLB1->Create(
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER | WS_VSCROLL 
					, CRect(10,40,230,210), this, 1);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"cancel", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,60,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"delete", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(65,220,115,240), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"memo", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(120,220,170,240), this, 103);

	m_pBT4 = new CButton;
	m_pBT4->Create(L"map", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(175,220,225,240), this, 104);


//-----------�t�@�C������ǂݍ���LB�\��
	CFile file;
	if(file.Open(m_strDataPath + FILE_MYMAP, CFile::modeRead) == 0){
		TRACE(L"File read error.");
		return;
	}

	int nSize = sizeof(m_structMyMap);
	for(;;){
		if(file.Read(&m_structMyMap,nSize) != (DWORD)nSize)break;
		m_pLB1->AddString((CString)m_structMyMap.zTitle);	

	}
	file.Close();
	m_pLB1->SetCurSel(0);

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS3E2(int nBTNo)
{
	if(nBTNo == 1){
		HlpCancel();
	}

	int nPos = 	m_pLB1->GetCurSel();
	if(nPos == -1)return;


	if(nBTNo == 2){
		#ifdef _DEBUG
		TRACE(L"�폜�m�F");
		#else
		if(MessageBox(L"delete?",NULL,MB_YESNO|MB_ICONQUESTION) == IDNO)return;
		#endif
		HlpDelete(nPos);							//�t�@�C�������R�[�h�폜
		PostMessage(WM_EVENT,EV_1);	//�R���g���[���\�z�v��
	}


	if(nBTNo == 3){
		//memo����
		PostMessage(WM_EVENT,EV_1,nPos);	//�R���g���[���\�z�v��
		m_nStatus		= 4;
	}	


	if(nBTNo == 4){
		//�n�}�\��
		CString str;
		//-----------�t�@�C������ǂݍ���LB�\��
		CFile file;
		if(file.Open(m_strDataPath + FILE_MYMAP, CFile::modeRead) == 0){
			TRACE(L"File read error.");
			return;
		}
		int nSize = sizeof(m_structMyMap);
		file.Seek(nSize*nPos,CFile::begin);
		file.Read(&m_structMyMap,nSize);
		file.Close();
		m_nEW = m_structMyMap.nEW;
		m_nNS = m_structMyMap.nNS;
		HlpOK();
	}

}
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS4E1(int nPos)
{
	HlpDeleteCtl();		//�R���g���[���p��

	m_pST1 = new CStatic;
	m_pST1->Create(L"",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,10,150,30), this, 1);

	m_pST2 = new CStatic;
	m_pST2->Create(L"memo",  SS_LEFT |
					WS_CHILD | WS_VISIBLE
					, CRect(10,50,150,70), this, 1);

	m_pED2 = new CEdit;
	m_pED2->Create(ES_WANTRETURN |ES_UPPERCASE | ES_MULTILINE  |
					  WS_CHILD | WS_VISIBLE | WS_TABSTOP| WS_BORDER
					, CRect(10,80,230,210), this, 1);
	m_pED2->SetWindowText(m_strED2);


	m_pBT1 = new CButton;
	m_pBT1->Create(L"bak", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(10,220,80,240), this, 101);

	m_pBT2 = new CButton;
	m_pBT2->Create(L"map", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(90,220,160,240), this, 102);

	m_pBT3 = new CButton;
	m_pBT3->Create(L"save", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON , 
					CRect(170,220,230,240), this, 103);


//--------�\��
	CFile file;
	if(file.Open(m_strDataPath + FILE_MYMAP, CFile::modeRead) == 0){
		TRACE(L"File read error.");
		return;
	}

	int nSize = sizeof(m_structMyMap);
	file.Seek(nSize*nPos,CFile::begin);
	file.Read(&m_structMyMap,nSize);
	file.Close();

	CString str;
	str.Format(L"title:%s",(CString)m_structMyMap.zTitle);
	m_pST1->SetWindowText(str);									//title
	m_pED2->SetWindowText(CString(m_structMyMap.zMemo));		//memo

	m_nPosSave = nPos;											//save���Ɏg�p
}	
/****************************************************************************
*  ��ظ��֐�
*****************************************************************************/
void CDlgMyMap::HlpS4E2(int nBTNo)
{
	if(nBTNo == 1){
		PostMessage(WM_EVENT,EV_1);	//�R���g���[���\�z�v��
		m_nStatus		= 3;
	}	

	if(nBTNo == 2){
		//map
		m_nEW = m_structMyMap.nEW;
		m_nNS = m_structMyMap.nNS;
		HlpOK();
	}	

	if(nBTNo == 3){
		//save

		//--------memo�ݒ�----------
		m_pED2->GetWindowText(m_strED2);
		char buf[128];
		WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strED2), -1, buf, 128,NULL, NULL);
		int nLen = strlen(buf);		
		int nLenMax = sizeof(m_structMyMap.zMemo);
		if(nLen > nLenMax-1)nLen = nLenMax-1;
		memset(m_structMyMap.zMemo,0,nLenMax);
		memcpy(m_structMyMap.zMemo,buf,nLen);

		CFile file;
		if(file.Open(m_strDataPath + FILE_MYMAP, CFile::modeWrite) == 0){
			TRACE(L"File write error.");
			return;
		}
		int nSize = sizeof(m_structMyMap);
		file.Seek(nSize*m_nPosSave,CFile::begin);
		file.Write(&m_structMyMap,nSize);
		file.Close();

	}	
}

/****************************************************************************
*  �t�@�C���֏�����
*****************************************************************************/
void CDlgMyMap::HlpWrite()
{

	CFile file;
	if(file.Open(m_strDataPath + FILE_MYMAP,CFile::modeCreate | CFile::modeNoTruncate  | CFile::modeReadWrite) == 0){
		TRACE(L"File read write error.");
		return;
	}

	structMyMap tmp;
	int nSize = sizeof(m_structMyMap);

//	int nPos=0;
	for(;;){
		if(file.Read(&tmp,nSize) != (DWORD)nSize)break;
		if(memcmp(tmp.zTitle,m_structMyMap.zTitle,sizeof(m_structMyMap.zTitle)) == 0){
			//�X�V
			file.Seek(-nSize,CFile::current);
			file.Write(&m_structMyMap,nSize);
			file.Close();
//			goto TAG_MEMO;
			return;
		}
//		nPos++;
	}
	//�ǉ�������
	file.Write(&m_structMyMap,nSize);
	file.Close();

//TAG_MEMO:
//---------memo������
/*	CString str;
	str.Format(FILE_MYMAP_MEMO,nPos);

	if(file.Open(m_strDataPath + str,CFile::modeCreate | CFile::modeWrite) == 0){
		TRACE(L"File write error.");
		return;
	}

	char buf[1024];
	WideCharToMultiByte(CP_ACP, 0, LPCTSTR(m_strED2), -1, buf, 128,NULL, NULL);
	int nLen = strlen(buf);		

	file.Write(&nLen,4);
	file.Write(buf,nLen);
	file.Close();
*/


}

/****************************************************************************
*  �t�@�C�������R�[�h�폜
*	nRecNo 0..
*****************************************************************************/
void CDlgMyMap::HlpDelete(int nRecNo)
{
	structMyMap structTmp;

	CFile file;		//read�p
	if(file.Open(m_strDataPath + FILE_MYMAP, CFile::modeRead) == 0){
		TRACE(L"File read error.");
		return;
	}

	CFile file2;	//write�p
	if(file2.Open(m_strDataPath + L"tmp.dat", CFile::modeCreate | CFile::modeWrite) == 0){
		TRACE(L"File write error.");
		return;
	}


	int nSize = sizeof(structTmp);
	int i;
	for(i=0;;i++){
//	file.Seek(nSize*nPos,CFile::begin);
		if(file.Read(&structTmp,nSize) != (DWORD)nSize)break;
		if(i != nRecNo){
			file2.Write(&structTmp,nSize);
		}
	}
	file.Close();
	file2.Close();

	CFile::Remove(m_strDataPath + FILE_MYMAP);
	CFile::Rename(m_strDataPath + L"tmp.dat",m_strDataPath + FILE_MYMAP);
}
