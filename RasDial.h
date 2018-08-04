// RasDial.h: interface for the CRasDial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RASDIAL_H__DCBF0CC6_434E_11D5_8611_0040CA1F5FB7__INCLUDED_)
#define AFX_RASDIAL_H__DCBF0CC6_434E_11D5_8611_0040CA1F5FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ras.h>
#include <raserror.h>

#define ERROR_ENTRY_NO_FOUND	(RASBASEEND + 2)

class CRasDial  
{
public:
	CRasDial();
	virtual ~CRasDial();

	int GetEntry();
	BOOL Connect(HANDLE hWnd,CString strEntryName);
	BOOL ChkConnected();
	BOOL NewEntry(CString strEntry,CString strPhoneNo,CString strUserName,CString strPassword);
	void Close();

private:
//------------------ïœêî-----------------------------------------------
	BOOL m_bASYNC;
	HRASCONN m_hRasConn;
//------------------∫›ƒ€∞Ÿ-----------------------------------------------
//------------------∏◊Ω-----------------------------------------------
//------------------ÕŸ ﬂä÷êî----------------------

	DWORD HlpCreateNewEntry(CString strEntry, 
		CString strDeviceType, 
		CString strDeviceName, 
		DWORD dwfNetProtocols, DWORD dwFrameProtocal, 
		CString strLocalPhone,
		CString strPhoneBook=_T(""));
	DWORD HlpSetEntryOption(CString strEntry, DWORD dwfOptions, 
			   BOOL bSet, CString strPhoneBook =_T(""));
	DWORD HlpGetEntryProperties(CString strEntry, RASENTRY* lpRasEntry
				, LPTSTR lpszPhoneBook);


};

#endif // !defined(AFX_RASDIAL_H__DCBF0CC6_434E_11D5_8611_0040CA1F5FB7__INCLUDED_)
