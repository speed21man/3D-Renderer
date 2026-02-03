#pragma once

#include "./camera.h"

class CStaticCamera : public CCamera
{
private:
	D3DXQUATERNION m_QuatCamera;
	D3DXMATRIX matCameraView;

	D3DXVECTOR3 m_vecEye;
	D3DXVECTOR3 m_vecLookat;

	D3DXVECTOR3 m_vecUp;
	D3DXVECTOR3 m_vecRight;
	D3DXVECTOR3 m_vecLook;

	//D3DXVECTOR3 m_vt3CameraPos;

protected:
	virtual bool ChildInit(void);
	virtual bool ChildFrame(void);
	virtual bool ChildRender(void);
	virtual bool ChildRelease(void);

public:
	virtual bool ControlCamera(CInput &InputDevice);

public:
	CStaticCamera(void);
	~CStaticCamera(void);
};
