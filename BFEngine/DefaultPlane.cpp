#include "DefaultPlane.h"

CDefaultPlane::CDefaultPlane(void)
{
	D3DXQuaternionIdentity(&m_quatRot);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matIdentity);

	m_strTexFilename = DEFBITMAP;
}

CDefaultPlane::~CDefaultPlane(void)
{
}

CDefaultPlane::CDefaultPlane(LPCTSTR filename)
{
	
}

bool CDefaultPlane::Init(void)
{
	this->SetVertexBuffer(2);
	this->SetPlaneTexture(m_strTexFilename);

	float fWidth = m_pPlaneTex->ddsd.Width / (2.0f * 100.0f);
	float fHeight = m_pPlaneTex->ddsd.Height / (2.0f * 100.0f);

	D3DXVECTOR3 vp(-fWidth, fHeight, 0.0f);
	D3DXVECTOR2 vt(0.0f, 0.0f);
	m_pBillboard[0].vp = vp;
	m_pBillboard[0].vt = vt;

	D3DXVECTOR3 vp1(fWidth, fHeight, 0.0f);
	D3DXVECTOR2 vt1(1.0f, 0.0f);
	m_pBillboard[1].vp = vp1;
	m_pBillboard[1].vt = vt1;
	m_pBillboard[4].vp = vp1;
	m_pBillboard[4].vt = vt1;

	D3DXVECTOR3 vp2(-fWidth, -fHeight, 0.0f);
	D3DXVECTOR2 vt2(0.0f, 1.0f);
	m_pBillboard[2].vp = vp2;
	m_pBillboard[2].vt = vt2;
	m_pBillboard[3].vp = vp2;
	m_pBillboard[3].vt = vt2;

	D3DXVECTOR3 vp3(fWidth, -fHeight, 0.0f);
	D3DXVECTOR2 vt3(1.0f, 1.0f);
	m_pBillboard[5].vp = vp3;
	m_pBillboard[5].vt = vt3;

	for(int i = 0; i < 6; i++)
	{
		m_pBillboard[i].vc = 0xffffffff;
	}
	return true;
}

bool CDefaultPlane::Frame(void)
{
	return true;
}

bool CDefaultPlane::Render(void)
{
	return true;
}

bool CDefaultPlane::Release(void)
{
	return true;
}