#include "stdafx.h"
#include "ARTSearchDlg.h"
#include "ARTDoc.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CARTSearchDlg, CDialog)
CARTSearchDlg::CARTSearchDlg(void)
{

}


CARTSearchDlg::~CARTSearchDlg(void)
{

}


CARTSearchDlg::CARTSearchDlg(UINT IDD, CWnd* pParent = NULL)
	:CDialog(IDD, pParent)
{

}

void CARTSearchDlg::SetPorgressInfo(LPCTSTR szInfo)
{
	
}

void CARTSearchDlg::AddFoundDevice(CDevice *pDevice)
{

}

void CARTSearchDlg::SetDialogStatus(BOOL bComplete)
{

}

CDevManager * CARTSearchDlg::GetDevManger()
{
	return NULL; 
}

