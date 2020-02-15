/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTDevSearchTask.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: Search Task������ʵ��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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
	// TODO: �ڴ����ר�ô����/����û���
	return TRUE;
}

void CARTDevSearchTask::VerfyIPRange()
{
	
}

/**************************************************************************************************
�� �� �� :OnSearch
�������� :�Ի���������Ϣ����
������� :ip��Χ
������� :��
�� �� ֵ :void
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

	//������ʾ������Ϣ
	//szProgressInfo.Format("��ʼ����......");
	//pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

	//����ɨ�������趨��ʼ����
	switch (m_iSearchType)
	{
		//���ݱ�������IP����������õ���������ɨ�裬ע������޶�4����������Ӧ4������
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

	   //����IP��Χ����ɨ��
		case DEVICE_SEARCH_BY_IPRANGE:

			ASSERT(m_dwSearchIP_S !=0);
			ASSERT(m_dwSearchIP_E !=0);

			if (m_dwSearchIP_E <= m_dwSearchIP_S)
			{
				m_dwSearchIP_E = m_dwSearchIP_S;
			}

			//ɨ��
			bRET = ProcessScanRequest(m_dwSearchIP_S, m_dwSearchIP_E);

			break;

		//����IP��ɨ��
		case DEVICE_SEARCH_BY_IP:

			ASSERT(m_dwSearchIP !=0);

			m_dwSearchIP_E = m_dwSearchIP_S = m_dwSearchIP ;

			//ɨ��
			bRET = ScanWithSelect(m_dwSearchIP_S, m_dwSearchIP_E);
			break;
		default:
			break;
	}

	//����ɨ�������Ϣ
	PostMessage(pDlg->m_hWnd, WM_COMPLETE, 0, 0);
}

/**************************************************************************************************
�� �� �� :ScanWithConnect
�������� :ɨ���豸��ʹ��ͬ������connect��������ӡ�
������� :ip��Χ
������� :��
�� �� ֵ :void
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

		//������ʾ������Ϣ
		szProgressInfo.Format("��������%s......", (LPCTSTR)IP_DW2STR(dwIP));
		pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);

		//new ͨѶ����֤�����Ƿ����
		CCOMM * pCOMM = new CCOMM(dwIP);
		iRet = pCOMM->VerifyHost();
		if (iRet == 0)
		{
			delete pCOMM;
		}
		else
		{
			//�������ӳɹ����ж��Ƿ��豸������ǣ��������豸�������豸ָ��
			pDevice = pCOMM->VerfyDevice();
			
			//����Ŀ���豸
			if (pDevice == NULL)
			{
				delete pCOMM;
			}
			else
			{
				//�������豸�����豸����Ա
				pDevManager->AddDevice(pDevice);

				//�����ֵ�Ŀ���豸��ʾ������б�
				pDlg->AddFoundDevice(pDevice);

			}
		}
	}
   

	return true;
}



/**************************************************************************************************
�� �� �� :ScanWithSelect
�������� :���÷�����connect������Select����
������� :��
������� :��
�� �� ֵ :void
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
	    szProgressInfo.Format("��������<%s>--<%s>......", (LPCTSTR)IP_DW2STR(dwIP_S), (LPCTSTR)IP_DW2STR(dwIP_E));
	    pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);
	}
	else
	{
		szProgressInfo.Format("��������%s......", (LPCTSTR)IP_DW2STR(dwIP_S));
	    pDlg->SetPorgressInfo((LPCTSTR)szProgressInfo);
	}


	for (dwIP = dwIP_S; dwIP <= dwIP_E ; dwIP++)
	{
		//������ʾ������Ϣ
		//szProgressInfo.Format("��������%s......", (LPCTSTR)IP_DW2STR(dwIP));
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

		//����Ϊ������ģʽ
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
			//Connect�ɹ������������д���
			ProcessHost(hSocket);
		}
	}

	if (iSockNum<=0)
	{
		return true;
	}

	

	szProgressInfo.Format("������֤�豸�������ĵȴ�......");
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

		//Select�����ȴ����ʱ��1��
		tval.tv_sec = 5;
		tval.tv_usec= 0;

		iRet = select(iSockNum, NULL, &writeFds, &exceptFds, &tval);

		//�쳣����
		if (iRet < 0)
		{
			break;
		}

		//select��ʱ
		if (iRet == 0)
		{
			continue;
		}

		for (i = 0 ; i < iSockNum ; i++)
		{
			//write fd_set ����
			if (FD_ISSET(sockArray[i], &writeFds))
			{
                 //Connect�ɹ������������д���
				 ProcessHost(sockArray[i]);

				 //��sockArray��ȡ������������
				 sockArray[i] = sockArray[iSockNum-1];
				 FD_CLR(sockArray[i],  &writeFds);
				 FD_CLR(sockArray[i],  &exceptFds);
				 iSockNum--;
			}
			
			//except fd_set ����
			if (FD_ISSET(sockArray[i], &exceptFds))
			{
				//�ر��쳣Socket,����sockArray�������
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
�� �� �� :ScanWithWSAEventSelect
�������� :���÷�����WSAEventSelect�첽�¼�����ģ��ɨ������(��ע��û�е���ͨ��)
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
bool CARTDevSearchTask::ScanWithWSAEventSelect(DWORD dwIP_S, DWORD dwIP_E)
{

	CString szProgressInfo;
	WSAEVENT    eventArray[WSA_MAXIMUM_WAIT_EVENTS];  
    SOCKET      sockArray[WSA_MAXIMUM_WAIT_EVENTS];  
    int nEventTotal  = 0;  
	int m_nLastError = 0;
	int iTimeOut     = 0;
  
    USHORT nPort = g_DevManagermentPort;    //�豸����TCP�˿ں�  
	
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

			//���ӳɹ�
			if (rc == NO_ERROR ) 
			{
				//����ɨ�赽������
				ProcessHost(hSocket);
			}
			else if(rc == SOCKET_ERROR && m_nLastError == WSAEWOULDBLOCK)
			{//����
				eventArray[nEventTotal] = hEvent;
				sockArray[nEventTotal]  = hSocket;
				nEventTotal++ ;
			}
			else 
			{//����
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
						//����ɨ�赽������
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
�� �� �� :AddNewHost
�������� :����ɨ�赽����������֤�Ƿ��豸�������������豸����
������� :��
������� :��
�� �� ֵ :void
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

	//�������ӳɹ����ж��Ƿ��豸������ǣ��������豸�������豸ָ��
	pDevice = pCOMM->VerfyDevice();
			
	//����Ŀ���豸
	if (pDevice == NULL)
	{
		delete pCOMM;
	}
	else
	{
		//�������豸�����豸����Ա
		pDevManager->AddDevice(pDevice);

		//�����ֵ�Ŀ���豸��ʾ������б�
		pDlg->AddFoundDevice(pDevice);

		
	}

	///////////////////////////////////////////////////////////////////////
}

/**************************************************************************************************
�� �� �� :Set_SearchType
�������� :������������
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchType(int iSearchType)
{
	m_iSearchType = iSearchType;
}

/**************************************************************************************************
�� �� �� :Set_SearchIP
�������� :��������IP
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchIP(DWORD dwIP)
{
	m_dwSearchIP = dwIP;
}


/**************************************************************************************************
�� �� �� :Set_SearchIPRange
�������� :��������IP��Χ
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
void CARTDevSearchTask::Set_SearchIPRange(DWORD dwIP_S, DWORD dwIP_E)
{
	m_dwSearchIP_S = dwIP_S ;
	m_dwSearchIP_E = dwIP_E ;
}

/**************************************************************************************************
�� �� �� :Set_SearchIPMask
�������� :��������IP��������
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :ProcessScanRequest
�������� :����ɨ�������豸������
������� :��
������� :��
�� �� ֵ :void
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