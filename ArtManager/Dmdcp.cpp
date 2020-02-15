#include "stdafx.h"
#include "Dmdcp.h"

#define VOS_Malloc  malloc 
#define VOS_MemSet  memset
#define VOS_MemCpy  memcpy
#define VOS_Free    free

/*****************************************************************************
 �� �� ��  : Dmdcp_GetDmdcpHead
 ��������  : ��ȡЭ�鱨�ĵ�ͷ��ַ
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_DecodeStart
 ��������  : dmdcЭ����뿪ʼ
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID* pMsg
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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

    /* �汾У�� */

    /* ���� */

    /* ��ѹ�� */

    /* crcУ�� */

    

    return (VOID*)pstDmdcpInfo;
     
}


/*****************************************************************************
 �� �� ��  : Dmdcp_DecodeEnd
 ��������  : dmdcЭ��������
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_EncodeStart
 ��������  : dmdcЭ����뿪ʼ
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID* pMsg
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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

    /* ����Ҫ���ɵı���(ԭʼ����) */
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
 �� �� ��  : Dmdcp_EncodeEnd
 ��������  : dmdcЭ��������
 �������  : VOID* pstDmdcp  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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

    /* ���ý�����־ */
    VOS_SetTlvEndFlag((TLVDATA_STRU *)pstDmdcpInfo->pCurMsg);

    /* ����crc */

    /* ѹ�� */

    /* ���� */

    /* ���ð汾 */

    pucMsg = (UCHAR*)((ULONG)(pstDmdcpInfo->pMsg) - sizeof(DMDCPHEAD_STRU));

    pstDmdcpInfo->stDmdcHead.ulMsgLen = htonl(pstDmdcpInfo->ulCurMsgLen + 4);
    VOS_MemCpy(pucMsg, &(pstDmdcpInfo->stDmdcHead), sizeof(DMDCPHEAD_STRU));

#if 0
    /* �����Ϻ��� */
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
 �� �� ��  : Dmdcp_SeekHead
 ��������  : ��ָ�붨λ�����ĵ�ͷ
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_Seek
 ��������  : ��ָ�붨λ��OidTypeλ��
 �������  : VOID* pMsg       
             ULONG ulOidType  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_SeekNext
 ��������  : ָ��ָ����һ��oid����λ��
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_IsEnd
 ��������  : �ж��Ƿ��Ѿ������ĵĵײ�
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_GetCurOidAddr
 ��������  : ��ȡ��ǰoid���ݵ�ַ
 �������  : VOID* pMsg  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_GetCurOidType
 ��������  : ��ȡ��ǰλ��oid������
 �������  : VOID* pMsg        
             VOID* pucOidType  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_GetCurOidValue
 ��������  : ��ȡ��ǰλ��oid��ֵ
 �������  : VOID* pMsg         
             VOID* pucOidValue  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��24��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_GetOidValuebyType
 ��������  : ͨ��oid��type��ȡoidֵ
 �������  : VOID* pMsg       
             ULONG ulOidType  
             VOID* pOidValue  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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
 �� �� ��  : Dmdcp_SetOid
 ��������  : �ڵ�ǰλ������oid����
 �������  : VOID* pMsg       
             ULONG ulOidType  
             ULONG ulOidLen   
             VOID* pOidValue  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��7��24��
    ��    ��   : qzz
    �޸�����   : �����ɺ���

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

