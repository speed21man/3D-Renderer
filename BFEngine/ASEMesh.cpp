#include "ASEMesh.h"
#include "./global.h"
#include "./ASEMeshParser.h"
#include "./ASEProcess.h"
#include "./ResObjMgt.h"

CASEMesh::CASEMesh(void)
:m_pMeshParser(NULL)
//,m_pAseProcess(NULL)
{
}

CASEMesh::~CASEMesh(void)
{
	SAFEDEL(m_pMeshParser);
}

CASEMesh::CASEMesh(LPCTSTR filename)
:m_pMeshParser(NULL)
//,m_pAseProcess(NULL)
{
	//memcpy(tchrFilename, filename, _mbstrlen(tchrFilename));
	this->SetMeshData(filename);
}

bool CASEMesh::SetMeshData(LPCTSTR filename)
{
	SAFENEW(m_pMeshParser, CASEMeshParser);
	this->m_pMeshParser->ASEFileLoad(filename);

	this->m_pMeshParser->GetASESceneCollect();
	this->m_pMeshParser->GetASEMtrlCollect();
	this->m_pMeshParser->GetASEGeoObjCollect();

	this->m_pMeshParser->ASEFileClose();
	SAFEDEL(m_pMeshParser);
	return true;
}

bool CASEMesh::SetMeshData(void)
{
	ST_ASEPARSER_MTRL_BITMAP *ptmpMtrl;
	ST_ASEPARSER_GEOOBJECT *ptmpGeoObj;
	ST_PTCN_MESHDATA *ptmpMeshData;

	ptmpMtrl = this->m_pMeshParser->GetASEMtrlCollect();
	//ptmpMeshData = new ST_PTCN_MESHDATA [ this->m_pMeshParser->GetMtrlCount() ];

	//tmpGeoObj = this->m_pMeshParser->GetASEGeoObjCollect();

	return true;
}

ST_MESHDATA& CASEMesh::GetMtrlRefVertex(int nMtrlRef)
{
	//임시로 데이터를 저장할 곳
	ST_PTCN_MESHDATA *pStMeshData = new ST_PTCN_MESHDATA;

	ST_ASEPARSER_GEOOBJECT *ptmpGeoObj = this->m_pMeshParser->GetASEGeoObjCollect();
	int nGeoCount = this->m_pMeshParser->GetGeoObjCount();

	return *pStMeshData;
}

ENUM_STAT_FVF CheckMeshData(ST_ASEPARSER_GEOOBJECT &stAseGeoObj)
{
	if((stAseGeoObj.stAseMesh->vt3MeshVertexList) &&
		(stAseGeoObj.stAseMesh->vt4MeshFaceList) &&
		(stAseGeoObj.stAseMesh->vt3TVertexList) && 
		(stAseGeoObj.stAseMesh->vt3TFaceList) &&
		(stAseGeoObj.stAseMesh->vt3MeshNormals))
	{
		return STATUS_FVF_PTN;
	}
	else if((stAseGeoObj.stAseMesh->vt3MeshVertexList) &&
			(stAseGeoObj.stAseMesh->vt4MeshFaceList) &&
			(!stAseGeoObj.stAseMesh->vt3TVertexList) && 
			(!stAseGeoObj.stAseMesh->vt3TFaceList) &&
			(stAseGeoObj.stAseMesh->vt3MeshNormals))
	{
		return STATUS_FVF_PN;
	}

	return STATUS_FVF_NONE;
}

//bool CASEMesh::InitMeshData(void)
//{
//	m_pMeshData->lpTexture = NULL;
//	m_pMeshData->NextMeshData = NULL;
//	m_pMeshData->PrevMeshData = NULL;
//
//	return true;
//}

ST_MESHDATA* CASEMesh::AddMeshData(ENUM_STAT_FVF Enum_FVF, ST_PTCN_MESHDATA *stMeshData)
{
	switch(Enum_FVF)
	{
	case STATUS_FVF_PTCN:
		SAFENEW(m_pMeshData, ST_PTCN_MESHDATA);
		memcpy(m_pMeshData, stMeshData, sizeof(ST_PTCN_MESHDATA));
		break;

	case STATUS_FVF_PTN:
		SAFENEW(m_pMeshData, ST_PTN_MESHDATA);
		((ST_PTN_MESHDATA*)m_pMeshData)->nFVF = stMeshData->nFVF;
		((ST_PTN_MESHDATA*)m_pMeshData)->lpTexture = stMeshData->lpTexture;
		((ST_PTN_MESHDATA*)m_pMeshData)->nTotalMesh = stMeshData->nTotalMesh;
		((ST_PTN_MESHDATA*)m_pMeshData)->pnMeshFaceIndex = stMeshData->pnMeshFaceIndex;
		((ST_PTN_MESHDATA*)m_pMeshData)->pVn = stMeshData->pVn;
		((ST_PTN_MESHDATA*)m_pMeshData)->pVp = stMeshData->pVp;
		((ST_PTN_MESHDATA*)m_pMeshData)->pVt = stMeshData->pVt;
		break;

	case STATUS_FVF_PCN:
		SAFENEW(m_pMeshData, ST_PCN_MESHDATA);
		((ST_PCN_MESHDATA*)m_pMeshData)->nFVF = stMeshData->nFVF;
		((ST_PCN_MESHDATA*)m_pMeshData)->lpTexture = NULL;
		((ST_PCN_MESHDATA*)m_pMeshData)->nTotalMesh = stMeshData->nTotalMesh;
		((ST_PCN_MESHDATA*)m_pMeshData)->pnMeshFaceIndex = stMeshData->pnMeshFaceIndex;
		((ST_PCN_MESHDATA*)m_pMeshData)->pVn = stMeshData->pVn;
		((ST_PCN_MESHDATA*)m_pMeshData)->pVp = stMeshData->pVp;
		((ST_PCN_MESHDATA*)m_pMeshData)->pDwColor = stMeshData->pDwColor;
		break;

	case STATUS_FVF_PN:
		SAFENEW(m_pMeshData, ST_PN_MESHDATA);
		((ST_PCN_MESHDATA*)m_pMeshData)->nFVF = stMeshData->nFVF;
		((ST_PCN_MESHDATA*)m_pMeshData)->lpTexture = NULL;
		((ST_PCN_MESHDATA*)m_pMeshData)->nTotalMesh = stMeshData->nTotalMesh;
		((ST_PCN_MESHDATA*)m_pMeshData)->pnMeshFaceIndex = stMeshData->pnMeshFaceIndex;
		((ST_PCN_MESHDATA*)m_pMeshData)->pVn = stMeshData->pVn;
		((ST_PCN_MESHDATA*)m_pMeshData)->pVp = stMeshData->pVp;
		break;
	}

	return m_pMeshData;
}
//
//bool CASEMesh::DelMeshData(void)
//{
//	return true;
//}

bool CASEMesh::Init(void)
{
	return true;
}

bool CASEMesh::Frame(void)
{
	//m_pAseProcess->ASEFrame(*this);
	return true;
}

bool CASEMesh::Render(void)
{
	//m_pAseProcess->ASERender(*this);
	return true;
}

bool CASEMesh::Release(void)
{
	return true;
}
