/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����PortMode.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ChannelMode(�˿�Channel����ģʽ)ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#include "stdafx.h"

// CPortChannel

CPortChannel::CPortChannel()
{

}

CPortChannel::~CPortChannel()
{

}

void CPortChannel::Set_ChannelID(int iChannel)
{
	m_iChannelID = iChannel;
}
int  CPortChannel::Get_ChannelID()
{
	return m_iChannelID;
}


// CPortChannel ��Ա����
void CPortChannel::Set_ModeName(LPCTSTR szModeName)
{
	m_szChannelModeName = szModeName;
}
CString  CPortChannel::Get_ModeName()
{
	return m_szChannelModeName ;
}

void CPortChannel::Set_ModeID(int iModeID)
{
	m_iChannelModeID = iModeID;
}
int  CPortChannel::Get_ModeID()
{
	return m_iChannelModeID;
}