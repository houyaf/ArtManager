/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：Port.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 端口类CPort声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once

// CPort 命令目标
class CPortChannel;
class CChannelStatistics;
class CPort : public CObject
{
public:
	CPort();
	~CPort();

protected:
	int m_iPortIndex      ;
	int m_iPortSwitch     ;

	CString m_szPortName ;

	int m_iBaudRate       ;
	int m_iParity         ;
	int m_iDataBits       ;

	int m_iStopBits       ;
	int m_iFlowCtrl       ;
	int m_iInterface      ;

	int m_iPortStatus     ;

protected: 
    int m_iChannelNum     ;

	//端口数据list
	CChannelList m_ChannelList ;

	 //SERIALSERV_CFG_OPMODE1,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP1,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT1,            /* COM PORT, USHORT类型, 长度:2 */ 
	 //SERIALSERV_CFG_CONNECTNUM1,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:4 */
	 //SERIALSERV_CFG_CHANNELSWITCH1,      /* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE1;
	 unsigned long  m_ulCOMIP1;
	 unsigned short m_usCOMPORT1;
	 unsigned long  m_ulCONNECTNUM1;
	 unsigned char  m_ucCHANNELSWITCH1;

	 //SERIALSERV_CFG_OPMODE2,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP2,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT2,            /* COM PORT, USHORT类型, 长度:2 */ 
	 //SERIALSERV_CFG_CONNECTNUM2,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
	 //SERIALSERV_CFG_CHANNELSWITCH2,		/* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE2;
	 unsigned long  m_ulCOMIP2;
	 unsigned short m_usCOMPORT2;
	 unsigned long  m_ulCONNECTNUM2;
	 unsigned char  m_ucCHANNELSWITCH2;

	 //SERIALSERV_CFG_OPMODE3,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP3,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT3,            /* COM PORT, USHORT类型, 长度:2 */ 
	 //SERIALSERV_CFG_CONNECTNUM3,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
	 //SERIALSERV_CFG_CHANNELSWITCH3,		/* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE3;
	 unsigned long  m_ulCOMIP3;
	 unsigned short m_usCOMPORT3;
	 unsigned long  m_ulCONNECTNUM3;
	 unsigned char  m_ucCHANNELSWITCH3;

	 //SERIALSERV_CFG_OPMODE4,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP4,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT4,            /* COM PORT, USHORT类型, 长度:2 */ 
	 //SERIALSERV_CFG_CONNECTNUM4,           /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
	 //SERIALSERV_CFG_CHANNELSWITCH4,		/* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE4;
	 unsigned long  m_ulCOMIP4;
	 unsigned short m_usCOMPORT4;
	 unsigned long  m_ulCONNECTNUM4;
	 unsigned char  m_ucCHANNELSWITCH4;

	 //SERIALSERV_CFG_OPMODE5,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP5,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT5,            /* COM PORT, USHORT类型, 长度:2 */ 
	 //SERIALSERV_CFG_CONNECTNUM5,            /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
	 //SERIALSERV_CFG_CHANNELSWITCH5,		/* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE5;
	 unsigned long  m_ulCOMIP5;
	 unsigned short m_usCOMPORT5;
	 unsigned long  m_ulCONNECTNUM5;
	 unsigned char  m_ucCHANNELSWITCH5;

	 //SERIALSERV_CFG_OPMODE6,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
	 //SERIALSERV_CFG_COMIP6,              /* COM IP, ULONG类型, 长度:4 */ 
	 //SERIALSERV_CFG_COMPORT6,            /* COM PORT, USHORT类型, 长度:2 */  
	 //SERIALSERV_CFG_CONNECTNUM6,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */
	 //SERIALSERV_CFG_CHANNELSWITCH6,		/* CHANNEL 开关 SERIALSERVCHANNELSWITCH_ENUM, 长度:1 */
	 unsigned char  m_ucOPMODE6;
	 unsigned long  m_ulCOMIP6;
	 unsigned short m_usCOMPORT6;
	 unsigned long  m_ulCONNECTNUM6;
	 unsigned char  m_ucCHANNELSWITCH6;

public:
	
	//获取端口数据列表
	CChannelList* Get_ChannelList();

	int Get_ChannelNum();
	void Set_ChannelNum(int iChannelNum);

	unsigned char  Get_OPMODE1(){ return m_ucOPMODE1   ; };
	unsigned long  Get_COMIP1() { return m_ulCOMIP1    ; };
	unsigned short Get_COMPORT1(){ return m_usCOMPORT1 ; };
	unsigned long  Get_CONNECTNUM1(){return m_ulCONNECTNUM1; };
	unsigned char  Get_CHANNELSWITCH1(){return m_ucCHANNELSWITCH1 ; };

	void  Set_OPMODE1(unsigned char ucMode)  { m_ucOPMODE1= ucMode ;};
	void  Set_COMIP1(unsigned long ulIP)     { m_ulCOMIP1 = ulIP;};
	void  Set_COMPORT1(unsigned short usPort){ m_usCOMPORT1 = usPort ;};
	void  Set_CONNECTNUM1(unsigned long ulConnNum){ m_ulCONNECTNUM1 = ulConnNum ;};
	void  Set_CHANNELSWITCH1(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH1 =ucChannelSwitch; };


	unsigned char  Get_OPMODE2(){ return m_ucOPMODE2   ; };
	unsigned long  Get_COMIP2() { return m_ulCOMIP2    ; };
	unsigned short Get_COMPORT2(){ return m_usCOMPORT2 ; };
	unsigned long  Get_CONNECTNUM2(){return m_ulCONNECTNUM2; };
	unsigned char  Get_CHANNELSWITCH2(){return m_ucCHANNELSWITCH2 ; };

	void  Set_OPMODE2(unsigned char ucMode)  { m_ucOPMODE2= ucMode ;};
	void  Set_COMIP2(unsigned long ulIP)     { m_ulCOMIP2 = ulIP;};
	void  Set_COMPORT2(unsigned short usPort){ m_usCOMPORT2 = usPort ;};
	void  Set_CONNECTNUM2(unsigned long ulConnNum){ m_ulCONNECTNUM2 = ulConnNum ;};
	void  Set_CHANNELSWITCH2(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH2 =ucChannelSwitch; };

	unsigned char  Get_OPMODE3(){ return m_ucOPMODE3   ; };
	unsigned long  Get_COMIP3() { return m_ulCOMIP3    ; };
	unsigned short Get_COMPORT3(){ return m_usCOMPORT3 ; };
	unsigned long  Get_CONNECTNUM3(){return m_ulCONNECTNUM3; };
	unsigned char  Get_CHANNELSWITCH3(){return m_ucCHANNELSWITCH3 ; };

	void  Set_OPMODE3(unsigned char ucMode)  { m_ucOPMODE3= ucMode ;};
	void  Set_COMIP3(unsigned long ulIP)     { m_ulCOMIP3 = ulIP;};
	void  Set_COMPORT3(unsigned short usPort){ m_usCOMPORT3 = usPort ;};
	void  Set_CONNECTNUM3(unsigned long ulConnNum){ m_ulCONNECTNUM3 = ulConnNum ;};
	void  Set_CHANNELSWITCH3(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH3 =ucChannelSwitch; };

	unsigned char  Get_OPMODE4(){ return m_ucOPMODE4   ; };
	unsigned long  Get_COMIP4() { return m_ulCOMIP4    ; };
	unsigned short Get_COMPORT4(){ return m_usCOMPORT4 ; };
	unsigned long  Get_CONNECTNUM4(){return m_ulCONNECTNUM4; };
	unsigned char  Get_CHANNELSWITCH4(){return m_ucCHANNELSWITCH4 ; };

	void  Set_OPMODE4(unsigned char ucMode)  { m_ucOPMODE4= ucMode ;};
	void  Set_COMIP4(unsigned long ulIP)     { m_ulCOMIP4 = ulIP;};
	void  Set_COMPORT4(unsigned short usPort){ m_usCOMPORT4 = usPort ;};
	void  Set_CONNECTNUM4(unsigned long ulConnNum){ m_ulCONNECTNUM4 = ulConnNum ;};
	void  Set_CHANNELSWITCH4(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH4 =ucChannelSwitch; };

	unsigned char  Get_OPMODE5(){ return m_ucOPMODE5   ; };
	unsigned long  Get_COMIP5() { return m_ulCOMIP5    ; };
	unsigned short Get_COMPORT5(){ return m_usCOMPORT5 ; };
	unsigned long  Get_CONNECTNUM5(){return m_ulCONNECTNUM5; };
	unsigned char  Get_CHANNELSWITCH5(){return m_ucCHANNELSWITCH5 ; };

	void  Set_OPMODE5(unsigned char ucMode)  { m_ucOPMODE5= ucMode ;};
	void  Set_COMIP5(unsigned long ulIP)     { m_ulCOMIP5 = ulIP;};
	void  Set_COMPORT5(unsigned short usPort){ m_usCOMPORT5 = usPort ;};
	void  Set_CONNECTNUM5(unsigned long ulConnNum){ m_ulCONNECTNUM5 = ulConnNum ;};
	void  Set_CHANNELSWITCH5(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH5 =ucChannelSwitch; };

	unsigned char  Get_OPMODE6(){ return m_ucOPMODE6   ; };
	unsigned long  Get_COMIP6() { return m_ulCOMIP6    ; };
	unsigned short Get_COMPORT6(){ return m_usCOMPORT6 ; };
	unsigned long  Get_CONNECTNUM6(){return m_ulCONNECTNUM6; };
	unsigned char  Get_CHANNELSWITCH6(){return m_ucCHANNELSWITCH6 ; };

	void  Set_OPMODE6(unsigned char ucMode)  { m_ucOPMODE6= ucMode ;};
	void  Set_COMIP6(unsigned long ulIP)     { m_ulCOMIP6 = ulIP;};
	void  Set_COMPORT6(unsigned short usPort){ m_usCOMPORT6 = usPort ;};
	void  Set_CONNECTNUM6(unsigned long ulConnNum){ m_ulCONNECTNUM6 = ulConnNum ;};
	void  Set_CHANNELSWITCH6(unsigned char ucChannelSwitch){ m_ucCHANNELSWITCH6 =ucChannelSwitch; };

public:
	//增加端口
	int AddChannel(CPortChannel *pChannel);

	//删除端口
	int DeleteChannel(CPortChannel *pChannel);

	//清空端口数据
	int ClearChannels();

	//根据端口索引获取端口数据指针
	CPortChannel *QueryChannelByNo(int iChannelIndex);

public:
	CChannelStatistics *m_pChannelStatic1;
	CChannelStatistics *m_pChannelStatic2;
	CChannelStatistics *m_pChannelStatic3;
	CChannelStatistics *m_pChannelStatic4;
	CChannelStatistics *m_pChannelStatic5;
	CChannelStatistics *m_pChannelStatic6;


public:

	//端口号
	void Set_Index(int iPortIndex);
	int  Get_Index();

	
	//端口开关
	void    Set_PortSwitch(int iSwitch);
	int     Get_PortSwitch();


	//端口名称
	void    Set_PortName(LPCTSTR szPortName);
	CString Get_PortName();

	//波特率
	void Set_BaudRate(int iBaudRate);
	int  Get_BaudRate();

	//奇偶校验位
	void    Set_Parity(int iParaty);
	int Get_Parity();

	//数据位
	void Set_DataBits(int iDataBits);
	int  Get_DataBits();

	//停止位
	void Set_StopBits(int iStopBits);
	int  Get_StopBits();

	//流控
	void Set_FlowCtrl(int iFlowCtrl);
	int  Get_FlowCtrl();

	//接口模式:RS232/RS485/RS422
	void Set_Interface(int iInterface);
	int  Get_Interface();

	//接口工作模式:TCP Server/TCP Client/RealCOM/UDP
	void Set_PortMode(int iPortMode);
	int  Get_PortMode();

	//接口工作模式数据:TCP Server/TCP Client/RealCOM/UDP
	void Set_PortModeData(CPortChannel * pPortMode);
	CPortChannel * Get_PortModeData();

	//端口状态
	void Set_PortStatus(int iPortStatus);
	int  Get_PortStatus();

public:

};


