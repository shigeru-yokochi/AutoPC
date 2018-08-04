#if !defined(AFX_RASENTRY_H__35E4C4E3_4187_4811_87F5_B76B0DADDC91__INCLUDED_)
#define AFX_RASENTRY_H__35E4C4E3_4187_4811_87F5_B76B0DADDC91__INCLUDED_

#include "AutoPC.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RasEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRasEntry dialog

class CRasEntry : public CDialog
{
// Construction
public:
	CRasEntry();
	~CRasEntry();
	BOOL Create(CWnd* pWnd,CString *pstrEntryName,int nIndex=0);

// Dialog Data
	//{{AFX_DATA(CRasEntry)
	enum { IDD = IDD_RAS_ENTRY };
	CListBox	m_List1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRasEntry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRasEntry)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//≤Õﬁ›ƒí ím

private:
//------------------ïœêî-----------------------------------------------
	int m_nIndex;										//≤›√ﬁØ∏Ω
	int m_nPos;
	int m_nPosMax;
//------------------∏◊Ω-----------------------------------------------
	CString *m_pstrEntryName;
	CWnd* m_pWnd;
	void HlpKeyDown(int nCode);
	int HlpGetEntry();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RASENTRY_H__35E4C4E3_4187_4811_87F5_B76B0DADDC91__INCLUDED_)
