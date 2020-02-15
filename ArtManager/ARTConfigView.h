/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTConfigView.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTConfigView ��Ľӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once

class CARTDoc ;
class CARTConfigSheet;

class CARTConfigView : public CListView
{
public: // �������л�����
	CARTConfigView();
	DECLARE_DYNCREATE(CARTConfigView)

// ����
public:
	CARTDoc* GetDocument() const;


// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CARTConfigView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

protected:


// ���ɵ���Ϣӳ�亯��
protected:
	
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:

	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // ARTConfigView.cpp �еĵ��԰汾
inline CARTDoc* CARTConfigView::GetDocument() const
   { return reinterpret_cast<CARTDoc*>(m_pDocument); }
#endif

