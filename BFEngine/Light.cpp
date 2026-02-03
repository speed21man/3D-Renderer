#include "Light.h"

#include "./global.h"

CLight::CLight(void)
{
	memset(&this->m_Light, 0, sizeof(this->m_Light));
	memset(&this->m_Mtrl, 0, sizeof(this->m_Mtrl));
	memset(&this->m_vecLight, 0, sizeof(this->m_vecLight));

}

CLight::~CLight(void)
{
}

bool CLight::Init(void)
{
	this->m_vecLight = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	return true;
}

bool CLight::Frame(void)
{
	//memset(&this->m_Mtrl, 0, sizeof(this->m_Mtrl));	

	//m_Mtrl.Diffuse.r = 1.0f;
	//m_Mtrl.Diffuse.g = 1.0f;
	//m_Mtrl.Diffuse.b = 0.0f;
	//m_Mtrl.Diffuse.a = 1.0f;

	memset(&this->m_Light, 0, sizeof(this->m_Light));

	this->m_Light.Type = D3DLIGHT_DIRECTIONAL;

	this->m_Light.Range = 1000.0f;

	this->m_Light.Diffuse.a = 1.0f;
	this->m_Light.Diffuse.r = 1.0f;
	this->m_Light.Diffuse.g = 1.0f;
	this->m_Light.Diffuse.b = 1.0f;

	this->m_vecLight = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), -1.0f, sinf(timeGetTime() / 350.0f));
	D3DXVec3Normalize((D3DXVECTOR3 *)&this->m_Light.Direction, &this->m_vecLight);

	return true;
}

bool CLight::Render(void)
{
	g_pD3device->SetLight(0, &this->m_Light);
	g_pD3device->LightEnable(0, TRUE);
	//g_pD3device->SetMaterial(&this->m_Mtrl);

	g_pD3device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3device->SetRenderState(D3DRS_LIGHTING, TRUE);

	g_pD3device->SetRenderState(D3DRS_AMBIENT, 0x00202020);

	return true;
}

bool CLight::Release(void)
{
	return true;
}

bool CLight::SetLight(bool bLight)
{
	

	return true;
}