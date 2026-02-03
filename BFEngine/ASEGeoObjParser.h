#pragma once

#include "./aseparserdef.h"
#include "./ASEparser.h"

class CASEGeoObjParser : public CASEParser
{
// 데이터를 모아놓을 임시 저장소(Collecter)
private:
	ST_ASEPARSER_GEOOBJECT m_GeoObject;
	ST_ASEPARSER_MESH *m_stAseMesh;
	ST_ASEPARSER_MESHANI *m_stAseMeshAni;

	void ErrorMsg(int nErrIndex);

	bool ParsingNodeTM(void);
	bool ParsingMesh(void);
	bool ParsingMeshVertexList(void);
	bool ParsingMeshTextureVertexList(void);
	bool ParsingMeshNormal(void);
	bool ParsingMeshAnimation(void);
	bool InitGeoObject(void);

	bool InitMeshData(void);
	bool InitMeshAniData(void);

public:
	bool ParsingGeoObjData(void);
	ST_ASEPARSER_GEOOBJECT& GetGeoObjParser(void) { return this->m_GeoObject; }

public:
	CASEGeoObjParser(void);
	CASEGeoObjParser(FILE *pFile);
	~CASEGeoObjParser(void);
};
