// FileIndex.h: interface for the CFileIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEINDEX_H__A2E78D68_9F9D_4EC7_ABA8_421EC73D8DCB__INCLUDED_)
#define AFX_FILEINDEX_H__A2E78D68_9F9D_4EC7_ABA8_421EC73D8DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileIndex  
{
public:
	CFileIndex();
	virtual ~CFileIndex();

	BOOL Create(CString strFName);
	int GetIndexPos(int nCode);
//--------------ファイルインデックス構造体---------
	typedef struct aaa{
		int nCode;
		int nPos;
		int nSize;
	}struct_Index;
	struct_Index *m_pIndex;

	int m_nIndexMaxCnt;
};

#endif // !defined(AFX_FILEINDEX_H__A2E78D68_9F9D_4EC7_ABA8_421EC73D8DCB__INCLUDED_)
