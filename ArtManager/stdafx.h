
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#define FD_SETSIZE 256


// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxcview.h>


#include <afxdisp.h>        // MFC �Զ�����

#include <Ws2tcpip.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afxdlgs.h>
#include <afx.h>

#include "Resource.h"

typedef  unsigned long   ULONG ;
typedef  unsigned int    UINT  ;
typedef  int             INT   ;
typedef  unsigned long   ULONG ;
typedef  long            LONG  ;
typedef  unsigned short  USHORT;
typedef  short           SHORT ;
typedef  unsigned char   UCHAR ;
typedef  char            CHAR;

#define  NULL_PTR        NULL 
#define  VOS_ERR         1
#define  VOS_OK          0

class CDevice;
typedef CTypedPtrList<CObList, CDevice *>   CDeviceList;

class CPort;
typedef CTypedPtrList<CObList, CPort *>   CPortList;

class CPortChannel;
typedef CTypedPtrList<CObList, CPortChannel *>   CChannelList;


class CLog;
typedef CTypedPtrList<CObList, CLog *>   CLogList;

#include "Tlv.h"
#include "Dmdcp.h"
#include "COMP.h"
#include "DataDefine.h"
#include "CommonFunc.h"

#include "XEvent.h"
#include "XSocket.h"

#include "ARTUIThread.h"
#include "ARTDevSearchTask.h"
#include "COMM.h"
#include "DevManager.h"
#include "Device.h"
#include "Port.h"
#include "PortChannel.h"
#include "TCPClientPortMode.h"
#include "TCPServerPortMode.h"
#include "RealCOMPortMode.h"
#include "UDPPortMode.h"
#include "ChannelStatistics.h"
#include "Log.h"

#include "LogManager.h"

#define WM_COMPLETE WM_USER+101
#define WM_SEARCH   WM_USER+102
#define WM_MONITOR  WM_USER+103

#define TIME_INTERVAL_MONITOR   3000

