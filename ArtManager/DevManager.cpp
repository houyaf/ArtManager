/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：DevManager.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 设备管理类DevManager实现
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#include "stdafx.h"

// CDevManager

CDevManager::CDevManager()
{

	//GenerateDeviceData();
}

CDevManager::~CDevManager()
{

}

/**************************************************************************************************
函 数 名 :ClearDevices
功能描述 :清除所有设备
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevManager::ClearDevices()
{
	while (!m_DevList.IsEmpty())
	{
		delete m_DevList.RemoveHead();
	}
	
}
// CDevManager 成员函数

/**************************************************************************************************
函 数 名 :ShowDevices
功能描述 :显示所有Device数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevManager::ShowDevices()
{
	CDevice *pDevice = NULL;
	POSITION pos;
	CString szMsg;

	pos = m_DevList.GetHeadPosition();
	while(pos != NULL)
	{
		pDevice = (CDevice *)m_DevList.GetNext(pos);
		szMsg.Format(_T("%s:%s:%d"), pDevice->Get_DevMode().GetBuffer(0), 
				                     pDevice->Get_DevName().GetBuffer(0), 
				                     pDevice->Get_PortNum());
		AfxMessageBox(szMsg.GetBuffer(0));
	}
}


/**************************************************************************************************
函 数 名 :AddDevice
功能描述 :增加Device
输入参数 :pDevice设备数据指针
输出参数 :无
返 回 值 :1 成功；0 失败
**************************************************************************************************/
int CDevManager::AddDevice(CDevice* pDevice)
{
	CDevice *pTDevice  = NULL;

	pTDevice = QueryDeviceByIP(pDevice->Get_DevIP());
	if (pTDevice!= NULL)
	{
		DeleteDevice(pTDevice);
	}
	m_DevList.AddTail(pDevice);

	return 1;
}

/**************************************************************************************************
函 数 名 :DeleteDevice
功能描述 :删除Device
输入参数 :pDevice设备数据指针
输出参数 :无
返 回 值 :1 成功；0 失败
**************************************************************************************************/
int CDevManager::DeleteDevice(CDevice *pDevice)
{
	POSITION pos;

	pos = m_DevList.Find((CObject*)pDevice);

	if (pos == NULL)
	{
		return 0;
	}

	m_DevList.RemoveAt(pos);
	
	delete pDevice;

	return 1;
}

/**************************************************************************************************
函 数 名 :Get_DevList
功能描述 :设备列表指针Get
输入参数 :无
输出参数 :无
返 回 值 :设备列表指针
**************************************************************************************************/
CDeviceList* CDevManager::Get_DevList()
{
	return &m_DevList ;
}

/**************************************************************************************************
函 数 名 :QueryDeviceByIP
功能描述 :根据IP地址查找设备Device数据
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :成功则返回设备指针，否则NULL
**************************************************************************************************/
CDevice *CDevManager::QueryDeviceByIP(DWORD dwIP)
{
	CDevice *pDevice = NULL;
	POSITION pos;
	DWORD dwDevIP;

	pos = m_DevList.GetHeadPosition();
	while(pos != NULL)
	{
		pDevice = (CDevice *)m_DevList.GetNext(pos);
		dwDevIP = pDevice->Get_DevIP();

		if (dwDevIP == dwIP)
		{
			return pDevice;
		}
	}

	return NULL;
}

//
/**************************************************************************************************
函 数 名 :QueryPortByIPandPortNo
功能描述 :根据IP和端口號查找端口数据
输入参数 :szIP IP地址, sz
输出参数 :无
返 回 值 :无
**************************************************************************************************/
CPort *CDevManager::QueryPortByIPandPortNo(DWORD dwIP, int iPortIndex)
{
	CDevice   *pDevice   = NULL;
	POSITION   pos;
	CPortList *pPortList = NULL;
	CPort     *pPort     = NULL;
	int        iPortNo   ;

	pDevice = QueryDeviceByIP(dwIP);

	if ( pDevice != NULL )
	{
		pPortList = pDevice->Get_PortList();

		if (pPortList != NULL)
		{
			pos = pPortList->GetHeadPosition();
			while (pos != NULL)
			{
				pPort = pPortList->GetNext(pos);
				if (pPort != NULL)
				{
					iPortNo = pPort->Get_Index();

					if (iPortNo == iPortIndex)
					{
						return pPort ;
					}
				}
			}
		}
	}

	return NULL;
}

/**************************************************************************************************
函 数 名 :GenerateDeviceData
功能描述 :生成测试用Device数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void CDevManager::GenerateDeviceData()
{
	CString szDevMode;
	CString szDevName;
	
	CString szMAC;
	
	DWORD dwIP;
	DWORD dwIPMask;
	DWORD dwIPGateWay;
	
	CString szSWVersion;
	CString szTimeZone;


	for (int i = 0; i < 20; i++)
	{
		CDevice *pDevice = new CDevice();

		//设备类型 
		szDevMode.Format("SC508%d", i);
		pDevice->Set_DevMode((LPCTSTR)szDevMode);

		//设备名称
		szDevName.Format("esdp%d", i);
		pDevice->Set_DevName((LPCTSTR)szDevName);

		//MAC
		szMAC.Format("00.80.12.33.12.%d",i+1);
		pDevice->Set_DevMAC((LPCTSTR)szMAC);

		//IP
		dwIP = 0xC0A80101 + i ;
		pDevice->Set_DevIP(dwIP);

		//IP Mask
		dwIPMask = 0xffffff00;
		//pDevice->Set_DevIPMask(dwIPMask);

		//GateWay
		dwIPGateWay = 0xC0A80001 ;
		//pDevice->Set_DevIPGateWay(dwIPGateWay);

		//设备时间
		pDevice->Set_DevTime(CTime(2013,05,01,12,30,30));

		//运行时间
		pDevice->Set_DevUpTime(CTime(2013,4,1,8,30,30));

		//时区
		pDevice->Set_DevTimeZone(ART_TIME_ZONE_UTC_8);

		//软件版本
		szSWVersion.Format("v100r001c01");
		pDevice->Set_DevSWVersion((LPCTSTR)szSWVersion);

		//Telnet Console开关
		pDevice->Set_DevTelnetFlg(0);

		//Web Console开关
		pDevice->Set_DevWebFlg(1);


		//端口数目 
		pDevice->Set_PortNum(i+1);

		GeneratePortData(pDevice, i+1);

		//设备状态
		pDevice->Set_DevStatus(1);

		pDevice->Set_CreateTime(CTime::GetCurrentTime());

		m_DevList.AddTail(pDevice);

	}
}

/**************************************************************************************************
函 数 名 :GeneratePortData
功能描述 :生成测试用Port数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void  CDevManager::GeneratePortData(CDevice *pDevice, int iPortNum)
{
	CPort *pNewPort = NULL;
	CString szPortName;

	for (int i = 1; i <= iPortNum; i++)
	{
		pNewPort = new CPort();
		pNewPort->Set_Index(i);

		szPortName.Format("Port %d", i);
		pNewPort->Set_PortName((LPCTSTR)szPortName);

		pNewPort->Set_BaudRate(Port_BaudRate_115200);
		pNewPort->Set_Parity(PORT_PARITY_ODD);

		pNewPort->Set_DataBits(Port_DataBits_6);
		pNewPort->Set_StopBits(Port_StopBits_2);
		pNewPort->Set_FlowCtrl(FLOW_CTRL_NONE);
		pNewPort->Set_Interface(i%4);

		//pNewPort->Set_PortMode(i%4);

		//GeneratePortModeData(pNewPort, i%4);

		pDevice->AddPort(pNewPort);
	} 
}

/**************************************************************************************************
函 数 名 :GeneratePortModeData
功能描述 :生成测试用PortMode数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void CDevManager::GeneratePortModeData(CPort *pPort, int iPortMode)
{

	switch (iPortMode)
	{
		case 0:
			GenerateTCPServerPortModeData(pPort);
			break;
		case 1:
			GenerateTCPClientPortModeData(pPort);
			break;
		case 2:
			GenerateUDPPortModeData(pPort);
			break;
		case 3:
			GenerateRealCOMPortModeData(pPort);
			break;
		default:

			break;
	}
}

/**************************************************************************************************
函 数 名 :GenerateTCPServerPortModeData
功能描述 :生成测试用TCPServerPortMode数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void  CDevManager::GenerateTCPServerPortModeData(CPort *pPort)
{
	CTCPServerPortMode *pPortMode = NULL;

	pPortMode = new CTCPServerPortMode();
	pPortMode->Set_ModeID(PORT_MODE_TCP_SERVER);
	pPortMode->Set_ModeName(_T("TCP Server Mode"));
	pPortMode->Set_ListenPort1(4000);
	pPortMode->Set_MaxConnection1(2);
	
	//pPort->Set_PortModeData((CPortChannel *)pPortMode);
}

/**************************************************************************************************
函 数 名 :GenerateTCPClientPortModeData
功能描述 :生成测试用TCPClientPortMode数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void  CDevManager::GenerateTCPClientPortModeData(CPort *pPort)
{
	CTCPClientPortMode *pPortMode = NULL;
	pPortMode = new CTCPClientPortMode();

	pPortMode->Set_ModeID(PORT_MODE_TCP_CLIENT);
	pPortMode->Set_ModeName(_T("TCP Client Mode"));

	pPortMode->Set_TargetHost1(0xC0A801A0, 4000, 4001);
	pPortMode->Set_TargetHost2(0xC0A801A1, 4000, 4002);
	pPortMode->Set_TargetHost3(0xC0A801A2, 4000, 4003);
	pPortMode->Set_TargetHost4(0xC0A801A3, 4000, 4004);

	//pPort->Set_PortModeData((CPortChannel *)pPortMode);
}

/**************************************************************************************************
函 数 名 :GenerateUDPPortModeData
功能描述 :生成测试用UDPPortMode数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void  CDevManager::GenerateUDPPortModeData(CPort *pPort)
{
	CUDPPortMode *pPortMode = NULL;

	pPortMode = new CUDPPortMode();

	//pPortMode->Set_ModeID(PORT_MODE_UDP);
	//pPortMode->Set_ModeName(_T("UDP Mode"));
	
	//pPortMode->Set_ListenPort1(4002);
	//pPortMode->Set_TargetHost1(0xC0A805A0,0xC0A805FF, 5000);
	//pPortMode->Set_TargetHost2(0xC0A806A0,0xC0A806FF, 5000);
	//pPortMode->Set_TargetHost3(0xC0A807A0,0xC0A807FF, 5000);
	//pPortMode->Set_TargetHost4(0xC0A808A0,0xC0A808FF, 5000);

	//pPort->Set_PortModeData((CPortChannel *)pPortMode);
}

/**************************************************************************************************
函 数 名 :GenerateRealCOMPortModeData
功能描述 :生成测试用RealCOM PortMode数据，用于Debug
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void  CDevManager::GenerateRealCOMPortModeData(CPort *pPort)
{
	CRealCOMPortMode *pPortMode = NULL;

	pPortMode = new CRealCOMPortMode();

	//pPortMode->Set_ModeID(PORT_MODE_REAL_COM);
	//pPortMode->Set_ModeName(_T("Real-COM Mode"));

	//pPort->Set_PortModeData((CPortChannel *)pPortMode);
}

