/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTConfigView.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTConfigView 类的接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

class CARTDoc ;
class CARTConfigSheet;

class CARTConfigView : public CListView
{
public: // 仅从序列化创建
	CARTConfigView();
	DECLARE_DYNCREATE(CARTConfigView)

// 特性
public:
	CARTDoc* GetDocument() const;


// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CARTConfigView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

protected:


// 生成的消息映射函数
protected:
	
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:

	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // ARTConfigView.cpp 中的调试版本
inline CARTDoc* CARTConfigView::GetDocument() const
   { return reinterpret_cast<CARTDoc*>(m_pDocument); }
#endif

