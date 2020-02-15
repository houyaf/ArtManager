/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTMonitorTask.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: Monitor Task任务类实现
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#include "stdafx.h"

#include "ARTMonitorTask.h"
#include "MainFrm.h"
#include "ARTDoc.h"

IMPLEMENT_DYNCREATE(CARTMonitorTask, CARTUIThread)

CARTMonitorTask::CARTMonitorTask(void)
{

}


CARTMonitorTask::~CARTMonitorTask(void)
{

}

BOOL CARTMonitorTask::InitInstance()
{
	return TRUE;
}


BEGIN_MESSAGE_MAP(CARTMonitorTask, CWinThread)
	//{{AFX_MSG_MAP(CARTDevSearchTask)
		// NOTE - the ClassWizard will add and remove mapping macros here.

	ON_THREAD_MESSAGE(WM_MONITOR, OnMonitor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/**************************************************************************************************
函 数 名 :OnMonitor
功能描述 :设备监控任务消息处理
输入参数 :ip范围
输出参数 :无
返 回 值 :void
**************************************************************************************************/
void CARTMonitorTask::OnMonitor(WPARAM wParam,LPARAM lParam)
{
	CMainFrame   *pView       = (CMainFrame *)m_pOwner;
	CARTDoc       *pArtDoc     = (CARTDoc *)pView->GetActiveView()->GetDocument();
	

	CDevManager   *pDevManager = (CDevManager *)pArtDoc->GetDeviceManager();
	CDeviceList   *pDevList    = NULL;
	CDevice       *pDevice     = NULL ;
	POSITION       pos  ;
	BOOL           bRet ;
	int            iDevStatus ;
	int            iRet;
	CString        szLog;
	CLogManager   *pLogManager = (CLogManager *)pArtDoc->GetLogManager();
	DWORD          dwDevIP;
    ASSERT(pView);
	ASSERT(pDevManager);

	pDevList = pDevManager->Get_DevList();

	pos = pDevList->GetHeadPosition();
	while(pos != NULL)
	{
		pDevice = pDevList->GetNext(pos);
		dwDevIP = pDevice->Get_DevIP();
		iDevStatus = pDevice->Get_DevStatus();
		if (iDevStatus==1)
		{
			bRet    = pDevice->SayHello();

			if (!bRet)
			{
				pDevice->Set_DevStatus(2);
				
				szLog.Format("设备%s下线!",IP_DW2STR(dwDevIP));
				pLogManager->AddLog(LOG_MONITOR,(LPCTSTR)szLog);
			}
			else
			{
				pDevice->GetDevStatic();
			}
		}
		else
		{
			iRet = pDevice->ReConnect();
			if (iRet == 1)
			{
				szLog.Format("设备%s重新上线!",IP_DW2STR(dwDevIP));
				pLogManager->AddLog(LOG_MONITOR,(LPCTSTR)szLog);
			}
		}
	}
	
	//发送扫描完成消息
	PostMessage(pView->m_hWnd, WM_COMPLETE, 0, 0);
}
