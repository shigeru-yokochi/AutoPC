#if !defined(AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_)
#define AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CategoryLB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoryLB window
#include "define.h"
class CCategoryLB : public CListBox
{
// Construction
public:
	CCategoryLB();

// Attributes
public:

// Operations
public:
	void DispCategoryData(CString strDataPath,CListBox *pLB1,CString strFname,int nType,
							int *npInfoCode=NULL);
														//カテゴリ検索ファイル 内容LB表示
	CString GetCategorySelectAreaCode(CString strDataPath,CListBox *pLB1,CString strFname);	
														//選択したカテゴリ地域コード獲得
	CString GetCategoryNextFile(CString strDataPath,CListBox *pLB1,CString strFname);
														//次カテゴリファイル名獲得
	BOOL GetEWNS(CString strDataPath,CListBox *pLB1,CString strFname,
						  int *npEW,int *npNS);			//現在選択しているアイテムの緯度経度を獲得

//	int GetStructCategoryFileSize();					//カテゴリ file 構造体サイズ獲得
	void SetCircumferenceItem(int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile);	//周辺検索ITEM全ての緯度経度と名称をバッファに格納
	int GetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile);		//周辺検索ITEM総数獲得
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoryLB)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCategoryLB();


	// Generated message map functions
protected:
	//{{AFX_MSG(CCategoryLB)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()


private:

//-----------地域file 構造体--------------------------------------
	struct struct_area_file{
		char zName[22];
		char zCode[4];
	};
//-----------大分類、小分類file 構造体--------------------------------------
	struct struct_G1G2_file{
		char zName[22];
		char zCode[2];
	};
//-----------カテゴリ file 構造体--------------------------------------
	struct struct_category_file{
		char zName[28];
		int nEW;
		int nNS;
		int nInfoCode;
	};

	int HlpGetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile);		//周辺検索ITEM総数獲得sub
	void HlpSetCircumferenceItem(int *npCnt,int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile);	//周辺検索ITEM全ての緯度経度と名称をバッファに格納sub
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATEGORYLB_H__82D4C948_4FA5_4124_9308_A3E26887AB81__INCLUDED_)
