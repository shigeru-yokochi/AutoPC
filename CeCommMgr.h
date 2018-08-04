// CeCommMgr.h: CCeCommMgr クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CECOMMMGR_H_)
#define _CECOMMMGR_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "define.h"
#define COMM_RECEIVE_BUF_SIZE 2000

class CCeCommMgr
{
// constructor, destructor & copy support
public:
	CCeCommMgr(CWnd *pWnd);
	virtual ~CCeCommMgr();
//	BOOL bReceiveEnable;
	int GetRecieveData(char *cpBuf);

// attributes
private:
	HANDLE	m_hcomm;

	HANDLE	m_hproc;
	HANDLE	m_hstop;

	CRITICAL_SECTION m_cs;

	DWORD	m_BaudRate;
	BYTE	m_Parity;
	BYTE	m_StopBits;

	VOID InitCommon()
	{
		m_hcomm = INVALID_HANDLE_VALUE;

		m_hproc = 0;
		m_hstop = 0;

		::InitializeCriticalSection(&m_cs);

		m_BaudRate	= COM_SPEED;
		m_Parity	= NOPARITY;
		m_StopBits	= ONESTOPBIT;
	}

// implementation
protected:
	BOOL IsOpenComm()
	{
		return m_hcomm != INVALID_HANDLE_VALUE;
	}

	VOID CloseReadCommProcRelatedHandles()
	{
		if (m_hproc) ::CloseHandle (m_hproc);
		m_hproc = 0;

		if (m_hstop) ::CloseHandle (m_hstop);
		m_hstop = 0;
	}

	static DWORD WINAPI ReadCommProc(LPVOID pParam);

// operation
public:
	BOOL	OpenComm(LPCTSTR lpszPort);
	VOID	CloseComm();

	BOOL	SetCommState(DWORD BaudRate, BYTE Parity, BYTE StopBits);
//	BOOL	GetCommState();

	BOOL	StartComm();
	void	StopComm();

	BOOL	WriteComm(LPVOID pvBuffer, DWORD dwNumberOfBytesToWrite);
//	virtual VOID OnRecieve(HLOCAL* phmem, DWORD dwNumberOfBytesRead) = 0;
//	VOID OnRecieve(HLOCAL* phmem, DWORD dwNumberOfBytesRead);


private:
	CWnd *m_pWnd;
//	char *m_pReceiveBuf;
};

#endif // _CECOMMMGR_H_
