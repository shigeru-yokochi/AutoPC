#if !defined(AFX_CETCPSOC_H__E8D8BED5_387C_11D5_896D_0040CA1F5D30__INCLUDED_)
#define AFX_CETCPSOC_H__E8D8BED5_387C_11D5_896D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CeTCPSoc.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCeTCPSoc command target

class CCeTCPSoc : public CCeSocket
{
// Attributes
public:

// Operations
public:
	CCeTCPSoc(CWnd * pWnd,int nIndex=0);
	virtual ~CCeTCPSoc();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeTCPSoc)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCeTCPSoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:


private:
	CWnd* m_pWnd;	
	int m_nIndex;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CETCPSOC_H__E8D8BED5_387C_11D5_896D_0040CA1F5D30__INCLUDED_)
