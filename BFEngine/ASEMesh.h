#pragma once

#include "./ASEParserDef.h"
#include "./MeshStatus.h"

class CASEMeshParser;
class CASEProcess;

class CASEMesh : public CMeshStatus
{
private:
	//TCHAR tchrFilename[255];
	CASEMeshParser *m_pMeshParser;
	bool SetMeshData(LPCTSTR filename);

	ST_MESHDATA *m_pMeshData;

	bool SetMeshData(void);
	ENUM_STAT_FVF CheckMeshData(ST_ASEPARSER_GEOOBJECT &stAseGeoObj);
	ST_MESHDATA& GetMtrlRefVertex(int nMtrlRef);

	ST_MESHDATA* AddMeshData(ENUM_STAT_FVF Enum_FVF, ST_PTCN_MESHDATA *stMeshData);
	//bool DelMeshData(void);
	//bool InitMeshData(void);

public:
	ST_MESHDATA& GetMeshData(void) { return *this->m_pMeshData; }
	
public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	CASEMesh(LPCTSTR filename);
	CASEMesh(void);
	~CASEMesh(void);
};
