#pragma once

#include "./PlaneStatus.h"

class CPlaneBillBoard : public CPlaneStatus
{
private:
	ST_PLANE m_pBillboard[6];

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
	CPlaneBillBoard(LPCSTR filename);
	CPlaneBillBoard(void);
	~CPlaneBillBoard(void);
};
