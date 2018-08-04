#if !defined(AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_)
#define AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CategoryLB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoryLB window
#include "define.h"
class CCategoryLB : public CListBox
{
// Construction
public:
	CCategoryLB();

// Attributes
public:

// Operations
public:
	void DispCategoryData(CString strDataPath,CListBox *pLB1,CString strFname,int nType,
							int *npInfoCode=NULL);
														//�J�e�S�������t�@�C�� ���eLB�\��
	CString GetCategorySelectAreaCode(CString strDataPath,CListBox *pLB1,CString strFname);	
														//�I�������J�e�S���n��R�[�h�l��
	CString GetCategoryNextFile(CString strDataPath,CListBox *pLB1,CString strFname);
														//���J�e�S���t�@�C�����l��
	BOOL GetEWNS(CString strDataPath,CListBox *pLB1,CString strFname,
						  int *npEW,int *npNS);			//���ݑI�����Ă���A�C�e���̈ܓx�o�x���l��

//	int GetStructCategoryFileSize();					//�J�e�S�� file �\���̃T�C�Y�l��
	void SetCircumferenceItem(int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile);	//���ӌ���ITEM�S�Ă̈ܓx�o�x�Ɩ��̂��o�b�t�@�Ɋi�[
	int GetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile);		//���ӌ���ITEM�����l��
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoryLB)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCategoryLB();


	// Generated message map functions
protected:
	//{{AFX_MSG(CCategoryLB)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


private:

//-----------�n��file �\����--------------------------------------
	struct struct_area_file{
		char zName[22];
		char zCode[4];
	};
//-----------�啪�ށA������file �\����--------------------------------------
	struct struct_G1G2_file{
		char zName[22];
		char zCode[2];
	};
//-----------�J�e�S�� file �\����--------------------------------------
	struct struct_category_file{
		char zName[28];
		int nEW;
		int nNS;
		int nInfoCode;
	};

	int HlpGetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile);		//���ӌ���ITEM�����l��sub
	void HlpSetCircumferenceItem(int *npCnt,int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile);	//���ӌ���ITEM�S�Ă̈ܓx�o�x�Ɩ��̂��o�b�t�@�Ɋi�[sub
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_)
