#pragma once
class NetScanEngine
{


public:
	bool Init();
	void Uninit();
    bool ScanHost(DWORD dwIP_S, DWORD dwIP_E);

};

