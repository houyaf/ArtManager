/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：DataDefine.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 全局数据及函數定义
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

//**********************************************************************************************/
//波特率//
//**********************************************************************************************/
typedef struct stPort_Baudrate
{
	int   iIndex         ;
	int   iBaudRate      ;
	char  szBaudRate[16] ;
} PORT_BAUDRATE;


 enum Port_Baudrate
{
	Port_BaudRate_50     , 
    Port_BaudRate_75     , 
    Port_BaudRate_110    , 
    Port_BaudRate_134    , 
    Port_BaudRate_150    , 
    Port_BaudRate_300    , 
    Port_BaudRate_600    , 
    Port_BaudRate_1200   , 
    Port_BaudRate_1800   , 
    Port_BaudRate_2400   , 
    Port_BaudRate_4800   , 
    Port_BaudRate_7200   , 
    Port_BaudRate_9600   , 
    Port_BaudRate_19200  , 
    Port_BaudRate_38400  , 
    Port_BaudRate_57600  , 
    Port_BaudRate_115200 , 
    Port_BaudRate_230400 , 
    Port_BaudRate_460800 , 
    Port_BaudRate_921600 ,

	Port_BaudRate_Max
};



//**********************************************************************************************/
//奇偶校驗位//
//**********************************************************************************************/
typedef struct stPort_Parity
{
	int   iIndex      ;
	int   iDevParity  ;
	char  szPortParity[16] ;
}PORT_PARITY;


enum Port_Parity
{
	PORT_PARITY_NONE = 0,
	PORT_PARITY_ODD ,
	PORT_PARITY_EVEN,

	PORT_PARITY_MAX
};

//**********************************************************************************************/
//数据位
//**********************************************************************************************/
typedef struct stPort_DataBits
{
	int   iIndex         ;
	int   iDevDataBits      ;
	char  szDataBits[16] ;
} PORT_DATABITS;


 enum Port_DataBits
{
	Port_DataBits_5     , 
    Port_DataBits_6     , 
    Port_DataBits_7     , 
    Port_DataBits_8     , 
   
	Port_DataBits_Max
};


//**********************************************************************************************/
//停止位//
//**********************************************************************************************/
typedef struct stPort_StopBits
{
	int    iIndex         ;
	int    iDevStopBits      ;
	char   szStopBits[16] ;
} PORT_STOPBITS;


 enum Port_StopBits
{
	Port_StopBits_1     , 
    Port_StopBits_2     , 
   
	Port_StopBits_Max
};


//********************************************************************************************/
//端口接口模式//
/**********************************************************************************************/
typedef struct stPort_Interface
{
	int   iIndex       ;
	int   iDevInterface;
	char  szInterface[16] ;
}PORT_INTERFACE;

enum Port_Interface
{
	INTERFACE_RS_232 = 0,
	INTERFACE_RS_422,
	INTERFACE_RS_485,
	
	INTERFACE_MAX
};

/*********************************************************************************************/
//端口工作模式//
/**********************************************************************************************/
typedef struct stPort_Mode
{
	int   iIndex      ;
	int   iDevPortWorkMode;
	char  szPortMode[16] ;
}PORT_MODE;


enum Port_Mode
{
	PORT_MODE_TCP_SERVER = 0,
	PORT_MODE_TCP_CLIENT,
	PORT_MODE_UDP_SERVER,
	PORT_MODE_UDP_CLIENT,
	//PORT_MODE_REAL_COM,

	PORT_MODE_MAX
};

/*********************************************************************************************/
//端口流控
/**********************************************************************************************/

typedef struct stPort_FlowCtrl
{
	int   iIndex      ;
	int   iDevPortFlowCtrl;
	char  szFlowCtrl[16] ;
}PORT_FLOWCTRL;

enum Port_FlowCtrl
{
	FLOW_CTRL_NONE = 0 ,  //"None"
	FLOW_CTRL_DTS_DSR  ,  //"DTS/DSR"
	FLOW_CTRL_RTS_CTS  ,  //"RTS/CTS"
	//FLOW_CTRL_XON_XOFF ,  //"XON/XOFF"

	FLOW_CTRL_MAX
};


/********************************************************************************************/
//TCP Server 最大連接數//
/**********************************************************************************************/
typedef struct stTCP_Server_MaxConnection
{
	int   iIndex      ;
	int   iMaxConnection      ;
	char  szMaxConnection[16] ;
}TCPSERVER_MAXCONNECTION;



/**********************************************************************************************/
//时区//
/**********************************************************************************************/
typedef struct stART_Time_Zone
{
	int   iIndex         ;
	int   iTimeZone      ;
	char  szTimeZone[64] ;
} ART_TIME_ZONE;


enum ENUM_ART_TIME_ZONE
{
	ART_TIME_ZONE_UTC__12     , 
	ART_TIME_ZONE_UTC__11     , 
	ART_TIME_ZONE_UTC__10     , 
	ART_TIME_ZONE_UTC__9      , 
	ART_TIME_ZONE_UTC__8      , 
	ART_TIME_ZONE_UTC__7      , 
	ART_TIME_ZONE_UTC__6      , 
	ART_TIME_ZONE_UTC__5      , 
	ART_TIME_ZONE_UTC__4      , 
	ART_TIME_ZONE_UTC__3      , 
	ART_TIME_ZONE_UTC__2      , 
	ART_TIME_ZONE_UTC__1      , 
	ART_TIME_ZONE_UTC         , 
	ART_TIME_ZONE_UTC_1       , 
    ART_TIME_ZONE_UTC_2       , 
	ART_TIME_ZONE_UTC_3       , 
	ART_TIME_ZONE_UTC_4       , 
	ART_TIME_ZONE_UTC_5       , 
	ART_TIME_ZONE_UTC_6       , 
	ART_TIME_ZONE_UTC_7       , 
	ART_TIME_ZONE_UTC_8       , 
	ART_TIME_ZONE_UTC_9       , 
	ART_TIME_ZONE_UTC_10      , 
	ART_TIME_ZONE_UTC_11      , 
	ART_TIME_ZONE_UTC_12      , 
	ART_TIME_ZONE_UTC_13      , 
	ART_TIME_ZONE_MAX

};

/*************************************************************************************************************/
//全局变量
/*************************************************************************************************************/


 extern    PORT_BAUDRATE   g_Port_BaudRate[] ; 
 extern    PORT_PARITY     g_Port_Parity[]   ;  
 extern    PORT_DATABITS   g_Port_DataBits[] ; 
 extern    PORT_STOPBITS   g_Port_StopBits[] ;
 extern    PORT_INTERFACE  g_Port_Interface[];
 extern    PORT_MODE       g_Port_Mode[]     ;        
 extern    PORT_FLOWCTRL   g_Port_FlowCtrl[] ;
 extern    TCPSERVER_MAXCONNECTION g_TCPServer_MaxConnection[];
 extern    ART_TIME_ZONE g_Art_Time_Zone[];

 extern    int   g_Port_BaudRate_Default           ; 
 extern    int   g_Port_Parity_Default             ;  
 extern    int   g_Port_DataBits_Default           ; 
 extern    int   g_Port_StopBits_Default           ;
 extern    int   g_Port_Interface_Default          ;
 extern    int   g_Port_Mode_Default               ;        
 extern    int   g_Port_FlowCtrl_Default           ;
 extern    int   g_TCPServer_MaxConnection_Default ;
 extern    int   g_TCPServerMode_ListenPort_Default;
 extern    int   g_UCPMode_ListenPort_Default      ;
 extern    int   g_Art_Time_Zone_Default           ;
 extern    int   g_DevManagermentPort              ;

 extern  char * PORT_Get_BaudRate_Text(int iBaudRate)   ;
 extern  char * PORT_Get_Parity_Text(int iParity)       ;
 extern  char * PORT_Get_DataBits_Text(int iDataBits)   ;
 extern  char * PORT_Get_StopBits_Text(int iStopBits)   ;
 extern  char * PORT_Get_Interface_Text(int iInterface) ;
 extern  char * PORT_Get_PortMode_Text(int iMode)       ;
 extern  char * PORT_Get_FlowCtrl_Text(int iFlowCtrl)   ; 
 extern  char * PORT_Get_TCPServer_MaxConn_Text(int iTCPConn);

 extern  int PORT_Get_BaudRate_By_Dev(int iDev_BaudRate);
 extern  int PORT_Get_Parity_By_Dev(int iDev_Parity);
 extern  int PORT_Get_DataBits_By_Dev(int iDev_DataBits);
 extern  int PORT_Get_StopBits_By_Dev(int iDev_StopBits);
 extern  int PORT_Get_FlowCtrl_By_Dev(int iDevPort_FlowCtrl);
 extern  int PORT_Get_Interface_By_Dev(int iDev_Interface);
 extern  int PORT_Get_PortMode_By_Dev(int iDev_PortWorkMode);

 extern  int PORT_Get_BaudRate_By_SYS(int iSYS_BaudRate);
 extern  int PORT_Get_Parity_By_SYS(int iSYS_Parity);
 extern  int PORT_Get_DataBits_By_SYS(int iSYS_DataBits);
 extern  int PORT_Get_StopBits_By_SYS(int iSYS_StopBits);
 extern  int PORT_Get_FlowCtrl_By_SYS(int iSYS_FlowCtrl);
 extern  int PORT_Get_Interface_By_SYS(int iSYS_Interface);
 extern  int PORT_Get_PortWorkMode_By_SYS(int iSYS_Mode);