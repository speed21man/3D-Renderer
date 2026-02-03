#include "PlaneOrthoAnimation.h"
#include "./global.h"

#define DEFBITMAP "../Resource/FX_Danger.tga"


CPlaneOrthoAnimation::CPlaneOrthoAnimation(void)
:m_nAniFrame(0)
,m_nAniTWidthCount(0)
,m_nAniTHeightCount(0)
,m_fAniTWidth(0.0f)
,m_fAniTHeight(0.0f)
{
	D3DXQuaternionIdentity(&m_quatRot);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matIdentity);
	D3DXMatrixIdentity(&m_matSrcWorld);

	m_strTexFilename = DEFBITMAP;

	this->m_fAniTWidth = 1.0f / 4;
	this->m_fAniTHeight = 1.0f / 4;

	this->m_nAniTWidthCount = 4;
	this->m_nAniTHeightCount = 4;

	m_fAniFrameTime = 16.0f;

}

CPlaneOrthoAnimation::~CPlaneOrthoAnimation(void)
{
}

CPlaneOrthoAnimation::CPlaneOrthoAnimation(LPCTSTR filename, int nTotalFrame, int nWidthNum, int nHeightNum)
:m_nAniFrame(0)
,m_nAniTWidthCount(0)
,m_nAniTHeightCount(0)
,m_fAniTWidth(0.0f)
,m_fAniTHeight(0.0f)
{
	D3DXQuaternionIdentity(&m_quatRot);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matIdentity);
	D3DXMatrixIdentity(&m_matSrcWorld);

	//m_fAniFrameTime = nTotalFrame;
	m_nAniFrame = nTotalFrame;

	//int nHeightNum = 0;

	//nHeightNum = this->m_fAniFrameTime / nWidthNum;

	this->m_fAniTWidth = 1.0f / (float)nWidthNum;
	this->m_fAniTHeight = 1.0f / (float)nHeightNum;

	this->m_nAniTWidthCount = nWidthNum;
	this->m_nAniTHeightCount = nHeightNum;

	m_strTexFilename = filename;
}

bool CPlaneOrthoAnimation::Init(void)
{
	this->SetVertexBuffer(2);
	this->SetPlaneTexture(m_strTexFilename);

	float fWidth = m_pPlaneTex->ddsd.Width / ((2.0f) * m_nAniTWidthCount);
	float fHeight = m_pPlaneTex->ddsd.Height / ((2.0f) * m_nAniTHeightCount);

	//m_fAniTLength = 1.0f / (float)nAniFrame;

	this->m_fGapWidth = ((0.5f)/ (fWidth * 2));
	this->m_fGapHeight = ((0.5f)/ (fHeight * 2));

	D3DXVECTOR3 vp(-fWidth, fHeight, 0.0f);
	D3DXVECTOR2 vt(0.0f + m_fGapWidth, 0.0f + m_fGapHeight);
	m_Animation[0].vp = vp;
	m_Animation[0].vt = vt;

	D3DXVECTOR3 vp1(fWidth, fHeight, 0.0f);
	D3DXVECTOR2 vt1(m_fAniTWidth + m_fGapWidth, 0.0f + m_fGapHeight);
	m_Animation[1].vp = vp1;
	m_Animation[1].vt = vt1;
	m_Animation[4].vp = vp1;
	m_Animation[4].vt = vt1;

	D3DXVECTOR3 vp2(-fWidth, -fHeight, 0.0f);
	D3DXVECTOR2 vt2(0.0f + m_fGapWidth, m_fAniTHeight + m_fGapHeight);
	m_Animation[2].vp = vp2;
	m_Animation[2].vt = vt2;
	m_Animation[3].vp = vp2;
	m_Animation[3].vt = vt2;

	D3DXVECTOR3 vp3(fWidth, -fHeight, 0.0f);
	D3DXVECTOR2 vt3(m_fAniTWidth + m_fGapWidth, m_fAniTHeight + m_fGapHeight);
	m_Animation[5].vp = vp3;
	m_Animation[5].vt = vt3;

	for(int i = 0; i < 6; i++)
	{
		m_Animation[i].vc = 0xffffffff;
	}

	return true;
}

bool CPlaneOrthoAnimation::Frame(void)
{
	//m_fAniFrameTime += this->m_fAniFrameRate * 0.001f;
	//if(m_fAniEndFrame <= (int)m_fAniFrameTime) m_fAniFrameTime = m_fAniBeginFrame;

	int nHeightFrame = (int)m_fAniFrameTime / m_nAniTWidthCount;
	int nWidthFrame = (int)m_fAniFrameTime % m_nAniTWidthCount;

	//D3DXVECTOR2 vt3(m_fAniTWidth, 1.0f);

	for(int i = 0; i < 6; i++)
		memset(&m_Animation[0].vt, 0 ,sizeof(D3DXVECTOR2));

	m_Animation[0].vt.x = m_fAniTWidth * nWidthFrame + this->m_fGapWidth;
	m_Animation[0].vt.y = m_fAniTHeight * nHeightFrame + this->m_fGapHeight;
	m_Animation[1].vt.x = m_Animation[4].vt.x = m_fAniTWidth * (nWidthFrame + 1) + this->m_fGapWidth;
	m_Animation[1].vt.y = m_Animation[4].vt.y = m_fAniTHeight * nHeightFrame + this->m_fGapHeight;
	m_Animation[2].vt.x = m_Animation[3].vt.x = m_fAniTWidth * nWidthFrame + this->m_fGapWidth;
	m_Animation[2].vt.y = m_Animation[3].vt.y = m_fAniTHeight * (nHeightFrame + 1) + this->m_fGapHeight;
	m_Animation[5].vt.x = m_fAniTWidth * (nWidthFrame + 1) + this->m_fGapWidth;
	m_Animation[5].vt.y = m_fAniTHeight * (nHeightFrame + 1) + this->m_fGapHeight;

	ST_PLANE *pAnimation;
	if(this->m_pVB->Lock(0, 0, (void**)&pAnimation, 0))
	{
		return false;
	}

	memcpy(pAnimation, &m_Animation, sizeof(m_Animation));
	
	this->m_pVB->Unlock();

	return true;
}

bool CPlaneOrthoAnimation::Render(void)
{
	//D3DXMatrixIdentity(&m_matSrcWorld);

	D3DXMatrixOrthoOffCenterLH(&this->m_matOrtho, 0.0f, 1024.0f, -768.0f, 0.0f, -100.0f, 100.0f);

	g_pD3device->GetTransform(D3DTS_PROJECTION, &this->m_matProject);
	g_pD3device->GetTransform(D3DTS_VIEW, &this->m_matView);

	g_pD3device->SetTexture(0, this->m_pPlaneTex->pTexture);
	g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_PLANE));

	//g_pD3device->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pD3device->SetRenderState(D3DRS_ALPHABLENDENABLE, this->m_bAlpha);
	g_pD3device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_pD3device->SetFVF(ST_PLANE::FVF);

	g_pD3device->SetTransform(D3DTS_WORLD, &this->m_mat);
	g_pD3device->SetTransform(D3DTS_VIEW, &m_matIdentity);
	
	g_pD3device->SetTransform(D3DTS_PROJECTION, &this->m_matOrtho);
	
	g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	g_pD3device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	g_pD3device->SetTransform(D3DTS_WORLD,  &this->m_matIdentity);
	g_pD3device->SetTransform(D3DTS_VIEW,  &this->m_matView);
	g_pD3device->SetTransform(D3DTS_PROJECTION,  &this->m_matProject);
	//g_pD3device->SetRenderState(D3DRS_ZENABLE, TRUE);

	return true;
}

bool CPlaneOrthoAnimation::Release(void)
{
	return true;
}