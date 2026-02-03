#pragma once

#include "./std.h"
#include <map>

typedef std::map<int, ST_TEXTURE*>::iterator itMapTex;

class CResObjMgt
{
private:
	static CResObjMgt *m_pRes;

private:
	int nTexCount;
	std::map<int, ST_TEXTURE*>	m_mpTex;

public:
	ST_TEXTURE* SetTextureRes(LPCTSTR filename);
	
	ST_TEXTURE* SearchRes(int KeyValue)	{
		return m_mpTex.find(KeyValue)->second;
	}

public:
	static CResObjMgt& CreateResMgt(void)	
	{
		if(!m_pRes)	
		{
			m_pRes = new CResObjMgt;
			m_pRes->Init();
		}

		return *m_pRes;
	}
	
	static bool DeleteObject(void)
	{
		if(m_pRes)
		{
			m_pRes->Release();
			delete[] m_pRes;
			m_pRes = NULL;
		}

		return true;
	}

private:
	bool Init(void);
	bool Release(void);

protected:
	CResObjMgt(void);
	~CResObjMgt(void);
};
