// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AutoPC.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Array tbSTDButton contains relevant buttons of bitmap IDB_STD_SMALL_COLOR
static TBBUTTON tbButtons[] = {
	{0, 0,				TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0},
	{0,	ID_GPS_RUN,		TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{1,	ID_ZOOM_IN,		TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{2, ID_ZOOM_OUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{3, ID_ROUTE_START,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{4, ID_ROUTE_END,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
//	{0, 0,				TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{5, ID_ROUTE_SEARCH,TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{6, ID_MY_MAP,		TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
//	{0, 0,				TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0, -1},
	{7, ID_MAP_MAIL,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, -1},
	{0, 0,				TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0, 0,  0}
};
const int nNumButtons = sizeof(tbButtons)/sizeof(TBBUTTON);
const int nNumImages = 8;
const DWORD dwAdornmentFlags = 0; // exit button

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_MESSAGE(WM_EVENT, CMainFrame::OnEvent)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Add the buttons and adornments to the CommandBar.
	if (!InsertButtons(tbButtons, nNumButtons, IDR_MAINFRAME, nNumImages) ||
	    !AddAdornments(dwAdornmentFlags))
	{
		TRACE0("Failed to add toolbar buttons\n");
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{

//	cs.x=0;
//	cs.y=0;
//	cs.x= GetSystemMetrics(SM_CXSCREEN);
//	cs.y= GetSystemMetrics(SM_CYSCREEN);
	
	cs.x=0;
	cs.y=0;
	cs.cx=DISP_CX;
	cs.cy=DISP_CY;


	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
/****************************************************************************
*  イベント通知
*  wParam:DLGｲﾝﾃﾞｯｸｽ
*  lParam:いろいろ
*****************************************************************************/
LONG CMainFrame::OnEvent(UINT wParam, LONG lParam)
{
	switch(wParam){
		case EV_APP_EXIT:				//終了
			CFrameWnd::OnClose();
			break;
		default:return 0L;
	}

	return 0L;
}
/****************************************************************************
*  終了
* viewで終了処理を行うためここではやらない
*****************************************************************************/
/*void CMainFrame::OnClose() 
{
//	CView* pView = GetActiveView();				//viewへのﾎﾟｲﾝﾀ獲得 
//	pView->PostMessage(WM_EVENT,EV_APP_EXIT,(LONG)this);



	CFrameWnd::OnClose();
}
*/
