/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����PortMode.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: PortMode(�˿ڹ���ģʽ)��ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once
class CPortChannel : public CObject
{
public:
	CPortChannel();
	virtual ~CPortChannel();

protected:
	CString m_szChannelModeName;
	int     m_iChannelModeID;

	int     m_iChannelID ;

public:
	void Set_ChannelID(int iChannel);
    int  Get_ChannelID();

	void Set_ModeName(LPCTSTR szModeName);
    CString  Get_ModeName();

	void Set_ModeID(int iModeID);
    int  Get_ModeID();
};


