// DrawTool.h: interface for the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWTOOL_H__6A750295_18D8_11D5_894F_0040CA1F5D30__INCLUDED_)
#define AFX_DRAWTOOL_H__6A750295_18D8_11D5_894F_0040CA1F5D30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawTool  
{
public:
	CDrawTool();
	virtual ~CDrawTool();

	void SetIndex(int nIndex);					//インデックス設定
	void Line(CDC *pDC,int nX1,int nY1,int nX2,int nY2,int nW,int nColor);	
	void Box(CDC *pDC,int x1,int y1,int x2,int y2,int nW,int nColor);
	void TextOut(CDC *pDC,int x1,int y1,CString str);
	void Circle1(CDC* pDC, const int CX, const int CY, const int x, const int y);
	void Split9(RECT *pRect,int nNo,int *pnX1,int *pnY1,int *pnX2,int *pnY2);	//9分割座標獲得
	void DistanceTime(double M, double S, int *HH, int *MM);


private:
	int m_nIndex;
//	CPen *m_pOldPen;
//	CPen m_pen1;

};

#endif // !defined(AFX_DRAWTOOL_H__6A750295_18D8_11D5_894F_0040CA1F5D30__INCLUDED_)
