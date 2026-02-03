#pragma once

#include "./camera.h"

class CDebugCamera : public CCamera
{
private:
	POINT m_LastMousePoint;
	POINT m_MousePoint;

	D3DXQUATERNION m_QuatCamera;

	D3DXMATRIX m_matRot;
	//D3DXMATRIX m_matWorldPos;

	//D3DXVECTOR3 m_vecWorldPos;

	D3DXMATRIX matCameraView;


	bool bMouseBtn;
	//D3DXMATRIX matInvCameraView;

	float m_fXRot, m_fYRot, m_TotalfXRot, m_TotalfYRot;

	bool SetCameraViewMartix(void);

protected:
	virtual bool ChildInit(void);
	virtual bool ChildFrame(void);
	virtual bool ChildRender(void);
	virtual bool ChildRelease(void);

public:
	virtual bool ControlCamera(CInput &InputDevice);

	bool CameraRotate(void);
	bool CameraRotateWalkMove(float fMove);
	bool CameraRotateStrafeMove(float fMove);
	bool CameraRotateFlyMove(float fMove);

public:
	CDebugCamera(void);
	~CDebugCamera(void);
};
