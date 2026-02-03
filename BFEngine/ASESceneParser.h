#pragma once

#include "./aseparserdef.h"
#include "./aseparser.h"

class CASESceneParser : public CASEParser
{
private:
	ST_ASEPARSER_SCENE m_stAseParser;

public:
	bool ParsingSceneData(void);
	ST_ASEPARSER_SCENE& GetSceneParser(void) { return this->m_stAseParser; }

public:
	CASESceneParser(void);
	CASESceneParser(FILE *pFile);
	~CASESceneParser(void);
};
