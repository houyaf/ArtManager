/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：COMM.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: COMM类声明，负责整个系统的Socket IO.
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once

class CXSocket ;
class CCOMM : public CObject
{
public:
	CCOMM(DWORD dwIP);
	CCOMM(DWORD dwIP, int iPort);
	CCOMM(SOCKET hSocket);
	virtual ~CCOMM();

public:
	CXSocket    *m_pSocket ;
	DWORD        m_dwIP    ;
	int          m_iPort   ; 
public:

	

public:
	//验证是否存在主机
	int VerifyHost();

	//从设备上获取信息
	int Get_DevConfig(CDevice *pDevice);
	int Get_DevNetworkConfig(CDevice *pDevice);

	//从设备上获取所有PORT配置信息
	int Get_DevAllPortsConfig(CDevice *pDevice); 

	//从设备上获取PORT配置信息
	int Get_DevPortConfig(CDevice *pDevice, int iPortIndex); 

	//配置设备上信息
	int Set_DevConfig(CDevice *pDevice);

	//配置设备所有端口信息
	int Set_DevAllPortsConfig(CDevice *pDevice); 

	//配置设备单个端口物理参数信息
	int Set_DevPortParaConfig(CDevice *pDevice, int iPortIndex); 

	//配置设备单个端口工作模式信息
	int Set_DevPortWorkModeConfig(CDevice *pDevice, int iPortIndex); 
	

	//验证主机是否设备，发送获取设备信息的报文
	CDevice * VerfyDevice();

	//重启设备
	int Set_Reboot();

	//保存设备配置数据
	int Set_SaveData();

	//心跳报文
	int Set_Hello(CDevice *pDevice);

	//从设备上获取PORT上Channel的数据转发统计项
	int Get_DevPortChannelStatic(CDevice *pDevice, int iPortIndex, unsigned char ucChannelNo);

	//从设备上获取PORT上的数据转发统计项
	int Get_DevPortStatic(CDevice *pDevice, int iPortIndex);

	//从设备上获取数据转发统计项
	int Get_DevStatic(CDevice *pDevice);

	//发送pszMsg,并获取响应消息
	int SendMsgAndGetResponse(char *pszData, int iDataSize,  char *pszRecvBuf, int iRecvBufSize, int  *iRecvDataSize);

};


