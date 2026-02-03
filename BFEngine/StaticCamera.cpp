#include "StaticCamera.h"
#include "./global.h"

CStaticCamera::CStaticCamera(void)
{
}

CStaticCamera::~CStaticCamera(void)
{
}

bool CStaticCamera::ChildInit(void)
{
	D3DXMATRIX matWorld, matView, matPerspect;
	D3DXMatrixIdentity(&matWorld);
	g_pD3device->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEye(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 vLook(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUP(0.0f, 1.0f, 0.0f);

	//memcpy(&this->m_vecEye, &vEye, sizeof(D3DXVECTOR3));
	//memcpy(&this->m_vecLookat, &vLook, sizeof(D3DXVECTOR3));
	//memcpy(&this->m_vecUp, &vUP, sizeof(D3DXVECTOR3));

	//this->m_vecLook = this->m_vecLookat - this->m_vecEye;
	
	D3DXMatrixLookAtLH(&matView, &vEye, &vLook, &vUP);

	g_pD3device->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&m_matPerspect, D3DX_PI/4, 1.33f, m_fNear, m_fFar);

	// ±ÍÂú¾Æ¼­ ÇÏµåÄÚµù -_-;;;
	//m_matPerspect._41 = (1024.0f / 2.0f);
	//m_matPerspect._42 = -(768.0f / 2.0f);

	g_pD3device->SetTransform(D3DTS_PROJECTION, &m_matPerspect);
	
	return true;
}

bool CStaticCamera::ChildFrame(void)
{
	//D3DXQuaternionIdentity(&this->m_QuatCamera);
	//D3DXMatrixIdentity(&m_matView);
	//D3DXQuaternionRotationYawPitchRoll(&this->m_QuatCamera, 0.0f, 0.0f, 0.0f);
	//D3DXMatrixAffineTransformation( &this->matCameraView, 1.25f, NULL, &this->m_QuatCamera, &m_vt3CameraPos );
	//D3DXMatrixInverse(&this->m_matView, NULL, &this->matCameraView);

	////m_matView._41 = -D3DXVec3Dot(&this->m_vecRight, &m_vt3CameraPos);
	////m_matView._42 = -D3DXVec3Dot(&this->m_vecUp,	&m_vt3CameraPos);
	////m_matView._43 = -D3DXVec3Dot(&this->m_vecLook,	&m_vt3CameraPos);

	//g_pD3device->SetTransform(D3DTS_VIEW, &m_matView);
	return true;
}

bool CStaticCamera::ChildRender(void)
{
	return true;
}

bool CStaticCamera::ChildRelease(void)
{
	return true;
}

bool CStaticCamera::ControlCamera(CInput &InputDevice)
{
	return true;
}