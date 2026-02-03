#pragma once

#include "./std.h"
#include <map>
#include <string>

using namespace std;

class CResourceMgt
{
public:
	UINT m_nIndex;

public:
	BOOL Init(void);
	BOOL Release(void);

public:
	//std::map< int, std::string> m_mapTexMgt;
	map< int, LPDIRECT3DTEXTURE9 > m_mapTexRes;
	
public:
	//LPDIRECT3DTEXTURE9 AddTextureRes(LPCTSTR filename, char* ID); 
	int AddTextureRes(LPCTSTR filename); 

	BOOL DelTextureRes(int nIndex); 
	LPDIRECT3DTEXTURE9 GetTextureRes(int nIndex);

public:
	LPDIRECT3DTEXTURE9 const operator [] (int nIndex)
	{
		return GetTextureRes(nIndex);
	}

public:
	CResourceMgt(void);
	~CResourceMgt(void);
};
