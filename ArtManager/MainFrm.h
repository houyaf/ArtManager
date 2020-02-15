
// MainFrm.h : CMainFrame ��Ľӿ�
//
#define NUMVIEWS 4
class CARTDoc ;
#pragma once
class CARTConfigView;
class CARTDoc;
class CARTMonitorTask;
class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	CSplitterWnd	m_wndFuncSplitter;
	CSplitterWnd	m_wndSplitter;
	BOOL			m_bSplitterCreated;
public:
	
	CARTMonitorTask *m_pMonitorTask ;
	BOOL             m_bRunning     ;

    // Index to current view
    UINT m_nCurView;   

// ����
public:


// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();

public: 
	void CreateFuncView(int iFuncMode);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar  ;
	CReBar            m_wndReBar    ;
	CDialogBar        m_wndDlgBar   ;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFuncSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusTime(CCmdUI* pCmdUI);
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDocument* GetActiveDocument();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnConsole();
};


