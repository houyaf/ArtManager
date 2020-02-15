#pragma once


// CLogManager

class CLogManager : public CWnd
{
	DECLARE_DYNAMIC(CLogManager)

public:
	CLogManager();
	virtual ~CLogManager();

public:
	CLogList m_MsgLogList;
	CLogList m_MonitorLogList;

	   

public:

	//LOGList Get;
	CLogList * Get_MsgLogList();
	CLogList * Get_MonitorLogList();
public:

	//���LOG
	void ClearLog();

	//��ʾLog,Debug
	void ShowLogs();

	//����Log
	int AddMsgLog(CLog* pLog);

	//����Log
	int AddMonitorLog(CLog* pLog);

	//����Log
	int AddLog(int iType, LPCSTR szMsg);

	//ɾ���豸
	int DeleteLog(CLog *pLog);

	


};


