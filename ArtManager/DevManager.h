/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����DevManager.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �豸������DevManager����
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once

// CDevManager ����Ŀ��
class CDevice ;
class CCOMM   ;
class CDevManager : public CObject
{
public:
	CDevManager();
	virtual ~CDevManager();

protected:

	//�豸�����б�;
	CDeviceList m_DevList;
	
public:
	//�豸�����б�Get;
	CDeviceList * Get_DevList();

public:

	//����豸����
	void ClearDevices();

	//��ʾ�豸����,Debug
	void ShowDevices();

	//�����豸
	int AddDevice(CDevice* pDevice);

	//ɾ���豸
	int DeleteDevice(CDevice *pDevice);

	//����IP�����豸����
	CDevice *QueryDeviceByIP(DWORD dwIP);

	//����IP�Ͷ˿�̖���Ҷ˿�����
	CPort *QueryPortByIPandPortNo(DWORD dwIP, int iPortIndex);


public :

	//�����豸����,Debug
	void GenerateDeviceData();
	void GeneratePortData(CDevice *pDevice, int iPortNum);
	void GeneratePortModeData(CPort *pPort, int iPortMode);
	void GenerateTCPServerPortModeData(CPort *pPort);
	void GenerateTCPClientPortModeData(CPort *pPort);
	void GenerateUDPPortModeData(CPort *pPort);
	void GenerateRealCOMPortModeData(CPort *pPort);
};


