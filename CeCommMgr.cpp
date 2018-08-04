// CeCommMgr.cpp : CCeCommMgr クラスプログラム
//
#include "stdafx.h"
#include "CeCommMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CeCommMgr

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////


char g_cReceiveBuf[COMM_RECEIVE_BUF_SIZE];		//受信ﾊﾞﾌｧ
int g_nBufReadSize;			//読込完了サイズ
BOOL	g_bReceiveDesable;
int g_nReceiveBufPos;

CCeCommMgr::CCeCommMgr(CWnd *pWnd)
{
	m_pWnd = pWnd;
//	bReceiveEnable		= TRUE;
	g_nReceiveBufPos	= 0;
	g_bReceiveDesable	= FALSE;			//受信禁止解除


	InitCommon();
}

CCeCommMgr::~CCeCommMgr()
{
	CloseComm();

	::DeleteCriticalSection(&m_cs);
}

BOOL CCeCommMgr::OpenComm(LPCTSTR lpszPort)
{
	CloseComm();

	HANDLE hcomm = ::CreateFile(
		lpszPort,GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

	if (hcomm == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	m_hcomm = hcomm;

	return TRUE;
}

VOID CCeCommMgr::CloseComm()
{
	StopComm();

	if (IsOpenComm())
	{
		::CloseHandle(m_hcomm);
		m_hcomm = INVALID_HANDLE_VALUE;
	}
	Sleep(SLEEP_232C_CLOSE);
}

BOOL CCeCommMgr::SetCommState(DWORD BaudRate, BYTE Parity, BYTE StopBits)
{
	if (!IsOpenComm())
	{
		return FALSE;
	}

	m_BaudRate	= BaudRate;
	m_Parity	= Parity;
	m_StopBits	= StopBits;

	COMMTIMEOUTS cto;

	cto.ReadIntervalTimeout         = 50;
	cto.ReadTotalTimeoutMultiplier  = 0;
	cto.ReadTotalTimeoutConstant    = 0;
	cto.WriteTotalTimeoutMultiplier = 0;
	cto.WriteTotalTimeoutConstant   = 0;

	::SetCommTimeouts(m_hcomm, &cto);
	
	DCB dcb;

	::GetCommState(m_hcomm, &dcb);

	dcb.BaudRate	= m_BaudRate;	// CBR_xxxx;
	dcb.Parity		= m_Parity;		// NOPARITY;
	dcb.StopBits	= m_StopBits;	// ONESTOPBIT;

	dcb.fBinary			= 1;
	dcb.fErrorChar		= 0;
	dcb.fNull			= 0;
	dcb.fOutxCtsFlow	= 1;
	dcb.fRtsControl		= 1;
	dcb.fOutX			= 0;
	dcb.fInX			= 0;

	return ::SetCommState(m_hcomm, &dcb);

}

BOOL CCeCommMgr::StartComm()
{
	if (!IsOpenComm())
	{
		return FALSE;
	}

	StopComm();

	if(SetCommState (m_BaudRate, m_Parity, m_StopBits) == FALSE)return FALSE;

	{
		HANDLE hstop = ::CreateEvent (0, 0, 0, 0);

		if (hstop == 0)
		{
			CloseReadCommProcRelatedHandles ();
			return FALSE;
		}

		m_hstop = hstop;
	}

	{
		DWORD ThreadID = 0;

		HANDLE hproc = ::CreateThread(
			0, 0, CCeCommMgr::ReadCommProc, LPVOID(this), 0, &ThreadID);

		if (hproc == 0)
		{
			CloseReadCommProcRelatedHandles ();
			return FALSE;
		}

		m_hproc = hproc;
	}

	g_nBufReadSize=0;			//読込完了サイズ初期化
	return TRUE;
}

void CCeCommMgr::StopComm()
{
	if (!m_hproc)
	{
		CloseReadCommProcRelatedHandles();
		return;
	}

	{
		DWORD dr = ::WaitForSingleObject (m_hproc, 0);

		switch (dr)
		{
		case WAIT_OBJECT_0:
			CloseReadCommProcRelatedHandles();
			return;

		case WAIT_TIMEOUT:
			// nothing to do, through.
			break;

		default:
			TRACE0("Fail to ::WaitForSingleObject().\n");
			ASSERT(0);
			CloseReadCommProcRelatedHandles();
			return;
		}
	}

	{
		::SetEvent (m_hstop);

		DWORD dr = ::WaitForSingleObject(m_hproc, 60 * 1000);

		switch (dr)
		{
		case WAIT_OBJECT_0:
			CloseReadCommProcRelatedHandles();
			return;

		case WAIT_TIMEOUT:
		default:
			TRACE0("Fail to ::WaitForSingleObject().\n");
			ASSERT(0);
			CloseReadCommProcRelatedHandles();
			return;
		}
	}
}

BOOL CCeCommMgr::WriteComm(LPVOID pvBuffer, DWORD dwNumberOfBytesToWrite)
{
	::EnterCriticalSection(&m_cs);
	DWORD dwNuberOfBytesWrote;		//書き込んだサイズ

	BOOL br = ::WriteFile(
		m_hcomm, pvBuffer, dwNumberOfBytesToWrite, &dwNuberOfBytesWrote, 0);

	::LeaveCriticalSection(&m_cs);

	return br;
}

/*VOID CCeCommMgr::OnRecieve(HLOCAL* phmem, DWORD dwNumberOfBytesRead)
{
	for(;;){
		if(bReceiveEnable == TRUE)break;
		Sleep(1);
	}

	if(m_nReceiveBufPos + dwNumberOfBytesRead  >= 1000){	//捨ててもいいからあんまりためない
		m_nReceiveBufPos=0;
	}

	memcpy(&m_cpReceiveBuf[m_nReceiveBufPos],LPSTR(*phmem),dwNumberOfBytesRead);
	m_nReceiveBufPos+= dwNumberOfBytesRead;



}
*/
DWORD WINAPI CCeCommMgr::ReadCommProc(LPVOID pParam)
{
	CCeCommMgr* p = (CCeCommMgr*)pParam;

	bool loop = true;

	while (loop)
	{
		{
			DWORD dr = ::WaitForSingleObject (p->m_hstop, 0);
	
			switch (dr)
			{
			case WAIT_OBJECT_0:
				loop = false;
				continue;

			case WAIT_TIMEOUT:
				// nothing to do, through.
				break;

			default:
				TRACE0("Fail to ::WaitForSingleObject().\n");
				ASSERT(0);
				loop = false;
				continue;
			}
		}

		::Sleep (1);

		{
			HANDLE hcomm = p->m_hcomm;

			DWORD	er = 0;
			COMSTAT	cs;

			::ClearCommError (hcomm, &er, &cs);

			DWORD NumberOfBytesToRead = cs.cbInQue;
			DWORD NumberOfBytesRead;
			if (NumberOfBytesToRead > 0){
				if(g_bReceiveDesable == FALSE){			//受信禁止解除中
					if(g_nBufReadSize >= 1000){			//あんまりためない
						g_nBufReadSize=0;
					}
					::ReadFile(hcomm, &g_cReceiveBuf[g_nBufReadSize],NumberOfBytesToRead, &NumberOfBytesRead, NULL) ;
					g_nBufReadSize+=NumberOfBytesRead;
				}
//				HLOCAL hmem = ::LocalAlloc (0, NumberOfBytesToRead + 1);
//				if (hmem)
//				{
//					::EnterCriticalSection(&p->m_cs);
//					DWORD NumberOfBytesRead = 0;
//					::ReadFile(hcomm, hmem, NumberOfBytesToRead, &NumberOfBytesRead, 0);
//					((LPBYTE)hmem) [NumberOfBytesRead] = 0;
//					::LeaveCriticalSection(&p->m_cs);
//					p->OnRecieve (&hmem, NumberOfBytesRead);
//					if (hmem)
//					{
//						::LocalFree (hmem);
//					}
//				}
			}
		}

	}
	return(GetCurrentThreadId());
}

/*********************************************************
*	受信ﾃﾞｰﾀ獲得
*********************************************************/
int CCeCommMgr::GetRecieveData(char *cpBuf)
{
	if(g_nBufReadSize == 0)return 0;
	if(g_nBufReadSize >= COM_RECEIVE_BUF_SIZE)g_nBufReadSize = 0;


	g_bReceiveDesable = TRUE;			//受信禁止
	int nSize = g_nBufReadSize;
	memcpy(cpBuf,g_cReceiveBuf,nSize);
	g_nBufReadSize = 0; //ｸﾘｱ
	g_bReceiveDesable = FALSE;			//受信禁止解除

	return nSize;
}
