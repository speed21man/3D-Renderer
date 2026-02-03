#pragma once

#include "./Parser.h"
#include "./AseParserDef.h"
//#include "./std.h"

class CASESceneParser;
class CASEMtrlParser;
class CASEGeoObjParser;

class CASEMeshParser : public Parser
{
private:
	CASESceneParser* m_pSceneParser;
	CASEMtrlParser* m_pMtrlParser;
	CASEGeoObjParser* m_pGeoObjParser;

	ST_ASEPARSER_SCENE *m_pSceneCollect;
	ST_ASEPARSER_MTRL_BITMAP *m_pMtrlCollect;
	ST_ASEPARSER_GEOOBJECT *m_pGeoObjCollect;

	int m_nMtrlCount, m_nGeoCount;

public:
	bool ASEFileLoad(LPCTSTR filename);
	bool ASEFileClose(void);
	
	ST_ASEPARSER_SCENE*			GetASESceneCollect(void)	{ return this->m_pSceneCollect; }
	ST_ASEPARSER_MTRL_BITMAP*	GetASEMtrlCollect(void)		{ return this->m_pMtrlCollect; }
	ST_ASEPARSER_GEOOBJECT*		GetASEGeoObjCollect(void)	{ return this->m_pGeoObjCollect; }

	int GetGeoObjCount(void) { return this->m_nGeoCount; }
	int GetMtrlCount(void) { return this->m_nMtrlCount; }

	CASEMeshParser(void);
	~CASEMeshParser(void);
};
