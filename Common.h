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
	void	SetCenter(long lx,long ly);			//センター座標設定
	void	SetBase(double dfx,double dfy);		//ベース座標設定
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
	void	SetAngle(int nAngle=90);		//アングル設定
	int		GetAngle();						//アングル獲得
	BOOL	ChkAngle(int nAngle,int nReDrawAngle);			//アングル変化検査
	void	SinCos(const double a, double *S, double *C);
	double	cos(const double a);
	double	sin(const double a);
	void	DrawSituation(CDC* pDC);
//	void	PaintMapUnit(int nLevel,CDC *pDC, CRect rect);//縮尺表示
	char*	CStringToChar(CString Str);
	void	GetDispArea2(double dfClientCenterEW,double dfClientCenterNS,
							  double *XS, double *YS, double *XE, double *YE);
	CString RealToStr2(const double Num);

	double RadToDeg(const double Radians);	//ラジアン→度に変える
	int PointToGpsAngle(const double EW0,const double NS0,const double EW1,const double NS1);//EW0,NS0を基点にEW1,NS1方向のＧＰＳ角度を求める。
	POINT XYPoint(const double RX, const double RY);				//緯度、経度をＸＹ座標にする
	void XYToEN(const int X, const int Y, double *E, double *N);	//ＸＹ座標を緯度、経度にする
	int DecodeLine(const double EW0, const double NS0,const double EW1, const double NS1);//直線２点間の緯度経度をｎ分割した座標（緯度経度）を求める
	double DemoEW[500];//とおりあえず500
	double DemoNS[500];//ここにSaveする
	POINT DistancePoint(const int EW0, const int NS0,const int EW1, const int NS1,const int Distance);//直線２点間の緯度経度をｎ分割した座標（緯度経度）を求める

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
