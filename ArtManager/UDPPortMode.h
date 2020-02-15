/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����UDPPortMode.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: UDPģʽ(UDP����ģʽ)��ӿ� 
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once
class CUDPPortMode :	public CPortChannel
{
public:
	CUDPPortMode(void);
	~CUDPPortMode(void);

protected:
	int m_iListenPort1;

	DWORD m_dwTagetHostIP_S1;
	DWORD m_dwTagetHostIP_E1;
	int   m_iTargetHostPort1;

	DWORD m_dwTagetHostIP_S2;
	DWORD m_dwTagetHostIP_E2;
	int   m_iTargetHostPort2;

	DWORD m_dwTagetHostIP_S3;
	DWORD m_dwTagetHostIP_E3;
	int   m_iTargetHostPort3;

	DWORD m_dwTagetHostIP_S4;
	DWORD m_dwTagetHostIP_E4;
	int   m_iTargetHostPort4;

public:
	void Set_ListenPort1(int iListenPort);
	int  Get_ListenPort1();

	void Set_TargetHost1(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort);
	void Get_TargetHost1(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int &iPort);

	void Set_TargetHost2(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort);
	void Get_TargetHost2(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int &iPort);

	void Set_TargetHost3(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort);
	void Get_TargetHost3(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int &iPort);

	void Set_TargetHost4(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort);
	void Get_TargetHost4(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int &iPort);
};

