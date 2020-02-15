/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����COMM.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: COMM����������������ϵͳ��Socket IO.
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once

class CXSocket ;
class CCOMM : public CObject
{
public:
	CCOMM(DWORD dwIP);
	CCOMM(DWORD dwIP, int iPort);
	CCOMM(SOCKET hSocket);
	virtual ~CCOMM();

public:
	CXSocket    *m_pSocket ;
	DWORD        m_dwIP    ;
	int          m_iPort   ; 
public:

	

public:
	//��֤�Ƿ��������
	int VerifyHost();

	//���豸�ϻ�ȡ��Ϣ
	int Get_DevConfig(CDevice *pDevice);
	int Get_DevNetworkConfig(CDevice *pDevice);

	//���豸�ϻ�ȡ����PORT������Ϣ
	int Get_DevAllPortsConfig(CDevice *pDevice); 

	//���豸�ϻ�ȡPORT������Ϣ
	int Get_DevPortConfig(CDevice *pDevice, int iPortIndex); 

	//�����豸����Ϣ
	int Set_DevConfig(CDevice *pDevice);

	//�����豸���ж˿���Ϣ
	int Set_DevAllPortsConfig(CDevice *pDevice); 

	//�����豸�����˿����������Ϣ
	int Set_DevPortParaConfig(CDevice *pDevice, int iPortIndex); 

	//�����豸�����˿ڹ���ģʽ��Ϣ
	int Set_DevPortWorkModeConfig(CDevice *pDevice, int iPortIndex); 
	

	//��֤�����Ƿ��豸�����ͻ�ȡ�豸��Ϣ�ı���
	CDevice * VerfyDevice();

	//�����豸
	int Set_Reboot();

	//�����豸��������
	int Set_SaveData();

	//��������
	int Set_Hello(CDevice *pDevice);

	//���豸�ϻ�ȡPORT��Channel������ת��ͳ����
	int Get_DevPortChannelStatic(CDevice *pDevice, int iPortIndex, unsigned char ucChannelNo);

	//���豸�ϻ�ȡPORT�ϵ�����ת��ͳ����
	int Get_DevPortStatic(CDevice *pDevice, int iPortIndex);

	//���豸�ϻ�ȡ����ת��ͳ����
	int Get_DevStatic(CDevice *pDevice);

	//����pszMsg,����ȡ��Ӧ��Ϣ
	int SendMsgAndGetResponse(char *pszData, int iDataSize,  char *pszRecvBuf, int iRecvBufSize, int  *iRecvDataSize);

};


