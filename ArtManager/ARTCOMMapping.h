#pragma once


// CARTCOMMapping 视图
class CARTDoc ;

class CARTCOMMapping : public CListView
{
	DECLARE_DYNCREATE(CARTCOMMapping)

protected:
	CARTCOMMapping();           // 动态创建所使用的受保护的构造函数
	virtual ~CARTCOMMapping();
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
public:
	CARTDoc* GetDocument() const ;// 非调试版本是内联的
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


