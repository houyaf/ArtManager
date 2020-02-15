/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：Device.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: Device类声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

// CDevice 命令目标
class CPort;

class CCOMM    ;

class CDevice : public CObject
{
public:
	CDevice();
	~CDevice();

public:
	CCOMM    *m_pCOMM  ;

public:
	//Set 设备通讯器
	void  Set_DevCOMM(CCOMM *pCOMM);

protected:
	//设备类型
	CString m_szDevMode;

	int m_iDevModeID;

	//设备名称(Sysname)
	CString m_szDevName;

	//MAC地址
	CString m_szDevMAC;

	//IP地址
	DWORD m_dwDevIP;

	//IP Mask
	DWORD m_dwDevIPMask;

	//Eth0 Mode
	BYTE  m_bDevNet1Mode;
	//Eth0 IP
	DWORD m_dwDevNet1IP;
	//Eth0 子网掩码 
	DWORD m_dwDevNet1IPMask;
	//Eth0 GateWay 
	DWORD m_dwDevNet1IPGateWay;

	//Eth1 Mode
	BYTE  m_bDevNet2Mode;
	//Eth0 IP
	DWORD m_dwDevNet2IP;
	//Eth0 子网掩码 
	DWORD m_dwDevNet2IPMask;
	//Eth0 GateWay 
	DWORD m_dwDevNet2IPGateWay;

	//设备时间
	CTime   m_tDevTime;

	//设备时区
	int   m_iDevTimeZone;

	//设备运行时间
	CTime   m_tDevUpTime;

	//软件版本
	CString m_szSWVersion;

	//Telnet Console状态
	int     m_iTelnetConsole;

    //WEB Console状态
	int     m_iWebConsole;

	//端口数目
	int     m_iDevPortNum ;

	//设备状态
	int     m_iDevStatus;

    //设备数据更新时间
    CTime   m_tTimeCreated;

protected: 
	//端口数据list
	CPortList m_DevPortList ;


public:
	//设备类型
	void Set_DevMode(LPCTSTR szDevMode);
	CString Get_DevMode();

	void Set_DevModeID(int iModeID){ m_iDevModeID = iModeID ;};
	int Get_DevModeID() { return m_iDevModeID ; };

	//Sysname
	void Set_DevName(LPCTSTR szDevName);
	CString Get_DevName();

	//IP
	void Set_DevIP(DWORD dwIP);
	DWORD Get_DevIP();

	//IP Mask
	void  Set_DevIPMask(DWORD dwIPMask);
	DWORD Get_DevIPMask();

    //MAC地址
	void Set_DevMAC(LPCTSTR szDevMAC);
	CString Get_DevMAC();

	//Net1 Mode
	void Set_DevNet1Mode(BYTE bMode);
	BYTE Get_DevNet1Mode();

	//Net1 IP
	void Set_DevNet1IP(DWORD dwIP);
	DWORD Get_DevNet1IP();

	//Net1 子网掩码 
	void Set_DevNet1IPMask(DWORD dwIPMask);
	DWORD Get_DevNet1IPMask();

	//Net1 GateWay 
	void Set_DevNet1IPGateWay(DWORD dwIPGateWay);
	DWORD Get_DevNet1IPGateWay();

	//Net2 Mode
	void Set_DevNet2Mode(BYTE bMode);
	BYTE Get_DevNet2Mode();

	//Net2 IP
	void Set_DevNet2IP(DWORD dwIP);
	DWORD Get_DevNet2IP();

	//Net2 子网掩码 
	void Set_DevNet2IPMask(DWORD dwIPMask);
	DWORD Get_DevNet2IPMask();

	//Net2 GateWay 
	void Set_DevNet2IPGateWay(DWORD dwIPGateWay);
	DWORD Get_DevNet2IPGateWay();


	//设备时间
	void Set_DevTime(CTime tTime);
	CTime* Get_DevTime();

	//设备时域
	void Set_DevTimeZone(int iTimeZone);
	int Get_DevTimeZone();

	//设备运行时间
	void Set_DevUpTime(CTime tTime);
	CTime* Get_DevUpTime();

	//软件版本
	void Set_DevSWVersion(LPCTSTR szVersion);
	CString Get_DevSWVersion();

	//Telnet Console状态
	void Set_DevTelnetFlg(int iTelnetFlg);
	int  Get_DevTelnetFlg();

    //WEB Console状态
	void Set_DevWebFlg(int iTelnetFlg);
	int  Get_DevWebFlg();


	//端口数目
	void Set_PortNum(int iPortNum);
	int  Get_PortNum();


	//设备状态
	void Set_DevStatus(int iDevStatus);
	int  Get_DevStatus();

	//设备数据更新时间
	void Set_CreateTime(CTime tTime);
	CTime* Get_CreateTime();

	//获取端口数据列表
	CPortList* Get_PortList();
public:
	//增加端口
	int AddPort(CPort *pPort);

	//删除端口
	int DeletePort(CPort *pPort);

	//清空端口数据
	int ClearPort();

	//根据端口索引获取端口数据指针
	CPort *QueryPortByPortNo(int iPortIndex);

public:
	//设备重启
	int ReConnect();

	int Reboot();
	int SaveData();

	BOOL SayHello();

	BOOL GetDevStatic();

	BOOL SaveSysParaToDev();
	BOOL SavePortParaToDev(int iPortNo);
	BOOL SavePortWorkModeParaToDev(int iPortNo);
};


