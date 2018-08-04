// Common.h: interface for the CCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMON_H__D644B014_1E8C_11D5_8951_0040CA1F5D30__INCLUDED_)
#define AFX_COMMON_H__D644B014_1E8C_11D5_8951_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommon  
{
public:
	CCommon();
	virtual ~CCommon();
	void	SetCenter(long lx,long ly);			//�Z���^�[���W�ݒ�
	void	SetBase(double dfx,double dfy);		//�x�[�X���W�ݒ�
	double	GetBaseX();
	double	GetBaseY();

	void	SetFact(const int L);
	POINT	RoadPoint(const long RX, const long RY);
	POINT	ImagePoint(const long RX, const long RY);
	POINT	GetXYPoint(const int L, const double E, const double N, const int XOff, const int YOff);
	void	GetTileNo(const int L, const double E, const double N, ULONG *SL,int nType);
	double	DegToRad(const double D);
	void	GetENPoint(const int X, const int Y,double *dfpEW,double *dfpNS);
	CPoint BMPPosition(double dfNewEW,double dfNewNS,int nGpsAngle);
	void	SetAngle(int nAngle=90);		//�A���O���ݒ�
	int		GetAngle();						//�A���O���l��
	BOOL	ChkAngle(int nAngle,int nReDrawAngle);			//�A���O���ω�����
	void	SinCos(const double a, double *S, double *C);
	double	cos(const double a);
	double	sin(const double a);
	void	DrawSituation(CDC* pDC);
//	void	PaintMapUnit(int nLevel,CDC *pDC, CRect rect);//�k�ڕ\��
	char*	CStringToChar(CString Str);
	void	GetDispArea2(double dfClientCenterEW,double dfClientCenterNS,
							  double *XS, double *YS, double *XE, double *YE);
	CString RealToStr2(const double Num);

	double RadToDeg(const double Radians);	//���W�A�����x�ɕς���
	int PointToGpsAngle(const double EW0,const double NS0,const double EW1,const double NS1);//EW0,NS0����_��EW1,NS1�����̂f�o�r�p�x�����߂�B
	POINT XYPoint(const double RX, const double RY);				//�ܓx�A�o�x���w�x���W�ɂ���
	void XYToEN(const int X, const int Y, double *E, double *N);	//�w�x���W���ܓx�A�o�x�ɂ���
	int DecodeLine(const double EW0, const double NS0,const double EW1, const double NS1);//�����Q�_�Ԃ̈ܓx�o�x���������������W�i�ܓx�o�x�j�����߂�
	double DemoEW[500];//�Ƃ��肠����500
	double DemoNS[500];//������Save����
	POINT DistancePoint(const int EW0, const int NS0,const int EW1, const int NS1,const int Distance);//�����Q�_�Ԃ̈ܓx�o�x���������������W�i�ܓx�o�x�j�����߂�

private:
	POINT DirectionPoint(const int X, const int Y, const int XC, const int YC);
	long	XCenter,
			YCenter;
	double MakeRad;
	double	XFact,
			YFact,
			LineFact;

	double XBase;
	double YBase;;
	int		m_nMakeAngle;
	char m_s[1024];



};

#endif // !defined(AFX_COMMON_H__D644B014_1E8C_11D5_8951_0040CA1F5D30__INCLUDED_)
