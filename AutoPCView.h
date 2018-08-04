// AutoPCView.h : interface of the CAutoPCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
#define AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "DlgMenu.h"
//#include "DlgWait.h"
//#include "Trace.h"
//#include "Search.h"
//#include "Search2.h"
#include "SearchID.h"
//#include "MapLevel.h"
//#include "Route.h"
#include "Dial.h"
#include "RasDial.h"
#include "RasEntry.h"



//#include "DataBase.h"
#include "Road.h"
#include "Line.h"
#include "Text.h"

#include "DrawTool.h"
#include "GPS.h"
#include "VView.h"
//#include "TCPSoc.h"
//#include "CeTCPSoc.h"
#include "Ulp.h"
#include "Tool.h"
#include "CeCommMgr.h"
#include "DriveLog.h"
#include "DlgInfo.h"
#include "DrawThread.h"
#include "Dijkstra.h"

//#include "RouteSearch.h"

class CAutoPCView : public CView
{
protected: // create from serialization only
	CAutoPCView();
	DECLARE_DYNCREATE(CAutoPCView)

// Attributes
public:
	CAutoPCDoc* GetDocument();
	void SetMainStatus(int nType,BOOL bVal);	//��ԃt���O�ݒ�
	BOOL GetMainStatus(int nType);				//��ԃt���O�l��

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPCView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPCView)
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnDemoStart();
	afx_msg void OnDemoStop();
	afx_msg void OnRouteSearch();
	afx_msg void OnRouteClr();
	afx_msg void OnRouteStart();
	afx_msg void OnRouteEnd();
	afx_msg void OnUpdateRouteStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRouteClr(CCmdUI* pCmdUI);
	afx_msg void OnThisPlace();
	afx_msg void OnRouteReSearch();
	afx_msg void OnMymapSet();
	afx_msg void OnMymapGet();
	afx_msg void OnUpdateRouteReSearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDemoStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDemoStop(CCmdUI* pCmdUI);
	afx_msg void OnSearchStruct();
	afx_msg void OnSystem();
	afx_msg void OnSearchCir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LONG OnDlgClose(UINT wParam, LONG lParam);		//�޲�۸޸۰�ޒʒm
	afx_msg LONG OnEvent(UINT wParam, LONG lParam);			//�C�x���g

private:
//-------------�萔-----------------------------------------
#define	TO_INIT					1			//�N�������҂����
#define	TO_DEMO_RUN				2			//�f�����s
#define TO_RAS_CONNECT_CHK		3			//RAS�ڑ��Ď�
//#define	TO_GPS_DRAW				3			//GPS�f�[�^�`��
//#define	TO_THREAD				4			//�X���b�h�I���Ď����
//#define	TO_AUTO_ZOOM			6			//�I�[�g�X�P�[���I�����
//#define	TO_WATCH_KEY			7			//�L�[���͊Ď����
#define	TO_WAIT_DLG_AUTO_CLOSE	8			//WAITDLG�����N���[�Y���
#define	TO_WAIT_THEAD_START		9			//�X���b�h�`��҂����
#define	TO_CYCLE_1				10			//��������1
#define	TO_REROUTE				11			//�ٰċ��Ď����


#define	TO_VAL_INIT				5000		//�N�������҂����
#define	TO_VAL_DEMO_RUN			1000		//�f�����s
#define TO_VAL_RAS_CONNECT_CHK	2000		//RAS�ڑ��Ď�

//#define	TO_VAL_GPS_DRAW			1000		//GPS�f�[�^�`��
//#define	TO_VAL_THREAD			500			//�X���b�h�I���Ď����
#define	TO_VAL_AUTO_ZOOM		60000		//�I�[�g�X�P�[���I�����
//#define	TO_VAL_WATCH_KEY		1000		//�L�[���͊Ď����
#define	TO_VAL_WAIT_THEAD_START	1000		//�X���b�h�`��҂����
#define	TO_VAL_CYCLE_1			1000		//��������1
#define	TO_VAL_REROUTE			10000		//�ٰċ��Ď����

//-------------�ϐ�-----------------------------------------
	CString m_strDataPath;			//�f�[�^�p�X��
	int m_nCountry;					//���썑

	RECT m_RECTClient;				//����ʻ���
	RECT m_RECTVview;				//���z��ʻ���
	double m_dfClientCenterEW;		//����ʒ��S�o�x
	double m_dfClientCenterNS;		//����ʒ��S�ܓx
	double m_dfClientCenterSaveEW;	//����ʒ��S�o�x�ۑ��p
	double m_dfClientCenterSaveNS;	//����ʒ��S�ܓx�ۑ��p


	CPoint m_POClientCenter;		//����ʒ��S
	int	 m_nClientCenterOffsetCar;	//���S����̎��ԕ\���I�t�Z�b�g
	CPoint m_POClientCenter_V1;		//���z��ʒ��S
	CPoint m_POClientScrollMax;		//����ʃX�N���[���ő�T�C�Y
	CPoint m_POClientScrollMaxV2Draw;//����ʃX�N���[��V2�`��v���T�C�Y
	CPoint m_POClientScroll;		//����ʃX�N���[����
	CPoint m_POClientScrollSave;	//����ʃX�N���[���ʕۑ��p



	int m_nBkColor;					//�w�i�F
	int m_nXOffset;					//���z���
	int m_nYOffset;					//

	int m_nMapLevel;
//	CDlgMenu	*m_pDlgMenu;
//	CDlgWait	*m_pDlgWait;
	CDlgInfo	*m_pDlgInfo;


//	CTrace		*m_pTRACE;
//	CSearch		*m_pSearch;
//	CSearch2	*m_pSearch2;
	CSearchID	*m_pSearchID;
//	CMapLevel	*m_pMapLevel;
//	CRoute		*m_pRoute;
	CDial		*m_pDial;
	CRasEntry	*m_pRasEntry;



	int m_nTestCnt;
//	BOOL m_bRs232cDraw;			//RS232C���R�[�h�`��t���O
	int m_nMapMachOffset;
	double m_dfMapMachOffsetEW;
	double m_dfMapMachOffsetNS;
	double m_dfSaveGPSEW;
	double m_dfSaveGPSNS;


//	int m_nMapMachAngle;
	int m_nStartAngle;
	BOOL m_bTRACE;
	int	m_nSocReceiveSize;
	BOOL m_bSocReceiveFault;
	int m_nSocReqType;
	CString m_strSearchMsg;
	CString m_strSearchMsg2;
	int m_nSaveAngle;
	BOOL m_bDemo;
	BOOL m_bKeyUP;
	BOOL m_bDemoRun;
	int m_nDriveLogWriteCnt;
	int	m_nKeyInSleepCnt;
	int m_nGPSSpeed;
	BOOL m_bAutoZoomIn;
	BOOL m_bChgMapTimer;
	int m_nSaveMapLevel;
	BOOL m_bAppExit;
	BOOL m_bWaitThreadStart;
	double m_dfRouteEW;				//���[�g�������W
	double m_dfRouteNS;				//���[�g�������W
	BOOL m_bReceiveGPS;				//GPS��M�L��

	CString m_strID;
	CString m_strDial;
	CString m_strWaitDlgMsg;
	BOOL m_bOnline;

	double	m_dfChkGPS_EW;
	double	m_dfChkGPS_NS;
	int m_nChkGPSChkFlg;

	BOOL m_bInitOK;
	int m_nRouteOnOff;		//0:���[�g�ݒ�Ȃ� 1:���[�g�ݒ肠��
	int m_nSendIDCnt;		//ID���M�Ǘ��J�E���^

	double m_dfRouteStartEW;	//���[�g�����ʒu�蓮�ݒ�l	
	double m_dfRouteStartNS;
	BOOL m_bRas;
	CString m_strRasEntryName;

	double dfSaveGPSEW;		//�O���M�ʒu�ۑ�

	int m_nCircumferenceListCnt;			//���ӌ���ITEM��
	int *m_npCircumferenceListBuf;			//���ӌ���ITEMؽ���̧�ւ��߲��(EW,NS....�̏���)
	CString *m_strpCircumferenceListBuf;	//���ӌ���ITEMؽ���̧�ւ��߲��(����)



	CDijkstra m_Dijkstra;		//�_�C�N�X�g��
//	int m_nLastDistance;		//�c�苗��
//	int m_nSaveLastDistance;	//�c�苗��(�ۑ��p)

	char m_zEnv[4];				//�V�X�e�����ݒ�l�@0000 0=ON 1=OFF
								//                    0�޲Ė�:ϯ��ϯ�&��ިݸޱ���
								//                    1�޲Ė�:��Ľ�����ݼ�
								//                    2�޲Ė�:����ٰ�
								//                    3�޲Ė�:�����ē�

	int m_nScaleDownPoint;		//�I�[�g�X�P�[���A�b�v�ɑ΂���_�E���|�C���g
//	BOOL m_bScaleUp;			//�I�[�g�X�P�[�����t���O
	int m_nNearNode;			//��ԋ߂��m�[�h�ԍ�
	int m_nDistanceTMP;			//�c�苗��
	int m_nNextDistance;		//��ɰ�ނ܂ł̋����iɰ�ފԁj

	BOOL m_bRerouteTimer;		//reroute�N����ώ��s����׸�
	int	m_nPassNode;			//�ʉߍς݃m�[�h
	int m_nNextNode;			//���m�[�h
	int m_nNodeTracePos;		//�m�[�h���z��ʒu
	int m_NextTurn;				//���E���܃m�[�h�̉�]�p�x
	int m_NextTurnDistance;		//���E���܃m�[�h�܂ł̋���
	BOOL m_b100m;				//100m��O�ʉߒ�
	int m_nSave100mPos;			//100m��O�ʉ�pos(�O��ʂ����ʒu)
	int	m_nEWScaleUpPoint;		//�X�P�[���_�E���|�C���g����p
	int	m_nNSScaleUpPoint;

//--------��ԃt���O---------------------------------------------------
	BOOL m_bMainStatus[ST_ITEM_MAX];

	
	int m_nMenuStatusRoute;	//���j���[�C�l�[�u��/�f�B�Z�[�u����ԁi���[�g�֘A�j

//-------------�N���X-----------------------------------------
	CVView	m_VView0;				//�����(�A�C�R����������Ȃ��悤��v1->v0)
	CVView	m_VView1;				//�����<-1(4)<-2(3)
	CVView	m_VView2;
	CVView	m_VView3;				//MapMach�p
	CVView	m_VView4;


	CRoad		*m_pRoad;
	CIcon		*m_pIcon;
	CText		*m_pText;
	CPoly		*m_pPoly;
	CLine		*m_pLine;


	CDrawTool	m_DrawTool;
//	CDataBase	*m_pDB;
	CPoint		m_poClick;
	CGPS *m_pGPS;
	CTool m_Tool;

	CDriveLog	*m_pDriveLog;

	CRasDial m_Ras;



//-------------�N���X�|�C���^-----------------------------------------
	CWnd *m_pWndMainFrame;		//���C���t���[���|�C���^
	CUlp *m_pSoc;
	CDrawThread	*m_pThread;
//	CRouteSearch *m_pRS;


//-------------�A�C�R���n���h��-----------------------------------------
	HICON	m_hCarIcon;
	HICON	m_hGPS_NON_Icon;
	HICON	m_hGPS_2D_Icon;
	HICON	m_hGPS_3D_Icon;
	HICON	m_hSearch_Icon;	
	HICON	m_hCross_Icon;	
	HICON	m_hArow_Icon;	
	HICON	m_hMap01_Icon;	
	HICON	m_hMap02_Icon;	
	HICON	m_hMap03_Icon;	
	HICON	m_hMap04_Icon;	
	HICON	m_hMap05_Icon;	
	HICON	m_hMap06_Icon;	
	HICON	m_hMap07_Icon;	
	HICON	m_hMap08_Icon;	
	HICON	m_hMap09_Icon;	
	HICON	m_hMap10_Icon;	
	HICON	m_hGoal_Icon;	
	HICON	m_hPoint_Icon;	
	HICON	m_hNode_Icon;
	HICON	m_hNextNode_Icon;
	
	HICON	m_hDemo_Icon;	
	HICON	m_hSound_Icon;	
//	HICON	m_hDistance2_Icon;	
	HICON	m_hOnline_Icon;	
	HICON	m_hOffline_Icon;
	HICON	m_hDirection_Icon[8];
	




//-------------�o�t�@----------------------------------------------
	char	m_SocBuf[BUF_SIZE];
	char m_cpBufGPSRec[BUF_SIZE];
	char *m_p232cReceiveBuf;
	struct_SearchID m_StructSearchID;	//ID�����\����
//-------------�y���p�֐�-----------------------------------------
	BOOL HlpMenuEnable(int nMenuType,int nMenuNo);	//���j���[�C�l�[�u��/�f�B�Z�[�u����Ԋl��
	BOOL SetFileFolder();							//������ɍ������t�@�C���t�H���_����ݒ�
	void HlpInit();
	void HlpAutoDemo(double dfEW,double dfNS,int nAngle);				//�����f�����s
	BOOL HlpScaleUpPoint(int nEW,int nNS);			//�X�P�[���_�E���|�C���g����
    BOOL HlpVPaint();								//���z��ʕ`��
    void HlpVPaint3();								//���z���3�`��
	void HlpZConv(double *dfpEW,double *dfpNS,POINT *popView,POINT *popVView);	//���W�ϊ�
    void HlpReDraw();				//���z��ʂ�����ʂɺ�߰
	void HlpV0Draw();				//���z���0���쐬
	int HlpMapMach();
	void HlpClickSearchIcon();		//���ӌ����A�C�R���N���b�N
	void HlpScroll(CPoint point,int nAngle=0xffff);	//��ʃX�N���[��
	BOOL HlpChkReDraw(CPoint point);	//����ʕ`��\����
	BOOL HlpChkDrawV(CPoint poVView);//���z��ʕ`��K�v������
	void HlpCurScroll(int nX,int nY);
	BOOL HlpCurScrollChk();
	long HlpGetRecords();
	void HlpRs232cStart();		//RS232C�J�n
	void HlpRs232cStop();		//RS232C��~
	BOOL HlpRs232cReceive();	//RS232C��M
	void HlpRs232cDraw();		//RS232C���R�[�h��M�I�̕`��

	void HlpSocConnectAndSend(int nSocReqType);
//	void HlpSocReceiveAndClose();
	int  HlpMakeRouteSetData(char *cpBuf,int nType);
//	BOOL HlpSocConnectAndSendG1G2(CString *strpSQL);
	void HlpTRACE(CString str,int level  =0 );
	void HlpTRACE(int nVal);
	void HlpGetCurEN(double *dfpEW,double *dfpNS);		//�J�[�\���ʒu�̈ܓx�o�l��
	void HlpSetRouteStartEN();				// ���[�g�����ʒu�蓮�ݒ�l	
	void HlpSetDriveLog();					//�O�Փ_�\��
	void HlpGetDriveLog();					//�O�Փ_�\��

	BOOL HlpV2DrawThreadCreate();				//V2�`��X���b�h�J�n
	BOOL HlpV2DrawThreadDelete(BOOL bForce=FALSE);	//V2�`��X���b�h�I��
//	CWinThread	*m_pThread;


	void HlpMemCard2Windows(CString strFname);		//��ض��ނ��windows�f�B���N�g���փR�s�[
	CCeCommMgr *m_pComm;

//	void HlpWaitDlg(BOOL bMode,CString strMsg="");
//	void HlpWaitDlgAutoClose(int nMSec);			//WAITDLG�����N���[�Y�ݒ�
	void HlpSaveENV();
	void HlpLoadENV(double *dfpEW,double *dfpNS,int *npAngle,int *npMapLevel,
							 CString *strpID,CString *strpDial,int *npRoute);
	void HlpSetDefaultEWNS(double *dfpEW,double *dfpNS);//�ܓx�o�x�����l�ݒ�
	void HlpSetCenterOffsetCar(int nType=0);
//	void HlpChgMapLevel(int nVal); 
	void HlpConnectOffline(int nSocReqType);		//offline���̏���
	char* CStringToChar2(CString Str,char* m_s);
	void HlpOfflineSSearch(char *cpKey,int nKeyLen);	//��ײݎ{�݌���
//	BOOL HlpChkGPSReceiveEWNS(double dfEW,double dfNS);	//GPS��M�ʒu�Ó�������
//t HlpGetDrectionPos();						//���p�A�C�R���ϐ��l��
	int HlpGetTurnCourse(int nAngle);				//��]�����l��
	void HlpDispInit();								//�������
	void HlpDispInitBMP(int nX,int nY,int nID);		//
	void HlpSendID();								//ID���M
	BOOL HlpDemoData();								//���[�g�`��O�Ղ���f���p��GPS��M�f�[�^�쐬 
//-----------�}�g���N�X�֐�------------------------------------------------------
	int m_nStatus;												//��ظ���Ԓl
	void HlpS1E1();
	void HlpS1E2();
	void HlpS1E3();
	void HlpS1E4();
	void HlpS1E5();
	void HlpS1E6();
	void HlpS1E7();
	void HlpS1E8();
	void HlpS1E9();
	void HlpS1E10();
	void HlpS1E11();
	void HlpS1E12(int nMapLevel);
	void HlpS1E13(int nMapLevel);
	void HlpS1E14();
	void HlpS1E15();
	void HlpS1E16(int nSocReqType);
	void HlpS1E17();
	void HlpS1E18();
	void HlpS1E19();
	void HlpS1E20();
	void HlpS1E21();
	void HlpS1E22();
	void HlpS1E23();
	void HlpS1E24();
	void HlpS1E25(int nVal);
	void HlpS1E26();
	void HlpS1E27();
	void HlpS1E28(int nEntryPos);
	void HlpS1E29();
	void HlpS1E101();
	void HlpS1E102();
	void HlpS1E103();
	void HlpS1E104();
	void HlpS1E105();
	void HlpS1E106();
	void HlpS1E107();
	void HlpS1E108();
	void HlpS1E109();
	void HlpS2E1();
	void HlpS2E2();
	void HlpS2E3();
	void HlpS2E4();
	void HlpS2E5();
	void HlpS2E6();
	void HlpS2E7();
	void HlpS2E8();
	void HlpS2E9();
	void HlpS2E10();
	void HlpS2E11();
	void HlpS2E12();
	void HlpS2E13();
	void HlpS2E14();
	void HlpS2E15();
	void HlpS2E16();
	void HlpS2E17();
	void HlpS2E18();
	void HlpS2E19();
	void HlpS2E20();
	void HlpS2E21();
	void HlpS2E22();
	void HlpS2E23();
	void HlpS2E24();
	void HlpS2E25();
	void HlpS2E26();
	void HlpS2E27();
	void HlpS2E28();
	void HlpS2E29();

	void HlpS2E101();
	void HlpS2E102();
	void HlpS2E103();
	void HlpS2E104();
	void HlpS2E105();
	void HlpS2E106();
	void HlpS2E107();
	void HlpS2E108();
	void HlpS2E109();
	void HlpS3E1();
	void HlpS3E2();
	void HlpS3E3();
	void HlpS3E4();
	void HlpS3E5();
	void HlpS3E6();
	void HlpS3E7();
	void HlpS3E8();
	void HlpS3E9();
	void HlpS3E10();
	void HlpS3E11();
	void HlpS3E12();
	void HlpS3E13();
	void HlpS3E14();
	void HlpS3E15();
	void HlpS3E16();
	void HlpS3E17();
	void HlpS3E18();
	void HlpS3E19();
	void HlpS3E20();
	void HlpS3E21();
	void HlpS3E22();
	void HlpS3E23();
	void HlpS3E24();
	void HlpS3E25();
	void HlpS3E26();
	void HlpS3E27();
	void HlpS3E28();
	void HlpS3E29();

	void HlpS3E101();
	void HlpS3E102();
	void HlpS3E103();
	void HlpS3E104();
	void HlpS3E105();
	void HlpS3E106();
	void HlpS3E107();
	void HlpS3E108();
	void HlpS3E109();


};

#ifndef _DEBUG  // debug version in AutoPCView.cpp
inline CAutoPCDoc* CAutoPCView::GetDocument()
   { return (CAutoPCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPCVIEW_H__6FFC58C4_181C_11D5_894D_0040CA1F5D30__INCLUDED_)
