
// ARTDoc.h : CARTDoc 类的接口
//


#pragma once
class CDevManager;
class CARTLog;

class CARTDoc : public CDocument
{
protected: // 仅从序列化创建
	CARTDoc();
	DECLARE_DYNCREATE(CARTDoc)

// 特性
public:

// 操作
public:
	UINT   m_ulFunctionMode ;
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
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

// 生成的消息映射函数
	afx_msg void OnFuncSelect(UINT nCommandID);
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
