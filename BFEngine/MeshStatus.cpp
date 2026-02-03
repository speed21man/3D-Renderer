#include "MeshStatus.h"
#include "./global.h"

CMeshStatus::CMeshStatus(void)
:m_pVB(NULL),
m_pIB(NULL),
m_dwFVF(0),
m_stMeshSize(0)
{
}

CMeshStatus::~CMeshStatus(void)
{
	this->m_pVB->Release();
	this->m_pIB->Release();
}

bool CMeshStatus::SetVertexBuffer(ENUM_STAT_FVF nFVF, int nVertexCount)
{
	this->SetMeshFVF(nFVF);

	if(FAILED(g_pD3device->CreateVertexBuffer(
		nVertexCount * 3 * this->m_stMeshSize, 
		0, 
		this->m_dwFVF, 
		D3DPOOL_MANAGED, 
		&this->m_pVB, 
		NULL)))
	{
		return false;
	}

	return true;
}

bool CMeshStatus::SetMeshFVF(ENUM_STAT_FVF nFVF)
{
	switch(nFVF)
	{
	case STATUS_FVF_PTCN:
		this->m_dwFVF =  D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
		this->m_stMeshSize = sizeof(ST_DX_PTCN_MESH);
		break;

	case STATUS_FVF_PTN:
		this->m_dwFVF =  D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
		this->m_stMeshSize = sizeof(ST_DX_PTN_MESH);
		break;

	case STATUS_FVF_PCN:
		this->m_dwFVF =  D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;
		this->m_stMeshSize = sizeof(ST_DX_PCN_MESH);
		break;

	case STATUS_FVF_PN:
		this->m_dwFVF =  D3DFVF_XYZ | D3DFVF_NORMAL;
		this->m_stMeshSize = sizeof(ST_DX_PN_MESH);
		break;
	}

	return true;
}

bool CMeshStatus::SetIndexBuffer(int nIndexCount)
{
	return true;
}


