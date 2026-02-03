#include "PlaneStatus.h"
#include "./ResObjMgt.h"
#include "./global.h"

CPlaneStatus::CPlaneStatus(void)
:m_pPlaneTex(NULL)
,m_pVB(NULL)
,m_bAlpha(false)
,m_fAniFrameTime(0.0f)
{
	D3DXMatrixIdentity(&this->m_mat);
}

CPlaneStatus::~CPlaneStatus(void)
{
	this->m_pPlaneTex->pTexture->Release();
	this->m_pVB->Release();
}

bool CPlaneStatus::SetPlaneTexture(LPCTSTR filename)
{
	//if(!this->SetVertexBuffer())
	//{
	//	return false;
	//}

	this->m_pPlaneTex = CResObjMgt::CreateResMgt().SetTextureRes(filename);

	if(!this->m_pPlaneTex)
	{
		return false;
	}

	return true;
}

bool CPlaneStatus::SetVertexBuffer(int nFaceCount)
{
	if(FAILED(g_pD3device->CreateVertexBuffer(
		nFaceCount * 3 * sizeof(ST_PLANE), 
		0, 
		ST_PLANE::FVF, 
		D3DPOOL_MANAGED, 
		&this->m_pVB, 
		NULL)))
	{
		return false;
	}

	return true;
}

bool CPlaneStatus::SetIndexBuffer(int nFaceCount)
{
	return true;
}