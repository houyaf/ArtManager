/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTConfigDlg.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �豸���öԻ����� ����
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/


#pragma once
#include "afxcmn.h"

#include "EntabCtrl.h"


class CARTBasicPage;
class CARTPortPage;
class CARTDoc ;
// CARTConfigDlg �Ի���

class CARTConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CARTConfigDlg)

public:
	CARTConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CARTConfigDlg(CWnd* pParent, DWORD dwDevIP);   // ��׼���캯��
	virtual ~CARTConfigDlg();

// �Ի�������
	enum { IDD = IDD_DLG_CONFIG };

public:
	CARTDoc *GetDocument();

public:
	CARTBasicPage    *m_pDlgBasicPage;
	CARTPortPage     *m_pDlgPortPage;

	void ShowChild(int iChild);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	DECLARE_MESSAGE_MAP()

public:
	CEnTabCtrl  m_TabCtrl_Config;
	COLORREF    m_color;
	CImageList  m_ilTabs; 
public:
	DWORD    m_dwDevIPSelected ;
	
	CString  m_szDevMode;
	int      m_iDevPortNum;
	CString  m_szSWVersion;
	CString  m_szUpTime;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnReboot();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNcDestroy();
	afx_msg void OnBnClickedBtnDevSavedata();
};
