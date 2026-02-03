#include "DebugCamera.h"
#include "./global.h"


CDebugCamera::CDebugCamera(void)
:m_fXRot(0.0f)
,m_fYRot(0.0f)
,m_TotalfXRot(0.0f)
,m_TotalfYRot(0.0f)
,bMouseBtn(false)
{
	memset(&this->m_LastMousePoint, 0, sizeof(POINT));
	memset(&this->m_MousePoint, 0, sizeof(POINT));

	//memset(&this->m_matEye, 0, sizeof(D3DXVECTOR3));
	//memset(&this->m_matLook, 0, sizeof(D3DXVECTOR3));
	//memset(&this->m_matUp, 0, sizeof(D3DXVECTOR3));

	D3DXQuaternionIdentity(&this->m_QuatCamera);
	D3DXMatrixIdentity(&this->m_matRot);

	//this->m_vt3CameraPos.x = 0.0f;
	//this->m_vt3CameraPos.y = 0.0f;
	//this->m_vt3CameraPos.z = -10.0f;
}

CDebugCamera::~CDebugCamera(void)
{
}

bool CDebugCamera::ChildInit(void)
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

	//m_matPerspect._41 = (1024.0f / 2.0f);
	//m_matPerspect._42 = -(768.0f / 2.0f);

	g_pD3device->SetTransform(D3DTS_PROJECTION, &m_matPerspect);


	return true;
}

bool CDebugCamera::ChildFrame(void)
{
	//D3DXVec3Normalize(&this->m_vecLook, &this->m_vecLook);

	//this->m_vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//D3DXVec3Cross(&this->m_vecRight, &this->m_vecUp, &this->m_vecLook);
	//D3DXVec3Normalize(&this->m_vecRight, &this->m_vecRight);

	//D3DXVec3Cross(&this->m_vecUp, &this->m_vecLook, &this->m_vecRight);
	//D3DXVec3Normalize(&this->m_vecUp, &this->m_vecUp);

	//if(this->m_fXRot != 0.0f || this->m_fYRot != 0.0f)
		this->CameraRotate();

	this->SetCameraViewMartix();

	return true;
}

bool CDebugCamera::ChildRender(void)
{
	return true;
}

bool CDebugCamera::ChildRelease(void)
{
	return true;
}

bool CDebugCamera::ControlCamera(CInput &InputDevice)
{
	if(InputDevice.m_KeyState[DIK_W] & 0x80)
		this->CameraRotateWalkMove(0.1f);

	if(InputDevice.m_KeyState[DIK_S] & 0x80)
		this->CameraRotateWalkMove(-0.1f);

	if(InputDevice.m_KeyState[DIK_D] & 0x80)
		this->CameraRotateStrafeMove(0.1f);

	if(InputDevice.m_KeyState[DIK_A] & 0x80)
		this->CameraRotateStrafeMove(-0.1f);

	if(InputDevice.m_KeyState[DIK_Q] & 0x80)
		this->CameraRotateFlyMove(0.1f);

	if(InputDevice.m_KeyState[DIK_E] & 0x80)
		this->CameraRotateFlyMove(-0.1f);

	GetCursorPos(&this->m_MousePoint);

	if(InputDevice.m_MouseState.rgbButtons[1] & 0x80)
	{	
		m_fXRot = (float)(this->m_MousePoint.x - this->m_LastMousePoint.x); //* (360 * 0.001f);
		m_fYRot = (float)(this->m_MousePoint.y - this->m_LastMousePoint.y); //* (360 * 0.001f);

		this->m_MousePoint = this->m_LastMousePoint;

		bMouseBtn = true;
	}
	else
	{
		if(bMouseBtn)
		{
			m_TotalfXRot += m_fXRot;
			m_TotalfYRot += m_fYRot;

			m_fXRot = 0.0f;
			m_fYRot = 0.0f;

			bMouseBtn = false;
		}

		this->m_LastMousePoint = this->m_MousePoint;
	}

	return true;
}


bool CDebugCamera::CameraRotate(void)
{

	D3DXQuaternionIdentity(&this->m_QuatCamera);
	D3DXMatrixIdentity(&this->matCameraView);

	//float fXRot = (this->m_MousePoint.x - this->m_LastMousePoint.x); //* (360 * 0.001f);
	//float fYRot = (this->m_MousePoint.y - this->m_LastMousePoint.y); //* (360 * 0.001f);
	//

	/////////////////////////////////////////////////////////////////////////////////
	// 방법 1
	/////////////////////////////////////////////////////////////////////////////////


	D3DXQuaternionRotationYawPitchRoll(&this->m_QuatCamera, (m_TotalfXRot + m_fXRot) * (D3DX_PI / 180), (m_TotalfYRot + m_fYRot) * (D3DX_PI / 180), 0.0f);
	//D3DXMATRIX matCameraView;

	D3DXMatrixAffineTransformation( &this->matCameraView, 1.25f, NULL, &this->m_QuatCamera, &m_vt3CameraPos );
	D3DXMatrixInverse(&this->m_matView, NULL, &this->matCameraView);

	m_vecLook.x = m_matView._13;
	m_vecLook.y = m_matView._23;
	m_vecLook.z = m_matView._33;
	m_vecRight.x = m_matView._11;
	m_vecRight.y = m_matView._21;
	m_vecRight.z = m_matView._31;
	m_vecUp.x = m_matView._12;
	m_vecUp.y = m_matView._22;
	m_vecUp.z = m_matView._32;

	/////////////////////////////////////////////////////////////////////////////////
	// 방법 2
	/////////////////////////////////////////////////////////////////////////////////

	//D3DXQuaternionRotationAxis(&this->m_QuatCamera, &this->m_vecUp, m_fXRot * (D3DX_PI / 180));
	//D3DXMatrixTransformation( &this->m_matRot, NULL, NULL, NULL, NULL, &this->m_QuatCamera, NULL );
	//D3DXVec3TransformCoord(&this->m_vecRight, &this->m_vecRight, &this->m_matRot );
	//D3DXVec3TransformCoord(&this->m_vecLook, &this->m_vecLook, &this->m_matRot );

	//D3DXQuaternionRotationAxis(&this->m_QuatCamera, &this->m_vecRight, m_fYRot * (D3DX_PI / 180));
	//D3DXMatrixTransformation( &this->m_matRot, NULL, NULL, NULL, NULL, &this->m_QuatCamera, NULL );
	//D3DXVec3TransformCoord(&this->m_vecLook, &this->m_vecLook, &this->m_matRot );
	//D3DXVec3TransformCoord(&this->m_vecUp, &this->m_vecUp, &this->m_matRot );

	//m_fXRot = 0.0f;
	//m_fYRot = 0.0f;


	/////////////////////////////////////////////////////////////////////////////////


	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.06
// 기능 : 카메라 마우스 이동
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
bool CDebugCamera::CameraRotateWalkMove(float fMove)
{
	m_vt3CameraPos.x += (fMove * this->m_vecLook.x);
	m_vt3CameraPos.y += (fMove * this->m_vecLook.y);
	m_vt3CameraPos.z += (fMove * this->m_vecLook.z);

	//g_pD3device->SetTransform(D3DTS_WORLD, &m_matWorldPos);

	return TRUE;	
}

bool CDebugCamera::CameraRotateStrafeMove(float fMove)
{
	m_vt3CameraPos.x += (fMove * this->m_vecRight.x);
	m_vt3CameraPos.y += (fMove * this->m_vecRight.y);
	m_vt3CameraPos.z += (fMove * this->m_vecRight.z);

	//g_pD3device->SetTransform(D3DTS_WORLD, &m_matWorldPos);

	return TRUE;
}

bool CDebugCamera::CameraRotateFlyMove(float fMove)
{
	m_vt3CameraPos.x += (fMove * this->m_vecUp.x);
	m_vt3CameraPos.y += (fMove * this->m_vecUp.y);
	m_vt3CameraPos.z += (fMove * this->m_vecUp.z);

	//g_pD3device->SetTransform(D3DTS_WORLD, &m_matWorldPos);

	return TRUE;
}

bool CDebugCamera::SetCameraViewMartix(void)
{

	//m_matView._11 = this->m_vecRight.x;
 //   m_matView._21 = this->m_vecRight.y;
 //   m_matView._31 = this->m_vecRight.z;

	//m_matView._12 = this->m_vecUp.x;
 //   m_matView._22 = this->m_vecUp.y;
 //   m_matView._32 = this->m_vecUp.z;

	//m_matView._13 = this->m_vecLook.x;
 //   m_matView._23 = this->m_vecLook.y;
	//m_matView._33 = this->m_vecLook.z;

	//m_matView._41 = -D3DXVec3Dot(&this->m_vecRight , &m_vt3CameraPos);
	//m_matView._42 = -D3DXVec3Dot(&this->m_vecUp, &m_vt3CameraPos);
 //   m_matView._43 = -D3DXVec3Dot(&this->m_vecLook, &m_vt3CameraPos);

	g_pD3device->SetTransform(D3DTS_VIEW, &m_matView);

	return true;
}