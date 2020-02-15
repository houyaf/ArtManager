// Log.cpp : 实现文件
//

#include "stdafx.h"
#include "Log.h"


// CLog

CLog::CLog()
{

}

CLog::CLog(int iLogType, CTime tLogTime, LPCTSTR szMsg)
	:m_iLogType(iLogType)
	,m_tLogTime(tLogTime)
	,m_szLogInfo(szMsg)
{

}
CLog::~CLog()
{
}


// CLog 成员函数
CTime CLog::Get_LogTime()
{
	return m_tLogTime;
}
CString  CLog::Get_LogInfo()
{
	return m_szLogInfo;
}