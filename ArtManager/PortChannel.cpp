/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：PortMode.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: ChannelMode(端口Channel工作模式)实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

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


// CPortChannel 成员函数
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