// NameIndex.h: interface for the CNameIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAMEINDEX_H__7E84C44A_9460_447B_A856_CA81C7A581BF__INCLUDED_)
#define AFX_NAMEINDEX_H__7E84C44A_9460_447B_A856_CA81C7A581BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNameIndex  
{
public:
	CNameIndex();
	virtual ~CNameIndex();
	BOOL Create(CString strFName);
	int GetIndexPos(char* cpBuf,int nLen,int *npKeyCnt);
	int GetBodyPos(int nPos);
	void GetBodyName(int nPos,char *cpName);

//--------------ファイルインデックス構造体---------
	typedef struct aaa{
		char cpName[28];
		int nPos;
	}struct_Index;
	struct_Index *m_pIndex;

	int m_nIndexMaxCnt;
private:
	CFile m_file;

};

#endif // !defined(AFX_NAMEINDEX_H__7E84C44A_9460_447B_A856_CA81C7A581BF__INCLUDED_)
