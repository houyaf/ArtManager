
// ART.h : ART Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CARTApp:
// �йش����ʵ�֣������ ART.cpp
//

class CARTApp : public CWinApp
{
public:
	CARTApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
    bool SysInit();
	void SysUnInit();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CARTApp theApp;
