/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：COMM.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: COMM类实现，负责整个系统的Socket IO.
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "COMM.h"


CCOMM::CCOMM(DWORD dwIP)
	:m_dwIP(dwIP)
	,m_iPort(g_DevManagermentPort)
{
	m_pSocket = new CXSocket();
	ASSERT( m_pSocket);

	m_pSocket->Init();
	 
}


CCOMM::CCOMM(DWORD dwIP, int iPort)
	:m_dwIP(dwIP)
	,m_iPort(iPort)
{
	m_pSocket = new CXSocket();
	ASSERT( m_pSocket);

	m_pSocket->Init();
	 
}


CCOMM::CCOMM(SOCKET hSocket)
	:m_iPort(g_DevManagermentPort)
{
	bool bRet ;
	m_pSocket = new CXSocket(hSocket);
	ASSERT( m_pSocket);

	bRet = m_pSocket->EventSelect();

	ASSERT(bRet);

	struct sockaddr_in addr;
	int    ilen = sizeof(struct sockaddr);

	getpeername(hSocket, (struct sockaddr *)&addr, &ilen);

	m_dwIP = ntohl(addr.sin_addr.S_un.S_addr);
}



CCOMM::~CCOMM()
{
	if (m_pSocket != NULL)
		delete m_pSocket;
}

/**************************************************************************************************
函 数 名 :SendMsgAndGetResponse
功能描述 :发送pszMsg,并获取响应消息
输入参数 :pszMsg :发送数据;  iRecvBufSize: 接收缓冲区大小
输出参数 :pszRecvBuf, 接收缓冲区, 
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int CCOMM::SendMsgAndGetResponse(char *pszData, int iDataSize,  char *pszRecvBuf, int iRecvBufSize, int *piRecvDataSize)
{
	int ilenSent   ;
	int iSizeRecved;

	if (m_pSocket->Send((char *)pszData, iDataSize, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(pszRecvBuf, iRecvBufSize, iSizeRecved, 5000) != E_XSOCKET_SUCCESS)
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}

	*piRecvDataSize = iSizeRecved ;

	return 1;
}

/**************************************************************************************************
函 数 名 :Get_DevConfig
功能描述 :获取设备信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int  CCOMM::Get_DevConfig(CDevice *pDevice)
{
	void *pGetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	void *pSendData = NULL;
	int ilenSent;

	char szRevBuff[4096];
	int iSizeRecevied;

	unsigned long ulRet;


	pGetMsg = COMP_CreateGetMsgOfDevice();
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

		//设备类型 
		CString szDevMode;
		unsigned long  ulDevMode ;

		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_DEVICEMODEL, &ulDevMode);
		if (ulDevMode == SERIALSERV_DEVICEMODEL_SC5083)
		{
			szDevMode.Format("SC5083");
		}
		else
		{
			szDevMode.Format("????");
		}
		pDevice->Set_DevModeID(ulDevMode);
		pDevice->Set_DevMode((LPCTSTR)szDevMode);

		//设备名称
		char szTDevName[16];
		memset(szTDevName, 0 ,16);
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_SYSNAME, szTDevName);
		pDevice->Set_DevName((LPCTSTR)szTDevName);

		//MAC
		char szMAC[24];
		CString szMACAddr;
		memset(szMAC, 0 ,24);
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_MAC, szMAC);

		szMACAddr.Format("%02x:%02x:%02x:%02x:%02x:%02x", (unsigned char)szMAC[0]
			                                , (unsigned char)szMAC[1]
											, (unsigned char)szMAC[2]
											, (unsigned char)szMAC[3]
											, (unsigned char)szMAC[4]
											, (unsigned char)szMAC[5]);
		pDevice->Set_DevMAC((LPCTSTR)szMACAddr);

		//IP
		DWORD   dwIP       ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IP, &dwIP);
		pDevice->Set_DevIP(ntohl(dwIP));

		//IP Mask
		DWORD dwIPMask;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IPMASK, &dwIPMask);
		pDevice->Set_DevNet1IPMask(ntohl(dwIPMask));

		//GateWay
		//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
		BYTE byteNet1Mode;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_NETMODE_1, &byteNet1Mode);
		pDevice->Set_DevNet1Mode(byteNet1Mode);

		//SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
		DWORD   dwNet1IP       ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IP_1, &dwNet1IP);
		pDevice->Set_DevNet1IP(ntohl(dwNet1IP));

		//SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
		//DWORD   dwNet1IPMASK       ;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IPMASK_1, &dwNet1IPMASK);
		//pDevice->Set_DevNet1IPMask(ntohl(dwNet1IPMASK));

		//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
		DWORD   dwNet1GetWay;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_GATEWAY_1, &dwNet1GetWay);
		pDevice->Set_DevNet1IPGateWay(ntohl(dwNet1GetWay));

		//GateWay
		//SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
		BYTE byteNet2Mode;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_NETMODE_2, &byteNet2Mode);
		pDevice->Set_DevNet2Mode(byteNet2Mode);

		//SERIALSERV_SYSPARA_IP_2,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
		DWORD   dwNet2IP       ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IP_2, &dwNet2IP);
		pDevice->Set_DevNet2IP(ntohl(dwNet2IP));

		//SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
		//DWORD   dwNet2IPMASK       ;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IPMASK_2, &dwNet2IPMASK);
		//pDevice->Set_DevNet2IPMask(ntohl(dwNet2IPMASK));

		//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
		DWORD   dwNet2GetWay;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_GATEWAY_2, &dwNet2GetWay);
		pDevice->Set_DevNet2IPGateWay(ntohl(dwNet2GetWay));

		//pDevice->Set_DevTime(CTime(2013,05,01,12,30,30));

		//运行时间 SERIALSERV_SYSPARA_UPTIME, 系统启动时间:1970以来的毫秒, ULONG类型, 长度:4
		struct tm stTime ; 
		time_t tTime;
		long nYear;
		long nMonth;
		long nDay;
		long nHour;
		long nMin;
		long nSec;


		//设备时间
		long nDevTime ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_DATATIME, &nDevTime);
		nDevTime = ntohl(nDevTime);
		tTime =(time_t)nDevTime;

		localtime_s(&stTime ,&tTime);
	    nYear  = stTime.tm_year+1900 ;
		nMonth = stTime.tm_mon+1  ;
		nDay   = stTime.tm_mday ;
		nHour  = stTime.tm_hour ;
		nMin   = stTime.tm_min  ;
		nSec   = stTime.tm_sec  ;

		//pDevice->Set_DevTime(CTime(nYear,nMonth,nDay,nHour,nMin,nSec));
		pDevice->Set_DevTime(CTime(2013,7,7,7,10,30));

		long nUPTime ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_UPTIME, &nUPTime);
		nUPTime = ntohl(nUPTime);
		tTime =(time_t)nUPTime;
		localtime_s(&stTime ,&tTime);
	    nYear  = stTime.tm_year+1900 ;
		nMonth = stTime.tm_mon+1  ;
		nDay   = stTime.tm_mday ;
		nHour  = stTime.tm_hour ;
		nMin   = stTime.tm_min  ;
		nSec   = stTime.tm_sec  ;

		//pDevice->Set_DevUpTime(CTime(nYear,nMonth,nDay,nHour,nMin,nSec));
		pDevice->Set_DevUpTime(CTime(2013,7,7,7,10,30));


		//时区写成固定
		pDevice->Set_DevTimeZone(ART_TIME_ZONE_UTC_8);

		//软件版本		SERIALSERV_SYSPARA_SWVERSION,      /* SW version, 长度:4 */
		char  szSWVersion[24];
		memset(szSWVersion, 0 ,24);
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_SWVERSION, szSWVersion);
		pDevice->Set_DevSWVersion((LPCTSTR)szSWVersion);

		//Telnet Console开关
		//pDevice->Set_DevTelnetFlg(0);

		//Web Console开关
		//pDevice->Set_DevWebFlg(1);

		//端口数目 
		unsigned char cPortNum;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_DEVPORTNUM, &cPortNum);
	    pDevice->Set_PortNum((int)cPortNum);

		//设备状态
		pDevice->Set_DevStatus(1);
		pDevice->Set_CreateTime(CTime::GetCurrentTime());
		pDevice->Set_DevCOMM(this);

	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);

	return 1;
}


/**************************************************************************************************
函 数 名 :Get_DevConfig
功能描述 :获取设备信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int  CCOMM::Get_DevNetworkConfig(CDevice *pDevice)
{
	void *pGetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	void *pSendData = NULL;
	int ilenSent;

	char szRevBuff[4096];
	int iSizeRecevied;

	unsigned long ulRet;

	//////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////

	pGetMsg = COMP_CreateGetMsgOfDeviceNetwork1();
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

		//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
		//BYTE byteNet1Mode;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_NETMODE_1, &byteNet1Mode);
		//pDevice->Set_DevNet1Mode(byteNet1Mode);

		//SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
		//DWORD   dwNet1IP       ;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IP_1, &dwNet1IP);
		//pDevice->Set_DevNet1IP(ntohl(dwNet1IP));

		//SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
		DWORD   dwNet1IPMASK       ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IPMASK_1, &dwNet1IPMASK);
		pDevice->Set_DevNet1IPMask(ntohl(dwNet1IPMASK));

		//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
		//DWORD   dwNet1GetWay;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_GATEWAY_1, &dwNet1GetWay);
		//pDevice->Set_DevNet1IPGateWay(ntohl(dwNet1GetWay));

	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);

	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////

	pGetMsg = COMP_CreateGetMsgOfDeviceNetwork2();
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

		//GateWay
		//SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
		//BYTE byteNet2Mode;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_NETMODE_2, &byteNet2Mode);
		//pDevice->Set_DevNet2Mode(byteNet2Mode);

		//SERIALSERV_SYSPARA_IP_2,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
		//DWORD   dwNet2IP       ;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IP_2, &dwNet2IP);
		//pDevice->Set_DevNet2IP(ntohl(dwNet2IP));

		//SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
		DWORD   dwNet2IPMASK       ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_IPMASK_2, &dwNet2IPMASK);
		pDevice->Set_DevNet2IPMask(ntohl(dwNet2IPMASK));

		//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
		//DWORD   dwNet2GetWay;
		//COMP_GetSubOption(pRecvMsg, SERIALSERV_SYSPARA_GATEWAY_2, &dwNet2GetWay);
		//pDevice->Set_DevNet2IPGateWay(ntohl(dwNet2GetWay));

	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
函 数 名 :Get_DevAllPortsConfig
功能描述 :获取设备所有端口信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/

int   CCOMM::Get_DevAllPortsConfig(CDevice *pDevice)
{

	int iPortNum = pDevice->Get_PortNum();
	int i;

	for (i=1; i <= iPortNum; i++)
	{
		Get_DevPortConfig(pDevice, i);
	}

	return 1;
}
	

/**************************************************************************************************
函 数 名 :Get_DevAllPortsConfig
功能描述 :获取设备单端口信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int   CCOMM::Get_DevPortConfig(CDevice *pDevice, int iPortIndex)
{
	void *pGetMsg = NULL;
	void *pRecvMsg= NULL;
	void *pSendData = NULL;
	unsigned long ulLen = 0;
	int ilenSent;

	char szRevBuff[4096];
	int iSizeRecevied;
	unsigned long ulRet ;
	

	pGetMsg = COMP_CreateGetMsgOfPort(iPortIndex);
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

		//Port switch 
		char     cPortSwitch ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_SWITCH, &cPortSwitch);
		
		

		//Port名称
		char szTCOMName[16];
		memset(szTCOMName, 0 ,16);
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMNAME, szTCOMName);
		
		
		//PORTMODE
		char     CPortChannel ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_PORTMODE, &CPortChannel);

		//BAUDRATE
		int iPortBaudRate      ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_BAUDRATE, &iPortBaudRate);
		iPortBaudRate = ntohl(iPortBaudRate);

		//SERIALSERV_CFG_PARITYBIT,          /* 数据校验位, SERIALSERVCFGPARITYBIT_ENUM, 长度:1 */
		char cParityBit;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_PARITYBIT, &cParityBit);

        //SERIALSERV_CFG_DATABIT,            /* 数据位, SERIALSERVCFGDATABIT_ENUM, 长度:1 */
		char cDataBit;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_DATABIT, &cDataBit);

        //SERIALSERV_CFG_STOPBIT,            /* 停止位, SERIALSERVCFGSTOPBIT_ENUM, 长度:1 */
		char cStopBit;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_STOPBIT, &cStopBit);

		//SERIALSERV_CFG_FLOWCTL,            /*   流控,   SERIALSERVCFGFLOWCTL_ENUM, 长度:1 */
		char cFlowCtrl;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_FLOWCTL, &cFlowCtrl);

		//SERIALSERV_CFG_WORKMODE
		char cWorkMode;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_WORKMODE, &cWorkMode);
		
		//////////////////////////////////////////////
		CPort *pNewPort = new CPort();
		pNewPort->Set_Index(iPortIndex);
		pNewPort->Set_PortName((LPCTSTR)szTCOMName);
		pNewPort->Set_PortSwitch((int)cPortSwitch);
		pNewPort->Set_BaudRate(PORT_Get_BaudRate_By_Dev(iPortBaudRate));
		pNewPort->Set_Parity(PORT_Get_Parity_By_Dev(cParityBit));
		pNewPort->Set_DataBits(PORT_Get_DataBits_By_Dev(cDataBit));
		pNewPort->Set_StopBits(PORT_Get_StopBits_By_Dev(cStopBit));
		pNewPort->Set_FlowCtrl(PORT_Get_FlowCtrl_By_Dev(cFlowCtrl));
		pNewPort->Set_Interface(PORT_Get_Interface_By_Dev(CPortChannel));
		//pNewPort->Set_PortMode(PORT_Get_PortMode_By_Dev(cWorkMode));
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		//SERIALSERV_CFG_OPMODE1,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
		//SERIALSERV_CFG_COMIP1,              /* COM IP, ULONG类型, 长度:4      */ 
		//SERIALSERV_CFG_COMPORT1,            /* COM PORT, USHORT类型, 长度:2   */ 
		//SERIALSERV_CFG_CONNECTNUM1,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
		//-------------------------------------------------------------------------------------------
		unsigned char ucChannelNum;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELNUM, &ucChannelNum);
		pNewPort->Set_ChannelNum((int)ucChannelNum);
		
		//------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------
		unsigned char ucOPMODE1;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE1, &ucOPMODE1);
		pNewPort->Set_OPMODE1(ucOPMODE1);


		unsigned long ulCOMIP1 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP1, &ulCOMIP1);
		ulCOMIP1 = ntohl(ulCOMIP1);
		pNewPort->Set_COMIP1(ulCOMIP1);

		unsigned short usCOMPORT1;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT1, &usCOMPORT1);
		usCOMPORT1 = ntohs(usCOMPORT1);
		pNewPort->Set_COMPORT1(usCOMPORT1);

		unsigned long ulCONNECTNUM1;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM1, &ulCONNECTNUM1);
		ulCONNECTNUM1 = ntohl(ulCONNECTNUM1);
		pNewPort->Set_CONNECTNUM1(ulCONNECTNUM1);

		unsigned char ucChannelSwitch1;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH1, &ucChannelSwitch1);
		pNewPort->Set_CHANNELSWITCH1(ucChannelSwitch1);
		
		//------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------
		unsigned char ucOPMODE2;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE2, &ucOPMODE2);
		pNewPort->Set_OPMODE2(ucOPMODE2);

		unsigned long ulCOMIP2 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP2, &ulCOMIP2);
		ulCOMIP2 = ntohl(ulCOMIP2);
		pNewPort->Set_COMIP2(ulCOMIP2);

		unsigned short usCOMPORT2;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT2, &usCOMPORT2);
		usCOMPORT2 = ntohs(usCOMPORT2);
		pNewPort->Set_COMPORT2(usCOMPORT2);

		unsigned long ulCONNECTNUM2;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM2, &ulCONNECTNUM2);
		ulCONNECTNUM2 = ntohl(ulCONNECTNUM2);
		pNewPort->Set_CONNECTNUM2(ulCONNECTNUM2);

		unsigned char ucChannelSwitch2;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH2, &ucChannelSwitch2);
		pNewPort->Set_CHANNELSWITCH2(ucChannelSwitch2);

		//------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------
		unsigned char ucOPMODE3;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE3, &ucOPMODE3);
		pNewPort->Set_OPMODE3(ucOPMODE3);

		unsigned long ulCOMIP3 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP3, &ulCOMIP3);
		ulCOMIP3 = ntohl(ulCOMIP3);
		pNewPort->Set_COMIP3(ulCOMIP3);

		unsigned short usCOMPORT3;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT3, &usCOMPORT3);
		usCOMPORT3 = ntohs(usCOMPORT3);
		pNewPort->Set_COMPORT3(usCOMPORT3);

		unsigned long ulCONNECTNUM3;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM3, &ulCONNECTNUM3);
		ulCONNECTNUM3 = ntohl(ulCONNECTNUM3);
		pNewPort->Set_CONNECTNUM3(ulCONNECTNUM3);


		unsigned char ucChannelSwitch3;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH3, &ucChannelSwitch3);
		pNewPort->Set_CHANNELSWITCH3(ucChannelSwitch3);
		//------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------------
		unsigned char ucOPMODE4;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE4, &ucOPMODE4);
		pNewPort->Set_OPMODE4(ucOPMODE4);

		unsigned long ulCOMIP4 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP4, &ulCOMIP4);
		ulCOMIP4 = ntohl(ulCOMIP4);
		pNewPort->Set_COMIP4(ulCOMIP4);

		unsigned short usCOMPORT4;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT4, &usCOMPORT4);
		usCOMPORT4 = ntohs(usCOMPORT4);
		pNewPort->Set_COMPORT4(usCOMPORT4);

		unsigned long ulCONNECTNUM4;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM4, &ulCONNECTNUM4);
		ulCONNECTNUM4 = ntohl(ulCONNECTNUM4);
		pNewPort->Set_CONNECTNUM4(ulCONNECTNUM4);

		unsigned char ucChannelSwitch4;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH4, &ucChannelSwitch4);
		pNewPort->Set_CHANNELSWITCH4(ucChannelSwitch4);

		//------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------
		unsigned char ucOPMODE5;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE5, &ucOPMODE5);
		pNewPort->Set_OPMODE5(ucOPMODE5);

		unsigned long ulCOMIP5 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP5, &ulCOMIP5);
		ulCOMIP5 = ntohl(ulCOMIP5);
		pNewPort->Set_COMIP5(ulCOMIP5);

		unsigned short usCOMPORT5;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT5, &usCOMPORT5);
		usCOMPORT5 = ntohs(usCOMPORT5);
		pNewPort->Set_COMPORT5(usCOMPORT5);

		unsigned long ulCONNECTNUM5;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM5, &ulCONNECTNUM5);
		ulCONNECTNUM5 = ntohl(ulCONNECTNUM5);
		pNewPort->Set_CONNECTNUM5(ulCONNECTNUM5);

		unsigned char ucChannelSwitch5;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH5, &ucChannelSwitch5);
		pNewPort->Set_CHANNELSWITCH5(ucChannelSwitch5);
		//------------------------------------------------------------------------------------------
		//-------------------------------------------------------------------------------------------
		unsigned char ucOPMODE6;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_OPMODE6, &ucOPMODE6);
		pNewPort->Set_OPMODE6(ucOPMODE6);

		unsigned long ulCOMIP6 ;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMIP6, &ulCOMIP6);
		ulCOMIP6 = ntohl(ulCOMIP6);
		pNewPort->Set_COMIP6(ulCOMIP6);

		unsigned short usCOMPORT6;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_COMPORT6, &usCOMPORT6);
		usCOMPORT6 = ntohs(usCOMPORT6);
		pNewPort->Set_COMPORT6(usCOMPORT6);

		unsigned long ulCONNECTNUM6;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CONNECTNUM6, &ulCONNECTNUM6);
		ulCONNECTNUM6 = ntohl(ulCONNECTNUM6);
		pNewPort->Set_CONNECTNUM6(ulCONNECTNUM6);

		unsigned char ucChannelSwitch6;
		COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_CHANNELSWITCH6, &ucChannelSwitch6);
		pNewPort->Set_CHANNELSWITCH6(ucChannelSwitch6);
		//------------------------------------------------------------------------------------------
		///////////////////////////////////////////////////////////////////////////////////////////////////

		pDevice->AddPort(pNewPort);
	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);


	//////////////////////////////////////////////////////////////////////////////////////
	//系统初始化获取设备及端口信息后，再直接获取一次端口通道统计信息
	//////////////////////////////////////////////////////////////////////////////////////
	int iRet;
	
	iRet = Get_DevPortStatic(pDevice, iPortIndex);
	if (iRet <= 0)
	{
		return 0;
	}


	return 1;
}



/**************************************************************************************************
函 数 名 :Set_DevConfig
功能描述 :配置设备
输入参数 :pDevice
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int  CCOMM::Set_DevConfig(CDevice *pDevice)
{
	void *pSetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	void *pOptionStart = NULL;
	void *pSendData    = NULL;
	int ilenSent;
	unsigned long ulRet = 0;

	int iRet; 

	char szRevBuff[4096];
	int iSizeRecevied;

	unsigned long ulDataType;
	unsigned long ulDataSize;
	

	pSetMsg = COMP_CreateSetMsgofDevice();
	if (pSetMsg == NULL)
	{
		return 0;
	}
		
	ulDataType        = SERIALSERV_SYSPARA_SYSNAME;
	CString szDevName = pDevice->Get_DevName();
	ulDataSize        = szDevName.GetLength();

	COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , szDevName.GetBuffer(0));
	
	//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 

    //SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan2 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_2,           /*57 Lan2 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_2,       /*58 Lan2 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan2 IP GateWay, ULONG类型, 长度:4 */   

	//Net1 Mode名称
	BYTE byteNet1Mode;
	byteNet1Mode     = pDevice->Get_DevNet1Mode();
	ulDataType       = SERIALSERV_SYSPARA_NETMODE_1;
	ulDataSize       = 1;
	ulRet           += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , &byteNet1Mode);
		
	if (byteNet1Mode == SERIALSERV_DEVICEIPMODE_STATIC)
	{
		//Net1 IP
		DWORD dwNet1IP;
		dwNet1IP        =  pDevice->Get_DevNet1IP(); 
		dwNet1IP        =  htonl(dwNet1IP);
		ulDataType      = SERIALSERV_SYSPARA_IP_1 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet1IP);

		//Net1 IPMASK
		DWORD dwNet1IPMask;
		dwNet1IPMask    = pDevice->Get_DevNet1IPMask(); 
		dwNet1IPMask    = htonl(dwNet1IPMask);
		ulDataType      = SERIALSERV_SYSPARA_IPMASK_1 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet1IPMask);

		//Net1 IPGateway
		DWORD dwNet1IPGateWay;
		dwNet1IPGateWay =  pDevice->Get_DevNet1IPGateWay(); 
		dwNet1IPGateWay =  htonl(dwNet1IPGateWay);
		ulDataType      = SERIALSERV_SYSPARA_GATEWAY_1 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet1IPGateWay);
	}

	//Net2 Mode名称
	BYTE byteNet2Mode;
	byteNet2Mode     = pDevice->Get_DevNet2Mode();
	ulDataType       = SERIALSERV_SYSPARA_NETMODE_2;
	ulDataSize       = 1;
	ulRet           += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , &byteNet2Mode);
	
	if (byteNet2Mode == SERIALSERV_DEVICEIPMODE_STATIC)
	{
		//Net2 IP
		DWORD dwNet2IP;
		dwNet2IP        =  pDevice->Get_DevNet2IP(); 
		dwNet2IP        =  htonl(dwNet2IP);
		ulDataType      = SERIALSERV_SYSPARA_IP_2 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet2IP);

		//Net2 IPMASK
		DWORD dwNet2IPMask;
		dwNet2IPMask    =  pDevice->Get_DevNet2IPMask(); 
		dwNet2IPMask    =  htonl(dwNet2IPMask);
		ulDataType      = SERIALSERV_SYSPARA_IPMASK_2 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet2IPMask);

		//Net2 IPGateway
		DWORD dwNet2IPGateWay;
		dwNet2IPGateWay =  pDevice->Get_DevNet2IPGateWay(); 
		dwNet2IPGateWay =  htonl(dwNet2IPGateWay);
		ulDataType      = SERIALSERV_SYSPARA_GATEWAY_2 ;
		ulDataSize      = 4; 
		ulRet          += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&dwNet2IPGateWay);
	}

	//写结束标记
	COMP_SetEndOfMsg(pSetMsg);

	ulLen = COMP_GetMsgSize(pSetMsg);

	pSendData = COMP_GetMsgData(pSetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pSetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		iRet = COMP_GetResult(pRecvMsg);
		if (iRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}
		
	}
	else
	{
		COMP_FreeMsg(pSetMsg);
		return 0;		
	}

	COMP_FreeMsg(pSetMsg);

	return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
函 数 名 :Set_DevAllPortsConfig(暂时没用)
功能描述 :配置设备所有端口信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/

int   CCOMM::Set_DevAllPortsConfig(CDevice *pDevice)
{
	int iPortNum = pDevice->Get_PortNum();
	int i;

	for (i=1; i <= iPortNum; i++)
	{
		//Set_DevPortConfig(pDevice, i);
	}

	return 1;
}


/**************************************************************************************************
函 数 名 :Set_DevPortParaConfig
功能描述 :配置设备单端口物理参数信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int   CCOMM::Set_DevPortParaConfig(CDevice *pDevice, int iPortIndex)
{
	void *pSetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	int ilenSent;
	unsigned long ulRet = 0;
	void * pSendData = NULL;

	char szRevBuff[4096];
	int iSizeRecevied;
	
	unsigned long ulDataType;
	unsigned long ulDataSize;

	pSetMsg = COMP_CreateSetMsgofPort(iPortIndex);
	if (pSetMsg == NULL)
	{
		return 0;
	}

	CPort *pPort = pDevice->QueryPortByPortNo(iPortIndex);
	if (pPort == NULL)
	{
		COMP_FreeMsg(pSetMsg);
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////

	//Port Switch 
	char     cPortSwitch ;
	//COMP_GetSubOption(pRecvMsg, SERIALSERV_CFG_SWITCH, &cPortStatus);
	cPortSwitch  = pPort->Get_PortSwitch();
	ulDataType = SERIALSERV_CFG_SWITCH ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cPortSwitch);

	//Port名称
	CString szPortName;
	szPortName = pPort->Get_PortName();
	ulDataType = SERIALSERV_CFG_COMNAME;
	ulDataSize = szPortName.GetLength();
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , szPortName.GetBuffer(0));
		
	//PORTMODE
	char     CPortChannel;
	CPortChannel  = PORT_Get_Interface_By_SYS(pPort->Get_Interface());
	ulDataType = SERIALSERV_CFG_PORTMODE ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&CPortChannel);

	//FD_SETSIZE 
	//BAUDRATE
	int iPortBaudRate      ;
	iPortBaudRate = PORT_Get_BaudRate_By_SYS(pPort->Get_BaudRate());
	iPortBaudRate = htonl(iPortBaudRate);
	ulDataType   = SERIALSERV_CFG_BAUDRATE ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&iPortBaudRate);

	//SERIALSERV_CFG_PARITYBIT,          /* 数据校验位, SERIALSERVCFGPARITYBIT_ENUM, 长度:1 */
	char cParityBit;
	cParityBit = PORT_Get_Parity_By_SYS(pPort->Get_Parity());
	ulDataType = SERIALSERV_CFG_PARITYBIT ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cParityBit);

    //SERIALSERV_CFG_DATABIT,            /* 数据位, SERIALSERVCFGDATABIT_ENUM, 长度:1 */
	char cDataBit;
	cDataBit = PORT_Get_DataBits_By_SYS(pPort->Get_DataBits());
	ulDataType = SERIALSERV_CFG_DATABIT ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cDataBit);

    //SERIALSERV_CFG_STOPBIT,            /* 停止位, SERIALSERVCFGSTOPBIT_ENUM, 长度:1 */
	char cStopBit;
	cStopBit = PORT_Get_StopBits_By_SYS(pPort->Get_StopBits());
	ulDataType = SERIALSERV_CFG_STOPBIT ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cStopBit);

	//SERIALSERV_CFG_FLOWCTL,            /*   流控,   SERIALSERVCFGFLOWCTL_ENUM, 长度:1 */
	char cFlowCtrl;
	cFlowCtrl = PORT_Get_FlowCtrl_By_SYS(pPort->Get_FlowCtrl());
	ulDataType = SERIALSERV_CFG_FLOWCTL ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cFlowCtrl);

	//SERIALSERV_CFG_WORKMODE
	//char cWorkMode;
	//cWorkMode = PORT_Get_PortWorkMode_By_SYS(pPort->Get_PortMode());
	//ulDataType = SERIALSERV_CFG_WORKMODE ;
	//ulDataSize = 1; 
	//pOptionStart = COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&cWorkMode);
	//ulLen += ulDataSize;

	//写结束标记
	COMP_SetEndOfMsg(pSetMsg);
	

	if (ulRet> 0)
	{
		COMP_FreeMsg(pSetMsg);
		return 0;
	}

	ulLen = COMP_GetMsgSize(pSetMsg);

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	pSendData = COMP_GetMsgData(pSetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pSetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		/////////////////////////////////////////////////////////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

	}
	else
	{
		COMP_FreeMsg(pSetMsg);
		return 0;		
	}

	COMP_FreeMsg(pSetMsg);

	return 1;
}


/**************************************************************************************************
函 数 名 :Set_DevPortWorkModeConfig
功能描述 :配置设备单端口工作模式信息
输入参数 :无
输出参数 :pDevice
返 回 值 :0 失败，1 成功
**************************************************************************************************/
int   CCOMM::Set_DevPortWorkModeConfig(CDevice *pDevice, int iPortIndex)
{
	void *pSetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	int ilenSent;
	unsigned long ulRet = 0;
	void *pSendData = NULL;

	char szRevBuff[4096];
	int iSizeRecevied;
	
	unsigned long ulDataType;
	unsigned long ulDataSize;

	pSetMsg = COMP_CreateSetMsgofPort(iPortIndex);
	if (pSetMsg == NULL)
	{
		return 0;
	}


	CPort *pPort = pDevice->QueryPortByPortNo(iPortIndex);
	if (pPort == NULL)
	{
		COMP_FreeMsg(pSetMsg);
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	
	unsigned char ucChannelNum;
	ucChannelNum  = pPort->Get_ChannelNum();
	ulDataType = SERIALSERV_CFG_CHANNELNUM ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelNum);

	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE1;
	ucOPMODE1    = pPort->Get_OPMODE1() ;
	ulDataType = SERIALSERV_CFG_OPMODE1 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE1);

	unsigned long ulCOMIP1 ;
	ulCOMIP1 = pPort->Get_COMIP1();
	ulCOMIP1 = htonl(ulCOMIP1);
	ulDataType   = SERIALSERV_CFG_COMIP1 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP1);

	unsigned short usCOMPORT1;
	usCOMPORT1 = pPort->Get_COMPORT1();
	usCOMPORT1 = htons(usCOMPORT1);
	ulDataType   = SERIALSERV_CFG_COMPORT1 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT1);

	unsigned long ulCONNECTNUM1;
	ulCONNECTNUM1 = pPort->Get_CONNECTNUM1();
	ulCONNECTNUM1 = htonl(ulCONNECTNUM1);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM1 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM1);

	unsigned char ucChannelSwitch1;
	ucChannelSwitch1	= pPort->Get_CHANNELSWITCH1() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH1 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch1);
	//----------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE2;
	ucOPMODE2    = pPort->Get_OPMODE2() ;
	ulDataType = SERIALSERV_CFG_OPMODE2 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE2);

	unsigned long ulCOMIP2 ;
	ulCOMIP2 = pPort->Get_COMIP2();
	ulCOMIP2 = htonl(ulCOMIP2);
	ulDataType   = SERIALSERV_CFG_COMIP2 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP2);

	unsigned short usCOMPORT2;
	usCOMPORT2 = pPort->Get_COMPORT2();
	usCOMPORT2 = htons(usCOMPORT2);
	ulDataType   = SERIALSERV_CFG_COMPORT2 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT2);

	unsigned long ulCONNECTNUM2;
	ulCONNECTNUM2 = pPort->Get_CONNECTNUM2();
	ulCONNECTNUM2 = htonl(ulCONNECTNUM2);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM1 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM2);

	unsigned char ucChannelSwitch2;
	ucChannelSwitch2	= pPort->Get_CHANNELSWITCH2() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH2 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch2);
	//----------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE3;
	ucOPMODE3    = pPort->Get_OPMODE3() ;
	ulDataType = SERIALSERV_CFG_OPMODE3 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE3);

	unsigned long ulCOMIP3 ;
	ulCOMIP3 = pPort->Get_COMIP3();
	ulCOMIP3 = htonl(ulCOMIP3);
	ulDataType   = SERIALSERV_CFG_COMIP3 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP3);

	unsigned short usCOMPORT3;
	usCOMPORT3 = pPort->Get_COMPORT3();
	usCOMPORT3 = htons(usCOMPORT3);
	ulDataType   = SERIALSERV_CFG_COMPORT3 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT3);

	unsigned long ulCONNECTNUM3;
	ulCONNECTNUM3 = pPort->Get_CONNECTNUM3();
	ulCONNECTNUM3 = htonl(ulCONNECTNUM3);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM3 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM3);

	unsigned char ucChannelSwitch3;
	ucChannelSwitch3	= pPort->Get_CHANNELSWITCH3() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH3 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch3);
	//----------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE4;
	ucOPMODE4    = pPort->Get_OPMODE4() ;
	ulDataType = SERIALSERV_CFG_OPMODE4 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE4);

	unsigned long ulCOMIP4 ;
	ulCOMIP4 = pPort->Get_COMIP4();
	ulCOMIP4 = htonl(ulCOMIP1);
	ulDataType   = SERIALSERV_CFG_COMIP4 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP4);

	unsigned short usCOMPORT4;
	usCOMPORT4 = pPort->Get_COMPORT4();
	usCOMPORT4 = htons(usCOMPORT4);
	ulDataType   = SERIALSERV_CFG_COMPORT4 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT4);

	unsigned long ulCONNECTNUM4;
	ulCONNECTNUM4 = pPort->Get_CONNECTNUM4();
	ulCONNECTNUM4 = htonl(ulCONNECTNUM4);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM4 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM4);

	unsigned char ucChannelSwitch4;
	ucChannelSwitch4	= pPort->Get_CHANNELSWITCH4() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH4 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch4);
	//-------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE5;
	ucOPMODE5    = pPort->Get_OPMODE5() ;
	ulDataType = SERIALSERV_CFG_OPMODE5 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE5);

	unsigned long ulCOMIP5 ;
	ulCOMIP5 = pPort->Get_COMIP5();
	ulCOMIP5 = htonl(ulCOMIP5);
	ulDataType   = SERIALSERV_CFG_COMIP5 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP5);

	unsigned short usCOMPORT5;
	usCOMPORT5 = pPort->Get_COMPORT5();
	usCOMPORT5 = htons(usCOMPORT5);
	ulDataType   = SERIALSERV_CFG_COMPORT5 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT5);

	unsigned long ulCONNECTNUM5;
	ulCONNECTNUM5 = pPort->Get_CONNECTNUM5();
	ulCONNECTNUM5 = htonl(ulCONNECTNUM5);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM5 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM5);

	unsigned char ucChannelSwitch5;
	ucChannelSwitch5	= pPort->Get_CHANNELSWITCH5() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH5 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch5);
	//----------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	unsigned char ucOPMODE6;
	ucOPMODE6    = pPort->Get_OPMODE6() ;
	ulDataType = SERIALSERV_CFG_OPMODE6 ;
	ulDataSize = 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucOPMODE6);

	unsigned long ulCOMIP6 ;
	ulCOMIP6 = pPort->Get_COMIP6();
	ulCOMIP6 = htonl(ulCOMIP6);
	ulDataType   = SERIALSERV_CFG_COMIP6 ;
	ulDataSize   = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCOMIP6);

	unsigned short usCOMPORT6;
	usCOMPORT6 = pPort->Get_COMPORT6();
	usCOMPORT6 = htons(usCOMPORT6);
	ulDataType   = SERIALSERV_CFG_COMPORT6 ;
	ulDataSize   = 2; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&usCOMPORT6);

	unsigned long ulCONNECTNUM6;
	ulCONNECTNUM6 = pPort->Get_CONNECTNUM6();
	ulCONNECTNUM6 = htonl(ulCONNECTNUM6);
	ulDataType    = SERIALSERV_CFG_CONNECTNUM6 ;
	ulDataSize    = 4; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ulCONNECTNUM6);

	unsigned char ucChannelSwitch6;
	ucChannelSwitch6	= pPort->Get_CHANNELSWITCH6() ;
	ulDataType			= SERIALSERV_CFG_CHANNELSWITCH6 ;
	ulDataSize			= 1; 
	ulRet += COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize ,&ucChannelSwitch6);
	
	ASSERT(ulRet == 0);

	COMP_SetEndOfMsg(pSetMsg);

	ulLen = COMP_GetMsgSize(pSetMsg);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	pSendData = COMP_GetMsgData(pSetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pSetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

	}
	else
	{
		COMP_FreeMsg(pSetMsg);
		return 0;		
	}

	COMP_FreeMsg(pSetMsg);

	return 1;
}



/**************************************************************************************************
函 数 名 :VerifyHost
功能描述 :验证主机是否存在
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::VerifyHost()
{
	bool bRet ; 
	
	bRet = m_pSocket->QConnect(m_dwIP, m_iPort);
	if (bRet != true)
	{
		return 0 ;
	}

	return 1;
}

/**************************************************************************************************
函 数 名 :Set_Reboot
功能描述 :重启设备
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Set_Reboot()
{
	void *pSetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	void *pOptionStart = NULL;
	void *pSendData    = NULL;
	int ilenSent;

	int iRet; 

	char szRevBuff[4096];
	int iSizeRecevied;

	unsigned long ulDataType;
	unsigned long ulDataSize;
	

	pSetMsg = COMP_CreateSetMsgofDevice();
	if (pSetMsg == NULL)
	{
		return 0;
	}
		
	ulDataType        = SERIALSERV_SYSPARA_DEVREBOOT;
	ulDataSize        = 0;

	COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , NULL);
	
	//写结束标记
	COMP_SetEndOfMsg(pSetMsg);

	ulLen = COMP_GetMsgSize(pSetMsg);

	pSendData = COMP_GetMsgData(pSetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{
		/*
		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pSetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;
		
		iRet = COMP_GetResult(pRecvMsg);
		if (iRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}
		*/
		
	}
	else
	{
		COMP_FreeMsg(pSetMsg);
		return 0;		
	}

	COMP_FreeMsg(pSetMsg);


	return 1;
}

/**************************************************************************************************
函 数 名 :Set_SaveData
功能描述 :保存设备配置数据
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Set_SaveData()
{
	void *pSetMsg = NULL;
	void *pRecvMsg= NULL;
	unsigned long ulLen = 0;
	void *pOptionStart = NULL;
	void *pSendData    = NULL;
	int ilenSent;

	int iRet; 

	char szRevBuff[4096];
	int iSizeRecevied;

	unsigned long ulDataType;
	unsigned long ulDataSize;
	

	pSetMsg = COMP_CreateSetMsgofDevice();
	if (pSetMsg == NULL)
	{
		return 0;
	}
		
	ulDataType        = SERIALSERV_SYSPARA_SAVETODB;
	ulDataSize        = 0;

	COMP_SetSubOption(pSetMsg , ulDataType, ulDataSize , NULL);
	
	//写结束标记
	COMP_SetEndOfMsg(pSetMsg);

	ulLen = COMP_GetMsgSize(pSetMsg);

	pSendData = COMP_GetMsgData(pSetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pSetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		iRet = COMP_GetResult(pRecvMsg);
		if (iRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}
		
	}
	else
	{
		COMP_FreeMsg(pSetMsg);
		return 0;		
	}

	COMP_FreeMsg(pSetMsg);


	return 1;
}



/**************************************************************************************************
函 数 名 :VerfyDevice
功能描述 :验证Device
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
CDevice* CCOMM::VerfyDevice()
{
	int iRet;
	CDevice *pDevice = new CDevice();
	
	pDevice->Set_DevIP(m_dwIP);

	iRet = Get_DevConfig(pDevice);
    
	if (iRet == 0)
	{
		delete pDevice;
		return NULL;
	}

	iRet = Get_DevNetworkConfig(pDevice);
    
	if (iRet == 0)
	{
		delete pDevice;
		return NULL;
	}


	Get_DevAllPortsConfig(pDevice);

	
	return pDevice ;
}


/**************************************************************************************************
函 数 名 :Set_Hello
功能描述 :发送心跳Hello报文
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Set_Hello(CDevice *pDevice)
{
	void *pGetMsg = NULL;
	void *pRecvMsg= NULL;
	void *pSendData = NULL;
	unsigned long ulLen = 0;
	int ilenSent;

	char szRevBuff[4096];
	int iSizeRecevied;
	unsigned long ulRet ;
	
	CPort *pPort = NULL;


	pGetMsg = COMP_CreateHeartMsg();
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}
	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);


	return 1;
}

/**************************************************************************************************
函 数 名 :Get_DevPortChannelStatic
功能描述 :从设备上获取PORT上的Channel数据转发统计项
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Get_DevPortChannelStatic(CDevice *pDevice, int iPortIndex, unsigned char ucChannelNo)
{
	void *pGetMsg = NULL;
	void *pRecvMsg= NULL;
	void *pSendData = NULL;
	unsigned long ulLen = 0;
	int ilenSent;

	char szRevBuff[4096];
	int iSizeRecevied;
	unsigned long ulRet ;
	
	CPort *pPort = NULL;


	pGetMsg = COMP_GetPortChannelStatistics(iPortIndex, ucChannelNo );
	if (pGetMsg == NULL)
	{
		return 0;
	}

	COMP_SetEndOfMsg(pGetMsg);

	ulLen = COMP_GetMsgSize(pGetMsg);

	pSendData = COMP_GetMsgData(pGetMsg);

	if (m_pSocket->Send((char *)pSendData, ulLen, ilenSent, 5000) == E_XSOCKET_SUCCESS)
	{

		if (m_pSocket->Recv(szRevBuff, 4096, iSizeRecevied, 5000) != E_XSOCKET_SUCCESS)
		{
			COMP_FreeMsg(pGetMsg);
			return 0;
		}

		pRecvMsg = (void *)szRevBuff;

		//////////////////////////////////////////////
		ulRet = COMP_GetResult(pRecvMsg);
		if (ulRet != SERIALSERV_OPRESULT_OK)
		{
			return 0;
		}

		pPort = pDevice->QueryPortByPortNo(iPortIndex);

        switch (ucChannelNo)
		{
			case 1:
				if (pPort->Get_CHANNELSWITCH1() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic1);
				}
				break;

			case 2:
				if (pPort->Get_CHANNELSWITCH2() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic2);
				}
				break;
			case 3:
				if (pPort->Get_CHANNELSWITCH3() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic3);
				}
				break;
			case 4:
				if (pPort->Get_CHANNELSWITCH4() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic4);
				}
				break;
			case 5:
				if (pPort->Get_CHANNELSWITCH5() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic5);
				}
				break;
			case 6:
				if (pPort->Get_CHANNELSWITCH6() == SERIALSERV_CHANNELSWITCH_ON)
				{
					COMP_GetPortChannelStisticData(pRecvMsg, pPort->m_pChannelStatic6);
				}
				break;
			default:
				break;
			
		}

	}
	else
	{
		COMP_FreeMsg(pGetMsg);
		return 0;		
	}

	COMP_FreeMsg(pGetMsg);

	return 1;

}


/**************************************************************************************************
函 数 名 :Get_DevPortStatic
功能描述 :从设备上获取PORT上的Channel数据转发统计项
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Get_DevPortStatic(CDevice *pDevice, int iPortIndex)
{
	CPort *pPort = NULL;
	int    iPortSwitch ;

	if (pDevice == NULL)
	{
		return 0;
	}

	pPort = pDevice->QueryPortByPortNo(iPortIndex);
	if (pPort != NULL)
	{
		iPortSwitch = pPort->Get_PortSwitch();

		if (iPortSwitch == SERIALSERV_SWITCH_ON)
		{
			if (pPort->Get_CHANNELSWITCH1() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  1 );
			}
			if (pPort->Get_CHANNELSWITCH2() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  2 );
			}

			if (pPort->Get_CHANNELSWITCH3() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  3 );
			}

			if (pPort->Get_CHANNELSWITCH4() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  4 );
			}

			if (pPort->Get_CHANNELSWITCH5() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  5 );
			}

			if (pPort->Get_CHANNELSWITCH6() == SERIALSERV_CHANNELSWITCH_ON)
			{
				Get_DevPortChannelStatic(pDevice, iPortIndex,  6 );
			}
		}
	}

	return 1;
}

/**************************************************************************************************
函 数 名 :Get_DevStatic
功能描述 ://从设备上获取数据转发统计项
输入参数 :无
输出参数 :无
返 回 值 :int
**************************************************************************************************/
int CCOMM::Get_DevStatic(CDevice *pDevice)
{
	int iPortNum = pDevice->Get_PortNum();

	for (int i=1; i <= iPortNum; i++)
	{
		Get_DevPortStatic(pDevice, i);
	}

	return 1;
}