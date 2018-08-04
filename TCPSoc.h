#if !defined(AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_)
#define AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_

#include "Tool.h"
//#include "Hed.h"	// ClassView によって追加されました。

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/*************************************************************************************************
*	TCPｿｹｯﾄ送受信
**************************************************************************************************/
class CTCPSoc : public CAsyncSocket
//class CTCPSoc : public CCeSocket
{
// アトリビュート
//public:

// オペレーション
public:
	CTCPSoc(CWnd * pWnd,int nIndex=1,char *pTraceBuf=0,BOOL bSrvr=FALSE);
	virtual ~CTCPSoc();

// オーバーライド
public:
	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CTCPSoc)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	//}}AFX_VIRTUAL

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CTCPSoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG

// インプリメンテーション
public:
	void Close();
	BOOL Create(UINT nSocketPort);
	BOOL Send(const void* lpBuf, int nBufLen);
	int Receive( void* lpBuf, int nBufLen,int nFlags=0);
	BOOL GetSockOpt(int nOptionName,DWORD *dwpBuf);		//ソケットオプションを獲得します。
	BOOL SetSockOpt(int nOptionName,DWORD *dwpBuf);		//ソケットオプションを設定します。
//-----------------ｻｰﾊﾞ側-------------------------------------------------------
	BOOL Listen();										//接続要求を待ちます。
	BOOL Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress=NULL);	//ソケットをローカル アドレスに結び付けます。
	BOOL Accept(CAsyncSocket& rConnectedSocket);		//ソケット上の接続を受け入れます。
//-----------------ｸﾗｲｱﾝﾄ側-------------------------------------------------------
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	CString	LocalIP; 
	UINT	LocalPort;
private:
	//UDP時の残骸なのでとりあえずprivateにしておく
	BOOL SendTo(const void * lpBuf, int nBufLen,
					UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0);
	int ReceiveFrom(void * lpBuf, int nBufLen,
				 CString& rSocketAddress, UINT& rSocketPort, int nFlags= 0);
//----------------------------------------------------------------------------
	CTool m_Tool;
	BOOL m_bSrvr;										//TRUE:ｻｰﾊﾞ FALSE:ｸﾗｲｱﾝﾄ(default)
	int m_nMode;
	CString m_strHostAdr;
	int m_nHostPort;
	char *m_pTraceBuf;

	int m_nIndex;
	CWnd* m_pWnd;	
	CString str;
	CTCPSoc* m_pTerm;									//ｻｰﾊﾞが構築するｸﾗｲｱﾝﾄへのﾎﾟｲﾝﾀ
	BOOL m_bTerm;										//ｻｰﾊﾞが構築するｸﾗｲｱﾝﾄ構築ﾌﾗｸﾞ
	int	m_nTermCnt;										//ｻｰﾊﾞが構築するｸﾗｲｱﾝﾄ構築数

//---------------ﾍﾙﾊﾟ関数-----------------------------------------------------------
	void HlpTRACE(CString str,int level=0);
	BOOL HlpChkSrvr(BOOL bSrvr=TRUE);					//ｻｰﾊﾞ/ｸﾗｲｱﾝﾄ制御検査

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_)
