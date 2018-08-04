#if !defined(AFX_SEARCHID_H__4CE0FA80_1620_40A2_8297_03BF1F196B0C__INCLUDED_)
#define AFX_SEARCHID_H__4CE0FA80_1620_40A2_8297_03BF1F196B0C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SearchID.h : header file
//
#include "AutoPC.h"


/////////////////////////////////////////////////////////////////////////////
// CSearchID dialog

#define SEARCH_ID_TYPE_SET		 1
#define SEARCH_ID_TYPE_GET		 2
#define SEARCH_ID_TYPE_RSPOK	 3
#define SEARCH_ID_TYPE_RSPNG	 4


//--------------IDåüçıIFç\ë¢ëÃ---------
struct StructSearchID{
	BYTE	cType;		//1:set 2:get 3:rspOK 4:rspNG
	BYTE    cID[11];
	DWORD	dwEW;
	DWORD	dwNS;
};
typedef StructSearchID struct_SearchID;

class CSearchID : public CDialog
{
// Construction
public:
	CSearchID(struct_SearchID *pStructSearchID);
	~CSearchID();
	BOOL Create(CWnd* pWnd,int nIndex=0);

// Dialog Data
	//{{AFX_DATA(CSearchID)
	enum { IDD = IDD_SEARCH_ID };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchID)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchID)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//≤Õﬁ›ƒí ím
private:
//------------------ïœêî-----------------------------------------------
	int m_nIndex;										//≤›√ﬁØ∏Ω
	int m_nPos;
	struct_SearchID *m_pStructSearchID;
//------------------∏◊Ω-----------------------------------------------
	CWnd* m_pWnd;
	CBrush m_Brush;
//	CWnd *m_pWndBtn[12];


	void HlpKeyDown(int nCode);
	void HlpRedrawWindow(int nPos);
	void HlpEnter(void);
	void HlpGetData(void);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHID_H__4CE0FA80_1620_40A2_8297_03BF1F196B0C__INCLUDED_)
