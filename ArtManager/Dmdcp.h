#pragma once

#define   DMDCP_TLVENDFLAG_LEN   4    /* TLV���������ʾ�ַ����� */
#define   DMDCP_TLVRET_LEN       12   /* TLV�����б�ʾ����������볤�� */
#define   DMDCP_TLVRESERVE_LEN   (DMDCP_TLVENDFLAG_LEN + DMDCP_TLVRET_LEN)

typedef struct DMDCPHEAD
{
    ULONG   ulMsgLen;       // ���ĳ���

    UCHAR   ucVersion;      // ���İ汾��
    UCHAR   ucEncodeType;   // ���ļ�������
    UCHAR   ucCompressType; // ����ѹ������
    UCHAR   ucReserve;      // Ԥ��
    
    ULONG   ulCrc;          // ����crcУ��ֵ
    ULONG   ulMsgNo;        // ������ˮ��
          
}DMDCPHEAD_STRU;

typedef struct DMDCPINFO
{
    
    DMDCPHEAD_STRU stDmdcHead; // ����ͷ
    
    VOID*   pMsg;              // ָ��������ͷ
    VOID*   pCurMsg;           // ָ��ǰ��������

    ULONG   ulCurMsgLen;       // ��ǰ���ĳ���
    
    
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
