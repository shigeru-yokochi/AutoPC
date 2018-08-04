// Icon.cpp: implementation of the CIcon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "Icon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/***********************************************************************************
*	ｺﾝｽﾄﾗｸﾀ
***********************************************************************************/
CIcon::CIcon(CString strDataPath)
{
	int i;
	for(i=0;i<ICON_MAX;i++){
		m_hIcon[i] = NULL;
	}

	int nVal,nMaxCnt=0;

	fb1.Create(FB_ICON,strDataPath+FILE_IDX_ICON1,strDataPath+FILE_DAT_ICON1,&nVal);nMaxCnt+=nVal;
	fb2.Create(FB_ICON,strDataPath+FILE_IDX_ICON2,strDataPath+FILE_DAT_ICON2,&nVal);nMaxCnt+=nVal;
	fb3.Create(FB_ICON,strDataPath+FILE_IDX_ICON3,strDataPath+FILE_DAT_ICON3,&nVal);nMaxCnt+=nVal;
	fb4.Create(FB_ICON,strDataPath+FILE_IDX_ICON4,strDataPath+FILE_DAT_ICON4,&nVal);nMaxCnt+=nVal;
	fb5.Create(FB_ICON,strDataPath+FILE_IDX_ICON5,strDataPath+FILE_DAT_ICON5,&nVal);nMaxCnt+=nVal;
	fb6.Create(FB_ICON,strDataPath+FILE_IDX_ICON6,strDataPath+FILE_DAT_ICON6,&nVal);nMaxCnt+=nVal;
	fb7.Create(FB_ICON,strDataPath+FILE_IDX_ICON7,strDataPath+FILE_DAT_ICON7,&nVal);nMaxCnt+=nVal;
	fb8.Create(FB_ICON,strDataPath+FILE_IDX_ICON8,strDataPath+FILE_DAT_ICON8,&nVal);nMaxCnt+=nVal;
	fb9.Create(FB_ICON,strDataPath+FILE_IDX_ICON9,strDataPath+FILE_DAT_ICON9,&nVal);nMaxCnt+=nVal;
	fb10.Create(FB_ICON,strDataPath+FILE_IDX_ICON10,strDataPath+FILE_DAT_ICON10,&nVal);nMaxCnt+=nVal;

}
/***********************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
***********************************************************************************/
CIcon::~CIcon()
{
	int i;
	for(i=0;i<ICON_MAX;i++){
		if(m_hIcon[i] != NULL){
			DestroyIcon(m_hIcon[i]);
		}
	}

}
/***********************************************************************************
*	９タイル分のデータをファイルよりメモリに設定
***********************************************************************************/
void CIcon::SetMemRec9(DWORD *dwpCode,int nMapLevel)
{
	m_nMapLevel = nMapLevel;
	Clr();

	switch(m_nMapLevel){
		case 1:
			m_pStructIconBody	= fb1.m_pIconBody;
			fb1.SetMemRec9(dwpCode);
			break;
		case 2:
			m_pStructIconBody	= fb2.m_pIconBody;
			fb2.SetMemRec9(dwpCode);
			break;
		case 3:
			m_pStructIconBody	= fb3.m_pIconBody;
			fb3.SetMemRec9(dwpCode);
			break;
		case 4:
			m_pStructIconBody	= fb4.m_pIconBody;
			fb4.SetMemRec9(dwpCode);
			break;
		case 5:
			m_pStructIconBody	= fb5.m_pIconBody;
			fb5.SetMemRec9(dwpCode);
			break;
		case 6:
			m_pStructIconBody	= fb6.m_pIconBody;
			fb6.SetMemRec9(dwpCode);
			break;
		case 7:
			m_pStructIconBody	= fb7.m_pIconBody;
			fb7.SetMemRec9(dwpCode);
			break;
		case 8:
			m_pStructIconBody	= fb8.m_pIconBody;
			fb8.SetMemRec9(dwpCode);
			break;
		case 9:
			m_pStructIconBody	= fb9.m_pIconBody;
			fb9.SetMemRec9(dwpCode);
			break;
		case 10:
			m_pStructIconBody	= fb10.m_pIconBody;
			fb10.SetMemRec9(dwpCode);
			break;

	}

}
/***********************************************************************************
*	ボディ数獲得
***********************************************************************************/
long CIcon::GetBodyMaxCnt()
{
	switch(m_nMapLevel){
		case 1:	return fb1.m_lBodyMaxCnt;
		case 2:	return fb2.m_lBodyMaxCnt;
		case 3:	return fb3.m_lBodyMaxCnt;
		case 4:	return fb4.m_lBodyMaxCnt;
		case 5:	return fb5.m_lBodyMaxCnt;
		case 6:	return fb6.m_lBodyMaxCnt;
		case 7:	return fb7.m_lBodyMaxCnt;
		case 8:	return fb8.m_lBodyMaxCnt;
		case 9:	return fb9.m_lBodyMaxCnt;
		case 10:return fb10.m_lBodyMaxCnt;

	}
	return 0; 
}
//***********************************************************************************
//*	クリア
//***********************************************************************************
void CIcon::Clr()
{
	switch(m_nMapLevel){
		case 1:	fb1.Clr();break;
		case 2:	fb2.Clr();break;
		case 3:	fb3.Clr();break;
		case 4:	fb4.Clr();break;
		case 5:	fb5.Clr();break;
		case 6:	fb6.Clr();break;
		case 7:	fb7.Clr();break;
		case 8:	fb8.Clr();break;
		case 9:	fb9.Clr();break;
		case 10:fb10.Clr();break;

	}

}

/***********************************************************************************
*	全て読み込み
***********************************************************************************/
BOOL CIcon::LoadIconAll()
{
	int nPos=0;
	m_nLoadFname[nPos] = 12;nPos++;
	m_nLoadFname[nPos] = 13;nPos++;
	m_nLoadFname[nPos] = 14;nPos++;
	m_nLoadFname[nPos] = 104;nPos++;
	m_nLoadFname[nPos] = 105;nPos++;
	m_nLoadFname[nPos] = 111;nPos++;
	m_nLoadFname[nPos] = 112;nPos++;
	m_nLoadFname[nPos] = 118;nPos++;
	m_nLoadFname[nPos] = 121;nPos++;
	m_nLoadFname[nPos] = 201;nPos++;
	m_nLoadFname[nPos] = 203;nPos++;
	m_nLoadFname[nPos] = 204;nPos++;
	m_nLoadFname[nPos] = 206;nPos++;
	m_nLoadFname[nPos] = 207;nPos++;
	m_nLoadFname[nPos] = 208;nPos++;
	m_nLoadFname[nPos] = 209;nPos++;
	m_nLoadFname[nPos] = 210;nPos++;
	m_nLoadFname[nPos] = 211;nPos++;
	m_nLoadFname[nPos] = 212;nPos++;
	m_nLoadFname[nPos] = 213;nPos++;
	m_nLoadFname[nPos] = 214;nPos++;
	m_nLoadFname[nPos] = 215;nPos++;
	m_nLoadFname[nPos] = 225;nPos++;
	m_nLoadFname[nPos] = 301;nPos++;
	m_nLoadFname[nPos] = 401;nPos++;
	m_nLoadFname[nPos] = 405;nPos++;
	m_nLoadFname[nPos] = 407;nPos++;
	m_nLoadFname[nPos] = 408;nPos++;
	m_nLoadFname[nPos] = 40801;nPos++;
	m_nLoadFname[nPos] = 409;nPos++;
	m_nLoadFname[nPos] = 411;nPos++;
	m_nLoadFname[nPos] = 412;nPos++;
	m_nLoadFname[nPos] = 413;nPos++;
	m_nLoadFname[nPos] = 414;nPos++;
	m_nLoadFname[nPos] = 415;nPos++;
	m_nLoadFname[nPos] = 500;nPos++;
	m_nLoadFname[nPos] = 501;nPos++;
	m_nLoadFname[nPos] = 502;nPos++;
	m_nLoadFname[nPos] = 506;nPos++;
	m_nLoadFname[nPos] = 601;nPos++;
	m_nLoadFname[nPos] = 801;nPos++;
	m_nLoadFname[nPos] = 802;nPos++;
	m_nLoadFname[nPos] = 803;nPos++;
	m_nLoadFname[nPos] = 901;nPos++;
	m_nLoadFname[nPos] = 910;nPos++;
	m_nLoadFname[nPos] = 911;nPos++;
	m_nLoadFname[nPos] = 913;nPos++;
	m_nLoadFname[nPos] = 1001;nPos++;
	m_nLoadFname[nPos] = 1002;nPos++;
	m_nLoadFname[nPos] = 1004;nPos++;
	m_nLoadFname[nPos] = 1007;nPos++;
	m_nLoadFname[nPos] = 1008;nPos++;
	m_nLoadFname[nPos] = 1009;nPos++;
	m_nLoadFname[nPos] = 11101;nPos++;
	m_nLoadFname[nPos] = 11102;nPos++;
	m_nLoadFname[nPos] = 11103;nPos++;
	m_nLoadFname[nPos] = 1110306;nPos++;
	m_nLoadFname[nPos] = 11104;nPos++;
	m_nLoadFname[nPos] = 11105;nPos++;
	m_nLoadFname[nPos] = 11106;nPos++;
	m_nLoadFname[nPos] = 1110602;nPos++;
	m_nLoadFname[nPos] = 11107;nPos++;
	m_nLoadFname[nPos] = 1111;nPos++;
	m_nLoadFname[nPos] = 11110;nPos++;
	m_nLoadFname[nPos] = 111101;nPos++;
	m_nLoadFname[nPos] = 11111;nPos++;
	m_nLoadFname[nPos] = 11112;nPos++;
	m_nLoadFname[nPos] = 11113;nPos++;
	m_nLoadFname[nPos] = 11114;nPos++;
	m_nLoadFname[nPos] = 11115;nPos++;
	m_nLoadFname[nPos] = 11116;nPos++;
	m_nLoadFname[nPos] = 11117;nPos++;
	m_nLoadFname[nPos] = 11119;nPos++;
	m_nLoadFname[nPos] = 1112;nPos++;
	m_nLoadFname[nPos] = 11121;nPos++;
	m_nLoadFname[nPos] = 1113;nPos++;
	m_nLoadFname[nPos] = 1114;nPos++;
	m_nLoadFname[nPos] = 1115;nPos++;
	m_nLoadFname[nPos] = 1116;nPos++;
	m_nLoadFname[nPos] = 1118;nPos++;
	m_nLoadFname[nPos] = 11188;nPos++;
	m_nLoadFname[nPos] = 1119;nPos++;
	m_nLoadFname[nPos] = 1212;nPos++;
	m_nLoadFname[nPos] = 1215;nPos++;
	m_nLoadFname[nPos] = 2020;nPos++;
	m_nLoadFname[nPos] = 2201;nPos++;
	m_nLoadFname[nPos] = 2202;nPos++;
	m_nLoadFname[nPos] = 2203;nPos++;
	m_nLoadFname[nPos] = 220306;nPos++;
	m_nLoadFname[nPos] = 2204;nPos++;
	m_nLoadFname[nPos] = 2205;nPos++;
	m_nLoadFname[nPos] = 2206;nPos++;
	m_nLoadFname[nPos] = 2207;nPos++;
	m_nLoadFname[nPos] = 2208;nPos++;
	m_nLoadFname[nPos] = 2209;nPos++;
	m_nLoadFname[nPos] = 2210;nPos++;
	m_nLoadFname[nPos] = 22101;nPos++;
	m_nLoadFname[nPos] = 2211;nPos++;
	m_nLoadFname[nPos] = 2212;nPos++;
	m_nLoadFname[nPos] = 2213;nPos++;
	m_nLoadFname[nPos] = 2214;nPos++;
	m_nLoadFname[nPos] = 2215;nPos++;
	m_nLoadFname[nPos] = 2216;nPos++;
	m_nLoadFname[nPos] = 2217;nPos++;
	m_nLoadFname[nPos] = 2218;nPos++;
	m_nLoadFname[nPos] = 2219;nPos++;
	m_nLoadFname[nPos] = 221902;nPos++;
	m_nLoadFname[nPos] = 2220;nPos++;
	m_nLoadFname[nPos] = 2221;nPos++;
	m_nLoadFname[nPos] = 2222;nPos++;
	m_nLoadFname[nPos] = 2223;nPos++;
	m_nLoadFname[nPos] = 2224;nPos++;
	m_nLoadFname[nPos] = 2225;nPos++;
	m_nLoadFname[nPos] = 2226;nPos++;
	m_nLoadFname[nPos] = 2227;nPos++;
	m_nLoadFname[nPos] = 2228;nPos++;
	m_nLoadFname[nPos] = 2229;nPos++;
	m_nLoadFname[nPos] = 2230;nPos++;
	m_nLoadFname[nPos] = 2231;nPos++;
	m_nLoadFname[nPos] = 2232;nPos++;
	m_nLoadFname[nPos] = 2233;nPos++;
	m_nLoadFname[nPos] = 2234;nPos++;
	m_nLoadFname[nPos] = 2235;nPos++;
	m_nLoadFname[nPos] = 2236;nPos++;
	m_nLoadFname[nPos] = 2237;nPos++;
	m_nLoadFname[nPos] = 2238;nPos++;
	m_nLoadFname[nPos] = 2239;nPos++;
	m_nLoadFname[nPos] = 2240;nPos++;
	m_nLoadFname[nPos] = 2241;nPos++;
	m_nLoadFname[nPos] = 2242;nPos++;
	m_nLoadFname[nPos] = 2243;nPos++;
	m_nLoadFname[nPos] = 2244;nPos++;
	m_nLoadFname[nPos] = 2245;nPos++;
	m_nLoadFname[nPos] = 2246;nPos++;
	m_nLoadFname[nPos] = 2247;nPos++;
	m_nLoadFname[nPos] = 2248;nPos++;
	m_nLoadFname[nPos] = 2256;nPos++;
	m_nLoadFname[nPos] = 2259;nPos++;
	m_nLoadFname[nPos] = 2262;nPos++;
	m_nLoadFname[nPos] = 2267;nPos++;
	m_nLoadFname[nPos] = 2282;nPos++;
	m_nLoadFname[nPos] = 2288;nPos++;
	m_nLoadFname[nPos] = 2299;nPos++;
	m_nLoadFname[nPos] = 3301;nPos++;
	m_nLoadFname[nPos] = 3302;nPos++;
	m_nLoadFname[nPos] = 3303;nPos++;
	m_nLoadFname[nPos] = 3304;nPos++;
	m_nLoadFname[nPos] = 3305;nPos++;
	m_nLoadFname[nPos] = 3306;nPos++;
	m_nLoadFname[nPos] = 3307;nPos++;
	m_nLoadFname[nPos] = 3308;nPos++;
	m_nLoadFname[nPos] = 3309;nPos++;
	m_nLoadFname[nPos] = 3310;nPos++;
	m_nLoadFname[nPos] = 3311;nPos++;
	m_nLoadFname[nPos] = 3312;nPos++;
	m_nLoadFname[nPos] = 3313;nPos++;
	m_nLoadFname[nPos] = 3314;nPos++;
	m_nLoadFname[nPos] = 3315;nPos++;
	m_nLoadFname[nPos] = 3316;nPos++;
	m_nLoadFname[nPos] = 3317;nPos++;
	m_nLoadFname[nPos] = 3318;nPos++;
	m_nLoadFname[nPos] = 3319;nPos++;
	m_nLoadFname[nPos] = 3320;nPos++;
	m_nLoadFname[nPos] = 3321;nPos++;
	m_nLoadFname[nPos] = 3322;nPos++;
	m_nLoadFname[nPos] = 3323;nPos++;
	m_nLoadFname[nPos] = 3324;nPos++;
	m_nLoadFname[nPos] = 3325;nPos++;
	m_nLoadFname[nPos] = 3326;nPos++;
	m_nLoadFname[nPos] = 3327;nPos++;
	m_nLoadFname[nPos] = 3328;nPos++;
	m_nLoadFname[nPos] = 3329;nPos++;
	m_nLoadFname[nPos] = 3330;nPos++;
	m_nLoadFname[nPos] = 3331;nPos++;
	m_nLoadFname[nPos] = 3332;nPos++;
	m_nLoadFname[nPos] = 3333;nPos++;
	m_nLoadFname[nPos] = 3334;nPos++;
	m_nLoadFname[nPos] = 3335;nPos++;
	m_nLoadFname[nPos] = 3336;nPos++;
	m_nLoadFname[nPos] = 3337;nPos++;
	m_nLoadFname[nPos] = 3338;nPos++;
	m_nLoadFname[nPos] = 3339;nPos++;
	m_nLoadFname[nPos] = 3340;nPos++;
	m_nLoadFname[nPos] = 3341;nPos++;
	m_nLoadFname[nPos] = 3342;nPos++;
	m_nLoadFname[nPos] = 3343;nPos++;
	m_nLoadFname[nPos] = 3344;nPos++;
	m_nLoadFname[nPos] = 3345;nPos++;
	m_nLoadFname[nPos] = 3346;nPos++;
	m_nLoadFname[nPos] = 3347;nPos++;
	m_nLoadFname[nPos] = 3348;nPos++;
	m_nLoadFname[nPos] = 3349;nPos++;
	m_nLoadFname[nPos] = 3350;nPos++;
	m_nLoadFname[nPos] = 3351;nPos++;
	m_nLoadFname[nPos] = 3352;nPos++;
	m_nLoadFname[nPos] = 3353;nPos++;
	m_nLoadFname[nPos] = 3354;nPos++;
	m_nLoadFname[nPos] = 3355;nPos++;
	m_nLoadFname[nPos] = 3356;nPos++;
	m_nLoadFname[nPos] = 3357;nPos++;
	m_nLoadFname[nPos] = 3358;nPos++;
	m_nLoadFname[nPos] = 3359;nPos++;
	m_nLoadFname[nPos] = 3360;nPos++;
	m_nLoadFname[nPos] = 3361;nPos++;
	m_nLoadFname[nPos] = 3362;nPos++;
	m_nLoadFname[nPos] = 3363;nPos++;
	m_nLoadFname[nPos] = 3364;nPos++;
	m_nLoadFname[nPos] = 3365;nPos++;
	m_nLoadFname[nPos] = 3366;nPos++;
	m_nLoadFname[nPos] = 3367;nPos++;
	m_nLoadFname[nPos] = 3368;nPos++;
	m_nLoadFname[nPos] = 3369;nPos++;
	m_nLoadFname[nPos] = 3370;nPos++;
	m_nLoadFname[nPos] = 3371;nPos++;
	m_nLoadFname[nPos] = 3372;nPos++;
	m_nLoadFname[nPos] = 3373;nPos++;
	m_nLoadFname[nPos] = 3374;nPos++;

	m_nLoadIconMax=nPos;
	if(m_nLoadIconMax > ICON_MAX){
		AfxMessageBox(L"ICON MAX OVER");
		m_nLoadIconMax = ICON_MAX;
	}

	int i;
	for(i=0;i<m_nLoadIconMax;i++){
		if(m_nLoadFname[i] == 12)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0012);
		if(m_nLoadFname[i] == 13)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0013);
		if(m_nLoadFname[i] == 14)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0014);
		if(m_nLoadFname[i] == 104)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0104);
		if(m_nLoadFname[i] == 105)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0105);
		if(m_nLoadFname[i] == 111)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0111);
		if(m_nLoadFname[i] == 112)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0112);
		if(m_nLoadFname[i] == 118)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0118);
		if(m_nLoadFname[i] == 121)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0121);
		if(m_nLoadFname[i] == 201)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0201);
		if(m_nLoadFname[i] == 203)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0203);
		if(m_nLoadFname[i] == 204)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0204);
		if(m_nLoadFname[i] == 206)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0206);
		if(m_nLoadFname[i] == 207)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0207);
		if(m_nLoadFname[i] == 208)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0208);
		if(m_nLoadFname[i] == 209)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0209);
		if(m_nLoadFname[i] == 210)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0210);
		if(m_nLoadFname[i] == 211)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0211);
		if(m_nLoadFname[i] == 212)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0212);
		if(m_nLoadFname[i] == 213)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0213);
		if(m_nLoadFname[i] == 214)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0214);
		if(m_nLoadFname[i] == 215)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0215);
		if(m_nLoadFname[i] == 225)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0225);
		if(m_nLoadFname[i] == 301)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0301);
		if(m_nLoadFname[i] == 401)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0401);
		if(m_nLoadFname[i] == 405)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0405);
		if(m_nLoadFname[i] == 407)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0407);
		if(m_nLoadFname[i] == 408)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0408);
		if(m_nLoadFname[i] == 40801)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_040801);
		if(m_nLoadFname[i] == 409)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0409);
		if(m_nLoadFname[i] == 411)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0411);
		if(m_nLoadFname[i] == 412)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0412);
		if(m_nLoadFname[i] == 413)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0413);
		if(m_nLoadFname[i] == 414)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0414);
		if(m_nLoadFname[i] == 415)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0415);
		if(m_nLoadFname[i] == 500)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0500);
		if(m_nLoadFname[i] == 501)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0501);
		if(m_nLoadFname[i] == 502)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0502);
		if(m_nLoadFname[i] == 506)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0506);
		if(m_nLoadFname[i] == 601)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0601);
		if(m_nLoadFname[i] == 801)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0801);
		if(m_nLoadFname[i] == 802)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0802);
		if(m_nLoadFname[i] == 803)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0803);
		if(m_nLoadFname[i] == 901)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0901);
		if(m_nLoadFname[i] == 910)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0910);
		if(m_nLoadFname[i] == 911)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0911);
		if(m_nLoadFname[i] == 913)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0913);
		if(m_nLoadFname[i] == 1001)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1001);
		if(m_nLoadFname[i] == 1002)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1002);
		if(m_nLoadFname[i] == 1004)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1004);
		if(m_nLoadFname[i] == 1007)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1007);
		if(m_nLoadFname[i] == 1008)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1008);
		if(m_nLoadFname[i] == 1009)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1009);
		if(m_nLoadFname[i] == 11101)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11101);
		if(m_nLoadFname[i] == 11102)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11102);
		if(m_nLoadFname[i] == 11103)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11103);
		if(m_nLoadFname[i] == 1110306)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1110306);
		if(m_nLoadFname[i] == 11104)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11104);
		if(m_nLoadFname[i] == 11105)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11105);
		if(m_nLoadFname[i] == 11106)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11106);
		if(m_nLoadFname[i] == 1110602)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1110602);
		if(m_nLoadFname[i] == 11107)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11107);
		if(m_nLoadFname[i] == 1111)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1111);
		if(m_nLoadFname[i] == 11110)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11110);
		if(m_nLoadFname[i] == 111101)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_111101);
		if(m_nLoadFname[i] == 11111)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11111);
		if(m_nLoadFname[i] == 11112)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11112);
		if(m_nLoadFname[i] == 11113)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11113);
		if(m_nLoadFname[i] == 11114)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11114);
		if(m_nLoadFname[i] == 11115)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11115);
		if(m_nLoadFname[i] == 11116)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11116);
		if(m_nLoadFname[i] == 11117)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11117);
		if(m_nLoadFname[i] == 11119)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11119);
		if(m_nLoadFname[i] == 1112)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1112);
		if(m_nLoadFname[i] == 11121)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11121);
		if(m_nLoadFname[i] == 1113)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1113);
		if(m_nLoadFname[i] == 1114)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1114);
		if(m_nLoadFname[i] == 1115)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1115);
		if(m_nLoadFname[i] == 1116)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1116);
		if(m_nLoadFname[i] == 1118)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1118);
		if(m_nLoadFname[i] == 11188)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_11188);
		if(m_nLoadFname[i] == 1119)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1119);
		if(m_nLoadFname[i] == 1212)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1212);
		if(m_nLoadFname[i] == 1215)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_1215);
		if(m_nLoadFname[i] == 2020)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2020);
		if(m_nLoadFname[i] == 2201)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2201);
		if(m_nLoadFname[i] == 2202)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2202);
		if(m_nLoadFname[i] == 2203)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2203);
		if(m_nLoadFname[i] == 220306)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_220306);
		if(m_nLoadFname[i] == 2204)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2204);
		if(m_nLoadFname[i] == 2205)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2205);
		if(m_nLoadFname[i] == 2206)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2206);
		if(m_nLoadFname[i] == 2207)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2207);
		if(m_nLoadFname[i] == 2208)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2208);
		if(m_nLoadFname[i] == 2209)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2209);
		if(m_nLoadFname[i] == 2210)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2210);
		if(m_nLoadFname[i] == 22101)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_22101);
		if(m_nLoadFname[i] == 2211)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2211);
		if(m_nLoadFname[i] == 2212)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2212);
		if(m_nLoadFname[i] == 2213)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2213);
		if(m_nLoadFname[i] == 2214)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2214);
		if(m_nLoadFname[i] == 2215)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2215);
		if(m_nLoadFname[i] == 2216)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2216);
		if(m_nLoadFname[i] == 2217)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2217);
		if(m_nLoadFname[i] == 2218)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2218);
		if(m_nLoadFname[i] == 2219)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2219);
		if(m_nLoadFname[i] == 221902)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_221902);
		if(m_nLoadFname[i] == 2220)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2220);
		if(m_nLoadFname[i] == 2221)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2221);
		if(m_nLoadFname[i] == 2222)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2222);
		if(m_nLoadFname[i] == 2223)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2223);
		if(m_nLoadFname[i] == 2224)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2224);
		if(m_nLoadFname[i] == 2225)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2225);
		if(m_nLoadFname[i] == 2226)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2226);
		if(m_nLoadFname[i] == 2227)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2227);
		if(m_nLoadFname[i] == 2228)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2228);
		if(m_nLoadFname[i] == 2229)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2229);
		if(m_nLoadFname[i] == 2230)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2230);
		if(m_nLoadFname[i] == 2231)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2231);
		if(m_nLoadFname[i] == 2232)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2232);
		if(m_nLoadFname[i] == 2233)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2233);
		if(m_nLoadFname[i] == 2234)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2234);
		if(m_nLoadFname[i] == 2235)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2235);
		if(m_nLoadFname[i] == 2236)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2236);
		if(m_nLoadFname[i] == 2237)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2237);
		if(m_nLoadFname[i] == 2238)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2238);
		if(m_nLoadFname[i] == 2239)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2239);
		if(m_nLoadFname[i] == 2240)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2240);
		if(m_nLoadFname[i] == 2241)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2241);
		if(m_nLoadFname[i] == 2242)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2242);
		if(m_nLoadFname[i] == 2243)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2243);
		if(m_nLoadFname[i] == 2244)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2244);
		if(m_nLoadFname[i] == 2245)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2245);
		if(m_nLoadFname[i] == 2246)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2246);
		if(m_nLoadFname[i] == 2247)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2247);
		if(m_nLoadFname[i] == 2248)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2248);
		if(m_nLoadFname[i] == 2256)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2256);
		if(m_nLoadFname[i] == 2259)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2259);
		if(m_nLoadFname[i] == 2262)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2262);
		if(m_nLoadFname[i] == 2267)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2267);
		if(m_nLoadFname[i] == 2282)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2282);
		if(m_nLoadFname[i] == 2288)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2288);
		if(m_nLoadFname[i] == 2299)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_2299);
		if(m_nLoadFname[i] == 3301)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3301);
		if(m_nLoadFname[i] == 3302)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3302);
		if(m_nLoadFname[i] == 3303)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3303);
		if(m_nLoadFname[i] == 3304)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3304);
		if(m_nLoadFname[i] == 3305)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3305);
		if(m_nLoadFname[i] == 3306)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3306);
		if(m_nLoadFname[i] == 3307)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3307);
		if(m_nLoadFname[i] == 3308)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3308);
		if(m_nLoadFname[i] == 3309)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3309);
		if(m_nLoadFname[i] == 3310)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3310);
		if(m_nLoadFname[i] == 3311)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3311);
		if(m_nLoadFname[i] == 3312)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3312);
		if(m_nLoadFname[i] == 3313)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3313);
		if(m_nLoadFname[i] == 3314)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3314);
		if(m_nLoadFname[i] == 3315)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3315);
		if(m_nLoadFname[i] == 3316)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3316);
		if(m_nLoadFname[i] == 3317)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3317);
		if(m_nLoadFname[i] == 3318)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3318);
		if(m_nLoadFname[i] == 3319)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3319);
		if(m_nLoadFname[i] == 3320)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3320);
		if(m_nLoadFname[i] == 3321)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3321);
		if(m_nLoadFname[i] == 3322)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3322);
		if(m_nLoadFname[i] == 3323)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3323);
		if(m_nLoadFname[i] == 3324)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3324);
		if(m_nLoadFname[i] == 3325)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3325);
		if(m_nLoadFname[i] == 3326)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3326);
		if(m_nLoadFname[i] == 3327)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3327);
		if(m_nLoadFname[i] == 3328)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3328);
		if(m_nLoadFname[i] == 3329)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3329);
		if(m_nLoadFname[i] == 3330)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3330);
		if(m_nLoadFname[i] == 3331)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3331);
		if(m_nLoadFname[i] == 3332)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3332);
		if(m_nLoadFname[i] == 3333)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3333);
		if(m_nLoadFname[i] == 3334)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3334);
		if(m_nLoadFname[i] == 3335)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3335);
		if(m_nLoadFname[i] == 3336)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3336);
		if(m_nLoadFname[i] == 3337)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3337);
		if(m_nLoadFname[i] == 3338)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3338);
		if(m_nLoadFname[i] == 3339)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3339);
		if(m_nLoadFname[i] == 3340)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3340);
		if(m_nLoadFname[i] == 3341)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3341);
		if(m_nLoadFname[i] == 3342)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3342);
		if(m_nLoadFname[i] == 3343)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3343);
		if(m_nLoadFname[i] == 3344)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3344);
		if(m_nLoadFname[i] == 3345)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3345);
		if(m_nLoadFname[i] == 3346)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3346);
		if(m_nLoadFname[i] == 3347)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3347);
		if(m_nLoadFname[i] == 3348)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3348);
		if(m_nLoadFname[i] == 3349)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3349);
		if(m_nLoadFname[i] == 3350)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3350);
		if(m_nLoadFname[i] == 3351)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3351);
		if(m_nLoadFname[i] == 3352)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3352);
		if(m_nLoadFname[i] == 3353)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3353);
		if(m_nLoadFname[i] == 3354)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3354);
		if(m_nLoadFname[i] == 3355)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3355);
		if(m_nLoadFname[i] == 3356)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3356);
		if(m_nLoadFname[i] == 3357)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3357);
		if(m_nLoadFname[i] == 3358)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3358);
		if(m_nLoadFname[i] == 3359)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3359);
		if(m_nLoadFname[i] == 3360)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3360);
		if(m_nLoadFname[i] == 3361)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3361);
		if(m_nLoadFname[i] == 3362)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3362);
		if(m_nLoadFname[i] == 3363)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3363);
		if(m_nLoadFname[i] == 3364)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3364);
		if(m_nLoadFname[i] == 3365)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3365);
		if(m_nLoadFname[i] == 3366)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3366);
		if(m_nLoadFname[i] == 3367)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3367);
		if(m_nLoadFname[i] == 3368)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3368);
		if(m_nLoadFname[i] == 3369)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3369);
		if(m_nLoadFname[i] == 3370)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3370);
		if(m_nLoadFname[i] == 3371)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3371);
		if(m_nLoadFname[i] == 3372)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3372);
		if(m_nLoadFname[i] == 3373)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3373);
		if(m_nLoadFname[i] == 3374)	m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_3374);

//		if(m_nLoadFname[i] == L"0411.ICO"){
//			m_hIcon[i] = AfxGetApp()->LoadIcon(IDI_0411);
//		}
	}







	return TRUE;

}
/***********************************************************************************
*	読む込み済みアイコンインデックスNo獲得
*	return 0..インデックス番号 -1:NG
***********************************************************************************/
int CIcon::GetLoadIconIndex(int nFname)
{
	int i;
	for(i=0;i<m_nLoadIconMax;i++){
		if(m_nLoadFname[i] == nFname)return i;
	}

	return -1;
}
/***********************************************************************************
*	ファイルから読み込み
***********************************************************************************/
void CIcon::LoadIcon(CString strFname,int nIndex)
{
//	strFname = L"0101.ICO";
//	::ExtractIconEx(strFname,0,&m_hIcon[nIndex],NULL,1);
	::ExtractIconEx(strFname,0,&m_hIcon[nIndex],NULL,1);

int n = GetLastError();
}
/***********************************************************************************
*	描画
***********************************************************************************/
//void CIcon::DrawIcon(HDC hDC,int nCenterX,int nCenterY,int nIndex,double dfFact/*=1.0*/)
void CIcon::DrawIcon(CDC *pDC,int nCenterX,int nCenterY,int nIndex,double dfFact/*=1.0*/)
{
	if(m_hIcon[nIndex] == NULL)return;

	int nSize = (int)(dfFact * 32);

//	CDC *pDCIcon = GetDC();

//	::DrawIconEx(hDC,
//		nCenterX,
//		nCenterY,
//		m_hIcon[nIndex],
//		nSize,nSize,
//		NULL,
//		NULL,
//		DI_NORMAL);


	pDC->DrawIcon(
		nCenterX,
		nCenterY,
		m_hIcon[nIndex]);



//		ReleaseDC(pDCIcon);
}
