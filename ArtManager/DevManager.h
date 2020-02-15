/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：DevManager.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 设备管理类DevManager声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

// CDevManager 命令目标
class CDevice ;
class CCOMM   ;
class CDevManager : public CObject
{
public:
	CDevManager();
	virtual ~CDevManager();

protected:

	//设备数据列表;
	CDeviceList m_DevList;
	
public:
	//设备数据列表Get;
	CDeviceList * Get_DevList();

public:

	//清除设备数据
	void ClearDevices();

	//显示设备数据,Debug
	void ShowDevices();

	//新增设备
	int AddDevice(CDevice* pDevice);

	//删除设备
	int DeleteDevice(CDevice *pDevice);

	//根据IP查找设备数据
	CDevice *QueryDeviceByIP(DWORD dwIP);

	//根据IP和端口號查找端口数据
	CPort *QueryPortByIPandPortNo(DWORD dwIP, int iPortIndex);


public :

	//生成设备数据,Debug
	void GenerateDeviceData();
	void GeneratePortData(CDevice *pDevice, int iPortNum);
	void GeneratePortModeData(CPort *pPort, int iPortMode);
	void GenerateTCPServerPortModeData(CPort *pPort);
	void GenerateTCPClientPortModeData(CPort *pPort);
	void GenerateUDPPortModeData(CPort *pPort);
	void GenerateRealCOMPortModeData(CPort *pPort);
};


