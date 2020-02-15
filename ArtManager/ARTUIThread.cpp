/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：CARTUIThread.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: ART UI Task基类实现
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
// ARTUIThread.cpp : 实现文件

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

