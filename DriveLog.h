// DriveLog.h: interface for the CDriveLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVELOG_H__7DFFB2C3_618C_4550_9E3E_03208C2A2F58__INCLUDED_)
#define AFX_DRIVELOG_H__7DFFB2C3_618C_4550_9E3E_03208C2A2F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define LOG_MAX				1000			//�ő�ۑ���
#define STEP_WAIT_CNT		15				//�Z�b�g����Ԋu

class CDriveLog  
{
public:
	CDriveLog();
	virtual ~CDriveLog();
	void SetPoint(DWORD dwEW,DWORD dwNS);	//�O�Փ_�ݒ�
//	void FileWritePoint(BOOL bPack=FALSE);	//�O�Փ_��������
//	BOOL FileReadPoint();					//�O�Փ_�ǂݏo��
	int GetMaxCnt();						//�ݒ萔�l��
	void Clr();
	void SetDataPath(CString strDataPath);	//�f�[�^�p�X�ݒ�
//-----------�ܓx�o�x�\����
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
