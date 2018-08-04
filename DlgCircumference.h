#if !defined(AFX_DLGCIRCUMFERENCE_H__FE8609A1_3A85_40A9_B6B8_66A8B02EFF00__INCLUDED_)
#define AFX_DLGCIRCUMFERENCE_H__FE8609A1_3A85_40A9_B6B8_66A8B02EFF00__INCLUDED_

#include "CategoryLB.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgCircumference.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCircumference dialog
#include "define.h"
class CDlgCircumference : public CDialog
{
// Construction
public:
	CDlgCircumference(CString strDataPath,CWnd* pParent = NULL);   // standard constructor
	~CDlgCircumference();
	int GetCircumferenceItemCntMax();		//周辺検索ITEM総数獲得
	void SetCircumferenceItem(int *npBuf,CString *strpName);	//周辺検索ITEM全ての緯度経度と名称をバッファに格納
	int m_nRetCode;							//0:cancel 1:stop 2:start
// Dialog Data
	//{{AFX_DATA(CDlgCircumference)
	enum { IDD = IDD_CIRCUMFERENCE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCircumference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCircumference)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//ｲﾍﾞﾝﾄ通知

private:
	CCategoryLB	m_CategoryLB;		//ｶﾃｺﾞﾘﾃﾞｰﾀＬＢ表示ｸﾗｽ
//-----------ｺﾝﾄﾛｰﾙ--------------------------------------
	CStatic *m_pST1;
	CStatic *m_pST2;
	CEdit *m_pED1;
	CEdit *m_pED2;
	CButton *m_pBT1;
	CButton *m_pBT2;
	CButton *m_pBT3;
	CButton *m_pBT4;
	CListBox *m_pLB1;	

//-------------変数--------------------------------------------------------------------
	int m_nStatus;
	CString m_strDataPath;
	CString m_strED1;
	CString m_strED2;
	CString m_strCircumferenceFile;		//選択したファイル名
	CString m_strNextFile;
//-------------ﾍﾙﾊﾟ関数--------------------------------------------------------------------
	void HlpDeleteCtl();								//コントロール廃棄
	void HlpCancel();									//ｷｬﾝｾﾙボタン
	void HlpOK();										//OKボタン
	void OnBtn1();										//ﾎﾞﾀﾝ1クリック
	void OnBtn2();										//ﾎﾞﾀﾝ2クリック
	void OnBtn3();										//ﾎﾞﾀﾝ3クリック
	void OnBtn4();										//ﾎﾞﾀﾝ4クリック


//-------------ﾏﾄﾘｸｽ関数--------------------------------------------------------------------
	void HlpS1E1();
	void HlpS1E2(int nBTNo);
	void HlpS2E1();
	void HlpS2E2(int nBTNo);
	void HlpS3E1();
	void HlpS3E2(int nBTNo);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCIRCUMFERENCE_H__FE8609A1_3A85_40A9_B6B8_66A8B02EFF00__INCLUDED_)
