/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：Device.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: Device类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
// CDevice
CDevice::CDevice()
{

}

CDevice::~CDevice()
{
	ClearPort();

}
// CDevice 成员函数

/**************************************************************************************************
函 数 名 :Set_DevCOMM
功能描述 :设备通讯器Set
输入参数 :略
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void  CDevice::Set_DevCOMM(CCOMM *pCOMM)
{
	ASSERT(pCOMM);

	m_pCOMM = pCOMM;

}

/**************************************************************************************************
函 数 名 :Set_DevMode
功能描述 :设备类型Set
输入参数 :szDevMode 设备类型
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevMode(LPCTSTR szDevMode)
{
	m_szDevMode = szDevMode;
}

/**************************************************************************************************
函 数 名 :Get_DevMode
功能描述 :设备类型Get
输入参数 :
输出参数 :无
返 回 值 :设备类型CString
**************************************************************************************************/
CString CDevice::Get_DevMode()
{
	return m_szDevMode;
}

/**************************************************************************************************
函 数 名 :Set_DevIP
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevIP(DWORD dwIP)
{
	m_dwDevIP = dwIP;
}
DWORD CDevice::Get_DevIP()
{
	return m_dwDevIP;
}

/**************************************************************************************************
函 数 名 :Set_DevIP
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void  CDevice::Set_DevIPMask(DWORD dwIPMask)
{
	m_dwDevIPMask = dwIPMask;
}

DWORD CDevice::Get_DevIPMask()
{
	return m_dwDevIPMask;
}

/**************************************************************************************************
函 数 名 :Set_DevName
功能描述 :设备名称Set/Get
输入参数 :szDevName 设备类型
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevName(LPCTSTR szDevName)
{
	m_szDevName = szDevName;
}
CString CDevice::Get_DevName()
{
	return m_szDevName;
}

/**************************************************************************************************
函 数 名 :Set_DevName
功能描述 :设备名称Set/Get
输入参数 :szDevName 设备类型
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevSWVersion(LPCTSTR szVersion)
{
	m_szSWVersion = szVersion;
}
CString CDevice::Get_DevSWVersion()
{
	return m_szSWVersion;
}

/**************************************************************************************************
函 数 名 :Set_PortNum
功能描述 :端口数目Set/Get
输入参数 :iPortNum 端口数目
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_PortNum(int iPortNum)
{
	m_iDevPortNum = iPortNum;
}
int  CDevice::Get_PortNum()
{
	return m_iDevPortNum;
}

/**************************************************************************************************
函 数 名 :Set_DevStatus
功能描述 :设备状态Set/Get
输入参数 :iDevStatus 设备状态
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevStatus(int iDevStatus)
{
	m_iDevStatus = iDevStatus;
}
int  CDevice::Get_DevStatus()
{
	return m_iDevStatus;
}

/**************************************************************************************************
函 数 名 :AddPort
功能描述 :增加端口
输入参数 :pPort 端口类数据指针
输出参数 :无
返 回 值 :1 成功， 0失败
**************************************************************************************************/
int CDevice::AddPort(CPort *pPort)
{
	m_DevPortList.AddTail(pPort);
	return 1;
}

/**************************************************************************************************
函 数 名 :DeletePort
功能描述 :删除端口
输入参数 :pPort 端口类数据指针
输出参数 :无
返 回 值 :1 成功， 0失败
**************************************************************************************************/
int CDevice::DeletePort(CPort *pPort)
{
	POSITION pos;
	pos = m_DevPortList.Find(pPort);
	if (pos == NULL)
	{
		return 0;
	}

	m_DevPortList.RemoveAt(pos);
	
	delete pPort;

	return 1;
}

/**************************************************************************************************
函 数 名 :ClearPort
功能描述 :清除所有端口数据
输入参数 :无 
输出参数 :无
返 回 值 :1 成功， 0失败
**************************************************************************************************/
int CDevice::ClearPort()
{
	while(!m_DevPortList.IsEmpty())
	{
		delete m_DevPortList.RemoveHead();
	}

	return 1;
}

/**************************************************************************************************
函 数 名 :Set_DevMAC
功能描述 :MAC地址Set/Get
输入参数 :szDevMAC MAC地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevMAC(LPCTSTR szDevMAC)
{
	m_szDevMAC = szDevMAC;
}
CString CDevice::Get_DevMAC()
{
	return m_szDevMAC;
}

/**************************************************************************************************
函 数 名 :Set_DevNet1Mode
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet1Mode(BYTE bMode)
{
	m_bDevNet1Mode = bMode;
}
BYTE CDevice::Get_DevNet1Mode()
{
	return m_bDevNet1Mode;
}


/**************************************************************************************************
函 数 名 :Set_DevIP
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet1IP(DWORD dwIP)
{
	m_dwDevNet1IP = dwIP;
}
DWORD CDevice::Get_DevNet1IP()
{
	return m_dwDevNet1IP;
}

/**************************************************************************************************
函 数 名 :Set_DevIPMask
功能描述 :子网掩码 Set/Get
输入参数 :szIPMask 子网掩码
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet1IPMask(DWORD dwIPMask)
{
	m_dwDevNet1IPMask = dwIPMask;
}
DWORD CDevice::Get_DevNet1IPMask()
{
	return m_dwDevNet1IPMask ;
}

/**************************************************************************************************
函 数 名 :Set_DevIPGateWay
功能描述 :GateWay Set/Get
输入参数 :szIPGateWay GateWay
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet1IPGateWay(DWORD dwIPGateWay)
{
    m_dwDevNet1IPGateWay = dwIPGateWay ;
}
DWORD CDevice::Get_DevNet1IPGateWay()
{
	return m_dwDevNet1IPGateWay ;
}



/**************************************************************************************************
函 数 名 :Set_DevNet1Mode
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet2Mode(BYTE bMode)
{
	m_bDevNet2Mode = bMode;
}
BYTE CDevice::Get_DevNet2Mode()
{
	return m_bDevNet2Mode;
}

/**************************************************************************************************
函 数 名 :Set_DevIP
功能描述 :IP地址Set/Get
输入参数 :szIP IP地址
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet2IP(DWORD dwIP)
{
	m_dwDevNet2IP = dwIP;
}
DWORD CDevice::Get_DevNet2IP()
{
	return m_dwDevNet2IP;
}

/**************************************************************************************************
函 数 名 :Set_DevIPMask
功能描述 :子网掩码 Set/Get
输入参数 :szIPMask 子网掩码
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet2IPMask(DWORD dwIPMask)
{
	m_dwDevNet2IPMask = dwIPMask;
}
DWORD CDevice::Get_DevNet2IPMask()
{
	return m_dwDevNet2IPMask ;
}

/**************************************************************************************************
函 数 名 :Set_DevIPGateWay
功能描述 :GateWay Set/Get
输入参数 :szIPGateWay GateWay
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevNet2IPGateWay(DWORD dwIPGateWay)
{
    m_dwDevNet2IPGateWay = dwIPGateWay ;
}
DWORD CDevice::Get_DevNet2IPGateWay()
{
	return m_dwDevNet2IPGateWay ;
}



/**************************************************************************************************
函 数 名 :Set_DevTime
功能描述 :设备时间 Set/Get
输入参数 :szTime 设备时间
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevTime(CTime tTime)
{
	 m_tDevTime = tTime;
}
CTime* CDevice::Get_DevTime()
{
	return &m_tDevTime;
}

/**************************************************************************************************
函 数 名 :Set_DevTimeZone
功能描述 :设备时域 Set/Get
输入参数 :szTimeZone 设备时域
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevTimeZone(int iTimeZone)
{
	m_iDevTimeZone = iTimeZone;
}
int CDevice::Get_DevTimeZone()
{
	return m_iDevTimeZone;
}

/**************************************************************************************************
函 数 名 :Set_DevUpTime
功能描述 :设备运行时间 Set/Get
输入参数 :szTime 设备运行时间
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevUpTime(CTime tTime)
{
	m_tDevUpTime = tTime;
}
CTime* CDevice::Get_DevUpTime()
{
	return &m_tDevUpTime;
}

/**************************************************************************************************
函 数 名 :Set_DevTelnetFlg
功能描述 :Telnet Console状态 Set/Get
输入参数 :iTelnetFlg Telnet Console状态, 1表示打开，0表示关闭
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevTelnetFlg(int iTelnetFlg)
{
	m_iTelnetConsole = iTelnetFlg ;
}
int  CDevice::Get_DevTelnetFlg()
{
	return m_iTelnetConsole ;
}

/**************************************************************************************************
函 数 名 :Set_DevWebFlg
功能描述 :Web Console状态 Set/Get
输入参数 :iWebFlg Web Console状态, 1表示打开，0表示关闭
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_DevWebFlg(int iWebFlg)
{
	m_iWebConsole = iWebFlg;
}
int  CDevice::Get_DevWebFlg()
{
	return m_iWebConsole ;
}

/**************************************************************************************************
函 数 名 :Get_PortList
功能描述 :设备端口数据列表 Get
输入参数 :无
输出参数 :无
返 回 值 :设备端口数据列表指针
**************************************************************************************************/
CPortList* CDevice::Get_PortList()
{
	return &m_DevPortList;
}

/**************************************************************************************************
函 数 名 :Set_CreateTime
功能描述 :设备数据更新时间 Set/Get
输入参数 :szTime 设备运行时间
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CDevice::Set_CreateTime(CTime tTime)
{
	m_tTimeCreated = tTime;
}
CTime* CDevice::Get_CreateTime()
{
	return &m_tTimeCreated;
}

/**************************************************************************************************
函 数 名 :Reboot
功能描述 :设备重启
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
int CDevice::Reboot()
{
	int iRet;

	if (m_pCOMM == NULL)
		return 0;

	iRet = m_pCOMM->Set_Reboot();

	return iRet;
}

/**************************************************************************************************
函 数 名 :Reboot
功能描述 :设备重启
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
int CDevice::ReConnect()
{
	int iRet;

	int m_nLastError = 0;
	int iTimeOut     = 0;

	//new 通讯器验证主机是否存在
	CCOMM * pCOMM = new CCOMM(m_dwDevIP);
	iRet = pCOMM->VerifyHost();
	if (iRet == 0)
	{
		delete pCOMM;
		return 0;
	}
	
	iRet = pCOMM->Get_DevConfig(this);
	if (iRet == 0)
	{
		delete pCOMM;
		return 0;
	}

	iRet = pCOMM->Get_DevNetworkConfig(this);
	if (iRet == 0)
	{
		delete pCOMM;
		return 0;
	}

	this->ClearPort();
	pCOMM->Get_DevAllPortsConfig(this);

	this->m_pCOMM = pCOMM;

	return 1;
}


/**************************************************************************************************
函 数 名 :SaveData
功能描述 :保存设备配置数据
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
int CDevice::SaveData()
{
	int iRet;

	if (m_pCOMM == NULL)
		return 0;

	iRet = m_pCOMM->Set_SaveData();

	return iRet;
}


/**************************************************************************************************
函 数 名 :SayHello
功能描述 :心跳hello报文功能
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
BOOL CDevice::SayHello()
{
	int iRet;

	if (m_pCOMM == NULL)
		return FALSE;

	iRet = m_pCOMM->Set_Hello(this);
	if (iRet !=1)
		return FALSE;


	return TRUE;
}

/**************************************************************************************************
函 数 名 :GetDevStatic
功能描述 :心跳hello报文功能
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
BOOL CDevice::GetDevStatic()
{
	int iRet;

	if (m_pCOMM == NULL)
		return FALSE;

	iRet = m_pCOMM->Get_DevStatic(this);
	if (iRet !=1)
		return FALSE;


	return TRUE;

}



/**************************************************************************************************
函 数 名 :SaveSysParaToDev
功能描述 :配置设备系统参数
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
BOOL CDevice::SaveSysParaToDev()
{
	int iRet;

	if (m_pCOMM == NULL)
	{
		return FALSE;
	}

	iRet = m_pCOMM->Set_DevConfig(this);
	if (iRet !=1)
	{
		return FALSE;
	}
	
	return TRUE;
}

/**************************************************************************************************
函 数 名 :SavePortParaToDev
功能描述 :配置设备端口物理参数
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
BOOL CDevice::SavePortParaToDev(int iPortNo)
{
	int iRet;

	if (m_pCOMM == NULL)
	{
		return FALSE;
	}

	iRet = m_pCOMM->Set_DevPortParaConfig(this, iPortNo);
	if (iRet !=1)
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************************************
函 数 名 :SavePortWorkModeParaToDev
功能描述 :配置设备端口工作模式参数
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
BOOL CDevice::SavePortWorkModeParaToDev(int iPortNo)
{
	int iRet;

	if (m_pCOMM == NULL)
		return FALSE;

	iRet = m_pCOMM->Set_DevPortWorkModeConfig(this, iPortNo);
	if (iRet !=1)
	{
		return FALSE;
	}

	return TRUE;
}

/**************************************************************************************************
函 数 名 :QueryPortByPortNo
功能描述 :根据端口索引获取端口参数数据指针
输入参数 :无
输出参数 :无
返 回 值 :void
**************************************************************************************************/
CPort *CDevice::QueryPortByPortNo(int iPortIndex)
{
	POSITION   pos;
	CPortList *pPortList = NULL;
	CPort     *pPort     = NULL;
	int        iPortNo   ;

	pPortList = Get_PortList();

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
	return NULL;
}
