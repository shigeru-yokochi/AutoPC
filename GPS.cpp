// GPS.cpp: implementation of the CGPS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "GPS.h"
#include "Tool.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//***********************************************************************************
//*	�R���X�g���N�^
//***********************************************************************************
CGPS::CGPS(int nDecodeGPSType,int nCountry)
{
	m_nDecodeGPSType	= nDecodeGPSType;
	m_nCountry			= nCountry;
	m_bOpenFlg = FALSE;
	m_nErrCnt = 0;
	ReceiveCount = 0;
	m_dfGPSInfoEast = 0;
	m_dfGPSInfoNorth = 0;
}
//***********************************************************************************
//*	�f�X�g���N�^
//***********************************************************************************
CGPS::~CGPS()
{

}
//***********************************************************************************
//*	GPS Demo (�t�@�C�����ǂݍ���)
//***********************************************************************************
int CGPS::Test(CString strDataPath,int nCnt)
{
	int nRet = -1;

	if(nCnt == 1){
		if(m_bOpenFlg == TRUE){
			m_file.Close();
			m_bOpenFlg = FALSE;
			return -1;
		}

		if(m_file.Open(strDataPath+DEMO_FILE_GPS, CFile::modeRead |CFile::shareExclusive) == FALSE){
			return -1;
		}
		m_bOpenFlg = TRUE;
	}

	int i;

	//----------�P���΂��ɂ��č�����------------------------
//	for(i=0;i<5;i++){
//		if(m_file.GetRec((char *)(&ReceiveBuff[0]),BUF_SIZE) < 0){
//			nRet = -1;
//			break;
//		}
//	}
	//-----------------------------------------

	for(i=0;i<5;i++){
		if(m_file.GetRec((char *)(&ReceiveBuff[0]),BUF_SIZE) < 0){
			nRet = -1;
			break;
		}
		ReceiveCount = strlen((char *)(&ReceiveBuff[0]));
		if(DecodeGps1(NULL,TRUE) == FALSE)nRet=0;
		else                     nRet=1;
	}


	if(nRet == -1){
		m_file.Close();
		m_bOpenFlg = FALSE;
	}


	return nRet;

}

//***********************************************************************************
// ��Ԋl��
//***********************************************************************************
void CGPS::GetStatus(CString *strpTRACE)
{
	strpTRACE->Format(_T("agl:%0.0lf status:%d speed:%0.0lf E:%0.5lf N:%0.5lf"),
		m_dfGPSInfoAngle,m_nGPSInfoStatus,m_dfGPSInfoSpeed,m_dfGPSInfoEast,m_dfGPSInfoNorth);

}
//***********************************************************************************
// ��Ԋl��
//***********************************************************************************
int CGPS::GetStatus()
{
	return m_nGPSInfoStatus;
}
//***********************************************************************************
// ���x�l��
//***********************************************************************************
int CGPS::GetSpeed()
{
	return (int)m_dfGPSInfoSpeed;
}
//***********************************************************************************
//	GPS��M���R�[�h�ݒ菈��
//	return 0:�r���̃��R�[�h 1:�K�v���R�[�h�ݒ芮��
//***********************************************************************************
//int CGPS::SetRec(char *buf,CString *strpTRACE)
//{
//	int nRet = 1;

//	strcpy((char *)(&ReceiveBuff[0]),buf);

//	ReceiveCount = strlen((char *)(&ReceiveBuff[0]));
//	if(DecodeGps1() == FALSE)nRet=0;

//	strpTRACE->Format(_T("agl:%0.0lf status:%d speed:%0.0lf E:%0.5lf N:%0.5lf"),
//		m_dfGPSInfoAngle,m_nGPSInfoStatus,m_dfGPSInfoSpeed,m_dfGPSInfoEast,m_dfGPSInfoNorth);


//	return nRet;
//}
//***********************************************************************************
//*	GPS�f�[�^�ݒ�
//*	cpBuf���Ɏ�M�f�[�^��ݒ肷��
//***********************************************************************************
//BOOL CGPS::SetData(char *cpBuf,int nLen)
//{
//	BOOL bRet = FALSE;
//	int i,nCont = 5;
//	if(m_nDecodeGPSType == 2)nCont = 1;

//	for(i=0;i<nCont;i++){
//		HlpGetRecData((char *)(&ReceiveBuff[0]),&cpBuf[0],nLen,i);
//		bRet = DecodeGps1();
//		ReceiveCount = strlen((char *)(&ReceiveBuff[0]));
//	}

//	return bRet;
//}
//***********************************************************************************
//*	GPS�f�[�^�K�v�ȃ��R�[�h������
//*	npLen�ɂ͓��͎��̓o�t�@�[���̗L���T�C�Y����߂莞�͕K�v�ȃT�C�Y
//***********************************************************************************
BOOL CGPS::ChkRecCnt(char *cpBuf,int *npLen,int nCntMax)
{
	int i,nCnt=0;
	for(i=0;i<*npLen;i++){
		if(cpBuf[i] == 0x0a){
			nCnt++;
			if(nCnt == nCntMax){
				*npLen = i+1;
				return TRUE;
			}
		}
	}
	return FALSE;
}
//***********************************************************************************
//*	GPS�f�[�^���R�[�h�f�[�^�l��
//***********************************************************************************
BOOL CGPS::HlpGetRecData(char* cpOutBuf,char *cpBuf,int nLen,int nRecNo)
{
	int i,nPos=0,nCnt=0;
	for(i=0;i<nLen;i++){
		if(cpBuf[i] == 0x0d)continue;
		cpOutBuf[nPos] = cpBuf[i];
		nPos++;
		if(cpBuf[i] == 0x0a){
			cpOutBuf[nPos-1] = 0;
			if(nCnt == nRecNo){
				return TRUE;
			}
			else{
				nCnt++;
				nPos=0;
			}
		}
	}
	return FALSE;
}


//***********************************************************************************
//*	GPS�f�[�^CSV�ϊ�
//***********************************************************************************
void CGPS::_DecodeCSV(const CString S)
{
	int		N, i, p;
	CString	C, Str;

	N = S.GetLength();
	Str = "";
	p = 0;
//	for( i = 0; i < N; ++i) {
	for( i = 0; i < N; i++) {
		C = S.Mid(i, 1);
		if( (C == ",")||(C == "*") ) {
			GPSSL[p] = Str;
			Str = "";
			++p;
		} else {
			Str = Str + C;
		}
	}
	GPSSL[p] = Str;
	GPSSL_Count = p+1;
}
//***********************************************************************************
//*	GPS�f�[�^CSV�ϊ�
//***********************************************************************************
void CGPS::_DecodeCSV2(void)
{
	int		i, p, pp;
	char 	C, Str[1024];


	p = 0;
	pp = 0;
//	for( i = 0; i < ReceiveCount; ++i) {
	for( i = 0; i < ReceiveCount; i++) {
		C = ReceiveBuff[i];
		if( (C == ',') || (C == '*') ) {
			Str[pp] = 0;
			GPSSL[p] = Str;
			pp = 0;
			++p;
		} else {
			Str[pp++] = C;
		}
	}
	GPSSL[p] = Str;
	GPSSL_Count = p+1;
}

//***********************************************************************************
//*	GPS�f�[�^�f�R�[�h����
//***********************************************************************************
int CGPS::ChkDecodeData(UCHAR c)
{
	if(m_nDecodeGPSType == 1){
		if( c == 0x0D ) return GPS_CONTINUE;
		else if( c == 0x0A ) return GPS_DECODE_OK;
	}
	else{
		if( c == 0xC6 ) ReceiveCount = 0;
		else if( c == 0xC7 ) ReceiveCount = 0;
		else if( c == 0xDA ) return GPS_DECODE_OK;
	}
	return GPS_DECODE_NO;
}
//***********************************************************************************
//*	GPS�f�[�^�f�R�[�h
//***********************************************************************************
BOOL CGPS::DecodeGps1(CCeCommMgr *pCom/*=NULL*/,BOOL bDemo/*=FALSE*/)
{
	if(m_nDecodeGPSType == 2){
		return DecodeGps2();
	}



	CTool tool;
//	CString S;
	int		i;

	if( ReceiveBuff[0] != '$' ) return FALSE;
//	S = ReceiveBuff;
//	_DecodeCSV(S);
	_DecodeCSV2();


/*
        GGA - GPS���ʃf�[�^
        GGA,050601,3523.262,N,13911.844,E,2,05,1.8,176.4,M,38.6,M,0,0700*73
[1]     050601       ���� taken at 05:06:01 UTC
[2,3]    3523.262,N   �ܓx  35 �x 23.262�� N(�k��)
[4,5]   13911.844,E  �o�x 139 �x 11.844�� E(���o)
[6]     2            �ʒu�i��   : 0 = ����
                                  1 = GPS����
                                  2 = DGPS����
[7]     05           GPS�q���̕ߑ���
[8]     1.8          DOP
[9,10]  176.4,M      �C�����x(m)
[11,12]  38.6,M       �W�I�C�h���@��ȉ~��(WGS-84)
[13]    0            �ŏIDGPS�X�V����̌o�ߎ���
[14]    0700         DGPS���ID�ԍ�
*/

	if( GPSSL[0] == "$GPGGA" ) {
		if( GPSSL_Count < 10 ) return FALSE;
		if( GPSSL[6] == "0" ) return FALSE;
		if( GPSSL[9] != "" ) m_dfGPSInfoAbove = tool.StrToExtended(GPSSL[9]);
		m_nGPSInfoUseGPS = tool.StrToIntDef(GPSSL[7], 0);
		return FALSE;
	}

/*
        GSA - ���ʂɎg�p����GPS�q����DOP�l
        GSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39
[1]    A            2D/3D�������� = A (�蓮 = M)
[2]    3            3��������
[3-15] 04,05...     ���ʂɎg�p����GPS�q��(PRN�ԍ�)(12�G���A)
       2.5          PDOP (Position Dilution Of Precision)
       1.3          HDOP (Horizontal Dilution Of Precision)
       2.1          VDOP (Vertical Dilution Of Precision)
       DOP�Ƃ́A�q���̊􉽊w�I�z�u�����ʐ��x�ɗ^����e���������Ă��܂��B
*/
	if( GPSSL[0] == "$GPGSA" ) {
		if( GPSSL_Count < 15 ) return FALSE;
		if(      GPSSL[2] == "2" ) m_nGPSInfoStatus = 2;  // 2D Mode
		else if( GPSSL[2] == "3" ) m_nGPSInfoStatus = 4;  // 3D Mode
	    else                       m_nGPSInfoStatus = 1;  // ����
		return FALSE;
	}

/*
        GSV - ���q��
        GSV,2,1,08,01,40,083,46,02,17,308,41,12,07,344,39,14,22,228,45*75
[1]         2            GSV�Z���e���X�̐�
[2]         1            �Z���e���X�ԍ� 1 of 2
[3]         08           ���q����
4           01           GPS�q����PRN�ԍ�
5           40           �p(�x)
6           083          ���ʊp(�x)
7           46           �M�����x - ���l�̑傫�������ǂ�
           <�Z���e���X����@4�q���܂ŌJ��Ԃ��B>
             GSV�Z���e���X�͍ő�3�s�ƂȂ�܂��B
*/
	if( GPSSL[0] == "$GPGSV" ) {
		if( GPSSL_Count < 20 ) return FALSE;
		i = tool.StrToIntDef(GPSSL[3], 0);
		m_nGPSInfoAllGps  = i;
//    Panel3.Caption = Format("Capture %d/%d",[GpsForm.GPSInfo.UseGPS, GpsForm.m_nGPSInfoAllGPS]);
		return FALSE;
	}
/*
        RMC - GPS�y��Transit�ł̍ŏ�������`�f�[�^
        RMC,050601,A,3523.262,N,13911.844,E,001.2,180.9,311296,006.9,W*66
[1]     050601       ���ʎ��� 05:06:01 UTC
[2]     A            �f�[�^�L���@= A, �f�[�^���� = V
[3,4]   3523.262,N   �ܓx 35 �x 23.262 �� �k��
[5,6]   13911.844,E  �o�x 139 �x 11.844 �� ���o
[7]     001.2        �Βn���x(�P��:[knot])
[8]     180.9        �^����
[9]     311296       ���ʓ��t�@DDMMYY 1996�N12��31��
[10,11] 006.9,W      ���C�΍��@6.9�x�@����
           *66          �`�F�b�N�T��(�K�{)
*/

	if(pCom != NULL && GPSSL[0] == "$GPGLL" ) {
//		char Buff[] = {"$PJRCE,GP,0,2,05,1,1,2,00,00,00,00,00,00,3,00*73\r\n"};
		char Buff[] = {"$PJRCE,GP,0,2,05,1,1,2,00,00,00,00,00,00,6,00*76\r\n"};
		pCom->WriteComm(Buff, strlen(Buff));
		return FALSE;
	}


	if( GPSSL[0] == "$GPRMC" ) {
		if( GPSSL_Count < 10 ) return FALSE;
		GPSUnitConnect = TRUE;
		Sleep(1);
		if( GPSSL[2] != "A" ) return FALSE;
//    yy  = StrToIntDef(copy(GPSSL[9], 5, 2), 0);
//    mm  = StrToIntDef(copy(GPSSL[9], 3, 2), 0);
//    dd  = StrToIntDef(copy(GPSSL[9], 1, 2), 0);
//    hh  = StrToIntDef(copy(GPSSL[1], 1, 2), 0);
//    min = StrToIntDef(copy(GPSSL[1], 3, 2), 0);
//    ss  = StrToIntDef(copy(GPSSL[1], 5, 2), 0);

		//NS�k��
		m_dfGPSInfoNorth = tool.StrToIntDef(  GPSSL[3].Mid(0,  2), 0)+
		                tool.StrToExtended(GPSSL[3].Mid(2, 10)) / 60;
		if( GPSSL[4] == "S" ) m_dfGPSInfoNorth *= -1;//<=====�ǉ�



		//EW���o
		m_dfGPSInfoEast  = tool.StrToIntDef(  GPSSL[5].Mid(0,  3), 0)+
			            tool.StrToExtended(GPSSL[5].Mid(3, 10)) / 60;
		if( GPSSL[6] == "W" ) m_dfGPSInfoEast *= -1;//<=====�ǉ�


		if(m_nCountry == COUNTRY_KOREA && bDemo == FALSE){			//�؍���GPS��M�@��WGS84�g�p
			 HlpWGS84_Tokyo(&m_dfGPSInfoEast,&m_dfGPSInfoNorth);	//WGS84���x�b�Z���ɕϊ�
		}

		//�X�s�[�h
		m_dfGPSInfoSpeed = tool.StrToExtended(GPSSL[7]) * 1.852;	
		//�A���O��
		if( m_dfGPSInfoSpeed > 5 ) {
			m_dfGPSInfoAngle = tool.StrToExtended(GPSSL[8]);			
		}
//m_dfGPSInfoAngle=0;
//    MakeHtml(TRUE);
//    CheckDistance;
//		S.Format(L" %3dKm/h", (int)floor(m_dfGPSInfoSpeed));
//		S += (L"    "+GPSModeText[m_nGPSInfoStatus]);
//		S += (L"  E:"+tool.RealToStr(m_dfGPSInfoEast ));
//		S += (L"  N:"+tool.RealToStr(m_dfGPSInfoNorth));
//    SetDlgItemText(IDC_STLabel1,  S);
//	Deb2(S);
		return  TRUE;

	}

	return  FALSE;
}
//***********************************************************************************
//*	GPS�f�[�^�f�R�[�h
//***********************************************************************************
BOOL CGPS::DecodeGps2(void)
{
	CTool tool;
	int		H;
	BYTE	B, Status;
	double	Spd;
	CString S;

	if( (ReceiveCount != 80 ) &&
        (ReceiveCount != 85 ) ) return FALSE;

	Status =  (ReceiveBuff[78]);
	if( (Status & 0x02) == 0x02 ) m_nGPSInfoStatus = 2;  // 2D Mode
	if( (Status & 0x04) == 0x04 ) m_nGPSInfoStatus = 4;  // 3D Mode
	if( (Status & 0x01) == 0x01 ) m_nGPSInfoStatus = 1;  // ����

  m_dfGPSInfoNorth = (((ReceiveBuff[ 1]) << 21) +
                   ((ReceiveBuff[ 2]) << 14) +
                   ((ReceiveBuff[ 3]) <<  7) +
                    (ReceiveBuff[ 4])             ) / (1000*60.0) ;
  m_dfGPSInfoEast  = (((ReceiveBuff[ 5]) << 21) +
                   ((ReceiveBuff[ 6]) << 14) +
                   ((ReceiveBuff[ 7]) <<  7) +
                    (ReceiveBuff[ 8])             ) / (1000*60.0) ;
  H             = (((ReceiveBuff[ 9]) << 14) +
                   ((ReceiveBuff[10]) <<  7) +
                    (ReceiveBuff[11])             );
  Spd           = (((ReceiveBuff[12]) <<  7) +
                    (ReceiveBuff[13])         ) / (10/3.6);
//�k���O�x�Ŏ��v���
  if( Spd > 2 ) 
    m_dfGPSInfoAngle = (((ReceiveBuff[14]) <<  7) +
                      (ReceiveBuff[15])         ) / (10.0);
  B =                 (ReceiveBuff[ 9]);
  if( (B & 0x40) != 0 ) { // ��
    H = H | 0xFFE00000;
  }
  m_dfGPSInfoSpeed = floor(Spd);

    S.Format(L"  %3dKm/h", (int)floor(m_dfGPSInfoSpeed));
    S += (L"    "+GPSModeText[m_nGPSInfoStatus]);
	S += (L"  E:"+tool.RealToStr(m_dfGPSInfoEast ));
    S += (L"  N:"+tool.RealToStr(m_dfGPSInfoNorth));
//	ED->SetWindowText(S);
//    SetDlgItemText(IDC_STLabel1,  S);
/*{{
	int i;
	CString C;
	C = "";
	for( i = 1; i<=8;++i){
		S.Format(L"%2.2x:", ReceiveBuff[i]);
		C += S;
	}
	Deb2(C);
}}*/
//  if( m_nGPSInfoStatus == 1 ) return FALSE;
//  MakeHtml(TRUE);
//  CheckDistance;

//  SpeedLabel.Caption = Format("%3dKm/h",   [Speed]);
//  HLabel.Caption = CText.Altitude + Format("%4dm",   [H]);

  return TRUE;
}
//(******************************************************************************)
//*	GPS�A���O������ʃA���O���Ċl��
int CGPS::GetAngle()
{
	return int((m_dfGPSInfoAngle - 270) + 360) % 360;
}
//(******************************************************************************)
//*	�o�x�ܓx�l��
void CGPS::GetENPoint(double *dfpEW,double *dfpNS)
{
	*dfpEW = m_dfGPSInfoEast;
	*dfpNS = m_dfGPSInfoNorth;
}



/***********************************************************************************
*	GPS��M�C���[�W�쐬
***********************************************************************************/
void CGPS::MakeGPSDataImage(char *cpBuf,double dfEW,double dfNS,int nSpeed,int nAngle)
{
	char tmp[100];
	char crlf[3];
	crlf[0]=0x0d;
	crlf[1]=0x0a;
	crlf[2]=0;

	char cEW = 'E';
	char cNS = 'N';

	if(dfEW < 0){
		cEW = 'W';
		dfEW = fabs(dfEW);
	}

	if(dfNS < 0){
		cEW = 'S';
		dfNS = fabs(dfNS);
	}


	dfEW = HlpGPSFormCnv(dfEW);		//GPS���W�t�H�[�}�b�g�ϊ�
	dfNS = HlpGPSFormCnv(dfNS);		//GPS���W�t�H�[�}�b�g�ϊ�

	sprintf(cpBuf,"$GPGGA,091649.4,%0.4lf,%c,%0.4lf,%c,1,4,3.29,-0041,M,,M,,*4B",dfNS,cNS,dfEW,cEW);
	strcat(cpBuf,crlf);
	strcat(cpBuf,"$GPGSA,A,3,05,09,21,23,26,29,15,,,,,,2.17,1.35,1.69*0A");
	strcat(cpBuf,crlf);
	strcat(cpBuf,"$GPGSV,2,1,8,05,32,146,43,09,69,050,43,00,34,207,00,21,34,315,43*40");
	strcat(cpBuf,crlf);
	strcat(cpBuf,"$GPGSV,2,2,8,23,82,318,45,26,28,075,40,29,25,286,42,15,20,311,34*4D");
	strcat(cpBuf,crlf);
	sprintf(tmp,"$GPRMC,095357.4,A,%0.4lf,%c,%0.4lf,%c,%04.1lf,%d,060700,,E*67",dfNS,cNS,dfEW,cEW,(double)(nSpeed)/1.852,nAngle);
	strcat(cpBuf,tmp);
	strcat(cpBuf,crlf);

}

/***********************************************************************************
*	GPS���W�t�H�[�}�b�g�ϊ�
*	126.983917�x��126�x59.03502�x(12659.03502)�ɕϊ�
***********************************************************************************/
double CGPS::HlpGPSFormCnv(double dfVal)
{
	double df1 = floor(dfVal);	//������
	double df2 = dfVal - df1;	//������

	return df1 * 100 + df2 * 60;
}


/***********************************************************************************
*	WGS84���x�b�Z���ɕϊ�(�덷�T�����x)
***********************************************************************************/
void CGPS::HlpWGS84_Tokyo(double *dfpEW,double *dfpNS)
{
	double dfWGS84EW = *dfpEW;
	double dfWGS84NS = *dfpNS;

	*dfpNS = dfWGS84NS + 0.00010696 *dfWGS84NS  - 0.000017467*dfWGS84EW -0.0046020;
	*dfpEW = dfWGS84EW + 0.000046047*dfWGS84NS + 0.000083049*dfWGS84EW -0.010041;

}



