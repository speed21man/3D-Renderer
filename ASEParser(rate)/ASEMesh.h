#pragma once

#include "./std.h"
#include "./ASEDefine.h"
#include <map>
#include <vector>

class ASEMtrl;
//class ASEMeshAnimation;

class ASEMesh
{
public:
	char								m_chNodeName[256];
	char								m_ParentNodeName[256];
	char								m_pAniNodeName[256];
	int									m_nFaceCount;
	int									SubMaterialCount;
	int									m_nTotalTick;
	float								m_nFrame;

	ASEMtrl*							m_pMeshmtrl;
	ASEMesh*							m_pParentMesh;
	//ASEMeshAnimation*					m_pParectMatrix;

	LPDIRECT3DVERTEXBUFFER9				m_pVB;

	D3DXMATRIX							m_matMatrix;
	D3DXMATRIX							m_matAniMatrix;
	D3DXMATRIX							m_matCalculate;

	D3DXMATRIX							m_matParentInvertMat;
	D3DXQUATERNION						m_matRot;
	D3DXVECTOR3							m_matPos;
	D3DXVECTOR3							m_matScale;

public:
	std::map<int, ST_VERTEX*>			m_mpSTVertex;

	std::map<int, D3DXVECTOR3*>			m_mpVerTex;
	std::map<int, D3DXVECTOR2*>			m_mpTVertex;
	std::map<int, D3DXVECTOR3*>			m_mpCVertex;

	std::map<int, ST_MESHFACE*>			m_mpIndexedVerTex;
	std::map<int, ST_FACECOLOR*>		m_mpIndexedCVertex;
	std::map<int, ST_TEXTUREFACE*>		m_mpIndexedTFace;
	std::map<int, ST_FACENORMAL*>		m_mpFaceNormal;
	
	std::map<int, int> m_mnSubMtrl;

	std::vector<ST_ANIROT*>				m_mpMatRot;
	std::vector<ST_ANIPOS*>				m_mpMatPos;
	std::vector<ST_ANISCALE*>			m_mpMatScale;

public:
	bool AddSTVertex(int Num);

	bool AddSubMtrlIndex(int nIndex, int nSubMtrl);

	bool AddVertex(int nSubMtrl, D3DXVECTOR3* pVec);
	bool AddTextureFace(int nSubMtrl, D3DXVECTOR2* pVec);
	bool AddFaceNormal(int nSubMtrl, D3DXVECTOR3* pVec);
	bool AddFaceColor(int nSubMtrl, D3DXVECTOR3* pVec);

public:
	bool SetSTVertex(int nSubMtrl, D3DXVECTOR3* pVec, D3DXVECTOR2* pFace, D3DXVECTOR3* pColor, D3DXVECTOR3* pNormal);
	bool SetMaterial(ASEMtrl* pMtrl);
	bool SetFaceCount(int nCount);

public:
	bool SortSubMaterialVertex(void);
	bool NoMaterialRefVeretex(void);

public:
	ST_VERTEX* GetSTVertex(int nSubMtrl);

	int GetSubMtrlIndex(int nIndex);

	D3DXVECTOR3* GetVertex(int nSubMtrl, int nIndex);
	D3DXVECTOR2* GetTextureFace(int nSubMtrl, int nIndex);
	D3DXVECTOR3* GetFaceNormal(int nSubMtrl, int nIndex);
	D3DXVECTOR3* GetFaceColor(int nSubMtrl, int nIndex);

protected:
	//int GetSubMaterialCount(int nIndex);
	ST_MESHFACE* GetVertexIndex(int nIndex);
	ST_TEXTUREFACE* GetTextureIndex(int nIndex);
	ST_FACENORMAL* GetNormalVertex(int nIndex);
	ST_FACECOLOR* GetColorVertex(int nIndex);

protected:
	bool SetMatrix(void);
	ST_ANIROT* GetAniRotTick(int CurFrame);
	ST_ANIROT* GetNextAniRotTick(int CurFrame);
	ST_ANIPOS* GetAniPosTick(int CurFrame);
	ST_ANIPOS* GetNextAniPosTick(int CurFrame);
	bool CalculateRotSlerp(void);
	bool CalculatePosSlerp(void);

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	ASEMesh(void);
	~ASEMesh(void);
};
