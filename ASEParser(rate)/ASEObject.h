#pragma once

#include "./AseParser.h"

class ASEObject : public ASEParser
{
public:
	//D3DMATERIAL9 m_mtrl;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	bool Init(void);
	bool Frame(void);
	bool Render(void);
	bool Release(void);

	bool CreateMesh(char* filename);

public:
	ASEObject(void);
	~ASEObject(void);
};
