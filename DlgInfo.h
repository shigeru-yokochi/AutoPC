#if !defined(AFX_DLGINFO_H__2949A97C_3D94_4572_96CC_FB232FFC563F__INCLUDED_)
#define AFX_DLGINFO_H__2949A97C_3D94_4572_96CC_FB232FFC563F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInfo dialog

class CDlgInfo : public CDialog
{
// Construction
public:
	CDlgInfo();
	BOOL Create(CWnd* pWnd,int nIndex=0);

// Dialog Data
	//{{AFX_DATA(CDlgInfo)
	enum { IDD = IDD_INFO };
	CEdit	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInfo)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);		//²ÍÞÝÄ’Ê’m
private:
	CWnd* m_pWnd;
	int m_nIndex;										//²ÝÃÞ¯¸½

	void HlpKeyDown(int nCode);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINFO_H__2949A97C_3D94_4572_96CC_FB232FFC563F__INCLUDED_)
