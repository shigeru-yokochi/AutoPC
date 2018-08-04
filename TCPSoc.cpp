/*************************************************************************************************
*	TCPｿｹｯﾄ送受信
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
*	ｺﾝｽﾄﾗｸﾀ
*	 nIndex  :1..
*	pTraceBuf:msg表示用ﾄﾚｰｽﾊﾞｯﾌｧへのﾎﾟｲﾝﾀ
**************************************************************************************************/
CTCPSoc::CTCPSoc(CWnd * pWnd,int nIndex/*=1*/,char *pTraceBuf/*=NULL*/,BOOL bSrvr/*=FALSE*/)
{
	m_pWnd			= pWnd;
	m_nIndex		= nIndex;
	m_pTraceBuf		= pTraceBuf;
	m_nMode			= 0;			// 0:Connect-Send-Receive 1:SendTo-ReceiveFrom
	m_bSrvr			= bSrvr;		//default:ｸﾗｲｱﾝﾄ
	m_nTermCnt		= 0;			//ｻｰﾊﾞが構築するｸﾗｲｱﾝﾄ構築数
	HlpTRACE("Ver1.00",3);
}
/*************************************************************************************************
*	ﾃﾞｽﾄﾗｸﾀ
**************************************************************************************************/
CTCPSoc::~CTCPSoc()
{
}
// ClassWizard が必要とする以下の行を編集しないでください。
#if 0
BEGIN_MESSAGE_MAP(CTCPSoc, CAsyncSocket)
	//{{AFX_MSG_MAP(CTCPSoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/*************************************************************************************************
*	ソケットを作成します。
* nSocketPort:ソケットで使う既知のポート。Windows ソケットにポートを選択させるときは 0 を指定します。
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
			case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEADDRINUSE:		str = "指定したアドレスは使用中です。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット操作がブロッキングされています。";break;
			case WSAEADDRNOTAVAIL:	str = "指定したアドレスは、ローカル マシンからは利用できません。";break;
			case WSAEAFNOSUPPORT:	str = "指定したアドレス ファミリは、このソケットではサポートしていません。";break;
			case WSAECONNREFUSED:	str = "接続を試みましたが、リジェクトされました。";break;
			case WSAEDESTADDRREQ:	str = "宛先アドレスが必要です。";break;
			case WSAEFAULT:			str = "引数 nSockAddrLen が不正です。";break;
			case WSAEINVAL:			str = "ソケットはまだアドレスにバインドされていません。";break;
			case WSAEISCONN:		str = "ソケットは既に接続されています。";break;
			case WSAEMFILE:			str = "利用できるファイル ディスクリプタがありません。";break;
			case WSAENETUNREACH:	str = "現時点で、ホストからネットワークに到達できません。";break;
			case WSAENOBUFS:		str = "利用できるバッファ領域がありません。ソケットは接続できません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			case WSAETIMEDOUT:		str = "接続を試みましたが、タイムアウトで接続を確立できませんでした。";break;
			case WSAEWOULDBLOCK:	str = "ソケットが非ブロッキングになっていて、接続が完了できません。 ";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("Create() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	ピア ソケットとの接続を確立します。
*  lpszHostAddress: オブジェクトを接続するソケットのネットワーク アドレス。 
*                   "ftp.microsoft.com" のようなマシン名、または "128.56.22.8" のようにドットで区切られた数字を指定します。
*  nHostPort      : ソケット アプリケーションを識別するポート。
**************************************************************************************************/
BOOL CTCPSoc::Connect(LPCTSTR lpszHostAddress, UINT nHostPort)
{
	CString str;
	str.Format(_T("Connect[adr:%s port:%d]"),lpszHostAddress,nHostPort);
	HlpTRACE(str,3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	m_strHostAdr	= lpszHostAddress;
	m_nHostPort		= nHostPort;

	if(m_nMode == 1){		//SendTo ReceiveFromを使用
		return TRUE;
	}
//-----------------------------------
	int nVal = 0;

	if(CAsyncSocket::Connect(lpszHostAddress,nHostPort) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEADDRINUSE:		str = "指定したアドレスは使用中です。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット操作がブロッキングされています。";break;
			case WSAEADDRNOTAVAIL:	str = "指定したアドレスは、ローカル マシンからは利用できません。";break;
			case WSAEAFNOSUPPORT:	str = "指定したアドレス ファミリは、このソケットではサポートしていません。";break;
			case WSAECONNREFUSED:	str = "接続を試みましたが、リジェクトされました。";break;
			case WSAEDESTADDRREQ:	str = "宛先アドレスが必要です。";break;
			case WSAEFAULT:			str = "引数 nSockAddrLen が不正です。";break;
			case WSAEINVAL:			str = "ソケットはまだアドレスにバインドされていません。";break;
			case WSAEISCONN:		str = "ソケットは既に接続されています。";break;
			case WSAEMFILE:			str = "利用できるファイル ディスクリプタがありません。";break;
			case WSAENETUNREACH:	str = "現時点で、ホストからネットワークに到達できません。";break;
			case WSAENOBUFS:		str = "利用できるバッファ領域がありません。ソケットは接続できません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			case WSAETIMEDOUT:		str = "接続を試みましたが、タイムアウトで接続を確立できませんでした。";break;
//			case WSAEWOULDBLOCK:	str = "ソケットが非ブロッキングになっていて、接続が完了できません。 ";break;
			case WSAEWOULDBLOCK:	return TRUE;//OnConnect()ｺｰﾙﾊﾞｯｸを使用しているのでOK
			default:str = "不明なエラー";break;
		}
		HlpTRACE("Connect() "+str,ERR);
*/
		return FALSE;
	}
	CAsyncSocket::GetSockName(LocalIP, LocalPort);
	return TRUE;
}
/*************************************************************************************************
*	接続要求を待ちます。
**************************************************************************************************/
BOOL CTCPSoc::Listen()
{
	HlpTRACE("Listen",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	if(CAsyncSocket::Listen() == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEADDRINUSE:		str = "使用中のアドレスに対してリスナになるよう試みました。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAEINVAL:			str = "ソケットは Bind を使ってバインドされていないか、既に接続されています。";break;
			case WSAEISCONN:		str = "ソケットは既に接続されています。";break;
			case WSAEMFILE:			str = "利用できるファイル ディスクリプタがありません。";break;
			case WSAENOBUFS:		str = "利用できるバッファ領域がありません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			case WSAEOPNOTSUPP:		str = "参照されるソケットの型は、Listen 操作をサポートしていません。";break;
			default:str = "()不明なエラー";break;
		}
		HlpTRACE("Listen() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	ソケットをローカル アドレスに結び付けます。
**************************************************************************************************/
BOOL CTCPSoc::Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress/*=NULL*/)
{
	HlpTRACE("Bind",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	if(CAsyncSocket::Bind(nSocketPort,lpszSocketAddress) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windowsソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEADDRINUSE:		str = "指定したアドレスは使用中です。SetSockOpt のソケット オプション SO_REUSEADDR を参照してください。";break;
			case WSAEFAULT:			str = "引数 nSockAddrLen が小さすぎます。SOCKADDR 構造体のサイズよりも小さくなっています。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット操作がブロッキングされています。";break;
			case WSAEAFNOSUPPORT:	str = "指定したアドレス ファミリは、このポートではサポートしていません。";break;
			case WSAEINVAL:			str = "ソケットは既にアドレスにバインドされています。";break;
			case WSAENOBUFS:		str = "利用できるバッファ領域がありません。接続が多すぎます。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("Bind() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	ソケット上の接続を受け入れます。
**************************************************************************************************/
BOOL CTCPSoc::Accept(CAsyncSocket& rConnectedSocket)
{
//	HlpTRACE("Accept",3);
	if(HlpChkSrvr(TRUE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	SOCKADDR SockAddr;
	int nLen = sizeof(SOCKADDR);
	if(CAsyncSocket::Accept(rConnectedSocket,&SockAddr,&nLen) == 0){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEFAULT:			str = "引数 lpSockAddrLen が小さすぎます。SOCKADDR 構造体のサイズよりも小さくなっています。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAEINVAL:			str = "受け入れる前に Listen が呼び出されていません。";break;
			case WSAEMFILE:			str = "受け入れるエントリ上のキューが空で、利用できるディスクリプタがありません。";break;
			case WSAENOBUFS:		str = "利用できるバッファ領域がありません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			case WSAEOPNOTSUPP:		str = "参照しているソケットは、接続指向のサービスをサポートするタイプではありません。";break;
			case WSAEWOULDBLOCK:	str = "ソケットは非ブロッキングになっていて、受け入れる接続がありません。";break; 
			default:str = "()不明なエラー";break;
		}
		HlpTRACE("Accept() "+str,ERR);
*/
		return FALSE;
	}

	CString str;
	WORD wVal;
	memcpy(&wVal,SockAddr.sa_data,2);
	str.Format(_T("ｸﾗｲｱﾝﾄ情報 ADR:%d.%d.%d.%d PORT:%d"),
		SockAddr.sa_data[2]*-1,SockAddr.sa_data[3],SockAddr.sa_data[4],SockAddr.sa_data[5],ntohs(wVal));
	HlpTRACE(str,3);
	return TRUE;
}
/*************************************************************************************************
*	接続されているソケットにデータを送信します。
*	lpBuf  : 転送するデータを保持するバッファ。
*	nBufLen: lpBuf 内のバイト単位のデータ長。
**************************************************************************************************/
BOOL CTCPSoc::Send(const void * lpBuf, int nBufLen)
{
	if(m_bSrvr == TRUE){
		return(m_pTerm->Send(lpBuf,nBufLen));
	}

	HlpTRACE("Send",3);
//-------------------------------------------------------------------------------------------
	if(m_nMode == 1){		//SendTo ReceiveFromを使用
		return SendTo(lpBuf,nBufLen,m_nHostPort,m_strHostAdr); 
	}

//	if(CCeSocket::Send(lpBuf,nBufLen) == SOCKET_ERROR){	//接続されているソケットにデータを送信します。
	if(CAsyncSocket::Send(lpBuf,nBufLen) == SOCKET_ERROR){	//接続されているソケットにデータを送信します。
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEACCES:			str = "要求したアドレスはブロードキャスト アドレスですが、適切なフラグが設定されていませんでした。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAEFAULT:			str = "引数 lpBuf がユーザー アドレス空間の有効な部分を指していません。";break;
			case WSAENETRESET:		str = "Windows ソケットのインプリメントがソケットをドロップしたので、接続をリセットする必要があります。";break;
			case WSAENOBUFS:		str = "Windows ソケットのインプリメントが、バッファのデッドロックをリポートています。";break;
			case WSAENOTCONN:		str = "ソケットが接続されていません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB が指定されましたが、SOCK_STREAM 型のソケットではありません。";break;
			case WSAESHUTDOWN:		str = "ソケットはシャット ダウンされています。nHow に 0 または 2 を指定して ShutDown を起動した後では、ソケットで Send を呼び出すことはできません。";break;
			case WSAEWOULDBLOCK:	str = "ソケットは非ブロッキングになっていて、要求した操作がブロックされました。";break;
			case WSAEMSGSIZE:		str = "ソケットが SOCK_DGRAM 型で、Windows ソケットのインプリメントがサポートする最大長よりもデータグラムが長すぎます。";break;
			case WSAEINVAL:			str = "ソケットが Bind を使ってバインドされていません。";break;
			case WSAECONNABORTED:	str = "タイムアウトまたはその他の障害により、仮想回路はアボートされました。";break;
			case WSAECONNRESET:		str = "リモート側から仮想回路がリセットされました。 ";break;
			default:str = "()不明なエラー";break;
		}
		HlpTRACE("Send() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	接続されているソケットにデータを送信します。
*	lpBuf  : 転送するデータを保持するバッファ。
*	nBufLen: lpBuf 内のバイト単位のデータ長。
**************************************************************************************************/
BOOL CTCPSoc::SendTo(const void * lpBuf, int nBufLen,
					UINT nHostPort, LPCTSTR lpszHostAddress /*= NULL*/, int nFlags /*= 0*/) 
{
	HlpTRACE("SendTo",3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	int nLen;
	if((nLen = CAsyncSocket::SendTo(lpBuf,nBufLen,nHostPort,lpszHostAddress)) == SOCKET_ERROR){	//接続されているソケットにデータを送信します。
/*
		int nErr = CAsyncSocket::GetLastError();
		switch(nErr){
			case WSANOTINITIALISED:		str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN: 			str = "Windowsソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEACCES:				str = "要求したアドレスはブロードキャスト アドレスですが、適切なフラグが設定されていませんでした。";break;
			case WSAEINPROGRESS:		str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAEFAULT:				str = "引数 lpBuf または lpSockAddr がユーザー アドレス空間の有効な部分を指していません。または、引数 lpSockAddr 小さすぎます。SOCKADDR 構造体のサイズより小さくなっています。";break;
			case WSAENETRESET:			str = "Windows ソケットのインプリメントがソケットをドロップしたので、接続をリセットする必要があります。";break;
			case WSAENOBUFS:			str = "Windows ソケットのインプリメントが、バッファのデッドロックをリポートています。";break;
			case WSAENOTCONN:			str = "ソケットが接続されていません (SOCK_STREAM 型のみ)。";break;
			case WSAENOTSOCK:			str = "ディスクリプタがソケットではありません。";break;
			case WSAEOPNOTSUPP:			str = "MSG_OOB が指定されましたが、SOCK_STREAM 型のソケットではありません。";break;
			case WSAESHUTDOWN:			str = "ソケットはシャット ダウンされています。nHow に 0 または 2 を指定して ShutDown を起動した後では、ソケットで SendTo を呼び出すことはできません。";break;
			case WSAEWOULDBLOCK:		str = "ソケットは非ブロッキングになっていて、要求した操作がブロックされました。";break;
			case WSAEMSGSIZE:			str = "ソケットが SOCK_DGRAM 型で、Windows ソケットのインプリメントがサポートする最大長よりもデータグラムが長すぎます。";break;
			case WSAEINVAL:				str = "ソケットが Bind を使ってバインドされていません。";break;
			case WSAECONNABORTED:		str = "タイムアウトまたはその他の障害により、仮想回路はアボートされました。";break;
			case WSAECONNRESET:			str = "リモート側から仮想回路がリセットされました。";break;
			case WSAEADDRNOTAVAIL:		str = "指定したアドレスはローカル マシンからは利用できません。";break;
			case WSAEAFNOSUPPORT:		str = "指定したファミリのアドレスはこのソケットでは使用できません。";break;
			case WSAEDESTADDRREQ:		str = "宛先アドレスが必要です。";break;
			case WSAENETUNREACH:		str = "現時点では、ホストからネットワークに到達できません。 ";break;
			case WSAEISCONN:			str = "Socket is already connected. A connect request was made on an already connected socket. Some implementations also return this error if sendto is called on a connected SOCK_DGRAM socket ";
										str += "(For SOCK_STREAM sockets, the to parameter in sendto is ignored), although other implementations treat this as a legal occurrence.  ";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("SendTo() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	ソケットからデータを受信します。（通常OnReceiveから呼び出されます）
*	lpBuf  : 受信データ バッファ。
*	nBufLen: lpBuf の長さ。バイト単位です。
**************************************************************************************************/
int CTCPSoc::Receive(void * lpBuf, int nBufLen,int nFlags/*=0*/)
{
//-------------------------------------------------------------------------------------------
	if(m_nMode == 1){		//SendTo ReceiveFromを使用
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
			case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。 ";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。 ";break;
			case WSAENOTCONN:		str = "ソケットが接続されていません。 ";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。 ";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。 ";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB が指定されましたが、SOCK_STREAM 型のソケットではありません。 ";break;
			case WSAESHUTDOWN:		str = "ソケットはシャット ダウンされました。nHow の 0 または 2 を渡して ShutDown を起動した後では、ソケットで Receive を呼び出すことはできません。 ";break;
			case WSAEWOULDBLOCK:	str = "ソケットは非ブロッキングになっていて、Receive 操作がブロックされました。 ";break;
			case WSAEMSGSIZE:		str = "データグラムが長すぎて、指定したバッファに入りきらないため、切り詰められました。 ";break;
			case WSAEINVAL:			str = "ソケットは Bind を使ってバインドされていません。 ";break;
			case WSAECONNABORTED:	str = "タイムアウトまたはその他の障害により、仮想回路はアボートされました。 ";break;
			case WSAECONNRESET:		str = "リモート側から仮想回路がリセットされました。  ";break;
			case WSAEFAULT:			str = "不良なアドレスです。";break;
			default:str = "不明なエラー";break;
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
*	ソケットからデータを受信します。
*	lpBuf  : 受信データ バッファ。
*	nBufLen: lpBuf の長さ。バイト単位です。
**************************************************************************************************/
int CTCPSoc::ReceiveFrom(void * lpBuf, int nBufLen,
						 CString& rSocketAddress, UINT& rSocketPort, int nFlags /*= 0*/)
{
	HlpTRACE("ReceiveFrom",3);
	if(HlpChkSrvr(FALSE) == FALSE)return FALSE;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	int len;
	len = CAsyncSocket::ReceiveFrom(lpBuf,nBufLen,rSocketAddress,rSocketPort,nFlags);
	if(len == SOCKET_ERROR){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。 ";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。 ";break;
			case WSAEFAULT:			str = "引数 lpSockAddrLen が不正です。ピア アドレスを格納するには、lpSockAddr バッファが小さすぎます。 ";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。 ";break;
			case WSAEINVAL:			str = "ソケットは Bind を使ってバインドされていません。 ";break;
			case WSAENOTCONN:		str = "ソケットは接続されていません (SOCK_STREAM 型のみ)。 ";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。 ";break;
			case WSAEOPNOTSUPP:		str = "MSG_OOB が指定されましたが、SOCK_STREAM 型のソケットではありません。 ";break;
			case WSAESHUTDOWN:		str = "ソケットはシャット ダウンされています。nHow に 0 または 2 を指定して ShutDown を起動した後では、ソケットで ReceiveFrom を呼び出すことはできません。 ";break;
			case WSAEWOULDBLOCK:	str = "ソケットは非ブロッキングになっていて、ReceiveFrom 操作がブロックされました。 ";break;
			case WSAEMSGSIZE:		str = "データグラムが長すぎて、指定したバッファに入りきらないため、切り詰められました。 ";break;
			case WSAECONNABORTED:	str = "タイムアウトまたはその他の障害により、仮想回路はアボートされました。 ";break;
			case WSAECONNRESET:		str = "リモート側から仮想回路がリセットされました。  ";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("ReceiveFrom() "+str,ERR);
*/
		return 0;
	}
	return len;
}
/*************************************************************************************************
*	ソケットオプションを獲得します。
**************************************************************************************************/
BOOL CTCPSoc::GetSockOpt(int nOptionName,DWORD *dwpBuf)
{
	HlpTRACE("GetSockOpt",3);

	int nBufSize=4;
	if(CAsyncSocket::GetSockOpt(nOptionName,dwpBuf,&nBufSize) == FALSE){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEFAULT:			str = "引数 lpOptionLen が不正です。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAENOPROTOOPT:	str = "オプションが不正かサポートされていません。特に SO_BROADCAST は SOCK_STREAM 型のソケットではサポートされていません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。 ";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("GetSockOpt() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	ソケットオプションを設定します。
**************************************************************************************************/
BOOL CTCPSoc::SetSockOpt(int nOptionName,DWORD *dwpBuf)
{
	HlpTRACE("SetSockOpt",3);

	int nBufSize=4;
	if(CAsyncSocket::SetSockOpt(nOptionName,dwpBuf,nBufSize) == FALSE){
/*
		switch(CAsyncSocket::GetLastError()){
			case WSANOTINITIALISED: str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
			case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
			case WSAEFAULT:			str = "引数 lpOptionLen が不正です。";break;
			case WSAEINPROGRESS:	str = "実行中の Windows ソケット呼び出しがブロッキングされています。";break;
			case WSAENOPROTOOPT:	str = "オプションが不正かサポートされていません。特に SO_BROADCAST は SOCK_STREAM 型のソケットではサポートされていません。";break;
			case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。 ";break;
			default:str = "不明なエラー";break;
		}
		HlpTRACE("SetSockOpt() "+str,ERR);
*/
		return FALSE;
	}
	return TRUE;
}
/*************************************************************************************************
*	クローズ
**************************************************************************************************/
void CTCPSoc::Close()
{
//-------------------------------------------------------------------------------
	CAsyncSocket::Close();
}
/*************************************************************************************************
*	受信データがバッファにあることをソケットに通知するために、フレームワークが呼び出します。
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
*	送信データ可能な場合に、フレームワークが呼び出します。
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
*  接続要求あり
***********************************************************************************************/
void CTCPSoc::OnAccept(int nErrorCode) 
{
	m_pWnd->PostMessage(WM_EVENT,EV_ACCEPT_NOTIFI, m_nIndex);
//-------------------------------------------------------------------------------
	CAsyncSocket::OnAccept(nErrorCode);
}
/**********************************************************************************************
*  接続完了
***********************************************************************************************/
void CTCPSoc::OnConnect(int nErrorCode) 
{
	CString str;

	HlpTRACE("OnConnect",3);
	if(HlpChkSrvr(FALSE) == FALSE)goto TAG_EXIT;		//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
//-------------------------------------------------------------------------------------------
	switch(nErrorCode){
		case 0:	goto TAG_EXIT;
		case WSANOTINITIALISED:	str = "この API を使う前に AfxSocketInit の呼び出しが正常終了していることが必要です。";break;
		case WSAENETDOWN:		str = "Windows ソケットのインプリメントが、ネットワーク サブシステムの異常を検出しました。";break;
		case WSAEADDRINUSE:		str = "指定したアドレスは使用中です。";break;
		case WSAEINPROGRESS:	str = "実行中の Windows ソケット操作がブロッキングされています。";break;
		case WSAEADDRNOTAVAIL:	str = "指定したアドレスは、ローカル マシンからは利用できません。";break;
		case WSAEAFNOSUPPORT:	str = "指定したアドレス ファミリは、このソケットではサポートしていません。";break;
		case WSAECONNREFUSED:	str = "接続を試みましたが、リジェクトされました。";break;
		case WSAEDESTADDRREQ:	str = "宛先アドレスが必要です。";break;
		case WSAEFAULT:			str = "引数 nSockAddrLen が不正です。";break;
		case WSAEINVAL:			str = "ソケットはまだアドレスにバインドされていません。";break;
		case WSAEISCONN:		str = "ソケットは既に接続されています。";break;
		case WSAEMFILE:			str = "利用できるファイル ディスクリプタがありません。";break;
		case WSAENETUNREACH:	str = "現時点で、ホストからネットワークに到達できません。";break;
		case WSAENOBUFS:		str = "利用できるバッファ領域がありません。ソケットは接続できません。";break;
		case WSAENOTSOCK:		str = "ディスクリプタがソケットではありません。";break;
		case WSAETIMEDOUT:		str = "接続を試みましたが、タイムアウトで接続を確立できませんでした。";break;
		case WSAEWOULDBLOCK:	str = "ソケットが非ブロッキングになっていて、接続が完了できません。 ";break;
//		case WSAEWOULDBLOCK:	return TRUE;//OnConnect()ｺｰﾙﾊﾞｯｸを使用しているのでOK
		default:str = "()不明なエラー";break;
	}
	HlpTRACE(str,2);
//-------------------------------------------------------------------------------------------
TAG_EXIT:
	DWORD dwParam;
	m_Tool.SetDwHighLow(&dwParam,m_nIndex,HIGH_WORD);			//上位にｲﾝﾃﾞｯｸｽ
	m_Tool.SetDwHighLow(&dwParam,nErrorCode,LOW_WORD);		//下位にｴﾗｰｺｰﾄﾞ
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_CONNECT_NOTIF, dwParam);	//ｿｹｯﾄ接続確定通知
//-------------------------------------------------------------------------------
	CAsyncSocket::OnConnect(nErrorCode);
//	CCeSocket::OnConnect(nErrorCode);
}
/**********************************************************************************************
*  切断要求あり
***********************************************************************************************/
void CTCPSoc::OnClose(int nErrorCode) 
{
	m_pWnd->PostMessage(WM_EVENT,EV_SOC_CLOSE, m_nIndex);
//-------------------------------------------------------------------------------------------
//	CAsyncSocket::OnClose(nErrorCode);

//	if(nErrorCode != 0)AfxMessageBox("end err");
}
/**********************************************************************************************
*  帯域外ﾃﾞｰﾀあり
***********************************************************************************************/
void CTCPSoc::OnOutOfBandData(int nErrorCode) 
{
	HlpTRACE("OnOutOfBandData",3);
//-------------------------------------------------------------------------------------------
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}
/**********************************************************************************************
*	ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査
*	bSrvr:TRUEはｻｰﾊﾞ時　FALSEはｸﾗｲｱﾝﾄ時
*	return;TRUEはOK FALSEはNG
***********************************************************************************************/
BOOL CTCPSoc::HlpChkSrvr(BOOL bSrvr/*=TRUE*/)
{
	if(m_bSrvr == bSrvr)return TRUE;
	HlpTRACE("ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御異常",2);
	return FALSE;
}
/**********************************************************************************************
*  TRACEへMSG送信
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
