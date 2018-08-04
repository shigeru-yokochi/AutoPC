// GPS.h: interface for the CGPS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPS_H__F9946EB5_2245_11D5_8955_0040CA1F5D30__INCLUDED_)
#define AFX_GPS_H__F9946EB5_2245_11D5_8955_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileText.h"
#include "CeCommMgr.h"

#define GPS_CONTINUE		1
#define GPS_DECODE_OK		2
#define GPS_DECODE_NO		3

class CGPS  
{
public:
	CGPS(int nDecodeGPSType,int nCountry);
	virtual ~CGPS();

	int Test(CString strDataPath,int nCnt);
//	int SetRec(char *buf,CString *strpTRACE);	//GPS��M���R�[�h�ݒ菈��
	void _DecodeCSV2(void);
	void _DecodeCSV(const CString S);
	BOOL DecodeGps1(CCeCommMgr *pCom=NULL,BOOL bDemo=FALSE);
	BOOL DecodeGps2(void);
	void GetStatus(CString *strpTRACE);			//��Ԋl��
	int GetSpeed();
	int GetStatus();							//��Ԋl��
	int GetAngle();
	void GetENPoint(double *dfpEW,double *dfpNS);

//	BOOL SetData(char *cpBuf,int nLen);		//GPS�f�[�^�ݒ�
	BOOL ChkRecCnt(char *cpBuf,int *npLen,int nCntMax);	//GPS�f�[�^�K�v�ȃ��R�[�h������


    UCHAR	ReceiveBuff[BUF_SIZE];
    int		ReceiveCount;
	int		ChkDecodeData(UCHAR c);			//GPS�f�[�^�f�R�[�h����

	void MakeGPSDataImage(char *cpBuf,double dfEW,double dfNS,int nSpeed,int nAngle);	//GPS��M�C���[�W�쐬
private:
	BOOL HlpGetRecData(char* cpOutBuf,char *cpBuf,int nLen,int nRecNo);	//GPS�f�[�^�w�背�R�[�h�f�[�^�l��
	double HlpGPSFormCnv(double dfVal);
	void HlpWGS84_Tokyo(double *dfpEW,double *dfpNS);					//WGS84���x�b�Z���ɕϊ�

	DWORD m_dwTestFileSeekPos;
	//---GPS DATA-----------------------
	double	m_dfGPSInfoAbove,
			m_dfGPSInfoAngle,
			m_dfGPSInfoSpeed,
			m_dfGPSInfoEast,
			m_dfGPSInfoNorth;
	int		m_nGPSInfoAllGps,
			m_nGPSInfoUseGPS,	
			m_nGPSInfoStatus;
	//-----------------------------

    CString	GPSSL[50];
	int GPSSL_Count;

	BOOL	GPSUnitConnect;
    CString GPSModeText[5];

	CFileText		m_file;
	BOOL m_bOpenFlg;

	int m_nDecodeGPSType;

	int m_nErrCnt;
	int m_nCountry;
};

#endif // !defined(AFX_GPS_H__F9946EB5_2245_11D5_8955_0040CA1F5D30__INCLUDED_)
