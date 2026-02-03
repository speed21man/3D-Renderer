#pragma once

#include "./PlaneStatus.h"

class CDefaultPlane : public CPlaneStatus
{
public:
	D3DXMATRIX m_matPlane;

	LPCTSTR m_strTexFilename;

	D3DXMATRIX m_matRot;
	D3DXMATRIX m_matIdentity;
	D3DXQUATERNION m_quatRot;

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	CDefaultPlane(LPCTSTR filename);
	CDefaultPlane(void);
	~CDefaultPlane(void);
};
