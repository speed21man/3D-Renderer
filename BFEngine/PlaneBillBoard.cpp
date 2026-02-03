#include "./PlaneBillBoard.h"
#include "./global.h"

#define DEFBITMAP "../Resource/d3dLogo.bmp"

CPlaneBillBoard::CPlaneBillBoard(void)
{
	D3DXQuaternionIdentity(&m_quatRot);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matIdentity);

	m_strTexFilename = DEFBITMAP;
}

CPlaneBillBoard::~CPlaneBillBoard(void)
{

}

CPlaneBillBoard::CPlaneBillBoard(LPCSTR filename)
{
	D3DXQuaternionIdentity(&m_quatRot);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matIdentity);

	m_strTexFilename = filename;
}

bool CPlaneBillBoard::Init(void)
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

bool CPlaneBillBoard::Frame(void)
{

	// 과거 빌보드 연산
	//this->m_mat = invmat;

	ST_PLANE *pBillBoard;
	if(this->m_pVB->Lock(0, 0, (void**)&pBillBoard, 0))
	{
		return false;
	}

	memcpy(pBillBoard, &this->m_pBillboard, sizeof(this->m_pBillboard));

	this->m_pVB->Unlock();

	return true;
}

bool CPlaneBillBoard::Render(void)
{
	g_pD3device->SetTransform(D3DTS_WORLD, &this->m_mat);

	g_pD3device->SetTexture(0, this->m_pPlaneTex->pTexture);
	g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_PLANE));
	g_pD3device->SetRenderState(D3DRS_ALPHABLENDENABLE, this->m_bAlpha);
	g_pD3device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3device->SetFVF(ST_PLANE::FVF);

	g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	g_pD3device->SetTransform(D3DTS_WORLD,  &this->m_matIdentity);
	g_pD3device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return true;
}

bool CPlaneBillBoard::Release(void)
{
	return true;
}
