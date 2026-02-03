#include "ASEMtrlParser.h"

CASEMtrlParser::CASEMtrlParser(void)
:m_nMtrlCount(0)
,m_stAseMtrl(NULL)
{
}

CASEMtrlParser::CASEMtrlParser(FILE *pFile)
:CASEParser(pFile)
,m_nMtrlCount(0)
,m_stAseMtrl(NULL)
{

}

CASEMtrlParser::~CASEMtrlParser(void)
{
}

bool CASEMtrlParser::CreateMtrlStruct(int nMtrlCount)
{
	// 갯수대로 배열 생성
	this->m_stAseMtrl = new ST_ASEPARSER_MTRL_BITMAP [ nMtrlCount ];

	return true;
}

bool CASEMtrlParser::ParsingMtrlData(void)
{

	this->GetDataFromString("*MATERIAL_COUNT", &this->m_nMtrlCount, TYPE_INT);

	// 에러 처리 부분 (실패시 인터럽트가 걸림)
	if(!this->m_nMtrlCount)
		this->ErrorMsg(0);

	// 재질 구조체 생성
	this->CreateMtrlStruct(this->m_nMtrlCount);

	// 비트맵 파서
	for(int i = 0 ; i < this->m_nMtrlCount ; i++)
		this->GetDataFromString("*BITMAP", &m_stAseMtrl[i].chBitmapFilepath, TYPE_STRING);

	return true;
}

void CASEMtrlParser::ErrorMsg(int nErrIndex)
{
	switch(nErrIndex)
	{
	case 0:
		MessageBox(NULL, "재질 파싱 도중 오류가 발생했습니다.", "파실 오류 발생" ,MB_OK);
		break;
	}

	// 인터럽트
	_asm{
		int 3;
	};
}

