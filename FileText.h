// FileText.h: interface for the CFileText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETEXT_H__27884F6A_288E_11D5_895C_0040CA1F5D30__INCLUDED_)
#define AFX_FILETEXT_H__27884F6A_288E_11D5_895C_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileText : public CFile  
{
public:
	CFileText();
	virtual ~CFileText();
	int GetRec(char *ReceiveBuff,int nBufSize);

};

#endif // !defined(AFX_FILETEXT_H__27884F6A_288E_11D5_895C_0040CA1F5D30__INCLUDED_)
