#pragma once

#include "std.h"
#include "Input.h"

class CCamera
{
private:
	bool FrustumBoundingBox(void);

protected:
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matPerspect;
	D3DXVECTOR3 m_vt3CameraPos;

	D3DXVECTOR3 m_vecUp;
	D3DXVECTOR3 m_vecRight;
	D3DXVECTOR3 m_vecLook;

	bool bFrustumRect;

	float m_fNear;
	float m_fFar;

#if defined(DEBUG) || defined(_DEBUG)

	WORD m_Index[36];
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	D3DXVECTOR3 vt3Render;
	D3DMATERIAL9 mtrl;
	D3DXMATRIX m_matInvPers;
	ST_DEBUGCAMERA m_stDebugCamera[8];

#endif

protected:
	virtual bool ChildInit(void) = 0;
	virtual bool ChildFrame(void) = 0;
	virtual bool ChildRender(void) = 0;
	virtual bool ChildRelease(void) = 0;

public:
	bool Init(void);
	bool Frame(void);
	bool Render(void);
	bool Release(void);

	bool SetCameraPos(float fPosX, int fPosY, int fPosZ);

	virtual bool ControlCamera(CInput &InputDevice) = 0;

public:
	CCamera(void);
	~CCamera(void);
};
