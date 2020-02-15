#include "stdafx.h"
#include "NetScanEngine.h"


bool NetScanEngine::Init()
{
	WORD    wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD( 2, 2 );


	int nErr = 0;

	if ((nErr = WSAStartup(wVersionRequested, &wsaData)) != 0)
	{
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

bool NetScanEngine::ScanHost(DWORD dwIP_S, DWORD dwIP_E)
{
	

	return true;

}



void NetScanEngine::Uninit()
{
	WSACleanup();
}
