// LinkIndex.h: interface for the CLinkIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKINDEX_H__A36B8263_A4C1_469F_8B30_E3C1A6C3E179__INCLUDED_)
#define AFX_LINKINDEX_H__A36B8263_A4C1_469F_8B30_E3C1A6C3E179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//--------------ファイルボディ構造体---------
	typedef struct bbb{
		int nEW;
		int nNS;
	}struct_Body;


class CLinkIndex  
{
public:
	CLinkIndex();
	virtual ~CLinkIndex();

	BOOL Create(CString strPath);
	int GetIndexPos(int nEW1,int nNS1,int nEW2,int nNS2,int *npBlkCnt);
	BOOL GetBody(int nPos,int nBlkCnt);			//Body獲得

//--------------ファイルインデックス構造体---------
	typedef struct aaa{
		int nEW1;
		int nNS1;
		int nEW2;
		int nNS2;
		int nPos;
		int nBlkCnt;
	}struct_Index;
	struct_Index *m_pIndex;

	int m_nIndexMaxCnt;


	struct_Body *m_pBody;	//body


private:
	CFile *m_pFileBody;
};

#endif // !defined(AFX_LINKINDEX_H__A36B8263_A4C1_469F_8B30_E3C1A6C3E179__INCLUDED_)
