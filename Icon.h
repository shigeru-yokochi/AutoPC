// Icon.h: interface for the CIcon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICON_H__E0274912_2F9F_11D5_8964_0040CA1F5D30__INCLUDED_)
#define AFX_ICON_H__E0274912_2F9F_11D5_8964_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ICON_MAX	300

//#include "Common.h"

#include "FileBody.h"

class CIcon  
{
public:
	CIcon(CString strDataPath);
	virtual ~CIcon();
	BOOL LoadIconAll();	//ICOファイルを全て読み込み
	void LoadIcon(CString strFname,int nIndex);
	void DrawIcon(CDC *pDC,int nCenterX,int nCenterY,int nIndex,double dfFact=1.0);
	void Clr();						//クリア
	int GetLoadIconIndex(int nFname);	//読む込み済みアイコンインデックスNo獲得

	void SetMemRec9(DWORD *dwpCode,int nMapLevel);
	long GetBodyMaxCnt();

	struct_IconBody *m_pStructIconBody;

private:
	int		m_nLoadFname[ICON_MAX];
	int		m_nLoadIconMax;

	CFileBody fb1;
	CFileBody fb2;
	CFileBody fb3;
	CFileBody fb4;
	CFileBody fb5;
	CFileBody fb6;
	CFileBody fb7;
	CFileBody fb8;
	CFileBody fb9;
	CFileBody fb10;

	int m_nMapLevel;


	HICON m_hIcon[ICON_MAX];

};

#endif // !defined(AFX_ICON_H__E0274912_2F9F_11D5_8964_0040CA1F5D30__INCLUDED_)
