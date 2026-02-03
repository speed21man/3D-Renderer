#include "ASEMeshParser.h"

#include "./ASESceneParser.h"
#include "./ASEMtrlParser.h"
#include "./ASEGeoObjParser.h"

CASEMeshParser::CASEMeshParser(void)
:m_pSceneParser(NULL),
m_pMtrlParser(NULL),
m_pGeoObjParser(NULL),
m_pGeoObjCollect(NULL),
m_pSceneCollect(NULL),
m_pMtrlCollect(NULL),
m_nMtrlCount(0),
m_nGeoCount(0)
{
}

CASEMeshParser::~CASEMeshParser(void)
{
}

bool CASEMeshParser::ASEFileLoad(LPCTSTR filename)
{
	this->FileOpen(filename);
	
	m_pSceneParser = new CASESceneParser(this->GetFilePointer());

	//this->GetDataFromString("*SCENE");
	m_pSceneParser->GetDataFromString("*SCENE");
	m_pSceneParser->ParsingSceneData();

	m_pMtrlParser = new CASEMtrlParser(m_pSceneParser->GetFilePointer());
	//this->GetDataFromString("*MATERIAL_LIST");
	m_pMtrlParser->GetDataFromString("*MATERIAL_LIST");
	m_pMtrlParser->ParsingMtrlData();

	m_pGeoObjParser = new CASEGeoObjParser(m_pMtrlParser->GetFilePointer());

	int nGeoCount = 0;

	while(1)
	{
		//this->GetDataFromString("*GEOMOBJECT");
		m_pGeoObjParser->GetDataFromString("*GEOMOBJECT");

		if(feof(m_pGeoObjParser->GetFilePointer()))
			break;

		if(!m_pGeoObjCollect)
		{
			m_pGeoObjCollect = new ST_ASEPARSER_GEOOBJECT;
			//m_pGeoObjCollect = (ST_ASEPARSER_GEOOBJECT*)malloc(sizeof(ST_ASEPARSER_GEOOBJECT));
		}
		else
		{
			m_pGeoObjCollect = (ST_ASEPARSER_GEOOBJECT*)realloc(
								m_pGeoObjCollect,
								sizeof(ST_ASEPARSER_GEOOBJECT) * (nGeoCount + 1));
		}

		memcpy(&m_pGeoObjCollect[nGeoCount], &m_pGeoObjParser->GetGeoObjParser(), sizeof(ST_ASEPARSER_GEOOBJECT));

		nGeoCount++;
	}

	memcpy(this->m_pSceneCollect, &m_pSceneParser->GetSceneParser(), sizeof(ST_ASEPARSER_SCENE));
	memcpy(this->m_pMtrlCollect, &m_pMtrlParser->GetMtrlParser(), sizeof(ST_ASEPARSER_MTRL_BITMAP));
	this->m_nGeoCount = nGeoCount;
	this->m_nMtrlCount = m_pMtrlParser->GetMtrlCount();
	return true;
}

bool CASEMeshParser::ASEFileClose(void)
{
	this->FileClose();

	SAFEARRAYDEL(m_pSceneParser);
	SAFEARRAYDEL(m_pMtrlParser);
	SAFEARRAYDEL(m_pGeoObjParser);

	SAFEARRAYDEL(m_pGeoObjCollect);

	return true;
}

