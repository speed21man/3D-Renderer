#pragma once

#include "./std.h"
#include "./ASEDefine.h"
#include <map>

class ASEMtrl
{
public:
	int m_nSubMaterialCount;

	D3DMATERIAL9 m_Mtrl;
	LPDIRECT3DTEXTURE9 m_pTexture;

	std::map<int ,ST_SubMaterial*> m_mpSubMaterial;

public:
	bool AddSubMaterial(int nIndex);
	ST_SubMaterial* FineSubMaterial(int nIndex);

	bool SetSubMaterialCount(int nCount);
public:
	bool Init(void);
	bool Release(void);

public:
	ASEMtrl(void);
	~ASEMtrl(void);
};
