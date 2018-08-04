#if !defined(AFX_DIAL_H__C65A26D0_693C_4E8F_9E81_8B344EEA8B6D__INCLUDED_)
#define AFX_DIAL_H__C65A26D0_693C_4E8F_9E81_8B344EEA8B6D__INCLUDED_

#include "AutoPC.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDial dialog

class CDial : public CDialog
{
// Construction
public:
	CDial(); 
	~CDial();
	BOOL Create(CWnd* pWnd,CString *strpID,CString *strpDial,int nIndex=0);
// Dialog Data
	//{{AFX_DATA(CDial)
	enum { IDD = IDD_DIAL };
	CString	m_strID;
	CString	m_strDial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDial)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//ｲﾍﾞﾝﾄ通知
private:
//-------------定数-----------------------------------------
	enum define{
		TO_NENT_CHAR		= 1,	//次キャラクタ入力
		TO_VAL_NENT_CHAR	= 1000,
	};
//------------------変数-----------------------------------------------
	int m_nIndex;										//ｲﾝﾃﾞｯｸｽ
	int m_nPos;
//------------------ｸﾗｽ-----------------------------------------------
	CWnd* m_pWnd;
	CBrush m_Brush;
	CString *m_strpID;
	CString *m_strpDial;


	void HlpTRACE(CString str);
	void HlpKeyDown(int nCode);
	void HlpRedrawWindow(int nPos);
	BOOL HlpEnter();

	void HlpDown(CString *strp);
	void HlpUp(CString *strp);
	TCHAR HlpGetNextChar(TCHAR c,BOOL bInc=TRUE);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAL_H__C65A26D0_693C_4E8F_9E81_8B344EEA8B6D__INCLUDED_)
