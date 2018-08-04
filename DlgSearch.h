#if !defined(AFX_DLGSEARCH_H__477B46F7_31D1_4685_BE36_9049A72186AD__INCLUDED_)
#define AFX_DLGSEARCH_H__477B46F7_31D1_4685_BE36_9049A72186AD__INCLUDED_

//#include "Define.h"

#include "CategoryLB.h"


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgSearch.h : header file
//


#include "define.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgSearch dialog

class CDlgSearch : public CDialog
{
// Construction
public:
	CDlgSearch(CString strDataPath,CWnd* pParent = NULL);   // standard constructor
	~CDlgSearch();
	
	void GetEWNS(int *npEW,int *npNS);					//�I������


// Dialog Data
	//{{AFX_DATA(CDlgSearch)
	enum { IDD = IDD_SEARCH_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSearch)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//����Ēʒm
private:
	#define 	TYPE_ADDRESS		0
	#define 	TYPE_CATEGORY		1

	CCategoryLB	m_CategoryLB;		//�ú���ް��k�a�\���׽

//-----------address file �\����--------------------------------------
	struct struct_address_file{
		char zName[22];
		int nEW;
		int nNS;
	};
	
//-----------���۰�--------------------------------------
	CStatic *m_pST1;
	CStatic *m_pST2;
	CEdit *m_pED1;
	CButton *m_pBT1;
	CButton *m_pBT2;
	CButton *m_pBT3;
	CButton *m_pBT4;
	CListBox *m_pLB1;	

	int m_nStatus;
	int m_nSaveStatus;
	int m_nSavePos;
	CString m_strDataPath;
	char	m_Buf[BUF_SIZE];
	CString m_strED1;
//	CString	m_strGetName[SEARCH_STRING_MAX];			//�������ʁ@����
	CString	m_strGetEW[SEARCH_STRING_MAX];				//�������ʁ@EW
	CString	m_strGetNS[SEARCH_STRING_MAX];				//�������ʁ@NS
	int		m_nGetInfoCode[SEARCH_STRING_MAX];			//�������ʁ@INFOCODE
	int m_nGetCnt;
	int m_nGetCntMax;
	int m_nEW;
	int m_nNS;
	int m_nType;
	CString m_strGroupFile[4];							//��ٰ�ߕʌ����t�@�C����


	CString m_strCategoryAreaCode;						//�I�������J�e�S���n��R�[�h

	void HlpDeleteCtl();								//�R���g���[���p��
	void OnBtn1();										//����1�N���b�N
	void OnBtn2();										//����2�N���b�N
	void OnBtn3();										//����3�N���b�N
	void OnBtn4();										//����4�N���b�N
	void HlpOfflineSSearch();							//��ײݎ{�݌���
	void HlpCancel();									//��ݾك{�^��
	void HlpOK();										//OK�{�^��
	void HlpDispAdrData(CString strFname);				//�Z�������t�@�C�� ���eLB�\��
	CString HlpGetInfoText(int nInfoCode);				//INFOTEXT�\��
//-------------��ظ��֐�--------------------------------------------------------------------
	void HlpS0E1();
	void HlpS0E2();
	void HlpS0E3(int nBTNo);
	void HlpS0E4();
	void HlpS1E1();
	void HlpS1E2();
	void HlpS1E3(int nBTNo);
	void HlpS1E4();
	void HlpS2E1();
	void HlpS2E2();
	void HlpS2E3(int nBTNo);
	void HlpS2E4();
	void HlpS3E1();
	void HlpS3E2();
	void HlpS3E3(int nBTNo);
	void HlpS3E4();
	void HlpS4E1();
	void HlpS4E2();
	void HlpS4E3(int nBTNo);
	void HlpS4E4();
	void HlpS5E1();
	void HlpS5E2();
	void HlpS5E3(int nBTNo);
	void HlpS5E4();
	void HlpS6E1();
	void HlpS6E2();
	void HlpS6E3(int nBTNo);
	void HlpS6E4();
	void HlpS7E1(int nPos);
	void HlpS7E2();
	void HlpS7E3(int nBTNo);
	void HlpS7E4();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSEARCH_H__477B46F7_31D1_4685_BE36_9049A72186AD__INCLUDED_)
