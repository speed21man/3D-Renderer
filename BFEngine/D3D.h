#pragma once

#include "./std.h"
#include <vector>

class D3D
{
public:
	LPDIRECT3D9 m_pD3d9;
	D3DCAPS9 m_pCaps;
	D3DPRESENT_PARAMETERS m_d3dpp;
	D3DDEVICE_CREATION_PARAMETERS m_d3dcrt;
	//D3DDISPLAYMODE *m_pDisMode;
	D3DFORMAT m_D3dFormat;
	//D3DDISPLAYMODE m_DisMode;
    
public:
	std::vector<D3DDISPLAYMODE *> vDisMode;

public:
	D3D(void);
	~D3D(void);

public:
	BOOL Init(void);
	BOOL Release(void);
	HRESULT CreateDevice9(void);
	HRESULT CreateDevice10(void);
	HRESULT SetupDevice9(void);
	HRESULT CheckDisplayMode(void);
	const D3DDISPLAYMODE PreDisplayMode(void);
	const D3DADAPTER_IDENTIFIER9 PreDisplayIdentifier(void);
};
