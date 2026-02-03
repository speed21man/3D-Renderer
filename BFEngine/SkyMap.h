#pragma once

#include "./std.h"

class CSkyMap
{
public:
	float m_fSize;
	float m_fGap;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DTEXTURE9 m_pTexture[6];

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	bool SetSkyMapTexture(int Index, char* filepath);
	bool SetTextureUVPos(void);

public:
	CSkyMap(void);
	~CSkyMap(void);
};
