// InfoData.h: interface for the CInfoData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFODATA_H__E2EC9C34_F16A_4999_B4B9_14DBD5F9D001__INCLUDED_)
#define AFX_INFODATA_H__E2EC9C34_F16A_4999_B4B9_14DBD5F9D001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInfoData  
{
public:
	CInfoData();
	virtual ~CInfoData();
	BOOL Create(CString strFName);
	int GetIndexPos(int nCode);
	CString GetBodyString(CString strFName);	//�{�f�B�l��
private:
	CFile m_file;
//--------------�t�@�C���C���f�b�N�X�\����---------
	typedef struct StructInfoIndex{
		int nInfoCode;
		int nBodyPos;
		int nBodySize;
	};
	StructInfoIndex *m_pIndex;
	int m_nIndexMaxCnt;

};

#endif // !defined(AFX_INFODATA_H__E2EC9C34_F16A_4999_B4B9_14DBD5F9D001__INCLUDED_)
