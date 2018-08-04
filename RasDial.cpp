// RasDial.cpp: implementation of the CRasDial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "RasDial.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/***********************************************************************************
*	コンストラクタ
***********************************************************************************/
CRasDial::CRasDial()
{
	m_bASYNC=FALSE;
	m_hRasConn=NULL;
}
/***********************************************************************************
*	デストラクタ
***********************************************************************************/
CRasDial::~CRasDial()
{
	if(m_hRasConn != NULL){
		::RasHangUp(m_hRasConn);
		::Sleep(SLEEP_232C_CLOSE);
	}
}
/***********************************************************************************
*	エントリ検出
***********************************************************************************/
int CRasDial::GetEntry()
{
	RASENTRYNAME renDmy,*pRen;
	DWORD dw,dwSize,dwEntries,dwResult;

	dwSize=sizeof(RASENTRYNAME);
	renDmy.dwSize=sizeof(RASENTRYNAME);
	dwResult=::RasEnumEntries(NULL,NULL,&renDmy,&dwSize,&dwEntries);

	if(!dwEntries)
	{
		TRACE(L"No entry.[CRasDial]\n");
		return -1;
	}

	if(dwResult && dwResult!=ERROR_BUFFER_TOO_SMALL)
	{
		TRACE(L"GetEntry()err-2[CRasDial]\n");
		return -2;
	}

	pRen=new RASENTRYNAME[dwEntries];
	pRen[0].dwSize=sizeof(RASENTRYNAME);
	dwResult=::RasEnumEntries(NULL,NULL,pRen,&dwSize,&dwEntries);
	
	if(dwResult)
	{
		delete [] pRen;
		TRACE(L"GetEntry()err-3[CRasDial]\n");
		return -3;
	}

	for(dw=0;dw<dwEntries;dw++){				//エントリ一覧表示
		TRACE(L"%s[CRasDial]\n",pRen[dw].szEntryName);
	}

	delete [] pRen;

	return 0;
}
/***********************************************************************************
*	Connect
***********************************************************************************/
BOOL CRasDial::Connect(HANDLE hWnd,CString strEntryName) 
{
	DWORD dwResult;
//	RASDIALPARAMS rdp;
//	CString str;

	if(m_hRasConn != NULL){
		TRACE(L"NG Connected.[CRasDial]\n");
		return FALSE;
	}

//#ifdef AUTO_PC
//	ZeroMemory(&rdp,sizeof(RASDIALPARAMS));
//#else
//	memset(&rdp,0,sizeof(RASDIALPARAMS));
//#endif

//	rdp.dwSize=sizeof(RASDIALPARAMS);

//	lstrcpy(rdp.szEntryName,pEntryName);
//	lstrcpy(rdp.szUserName,pUserName);
//	lstrcpy(rdp.szPassword,pPassword);



	RASDIALPARAMS rdp;
	BOOL b;
//	char szEntryName[21];

	ZeroMemory(&rdp,sizeof(RASDIALPARAMS));
	rdp.dwSize=sizeof(RASDIALPARAMS);

//	strcpy(szEntryName,"1");	

	lstrcpy(rdp.szEntryName,strEntryName);
	::RasGetEntryDialParams(NULL,&rdp,&b);



	TRACE(L"Connecting...[CRasDial]\n");

	m_hRasConn=NULL;
	
	if(m_bASYNC==TRUE)
		dwResult=::RasDial(NULL,NULL,&rdp,0xFFFFFFFF,hWnd,&m_hRasConn);
	else
		dwResult=::RasDial(NULL,NULL,&rdp,NULL,NULL,&m_hRasConn);


	if(!dwResult){
		if(m_bASYNC==TRUE)TRACE(L"Async Connecting...[CRasDial]\n");
		else			  TRACE(L"Connect OK[CRasDial]\n");
		return TRUE;			//OK
	}


//	::RasGetErrorString(dwResult,szErrStr,512);
	TRACE(L"Connect err(%u)[CRasDial]\n",dwResult);
	::RasHangUp(m_hRasConn);
	::Sleep(SLEEP_232C_CLOSE);
	m_hRasConn=NULL;
	return FALSE;
}
/***********************************************************************************
*	接続中検査
***********************************************************************************/
BOOL CRasDial::ChkConnected()
{
	RASCONNSTATUS status;
	::RasGetConnectStatus(m_hRasConn,&status);
	if(status.rasconnstate == RASCS_Connected)return TRUE;

	return FALSE;
}
/***********************************************************************************
*	NewEntry
***********************************************************************************/
BOOL CRasDial::NewEntry(CString strEntry,CString strPhoneNo,CString strUserName,CString strPassword) 
{
//	CString m_strModemName= L"Hayes Compatible on COM1";
	CString m_strModemName= L"MELCO-IGM-PCM56KH_MODEM";

//	CString strEntry = "NewEntry";
	if(HlpCreateNewEntry(strEntry, "modem",
		m_strModemName, RASNP_Ip, RASFP_Ppp, strPhoneNo) 
		!= ERROR_ALREADY_EXISTS)
	{
		DWORD dwfOptions = RASEO_SwCompression | 
			RASEO_RequireEncryptedPw | RASEO_RequireMsEncryptedPw |
			RASEO_UseLogonCredentials;
		if(HlpSetEntryOption(strEntry, dwfOptions, TRUE) != 0) 
		{
			return FALSE;
		}
	}



	RASDIALPARAMS params;	//　接続情報の構造体
	memset( &params, '\0', sizeof( RASDIALPARAMS ) );
	params.dwSize = sizeof( RASDIALPARAMS );	//　構造体のサイズをセット
//	lstrcpy( params.szEntryName,L"NewEntry");
	lstrcpy( params.szEntryName,strEntry);
	BOOL bPassword = TRUE;//パスワードも取得するというフラグ
	::RasGetEntryDialParams( NULL, &params, &bPassword );

//	lstrcpy( params.szUserName,L"AutoPC");	
//	lstrcpy( params.szPassword,L"");
	lstrcpy( params.szUserName,strUserName);	
	lstrcpy( params.szPassword,strPassword);


	::RasSetEntryDialParams( NULL, &params, FALSE );





	return TRUE;
}
/***********************************************************************************
*	Close
***********************************************************************************/
void CRasDial::Close()
{
	if(m_hRasConn == NULL)return;
	::RasHangUp(m_hRasConn);
	::Sleep(SLEEP_232C_CLOSE);
	TRACE(L"RasClose[CRasDial]\n");
	m_hRasConn = NULL;
}
/***********************************************************************************
*	NewEntry
***********************************************************************************/
DWORD CRasDial::HlpCreateNewEntry(CString strEntry, 
		CString strDeviceType, 
		CString strDeviceName, 
		DWORD dwfNetProtocols, DWORD dwFrameProtocal, 
		CString strLocalPhone,
		CString strPhoneBook /*=_T("")*/)
{
	LPTSTR lpszEntry = strEntry.GetBuffer(1);
	strEntry.ReleaseBuffer();
	LPTSTR lpszPhoneBook = strPhoneBook.GetBuffer(1);
	if(strPhoneBook == _T(""))
		lpszPhoneBook = NULL;
	strPhoneBook.ReleaseBuffer();
	if(RasValidateEntryName(lpszPhoneBook, lpszEntry) != ERROR_ALREADY_EXISTS)
	{
		RASENTRY rasEntry;
#ifdef AUTO_PC
		::ZeroMemory(&rasEntry, sizeof(rasEntry));
#else
		memset(&rasEntry, 0,sizeof(rasEntry));
#endif
		rasEntry.dwSize = sizeof(rasEntry);
		lstrcpy(rasEntry.szLocalPhoneNumber, strLocalPhone);
		rasEntry.dwfNetProtocols = dwfNetProtocols;   		
		rasEntry.dwFramingProtocol = dwFrameProtocal;
		// DON'T USE "RASDT_Modem", use "modem", otherwise dwRV = 87
		lstrcpy(rasEntry.szDeviceType, strDeviceType); 
		lstrcpy(rasEntry.szDeviceName, strDeviceName);
#ifdef AUTO_PC
		DWORD dwRV = RasSetEntryProperties(lpszPhoneBook, lpszEntry, &rasEntry, 
			sizeof(rasEntry), NULL, 0);
#else
		DWORD dwRV = RasSetEntryProperties(lpszPhoneBook, lpszEntry, (BYTE *)&rasEntry, 
			sizeof(rasEntry), NULL, 0);
#endif
		return dwRV;
	}
	return ERROR_ALREADY_EXISTS;
}

/***********************************************************************************
*	SetEntryOption
***********************************************************************************/
DWORD CRasDial::HlpSetEntryOption(CString strEntry, DWORD dwfOptions, 
			   BOOL bSet, CString strPhoneBook /*=_T("")*/)
{
	LPTSTR lpszEntry = strEntry.GetBuffer(1);
	strEntry.ReleaseBuffer();
	LPTSTR lpszPhoneBook = strPhoneBook.GetBuffer(1);
	if(strPhoneBook == _T(""))
		lpszPhoneBook = NULL;
	strPhoneBook.ReleaseBuffer();
	RASENTRY entry;
	DWORD dwRV = HlpGetEntryProperties(strEntry, &entry, lpszPhoneBook);
	if(dwRV == 0)
	{
		if(bSet)
			entry.dwfOptions |= dwfOptions; 
		else
			entry.dwfOptions &= ~dwfOptions;
#ifdef AUTO_PC
		dwRV = RasSetEntryProperties(lpszPhoneBook, lpszEntry, &entry, 
			sizeof(entry), NULL, 0);
#else
		dwRV = RasSetEntryProperties(lpszPhoneBook, lpszEntry, (BYTE *)&entry, 
			sizeof(entry), NULL, 0);
#endif

	}
	return dwRV;
}
/***********************************************************************************
*	GetEntryProperties
***********************************************************************************/
DWORD CRasDial::HlpGetEntryProperties(CString strEntry, RASENTRY* lpRasEntry
				, LPTSTR lpszPhoneBook)
{
	LPTSTR lpszEntry = strEntry.GetBuffer(1);
	strEntry.ReleaseBuffer();
	if(RasValidateEntryName(lpszPhoneBook, lpszEntry) == ERROR_ALREADY_EXISTS)
	{
		BYTE bDeviceInfo = NULL;
		DWORD dwDeviceInfoSize = sizeof(bDeviceInfo);
		DWORD dwEntrySize = 0;
		DWORD dwRV;
		lpRasEntry->dwSize = sizeof(*lpRasEntry);
#ifdef AUTO_PC
		dwRV = RasGetEntryProperties(lpszPhoneBook, lpszEntry, lpRasEntry, &dwEntrySize, 
			&bDeviceInfo, &dwDeviceInfoSize);   // GET 603
		dwRV = RasGetEntryProperties(lpszPhoneBook, lpszEntry, lpRasEntry, &dwEntrySize, 
			&bDeviceInfo, &dwDeviceInfoSize);   // GET 0
#else
		dwRV = RasGetEntryProperties(lpszPhoneBook, lpszEntry, (BYTE*)lpRasEntry, &dwEntrySize, 
			&bDeviceInfo, &dwDeviceInfoSize);   // GET 603
		dwRV = RasGetEntryProperties(lpszPhoneBook, lpszEntry, (BYTE*)lpRasEntry, &dwEntrySize, 
			&bDeviceInfo, &dwDeviceInfoSize);   // GET 0
#endif
	    return dwRV;
	}
	else
		return ERROR_ENTRY_NO_FOUND;
}

