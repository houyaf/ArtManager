// ARTTaskView.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTTaskView.h"
#include "LABEL.H"
#include "ARTSearchIPMaskDlg.h"
#include "ARTSearchIPDlg.h"
#include "ARTSearchIPRange.h"

// CARTTaskView

IMPLEMENT_DYNCREATE(CARTTaskView, CFormView)

CARTTaskView::CARTTaskView()
	: CFormView(CARTTaskView::IDD)
{
	m_BkBrush.CreateSolidBrush(RGB(255,255,255));
}

CARTTaskView::~CARTTaskView()
{
}

void CARTTaskView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_FUNC, m_FuncLabel);
	DDX_Control(pDX, IDC_STATIC_ADD, m_AddLabel);
	DDX_Control(pDX, IDC_STATIC_SEARCH, m_SearchLabel);
	DDX_Control(pDX, IDC_STATIC_SEARCH_BY_IP, m_SearchIPLabel);
	DDX_Control(pDX, IDC_STATIC_SEARCH_BY_IPRANGE, m_Ctrl_Lable_IPRange);
	DDX_Control(pDX, IDC_STATIC_MONITOR_LABLE, m_Ctrl_Label_Monitor_Msg);
}

BEGIN_MESSAGE_MAP(CARTTaskView, CFormView)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_SEARCH, &CARTTaskView::OnStnClickedStaticSearch)
	ON_STN_CLICKED(IDC_STATIC_SEARCH_BY_IP, &CARTTaskView::OnStnClickedStaticSearchByIp)
	ON_STN_CLICKED(IDC_STATIC_SEARCH_BY_IPRANGE, &CARTTaskView::OnStnClickedStaticSearchByIprange)
END_MESSAGE_MAP()


// CARTTaskView 诊断

#ifdef _DEBUG
void CARTTaskView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTTaskView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

CARTDoc* CARTTaskView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}
// CARTTaskView 消息处理程序


void CARTTaskView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	int iFuncMode ;

	iFuncMode = GetDocument()->m_ulFunctionMode ;

	switch (iFuncMode)
	{
	case 0:
		m_FuncLabel.SetText("设备配置");
		ShowTaskView(iFuncMode);
		break;
	case 1:
        m_FuncLabel.SetText("设备监控");
		ShowTaskView(iFuncMode);
		break;
	case 2:
		m_FuncLabel.SetText("端口监控");
		ShowTaskView(iFuncMode);
		break;
	case 3:
		m_FuncLabel.SetText("端口映射");
		ShowTaskView(iFuncMode);
		break;
	default :
		break;

	}

	return ;
}
void CARTTaskView::ShowTaskView(int iView)
{
	m_AddLabel.ShowWindow(iView ==0 ?  SW_SHOW: SW_HIDE);
	m_SearchLabel.ShowWindow(iView ==0 ?  SW_SHOW: SW_HIDE);
	m_SearchIPLabel.ShowWindow(iView ==0 ?  SW_SHOW: SW_HIDE);
	m_Ctrl_Lable_IPRange.ShowWindow(iView ==0 ?  SW_SHOW: SW_HIDE);

	m_Ctrl_Label_Monitor_Msg.ShowWindow(iView ==1 ?  SW_SHOW: SW_HIDE);
}

int CARTTaskView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;



		
	return 0;
}


void CARTTaskView::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();
	
	// TODO: 在此添加专用代码和/或调用基类
	m_FuncLabel.SetTextColor(RGB(0,64,128));
	m_FuncLabel.SetFontBold(TRUE);
	m_FuncLabel.SetFontSize(20);

	m_AddLabel.SetFontSize(14);
	m_AddLabel.SetTextColor(RGB(0,64,128));

	m_SearchIPLabel.SetLink(TRUE);
	m_SearchIPLabel.SetTextColor(RGB(0,0,255));
	m_SearchIPLabel.SetFontUnderline(TRUE);
	m_SearchIPLabel.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND_CUR));

	m_SearchLabel.SetLink(TRUE);
	m_SearchLabel.SetTextColor(RGB(0,0,255));
	m_SearchLabel.SetFontUnderline(TRUE);
	m_SearchLabel.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND_CUR));

	
	m_Ctrl_Lable_IPRange.SetLink(TRUE);
	m_Ctrl_Lable_IPRange.SetTextColor(RGB(0,0,255));
	m_Ctrl_Lable_IPRange.SetFontUnderline(TRUE);
	m_Ctrl_Lable_IPRange.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND_CUR));

	
    m_Ctrl_Label_Monitor_Msg.SetTextColor(RGB(0,0,255));


}


HBRUSH CARTTaskView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return m_BkBrush;
}


void CARTTaskView::OnStnClickedStaticSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CARTSearchIPMaskDlg SearchDlg ;

	if (SearchDlg.DoModal() == IDOK)
	{
		
	}

}


void CARTTaskView::OnStnClickedStaticSearchByIp()
{
	// TODO: 在此添加控件通知处理程序代码

	CARTSearchIPDlg SearchIPDlg;

	if (SearchIPDlg.DoModal()== IDOK)
	{
		
	}
}


void CARTTaskView::OnStnClickedStaticSearchByIprange()
{
	// TODO: 在此添加控件通知处理程序代码
	CARTSearchIPRange SearchIPRangeDlg;

	if (SearchIPRangeDlg.DoModal() == IDOK)
	{

	}
}
