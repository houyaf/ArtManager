/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：TCPClientPortMode.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: TCPClient模式(TCP Client工作模式)类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#include "stdafx.h"

CTCPClientPortMode::CTCPClientPortMode(void)
{
}


CTCPClientPortMode::~CTCPClientPortMode(void)
{
}

void CTCPClientPortMode::Set_TargetHost1(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP1  = dwHostIP;
	m_iTargetHostPort1 = iHostPort;
	m_iLocalPort1      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost1(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP       = m_dwTargetHostIP1 ;
	iHostPort      = m_iTargetHostPort1;
	iLocalPort     = m_iLocalPort1     ;
}

void CTCPClientPortMode::Set_TargetHost2(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP2  = dwHostIP;
	m_iTargetHostPort2 = iHostPort;
	m_iLocalPort2      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost2(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP           = m_dwTargetHostIP2 ;
	iHostPort          = m_iTargetHostPort2;
	iLocalPort         = m_iLocalPort2     ;
}

void CTCPClientPortMode::Set_TargetHost3(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP3  = dwHostIP;
	m_iTargetHostPort3 = iHostPort;
	m_iLocalPort3      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost3(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP           = m_dwTargetHostIP3 ;
	iHostPort          = m_iTargetHostPort3;
	iLocalPort         = m_iLocalPort3     ;
}

void CTCPClientPortMode::Set_TargetHost4(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP4  = dwHostIP;
	m_iTargetHostPort4 = iHostPort;
	m_iLocalPort4      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost4(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP           = m_dwTargetHostIP4 ;
	iHostPort          = m_iTargetHostPort4;
	iLocalPort         = m_iLocalPort4     ;
}

void CTCPClientPortMode::Set_TargetHost5(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP5  = dwHostIP;
	m_iTargetHostPort5 = iHostPort;
	m_iLocalPort5      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost5(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP           = m_dwTargetHostIP5 ;
	iHostPort          = m_iTargetHostPort5;
	iLocalPort         = m_iLocalPort5     ;
}

void CTCPClientPortMode::Set_TargetHost6(DWORD dwHostIP , int iHostPort, int iLocalPort)
{
	m_dwTargetHostIP6  = dwHostIP;
	m_iTargetHostPort6 = iHostPort;
	m_iLocalPort6      = iLocalPort;
}
void CTCPClientPortMode::Get_TargetHost6(DWORD &dwHostIP, int &iHostPort, int& iLocalPort)
{
	dwHostIP           = m_dwTargetHostIP6 ;
	iHostPort          = m_iTargetHostPort6;
	iLocalPort         = m_iLocalPort6     ;
}
