#include "ResObjMgt.h"
#include "./global.h"

CResObjMgt *CResObjMgt::m_pRes = NULL;

CResObjMgt::CResObjMgt(void)
:nTexCount(0)
{
}

CResObjMgt::~CResObjMgt(void)
{
}

bool CResObjMgt::Init(void)
{
	return true;
}

bool CResObjMgt::Release(void)
{
	itMapTex itTex = this->m_mpTex.begin();

	while(itTex != this->m_mpTex.end())
	{
		itTex->second->pTexture->Release();
		itTex++;
	}

	//완전 클리어 시킴
	this->m_mpTex.clear();

	return true;
}

ST_TEXTURE* CResObjMgt::SetTextureRes(LPCTSTR filename)
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DSURFACE_DESC ddsd;

	pTexture = NULL;
	memset(&ddsd, 0, sizeof(&ddsd));

	if(FAILED(D3DXCreateTextureFromFileEx( g_pD3device,
									filename,
									D3DX_DEFAULT,
									D3DX_DEFAULT,
									D3DX_DEFAULT,
									//D3DX_FROM_FILE,
									0,
									D3DFMT_UNKNOWN, //D3DFMT_FROM_FILE, //
									D3DPOOL_MANAGED,
									//D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
									//D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
									D3DX_FILTER_LINEAR,   //D3DX_FILTER_LINEAR,
									D3DX_FILTER_LINEAR,   //D3DX_FILTER_LINEAR,
									MASKCOLOR,     // 투명컬러키
									NULL,
									NULL,
									&pTexture )))
	{
		return 0;
	}

	pTexture->GetLevelDesc(0, &ddsd);

// 임시로 사용할 곳(나중에 메모리 풀을 만들어 관리할 것임)
///////////////////////////////////////////////////////////
	ST_TEXTURE *temp = new ST_TEXTURE(pTexture, ddsd);
	m_mpTex.insert(std::make_pair(this->nTexCount, temp));
///////////////////////////////////////////////////////////

	this->nTexCount++;

	return temp;
}
