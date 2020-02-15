#include "stdafx.h"
#include "Dmdcp.h"

#define VOS_Malloc  malloc 
#define VOS_MemSet  memset
#define VOS_MemCpy  memcpy
#define VOS_Free    free

/*****************************************************************************
 函 数 名  : Dmdcp_GetDmdcpHead
 功能描述  : 获取协议报文的头地址
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID*  Dmdcp_GetDmdcpHead( VOID* pMsg )
{
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return NULL_PTR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    return (VOID*)((ULONG)pstDmdcInfo->pMsg - sizeof(DMDCPHEAD_STRU));
}

/*****************************************************************************
 函 数 名  : Dmdcp_DecodeStart
 功能描述  : dmdc协议解码开始
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID* pMsg
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID*  Dmdcp_DecodeStart( ULONG ulModuleId, VOID* pMsg )
{
    DMDCPINFO_STRU* pstDmdcpInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return NULL_PTR;
    }

    pstDmdcpInfo = (DMDCPINFO_STRU*)VOS_Malloc(sizeof(DMDCPINFO_STRU));
    if ( NULL_PTR == pstDmdcpInfo)
    {
        return NULL_PTR;
    }
    VOS_MemSet(pstDmdcpInfo, 0, sizeof(DMDCPINFO_STRU));

    VOS_MemCpy(pstDmdcpInfo, pMsg, sizeof(DMDCPHEAD_STRU));

    pstDmdcpInfo->stDmdcHead.ulCrc = ntohl(pstDmdcpInfo->stDmdcHead.ulCrc);
    pstDmdcpInfo->stDmdcHead.ulMsgLen = ntohl(pstDmdcpInfo->stDmdcHead.ulMsgLen);
    pstDmdcpInfo->stDmdcHead.ulMsgNo = ntohl(pstDmdcpInfo->stDmdcHead.ulMsgNo);

    pstDmdcpInfo->pMsg = (VOID*)((ULONG)pMsg + sizeof(DMDCPHEAD_STRU));
    pstDmdcpInfo->pCurMsg = pstDmdcpInfo->pMsg;

    /* 版本校验 */

    /* 解密 */

    /* 解压缩 */

    /* crc校验 */

    

    return (VOID*)pstDmdcpInfo;
     
}


/*****************************************************************************
 函 数 名  : Dmdcp_DecodeEnd
 功能描述  : dmdc协议解码结束
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID  Dmdcp_DecodeEnd( VOID* pstDmdcp )
{
    
    if ( NULL_PTR == pstDmdcp)
    {
        return;
    }

    VOS_Free(pstDmdcp);

    return;
}




/*****************************************************************************
 函 数 名  : Dmdcp_EncodeStart
 功能描述  : dmdc协议编码开始
 输入参数  : VOID
 输出参数  : 无
 返 回 值  : VOID* pMsg
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月22日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID*  Dmdcp_EncodeStart( ULONG ulModuleId, ULONG ulDmdcpMsgBodyLen, ULONG ulLinkId)
{
    DMDCPINFO_STRU* pstDmdcpInfo = NULL_PTR;
    VOID* pMsg = NULL_PTR;
    ULONG ulDmdcpMsgLen = 0;


    pstDmdcpInfo = (DMDCPINFO_STRU *)VOS_Malloc(sizeof(DMDCPINFO_STRU));
    if ( NULL_PTR == pstDmdcpInfo)
    {
        return NULL_PTR;
    }
    VOS_MemSet(pstDmdcpInfo, 0, sizeof(DMDCPINFO_STRU));

    /* 申请要生成的报文(原始长度) */
    ulDmdcpMsgLen = (ulDmdcpMsgBodyLen + sizeof(DMDCPHEAD_STRU) + DMDCP_TLVRESERVE_LEN);
    pMsg = VOS_Malloc(ulDmdcpMsgLen);
    if ( NULL_PTR == pMsg)
    {
        return NULL_PTR;
    }
    VOS_MemSet(pMsg, 0, ulDmdcpMsgLen);
    

    pstDmdcpInfo->pMsg = (VOID*)((ULONG)pMsg + sizeof(DMDCPHEAD_STRU));
    pstDmdcpInfo->pCurMsg = pstDmdcpInfo->pMsg;
    pstDmdcpInfo->stDmdcHead.ulMsgLen = ulDmdcpMsgBodyLen;
    
    return (VOID*)pstDmdcpInfo;
     
}

/*****************************************************************************
 函 数 名  : Dmdcp_EncodeEnd
 功能描述  : dmdc协议编码结束
 输入参数  : VOID* pstDmdcp  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID  Dmdcp_EncodeEnd( VOID* pstDmdcp )
{
    ULONG ulRet = VOS_OK;
    DMDCPINFO_STRU* pstDmdcpInfo = NULL_PTR;
    UCHAR* pucMsg = NULL_PTR;
    VOID*  ptoNetDmdcp = NULL_PTR;
    
    if ( NULL_PTR == pstDmdcp)
    {
        return;
    }

    pstDmdcpInfo = (DMDCPINFO_STRU*)pstDmdcp;

    /* 设置结束标志 */
    VOS_SetTlvEndFlag((TLVDATA_STRU *)pstDmdcpInfo->pCurMsg);

    /* 计算crc */

    /* 压缩 */

    /* 加密 */

    /* 设置版本 */

    pucMsg = (UCHAR*)((ULONG)(pstDmdcpInfo->pMsg) - sizeof(DMDCPHEAD_STRU));

    pstDmdcpInfo->stDmdcHead.ulMsgLen = htonl(pstDmdcpInfo->ulCurMsgLen + 4);
    VOS_MemCpy(pucMsg, &(pstDmdcpInfo->stDmdcHead), sizeof(DMDCPHEAD_STRU));

#if 0
    /* 填充完毕后发送 */
    ptoNetDmdcp = Dmdcp_GetDmdcpHead(pstDmdcpInfo);
    ulRet = Esdp_SendMsg(ESDP_MODULE_ID_COMMON, ESDP_MODULE_ID_BUS, ptoNetDmdcp);
    if ( VOS_OK != ulRet)
    {
        Esdp_FreeMsg(ptoNetDmdcp);
        LOG_Write(LOG_ERROR, "[%s:%d] send msg fail, ulRet = %d \r\n",__FILE__, __LINE__, ulRet);
    }
    else
    {
        
    }

    VOS_Free(pstDmdcpInfo);
#endif

    return;
}


/*****************************************************************************
 函 数 名  : Dmdcp_SeekHead
 功能描述  : 将指针定位到报文的头
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_SeekHead( VOID* pMsg )
{
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    pstDmdcInfo->pCurMsg = pstDmdcInfo->pMsg;

    pstDmdcInfo->ulCurMsgLen = 0;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Dmdcp_Seek
 功能描述  : 将指针定位到OidType位置
 输入参数  : VOID* pMsg       
             ULONG ulOidType  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_Seek( VOID* pMsg, ULONG ulOidType )
{
    VOID* pCurMsg = NULL_PTR;
    
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;
    
    pCurMsg = VOS_GetTlvAddrbyType((TLVDATA_STRU*) (pstDmdcInfo->pMsg), ulOidType);
    if ( NULL_PTR == pCurMsg)
    {
        return VOS_ERR;
    }

    pstDmdcInfo->pCurMsg = pCurMsg;

    pstDmdcInfo->ulCurMsgLen = (ULONG)pCurMsg - (ULONG)(pstDmdcInfo->pMsg);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Dmdcp_SeekNext
 功能描述  : 指针指向下一个oid数据位置
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_SeekNext( VOID* pMsg )
{
    VOID* pCurMsg = NULL_PTR;
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }

    if ( TRUE == Dmdcp_IsEnd( pMsg ))
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    pCurMsg = (VOID*)VOS_GetNextTlvAddr( (TLVDATA_STRU*)(pstDmdcInfo->pCurMsg));

    pstDmdcInfo->pCurMsg = pCurMsg;

    pstDmdcInfo->ulCurMsgLen = (ULONG)pCurMsg - (ULONG)(pstDmdcInfo->pMsg);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Dmdcp_IsEnd
 功能描述  : 判断是否已经到报文的底部
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
UCHAR Dmdcp_IsEnd( VOID* pMsg )
{
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return TRUE;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    if ( (pstDmdcInfo->ulCurMsgLen >= pstDmdcInfo->stDmdcHead.ulMsgLen)
      || (TRUE == VOS_IsTlvEnd((TLVDATA_STRU*)(pstDmdcInfo->pCurMsg))))
    {
        return TRUE;
    }

    return FALSE;
}

/*****************************************************************************
 函 数 名  : Dmdcp_GetCurOidAddr
 功能描述  : 获取当前oid数据地址
 输入参数  : VOID* pMsg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID*  Dmdcp_GetCurOidAddr( VOID* pMsg )
{
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( NULL_PTR == pMsg)
    {
        return NULL_PTR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    return (pstDmdcInfo->pCurMsg);
}

/*****************************************************************************
 函 数 名  : Dmdcp_GetCurOidType
 功能描述  : 获取当前位置oid的类型
 输入参数  : VOID* pMsg        
             VOID* pucOidType  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月31日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_GetCurOidType( VOID* pMsg, ULONG* pulOidType )
{
    ULONG ulType;
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;
    TLVDATA_STRU*   pstTlv = NULL_PTR;

    if ( (NULL_PTR == pMsg) || (NULL_PTR == pulOidType))
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    pstTlv = (TLVDATA_STRU*)(pstDmdcInfo->pCurMsg);

    VOS_MemCpy(&ulType, &(pstTlv->ulType), sizeof(ULONG));
    *pulOidType = ntohl(ulType);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : Dmdcp_GetCurOidValue
 功能描述  : 获取当前位置oid的值
 输入参数  : VOID* pMsg         
             VOID* pucOidValue  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_GetCurOidValue( VOID* pMsg, ULONG ulOidLen, VOID* pucOidValue )
{
    ULONG ulRet = VOS_OK;
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( (NULL_PTR == pMsg) || (NULL_PTR == pucOidValue))
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    ulRet = VOS_GetTlvValue((TLVDATA_STRU*)(pstDmdcInfo->pCurMsg), ulOidLen, (UCHAR *)pucOidValue);

    return ulRet;
}

/*****************************************************************************
 函 数 名  : Dmdcp_GetOidValuebyType
 功能描述  : 通过oid的type获取oid值
 输入参数  : VOID* pMsg       
             ULONG ulOidType  
             VOID* pOidValue  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG  Dmdcp_GetOidValuebyType( VOID* pMsg, ULONG ulOidType, VOID* pOidValue )
{
    ULONG ulRet = VOS_OK;
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( (NULL_PTR == pMsg) || (NULL_PTR == pOidValue))
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    ulRet = VOS_GetTlvValuebyType((TLVDATA_STRU*)(pstDmdcInfo->pMsg), ulOidType, (UCHAR *)pOidValue);

    return ulRet;

}

/*****************************************************************************
 函 数 名  : Dmdcp_SetOid
 功能描述  : 在当前位置设置oid数据
 输入参数  : VOID* pMsg       
             ULONG ulOidType  
             ULONG ulOidLen   
             VOID* pOidValue  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月24日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG Dmdcp_SetOid( VOID* pMsg, ULONG ulOidType, ULONG ulOidLen, VOID* pOidValue )
{
    ULONG ulRet = VOS_OK;
    DMDCPINFO_STRU* pstDmdcInfo = NULL_PTR;

    if ( (NULL_PTR == pMsg) || ((NULL_PTR == pOidValue) && (0 != ulOidLen)))
    {
        return VOS_ERR;
    }

    pstDmdcInfo = (DMDCPINFO_STRU*)pMsg;

    if ( (pstDmdcInfo->ulCurMsgLen + ulOidLen + sizeof(TLVDATA_STRU)) >= pstDmdcInfo->stDmdcHead.ulMsgLen)
    {
        return VOS_ERR;
    }

    ulRet = VOS_SetTlv((TLVDATA_STRU*) pstDmdcInfo->pCurMsg, ulOidType, ulOidLen, pOidValue);
    if ( VOS_OK == ulRet)
    {
        pstDmdcInfo->ulCurMsgLen += (sizeof(TLVDATA_STRU) + ulOidLen);
        pstDmdcInfo->pCurMsg = (VOID*)((ULONG)(pstDmdcInfo->pCurMsg) + (sizeof(TLVDATA_STRU) + ulOidLen));
    }
    
    return ulRet;
}

