/******************************************************************************

                  版权所有 (C), 2012-2022, 西安xxx信息科技有限公司

 ******************************************************************************
  文 件 名   : Tlv.cpp
  版 本 号   : 初稿
  作    者   : qzz
  生成日期   : 2013年3月19日
  最近修改   :
  功能描述   : tlv算法头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 创建文件

******************************************************************************/

#include "stdafx.h"
#include "Tlv.h"

#define VOS_MemCpy memcpy

/*****************************************************************************
 函 数 名  : VOS_PackageTlv
 功能描述  : TLV格式组装数据
 输入参数  : TLVDATA_STRU* pTlvData  
             ULONG ulType            
             ULONG ulLen             
             VOID* pValue            
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG VOS_SetTlv(TLVDATA_STRU* pstTlvData, ULONG ulType, ULONG ulLen, VOID* pValue)
{
    TLVDATA_STRU stTlvData;
    TLVDATA_STRU* pstNextTlvDataAddr = NULL_PTR;
    
    if ( (NULL_PTR == pstTlvData) || ((NULL_PTR == pValue)&&(0 != ulLen)))
    {
        return VOS_ERR;
    }

    stTlvData.ulType = htonl(ulType);
    stTlvData.ulLen = htonl(ulLen);

    VOS_MemCpy(pstTlvData, &stTlvData, sizeof(TLVDATA_STRU));

    if ( 0 != ulLen )
    {
        VOS_MemCpy(pstTlvData->aucValue, pValue, ulLen);
    }
    
    return VOS_OK;
    
}

/*****************************************************************************
 函 数 名  : VOS_SetTlvEndFlag
 功能描述  : 设置tlv格式数据的结束标示
 输入参数  : TLVDATA_STRU* pstTlvData  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID VOS_SetTlvEndFlag(TLVDATA_STRU* pstTlvData)
{
    UCHAR* pucTlvData = NULL_PTR;
    
    if ( NULL_PTR == pstTlvData)
    {
        return;
    }

    pucTlvData = (UCHAR*)pstTlvData;

    pucTlvData[0] = 0xaa;
    pucTlvData[1] = 0xbb;
    pucTlvData[2] = 0xcc;
    pucTlvData[3] = 0xdd;

    return;
}

/*****************************************************************************
 函 数 名  : VOS_IsTlvEnd
 功能描述  : 判断是否已经到tlv格式数据的底部
 输入参数  : TLVDATA_STRU* pstTlvData  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
UCHAR VOS_IsTlvEnd(TLVDATA_STRU* pstTlvData)
{
    UCHAR* pucTlvData = NULL_PTR;
    
    if ( NULL_PTR == pstTlvData)
    {
        return TRUE;
    }

    pucTlvData = (UCHAR*)pstTlvData;

    if ( (0xaa == pucTlvData[0]) && (0xbb == pucTlvData[1])
      && (0xcc == pucTlvData[2]) && (0xdd == pucTlvData[3]))
    {
        return TRUE;
    }

    return FALSE;
}

/*****************************************************************************
 函 数 名  : VOS_GetTlvValue
 功能描述  : 获取tlv数据
 输入参数  : TLVDATA_STRU* pstTlvData  
             UCHAR* pucTlvValue        
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG VOS_GetTlvValue(TLVDATA_STRU* pstTlvData, ULONG ulTlvLen, UCHAR* pucTlvValue)
{
    ULONG ulLen;
    
    if ( (NULL_PTR == pstTlvData) || (NULL_PTR == pucTlvValue))
    {
        return VOS_ERR;
    }

    VOS_MemCpy(&ulLen, &(pstTlvData->ulLen), sizeof(ULONG));

    ulLen = ntohl(ulLen);
    if ( ulLen > ulTlvLen )
    {
        return VOS_ERR;
    }

    VOS_MemCpy(pucTlvValue, pstTlvData->aucValue, ulLen);


    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : VOS_GetNextTlvAddr
 功能描述  : 获取下一个tlv数据地址
 输入参数  : TLVDATA_STRU* pstCurTlvDataAddr  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
TLVDATA_STRU* VOS_GetNextTlvAddr(TLVDATA_STRU* pstCurTlvDataAddr)
{
    TLVDATA_STRU* pstNextTlvDataAddr = NULL_PTR;
    ULONG ulCurLen;
    
    if ( NULL_PTR == pstCurTlvDataAddr)
    {
        return NULL_PTR;
    }

    VOS_MemCpy(&ulCurLen, &(pstCurTlvDataAddr->ulLen), sizeof(ULONG));

    pstNextTlvDataAddr = (TLVDATA_STRU*)(((UCHAR*)pstCurTlvDataAddr) + sizeof(TLVDATA_STRU) + ntohl(ulCurLen));

    return pstNextTlvDataAddr;
}


/*****************************************************************************
 函 数 名  : VOS_GetTlvValuebyType
 功能描述  : 根据tlv的type获取tlv的value
 输入参数  : TLVDATA_STRU* pstTlvData  
             ULONG ulType              
             UCHAR* pucTlvValue        
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年3月19日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
ULONG VOS_GetTlvValuebyType(TLVDATA_STRU* pstTlvData, ULONG ulType, UCHAR* pucTlvValue)
{
    TLVDATA_STRU* pstCurTlvData = NULL_PTR; 

    ULONG ulCurType;
    ULONG ulCurLen;
    
    if ( (NULL_PTR == pstTlvData) || (NULL_PTR == pucTlvValue))
    {
        return VOS_ERR;
    }

    pstCurTlvData = pstTlvData;

    while ( FALSE == VOS_IsTlvEnd(pstCurTlvData) )
    {
        VOS_MemCpy(&ulCurType, &(pstCurTlvData->ulType), sizeof(ULONG));
        ulCurType = ntohl(ulCurType);
        if ( ulCurType == ulType)
        {
            VOS_MemCpy(&ulCurLen, &(pstCurTlvData->ulLen), sizeof(ULONG));
            VOS_MemCpy(pucTlvValue, pstCurTlvData->aucValue, ntohl(ulCurLen));
            return VOS_OK;
        }

        pstCurTlvData = VOS_GetNextTlvAddr(pstCurTlvData);        
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : VOS_GetTlvAddrbyType
 功能描述  : 根据tlv的type获取tlv的地址
 输入参数  : TLVDATA_STRU* pstTlvData  
             ULONG ulType              
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2013年7月23日
    作    者   : qzz
    修改内容   : 新生成函数

*****************************************************************************/
VOID* VOS_GetTlvAddrbyType(TLVDATA_STRU* pstTlvData, ULONG ulType)
{
    TLVDATA_STRU* pstCurTlvData = NULL_PTR; 

    ULONG ulCurType;
    
    if ( NULL_PTR == pstTlvData)
    {
        return NULL_PTR;
    }

    pstCurTlvData = pstTlvData;

    while ( FALSE == VOS_IsTlvEnd(pstCurTlvData) )
    {
        VOS_MemCpy(&ulCurType, &(pstCurTlvData->ulType), sizeof(ULONG));
        ulCurType = ntohl(ulCurType);
        if ( ulCurType == ulType)
        {
            return pstCurTlvData;
        }

        pstCurTlvData = VOS_GetNextTlvAddr(pstCurTlvData);        
    }

    return NULL_PTR;
}


