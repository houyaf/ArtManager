// ChannelStatistics.cpp : 实现文件
//

#include "stdafx.h"
#include "ChannelStatistics.h"

// CChannelStatistics

CChannelStatistics::CChannelStatistics()
{

}

/*
    unsigned long  m_ulRemoteIP  ;
	unsigned short m_ulRemotePort;

	unsigned long  m_ulSendNum ;
	unsigned long  m_ulSendSize;
	unsigned long  m_ulRecNum  ;
	unsigned long  m_ulRecSize ;

	unsigned long  m_ulLinkNum ;
*/

CChannelStatistics::CChannelStatistics(unsigned char ucChannelNo)
	:m_ucChannelNO(ucChannelNo)
	,m_ulRemoteIP(0)
	,m_usRemotePort(0)
	,m_ulSendNum(0)
	,m_ulSendSize(0)
	,m_ulRecNum(0)
	,m_ulRecSize(0)
	,m_ulLinkNum(0)
{

}

CChannelStatistics::~CChannelStatistics()
{
}


// CChannelStatistics 成员函数
