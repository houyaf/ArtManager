/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����TCPClientPortMode.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: TCPClientģʽ(TCP Client����ģʽ)��ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once
class CTCPClientPortMode :	public CPortChannel
{
public:
	CTCPClientPortMode(void);
	~CTCPClientPortMode(void);

protected:
	DWORD m_dwTargetHostIP1;
	int m_iTargetHostPort1;
	int m_iLocalPort1;

	DWORD m_dwTargetHostIP2;
	int m_iTargetHostPort2;
	int m_iLocalPort2;

	DWORD m_dwTargetHostIP3;
	int m_iTargetHostPort3;
	int m_iLocalPort3;

	DWORD m_dwTargetHostIP4;
	int m_iTargetHostPort4;
	int m_iLocalPort4;

	DWORD m_dwTargetHostIP5;
	int m_iTargetHostPort5;
	int m_iLocalPort5;

	DWORD m_dwTargetHostIP6;
	int m_iTargetHostPort6;
	int m_iLocalPort6;

public:
	void Set_TargetHost1(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost1(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost2(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost2(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost3(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost3(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost4(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost4(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost5(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost5(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost6(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost6(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

};

