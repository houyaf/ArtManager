
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"
#define _CRTDBG_MAP_ALLOC
#include "stdlib.h"
#include "crtdbg.h"
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#define FD_SETSIZE 256


// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxcview.h>


#include <afxdisp.h>        // MFC 自动化类

#include <Ws2tcpip.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
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

