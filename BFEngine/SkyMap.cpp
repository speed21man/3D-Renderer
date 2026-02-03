#include "SkyMap.h"
#include "./global.h"
#include "./ResObjMgt.h"

struct ST_SKYMAP
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1) };

	D3DXVECTOR3 vp;
	DWORD vc;
	D3DXVECTOR2 vt;

};


float fSkyVecArray[24][3] = 
{
	//TOP
	{-1, 1, 1},
	{-1, 1, -1},
	{1, 1, 1},
	{1, 1, -1},

	//BOTTOM
	{-1, -1, -1},
	{-1, -1, 1},
	{1, -1, -1},
	{1, -1, 1},

	//RIGHT
	{1, 1, -1},
	{1, -1, -1},
	{1, 1, 1},
	{1, -1, 1},

	//LEFT
	{-1, 1, 1},
	{-1, -1, 1},
	{-1, 1, -1},
	{-1, -1, -1},

	//FRONT
	{1, 1, 1},
	{1, -1, 1},
	{-1, 1, 1},
	{-1, -1, 1},

	//BACK
	{-1, 1, -1},
	{-1, -1, -1},
	{1, 1, -1},
	{1, -1, -1}
};

float fSkyUVArray[24][2] = 
{
	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f},

	{0.0f, 0.0f},
	{0.0f, 1.0f},
	{1.0f, 0.0f},
	{1.0f, 1.0f}
};

CSkyMap::CSkyMap(void)
{
}

CSkyMap::~CSkyMap(void)
{
}

bool CSkyMap::Init(void)
{	
	this->m_fSize = 500.0f;
	this->m_fGap = 0.5f;

	if(FAILED(g_pD3device->CreateVertexBuffer(6 * 4 * sizeof(ST_SKYMAP), 
		0, ST_SKYMAP::FVF, D3DPOOL_DEFAULT, &this->m_pVB, NULL)))
	{
		return false;
	}

	return true;
}

bool CSkyMap::Frame(void)
{
	ST_SKYMAP *pSkymap;

	if(FAILED(this->m_pVB->Lock(0, 0, (void**)&pSkymap, 0)))
	{
		return false;
	}

	for(int i = 0 ; i < 24 ; i++)
	{
		float fPosX = m_fSize * fSkyVecArray[i][0];
		float fPosY = m_fSize * fSkyVecArray[i][1];
		float fPosZ = m_fSize * fSkyVecArray[i][2];

		float fPosU = fSkyUVArray[i][0];
		float fPosV = fSkyUVArray[i][1];

		pSkymap->vp = D3DXVECTOR3(fPosX, fPosY, fPosZ);
		pSkymap->vc = D3DXCOLOR(255, 255, 255, 255);
		pSkymap->vt = D3DXVECTOR2(fPosU, fPosV);

		pSkymap++;
	}

	this->m_pVB->Unlock();

	return true;
}

bool CSkyMap::Render(void)
{
	D3DXMATRIX matView;
	D3DXMatrixIdentity(&matView);
	g_pD3device->GetTransform(D3DTS_VIEW, &matView);

	g_pD3device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3device->SetStreamSource(0, m_pVB, 0, sizeof(ST_SKYMAP));
	g_pD3device->SetFVF(ST_SKYMAP::FVF);

	D3DXMATRIX tmpWorld, tmpView, tmpInv;

	D3DXMatrixIdentity(&tmpWorld);
	D3DXMatrixIdentity(&tmpView);
	D3DXMatrixIdentity(&tmpInv);

	tmpView = matView;

	tmpView._41 = 0.0f;
	tmpView._42 = 0.0f;
	tmpView._43 = 0.0f;

	//D3DXMatrixInverse(&tmpInv, 0, g_pMatView);

	//D3DXMatrixMultiply(&tmpWorld, &tmpView, &tmpInv);
	
	g_pD3device->SetTransform(D3DTS_VIEW, &tmpView);

	g_pD3device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	g_pD3device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	g_pD3device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);

	for(int i = 0 ; i < 6 ; i++)
	{
		g_pD3device->SetTexture(0, m_pTexture[i]);
		g_pD3device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2); 
	}

	g_pD3device->SetTransform(D3DTS_VIEW, &matView);

	return true;
}

bool CSkyMap::Release(void)
{

	for(int i = 0; i < 6; i++)
	{
		this->m_pTexture[i]->Release();
	}

	return true;
}

bool CSkyMap::SetTextureUVPos(void)
{	
	D3DSURFACE_DESC desc;
	float Gap;

	for(int i = 0; i < 24; i++)
	{
		if(i % 4 == 0)
		{
			this->m_pTexture[ (int)i/4 ]->GetLevelDesc(0,&desc);	
			Gap = 0.5f / (float)(desc.Width);	

			fSkyUVArray[i][0] += Gap;
			fSkyUVArray[i][1] += Gap;
		}
		else if(i % 4 == 1)
		{
			fSkyUVArray[i][0] += Gap;
			fSkyUVArray[i][1] -= Gap;
		}
		else if(i % 4 == 2)
		{
			fSkyUVArray[i][0] -= Gap;
			fSkyUVArray[i][1] += Gap;
		}
		else if(i % 4 == 3)
		{
			fSkyUVArray[i][0] -= Gap;
			fSkyUVArray[i][1] -= Gap;
		}
	}

	return true;
}

bool CSkyMap::SetSkyMapTexture(int Index, char* filepath)
{

	if(Index < 0 || Index > 6)
	{
		return false;
	}

	ST_TEXTURE *tmpTexure;

	tmpTexure = CResObjMgt::CreateResMgt().SetTextureRes(filepath);

	this->m_pTexture[Index] = tmpTexure->pTexture;

	return true;
}