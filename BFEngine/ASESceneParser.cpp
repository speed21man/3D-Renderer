#include "ASESceneParser.h"

CASESceneParser::CASESceneParser(void)
{
}

CASESceneParser::~CASESceneParser(void)
{
}

CASESceneParser::CASESceneParser(FILE *pFile)
:CASEParser(pFile)
{
}

bool CASESceneParser::ParsingSceneData(void)
{
	this->GetDataFromString("*SCENE_FIRSTFRAME", &m_stAseParser.nFirstFrame, TYPE_INT);
	this->GetDataFromString("*SCENE_LASTFRAME", &m_stAseParser.nLastFrame, TYPE_INT);
	this->GetDataFromString("*SCENE_FRAMESPEED", &m_stAseParser.nFrameSpeed, TYPE_INT);
	this->GetDataFromString("*SCENE_TICKSPERFRAME", &m_stAseParser.nTickPerFrame, TYPE_INT);
	this->GetDataFromString("*SCENE_BACKGROUND_STATIC", &m_stAseParser.vt3Background_Static, TYPE_VERTEX);
	this->GetDataFromString("*SCENE_AMBIENT_STATIC", &m_stAseParser.vt3Ambient_Static, TYPE_VERTEX);

	return true;
}

