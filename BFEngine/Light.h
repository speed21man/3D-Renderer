#pragma once

#include "./std.h"

class CLight
{
public:
	D3DMATERIAL9 m_Mtrl;
	D3DLIGHT9 m_Light;

	D3DXVECTOR3 m_vecLight;

public:
	bool Init(void);
	bool Frame(void);
	bool Render(void);
	bool Release(void);

public:
	bool SetLight(bool bLight);

public:
	CLight(void);
	~CLight(void);
};
