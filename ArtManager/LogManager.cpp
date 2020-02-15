// LogManager.cpp : 实现文件
//

#include "stdafx.h"
#include "LogManager.h"


// CLogManager
IMPLEMENT_DYNAMIC(CLogManager, CWnd)

CLogManager::CLogManager()
{

}

CLogManager::~CLogManager()
{

}

//清除log数据
void CLogManager::ClearLog()
{
	while (!m_MsgLogList.IsEmpty())
	{
		delete m_MsgLogList.RemoveHead();
	}

	while (!m_MonitorLogList.IsEmpty())
	{
		delete m_MonitorLogList.RemoveHead();
	}
}

//显示LOG数据,Debug
void CLogManager::ShowLogs()
{

}

//新增设备
int CLogManager::AddMsgLog(CLog* pLog)
{
	m_MsgLogList.AddTail(pLog);
	return 1;
}

//新增Log
int CLogManager::AddMonitorLog(CLog* pLog)
{
	m_MonitorLogList.AddTail(pLog);
	return 1;

}

//新增设备
int CLogManager::AddLog(int iType, LPCSTR szMsg)
{
	CLog *pLog = new CLog(iType, CTime::GetCurrentTime(),  szMsg);

	if (iType == LOG_MSG)
	{
		AddMsgLog(pLog);
	}
	else
	{
		AddMonitorLog(pLog);
	}

	return 1;
}

//删除设备
int CLogManager::DeleteLog(CLog *pLog)
{
	return 1;
}

CLogList * CLogManager::Get_MsgLogList()
{
	return &m_MsgLogList ;
}
CLogList * CLogManager::Get_MonitorLogList()
{
	return &m_MonitorLogList;
}

