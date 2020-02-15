/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����DataDefine.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ȫ�����ݼ���������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#include "stdafx.h"

PORT_BAUDRATE g_Port_BaudRate[] = {
   { Port_BaudRate_50     ,50     ,"50"    } ,
   { Port_BaudRate_75     ,75     ,"75"    } ,
   { Port_BaudRate_110    ,110    ,"110"   } ,
   { Port_BaudRate_134    ,134    ,"134"   } ,
   { Port_BaudRate_150    ,150    ,"150"   } ,
   { Port_BaudRate_300    ,300    ,"300"   } ,
   { Port_BaudRate_600    ,600    ,"600"   } ,
   { Port_BaudRate_1200   ,1200   ,"1200"  } ,
   { Port_BaudRate_1800   ,1800   ,"1800"  } ,
   { Port_BaudRate_2400   ,2400   ,"2400"  } ,
   { Port_BaudRate_4800   ,4800   ,"4800"  } ,
   { Port_BaudRate_7200   ,7200   ,"7200"  } ,
   { Port_BaudRate_9600   ,9600   ,"9600"  } ,
   { Port_BaudRate_19200  ,19200  ,"19200" } ,
   { Port_BaudRate_38400  ,38400  ,"38400" } ,
   { Port_BaudRate_57600  ,57600  ,"57600" } ,
   { Port_BaudRate_115200 ,115200 ,"115200"} ,
   { Port_BaudRate_230400 ,230400 ,"230400"} ,
   { Port_BaudRate_460800 ,460800 ,"460800"} ,
   { Port_BaudRate_921600 ,921600 ,"921600"}

};




PORT_PARITY   g_Port_Parity[] = {
	{ PORT_PARITY_NONE     , SERIALSERV_PARITYBIT_NONE ,"None"        } ,
	{ PORT_PARITY_ODD      , SERIALSERV_PARITYBIT_ODD  ,"Odd"         } ,
	{ PORT_PARITY_EVEN     , SERIALSERV_PARITYBIT_EVEN ,"Even"        }
};


PORT_DATABITS g_Port_DataBits[] = {
   { Port_DataBits_5      , SERIALSERV_DATABIT_CS5    ,"5"   } ,
   { Port_DataBits_6      , SERIALSERV_DATABIT_CS6    ,"6"   } ,
   { Port_DataBits_7      , SERIALSERV_DATABIT_CS7    ,"7"   } ,
   { Port_DataBits_8      , SERIALSERV_DATABIT_CS8    ,"8"   } 
};

PORT_STOPBITS g_Port_StopBits[] = {
	{ Port_StopBits_1     ,SERIALSERV_STOPBIT_1      ,"1"     } ,
	{ Port_StopBits_2     ,SERIALSERV_STOPBIT_2      ,"2"     } 
};


PORT_INTERFACE g_Port_Interface[] = {
	{ INTERFACE_RS_232      ,SERIALSERV_PORTMODE_RS232 , "RS-232"     } ,
	{ INTERFACE_RS_422      ,SERIALSERV_PORTMODE_RS422 , "RS-422"     } ,
	{ INTERFACE_RS_485      ,SERIALSERV_PORTMODE_RS485 , "RS-485"     } 
};

PORT_MODE g_Port_Mode[] = {
	{ PORT_MODE_TCP_SERVER    , SERIALSERV_OPMODE_TCPSERVER  ,"TCP Server Mode"  } ,
	{ PORT_MODE_TCP_CLIENT    , SERIALSERV_OPMODE_TCPCLIENT  ,"TCP Client Mode"  } ,
	{ PORT_MODE_UDP_SERVER	  ,	SERIALSERV_OPMODE_UDPSERVER  ,"UDP Server Mode"         } ,
	{ PORT_MODE_UDP_CLIENT	  ,	SERIALSERV_OPMODE_UDPCLIENT  ,"UDP Client Mode"         }
//	{ PORT_MODE_REAL_COM	  , SERIALSERV_OPMODE_REALCOM    ,"Real COM Mode"    } 
};


PORT_FLOWCTRL g_Port_FlowCtrl[] = {

	{ FLOW_CTRL_NONE        ,SERIALSERV_FLOWCTL_NONE , "None"    },
	{ FLOW_CTRL_DTS_DSR     ,SERIALSERV_FLOWCTL_HW   ,"DTS/DSR"  },
	{ FLOW_CTRL_RTS_CTS     ,SERIALSERV_FLOWCTL_SW   ,"RTS/CTS"  }//,
	//{ FLOW_CTRL_XON_XOFF    , ,"XON/XOFF" }
};



ART_TIME_ZONE g_Art_Time_Zone[] = {
	{ART_TIME_ZONE_UTC__12     ,  -12 , "(UTC-12:00)�������ڱ������"},
	{ART_TIME_ZONE_UTC__11     ,  -11 , "(UTC-11:00)��Ħ��Ⱥ��"},
	{ART_TIME_ZONE_UTC__10     ,  -10 , "(UTC-10:00)������"},
	{ART_TIME_ZONE_UTC__9      ,  -9  , "(UTC-09:00)����˹��"},
	{ART_TIME_ZONE_UTC__8      ,  -8  , "(UTC-08:00)���������ǵ�"},
	{ART_TIME_ZONE_UTC__7      ,  -7  , "(UTC-07:00)����ɣ�ǵ�"},
	{ART_TIME_ZONE_UTC__6      ,  -6  , "(UTC-06:00)ī���磬�����޵�"},
	{ART_TIME_ZONE_UTC__5      ,  -5  , "(UTC-05:00)ӡ�ذ��ǣ�������"},
	{ART_TIME_ZONE_UTC__4      ,  -4  , "(UTC-04:00)ʥ���Ǹ��"},
	{ART_TIME_ZONE_UTC__3      ,  -3  , "(UTC-03:00)Ŧ����������ŵ˹����˹��"},
	{ART_TIME_ZONE_UTC__2      ,  -2  , "(UTC-02:00)�д�����"},
	{ART_TIME_ZONE_UTC__1      ,  -1  , "(UTC-01:00)��ý�Ⱥ��"},
	{ART_TIME_ZONE_UTC         ,   0  , "(UTC)�׶أ������֣�������������"},
	{ART_TIME_ZONE_UTC_1       ,   1  , "(UTC+01:00)��³���������֣������"},
    {ART_TIME_ZONE_UTC_2       ,   2  , "(UTC+02:00)���޵�"},
	{ART_TIME_ZONE_UTC_3       ,   3  , "(UTC+03:00)�͸�Ī˹�ƣ�ʥ�˵ñ���������"},
	{ART_TIME_ZONE_UTC_4       ,   4  , "(UTC+04:00)�ڱ���˹��·�׸�"},
	{ART_TIME_ZONE_UTC_5       ,   5  , "(UTC+05:00)������˹������������"},
	{ART_TIME_ZONE_UTC_6       ,   6  , "(UTC+06:00)�￨"},
	{ART_TIME_ZONE_UTC_7       ,   7  , "(UTC+07:00)���ȣ����ڣ��żӴ�"},
	{ART_TIME_ZONE_UTC_8       ,   8  , "(UTC+08:00)�������Ϻ������"},
	{ART_TIME_ZONE_UTC_9       ,   9  , "(UTC+09:00)�׶�������"},
	{ART_TIME_ZONE_UTC_10      ,   10 , "(UTC+10:00)����˹�࣬�ص���ī������Ϥ��"},
	{ART_TIME_ZONE_UTC_11      ,   11 , "(UTC+11:00)��ӵ���������"},
	{ART_TIME_ZONE_UTC_12      ,   12 , "(UTC+12:00)�¿����������"},
	{ART_TIME_ZONE_UTC_13      ,   13 , "(UTC+13:00)Ŭ�Ⱒ�巨"}

};

/*******************************************************
PORT_Get_BaudRate_Text
********************************************************/
char * PORT_Get_BaudRate_Text(int iBaudRate)
{
	return g_Port_BaudRate[iBaudRate].szBaudRate ;
}

/*******************************************************
PORT_Get_BaudRate_By_Dev
********************************************************/
int PORT_Get_BaudRate_By_Dev(int iDev_BaudRate)
{

	for (int i = 0 ; i < Port_BaudRate_Max ; i++)
	{
		PORT_BAUDRATE * pstPort_Baudrate = NULL;
		pstPort_Baudrate = &g_Port_BaudRate[i] ;

		if (pstPort_Baudrate->iBaudRate == iDev_BaudRate )
		{
			return pstPort_Baudrate->iIndex ;
		}
   }
   
   return 0;
}


/*******************************************************
PORT_Get_BaudRate_By_SYS
********************************************************/
int PORT_Get_BaudRate_By_SYS(int iSYS_BaudRate)
{
	return g_Port_BaudRate[iSYS_BaudRate].iBaudRate ;
}


/*******************************************************
PORT_Get_Parity_Text
********************************************************/
char * PORT_Get_Parity_Text(int iParity)
{
	return g_Port_Parity[iParity].szPortParity ;
}

/*******************************************************
PORT_Get_Parity_By_Dev
********************************************************/
int PORT_Get_Parity_By_Dev(int iDev_Parity)
{

	for (int i = 0 ; i < PORT_PARITY_MAX ; i++)
	{
		PORT_PARITY * pstPort_Parity = NULL;
		pstPort_Parity = &g_Port_Parity[i]  ;

		if (pstPort_Parity->iDevParity == iDev_Parity )
		{
			return pstPort_Parity->iIndex ;
		}
   }

	return 1 ;
}


/*******************************************************
PORT_Get_Parity_By_SYS
********************************************************/
int PORT_Get_Parity_By_SYS(int iSYS_Parity)
{
	return g_Port_Parity[iSYS_Parity].iDevParity ;
}


/*******************************************************
PORT_Get_DataBits_Text
********************************************************/
char * PORT_Get_DataBits_Text(int iDataBits)
{
	return g_Port_DataBits[iDataBits].szDataBits ;
}

/*******************************************************
PORT_Get_DataBits_By_Dev
********************************************************/
int PORT_Get_DataBits_By_Dev(int iDev_DataBits)
{
	for (int i = 0 ; i < Port_DataBits_Max ; i++)
	{
		PORT_DATABITS * pstPort_DataBits = NULL;
		pstPort_DataBits = &g_Port_DataBits[i]  ;

		if (pstPort_DataBits->iDevDataBits == iDev_DataBits )
		{
			return pstPort_DataBits->iIndex ;
		}
    }
    
	return 0; 	
}

/*******************************************************
PORT_Get_DataBits_By_SYS
********************************************************/
int PORT_Get_DataBits_By_SYS(int iSYS_DataBits)
{
	return g_Port_DataBits[iSYS_DataBits].iDevDataBits ;
}

/*******************************************************
PORT_Get_StopBits_Text
********************************************************/
char * PORT_Get_StopBits_Text(int iStopBits)
{
	return g_Port_StopBits[iStopBits].szStopBits ;
}

/*******************************************************
PORT_Get_StopBits_By_Dev
********************************************************/
int PORT_Get_StopBits_By_Dev(int iDev_StopBits)
{
	for (int i = 0 ; i < Port_StopBits_Max ; i++)
	{
		PORT_STOPBITS * pstPort_StopBits = &g_Port_StopBits[i];

		if (pstPort_StopBits->iDevStopBits == iDev_StopBits )
		{
			return pstPort_StopBits->iIndex ;
		}
    }
    
	return 0; 	
}

/*******************************************************
PORT_Get_StopBits_By_Dev
********************************************************/
int PORT_Get_FlowCtrl_By_Dev(int iDevPort_FlowCtrl)
{
	for (int i = 0 ; i < FLOW_CTRL_MAX ; i++)
	{
		PORT_FLOWCTRL * pstPort_FlowCtrl = &g_Port_FlowCtrl[i];

		if (pstPort_FlowCtrl->iDevPortFlowCtrl == iDevPort_FlowCtrl )
		{
			return pstPort_FlowCtrl->iIndex ;
		}
    }
    
	return 0; 	
}

/*******************************************************
PORT_Get_StopBits_By_SYS
********************************************************/
int PORT_Get_StopBits_By_SYS(int iSYS_StopBits)
{
	return g_Port_StopBits[iSYS_StopBits].iDevStopBits ;
}

/*******************************************************
PORT_Get_StopBits_By_SYS
********************************************************/
int PORT_Get_FlowCtrl_By_SYS(int iSYS_FlowCtrl)
{
	return g_Port_FlowCtrl[iSYS_FlowCtrl].iDevPortFlowCtrl ;
}


/*******************************************************
PORT_Get_Interface_Text
********************************************************/
char * PORT_Get_Interface_Text(int iInterface)
{
	return g_Port_Interface[iInterface].szInterface ;
}

/*******************************************************
PORT_Get_Interface_By_Dev
********************************************************/
int PORT_Get_Interface_By_Dev(int iDev_Interface)
{
	for (int i = 0 ; i < INTERFACE_MAX ; i++)
	{
		PORT_INTERFACE * pstPort_Interface = &g_Port_Interface[i];

		if (pstPort_Interface->iDevInterface == iDev_Interface )
		{
			return pstPort_Interface->iIndex ;
		}
    }
    
	return 0; 	

}


/*******************************************************
PORT_Get_Interface_By_SYS
********************************************************/
int PORT_Get_Interface_By_SYS(int iSYS_Interface)
{
	return g_Port_Interface[iSYS_Interface].iDevInterface ;
}

/*******************************************************
PORT_Get_PortMode_Text
********************************************************/
char * PORT_Get_PortMode_Text(int iMode)
{
	return g_Port_Mode[iMode].szPortMode ;
}

/*******************************************************
PORT_Get_PortMode_By_Dev
********************************************************/
int PORT_Get_PortMode_By_Dev(int iDev_PortWorkMode)
{
	for (int i = 0 ; i < INTERFACE_MAX ; i++)
	{
		PORT_MODE * pstPort_Mode = &g_Port_Mode[i];

		if (pstPort_Mode->iDevPortWorkMode == iDev_PortWorkMode )
		{
			return pstPort_Mode->iIndex ;
		}
    }
    
	return 0; 	
}


/*******************************************************
PORT_Get_PortMode_By_SYS
********************************************************/
int PORT_Get_PortWorkMode_By_SYS(int iSYS_Mode)
{
	return g_Port_Mode[iSYS_Mode].iDevPortWorkMode ;
}


char * PORT_Get_FlowCtrl_Text(int iFlowCtrl)
{
	return g_Port_FlowCtrl[iFlowCtrl].szFlowCtrl ;
}

/******************************************************************************************************
�豸���˿ڲ���ȱʡֵ
*******************************************************************************************************/
int g_Port_BaudRate_Default    = Port_BaudRate_9600;
int g_Port_Parity_Default      = PORT_PARITY_NONE;
int g_Port_DataBits_Default    = Port_DataBits_5;
int g_Port_StopBits_Default    = Port_StopBits_1;
int g_Port_Interface_Default   = INTERFACE_RS_232 ;
int g_Port_Mode_Default        = PORT_MODE_TCP_SERVER;
int g_Port_FlowCtrl_Default    = FLOW_CTRL_NONE;
int g_TCPServer_MaxConnection_Default  = 6 ;


int g_UCPMode_ListenPort_Default       = 6000 ;
int g_DevManagermentPort               = SERIALSERV_COM_CFGPORT ;
int g_Art_Time_Zone_Default            = ART_TIME_ZONE_UTC_8;