/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����CARTUIThread.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ART UI Task��������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once

// CARTUIThread
class CARTUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CARTUIThread)

protected:
	CARTUIThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CARTUIThread();

public:
	CWnd* m_pOwner;
	BOOL  m_bDone;
	void SetOwner(CWnd* pOwner) { m_pOwner = pOwner; };
};


