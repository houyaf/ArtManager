#include "stdafx.h"
#include "COMP.h"

/*****************************************************************************
 函 数 名  : COMP_CreateGetMsg
 功能描述  : 生成Get消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 返回消息数据包中目前数据长度
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
ULONG COMP_CreateGetMsg(ULONG ulComNo, VOID *pEncodeMsg)
{
	ULONG ulOp_Code;
	INT   iSize;
	UCHAR ucOp_Type;
	ULONG ulOp_Obj;

	ULONG ulRet = 0;

	if (pEncodeMsg == NULL)
	{
		return 1;
	}

	//写入: SERIALSERV_OPERATION_OID
	ulOp_Code = GetTickCount();
	iSize     = 4;
	ulOp_Code = htonl(ulOp_Code);
	ulRet += Dmdcp_SetOid(pEncodeMsg,  SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);
	
	//写入: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_GET;
	iSize     = 1;
	ulRet += Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, iSize, (VOID *)&ucOp_Type);
	

	//写入SERIALSERV_OPERATION_OBJECT
	ulOp_Obj  = ulComNo;
	iSize     = 4;
	ulOp_Obj  = htonl(ulOp_Obj);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);


	return 0;

	
}

/*****************************************************************************
 函 数 名  : CreateGetMsgOfDeviceInfo
 功能描述  : 生成设备信息Get消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID * COMP_CreateGetMsgOfDevice()
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    // /* 系统配置参数 begin */
	//SERIALSERV_SYSPARA_DEVPORTNUM   端口数目
    //SERIALSERV_SYSPARA_DATATIME,       /* 系统时间:1970以来的秒数, ULONG类型, 长度:4 */
    //SERIALSERV_SYSPARA_SYSNAME,        /* sysname,最大长度为 SYS_SYSNAMElEN_MAX - 1 */
    //SERIALSERV_SYSPARA_IP,             /* IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK,         /* IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY,        /* IP GateWay, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_MAC,            /* MAC 长度:32*/ 
    //SERIALSERV_SYSPARA_SWVERSION,      /* SW version, 长度:4 */
    //SERIALSERV_SYSPARA_UPTIME,         /* 系统启动时间:1970以来的毫秒, ULONG类型, 长度:4 */
    //SERIALSERV_SYSPARA_DEVICEMODEL,    /* 设备类型,具体参见枚举 SERIALSERVSYSPARADEVICEMODEL_ENUM, 长度:4 */
    /* 系统配置参数 end */

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DEVPORTNUM   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DATATIME     , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_SYSNAME      , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_MAC          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_SWVERSION    , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_UPTIME       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DEVICEMODEL  , 0 , NULL);
	
	//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_1  , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_1       , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_1   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_1  , 0 , NULL);

    //SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan2 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_2,           /*57 Lan2 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_2,       /*58 Lan2 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan2 IP GateWay, ULONG类型, 长度:4 */   
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_2  , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_2       , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_2   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_2  , 0 , NULL);

	/* dmdc协议报文编码结束 */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 函 数 名  : COMP_CreateGetMsgOfDeviceNetwork
 功能描述  : 生成设备网络配置ip mask
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID * COMP_CreateGetMsgOfDeviceNetwork1()
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

	//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG类型, 长度:4 */ 
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_1  , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_1       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_1   , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_1  , 0 , NULL);

   
	/* dmdc协议报文编码结束 */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 函 数 名  : COMP_CreateGetMsgOfDeviceNetwork
 功能描述  : 生成设备网络配置ip mask
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID * COMP_CreateGetMsgOfDeviceNetwork2()
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    //SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan2 net mode, 具体参见枚举 SERIALSERVSYSPARANETMODE_ENUM, 长度:1 */ 
    //SERIALSERV_SYSPARA_IP_2,           /*57 Lan2 IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_2,       /*58 Lan2 IP Subnet Mask, ULONG类型, 长度:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan2 IP GateWay, ULONG类型, 长度:4 */   
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_2  , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_2       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_2   , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_2  , 0 , NULL);

	/* dmdc协议报文编码结束 */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 函 数 名  : CreateGetMsgOfDeviceInfo
 功能描述  : 生成设备信息Get消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID* COMP_CreateGetMsgOfPort(ULONG ulCOMNo)
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(ulCOMNo , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    
    /* 下面是一些串口配置数据 */
    //SERIALSERV_CFG_SWITCH,             /* 开关具体见枚举 SERIALSERVCFGSWTICH_ENUM, 长度:1 */
    //SERIALSERV_CFG_COMNAME,            /* com名称, 长度:SERIALSERV_NAMELEN_MAX - 1， 15 */
    
    //SERIALSERV_CFG_PORTMODE,           /* 串口类型具体见枚举 SERIALSERVCFGPORTMODE_ENUM, 长度:1 */
    //SERIALSERV_CFG_BAUDRATE,           /* 串口波特率, ULONG类型, 长度:4 */
    //SERIALSERV_CFG_WORKMODE,           /* 串口工作模式具体见枚举 SERIALSERVCFGWORKMODE_ENUM, 长度:1 */

    //SERIALSERV_CFG_OPMODE,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
    //SERIALSERV_CFG_COMIP,              /* COM IP, ULONG类型, 长度:4 */ 
    //SERIALSERV_CFG_COMPORT,            /* COM PORT, USHORT类型, 长度:2 */ 
    /* 上面是一些配置数据 */


	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_SWITCH            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMNAME           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_PORTMODE          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_BAUDRATE          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_WORKMODE          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE            , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_PARITYBIT         , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_DATABIT           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_STOPBIT           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_FLOWCTL           , 0 , NULL);
	///////////////////////////////////////////////////////////////////////////////////////////

	//SERIALSERV_CFG_CHANNELNUM
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELNUM           , 0 , NULL);
	//SERIALSERV_CFG_OPMODE1,             /* 操作类型具体见枚举 SERIALSERVCFGOPMODE_ENUM, 长度:1 */
    //SERIALSERV_CFG_COMIP1,              /* COM IP, ULONG类型, 长度:4      */ 
    //SERIALSERV_CFG_COMPORT1,            /* COM PORT, USHORT类型, 长度:2   */ 
    //SERIALSERV_CFG_CONNECTNUM1,         /* CHANNEL CONNECT NUM, ULONG类型, 长度:5 */

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE1           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP1            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT1          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM1       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH1    , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE2           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP2            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT2          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM2       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH2    , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE3           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP3            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT3          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM3       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH3    , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE4           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP4            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT4          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM4       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH4    , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE5           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP5            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT5          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM5       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH5    , 0 , NULL);

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_OPMODE6           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMIP6            , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_COMPORT6          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CONNECTNUM6       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_CFG_CHANNELSWITCH6    , 0 , NULL);
	//pstOption = VOS_SetTlv(pstOption, SERIALSERV_CFG_COMIP           , 0 , NULL);
   
	return  (VOID *)pEncodeMsg;
}

/*****************************************************************************
 函 数 名  : COMP_CreateSetMsg
 功能描述  : 生成Set消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID *COMP_CreateSetMsgofDevice()
{
	
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	ULONG ulOp_Code;
	INT   iSize;
	UCHAR ucOp_Type;
	ULONG ulOp_Obj;

	//写入: SERIALSERV_OPERATION_OID
	ulOp_Code= GetTickCount();
	iSize    = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);

	//写入: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_SET;
	iSize     = 1;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, iSize, (VOID *)&ucOp_Type);

	//写入SERIALSERV_OPERATION_OBJECT,　　设备暂时写为1
	//pstOption->ulType  = SERIALSERV_OPERATION_OBJECT;
	ulOp_Obj  = htonl(1);
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);

	
	/* dmdc协议报文编码结束 */
    //Dmdcp_EncodeEnd(pEncodeMsg);

	pstDmdcInfo = (DMDCPINFO_STRU*)pEncodeMsg;

	//pSendMsg    = (VOID*)((ULONG)pstDmdcInfo->pMsg - sizeof(DMDCPHEAD_STRU));
	
	//free(pEncodeMsg);

	return  (VOID *)pstDmdcInfo;
}



/*****************************************************************************
 函 数 名  : COMP_CreateSetMsgofPort
 功能描述  : 生成Set消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID *COMP_CreateSetMsgofPort(ULONG ulComNo)
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	ULONG ulOp_Code;
	INT   iSize;
	UCHAR ucOp_Type;
	ULONG ulOp_Obj;

	//写入: SERIALSERV_OPERATION_OID
	ulOp_Code= GetTickCount();
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);

	//写入: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_SET;
	iSize     =  1;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, 1, (VOID *)&ucOp_Type);

	//写入SERIALSERV_OPERATION_OBJECT,　端口号
	ulOp_Obj  = htonl(ulComNo);
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);
	
	
	return  (VOID *)pEncodeMsg;
}


/*****************************************************************************
 函 数 名  : COMP_GetSubOption
 功能描述  : 获取响应消息报文中的数据
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
ULONG COMP_GetSubOption(VOID *pMsgPkg, ULONG ulType, VOID *pValue)
{
	VOID* pDecodeMsg = NULL_PTR;
	ULONG ulRet;

	pDecodeMsg = Dmdcp_DecodeStart( 0, pMsgPkg);
    if ( NULL_PTR == pDecodeMsg)
    {
        return VOS_ERR;
    }

	if (pMsgPkg == NULL)
	{
		return 0;
	}

	//VOS_GetTlvValuebyType((TLVDATA_STRU* )pMsgPkg, ulType, (UCHAR *)pValue);
	ulRet = Dmdcp_GetOidValuebyType( pDecodeMsg, ulType, pValue );    
    
	Dmdcp_DecodeEnd(pDecodeMsg);
	return ulRet ;
}

//配置Set消息报文中的单个参数信息
ULONG COMP_SetSubOption(VOID *pMsgPkg, ULONG ulType, ULONG ulLen, VOID *pValue)
{
	return Dmdcp_SetOid((TLVDATA_STRU*)pMsgPkg, ulType, ulLen, pValue);
}

//获取响应消息报文中的结果信息
ULONG COMP_GetResult(VOID *pMsgPkg)
{
	ULONG ulRet ;
	ULONG ulResult;

	VOID *pDecodeMsg = NULL;

	pDecodeMsg = Dmdcp_DecodeStart( 0, pMsgPkg);

	ulRet = Dmdcp_GetOidValuebyType(pDecodeMsg, SERIALSERV_OPERATION_RESULT, (UCHAR *)&ulResult);

	/* dmdc协议报文编码结束 */
    Dmdcp_DecodeEnd(pDecodeMsg);

	return ulResult;
}

ULONG  COMP_SetEndOfMsg(VOID *pMsgPkg)
{
	/* dmdc协议报文编码结束 */

    Dmdcp_EncodeEnd(pMsgPkg);
	
	return 1;
}

//心跳消息包
/*****************************************************************************
 函 数 名  : COMP_CreateHeartMsg
 功能描述  : 生成心跳Get消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
void * COMP_CreateHeartMsg()
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    // /* 系统配置参数 begin */

    /* 系统配置参数 end */
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_INFO_HEART  , 0 , NULL);
	/* dmdc协议报文编码结束 */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}


/*****************************************************************************
 函 数 名  : COMP_FreeMsg
 功能描述  : 释放消息包
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID COMP_FreeMsg(VOID *pMsg)
{
	DMDCPINFO_STRU * pstDmdcInfo = NULL;
	VOID *pMsgInfo = NULL;

	if (pMsg == NULL)
	{
		return ;
	}

	pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

	pMsgInfo    = (VOID*)((UCHAR *)pstDmdcInfo->pMsg - sizeof(DMDCPHEAD_STRU));

	if (pMsgInfo != NULL)
	{
		free(pMsgInfo);
	}

	free(pMsg );
}


/*****************************************************************************
 函 数 名  : COMP_GetMsgSize
 功能描述  : 获取消息包大小
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
ULONG COMP_GetMsgSize(VOID *pMsgPkg)
{
	DMDCPINFO_STRU *pstDmdcInfo = NULL;
	ULONG ulSize = 0;

	pstDmdcInfo = (DMDCPINFO_STRU*)pMsgPkg;


	ulSize = ntohl(pstDmdcInfo->stDmdcHead.ulMsgLen)  + sizeof(DMDCPHEAD_STRU) ;

	return ulSize;
}

/*****************************************************************************
 函 数 名  : COMP_GetMsgData
 功能描述  : 获取消息包中数据指针
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID *COMP_GetMsgData(VOID *pMsgPkg)
{

	DMDCPINFO_STRU *pstDmdcInfo = NULL;
	ULONG ulSize = 0;
	VOID *pSendMsg = NULL;

	pstDmdcInfo = (DMDCPINFO_STRU*)pMsgPkg;


	pSendMsg    = (VOID*)((ULONG)pstDmdcInfo->pMsg - sizeof(DMDCPHEAD_STRU));

	return pSendMsg;
}

/*****************************************************************************
 函 数 名  : COMP_GetPortChannelStatistics
 功能描述  : 生成特定端口的数据发送统计请求
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID *COMP_GetPortChannelStatistics(ULONG ulPort, UCHAR ucChannel)
{
	ULONG         ulRet = 0;
	VOID         *pEncodeMsg   = NULL;
	VOID         *pSendMsg     = NULL;
	ULONG         ulBodyTlvLen = COMP_MSG_MAX_SIZE ;
	DMDCPINFO_STRU* pstDmdcInfo = NULL;

	pEncodeMsg = Dmdcp_EncodeStart( 0, ulBodyTlvLen, 0);
    if ( NULL_PTR == pEncodeMsg)
    {
        return NULL_PTR;
    }

	//串口1填入，后面看设备怎么定义
	ulRet = COMP_CreateGetMsg(ulPort , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}
	
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_STA_CHANNELNO            , 1 , &ucChannel);

	return  (VOID *)pEncodeMsg;

}

/*****************************************************************************
 函 数 名  : COMP_GetPortChannelStisticData
 功能描述  : 解析特定端口的数据统计数据
 输入参数  : 略
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年4月7日
    作    者   : HYF
    修改内容   : 新生成函数

*****************************************************************************/
VOID COMP_GetPortChannelStisticData(VOID *pMsg, CChannelStatistics *pChannelStatic)
{
	VOID* pDecodeMsg = NULL_PTR;

	if (pChannelStatic == NULL)
	{
		return ;
	}

	pDecodeMsg = Dmdcp_DecodeStart( 0, pMsg);
    if ( NULL_PTR == pDecodeMsg)
    {
        return ;
    }

	UCHAR ucChannelNo = pChannelStatic->Get_ChannelNO();
	ULONG ulSendNum   = 0;
	ULONG ulSendSize  = 0;
	ULONG ulRecNum   = 0;
	ULONG ulRecSize  = 0;
	ULONG ulRemoteIP = 0;
	USHORT usRemportPort = 0;

	//SERIALSERV_STA_CHANNELNO,           /* COM CHANNELNO, UCHAR类型, 长度:1 */ 
	//SERIALSERV_STA_SENDNUM,             /* 发送报文个数,  ULONG类型, 长度:4 */ 
    //SERIALSERV_STA_SENDSIZE,            /* 发送报文大小,  ULONG类型, 长度:4 */

    //SERIALSERV_STA_RECNUM,              /* 接收报文个数,  ULONG类型, 长度:4 */ 
    //SERIALSERV_STA_RECSIZE,             /* 接收报文大小,  ULONG类型, 长度:4 */

	//SERIALSERV_STA_REMOTEIP,             /* 远端IP,       ULONG类型, 长度:4 */
    //SERIALSERV_STA_REMOTEPORT,           /* 远端PORT,     USHORT类型,长度:2 */

	ULONG ulType;
	while ( FALSE == Dmdcp_IsEnd(pDecodeMsg) )
    {  
	   (VOID)Dmdcp_GetCurOidType( pDecodeMsg, &ulType);
	    switch ( ulType )
	    {
		    case SERIALSERV_STA_CHANNELNO :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(UCHAR), &ucChannelNo);

				ASSERT(ucChannelNo == pChannelStatic->Get_ChannelNO());
				break;

		    case SERIALSERV_STA_REMOTEIP :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(ULONG), &ulRemoteIP);
				ulRemoteIP = ntohl(ulRemoteIP);
				break;

			case SERIALSERV_STA_REMOTEPORT :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(USHORT), &usRemportPort);
				usRemportPort = ntohs(usRemportPort);
				break;
            
		    case SERIALSERV_STA_SENDNUM :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(ULONG), &ulSendNum);
				ulSendNum = ntohl(ulSendNum);
				break;

			case SERIALSERV_STA_SENDSIZE :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(ULONG), &ulSendSize);
				ulSendSize = ntohl(ulSendSize);
				break;

			case SERIALSERV_STA_RECNUM :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(ULONG), &ulRecNum);
				ulRecNum = ntohl(ulRecNum);
				break;

			case SERIALSERV_STA_RECSIZE :
				(VOID)Dmdcp_GetCurOidValue(pDecodeMsg, sizeof(ULONG), &ulRecSize);
				ulRecSize = ntohl(ulRecSize);
				break;

		}

		(VOID)Dmdcp_SeekNext( pDecodeMsg ); 

    }

	Dmdcp_DecodeEnd(pDecodeMsg);

	pChannelStatic->Set_RemoteIP(ulRemoteIP);
	pChannelStatic->Set_RemotePort(usRemportPort);
	pChannelStatic->Set_SendNum(ulSendNum);
	pChannelStatic->Set_SendSize(ulSendSize);
	pChannelStatic->Set_RecNum(ulRecNum);
	pChannelStatic->Set_RecSize(ulRecSize);
}