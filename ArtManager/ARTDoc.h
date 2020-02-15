
// ARTDoc.h : CARTDoc ��Ľӿ�
//


#pragma once
class CDevManager;
class CARTLog;

class CARTDoc : public CDocument
{
protected: // �������л�����
	CARTDoc();
	DECLARE_DYNCREATE(CARTDoc)

// ����
public:

// ����
public:
	UINT   m_ulFunctionMode ;
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CARTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CDevManager * m_pDevManager;
	CLogManager * m_pLogManger ;
public :
	CDevManager *GetDeviceManager();
	CLogManager *GetLogManager();

public : 
	CView      *m_RightView;
	CARTLog    *m_LogView  ;

protected:

// ���ɵ���Ϣӳ�亯��
	afx_msg void OnFuncSelect(UINT nCommandID);
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
