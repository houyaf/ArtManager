/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����Device.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: Device������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once

// CDevice ����Ŀ��
class CPort;

class CCOMM    ;

class CDevice : public CObject
{
public:
	CDevice();
	~CDevice();

public:
	CCOMM    *m_pCOMM  ;

public:
	//Set �豸ͨѶ��
	void  Set_DevCOMM(CCOMM *pCOMM);

protected:
	//�豸����
	CString m_szDevMode;

	int m_iDevModeID;

	//�豸����(Sysname)
	CString m_szDevName;

	//MAC��ַ
	CString m_szDevMAC;

	//IP��ַ
	DWORD m_dwDevIP;

	//IP Mask
	DWORD m_dwDevIPMask;

	//Eth0 Mode
	BYTE  m_bDevNet1Mode;
	//Eth0 IP
	DWORD m_dwDevNet1IP;
	//Eth0 �������� 
	DWORD m_dwDevNet1IPMask;
	//Eth0 GateWay 
	DWORD m_dwDevNet1IPGateWay;

	//Eth1 Mode
	BYTE  m_bDevNet2Mode;
	//Eth0 IP
	DWORD m_dwDevNet2IP;
	//Eth0 �������� 
	DWORD m_dwDevNet2IPMask;
	//Eth0 GateWay 
	DWORD m_dwDevNet2IPGateWay;

	//�豸ʱ��
	CTime   m_tDevTime;

	//�豸ʱ��
	int   m_iDevTimeZone;

	//�豸����ʱ��
	CTime   m_tDevUpTime;

	//����汾
	CString m_szSWVersion;

	//Telnet Console״̬
	int     m_iTelnetConsole;

    //WEB Console״̬
	int     m_iWebConsole;

	//�˿���Ŀ
	int     m_iDevPortNum ;

	//�豸״̬
	int     m_iDevStatus;

    //�豸���ݸ���ʱ��
    CTime   m_tTimeCreated;

protected: 
	//�˿�����list
	CPortList m_DevPortList ;


public:
	//�豸����
	void Set_DevMode(LPCTSTR szDevMode);
	CString Get_DevMode();

	void Set_DevModeID(int iModeID){ m_iDevModeID = iModeID ;};
	int Get_DevModeID() { return m_iDevModeID ; };

	//Sysname
	void Set_DevName(LPCTSTR szDevName);
	CString Get_DevName();

	//IP
	void Set_DevIP(DWORD dwIP);
	DWORD Get_DevIP();

	//IP Mask
	void  Set_DevIPMask(DWORD dwIPMask);
	DWORD Get_DevIPMask();

    //MAC��ַ
	void Set_DevMAC(LPCTSTR szDevMAC);
	CString Get_DevMAC();

	//Net1 Mode
	void Set_DevNet1Mode(BYTE bMode);
	BYTE Get_DevNet1Mode();

	//Net1 IP
	void Set_DevNet1IP(DWORD dwIP);
	DWORD Get_DevNet1IP();

	//Net1 �������� 
	void Set_DevNet1IPMask(DWORD dwIPMask);
	DWORD Get_DevNet1IPMask();

	//Net1 GateWay 
	void Set_DevNet1IPGateWay(DWORD dwIPGateWay);
	DWORD Get_DevNet1IPGateWay();

	//Net2 Mode
	void Set_DevNet2Mode(BYTE bMode);
	BYTE Get_DevNet2Mode();

	//Net2 IP
	void Set_DevNet2IP(DWORD dwIP);
	DWORD Get_DevNet2IP();

	//Net2 �������� 
	void Set_DevNet2IPMask(DWORD dwIPMask);
	DWORD Get_DevNet2IPMask();

	//Net2 GateWay 
	void Set_DevNet2IPGateWay(DWORD dwIPGateWay);
	DWORD Get_DevNet2IPGateWay();


	//�豸ʱ��
	void Set_DevTime(CTime tTime);
	CTime* Get_DevTime();

	//�豸ʱ��
	void Set_DevTimeZone(int iTimeZone);
	int Get_DevTimeZone();

	//�豸����ʱ��
	void Set_DevUpTime(CTime tTime);
	CTime* Get_DevUpTime();

	//����汾
	void Set_DevSWVersion(LPCTSTR szVersion);
	CString Get_DevSWVersion();

	//Telnet Console״̬
	void Set_DevTelnetFlg(int iTelnetFlg);
	int  Get_DevTelnetFlg();

    //WEB Console״̬
	void Set_DevWebFlg(int iTelnetFlg);
	int  Get_DevWebFlg();


	//�˿���Ŀ
	void Set_PortNum(int iPortNum);
	int  Get_PortNum();


	//�豸״̬
	void Set_DevStatus(int iDevStatus);
	int  Get_DevStatus();

	//�豸���ݸ���ʱ��
	void Set_CreateTime(CTime tTime);
	CTime* Get_CreateTime();

	//��ȡ�˿������б�
	CPortList* Get_PortList();
public:
	//���Ӷ˿�
	int AddPort(CPort *pPort);

	//ɾ���˿�
	int DeletePort(CPort *pPort);

	//��ն˿�����
	int ClearPort();

	//���ݶ˿�������ȡ�˿�����ָ��
	CPort *QueryPortByPortNo(int iPortIndex);

public:
	//�豸����
	int ReConnect();

	int Reboot();
	int SaveData();

	BOOL SayHello();

	BOOL GetDevStatic();

	BOOL SaveSysParaToDev();
	BOOL SavePortParaToDev(int iPortNo);
	BOOL SavePortWorkModeParaToDev(int iPortNo);
};


