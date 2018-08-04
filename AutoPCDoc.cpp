// AutoPCDoc.cpp : implementation of the CAutoPCDoc class
//

#include "stdafx.h"
#include "AutoPC.h"

#include "AutoPCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoPCDoc

IMPLEMENT_DYNCREATE(CAutoPCDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoPCDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoPCDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoPCDoc construction/destruction

CAutoPCDoc::CAutoPCDoc()
{
	// TODO: add one-time construction code here

}

CAutoPCDoc::~CAutoPCDoc()
{
}

BOOL CAutoPCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoPCDoc serialization

void CAutoPCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoPCDoc diagnostics

#ifdef _DEBUG
void CAutoPCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoPCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoPCDoc commands
