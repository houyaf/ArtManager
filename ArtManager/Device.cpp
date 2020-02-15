/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����Device.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: Device��ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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
// CDevice ��Ա����

/**************************************************************************************************
�� �� �� :Set_DevCOMM
�������� :�豸ͨѶ��Set
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
void  CDevice::Set_DevCOMM(CCOMM *pCOMM)
{
	ASSERT(pCOMM);

	m_pCOMM = pCOMM;

}

/**************************************************************************************************
�� �� �� :Set_DevMode
�������� :�豸����Set
������� :szDevMode �豸����
������� :��
�� �� ֵ :void
**************************************************************************************************/
void CDevice::Set_DevMode(LPCTSTR szDevMode)
{
	m_szDevMode = szDevMode;
}

/**************************************************************************************************
�� �� �� :Get_DevMode
�������� :�豸����Get
������� :
������� :��
�� �� ֵ :�豸����CString
**************************************************************************************************/
CString CDevice::Get_DevMode()
{
	return m_szDevMode;
}

/**************************************************************************************************
�� �� �� :Set_DevIP
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIP
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevName
�������� :�豸����Set/Get
������� :szDevName �豸����
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevName
�������� :�豸����Set/Get
������� :szDevName �豸����
������� :��
�� �� ֵ :void
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
�� �� �� :Set_PortNum
�������� :�˿���ĿSet/Get
������� :iPortNum �˿���Ŀ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevStatus
�������� :�豸״̬Set/Get
������� :iDevStatus �豸״̬
������� :��
�� �� ֵ :void
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
�� �� �� :AddPort
�������� :���Ӷ˿�
������� :pPort �˿�������ָ��
������� :��
�� �� ֵ :1 �ɹ��� 0ʧ��
**************************************************************************************************/
int CDevice::AddPort(CPort *pPort)
{
	m_DevPortList.AddTail(pPort);
	return 1;
}

/**************************************************************************************************
�� �� �� :DeletePort
�������� :ɾ���˿�
������� :pPort �˿�������ָ��
������� :��
�� �� ֵ :1 �ɹ��� 0ʧ��
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
�� �� �� :ClearPort
�������� :������ж˿�����
������� :�� 
������� :��
�� �� ֵ :1 �ɹ��� 0ʧ��
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
�� �� �� :Set_DevMAC
�������� :MAC��ַSet/Get
������� :szDevMAC MAC��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevNet1Mode
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIP
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIPMask
�������� :�������� Set/Get
������� :szIPMask ��������
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIPGateWay
�������� :GateWay Set/Get
������� :szIPGateWay GateWay
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevNet1Mode
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIP
�������� :IP��ַSet/Get
������� :szIP IP��ַ
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIPMask
�������� :�������� Set/Get
������� :szIPMask ��������
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevIPGateWay
�������� :GateWay Set/Get
������� :szIPGateWay GateWay
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevTime
�������� :�豸ʱ�� Set/Get
������� :szTime �豸ʱ��
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevTimeZone
�������� :�豸ʱ�� Set/Get
������� :szTimeZone �豸ʱ��
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevUpTime
�������� :�豸����ʱ�� Set/Get
������� :szTime �豸����ʱ��
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevTelnetFlg
�������� :Telnet Console״̬ Set/Get
������� :iTelnetFlg Telnet Console״̬, 1��ʾ�򿪣�0��ʾ�ر�
������� :��
�� �� ֵ :void
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
�� �� �� :Set_DevWebFlg
�������� :Web Console״̬ Set/Get
������� :iWebFlg Web Console״̬, 1��ʾ�򿪣�0��ʾ�ر�
������� :��
�� �� ֵ :void
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
�� �� �� :Get_PortList
�������� :�豸�˿������б� Get
������� :��
������� :��
�� �� ֵ :�豸�˿������б�ָ��
**************************************************************************************************/
CPortList* CDevice::Get_PortList()
{
	return &m_DevPortList;
}

/**************************************************************************************************
�� �� �� :Set_CreateTime
�������� :�豸���ݸ���ʱ�� Set/Get
������� :szTime �豸����ʱ��
������� :��
�� �� ֵ :void
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
�� �� �� :Reboot
�������� :�豸����
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :Reboot
�������� :�豸����
������� :��
������� :��
�� �� ֵ :void
**************************************************************************************************/
int CDevice::ReConnect()
{
	int iRet;

	int m_nLastError = 0;
	int iTimeOut     = 0;

	//new ͨѶ����֤�����Ƿ����
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
�� �� �� :SaveData
�������� :�����豸��������
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :SayHello
�������� :����hello���Ĺ���
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :GetDevStatic
�������� :����hello���Ĺ���
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :SaveSysParaToDev
�������� :�����豸ϵͳ����
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :SavePortParaToDev
�������� :�����豸�˿��������
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :SavePortWorkModeParaToDev
�������� :�����豸�˿ڹ���ģʽ����
������� :��
������� :��
�� �� ֵ :void
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
�� �� �� :QueryPortByPortNo
�������� :���ݶ˿�������ȡ�˿ڲ�������ָ��
������� :��
������� :��
�� �� ֵ :void
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
