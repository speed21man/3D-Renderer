#include ".\camera.h"
#include "./global.h"

#define DEBUGCOLOR 0xffffff00

CCamera::CCamera(void)
:m_fNear(1.0f)
,m_fFar(1000.0f)
,m_vt3CameraPos(0.0f, 0.0f, -10.0f)
,m_vecUp(0.0f, 1.0f, 0.0f)
,m_vecRight(1.0f, 0.0f, 0.0f)
,m_vecLook(0.0f, 0.0f, 1.0f)
,bFrustumRect(false)
{
	D3DXMatrixIdentity(&this->m_matView);
	D3DXMatrixIdentity(&this->m_matPerspect);


#if defined(DEBUG) || defined(_DEBUG)

	D3DXMatrixIdentity(&this->m_matInvPers);

	WORD	index[] = { 0, 1, 2,
						0, 2, 3,
						4, 7, 6,
						4, 6, 5,
						1, 5, 6,
						1, 6, 2,
						0, 3, 7,
						0, 7, 4,
						0, 4, 5,
						0, 5, 1,
						3, 7, 6,
						3, 6, 2 };


	memcpy(&m_Index, &index, sizeof(m_Index));

#endif
}

CCamera::~CCamera(void)
{
}

bool CCamera::Init(void)
{
	//if(FAILED(g_pD3device->CreateVertexBuffer(
	//	12 * 3 * sizeof(ST_DEBUGCAMERA), 
	//	0, 
	//	ST_DEBUGCAMERA::FVF, 
	//	D3DPOOL_MANAGED, 
	//	&this->m_pVB, 
	//	NULL)))
	//{
	//	return false;
	//}

	this->ChildInit();
	return true;
}

bool CCamera::Frame(void)
{
	//ST_DEBUGCAMERA *st_debug;

	//m_matView._41 = -D3DXVec3Dot(&this->m_vecRight, &m_vt3CameraPos);
	//m_matView._42 = -D3DXVec3Dot(&this->m_vecUp,	&m_vt3CameraPos);
 //   m_matView._43 = -D3DXVec3Dot(&this->m_vecLook,	&m_vt3CameraPos);

	//vt3Render.x = m_matView._41;
	//vt3Render.y = m_matView._42;
	//vt3Render.z = m_matView._43;

	//if(this->m_pVB->Lock(0, 0, (void**)&st_debug, 0))
	//{
	//	return false;
	//}

	//st_debug

	//this->m_pVB->Unlock();

	this->FrustumBoundingBox();

	this->ChildFrame();
	return true;
}

bool CCamera::Render(void)
{
	//g_pD3device->SetRenderState(D3DRS_AMBIENT, 0x44ffffff);

#if defined(DEBUG) || defined(_DEBUG)

	if(!bFrustumRect)
		return true;

	g_pD3device->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DISABLE );
	g_pD3device->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE );

	g_pD3device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
	g_pD3device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

	//g_pD3device->SetFVF(ST_DEBUGCAMERA::FVF);
	//g_pD3device->SetStreamSource(0, NULL, 0 ,sizeof(ST_DEBUGCAMERA));

	g_pD3device->SetRenderState( D3DRS_LIGHTING, TRUE );
	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
    g_pD3device->SetMaterial( &mtrl );
	
	g_pD3device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 8, 4, m_Index , D3DFMT_INDEX16, m_stDebugCamera, sizeof( ST_DEBUGCAMERA )) ;

	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.b = mtrl.Ambient.g = 1.0f;
    g_pD3device->SetMaterial( &mtrl );

	g_pD3device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 8, 4, m_Index+4*3 , D3DFMT_INDEX16, m_stDebugCamera, sizeof( ST_DEBUGCAMERA )) ;

	ZeroMemory( &mtrl, sizeof(D3DMATERIAL9) );
    mtrl.Diffuse.b = mtrl.Ambient.r = 1.0f;
    g_pD3device->SetMaterial( &mtrl );

	g_pD3device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 0, 8, 4, m_Index+8*3 , D3DFMT_INDEX16, m_stDebugCamera, sizeof( ST_DEBUGCAMERA )) ;

	g_pD3device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE);

#endif
	//g_pD3device->SetRenderState( D3DRS_LIGHTING, FALSE );

	//g_pD3device->SetRenderState(D3DRS_AMBIENT, 0x00202020);

	this->ChildRender();
	return true;
}

bool CCamera::Release(void)
{
	//m_pVB->Release();

	this->ChildRelease();
	return true;
}

bool CCamera::FrustumBoundingBox(void)
{
	//D3DXMatrixIdentity(&this->m_matInvPers);
	//D3DXMatrixIdentity(&this->m_matPerspect);

#if defined(DEBUG) || defined(_DEBUG)
	D3DXMATRIX mattmp;
	//g_pD3device->GetTransform(D3DTS_PROJECTION, &this->m_matPerspect);

	mattmp = this->m_matView * this->m_matPerspect;

	D3DXMatrixInverse(&this->m_matInvPers, NULL, &mattmp);

	m_stDebugCamera[0].vp.x = -1.0f;	m_stDebugCamera[0].vp.y = -1.0f;	m_stDebugCamera[0].vp.z = 0.0f;		
	m_stDebugCamera[1].vp.x = 1.0f;		m_stDebugCamera[1].vp.y = -1.0f;	m_stDebugCamera[1].vp.z = 0.0f;	
	m_stDebugCamera[2].vp.x = 1.0f;		m_stDebugCamera[2].vp.y = -1.0f;	m_stDebugCamera[2].vp.z = 1.0f;	
	m_stDebugCamera[3].vp.x = -1.0f;	m_stDebugCamera[3].vp.y = -1.0f;	m_stDebugCamera[3].vp.z = 1.0f;	
	m_stDebugCamera[4].vp.x = -1.0f;	m_stDebugCamera[4].vp.y = 1.0f;		m_stDebugCamera[4].vp.z = 0.0f;	
	m_stDebugCamera[5].vp.x = 1.0f;		m_stDebugCamera[5].vp.y = 1.0f;		m_stDebugCamera[5].vp.z = 0.0f;	
	m_stDebugCamera[6].vp.x = 1.0f;		m_stDebugCamera[6].vp.y = 1.0f;		m_stDebugCamera[6].vp.z = 1.0f;	
	m_stDebugCamera[7].vp.x = -1.0f;	m_stDebugCamera[7].vp.y = 1.0f;		m_stDebugCamera[7].vp.z = 1.0f;	
	
	for(int i = 0; i < 8 ; i++)
		D3DXVec3TransformCoord( &m_stDebugCamera[i].vp, &m_stDebugCamera[i].vp, &this->m_matInvPers);
#endif

	return true;
}

bool CCamera::SetCameraPos(float fPosX, int fPosY, int fPosZ)
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3device->GetTransform(D3DTS_WORLD, &matWorld);

	matWorld._41 = fPosX;
	matWorld._42 = fPosY;
	matWorld._43 = fPosZ;

	g_pD3device->SetTransform(D3DTS_WORLD, &matWorld);


	return true;
}