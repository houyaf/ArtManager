/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：UDPPortMode.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: UDP模式(UDP工作模式)类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#include "stdafx.h"

CUDPPortMode::CUDPPortMode(void)
{
}


CUDPPortMode::~CUDPPortMode(void)
{
}

void CUDPPortMode::Set_ListenPort1(int iListenPort)
{
	m_iListenPort1 = iListenPort;
}
int  CUDPPortMode::Get_ListenPort1()
{
	return m_iListenPort1;
}

void CUDPPortMode::Set_TargetHost1(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort)
{
	m_dwTagetHostIP_S1 = dwHostIP_S;
	m_dwTagetHostIP_E1 = dwHostIP_E;
	m_iTargetHostPort1 = iPort;
}
void CUDPPortMode::Get_TargetHost1(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int& iPort)
{
	dwHostIP_S = m_dwTagetHostIP_S1  ;
	dwHostIP_E = m_dwTagetHostIP_E1  ;
	iPort      = m_iTargetHostPort1  ;
}

void CUDPPortMode::Set_TargetHost2(DWORD dwHostIP_S , DWORD dwHostIP_E, int iPort)
{
	m_dwTagetHostIP_S2 = dwHostIP_S;
	m_dwTagetHostIP_E2 = dwHostIP_E;
	m_iTargetHostPort2 = iPort;
}
void CUDPPortMode::Get_TargetHost2(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int& iPort)
{
	dwHostIP_S = m_dwTagetHostIP_S2  ;
	dwHostIP_E = m_dwTagetHostIP_E2  ;
	iPort      = m_iTargetHostPort2  ;
}

void CUDPPortMode::Set_TargetHost3(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort)
{
	m_dwTagetHostIP_S3 = dwHostIP_S;
	m_dwTagetHostIP_E3 = dwHostIP_E;
	m_iTargetHostPort3 = iPort;
}
void CUDPPortMode::Get_TargetHost3(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int& iPort)
{
	dwHostIP_S = m_dwTagetHostIP_S3  ;
	dwHostIP_E = m_dwTagetHostIP_E3  ;
	iPort      = m_iTargetHostPort3  ;
}

void CUDPPortMode::Set_TargetHost4(DWORD dwHostIP_S , DWORD dwHostIP_E , int iPort)
{
	m_dwTagetHostIP_S4 = dwHostIP_S;
	m_dwTagetHostIP_E4 = dwHostIP_E;
	m_iTargetHostPort4 = iPort;
}
void CUDPPortMode::Get_TargetHost4(DWORD &dwHostIP_S, DWORD &dwHostIP_E, int& iPort)
{
	dwHostIP_S = m_dwTagetHostIP_S4  ;
	dwHostIP_E = m_dwTagetHostIP_E4  ;
	iPort      = m_iTargetHostPort4  ;
}