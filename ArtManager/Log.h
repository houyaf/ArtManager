#pragma once

// CLog ÃüÁîÄ¿±ê
enum enLog_Type
{
	LOG_MSG    ,
	LOG_MONITOR,

	LOG_MAX
};

class CLog : public CObject
{
public:
	CLog();
	CLog(int iLogType, CTime tLogTime, LPCTSTR szInfo);
	~CLog();

protected:
	CTime     m_tLogTime ;
	int       m_iLogType ;
	CString   m_szLogInfo ;

public:
   CTime Get_LogTime();
   CString Get_LogInfo();
};


