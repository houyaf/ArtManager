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

	//清除LOG
	void ClearLog();

	//显示Log,Debug
	void ShowLogs();

	//新增Log
	int AddMsgLog(CLog* pLog);

	//新增Log
	int AddMonitorLog(CLog* pLog);

	//新增Log
	int AddLog(int iType, LPCSTR szMsg);

	//删除设备
	int DeleteLog(CLog *pLog);

	


};


