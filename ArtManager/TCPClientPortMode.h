/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：TCPClientPortMode.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: TCPClient模式(TCP Client工作模式)类接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once
class CTCPClientPortMode :	public CPortChannel
{
public:
	CTCPClientPortMode(void);
	~CTCPClientPortMode(void);

protected:
	DWORD m_dwTargetHostIP1;
	int m_iTargetHostPort1;
	int m_iLocalPort1;

	DWORD m_dwTargetHostIP2;
	int m_iTargetHostPort2;
	int m_iLocalPort2;

	DWORD m_dwTargetHostIP3;
	int m_iTargetHostPort3;
	int m_iLocalPort3;

	DWORD m_dwTargetHostIP4;
	int m_iTargetHostPort4;
	int m_iLocalPort4;

	DWORD m_dwTargetHostIP5;
	int m_iTargetHostPort5;
	int m_iLocalPort5;

	DWORD m_dwTargetHostIP6;
	int m_iTargetHostPort6;
	int m_iLocalPort6;

public:
	void Set_TargetHost1(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost1(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost2(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost2(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost3(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost3(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost4(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost4(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost5(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost5(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

	void Set_TargetHost6(DWORD dwHostIP , int iHostPort, int iLocalPort);
	void Get_TargetHost6(DWORD &dwHostIP, int &iHostPort, int& iLocalPort);

};

