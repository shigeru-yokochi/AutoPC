// DriveLog.h: interface for the CDriveLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVELOG_H__7DFFB2C3_618C_4550_9E3E_03208C2A2F58__INCLUDED_)
#define AFX_DRIVELOG_H__7DFFB2C3_618C_4550_9E3E_03208C2A2F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define LOG_MAX				1000			//最大保存数
#define STEP_WAIT_CNT		15				//セットする間隔

class CDriveLog  
{
public:
	CDriveLog();
	virtual ~CDriveLog();
	void SetPoint(DWORD dwEW,DWORD dwNS);	//軌跡点設定
//	void FileWritePoint(BOOL bPack=FALSE);	//軌跡点書き込み
//	BOOL FileReadPoint();					//軌跡点読み出し
	int GetMaxCnt();						//設定数獲得
	void Clr();
	void SetDataPath(CString strDataPath);	//データパス設定
//-----------緯度経度構造体
	struct StructEN{
		DWORD	dwEW;
		DWORD	dwNS;
	};
	typedef StructEN struct_EN;
	struct_EN *m_pEN;

private:
	int m_nSetPos;
//	int nStepWaitCnt;
	CString m_strDataPath;


	void HlpFileRead();
	void HlpFileWrite();

};

#endif // !defined(AFX_DRIVELOG_H__7DFFB2C3_618C_4550_9E3E_03208C2A2F58__INCLUDED_)
