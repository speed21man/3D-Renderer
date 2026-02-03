#pragma once

#include "./aseparserdef.h"
#include "./ASEparser.h"

class CASEMtrlParser : public CASEParser
{
private:
	int m_nMtrlCount;
	ST_ASEPARSER_MTRL_BITMAP *m_stAseMtrl;

	bool CreateMtrlStruct(int nMtrlCount);
	void ErrorMsg(int nErrIndex);

public:
	bool ParsingMtrlData(void);
	int GetMtrlCount(void) { return this->m_nMtrlCount; }
	ST_ASEPARSER_MTRL_BITMAP& GetMtrlParser(void) { return *m_stAseMtrl; };
	
	//bool ParsingMtrlData(ST_ASEPARSER_MTRL_SUBMTRL &st_submtrlBmp);

public:
	CASEMtrlParser(void);
	CASEMtrlParser(FILE *pFile);
	~CASEMtrlParser(void);
};

