// LogManager.cpp : ʵ���ļ�
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

//���log����
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

//��ʾLOG����,Debug
void CLogManager::ShowLogs()
{

}

//�����豸
int CLogManager::AddMsgLog(CLog* pLog)
{
	m_MsgLogList.AddTail(pLog);
	return 1;
}

//����Log
int CLogManager::AddMonitorLog(CLog* pLog)
{
	m_MonitorLogList.AddTail(pLog);
	return 1;

}

//�����豸
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

//ɾ���豸
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

