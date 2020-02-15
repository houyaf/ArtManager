#include "stdafx.h"
#include "COMP.h"

/*****************************************************************************
 �� �� ��  : COMP_CreateGetMsg
 ��������  : ����Get��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������Ϣ���ݰ���Ŀǰ���ݳ���
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//д��: SERIALSERV_OPERATION_OID
	ulOp_Code = GetTickCount();
	iSize     = 4;
	ulOp_Code = htonl(ulOp_Code);
	ulRet += Dmdcp_SetOid(pEncodeMsg,  SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);
	
	//д��: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_GET;
	iSize     = 1;
	ulRet += Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, iSize, (VOID *)&ucOp_Type);
	

	//д��SERIALSERV_OPERATION_OBJECT
	ulOp_Obj  = ulComNo;
	iSize     = 4;
	ulOp_Obj  = htonl(ulOp_Obj);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);


	return 0;

	
}

/*****************************************************************************
 �� �� ��  : CreateGetMsgOfDeviceInfo
 ��������  : �����豸��ϢGet��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    // /* ϵͳ���ò��� begin */
	//SERIALSERV_SYSPARA_DEVPORTNUM   �˿���Ŀ
    //SERIALSERV_SYSPARA_DATATIME,       /* ϵͳʱ��:1970����������, ULONG����, ����:4 */
    //SERIALSERV_SYSPARA_SYSNAME,        /* sysname,��󳤶�Ϊ SYS_SYSNAMElEN_MAX - 1 */
    //SERIALSERV_SYSPARA_IP,             /* IP, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_IPMASK,         /* IP Subnet Mask, ULONG����, ����:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY,        /* IP GateWay, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_MAC,            /* MAC ����:32*/ 
    //SERIALSERV_SYSPARA_SWVERSION,      /* SW version, ����:4 */
    //SERIALSERV_SYSPARA_UPTIME,         /* ϵͳ����ʱ��:1970�����ĺ���, ULONG����, ����:4 */
    //SERIALSERV_SYSPARA_DEVICEMODEL,    /* �豸����,����μ�ö�� SERIALSERVSYSPARADEVICEMODEL_ENUM, ����:4 */
    /* ϵͳ���ò��� end */

	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DEVPORTNUM   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DATATIME     , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_SYSNAME      , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP           , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_MAC          , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_SWVERSION    , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_UPTIME       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_DEVICEMODEL  , 0 , NULL);
	
	//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, ����μ�ö�� SERIALSERVSYSPARANETMODE_ENUM, ����:1 */ 
    //SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG����, ����:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG����, ����:4 */ 
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_1  , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_1       , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_1   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_1  , 0 , NULL);

    //SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan2 net mode, ����μ�ö�� SERIALSERVSYSPARANETMODE_ENUM, ����:1 */ 
    //SERIALSERV_SYSPARA_IP_2,           /*57 Lan2 IP, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_2,       /*58 Lan2 IP Subnet Mask, ULONG����, ����:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan2 IP GateWay, ULONG����, ����:4 */   
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_2  , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_2       , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_2   , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_2  , 0 , NULL);

	/* dmdcЭ�鱨�ı������ */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 �� �� ��  : COMP_CreateGetMsgOfDeviceNetwork
 ��������  : �����豸��������ip mask
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

	//SERIALSERV_SYSPARA_NETMODE_1,      /*57 Lan1 net mode, ����μ�ö�� SERIALSERVSYSPARANETMODE_ENUM, ����:1 */ 
    //SERIALSERV_SYSPARA_IP_1,           /*57 Lan1 IP, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_1,       /*58 Lan1 IP Subnet Mask, ULONG����, ����:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_1,      /*59 Lan1 IP GateWay, ULONG����, ����:4 */ 
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_1  , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_1       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_1   , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_1  , 0 , NULL);

   
	/* dmdcЭ�鱨�ı������ */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 �� �� ��  : COMP_CreateGetMsgOfDeviceNetwork
 ��������  : �����豸��������ip mask
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    //SERIALSERV_SYSPARA_NETMODE_2,      /*57 Lan2 net mode, ����μ�ö�� SERIALSERVSYSPARANETMODE_ENUM, ����:1 */ 
    //SERIALSERV_SYSPARA_IP_2,           /*57 Lan2 IP, ULONG����, ����:4 */ 
    //SERIALSERV_SYSPARA_IPMASK_2,       /*58 Lan2 IP Subnet Mask, ULONG����, ����:4 */ 
	//SERIALSERV_SYSPARA_GATEWAY_2,      /*59 Lan2 IP GateWay, ULONG����, ����:4 */   
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_NETMODE_2  , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IP_2       , 0 , NULL);
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_IPMASK_2   , 0 , NULL);
	//ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_SYSPARA_GATEWAY_2  , 0 , NULL);

	/* dmdcЭ�鱨�ı������ */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}

/*****************************************************************************
 �� �� ��  : CreateGetMsgOfDeviceInfo
 ��������  : �����豸��ϢGet��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(ulCOMNo , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    
    /* ������һЩ������������ */
    //SERIALSERV_CFG_SWITCH,             /* ���ؾ����ö�� SERIALSERVCFGSWTICH_ENUM, ����:1 */
    //SERIALSERV_CFG_COMNAME,            /* com����, ����:SERIALSERV_NAMELEN_MAX - 1�� 15 */
    
    //SERIALSERV_CFG_PORTMODE,           /* �������;����ö�� SERIALSERVCFGPORTMODE_ENUM, ����:1 */
    //SERIALSERV_CFG_BAUDRATE,           /* ���ڲ�����, ULONG����, ����:4 */
    //SERIALSERV_CFG_WORKMODE,           /* ���ڹ���ģʽ�����ö�� SERIALSERVCFGWORKMODE_ENUM, ����:1 */

    //SERIALSERV_CFG_OPMODE,             /* �������;����ö�� SERIALSERVCFGOPMODE_ENUM, ����:1 */
    //SERIALSERV_CFG_COMIP,              /* COM IP, ULONG����, ����:4 */ 
    //SERIALSERV_CFG_COMPORT,            /* COM PORT, USHORT����, ����:2 */ 
    /* ������һЩ�������� */


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
	//SERIALSERV_CFG_OPMODE1,             /* �������;����ö�� SERIALSERVCFGOPMODE_ENUM, ����:1 */
    //SERIALSERV_CFG_COMIP1,              /* COM IP, ULONG����, ����:4      */ 
    //SERIALSERV_CFG_COMPORT1,            /* COM PORT, USHORT����, ����:2   */ 
    //SERIALSERV_CFG_CONNECTNUM1,         /* CHANNEL CONNECT NUM, ULONG����, ����:5 */

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
 �� �� ��  : COMP_CreateSetMsg
 ��������  : ����Set��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//д��: SERIALSERV_OPERATION_OID
	ulOp_Code= GetTickCount();
	iSize    = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);

	//д��: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_SET;
	iSize     = 1;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, iSize, (VOID *)&ucOp_Type);

	//д��SERIALSERV_OPERATION_OBJECT,�����豸��ʱдΪ1
	//pstOption->ulType  = SERIALSERV_OPERATION_OBJECT;
	ulOp_Obj  = htonl(1);
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);

	
	/* dmdcЭ�鱨�ı������ */
    //Dmdcp_EncodeEnd(pEncodeMsg);

	pstDmdcInfo = (DMDCPINFO_STRU*)pEncodeMsg;

	//pSendMsg    = (VOID*)((ULONG)pstDmdcInfo->pMsg - sizeof(DMDCPHEAD_STRU));
	
	//free(pEncodeMsg);

	return  (VOID *)pstDmdcInfo;
}



/*****************************************************************************
 �� �� ��  : COMP_CreateSetMsgofPort
 ��������  : ����Set��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//д��: SERIALSERV_OPERATION_OID
	ulOp_Code= GetTickCount();
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OID, iSize, (VOID *)&ulOp_Code);

	//д��: SERIALSERV_OPERATION_TYPE
	ucOp_Type = SERIALSERV_OPTYPE_SET;
	iSize     =  1;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_TYPE, 1, (VOID *)&ucOp_Type);

	//д��SERIALSERV_OPERATION_OBJECT,���˿ں�
	ulOp_Obj  = htonl(ulComNo);
	iSize     = 4;
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_OPERATION_OBJECT, iSize, (VOID *)&ulOp_Obj);
	
	
	return  (VOID *)pEncodeMsg;
}


/*****************************************************************************
 �� �� ��  : COMP_GetSubOption
 ��������  : ��ȡ��Ӧ��Ϣ�����е�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

//����Set��Ϣ�����еĵ���������Ϣ
ULONG COMP_SetSubOption(VOID *pMsgPkg, ULONG ulType, ULONG ulLen, VOID *pValue)
{
	return Dmdcp_SetOid((TLVDATA_STRU*)pMsgPkg, ulType, ulLen, pValue);
}

//��ȡ��Ӧ��Ϣ�����еĽ����Ϣ
ULONG COMP_GetResult(VOID *pMsgPkg)
{
	ULONG ulRet ;
	ULONG ulResult;

	VOID *pDecodeMsg = NULL;

	pDecodeMsg = Dmdcp_DecodeStart( 0, pMsgPkg);

	ulRet = Dmdcp_GetOidValuebyType(pDecodeMsg, SERIALSERV_OPERATION_RESULT, (UCHAR *)&ulResult);

	/* dmdcЭ�鱨�ı������ */
    Dmdcp_DecodeEnd(pDecodeMsg);

	return ulResult;
}

ULONG  COMP_SetEndOfMsg(VOID *pMsgPkg)
{
	/* dmdcЭ�鱨�ı������ */

    Dmdcp_EncodeEnd(pMsgPkg);
	
	return 1;
}

//������Ϣ��
/*****************************************************************************
 �� �� ��  : COMP_CreateHeartMsg
 ��������  : ��������Get��Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(1 , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}

    // /* ϵͳ���ò��� begin */

    /* ϵͳ���ò��� end */
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_INFO_HEART  , 0 , NULL);
	/* dmdcЭ�鱨�ı������ */

	ASSERT(ulRet == 0);
   

	return  pEncodeMsg;
}


/*****************************************************************************
 �� �� ��  : COMP_FreeMsg
 ��������  : �ͷ���Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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
 �� �� ��  : COMP_GetMsgSize
 ��������  : ��ȡ��Ϣ����С
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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
 �� �� ��  : COMP_GetMsgData
 ��������  : ��ȡ��Ϣ��������ָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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
 �� �� ��  : COMP_GetPortChannelStatistics
 ��������  : �����ض��˿ڵ����ݷ���ͳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//����1���룬���濴�豸��ô����
	ulRet = COMP_CreateGetMsg(ulPort , pEncodeMsg);
	if (ulRet > 0 )
	{
		return NULL_PTR;
	}
	
	ulRet +=  Dmdcp_SetOid(pEncodeMsg, SERIALSERV_STA_CHANNELNO            , 1 , &ucChannel);

	return  (VOID *)pEncodeMsg;

}

/*****************************************************************************
 �� �� ��  : COMP_GetPortChannelStisticData
 ��������  : �����ض��˿ڵ�����ͳ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��4��7��
    ��    ��   : HYF
    �޸�����   : �����ɺ���

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

	//SERIALSERV_STA_CHANNELNO,           /* COM CHANNELNO, UCHAR����, ����:1 */ 
	//SERIALSERV_STA_SENDNUM,             /* ���ͱ��ĸ���,  ULONG����, ����:4 */ 
    //SERIALSERV_STA_SENDSIZE,            /* ���ͱ��Ĵ�С,  ULONG����, ����:4 */

    //SERIALSERV_STA_RECNUM,              /* ���ձ��ĸ���,  ULONG����, ����:4 */ 
    //SERIALSERV_STA_RECSIZE,             /* ���ձ��Ĵ�С,  ULONG����, ����:4 */

	//SERIALSERV_STA_REMOTEIP,             /* Զ��IP,       ULONG����, ����:4 */
    //SERIALSERV_STA_REMOTEPORT,           /* Զ��PORT,     USHORT����,����:2 */

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