/******************************************************************************

                  ��Ȩ���� (C), 2012-2022, ����xxx��Ϣ�Ƽ����޹�˾

 ******************************************************************************
  �� �� ��   : Tlv.cpp
  �� �� ��   : ����
  ��    ��   : qzz
  ��������   : 2013��3��19��
  ����޸�   :
  ��������   : tlv�㷨ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ļ�

******************************************************************************/

#include "stdafx.h"
#include "Tlv.h"

#define VOS_MemCpy memcpy

/*****************************************************************************
 �� �� ��  : VOS_PackageTlv
 ��������  : TLV��ʽ��װ����
 �������  : TLVDATA_STRU* pTlvData  
             ULONG ulType            
             ULONG ulLen             
             VOID* pValue            
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_SetTlvEndFlag
 ��������  : ����tlv��ʽ���ݵĽ�����ʾ
 �������  : TLVDATA_STRU* pstTlvData  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_IsTlvEnd
 ��������  : �ж��Ƿ��Ѿ���tlv��ʽ���ݵĵײ�
 �������  : TLVDATA_STRU* pstTlvData  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_GetTlvValue
 ��������  : ��ȡtlv����
 �������  : TLVDATA_STRU* pstTlvData  
             UCHAR* pucTlvValue        
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_GetNextTlvAddr
 ��������  : ��ȡ��һ��tlv���ݵ�ַ
 �������  : TLVDATA_STRU* pstCurTlvDataAddr  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_GetTlvValuebyType
 ��������  : ����tlv��type��ȡtlv��value
 �������  : TLVDATA_STRU* pstTlvData  
             ULONG ulType              
             UCHAR* pucTlvValue        
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��3��19��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : VOS_GetTlvAddrbyType
 ��������  : ����tlv��type��ȡtlv�ĵ�ַ
 �������  : TLVDATA_STRU* pstTlvData  
             ULONG ulType              
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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


