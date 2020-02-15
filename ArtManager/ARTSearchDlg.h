#pragma once
#include "afxwin.h"
class CARTSearchDlg :	public CDialog
{
	DECLARE_DYNAMIC(CARTSearchDlg)

public:
	CARTSearchDlg(void);
	CARTSearchDlg(UINT IDD, CWnd* pParent);  
	virtual ~CARTSearchDlg(void);

public:
	virtual void SetPorgressInfo(LPCTSTR szInfo);
	virtual void AddFoundDevice(CDevice *pDevice);
	virtual void SetDialogStatus(BOOL bComplete);
	virtual CDevManager *GetDevManger();

public:
	
};

