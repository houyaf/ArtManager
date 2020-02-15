/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����Port.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �˿���CPortʵ��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#include "stdafx.h"

// CPort

CPort::CPort()
{
	m_pChannelStatic1 = new CChannelStatistics(1);
	m_pChannelStatic2 = new CChannelStatistics(2);
	m_pChannelStatic3 = new CChannelStatistics(3);
	m_pChannelStatic4 = new CChannelStatistics(4);
	m_pChannelStatic5 = new CChannelStatistics(5);
	m_pChannelStatic6 = new CChannelStatistics(6);
}

CPort::~CPort()
{
	
}

//�˿ں�
void CPort::Set_Index(int iPortIndex)
{
	m_iPortIndex = iPortIndex;
}

int  CPort::Get_Index()
{
	return m_iPortIndex;
}


	//�˿ڿ���
void  CPort::Set_PortSwitch(int iSwitch)
{
	m_iPortSwitch = iSwitch;
}

int   CPort::Get_PortSwitch()
{
	return m_iPortSwitch;
}

//�˿�����
void CPort::Set_PortName(LPCTSTR szPortName)
{
	m_szPortName = szPortName;
}
CString CPort::Get_PortName()
{
	return m_szPortName;
}

//������
void  CPort::Set_BaudRate(int iBaudRate)
{
	m_iBaudRate = iBaudRate;
}
int   CPort::Get_BaudRate()
{
	return m_iBaudRate;
}

//��żУ��λ
void    CPort::Set_Parity(int iParaty)
{
	m_iParity = iParaty;
}
int CPort::Get_Parity()
{
	return m_iParity;
}

//����λ
void   CPort::Set_DataBits(int iDataBits)
{
	m_iDataBits = iDataBits;
}
int    CPort::Get_DataBits()
{
	return m_iDataBits ;
}

//ֹͣλ
void   CPort::Set_StopBits(int iStopBits)
{
	m_iStopBits = iStopBits;
}
int    CPort::Get_StopBits()
{
	return m_iStopBits;
}

//����
void  CPort::Set_FlowCtrl(int iFlowCtrl)
{
	m_iFlowCtrl = iFlowCtrl ;
}
int   CPort::Get_FlowCtrl()
{
	return m_iFlowCtrl;
}

//�ӿ�ģʽ:RS232/RS485/RS422
void  CPort::Set_Interface(int iInterface)
{
	m_iInterface = iInterface ;
}
int   CPort::Get_Interface()
{
	return m_iInterface;
}

//�˿�״̬
void CPort::Set_PortStatus(int iPortStatus)
{
	m_iPortStatus = iPortStatus;
}

int  CPort::Get_PortStatus()
{
	return m_iPortStatus;
}

//��ȡ�˿�Channel�б�
CChannelList* CPort::Get_ChannelList()
{
	return &m_ChannelList;
}

//���Ӷ˿�Channel
int CPort::AddChannel(CPortChannel *pChannel)
{
	m_ChannelList.AddTail(pChannel);

	return 1;
}


//ɾ���˿�Channel
int CPort::DeleteChannel(CPortChannel *pChannel)
{
	POSITION pos;
	pos = m_ChannelList.Find(pChannel);
	if (pos == NULL)
	{
		return 0;
	}

	m_ChannelList.RemoveAt(pos);
	
	delete pChannel;

	return 1;
}

//��ն˿�Channel����
int CPort::ClearChannels()
{
	while(!m_ChannelList.IsEmpty())
	{
		delete m_ChannelList.RemoveHead();
	}

	return 1;
}

//���ݶ˿�������ȡ�˿�Channel����ָ��
CPortChannel *CPort::QueryChannelByNo(int iChannel)
{
	POSITION   pos;
	CChannelList *pChannelList = NULL;
	CPortChannel *pChannel     = NULL;
	int           iChannelID   ;

	pChannelList = Get_ChannelList();

	if (pChannelList != NULL)
	{
		pos = pChannelList->GetHeadPosition();
		while (pos != NULL)
		{
			pChannel = pChannelList->GetNext(pos);
			if (pChannel != NULL)
			{
				iChannelID = pChannel->Get_ChannelID();

				if (iChannelID == iChannel)
				{
					return pChannel ;
				}
			}
		}
	}
	return NULL;
}



int CPort::Get_ChannelNum()
{
	return m_iChannelNum;
}

void CPort::Set_ChannelNum(int iChannel)
{
	m_iChannelNum = iChannel;
}
