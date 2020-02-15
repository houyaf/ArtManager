
#pragma once

#include "XEvent.h"
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")


enum
{
	E_XSOCKET_SUCCESS,
	E_XSOCKET_TIMEDOUT,
	E_XSOCKET_ABORTED,
	E_XSOCKET_NOMOREDATA,
	E_XSOCKET_SOCKERR
};


class CXSocket
{
protected:

	SOCKET	m_hSocket;

	CXEvent	m_eventNet;
	CXEvent m_eventStop;

	int		m_nLastError;


public:

	CXSocket(void);
	CXSocket(SOCKET hSocket);
	~CXSocket(void);

	bool Init();
	void Uninit();


	////////////////////////////////////////////////////
	bool EventSelect();
	bool Connect(const char* pAddr, unsigned short  uPort);

	bool QConnect(DWORD dwIP, unsigned short  uPort);

	int Recv(char* pBuff, int nLen, int& nLenReceived, DWORD dwTimeOut = 0);
	int Send(const char* pBuff, int nLen, int& nLenSent, DWORD dwTimeOut = 0);
	
	long GetLenDataAvail();
	int GetLastError();
	
	void Close();
	void Abort();
	bool IsStopped();
};
