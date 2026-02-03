#include ".\resourcemgt.h"
#include "./global.h"

CResourceMgt::CResourceMgt(void)
:m_nIndex(0)
{
}

CResourceMgt::~CResourceMgt(void)
{
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.07
// 기능 : 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CResourceMgt::Init(void)
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.07
// 기능 : 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL CResourceMgt::Release(void)
{
	map< int, LPDIRECT3DTEXTURE9 >::iterator it_Pos;

	for(it_Pos = this->m_mapTexRes.begin(); 
						it_Pos != this->m_mapTexRes.end(); it_Pos++)
	{
		it_Pos->second->Release();
		delete it_Pos->second;
	}

	this->m_mapTexRes.clear();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.07
// 기능 : STL(map)에 리소스 추가
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
int CResourceMgt::AddTextureRes(LPCTSTR filename)
{
	int nIndex = this->m_nIndex;

	LPDIRECT3DTEXTURE9 pTexture;

	D3DXCreateTextureFromFileEx( g_pD3device,
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
									&pTexture );

	m_mapTexRes.insert( make_pair( m_nIndex, pTexture ) );

	this->m_nIndex++;

	return nIndex;
}

BOOL CResourceMgt::DelTextureRes(int nIndex)
{
	return TRUE;
}

LPDIRECT3DTEXTURE9 CResourceMgt::GetTextureRes(int nIndex)
{
	//LPDIRECT3DTEXTURE9 pTexture;

	map< int, LPDIRECT3DTEXTURE9 >::iterator itPos;

	itPos = m_mapTexRes.find(nIndex);

	return itPos->second;
}


