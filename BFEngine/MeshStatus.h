#pragma once

#include "./std.h"

class CMeshStatus
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	DWORD m_dwFVF;
	size_t m_stMeshSize;

public:
	bool SetVertexBuffer(ENUM_STAT_FVF nFVF, int nVertexCount);
	bool SetMeshFVF(ENUM_STAT_FVF nFVF);
	bool SetIndexBuffer(int nIndexCount);
	//bool SetMeshTexture(LPCTSTR filename);

public:
	virtual bool Init(void) = 0;
	virtual bool Frame(void) = 0;
	virtual bool Render(void) = 0;
	virtual bool Release(void) = 0;

public:
	CMeshStatus(void);
	~CMeshStatus(void);
};
