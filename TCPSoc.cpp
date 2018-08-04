/*************************************************************************************************
*	TCP���đ���M
**************************************************************************************************/
#include "stdafx.h"
#include "TCPSoc.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/*************************************************************************************************
*	�ݽ�׸�
*	 nIndex  :1..
*	pTraceBuf:msg�\���p�ڰ��ޯ̧�ւ��߲��
**************************************************************************************************/
CTCPSoc::CTCPSoc(CWnd * pWnd,int nIndex/*=1*/,char *pTraceBuf/*=NULL*/,BOOL bSrvr/*=FALSE*/)
{
	m_pWnd			= pWnd;
	m_nIndex		= nIndex;
	m_pTraceBuf		= pTraceBuf;
	m_nMode			= 0;			// 0:Connect-Send-Receive 1:SendTo-ReceiveFrom
	m_bSrvr			= bSrvr;		//default:�ײ���
	m_nTermCnt		= 0;			//���ނ��\�z����ײ��č\�z��
	HlpTRACE("Ver1.00",3);
}
/*************************************************************************************************
*	�޽�׸�
**************************************************************************************************/
CTCPSoc::~CTCPSoc()
{
}
// ClassWizard ���K�v�Ƃ���ȉ��̍s��ҏW���Ȃ��ł��������B
#if 0
BEGIN_MESSAGE_MAP(CTCPSoc, CAsyncSocket)
	//{{AFX_MSG_MAP(CTCPSoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/*************************************************************************************************
*	�\�P�b�g���쐬���܂��B
* nSocketPort:�\�P�b�g�Ŏg�����m�̃|�[�g�BWindows �\�P�b�g�Ƀ|�[�g��I��������Ƃ��� 0 ���w�肵�܂��B
**************************************************************************************************/
BOOL CTCPSoc::Create(UINT nSocketPort)
{
	CString str;
	str.Format(_T("Create[port:%d]"),nSocketPort);
	HlpTRACE(str,3);

//	if(CAsyncSocket::Create(nSocketPort,SOCK_DGRAM) == 0){
	if(CAsyncSocket::Create(nSocketPort,SOCK_STREAM,FD_READ|FD_WRITE|FD_OOB|FD_ACCEPT|FD_CONNECT|FD_CLOSE) == 0){
//	if(CCeSocket::Create(nSocketPort) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEADDRINUSE:		str = "�w�肵���A�h���X�͎g�p���ł��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g���삪�u���b�L���O����Ă��܂��B";break;
			case WSAEADDRNOTAVAIL:	str = "�w�肵���A�h���X�́A���[�J�� �}�V������͗��p�ł��܂���B";break;
			case WSAEAFNOSUPPORT:	str = "�w�肵���A�h���X �t�@�~���́A���̃\�P�b�g�ł̓T�|�[�g���Ă��܂���B";break;
			case WSAECONNREFUSED:	str = "�ڑ������݂܂������A���W�F�N�g����܂����B";break;
			case WSAEDESTADDRREQ:	str = "����A�h���X���K�v�ł��B";break;
			case WSAEFAULT:			str = "���� nSockAddrLen ���s���ł��B";break;
			case WSAEINVAL:			str = "�\�P�b�g�͂܂��A�h���X�Ƀo�C���h����Ă��܂���B";break;
			case WSAEISCONN:		str = "�\�P�b�g�͊��ɐڑ�����Ă��܂��B";break;
			case WSAEMFILE:			str = "���p�ł���t�@�C�� �f�B�X�N���v�^������܂���B";break;
			case WSAENETUNREACH:	str = "�����_�ŁA�z�X�g����l�b�g���[�N�ɓ��B�ł��܂���B";break;
			case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B�\�P�b�g�͐ڑ��ł��܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAETIMEDOUT:		str = "�ڑ������݂܂������A�^�C���A�E�g�Őڑ����m���ł��܂���ł����B";break;
			case WSAEWOULDBLOCK:	str = "�\�P�b�g����u���b�L���O�ɂȂ��Ă��āA�ڑ��������ł��܂���B ";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("Create() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�s�A �\�P�b�g�Ƃ̐ڑ����m�����܂��B
*  lpszHostAddress: �I�u�W�F�N�g��ڑ�����\�P�b�g�̃l�b�g���[�N �A�h���X�B 
*                   "ftp.microsoft.com" �̂悤�ȃ}�V�����A�܂��� "128.56.22.8" �̂悤�Ƀh�b�g�ŋ�؂�ꂽ�������w�肵�܂��B
*  nHostPort      : �\�P�b�g �A�v���P�[�V���������ʂ���|�[�g�B
**************************************************************************************************/
BOOL CTCPSoc::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	CString str;
	str.Format(_T("Connect[adr:%s port:%d]"),lpszHostAddress,nHostPort);
	HlpTRACE(str,3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	m_strHostAdr	= lpszHostAddress;
	m_nHostPort		= nHostPort;

	if(m_nMode == 1){		//SendTo ReceiveFrom���g�p
		return TRUE;
	}
//-----------------------------------
	int nVal = 0;

	if(CAsyncSocket::Connect(lpszHostAddress,nHostPort) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEADDRINUSE:		str = "�w�肵���A�h���X�͎g�p���ł��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g���삪�u���b�L���O����Ă��܂��B";break;
			case WSAEADDRNOTAVAIL:	str = "�w�肵���A�h���X�́A���[�J�� �}�V������͗��p�ł��܂���B";break;
			case WSAEAFNOSUPPORT:	str = "�w�肵���A�h���X �t�@�~���́A���̃\�P�b�g�ł̓T�|�[�g���Ă��܂���B";break;
			case WSAECONNREFUSED:	str = "�ڑ������݂܂������A���W�F�N�g����܂����B";break;
			case WSAEDESTADDRREQ:	str = "����A�h���X���K�v�ł��B";break;
			case WSAEFAULT:			str = "���� nSockAddrLen ���s���ł��B";break;
			case WSAEINVAL:			str = "�\�P�b�g�͂܂��A�h���X�Ƀo�C���h����Ă��܂���B";break;
			case WSAEISCONN:		str = "�\�P�b�g�͊��ɐڑ�����Ă��܂��B";break;
			case WSAEMFILE:			str = "���p�ł���t�@�C�� �f�B�X�N���v�^������܂���B";break;
			case WSAENETUNREACH:	str = "�����_�ŁA�z�X�g����l�b�g���[�N�ɓ��B�ł��܂���B";break;
			case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B�\�P�b�g�͐ڑ��ł��܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAETIMEDOUT:		str = "�ڑ������݂܂������A�^�C���A�E�g�Őڑ����m���ł��܂���ł����B";break;
//			case WSAEWOULDBLOCK:	str = "�\�P�b�g����u���b�L���O�ɂȂ��Ă��āA�ڑ��������ł��܂���B ";break;
			case WSAEWOULDBLOCK:	return TRUE;//OnConnect()����ޯ����g�p���Ă���̂�OK
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("Connect() "+str,ERR);
*/
		return FALSE;
	}
	CAsyncSocket::GetSockName(LocalIP, LocalPort);
	return TRUE;
}
/*************************************************************************************************
*	�ڑ��v����҂��܂��B
**************************************************************************************************/
BOOL CTCPSoc::Listen()
{
	HlpTRACE("Listen",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	if(CAsyncSocket::Listen() == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEADDRINUSE:		str = "�g�p���̃A�h���X�ɑ΂��ă��X�i�ɂȂ�悤���݂܂����B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAEINVAL:			str = "�\�P�b�g�� Bind ���g���ăo�C���h����Ă��Ȃ����A���ɐڑ�����Ă��܂��B";break;
			case WSAEISCONN:		str = "�\�P�b�g�͊��ɐڑ�����Ă��܂��B";break;
			case WSAEMFILE:			str = "���p�ł���t�@�C�� �f�B�X�N���v�^������܂���B";break;
			case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAEOPNOTSUPP:		str = "�Q�Ƃ����\�P�b�g�̌^�́AListen ������T�|�[�g���Ă��܂���B";break;
			default:str = "()�s���ȃG���[";break;
		}
		HlpTRACE("Listen() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�\�P�b�g�����[�J�� �A�h���X�Ɍ��ѕt���܂��B
**************************************************************************************************/
BOOL CTCPSoc::Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress/*=NULL*/)
{
	HlpTRACE("Bind",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	if(CAsyncSocket::Bind(nSocketPort,lpszSocketAddress) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows�\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEADDRINUSE:		str = "�w�肵���A�h���X�͎g�p���ł��BSetSockOpt �̃\�P�b�g �I�v�V���� SO_REUSEADDR ���Q�Ƃ��Ă��������B";break;
			case WSAEFAULT:			str = "���� nSockAddrLen �����������܂��BSOCKADDR �\���̂̃T�C�Y�����������Ȃ��Ă��܂��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g���삪�u���b�L���O����Ă��܂��B";break;
			case WSAEAFNOSUPPORT:	str = "�w�肵���A�h���X �t�@�~���́A���̃|�[�g�ł̓T�|�[�g���Ă��܂���B";break;
			case WSAEINVAL:			str = "�\�P�b�g�͊��ɃA�h���X�Ƀo�C���h����Ă��܂��B";break;
			case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B�ڑ����������܂��B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("Bind() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�\�P�b�g��̐ڑ����󂯓���܂��B
**************************************************************************************************/
BOOL CTCPSoc::Accept(CAsyncSocket& rConnectedSocket)
{
//	HlpTRACE("Accept",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	SOCKADDR SockAddr;
	int nLen = sizeof(SOCKADDR);
	if(CAsyncSocket::Accept(rConnectedSocket,&SockAddr,&nLen) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEFAULT:			str = "���� lpSockAddrLen �����������܂��BSOCKADDR �\���̂̃T�C�Y�����������Ȃ��Ă��܂��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAEINVAL:			str = "�󂯓����O�� Listen ���Ăяo����Ă��܂���B";break;
			case WSAEMFILE:			str = "�󂯓����G���g����̃L���[����ŁA���p�ł���f�B�X�N���v�^������܂���B";break;
			case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAEOPNOTSUPP:		str = "�Q�Ƃ��Ă���\�P�b�g�́A�ڑ��w���̃T�[�r�X���T�|�[�g����^�C�v�ł͂���܂���B";break;
			case WSAEWOULDBLOCK:	str = "�\�P�b�g�͔�u���b�L���O�ɂȂ��Ă��āA�󂯓����ڑ�������܂���B";break; 
			default:str = "()�s���ȃG���[";break;
		}
		HlpTRACE("Accept() "+str,ERR);
*/
		return FALSE;
	}

	CString str;
	WORD wVal;
	memcpy(&wVal,SockAddr.sa_data,2);
	str.Format(_T("�ײ��ď�� ADR:%d.%d.%d.%d PORT:%d"),
		SockAddr.sa_data[2]*-1,SockAddr.sa_data[3],SockAddr.sa_data[4],SockAddr.sa_data[5],ntohs(wVal));
	HlpTRACE(str,3);
	return TRUE;
}
/*************************************************************************************************
*	�ڑ�����Ă���\�P�b�g�Ƀf�[�^�𑗐M���܂��B
*	lpBuf  : �]������f�[�^��ێ�����o�b�t�@�B
*	nBufLen: lpBuf ���̃o�C�g�P�ʂ̃f�[�^���B
**************************************************************************************************/
BOOL CTCPSoc::Send(const void * lpBuf, int nBufLen)
{
	if(m_bSrvr == TRUE){
		return(m_pTerm->Send(lpBuf,nBufLen));
	}

	HlpTRACE("Send",3);
//-------------------------------------------------------------------------------------------
	if(m_nMode == 1){		//SendTo ReceiveFrom���g�p
		return SendTo(lpBuf,nBufLen,m_nHostPort,m_strHostAdr); 
	}

//	if(CCeSocket::Send(lpBuf,nBufLen) == SOCKET_ERROR){	//�ڑ�����Ă���\�P�b�g�Ƀf�[�^�𑗐M���܂��B
	if(CAsyncSocket::Send(lpBuf,nBufLen) == SOCKET_ERROR){	//�ڑ�����Ă���\�P�b�g�Ƀf�[�^�𑗐M���܂��B
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEACCES:			str = "�v�������A�h���X�̓u���[�h�L���X�g �A�h���X�ł����A�K�؂ȃt���O���ݒ肳��Ă��܂���ł����B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAEFAULT:			str = "���� lpBuf �����[�U�[ �A�h���X��Ԃ̗L���ȕ������w���Ă��܂���B";break;
			case WSAENETRESET:		str = "Windows �\�P�b�g�̃C���v�������g���\�P�b�g���h���b�v�����̂ŁA�ڑ������Z�b�g����K�v������܂��B";break;
			case WSAENOBUFS:		str = "Windows �\�P�b�g�̃C���v�������g���A�o�b�t�@�̃f�b�h���b�N�����|�[�g�Ă��܂��B";break;
			case WSAENOTCONN:		str = "�\�P�b�g���ڑ�����Ă��܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB ���w�肳��܂������ASOCK_STREAM �^�̃\�P�b�g�ł͂���܂���B";break;
			case WSAESHUTDOWN:		str = "�\�P�b�g�̓V���b�g �_�E������Ă��܂��BnHow �� 0 �܂��� 2 ���w�肵�� ShutDown ���N��������ł́A�\�P�b�g�� Send ���Ăяo�����Ƃ͂ł��܂���B";break;
			case WSAEWOULDBLOCK:	str = "�\�P�b�g�͔�u���b�L���O�ɂȂ��Ă��āA�v���������삪�u���b�N����܂����B";break;
			case WSAEMSGSIZE:		str = "�\�P�b�g�� SOCK_DGRAM �^�ŁAWindows �\�P�b�g�̃C���v�������g���T�|�[�g����ő咷�����f�[�^�O�������������܂��B";break;
			case WSAEINVAL:			str = "�\�P�b�g�� Bind ���g���ăo�C���h����Ă��܂���B";break;
			case WSAECONNABORTED:	str = "�^�C���A�E�g�܂��͂��̑��̏�Q�ɂ��A���z��H�̓A�{�[�g����܂����B";break;
			case WSAECONNRESET:		str = "�����[�g�����牼�z��H�����Z�b�g����܂����B ";break;
			default:str = "()�s���ȃG���[";break;
		}
		HlpTRACE("Send() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�ڑ�����Ă���\�P�b�g�Ƀf�[�^�𑗐M���܂��B
*	lpBuf  : �]������f�[�^��ێ�����o�b�t�@�B
*	nBufLen: lpBuf ���̃o�C�g�P�ʂ̃f�[�^���B
**************************************************************************************************/
BOOL CTCPSoc::SendTo(const void * lpBuf, int nBufLen,
					UINT nHostPort, LPCTSTR lpszHostAddress /*= NULL*/, int nFlags /*= 0*/) 
{
	HlpTRACE("SendTo",3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	int nLen;
	if((nLen = CAsyncSocket::SendTo(lpBuf,nBufLen,nHostPort,lpszHostAddress)) == SOCKET_ERROR){	//�ڑ�����Ă���\�P�b�g�Ƀf�[�^�𑗐M���܂��B
/*
		int nErr = CAsyncSocket::GetLastError();
		switch(nErr){
			case WSANOTINITIALISED:		str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN: 			str = "Windows�\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEACCES:				str = "�v�������A�h���X�̓u���[�h�L���X�g �A�h���X�ł����A�K�؂ȃt���O���ݒ肳��Ă��܂���ł����B";break;
			case WSAEINPROGRESS:		str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAEFAULT:				str = "���� lpBuf �܂��� lpSockAddr �����[�U�[ �A�h���X��Ԃ̗L���ȕ������w���Ă��܂���B�܂��́A���� lpSockAddr ���������܂��BSOCKADDR �\���̂̃T�C�Y��菬�����Ȃ��Ă��܂��B";break;
			case WSAENETRESET:			str = "Windows �\�P�b�g�̃C���v�������g���\�P�b�g���h���b�v�����̂ŁA�ڑ������Z�b�g����K�v������܂��B";break;
			case WSAENOBUFS:			str = "Windows �\�P�b�g�̃C���v�������g���A�o�b�t�@�̃f�b�h���b�N�����|�[�g�Ă��܂��B";break;
			case WSAENOTCONN:			str = "�\�P�b�g���ڑ�����Ă��܂��� (SOCK_STREAM �^�̂�)�B";break;
			case WSAENOTSOCK:			str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
			case WSAEOPNOTSUPP:			str = "MSG_OOB ���w�肳��܂������ASOCK_STREAM �^�̃\�P�b�g�ł͂���܂���B";break;
			case WSAESHUTDOWN:			str = "�\�P�b�g�̓V���b�g �_�E������Ă��܂��BnHow �� 0 �܂��� 2 ���w�肵�� ShutDown ���N��������ł́A�\�P�b�g�� SendTo ���Ăяo�����Ƃ͂ł��܂���B";break;
			case WSAEWOULDBLOCK:		str = "�\�P�b�g�͔�u���b�L���O�ɂȂ��Ă��āA�v���������삪�u���b�N����܂����B";break;
			case WSAEMSGSIZE:			str = "�\�P�b�g�� SOCK_DGRAM �^�ŁAWindows �\�P�b�g�̃C���v�������g���T�|�[�g����ő咷�����f�[�^�O�������������܂��B";break;
			case WSAEINVAL:				str = "�\�P�b�g�� Bind ���g���ăo�C���h����Ă��܂���B";break;
			case WSAECONNABORTED:		str = "�^�C���A�E�g�܂��͂��̑��̏�Q�ɂ��A���z��H�̓A�{�[�g����܂����B";break;
			case WSAECONNRESET:			str = "�����[�g�����牼�z��H�����Z�b�g����܂����B";break;
			case WSAEADDRNOTAVAIL:		str = "�w�肵���A�h���X�̓��[�J�� �}�V������͗��p�ł��܂���B";break;
			case WSAEAFNOSUPPORT:		str = "�w�肵���t�@�~���̃A�h���X�͂��̃\�P�b�g�ł͎g�p�ł��܂���B";break;
			case WSAEDESTADDRREQ:		str = "����A�h���X���K�v�ł��B";break;
			case WSAENETUNREACH:		str = "�����_�ł́A�z�X�g����l�b�g���[�N�ɓ��B�ł��܂���B ";break;
			case WSAEISCONN:			str = "Socket is already connected. A connect request was made on an already connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket ";
										str += "(For SOCK_STREAM sockets, the to parameter in sendto is ignored), although other implementations treat this as a legal occurrence.  ";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("SendTo() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�\�P�b�g����f�[�^����M���܂��B�i�ʏ�OnReceive����Ăяo����܂��j
*	lpBuf  : ��M�f�[�^ �o�b�t�@�B
*	nBufLen: lpBuf �̒����B�o�C�g�P�ʂł��B
**************************************************************************************************/
int CTCPSoc::Receive(void * lpBuf, int nBufLen,int nFlags/*=0*/)
{
//-------------------------------------------------------------------------------------------
	if(m_nMode == 1){		//SendTo ReceiveFrom���g�p
		CString rSocketAddress;
		UINT rSocketPort;
		return ReceiveFrom(lpBuf,nBufLen,rSocketAddress,rSocketPort,nFlags);
	}

	int len;
	len = CAsyncSocket::Receive(lpBuf,nBufLen,nFlags);
	if(len == SOCKET_ERROR){
/*
		int err = CAsyncSocket::GetLastError();
		switch(err){
			case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B ";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B ";break;
			case WSAENOTCONN:		str = "�\�P�b�g���ڑ�����Ă��܂���B ";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B ";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B ";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB ���w�肳��܂������ASOCK_STREAM �^�̃\�P�b�g�ł͂���܂���B ";break;
			case WSAESHUTDOWN:		str = "�\�P�b�g�̓V���b�g �_�E������܂����BnHow �� 0 �܂��� 2 ��n���� ShutDown ���N��������ł́A�\�P�b�g�� Receive ���Ăяo�����Ƃ͂ł��܂���B ";break;
			case WSAEWOULDBLOCK:	str = "�\�P�b�g�͔�u���b�L���O�ɂȂ��Ă��āAReceive ���삪�u���b�N����܂����B ";break;
			case WSAEMSGSIZE:		str = "�f�[�^�O�������������āA�w�肵���o�b�t�@�ɓ��肫��Ȃ����߁A�؂�l�߂��܂����B ";break;
			case WSAEINVAL:			str = "�\�P�b�g�� Bind ���g���ăo�C���h����Ă��܂���B ";break;
			case WSAECONNABORTED:	str = "�^�C���A�E�g�܂��͂��̑��̏�Q�ɂ��A���z��H�̓A�{�[�g����܂����B ";break;
			case WSAECONNRESET:		str = "�����[�g�����牼�z��H�����Z�b�g����܂����B  ";break;
			case WSAEFAULT:			str = "�s�ǂȃA�h���X�ł��B";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("Receive() "+str,ERR);
		str.Format("ECode:%d",err);
		HlpTRACE(str,ERR);
*/
		return 0;
	}
	return len;
}
/*************************************************************************************************
*	�\�P�b�g����f�[�^����M���܂��B
*	lpBuf  : ��M�f�[�^ �o�b�t�@�B
*	nBufLen: lpBuf �̒����B�o�C�g�P�ʂł��B
**************************************************************************************************/
int CTCPSoc::ReceiveFrom(void * lpBuf, int nBufLen,
						 CString& rSocketAddress, UINT& rSocketPort, int nFlags /*= 0*/)
{
	HlpTRACE("ReceiveFrom",3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	int len;
	len = CAsyncSocket::ReceiveFrom(lpBuf,nBufLen,rSocketAddress,rSocketPort,nFlags);
	if(len == SOCKET_ERROR){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B ";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B ";break;
			case WSAEFAULT:			str = "���� lpSockAddrLen ���s���ł��B�s�A �A�h���X���i�[����ɂ́AlpSockAddr �o�b�t�@�����������܂��B ";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B ";break;
			case WSAEINVAL:			str = "�\�P�b�g�� Bind ���g���ăo�C���h����Ă��܂���B ";break;
			case WSAENOTCONN:		str = "�\�P�b�g�͐ڑ�����Ă��܂��� (SOCK_STREAM �^�̂�)�B ";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B ";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB ���w�肳��܂������ASOCK_STREAM �^�̃\�P�b�g�ł͂���܂���B ";break;
			case WSAESHUTDOWN:		str = "�\�P�b�g�̓V���b�g �_�E������Ă��܂��BnHow �� 0 �܂��� 2 ���w�肵�� ShutDown ���N��������ł́A�\�P�b�g�� ReceiveFrom ���Ăяo�����Ƃ͂ł��܂���B ";break;
			case WSAEWOULDBLOCK:	str = "�\�P�b�g�͔�u���b�L���O�ɂȂ��Ă��āAReceiveFrom ���삪�u���b�N����܂����B ";break;
			case WSAEMSGSIZE:		str = "�f�[�^�O�������������āA�w�肵���o�b�t�@�ɓ��肫��Ȃ����߁A�؂�l�߂��܂����B ";break;
			case WSAECONNABORTED:	str = "�^�C���A�E�g�܂��͂��̑��̏�Q�ɂ��A���z��H�̓A�{�[�g����܂����B ";break;
			case WSAECONNRESET:		str = "�����[�g�����牼�z��H�����Z�b�g����܂����B  ";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("ReceiveFrom() "+str,ERR);
*/
		return 0;
	}
	return len;
}
/*************************************************************************************************
*	�\�P�b�g�I�v�V�������l�����܂��B
**************************************************************************************************/
BOOL CTCPSoc::GetSockOpt(int nOptionName,DWORD *dwpBuf)
{
	HlpTRACE("GetSockOpt",3);

	int nBufSize=4;
	if(CAsyncSocket::GetSockOpt(nOptionName,dwpBuf,&nBufSize) == FALSE){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEFAULT:			str = "���� lpOptionLen ���s���ł��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAENOPROTOOPT:	str = "�I�v�V�������s�����T�|�[�g����Ă��܂���B���� SO_BROADCAST �� SOCK_STREAM �^�̃\�P�b�g�ł̓T�|�[�g����Ă��܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B ";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("GetSockOpt() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�\�P�b�g�I�v�V������ݒ肵�܂��B
**************************************************************************************************/
BOOL CTCPSoc::SetSockOpt(int nOptionName,DWORD *dwpBuf)
{
	HlpTRACE("SetSockOpt",3);

	int nBufSize=4;
	if(CAsyncSocket::SetSockOpt(nOptionName,dwpBuf,nBufSize) == FALSE){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
			case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
			case WSAEFAULT:			str = "���� lpOptionLen ���s���ł��B";break;
			case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g�Ăяo�����u���b�L���O����Ă��܂��B";break;
			case WSAENOPROTOOPT:	str = "�I�v�V�������s�����T�|�[�g����Ă��܂���B���� SO_BROADCAST �� SOCK_STREAM �^�̃\�P�b�g�ł̓T�|�[�g����Ă��܂���B";break;
			case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B ";break;
			default:str = "�s���ȃG���[";break;
		}
		HlpTRACE("SetSockOpt() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	�N���[�Y
**************************************************************************************************/
void CTCPSoc::Close()
{
//-------------------------------------------------------------------------------
	CAsyncSocket::Close();
}
/*************************************************************************************************
*	��M�f�[�^���o�b�t�@�ɂ��邱�Ƃ��\�P�b�g�ɒʒm���邽�߂ɁA�t���[�����[�N���Ăяo���܂��B
**************************************************************************************************/
void CTCPSoc::OnReceive(int nErrorCode) 
{
//	HlpTRACE("OnReceive",3);
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_RECEIVE_NOTIF, m_nIndex);
//-------------------------------------------------------------------------------
	CAsyncSocket::OnReceive(nErrorCode);
//	CCeSocket::OnReceive(nErrorCode);
}
/*************************************************************************************************
*	���M�f�[�^�\�ȏꍇ�ɁA�t���[�����[�N���Ăяo���܂��B
**************************************************************************************************/
void CTCPSoc::OnSend(int nErrorCode) 
{
//	HlpTRACE("OnSend",3);
//	m_pWnd->PostMessage(WM_EVENT,EV_SEND_NOTIFI, m_nIndex);
//-------------------------------------------------------------------------------
	CAsyncSocket::OnSend(nErrorCode);
//	CCeSocket::OnSend(nErrorCode);
}
/**********************************************************************************************
*  �ڑ��v������
***********************************************************************************************/
void CTCPSoc::OnAccept(int nErrorCode) 
{
	m_pWnd->PostMessage(WM_EVENT,EV_ACCEPT_NOTIFI, m_nIndex);
//-------------------------------------------------------------------------------
	CAsyncSocket::OnAccept(nErrorCode);
}
/**********************************************************************************************
*  �ڑ�����
***********************************************************************************************/
void CTCPSoc::OnConnect(int nErrorCode) 
{
	CString str;

	HlpTRACE("OnConnect",3);
	if(HlpChkSrvr(FALSE) == FALSE)goto TAG_EXIT;		//����/�ײ��Đ��䌟��
//-------------------------------------------------------------------------------------------
	switch(nErrorCode){
		case 0:	goto TAG_EXIT;
		case WSANOTINITIALISED:	str = "���� API ���g���O�� AfxSocketInit �̌Ăяo��������I�����Ă��邱�Ƃ��K�v�ł��B";break;
		case WSAENETDOWN:		str = "Windows �\�P�b�g�̃C���v�������g���A�l�b�g���[�N �T�u�V�X�e���ُ̈�����o���܂����B";break;
		case WSAEADDRINUSE:		str = "�w�肵���A�h���X�͎g�p���ł��B";break;
		case WSAEINPROGRESS:	str = "���s���� Windows �\�P�b�g���삪�u���b�L���O����Ă��܂��B";break;
		case WSAEADDRNOTAVAIL:	str = "�w�肵���A�h���X�́A���[�J�� �}�V������͗��p�ł��܂���B";break;
		case WSAEAFNOSUPPORT:	str = "�w�肵���A�h���X �t�@�~���́A���̃\�P�b�g�ł̓T�|�[�g���Ă��܂���B";break;
		case WSAECONNREFUSED:	str = "�ڑ������݂܂������A���W�F�N�g����܂����B";break;
		case WSAEDESTADDRREQ:	str = "����A�h���X���K�v�ł��B";break;
		case WSAEFAULT:			str = "���� nSockAddrLen ���s���ł��B";break;
		case WSAEINVAL:			str = "�\�P�b�g�͂܂��A�h���X�Ƀo�C���h����Ă��܂���B";break;
		case WSAEISCONN:		str = "�\�P�b�g�͊��ɐڑ�����Ă��܂��B";break;
		case WSAEMFILE:			str = "���p�ł���t�@�C�� �f�B�X�N���v�^������܂���B";break;
		case WSAENETUNREACH:	str = "�����_�ŁA�z�X�g����l�b�g���[�N�ɓ��B�ł��܂���B";break;
		case WSAENOBUFS:		str = "���p�ł���o�b�t�@�̈悪����܂���B�\�P�b�g�͐ڑ��ł��܂���B";break;
		case WSAENOTSOCK:		str = "�f�B�X�N���v�^���\�P�b�g�ł͂���܂���B";break;
		case WSAETIMEDOUT:		str = "�ڑ������݂܂������A�^�C���A�E�g�Őڑ����m���ł��܂���ł����B";break;
		case WSAEWOULDBLOCK:	str = "�\�P�b�g����u���b�L���O�ɂȂ��Ă��āA�ڑ��������ł��܂���B ";break;
//		case WSAEWOULDBLOCK:	return TRUE;//OnConnect()����ޯ����g�p���Ă���̂�OK
		default:str = "()�s���ȃG���[";break;
	}
	HlpTRACE(str,2);
//-------------------------------------------------------------------------------------------
TAG_EXIT:
	DWORD dwParam;
	m_Tool.SetDwHighLow(&dwParam,m_nIndex,HIGH_WORD);			//��ʂɲ��ޯ��
	m_Tool.SetDwHighLow(&dwParam,nErrorCode,LOW_WORD);		//���ʂɴװ����
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_CONNECT_NOTIF, dwParam);	//���Đڑ��m��ʒm
//-------------------------------------------------------------------------------
	CAsyncSocket::OnConnect(nErrorCode);
//	CCeSocket::OnConnect(nErrorCode);
}
/**********************************************************************************************
*  �ؒf�v������
***********************************************************************************************/
void CTCPSoc::OnClose(int nErrorCode) 
{
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_CLOSE, m_nIndex);
//-------------------------------------------------------------------------------------------
//	CAsyncSocket::OnClose(nErrorCode);

//	if(nErrorCode != 0)AfxMessageBox("end err");
}
/**********************************************************************************************
*  �ш�O�ް�����
***********************************************************************************************/
void CTCPSoc::OnOutOfBandData(int nErrorCode) 
{
	HlpTRACE("OnOutOfBandData",3);
//-------------------------------------------------------------------------------------------
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}
/**********************************************************************************************
*	����/�ײ��Đ��䌟��
*	bSrvr:TRUE�ͻ��ގ��@FALSE�͸ײ��Ď�
*	return;TRUE��OK FALSE��NG
***********************************************************************************************/
BOOL CTCPSoc::HlpChkSrvr(BOOL bSrvr/*=TRUE*/)
{
	if(m_bSrvr == bSrvr)return TRUE;
	HlpTRACE("����/�ײ��Đ���ُ�",2);
	return FALSE;
}
/**********************************************************************************************
*  TRACE��MSG���M
***********************************************************************************************/
void CTCPSoc::HlpTRACE(CString str,int level /* =0 */)
{
	if(m_pTraceBuf == NULL)return;
	CString msg;

	if(m_bSrvr == TRUE)msg.Format(_T("[CTCPSoc(Srvr)]"));
	else               msg.Format(_T("[CTCPSoc(Term)]"));

	m_pTraceBuf = m_Tool.CStringToChar(str + msg);
	m_pWnd->SendMessage(WM_TRACE, level, 0);
}
