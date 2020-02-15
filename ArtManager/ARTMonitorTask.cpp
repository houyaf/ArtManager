/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTMonitorTask.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: Monitor Task������ʵ��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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
�� �� �� :OnMonitor
�������� :�豸���������Ϣ����
������� :ip��Χ
������� :��
�� �� ֵ :void
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
				
				szLog.Format("�豸%s����!",IP_DW2STR(dwDevIP));
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
				szLog.Format("�豸%s��������!",IP_DW2STR(dwDevIP));
				pLogManager->AddLog(LOG_MONITOR,(LPCTSTR)szLog);
			}
		}
	}
	
	//����ɨ�������Ϣ
	PostMessage(pView->m_hWnd, WM_COMPLETE, 0, 0);
}
