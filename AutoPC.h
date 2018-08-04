// AutoPC.h : main header file for the AUTOPC application
//

#if !defined(AFX_AUTOPC_H__6FFC58BB_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
#define AFX_AUTOPC_H__6FFC58BB_181C_11D5_894D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Define.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoPCApp:
// See AutoPC.cpp for the implementation of this class
//

class CAutoPCApp : public CWinApp
{
public:
	CAutoPCApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPCApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoPCApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPC_H__6FFC58BB_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
