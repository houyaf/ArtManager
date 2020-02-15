#pragma once

#define   DMDCP_TLVENDFLAG_LEN   4    /* TLV编码结束标示字符长度 */
#define   DMDCP_TLVRET_LEN       12   /* TLV编码中表示操作结果编码长度 */
#define   DMDCP_TLVRESERVE_LEN   (DMDCP_TLVENDFLAG_LEN + DMDCP_TLVRET_LEN)

typedef struct DMDCPHEAD
{
    ULONG   ulMsgLen;       // 报文长度

    UCHAR   ucVersion;      // 报文版本号
    UCHAR   ucEncodeType;   // 报文加密类型
    UCHAR   ucCompressType; // 报文压缩类型
    UCHAR   ucReserve;      // 预留
    
    ULONG   ulCrc;          // 报文crc校验值
    ULONG   ulMsgNo;        // 报文流水号
          
}DMDCPHEAD_STRU;

typedef struct DMDCPINFO
{
    
    DMDCPHEAD_STRU stDmdcHead; // 报文头
    
    VOID*   pMsg;              // 指向报文内容头
    VOID*   pCurMsg;           // 指向当前报文内容

    ULONG   ulCurMsgLen;       // 当前报文长度
    
    
}DMDCPINFO_STRU;



VOID*  Dmdcp_GetDmdcpHead( VOID* pMsg );
VOID*  Dmdcp_DecodeStart( ULONG ulModuleId, VOID* pMsg );
VOID   Dmdcp_DecodeEnd( VOID* pstDmdcp );
VOID*  Dmdcp_EncodeStart( ULONG ulModuleId, ULONG ulDmdcpMsgBodyLen, ULONG ulLinkId);
VOID   Dmdcp_EncodeEnd( VOID* pstDmdcp );
ULONG  Dmdcp_SeekHead( VOID* pMsg );
ULONG  Dmdcp_Seek( VOID* pMsg, ULONG ulOidType );
ULONG  Dmdcp_SeekNext( VOID* pMsg );
UCHAR  Dmdcp_IsEnd( VOID* pMsg );
VOID*  Dmdcp_GetCurOidAddr( VOID* pMsg );
ULONG  Dmdcp_GetCurOidType( VOID* pMsg, ULONG* pulOidType );
ULONG  Dmdcp_GetCurOidValue( VOID* pMsg, ULONG ulOidLen, VOID* pucOidValue );
ULONG  Dmdcp_GetOidValuebyType( VOID* pMsg, ULONG ulOidType, VOID* pOidValue );
ULONG  Dmdcp_SetOid( VOID* pMsg, ULONG ulOidType, ULONG ulOidLen, VOID* pOidValue );
