// FileText.cpp: implementation of the CFileText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AutoPC.h"
#include "FileText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileText::CFileText()
{

}

CFileText::~CFileText()
{

}
/***********************************************************************************
*
***********************************************************************************/
int CFileText::GetRec(char *ReceiveBuff,int nBufSize)
{
	int nSize;

	int nPos=0;
	for(;;){
		if(nPos+1 >= nBufSize){
			ReceiveBuff[nPos] = 0;
			AfxMessageBox(L"nBufSize err");
			return -2;
		}
		if(CFile::Read(&ReceiveBuff[nPos],1) < 1){
			return -1;
//			ReceiveBuff[nPos] = 0;
//			nSize = strlen(&ReceiveBuff[0]);
//			break;
		}
		if(ReceiveBuff[nPos] == 0x0d)continue;
		if(ReceiveBuff[nPos] == 0x0a){
			ReceiveBuff[nPos] = 0;
			nSize = strlen(&ReceiveBuff[0]);
			break;
		}
		nPos++;
	}

//	AfxMessageBox((CString)ReceiveBuff);
	return nSize;







}
