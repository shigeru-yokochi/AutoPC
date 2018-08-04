#if !defined(AFX_DLGMYMAP_H__19AEC9CC_CD7D_44F4_9643_9F9EC9872139__INCLUDED_)
#define AFX_DLGMYMAP_H__19AEC9CC_CD7D_44F4_9643_9F9EC9872139__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgMyMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMyMap dialog
#include "define.h"
class CDlgMyMap : public CDialog
{
// Construction
public:
	CDlgMyMap(int nType,CString strDataPath,CWnd* pParent = NULL);   // standard constructor
	~CDlgMyMap();
	int m_nEW;
	int m_nNS;

// Dialog Data
	//{{AFX_DATA(CDlgMyMap)
	enum { IDD = IDD_MYMAP_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMyMap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMyMap)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//ｲﾍﾞﾝﾄ通知

private:
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
	int m_nType;			//0:set 1:get
	CString m_strDataPath;
	CString m_strED1;
	CString m_strED2;
	struct structMyMap{
		char zTitle[21];			//ﾀｲﾄﾙ（固定長NULL終端）
		int  nEW;
		int  nNS;
		char zMemo[101];			//memo（固定長NULL終端）
	};
	structMyMap m_structMyMap;
	int m_nPosSave;					//save時に使用
//-------------ﾍﾙﾊﾟ関数--------------------------------------------------------------------
	void HlpWrite();									//ファイルへ書込み
	void HlpDelete(int nRecNo);							//ファイル内レコード削除
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
	void HlpS4E1(int nPos);
	void HlpS4E2(int nBTNo);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMYMAP_H__19AEC9CC_CD7D_44F4_9643_9F9EC9872139__INCLUDED_)
