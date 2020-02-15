/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：PortMode.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: PortMode(端口工作模式)类接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

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


