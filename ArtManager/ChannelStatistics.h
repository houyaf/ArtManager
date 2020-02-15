#pragma once

// CChannelStatistics ÃüÁîÄ¿±ê

class CChannelStatistics : public CObject
{
public:
	CChannelStatistics();
	CChannelStatistics(unsigned char ucChannelNo);
	virtual ~CChannelStatistics();

private:

	unsigned char  m_ucChannelNO ;
	unsigned long  m_ulRemoteIP  ;
	unsigned short m_usRemotePort;

	unsigned long  m_ulSendNum ;
	unsigned long  m_ulSendSize;
	unsigned long  m_ulRecNum  ;
	unsigned long  m_ulRecSize ;

	unsigned long  m_ulLinkNum ;

public:
	unsigned char  Get_ChannelNO(){  return m_ucChannelNO ;}  ;
	unsigned long  Get_RemoteIP() {  return m_ulRemoteIP  ;}  ;
	unsigned short Get_RemotePort(){ return m_usRemotePort ;}  ;
	unsigned long  Get_SendNum(){    return m_ulSendNum ;}  ;
	unsigned long  Get_SendSize(){   return m_ulSendSize ;}  ;
	unsigned long  Get_RecNum(){     return m_ulRecNum ;}  ;
	unsigned long  Get_RecSize(){    return m_ulRecSize ;}  ;
	unsigned long  Get_LinkNum(){    return m_ulLinkNum ;}  ;

	void    Set_ChannelNO(unsigned char ucChannelNo){  m_ucChannelNO= ucChannelNo ;}  ;
	void    Set_RemoteIP(unsigned long ulRemoteIP) {  m_ulRemoteIP = ulRemoteIP  ;}  ;
	void    Set_RemotePort(unsigned short usRemotePort){  m_usRemotePort = usRemotePort ;}  ;
	void    Set_SendNum(unsigned long  ulSendNum){     m_ulSendNum  = ulSendNum ;}  ;
	void    Set_SendSize(unsigned long ulSendSize){    m_ulSendSize = ulSendSize ;}  ;
	void    Set_RecNum(unsigned long   ulRecNum){      m_ulRecNum = ulRecNum ;}  ;
	void    Set_RecSize(unsigned long  ulRecSize){     m_ulRecSize = ulRecSize;}  ;
	void    Set_LinkNum(unsigned long ulLinkNum){     m_ulLinkNum = ulLinkNum;}  ;
};


