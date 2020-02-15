#pragma once


// CARTLog ��ͼ
class CARTDoc;

class CARTLog : public CTabView
{
	DECLARE_DYNCREATE(CARTLog)

protected:
	CARTLog();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CARTLog();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnInitialUpdate();
	CARTDoc* GetDocument() const ;

public:
	void ShowLogView(int iLogType);
};


