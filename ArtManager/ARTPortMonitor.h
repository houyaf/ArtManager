#pragma once


// CARTPortMonitor ��ͼ
class CARTDoc;

class CARTPortMonitor : public CListView
{
	DECLARE_DYNCREATE(CARTPortMonitor)

protected:
	CARTPortMonitor();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CARTPortMonitor();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
public:
	 CARTDoc* GetDocument() const ;// �ǵ��԰汾��������

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


