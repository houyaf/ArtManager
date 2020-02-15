/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名： ARTMonitor.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTMonitor 类接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

// CARTMonitor 视图
class CARTDoc ;
class CARTMonitorTask;

class CARTMonitor : public CListView
{
	DECLARE_DYNCREATE(CARTMonitor)

protected:
	CARTMonitor();           // 动态创建所使用的受保护的构造函数
	virtual ~CARTMonitor();
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
// 特性
public:
	CARTDoc* GetDocument() const;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif


public:
	CARTMonitorTask *m_pMonitorTask ;
	BOOL             m_bRunning     ;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);


};


