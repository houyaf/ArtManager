/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����CARTUIThread.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ART UI Task����ʵ��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
// ARTUIThread.cpp : ʵ���ļ�

#include "stdafx.h"
#include "ARTUIThread.h"


// CARTUIThread

IMPLEMENT_DYNCREATE(CARTUIThread, CWinThread)

CARTUIThread::CARTUIThread()
{
	m_bDone = FALSE;
	m_pOwner = NULL;
	m_bAutoDelete = TRUE;
}

CARTUIThread::~CARTUIThread()
{

}

