/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTPortPage.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �������öԻ�����ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once
#include "LABEL.H"
#include "afxcmn.h"

class CARTDoc;
// CARTPortPage �Ի���

class CARTPortPage : public CDialog
{
	DECLARE_DYNAMIC(CARTPortPage)

public:
	CARTPortPage(CWnd* pParent = NULL);   // ��׼���캯��
	CARTPortPage(CWnd* pParent, DWORD dwDevIP);   // ��չ���캯��
	virtual ~CARTPortPage();

// �Ի�������
	enum { IDD = IDD_DLG_PORT_PAGE };

public:
	CARTDoc *GetDocument();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Ctrl_List_PortPara;
	CListCtrl m_Ctrl_List_PortMode;
	void SetListCtrlSelectedState(CListCtrl& ListCtrl, int iRow, UINT ulState, UINT ulMask, UINT iCtrlIndex);

	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPortMode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPortpara();
	afx_msg void OnBnClickedBtnPortmode();
	afx_msg void OnNMClickListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPortMode(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT SetCtrlInitValue(WPARAM wParam, LPARAM lParam);

	CString m_szPortSelectedofPortPara;
	CString m_szPortSelectedofPortMode;
	DWORD   m_dwDevIPSelected ;
	afx_msg void OnBnClickedBtnConfigAllport();
	afx_msg void OnDblclkListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListPortWorkMode(NMHDR *pNMHDR, LRESULT *pResult);
};
