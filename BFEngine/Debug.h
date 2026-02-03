#pragma once

#include "./std.h"
#include "./SkyMap.h"

class CDebug
{
public:
	CSkyMap m_Skymap;

public:
	D3DXVECTOR3 vPos1;
	D3DXVECTOR3 vPos2;
	D3DXVECTOR3 vPos3;
	D3DXVECTOR3 vPos4;

public:
	ID3DXFont *m_font;
	DWORD dwbefFrame;
	DWORD dwMillisec;
	float fFrameCount;
	int nFPS;
	char sFrame[255];

	BOOL InitFont(void);

public:
	ST_DEBUGLINE m_dLine[2];

public:
	BOOL DrawLine(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DCOLOR color = 0xffff0000);
	BOOL CheckFrame(void);

public:
	BOOL SetLine(D3DXVECTOR3 v0, D3DXVECTOR3 v1);

public:
	BOOL Init(void);
	BOOL Frame(void);
	BOOL Render(void);
	BOOL Release(void);

public:
	CDebug(void);
	~CDebug(void);
};
