#if !defined(AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_)
#define AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_

#include "Tool.h"
//#include "Hed.h"	// ClassView �ɂ���Ēǉ�����܂����B

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/*************************************************************************************************
*	TCP���đ���M
**************************************************************************************************/
class CTCPSoc : public CAsyncSocket
//class CTCPSoc : public CCeSocket
{
// �A�g���r���[�g
//public:

// �I�y���[�V����
public:
	CTCPSoc(CWnd * pWnd,int nIndex=1,char *pTraceBuf=0,BOOL bSrvr=FALSE);
	virtual ~CTCPSoc();

// �I�[�o�[���C�h
public:
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CTCPSoc)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	//}}AFX_VIRTUAL

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CTCPSoc)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

// �C���v�������e�[�V����
public:
	void Close();
	BOOL Create(UINT nSocketPort);
	BOOL Send(const void* lpBuf, int nBufLen);
	int Receive( void* lpBuf, int nBufLen,int nFlags=0);
	BOOL GetSockOpt(int nOptionName,DWORD *dwpBuf);		//�\�P�b�g�I�v�V�������l�����܂��B
	BOOL SetSockOpt(int nOptionName,DWORD *dwpBuf);		//�\�P�b�g�I�v�V������ݒ肵�܂��B
//-----------------���ޑ�-------------------------------------------------------
	BOOL Listen();										//�ڑ��v����҂��܂��B
	BOOL Bind(UINT nSocketPort, LPCTSTR lpszSocketAddress=NULL);	//�\�P�b�g�����[�J�� �A�h���X�Ɍ��ѕt���܂��B
	BOOL Accept(CAsyncSocket& rConnectedSocket);		//�\�P�b�g��̐ڑ����󂯓���܂��B
//-----------------�ײ��đ�-------------------------------------------------------
	BOOL Connect(LPCTSTR lpszHostAddress, UINT nHostPort);
	CString	LocalIP; 
	UINT	LocalPort;
private:
	//UDP���̎c�[�Ȃ̂łƂ肠����private�ɂ��Ă���
	BOOL SendTo(const void * lpBuf, int nBufLen,
					UINT nHostPort, LPCTSTR lpszHostAddress = NULL, int nFlags = 0);
	int ReceiveFrom(void * lpBuf, int nBufLen,
				 CString& rSocketAddress, UINT& rSocketPort, int nFlags= 0);
//----------------------------------------------------------------------------
	CTool m_Tool;
	BOOL m_bSrvr;										//TRUE:���� FALSE:�ײ���(default)
	int m_nMode;
	CString m_strHostAdr;
	int m_nHostPort;
	char *m_pTraceBuf;

	int m_nIndex;
	CWnd* m_pWnd;	
	CString str;
	CTCPSoc* m_pTerm;									//���ނ��\�z����ײ��Ăւ��߲��
	BOOL m_bTerm;										//���ނ��\�z����ײ��č\�z�׸�
	int	m_nTermCnt;										//���ނ��\�z����ײ��č\�z��

//---------------���ߊ֐�-----------------------------------------------------------
	void HlpTRACE(CString str,int level=0);
	BOOL HlpChkSrvr(BOOL bSrvr=TRUE);					//����/�ײ��Đ��䌟��

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TCPSOC_H__BEDF6FAA_7AAD_11D1_B991_52544C01278A__INCLUDED_)
