/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����TCPServerPortMode.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: TCPServerģʽ(TCP Server����ģʽ)��ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once
class CTCPServerPortMode :	public CPortChannel
{
public:
	CTCPServerPortMode(void);
	~CTCPServerPortMode(void);

protected:
	int m_iListenPort1;
	int m_iMaxConnection1;

	int m_iListenPort2;
	int m_iMaxConnection2;

	int m_iListenPort3;
	int m_iMaxConnection3;

	int m_iListenPort4;
	int m_iMaxConnection4;

	int m_iListenPort5;
	int m_iMaxConnection5;

	int m_iListenPort6;
	int m_iMaxConnection6;
public:

	void Set_ListenPort1(int iListenPort);
	int  Get_ListenPort1();

	void Set_MaxConnection1(int iMaxConnection);
	int  Get_MaxConnection1();
	

	void Set_ListenPort2(int iListenPort);
	int  Get_ListenPort2();

	void Set_MaxConnection2(int iMaxConnection);
	int  Get_MaxConnection2();

	void Set_ListenPort3(int iListenPort);
	int  Get_ListenPort3();

	void Set_MaxConnection3(int iMaxConnection);
	int  Get_MaxConnection3();

	void Set_ListenPort4(int iListenPort);
	int  Get_ListenPort4();

	void Set_MaxConnection4(int iMaxConnection);
	int  Get_MaxConnection4();

	void Set_ListenPort5(int iListenPort);
	int  Get_ListenPort5();

	void Set_MaxConnection5(int iMaxConnection);
	int  Get_MaxConnection5();

	void Set_ListenPort6(int iListenPort);
	int  Get_ListenPort6();

	void Set_MaxConnection6(int iMaxConnection);
	int  Get_MaxConnection6();
};

