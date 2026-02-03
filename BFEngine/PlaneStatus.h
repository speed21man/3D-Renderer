#pragma once

#include "./std.h"

class CPlaneStatus
{
protected:
	D3DXMATRIX m_mat;
	ST_TEXTURE *m_pPlaneTex;

	bool m_bAlpha;
	//float m_fAniFrameRate;

	float m_fAniFrameTime;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB; 

//인라인 함수들
public:
	D3DXMATRIX& GetPlaneMatrix(void)			{	return this->m_mat;		}
	bool SetAlphaBlend(bool bAlpha)				{	m_bAlpha = bAlpha;	return true;	}
	bool SetPlaneMatrix(D3DXMATRIX &matPlane)	{	m_mat = matPlane;	return true;	}
	bool SetAniFrame(float fAniFrameTime)		{	m_fAniFrameTime = fAniFrameTime; return true; }

public:
	bool SetPlaneTexture(LPCTSTR filename);
	bool SetVertexBuffer(int nFaceCount);
	bool SetIndexBuffer(int nFaceCount);

public:
	virtual bool Init(void) = 0;
	virtual bool Frame(void) = 0;
	virtual bool Render(void) = 0;
	virtual bool Release(void) = 0;

public:
	CPlaneStatus(void);
	~CPlaneStatus(void);
};
