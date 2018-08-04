#if !defined(AFX_ULP_H__E8D8BED6_387C_11D5_896D_0040CA1F5D30__INCLUDED_)
#define AFX_ULP_H__E8D8BED6_387C_11D5_896D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Ulp.h : header file
//

#define ULP_NO_DATA		"NODATA"
#define ULP_NO_RECEIVE	"NORECEIVE"
#define ULP_NO_RSP		"NORSP"

#include "CeTCPSoc.h"
#include "Define.h"

/////////////////////////////////////////////////////////////////////////////
// CUlp window

class CUlp : public CStatic
{
// Construction
public:
	CUlp(CWnd *pWnd,int nIndex=0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUlp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUlp();

	BOOL Create(int nPort);
	BOOL Connect(CString strAdr,int nPort);
	void Send(char *buf,int nLen,BOOL bClose=FALSE);
	int	 Receive(char* buf,int nLen);
	void Close();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUlp)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);			//ƒCƒxƒ“ƒg

private:
	CCeTCPSoc *m_pSoc;
	CWnd *m_pWnd;
	int m_nIndex;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULP_H__E8D8BED6_387C_11D5_896D_0040CA1F5D30__INCLUDED_)
