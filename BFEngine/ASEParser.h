#pragma once

#include "./Parser.h"
#include "./std.h"

class CASEParser : public Parser
{
private:
	char m_Buffer[256];
	char m_Stream[256];
	char m_String[256];

protected:
	D3DXVECTOR3* CreateD3DXVector3(int count);
	D3DXVECTOR4* CreateD3DXVector4(int count);

	//bool GetMeshFaceLIst(D3DXVECTOR4* tmpVec4);
	bool GetASEFileVertex3Data(D3DXVECTOR3* tmpVec);
	bool GetASEFileVertex3Data(D3DXVECTOR3* tmpVec, int *nIndex);

	bool GetASEFileVertex4Data(D3DXVECTOR4* tmpVec4);	
	bool GetASEFileQuaternionData(D3DXQUATERNION* tmpQuat);
	bool GetASEFileQuaternionData(D3DXQUATERNION* tmpQuat, int *nIndex);

	bool GetASEFileSkipData(void);

public:
	CASEParser(void);
	CASEParser(FILE *pFile);
	~CASEParser(void);
};
