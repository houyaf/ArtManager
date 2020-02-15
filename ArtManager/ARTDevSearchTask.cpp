/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTDevSearchTask.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: Search Task任务类实现
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "ARTDevSearchTask.h"
#include "ARTSearchDlg.h"



IMPLEMENT_DYNCREATE(CARTDevSearchTask, CARTUIThread)

CARTDevSearchTask::CARTDevSearchTask(void)
{
	
}


CARTDevSearchTask::~CARTDevSearchTask(void)
{

}



BOOL CARTDevSearchTask::InitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	return TRUE;
}

void CARTDevSearchTask::VerfyIPRange()
{
	
}

/**************************************************************************************************
函 数 名 :OnSearch
功能描述 :对话框搜索消息处理
输入参数 :ip范围
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::OnSearch(WPARAM wParam,LPARAM lParam)
{
	CARTSearchDlg *pDlg = (CARTSearchDlg *)m_pOwner;
	CDevManager   *pDevManager = pDlg->GetDevManger();
	CString        szProgressInfo;
	bool           bRET;

	DWORD          dwIP1           = 0;
	DWORD          dwIPMask1       = 0;
	DWORD          dwIP2           = 0;
	DWORD          dwIPMask2       = 0;
	DWORD          dwIP3           = 0;
	DWORD          dwIPMask3       = 0;
	DWORD          dwIP4           = 0;
	DWORD          dwIPMask4       = 0;

	ASSERT(pDlg);
	ASSERT(pDevManager);

	//界面显示进度信息
	//szProgressInfo.Format("开始搜索......");
	//pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

	//根据扫描类型设定开始搜索
	switch (m_iSearchType)
	{
		//根据本地网卡IP及子网掩码得到子网进行扫描，注意最多限定4个网卡，对应4个子网
		case DEVICE_SEARCH_BY_IPMASK:

			ASSERT(m_dwSearchIP !=0);
			ASSERT(m_dwIPMask   !=0);

			bRET = GetLocalIPandMask(&dwIP1, &dwIPMask1, &dwIP2, &dwIPMask2, &dwIP3, &dwIPMask3, &dwIP4, &dwIPMask4);

			if ((dwIP1 != 0) && (dwIPMask1 != 0)) 
			{
				m_dwSearchIP_S = (dwIP1 & dwIPMask1) + 1;
				m_dwSearchIP_E = (m_dwSearchIP_S | 0x000000FF) - 1;
				bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);
				ASSERT(bRET);
			}

			if ((dwIP2 != 0) && (dwIPMask2 != 0)) 
			{
				m_dwSearchIP_S = (dwIP2 & dwIPMask2) + 1;
				m_dwSearchIP_E = (m_dwSearchIP_S | 0x000000FF) - 1;
				bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);
				ASSERT(bRET);
			}

			if ((dwIP3 != 0) && (dwIPMask3 != 0)) 
			{
				m_dwSearchIP_S = (dwIP3 & dwIPMask3) + 1;
				m_dwSearchIP_E = (m_dwSearchIP_S | 0x000000FF) - 1;
				bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);
				ASSERT(bRET);
			}

			if ((dwIP4 != 0) && (dwIPMask4 != 0)) 
			{
				m_dwSearchIP_S = (dwIP4 & dwIPMask4) + 1;
				m_dwSearchIP_E = (m_dwSearchIP_S | 0x000000FF) - 1;
				bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);
				ASSERT(bRET);
			}

			break;

	   //根据IP范围进行扫描
		case DEVICE_SEARCH_BY_IPRANGE:

			ASSERT(m_dwSearchIP_S !=0);
			ASSERT(m_dwSearchIP_E !=0);

			if (m_dwSearchIP_E <= m_dwSearchIP_S)
			{
				m_dwSearchIP_E = m_dwSearchIP_S;
			}

			//扫描
			bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);

			break;

		//根据IP行扫描
		case DEVICE_SEARCH_BY_IP:

			ASSERT(m_dwSearchIP !=0);

			m_dwSearchIP_E = m_dwSearchIP_S = m_dwSearchIP ;

			//扫描
			bRET = ScanWithSelect(m_dwSearchIP_S, m_dwSearchIP_E);
			break;
		default:
			break;
	}

	//发送扫描完成消息
	PostMessage(pDlg->m_hWnd, WM_COMPLETE, 0, 0);
}

/**************************************************************************************************
函 数 名 :ScanWithConnect
功能描述 :扫描设备，使用同步阻塞connect，逐个连接。
输入参数 :ip范围
输出参数 :无
返 回 值 :void
**************************************************************************************************/
bool CARTDevSearchTask::ScanWithConnect(DWORD dwIP_S, DWORD dwIP_E)
{
	CARTSearchDlg *pDlg = (CARTSearchDlg *)m_pOwner;
	CDevManager   *pDevManager = pDlg->GetDevManger();
	CDevice       *pDevice     = NULL ;
	int            iRet ;
	CString        szProgressInfo;

	ASSERT(pDlg);
	ASSERT(pDevManager);

	for (DWORD dwIP= dwIP_S ; dwIP <= dwIP_E ; dwIP++)
	{

		//界面显示进度信息
		szProgressInfo.Format("偿试连接%s......", (LPCTSTR)IP_DW2STR(dwIP));
		pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

		//new 通讯器验证主机是否存在
		CCOMM * pCOMM = new CCOMM(dwIP);
		iRet = pCOMM->VerifyHost();
		if (iRet == 0)
		{
			delete pCOMM;
		}
		else
		{
			//主机连接成功，判断是否设备，如果是，则增加设备并返回设备指针
			pDevice = pCOMM->VerfyDevice();
			
			//不是目标设备
			if (pDevice == NULL)
			{
				delete pCOMM;
			}
			else
			{
				//将发现设备交给设备管理员
				pDevManager->AddDevice(pDevice);

				//将发现的目标设备显示到结果列表
				pDlg->AddFoundDevice(pDevice);

			}
		}
	}
   

	return true;
}



/**************************************************************************************************
函 数 名 :ScanWithSelect
功能描述 :采用非阻塞connect及并发Select主机
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
bool CARTDevSearchTask::ScanWithSelect(DWORD dwIP_S, DWORD dwIP_E)
{
	SOCKET hSocket;
	struct sockaddr_in sin;

	DWORD dwIP ;
	unsigned long ulBlockSwitch;

	int m_nLastError;
	int iRet;

	fd_set writeFds;
	fd_set exceptFds;

	timeval tval;

	SOCKET sockArray[1024];
	int    iSockNum = 0;
	
	DWORD  tStart = GetTickCount();
	DWORD  tEnd = tStart;
	int i;

	CARTSearchDlg *pDlg = (CARTSearchDlg *)m_pOwner;
	CDevManager   *pDevManager = pDlg->GetDevManger();
	CString        szProgressInfo;
    
	ASSERT(pDlg);
	ASSERT(pDevManager);

	memset(sockArray, 0, 1024*sizeof(SOCKET));
	
	if (dwIP_S!= dwIP_E)
	{
	    szProgressInfo.Format("偿试连接<%s>--<%s>......", (LPCTSTR)IP_DW2STR(dwIP_S), (LPCTSTR)IP_DW2STR(dwIP_E));
	    pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);
	}
	else
	{
		szProgressInfo.Format("偿试连接%s......", (LPCTSTR)IP_DW2STR(dwIP_S));
	    pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);
	}


	for (dwIP = dwIP_S; dwIP <= dwIP_E ; dwIP++)
	{
		//界面显示进度信息
		//szProgressInfo.Format("偿试连接%s......", (LPCTSTR)IP_DW2STR(dwIP));
		//pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

		if ((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			m_nLastError = WSAGetLastError();
			return false;
		}

		memset(&sin, 0, sizeof(struct sockaddr_in));

		sin.sin_family = AF_INET;
		sin.sin_port   = htons(g_DevManagermentPort);
		sin.sin_addr.S_un.S_addr = htonl(dwIP);

		//配置为非阻塞模式
		ulBlockSwitch = 1;
		iRet = ioctlsocket(hSocket, FIONBIO, (u_long *)&ulBlockSwitch);
		if(iRet == SOCKET_ERROR)  
		{  
			closesocket(hSocket);  
			hSocket = INVALID_SOCKET;
			return false;  
		}  

		/////////////////////////////////////////////////////////////////////////////
		//connect
		iRet = connect(hSocket, (SOCKADDR*) &sin, sizeof(sin));
		if (iRet == SOCKET_ERROR)
		{
			m_nLastError = WSAGetLastError();

			if (m_nLastError == WSAEWOULDBLOCK)
			{
				sockArray[iSockNum] = hSocket ;
				iSockNum++;
			}
			else
			{
				closesocket(hSocket)    ;
				hSocket = INVALID_SOCKET;
			}
		}
		else
		{
			//Connect成功，对主机进行处理
			ProcessHost(hSocket);
		}
	}

	if (iSockNum<=0)
	{
		return true;
	}

	

	szProgressInfo.Format("正在验证设备，请耐心等待......");
	pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

	while (tEnd - tStart <2000)
	{   
		tEnd = GetTickCount();

		FD_ZERO(&writeFds);
		FD_ZERO(&exceptFds);

		for (i=0 ; i< iSockNum ; i++)
		{
			FD_SET(sockArray[i] , &exceptFds);
			FD_SET(sockArray[i] , &writeFds );
		}

		//Select阻塞等待最大时长1秒
		tval.tv_sec = 5;
		tval.tv_usec= 0;

		iRet = select(iSockNum, NULL, &writeFds, &exceptFds, &tval);

		//异常出错
		if (iRet < 0)
		{
			break;
		}

		//select超时
		if (iRet == 0)
		{
			continue;
		}

		for (i = 0 ; i < iSockNum ; i++)
		{
			//write fd_set 处理
			if (FD_ISSET(sockArray[i], &writeFds))
			{
                 //Connect成功，对主机进行处理
				 ProcessHost(sockArray[i]);

				 //从sockArray中取掉已连接主机
				 sockArray[i] = sockArray[iSockNum-1];
				 FD_CLR(sockArray[i],  &writeFds);
				 FD_CLR(sockArray[i],  &exceptFds);
				 iSockNum--;
			}
			
			//except fd_set 处理
			if (FD_ISSET(sockArray[i], &exceptFds))
			{
				//关闭异常Socket,并从sockArray中清除。
				closesocket(sockArray[i])    ;
				sockArray[i] = sockArray[iSockNum-1];
				FD_CLR(sockArray[i],  &writeFds);
				FD_CLR(sockArray[i],  &exceptFds);
				iSockNum--;
			}
		}
	}

	return true;
}

/**************************************************************************************************
函 数 名 :ScanWithWSAEventSelect
功能描述 :采用非阻塞WSAEventSelect异步事件网络模型扫描主机(备注：没有调试通过)
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
bool CARTDevSearchTask::ScanWithWSAEventSelect(DWORD dwIP_S, DWORD dwIP_E)
{

	CString szProgressInfo;
	WSAEVENT    eventArray[WSA_MAXIMUM_WAIT_EVENTS];  
    SOCKET      sockArray[WSA_MAXIMUM_WAIT_EVENTS];  
    int nEventTotal  = 0;  
	int m_nLastError = 0;
	int iTimeOut     = 0;
  
    USHORT nPort = g_DevManagermentPort;    //设备管理TCP端口号  
	
	SOCKET     hSocket;
	WSAEVENT   hEvent ;

	for (DWORD dwIP= dwIP_S ; dwIP <= dwIP_E ; dwIP++)
	{
		if ((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		{
			m_nLastError = WSAGetLastError();
			return false;
		}
		/////////////////////////////////////////////////////////////////////////////
	    
		hEvent = WSACreateEvent();

		sockaddr_in sa;
		sa.sin_family = AF_INET ;
		sa.sin_addr.S_un.S_addr = htonl(dwIP);
		sa.sin_port = htons(nPort);
	    
		if (WSAEventSelect(hSocket, hEvent, FD_CONNECT |FD_CLOSE) != SOCKET_ERROR)
		{
		
			int rc = connect(hSocket, (SOCKADDR*) &sa, sizeof(sa));
			m_nLastError = WSAGetLastError();

			//连接成功
			if (rc == NO_ERROR ) 
			{
				//处理扫描到地主机
				ProcessHost(hSocket);
			}
			else if(rc == SOCKET_ERROR && m_nLastError == WSAEWOULDBLOCK)
			{//阻塞
				eventArray[nEventTotal] = hEvent;
				sockArray[nEventTotal]  = hSocket;
				nEventTotal++ ;
			}
			else 
			{//错误
				closesocket(hSocket);
				hSocket = INVALID_SOCKET;
			}
		 }
	}

	while (iTimeOut< 3 && nEventTotal > 0)
	{
		int nIndex = ::WSAWaitForMultipleEvents(nEventTotal, eventArray, FALSE, WSA_INFINITE, FALSE);

		nIndex = nIndex -WSA_WAIT_EVENT_0 ;

		for (int i = nIndex ; i < nEventTotal; i++)
		{

			nIndex = ::WSAWaitForMultipleEvents(1, &eventArray[i], TRUE, 1000, FALSE);

			if (nIndex == WSA_WAIT_FAILED)
			{
				continue ;
			}
			else if(nIndex == WSA_WAIT_TIMEOUT)
			{
				iTimeOut++ ;
				continue ;
			}
			else
			{
				WSANETWORKEVENTS netevent;

				::WSAEnumNetworkEvents(sockArray[i], eventArray[i], &netevent);

				if (netevent.lNetworkEvents &FD_CONNECT)
				{
					if (netevent.iErrorCode[FD_CONNECT_BIT] != 0)
					{
						::closesocket(sockArray[i]);
						::WSACloseEvent(eventArray[i]);

						for (int j=i; j<nEventTotal-1; j++)
						{
							eventArray[j]= eventArray[j+1];
							sockArray[j] = sockArray[j+1];
						}
						nEventTotal--;
						i--;
					}
					else
					{
						//处理扫描到地主机
						ProcessHost(hSocket);
					}
				}
				else if(netevent.lNetworkEvents &FD_CLOSE)
				{
					if (netevent.iErrorCode[FD_CLOSE_BIT] == 0)
					{
						::closesocket(sockArray[i]);
						::WSACloseEvent(eventArray[i]);

						for (int j=i; j<nEventTotal-1; j++)
						{
							eventArray[j]= eventArray[j+1];
							sockArray[j] = sockArray[j+1];
						}
						nEventTotal--;
						i--;
					}
				}

			}
		}
	}

	return true;
}

/**************************************************************************************************
函 数 名 :AddNewHost
功能描述 :处理扫描到的主机，验证是否设备，如果是则加入设备管理
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::ProcessHost(SOCKET hSocket)
{
	CDevice       *pDevice     = NULL;
	CARTSearchDlg *pDlg        = (CARTSearchDlg *)m_pOwner;
	CDevManager   *pDevManager = pDlg->GetDevManger();

	ASSERT(pDevManager);
	ASSERT(pDlg);
	ASSERT(hSocket != INVALID_SOCKET);

	///////////////////////////////////////////////////////////////////////
	CCOMM * pCOMM = new CCOMM(hSocket);

	//主机连接成功，判断是否设备，如果是，则增加设备并返回设备指针
	pDevice = pCOMM->VerfyDevice();
			
	//不是目标设备
	if (pDevice == NULL)
	{
		delete pCOMM;
	}
	else
	{
		//将发现设备交给设备管理员
		pDevManager->AddDevice(pDevice);

		//将发现的目标设备显示到结果列表
		pDlg->AddFoundDevice(pDevice);

		
	}

	///////////////////////////////////////////////////////////////////////
}

/**************************************************************************************************
函 数 名 :Set_SearchType
功能描述 :配置搜索类型
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchType(int iSearchType)
{
	m_iSearchType = iSearchType;
}

/**************************************************************************************************
函 数 名 :Set_SearchIP
功能描述 :配置搜索IP
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchIP(DWORD dwIP)
{
	m_dwSearchIP = dwIP;
}


/**************************************************************************************************
函 数 名 :Set_SearchIPRange
功能描述 :配置搜索IP范围
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchIPRange(DWORD dwIP_S, DWORD dwIP_E)
{
	m_dwSearchIP_S = dwIP_S ;
	m_dwSearchIP_E = dwIP_E ;
}

/**************************************************************************************************
函 数 名 :Set_SearchIPMask
功能描述 :配置搜索IP子网掩码
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchIPMask(DWORD dwIPMask)
{
	m_dwIPMask = dwIPMask;
}

BEGIN_MESSAGE_MAP(CARTDevSearchTask, CWinThread)
	//{{AFX_MSG_MAP(CARTDevSearchTask)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	ON_THREAD_MESSAGE(WM_SEARCH, OnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/**************************************************************************************************
函 数 名 :ProcessScanRequest
功能描述 :处理扫描搜索设备的请求
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
bool  CARTDevSearchTask::ProcessScanRequest(DWORD dwIP_S, DWORD dwIP_E)
{
	bool bRet = true ;
	bRet = ScanWithSelect(dwIP_S, dwIP_E);

/*
	for (DWORD dwTmp_IP=dwIP_S; dwTmp_IP<dwIP_E; dwTmp_IP+=127)
	{
		if (dwTmp_IP+127 < dwIP_E)
		{
			bRet = ScanWithSelect(dwTmp_IP, dwTmp_IP+127);
		}
		else
		{
			bRet = ScanWithSelect(dwTmp_IP, dwIP_E);
		}
	}
*/
	return bRet;
}