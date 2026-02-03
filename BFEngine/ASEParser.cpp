#include "ASEParser.h"
#include "./global.h"

CASEParser::CASEParser(void)
{
	memset(&this->m_pBuffer, 0, sizeof(this->m_pBuffer));
	memset(&this->m_Stream, 0, sizeof(this->m_Stream));
	memset(&this->m_String, 0, sizeof(this->m_String));
}

CASEParser::CASEParser(FILE *pFile)
:Parser(pFile)
{
	memset(&this->m_pBuffer, 0, sizeof(this->m_pBuffer));
	memset(&this->m_Stream, 0, sizeof(this->m_Stream));
	memset(&this->m_String, 0, sizeof(this->m_String));
}

CASEParser::~CASEParser(void)
{	
}

D3DXVECTOR3* CASEParser::CreateD3DXVector3(int nCount)
{
	D3DXVECTOR3 *tmpVec = new D3DXVECTOR3[nCount];
	memset(tmpVec, 0, sizeof(tmpVec));

	return tmpVec;
}

D3DXVECTOR4* CASEParser::CreateD3DXVector4(int nCount)
{
	D3DXVECTOR4 *tmpVec = new D3DXVECTOR4[nCount];
	memset(tmpVec, 0, sizeof(tmpVec));

	return tmpVec;
}

bool CASEParser::GetASEFileVertex3Data(D3DXVECTOR3* tmpVec)
{
	int ntmpNum;

	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		&this->m_pString, &ntmpNum, 
		&tmpVec->x, &tmpVec->z, &tmpVec->y);

	return true;
}

bool CASEParser::GetASEFileVertex3Data(D3DXVECTOR3* tmpVec, int *nIndex)
{
	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		&this->m_pString, &nIndex, 
		&tmpVec->x, &tmpVec->z, &tmpVec->y);

	return true;
}

bool CASEParser::GetASEFileVertex4Data(D3DXVECTOR4* tmpVec4)
{
	int tmpInt;

	fgets(m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %s %s %f %s %f %s %f %s %f %s %f %s %f %s %f %s %f", 
		this->m_pString, this->m_pString,
		this->m_pString, &tmpVec4->x, 
		this->m_pString, &tmpVec4->z,
		this->m_pString, &tmpVec4->y,
		this->m_pString, &tmpInt,
		this->m_pString, &tmpInt,
		this->m_pString, &tmpInt,
		this->m_pString, &tmpInt,
		this->m_pString, &tmpVec4->w);

	return true;
}


bool CASEParser::GetASEFileSkipData(void)
{
	int nIndex;

	// FACEÀÇ ³ë¸Ö º¤ÅÍ
	fgets(m_pBuffer, 255, this->m_pStream);
	return true;
}

bool CASEParser::GetASEFileQuaternionData(D3DXQUATERNION* tmpQuat)
{
	int nTmpIndex;

	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f %f", 
		&this->m_pString, &nTmpIndex, 
		&tmpQuat->x, &tmpQuat->z, &tmpQuat->y, &tmpQuat->w);

	return true;
}

bool CASEParser::GetASEFileQuaternionData(D3DXQUATERNION* tmpQuat, int *nIndex)
{
	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f %f", 
		&this->m_pString, &nIndex, 
		&tmpQuat->x, &tmpQuat->z, &tmpQuat->y, &tmpQuat->w);

	return true;
}