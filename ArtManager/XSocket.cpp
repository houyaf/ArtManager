
#include "stdafx.h"
#include <Ws2tcpip.h>
#include "XSocket.h"


CXSocket::CXSocket(void)
{
	m_hSocket = INVALID_SOCKET;
}

CXSocket::CXSocket(SOCKET hSocket)
	:m_hSocket(hSocket)
{

}

CXSocket::~CXSocket(void)
{
	Close();
}

bool CXSocket::EventSelect()
{
	/////////////////////////////////////////////////////////////////////////////
	//event select
	if (WSAEventSelect(m_hSocket, m_eventNet.GetEvent(), FD_READ | FD_WRITE | FD_CLOSE) != 0)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}

	return true;
}


int CXSocket::GetLastError()
{
	return m_nLastError;
}

bool CXSocket::Init()
{
	WORD    wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD( 2, 2 );


	int nErr = 0;
	m_nLastError = 0;

	if ((nErr = WSAStartup(wVersionRequested, &wsaData)) != 0)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}


	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) 
	{
		WSACleanup();
		return false;
	}


	return true;
}


void CXSocket::Uninit()
{
	WSACleanup();
}


void CXSocket::Close()
{
	if (m_hSocket != INVALID_SOCKET)
	{
		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;
	}
}


void CXSocket::Abort()
{
	m_eventStop.Set();
}


bool CXSocket::Connect(const char *pAddr, unsigned short uPort)
{
	
	m_nLastError = 0;

	//Create
	if ((m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}
	

	/////////////////////////////////////////////////////////////////////////////
	
	sockaddr_in sa;

	addrinfo aiHints;
	addrinfo *aiList = NULL;

	memset(&aiHints, 0, sizeof(aiHints));

	aiHints.ai_family	= AF_INET;
	aiHints.ai_socktype	= SOCK_STREAM;
	aiHints.ai_protocol	= IPPROTO_TCP;

	if (getaddrinfo(pAddr, NULL, &aiHints, &aiList) != 0)
	{
		m_nLastError = WSAGetLastError();

		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;

		return false;
	}

	sa = *((sockaddr_in*)aiList->ai_addr);
	sa.sin_port = htons(uPort);


	/////////////////////////////////////////////////////////////////////////////
	//connect
	if (connect(m_hSocket, (SOCKADDR*) &sa, sizeof(sa)) == SOCKET_ERROR)
	{
		m_nLastError = WSAGetLastError();

		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;

		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	//event select
	if (WSAEventSelect(m_hSocket, m_eventNet.GetEvent(), FD_READ | FD_WRITE | FD_CLOSE) != 0)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}


	return true;
}


bool CXSocket::QConnect(DWORD dwip, unsigned short  uPort)
{

	m_nLastError = 0;

	if ((m_hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}
	/////////////////////////////////////////////////////////////////////////////
	
	sockaddr_in sa;


	sa.sin_family = AF_INET ;
	sa.sin_addr.S_un.S_addr = htonl(dwip);
	sa.sin_port = htons(uPort);
	

	

/////////////////////////////////////////////////////////////////////////////
	//connect
	if (connect(m_hSocket, (SOCKADDR*) &sa, sizeof(sa)) == SOCKET_ERROR)
	{
		m_nLastError = WSAGetLastError();

		closesocket(m_hSocket);
		m_hSocket = INVALID_SOCKET;

		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	//event select
	if (WSAEventSelect(m_hSocket, m_eventNet.GetEvent(), FD_READ | FD_WRITE | FD_CLOSE) != 0)
	{
		m_nLastError = WSAGetLastError();
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	return true;
}




int CXSocket::Send(const char* pBuff, int nLen, int& nLenSent, DWORD dwTimeOut)
{	

_BEGIN:

	int nRet = 0;
	m_nLastError = 0;

	if ((nRet = send(m_hSocket, pBuff, nLen, 0)) > 0 || (m_nLastError = WSAGetLastError()) != WSAEWOULDBLOCK)
	{
		nLenSent = nRet ;
		return E_XSOCKET_SUCCESS;
	}


	///////////////////////////////////////////////////////////////////////////////////

	HANDLE arrHandles[2];

	arrHandles[0] = m_eventNet.GetEvent();
	arrHandles[1] = m_eventStop.GetEvent();

	DWORD dwWaitRes = WaitForMultipleObjects(2, arrHandles, FALSE, dwTimeOut); 
	
	if (dwWaitRes == WAIT_OBJECT_0 + 1)
		return E_XSOCKET_ABORTED;
	else if (dwWaitRes != WAIT_OBJECT_0)
		return E_XSOCKET_TIMEDOUT;


	//////////////////////////////////////////////////////////////////////////////////

	WSANETWORKEVENTS myNetEvents;

	if (WSAEnumNetworkEvents(m_hSocket, m_eventNet.GetEvent(), &myNetEvents) != 0)
	{
		m_nLastError = WSAGetLastError();
		return E_XSOCKET_SOCKERR;
	}

	if ((myNetEvents.lNetworkEvents & FD_WRITE) != FD_WRITE)
	{
		goto _BEGIN;
	}

	if (myNetEvents.iErrorCode[FD_WRITE_BIT] != 0)
		return E_XSOCKET_SOCKERR;


	/////////////////////////////////////////////////////////////////////////////////////

	nLenSent = send(m_hSocket, pBuff, nLen, 0);


	return E_XSOCKET_SUCCESS;
}


int CXSocket::Recv(char* pBuff, int nLen, int& nLenReceived, DWORD dwTimeOut)
{

_BEGIN:

	///////////////////////////////////////////////////////////////////////////////////

	HANDLE arrHandles[2];

	arrHandles[0] = m_eventNet.GetEvent();
	arrHandles[1] = m_eventStop.GetEvent();

	DWORD dwWaitRes = WaitForMultipleObjects(2, arrHandles, FALSE, dwTimeOut); 
	
	if (dwWaitRes == WAIT_OBJECT_0 + 1)
		return E_XSOCKET_ABORTED;
	else if (dwWaitRes != WAIT_OBJECT_0)
		return E_XSOCKET_TIMEDOUT;


	////////////////////////////////////////////////////////////////////////////////////

	WSANETWORKEVENTS myNetEvents;

	if (WSAEnumNetworkEvents(m_hSocket, m_eventNet.GetEvent(), &myNetEvents) != 0)
	{
		m_nLastError = WSAGetLastError();
		return E_XSOCKET_SOCKERR;
	}

	if ((myNetEvents.lNetworkEvents & FD_READ) != FD_READ)
		goto _BEGIN;

	if (myNetEvents.iErrorCode[FD_READ_BIT] != 0)
		return E_XSOCKET_SOCKERR;


	/////////////////////////////////////////////////////////////////////////////////////

	if ((nLenReceived = recv(m_hSocket, pBuff, nLen, 0)) == WSAEWOULDBLOCK)
	{
		nLenReceived = 0;
		return E_XSOCKET_NOMOREDATA;
	}


	return E_XSOCKET_SUCCESS;
}

long CXSocket::GetLenDataAvail()
{
	u_long lLen = 0;
	if (ioctlsocket(m_hSocket, FIONREAD, &lLen) != 0)
	{
		m_nLastError = WSAGetLastError();
		return E_XSOCKET_SOCKERR;
	}


	return lLen;
}