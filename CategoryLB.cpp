// CategoryLB.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "CategoryLB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**************************************************************************
*	コンストラクタ
**************************************************************************/
CCategoryLB::CCategoryLB()
{
}
/**************************************************************************
*	デストラクタ
**************************************************************************/
CCategoryLB::~CCategoryLB()
{
}
/**************************************************************************
*	メッセージマップ
**************************************************************************/
BEGIN_MESSAGE_MAP(CCategoryLB, CListBox)
	//{{AFX_MSG_MAP(CCategoryLB)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/***********************************************************************************
*	カテゴリ検索ファイル 内容LB表示
*	nType 0:struct_area_file 1:struct_G1G2_file 2:struct_category_file
***********************************************************************************/
void CCategoryLB::DispCategoryData(CString strDataPath,CListBox *pLB1,CString strFname,int nType,
								   int *npInfoCode/*=NULL*/)
{
	CFile file;
	int nPos=0;
	struct_area_file area;
	struct_G1G2_file g1g2;
	struct_category_file category;
	CString str;
	char tmp[50];

	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strFname, CFile::modeRead) == FALSE){
		pLB1->AddString(L"No data");	
		return;
	}

	for(;;){
		if(nType == 0){
			if(file.Read(&area,sizeof(area)) != sizeof(area))break;
			memcpy(tmp,area.zName,sizeof(area.zName));tmp[sizeof(area.zName)]=0;
			str = tmp;
		}
		else
		if(nType == 1){
			if(file.Read(&g1g2,sizeof(g1g2)) != sizeof(g1g2))break;
			memcpy(tmp,g1g2.zName,sizeof(g1g2.zName));tmp[sizeof(g1g2.zName)]=0;
			str = tmp;
//			str = g1g2.zName;
		}
		else{
			if(file.Read(&category,sizeof(category)) != sizeof(category))break;
			memcpy(tmp,category.zName,sizeof(category.zName));tmp[sizeof(category.zName)]=0;
			str = tmp;
//			str = category.zName;
			if(npInfoCode != NULL){
				npInfoCode[nPos] = category.nInfoCode;
			}

		}
		
		pLB1->AddString(str);	
		nPos++;
		if(nPos == 100){
			pLB1->AddString(L"No display over count 100.");	
			break;
		}
	}

	file.Close();

	if(nPos > 0){
		pLB1->SetCurSel(0);
	}
}
/***********************************************************************************
*	選択したカテゴリ地域コード獲得
***********************************************************************************/
CString CCategoryLB::GetCategorySelectAreaCode(CString strDataPath,CListBox *pLB1,CString strFname)
{
	int nPos = pLB1->GetCurSel();
	CFile file;
	CString str;
	struct_area_file category;
	char tmp[10];

	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strFname, CFile::modeRead) == FALSE){
		pLB1->AddString(L"No data");	
		return "";
	}


	file.Seek(nPos*sizeof(category),CFile::begin);
	file.Read(&category,sizeof(category));
	memcpy(tmp,category.zCode,4);tmp[4]=0;
	str = tmp;
	file.Close();

	return str;
}
/***********************************************************************************
*	次カテゴリファイル名獲得
***********************************************************************************/
CString CCategoryLB::GetCategoryNextFile(CString strDataPath,CListBox *pLB1,CString strFname)
{
	int nPos = pLB1->GetCurSel();

	CFile file;
	CString str;
	char tmp[10];
	struct_G1G2_file category;

	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strFname, CFile::modeRead) == FALSE){
		pLB1->AddString(L"No data");	
		return "";
	}


	file.Seek(nPos*sizeof(category),CFile::begin);
	file.Read(&category,sizeof(category));
	memcpy(tmp,category.zCode,2);tmp[2]=0;
	str = tmp;
	file.Close();

	return str + L".dat";
}
/***********************************************************************************
*	現在選択しているアイテムの緯度経度を獲得
***********************************************************************************/
BOOL CCategoryLB::GetEWNS(CString strDataPath,CListBox *pLB1,CString strFname,
						  int *npEW,int *npNS)
{
	int nPos = pLB1->GetCurSel();
	struct_category_file category;
	CFile file;
	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strFname, CFile::modeRead) == FALSE){
		pLB1->AddString(L"No data");	
		return FALSE;
	}
	file.Seek(nPos*sizeof(category),CFile::begin);
	file.Read(&category,sizeof(category));
	file.Close();
	*npEW = category.nEW;
	*npNS = category.nNS;
	return TRUE;
}
/***********************************************************************************
*	カテゴリ file 構造体サイズ獲得
***********************************************************************************/
//int CCategoryLB::GetStructCategoryFileSize()
//{
//	return sizeof(struct_category_file);
//}
/****************************************************************************
*  周辺検索ITEM全ての緯度経度と名称をバッファに格納
*	緯度経度はEW,NS,EW,NS....の順で格納する
*****************************************************************************/
void CCategoryLB::SetCircumferenceItem(int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile)
{
	CString strArea;
	struct struct_area_file area;
	int nCnt=0;

	CFile file;
	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + FILE_CATEGORY_AREA, CFile::modeRead) == FALSE)return;
	for(;;){
		if(file.Read(&area,sizeof(area)) != sizeof(area))break;
		strArea.Format(L"\\%s\\",(CString)area.zCode);
		HlpSetCircumferenceItem(&nCnt,npBuf,strpName,strDataPath,strArea + strCircumferenceFile);
	}
	file.Close();
}
/****************************************************************************
*  周辺検索ITEM全ての緯度経度と名称をバッファに格納sub
*	緯度経度はEW,NS,EW,NS....の順で格納する
*****************************************************************************/
void CCategoryLB::HlpSetCircumferenceItem(int *npCnt,int *npBuf,CString *strpName,CString strDataPath,CString strCircumferenceFile)
{
	CFile file;
	struct_category_file category;
	int i;

	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strCircumferenceFile, CFile::modeRead) == FALSE)return;

	for(i=0;;i++){
		if(file.Read(&category,sizeof(category)) != sizeof(category))break;
			npBuf[*npCnt] = category.nEW;(*npCnt)++;
			npBuf[*npCnt] = category.nNS;(*npCnt)++;
			strpName[*npCnt/2-1] = category.zName;

	}
	file.Close();
}


/****************************************************************************
*  周辺検索ITEM総数獲得
*****************************************************************************/
int CCategoryLB::GetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile)
{
	int nCntMax=0;
	CString strArea;
	struct struct_area_file area;

	CFile file;
	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + FILE_CATEGORY_AREA, CFile::modeRead) == FALSE)return 0;
	for(;;){
		if(file.Read(&area,sizeof(area)) != sizeof(area))break;
		strArea.Format(L"\\%s\\",(CString)area.zCode);
		nCntMax += HlpGetCircumferenceItemCntMax(strDataPath ,strArea + strCircumferenceFile);
	}
	file.Close();
	return nCntMax;
}
/****************************************************************************
*  周辺検索ITEM総数獲得sub
*****************************************************************************/
int CCategoryLB::HlpGetCircumferenceItemCntMax(CString strDataPath,CString strCircumferenceFile)
{
	CFile file;
	if(file.Open(strDataPath + FILE_CATEGORY_FOLDER + strCircumferenceFile, CFile::modeRead) == FALSE)return 0;
	int nCntMax = file.GetLength()/sizeof(struct_category_file);
	file.Close();
	return nCntMax;
}