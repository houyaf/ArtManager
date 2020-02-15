
// ART.h : ART 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CARTApp:
// 有关此类的实现，请参阅 ART.cpp
//

class CARTApp : public CWinApp
{
public:
	CARTApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
    bool SysInit();
	void SysUnInit();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CARTApp theApp;
