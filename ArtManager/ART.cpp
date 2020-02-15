/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ART.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: ART.cpp : 定义应用程序的类行为
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ART.h"
#include "MainFrm.h"

#include "ARTDoc.h"
#include "ARTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CARTApp

BEGIN_MESSAGE_MAP(CARTApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CARTApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CARTApp 构造

CARTApp::CARTApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ART.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CARTApp 对象

CARTApp theApp;


// CARTApp 初始化

BOOL CARTApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if(!SysInit())
	{
		return FALSE;
	}

	// 初始化 OLE 库
	//if (!AfxOleInit())
	//{
	//	AfxMessageBox(IDP_OLE_INIT_FAILED);
	//	return FALSE;
	//}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CARTDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CARTView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CARTApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	//AfxOleTerm(FALSE);
	SysUnInit();
	CMFCVisualManager::DestroyInstance( TRUE );
	return CWinApp::ExitInstance();
}

bool CARTApp::SysInit()
{
	//WinSock初始化

	WORD    wVersionRequested;
	WSADATA wsaData;
	int iLastError ;

	wVersionRequested = MAKEWORD( 2, 2 );


	int nErr = 0;
	iLastError = 0;

	if ((nErr = WSAStartup(wVersionRequested, &wsaData)) != 0)
	{
		iLastError = WSAGetLastError();
		return false;
	}


	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) 
	{
		WSACleanup();
		return false;
	}


	return true;
}

void CARTApp::SysUnInit()
{
	WSACleanup();
}

// CARTApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CARTApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CARTApp 消息处理程序





BOOL CAboutDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::PreCreateWindow(cs);
}


int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

		return 0;
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();




	return TRUE;  // return TRUE unless you set the focus to a control

}


BOOL CAboutDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialog::DestroyWindow();
}
