#pragma once

#include "./Parser.h"
//#include "./std.h"
#include <vector>
#include <map>

class ASEMtrl;
class ASEMesh;
class ASEMeshBiped;
class ASEMeshObject;

//class ASEMeshAnimation;

typedef std::map<int, D3DXVECTOR3*> mapVertex;

class ASEParser : public Parser
{
public:
	int m_nMaterialCount, m_nSubMtrl;
	int m_nTotalVertex, m_nTotalFace;
	int m_nTotalTVertex, m_nTotalTFace;
	int m_nTotalCTertex, m_nTotalCFace;

	int m_nStartFrame, m_nLastFrame, m_nTickPerSec;
	int m_nAniTickCount;
	int m_nGeoObjectCount, m_nBipedCount;

	std::map<int, ASEMtrl*> m_mpMtrl;
	std::map<int, ASEMesh*> m_mpMeshBiped;
	std::map<int, ASEMesh*> m_mpMeshVertex;


	ASEMesh* m_pMeshVertex;
	//ASEMeshAnimation* m_pMeshAni;

public:
	bool LoadASEFile(char* filename);

	int AddMaterialData(int nIndex);

	bool SetMaterialData(int nIndex);
	bool SetSubMaterialData(int nMtrlIndex, int nIndex);
	bool SetDiffuseMapData(int nMtrlIndex, int nIndex);
	bool SetDiffuseMapDataRef(int nIndex);

	ASEMesh* SetGeoMObjectData(int nIndex);
	ASEMesh* SetGeoMBipedData(int nIndex);

	bool SetVertexData(void);
	bool SetVertexFaceListData(int nIndex);
	bool ConvertIndextoVertex(int nIndex, int nIndex1, int nIndex2, int nIndex3, int nMtrl);

	D3DXVECTOR3* GetVertexIndex(int nIndex);

	bool SetTextureUVData(void);
	bool SetTextureUVFaceData(void);
	bool ConvertIndextoTextureUV(int nIndex, int nIndex1, int nIndex2, int nIndex3);

	D3DXVECTOR2* GetTextureUVIndex(int nIndex);

	bool SetVertexColorData(void);
	bool SetVertexColorFaceData(void);
	bool ConvertIndextoVertexColor(int nIndex, int nIndex1, int nIndex2, int nIndex3);

	D3DXVECTOR3* GetFaceColorIndex(int nIndex);

	bool SetFaceNormalData(void);
	bool SetVertexNormalData(int nIndex, D3DXVECTOR3* pVec1, D3DXVECTOR3* pVec2, D3DXVECTOR3* pVec3);

	bool SetMaterialREF(int nIndex);

	bool SetAnimationData(void);
	bool SetAniMatrixData(void);

protected:
	bool SetASESceneData(void);
	bool SetMeshData(void);

	LPDIRECT3DTEXTURE9 CreateMeshTexture(LPCTSTR filename);

	ASEMtrl* const GetFineMaterial(int nIndex);
	ASEMesh* const GetFineSubMeshVertex(int nIndex);
	ASEMeshBiped* GetFineBiped(int nIndex);
	ASEMeshObject* GetFineMesh(int nIndex);

protected:
	bool SetSortVertex(void);

public:
	ASEParser(void);
	~ASEParser(void);
};