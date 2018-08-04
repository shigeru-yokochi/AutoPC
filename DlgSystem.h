#if !defined(AFX_DLGSYSTEM_H__1E00044F_17BD_40E4_8FE9_3B6E3AA202D9__INCLUDED_)
#define AFX_DLGSYSTEM_H__1E00044F_17BD_40E4_8FE9_3B6E3AA202D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgSystem.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSystem dialog
#include "define.h"
#include "GPS.h"

class CDlgSystem : public CDialog
{
// Construction
public:
	CDlgSystem(int nCountry,CGPS *pGPS,char *pzEnv,CWnd* pParent = NULL);   // standard constructor
	~CDlgSystem();

// Dialog Data
	//{{AFX_DATA(CDlgSystem)
	enum { IDD = IDD_SYSTEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSystem)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//����Ēʒm
private:
	int		m_nCountry;			//���썑
	CGPS *m_pGPS;
	char *m_pzEnv;				//�V�X�e�����ݒ�l�@0000 0=OFF 1=ON
//-----------���۰�--------------------------------------
	CStatic *m_pST1;
	CStatic *m_pST2;
	CStatic *m_pST3;
	CStatic *m_pST4;
	CStatic *m_pST5;
	CButton *m_pBT1;
	CButton *m_pBT2;
	CButton *m_pBT3;
	CButton *m_pBT4;
	CComboBox *m_pCB1;
	CComboBox *m_pCB2;
	CComboBox *m_pCB3;
	CComboBox *m_pCB4;

	int m_nStatus;

	void HlpDeleteCtl();								//�R���g���[���p��
	void OnBtn1();										//����1�N���b�N
	void OnBtn2();										//����2�N���b�N
	void OnBtn3();										//����3�N���b�N
	void OnBtn4();										//����4�N���b�N
	void HlpCancel();									//��ݾك{�^��
	void HlpOK();										//OK�{�^��
	void HlpDispGPSInfo();								//GPS���\��
//-------------��ظ��֐�--------------------------------------------------------------------
	void HlpS1E1();
	void HlpS1E2(int nBTNo);
	void HlpS2E1();
	void HlpS2E2(int nBTNo);
	void HlpS3E1();
	void HlpS3E2(int nBTNo);
	void HlpS4E1();
	void HlpS4E2(int nBTNo);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSYSTEM_H__1E00044F_17BD_40E4_8FE9_3B6E3AA202D9__INCLUDED_)
