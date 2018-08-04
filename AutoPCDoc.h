// AutoPCDoc.h : interface of the CAutoPCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPCDOC_H__6FFC58C2_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
#define AFX_AUTOPCDOC_H__6FFC58C2_181C_11D5_894D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CAutoPCDoc : public CDocument
{
protected: // create from serialization only
	CAutoPCDoc();
	DECLARE_DYNCREATE(CAutoPCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPCDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPCDOC_H__6FFC58C2_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
