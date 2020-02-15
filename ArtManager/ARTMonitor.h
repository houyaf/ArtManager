/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ���� ARTMonitor.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTMonitor ��ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once

// CARTMonitor ��ͼ
class CARTDoc ;
class CARTMonitorTask;

class CARTMonitor : public CListView
{
	DECLARE_DYNCREATE(CARTMonitor)

protected:
	CARTMonitor();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CARTMonitor();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
// ����
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


