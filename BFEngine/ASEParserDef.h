#ifndef _ASEPARSER_H
#define _ASEPARSER_H

#include "./std.h"

struct ST_ASEPARSER_SCENE
{
	int nFirstFrame;
	int nLastFrame;
	int nFrameSpeed;
	int nTickPerFrame;
	D3DXVECTOR3 vt3Background_Static;
	D3DXVECTOR3 vt3Ambient_Static;
};

// 마테리얼 경우의 수에 따른 분류
// 서브 마테리얼이 없고 비트맵이 없을 경우
struct ST_ASEPARSER_MTRL_BITMAP
{
	char chBitmapFilepath[512];
};

// 서브 마테리얼이 존재하는 경우
struct ST_ASEPARSER_MTRL_SUBMTRL
{
	int nSubMaterial_count;
	ST_ASEPARSER_MTRL_BITMAP *subMtrl;
};

struct ST_ASEPARSER_MESH
{
	// 메쉬 출력을 위한 인덱스 버퍼 지정
	int nMeshVertexCount, nMeshFaceCount;
	D3DXVECTOR3 *vt3MeshVertexList;
	D3DXVECTOR4 *vt4MeshFaceList;

	// 메쉬 출력을 위한 텍스쳐 UV 좌표지정
	int nTextureVertexCount, nTextureFaceCount;
	D3DXVECTOR3 *vt3TVertexList;
	D3DXVECTOR3 *vt3TFaceList;

	// 메쉬 출력을 위한
	int nNormalCount;
	D3DXVECTOR3 *vt3MeshNormals;
};

struct ST_ANI_QUATROT
{
	int nRotFrame;
	D3DXQUATERNION qtRot;
};

struct ST_ANI_VERTEXPOS
{
	int nPosFrame;
	D3DXVECTOR3 vt3AniPos;
};

struct ST_ANI_VERTEXSCALE
{
	int nScaleFrame;
	D3DXVECTOR3 vt3AniScl;
};

struct ST_ASEPARSER_MESHANI
{
	// 부모 노드 이름
	char NodeName[256];

	// Pos Vertex Data
	int nAniPosCount;
	ST_ANI_VERTEXPOS *pAniPos;

	// ROT Quaternion DATA
	int nAniRotCount;
	ST_ANI_QUATROT *pAniRot;

	// Scale Vertex Data
	int nAniSclCount;
	ST_ANI_VERTEXSCALE *pAniScl;
};



struct ST_ASEPARSER_GEOOBJECT
{
	char strNodeName[256];
	char strParentName[256];

	D3DXVECTOR3 vt3inhPos;
	D3DXVECTOR3 vt3inhRot;
	D3DXVECTOR3 vt3inhScl;
	
	D3DXVECTOR3 matVecGeoObj[4];
	//D3DXMATRIX matGeoObj;

	D3DXVECTOR3 vt3Pos;
	D3DXVECTOR3 vt3RotAxis;
	D3DXVECTOR3 vt3Scale;
	D3DXVECTOR3 vt3ScaleAxis;

	ST_ASEPARSER_MESH *stAseMesh;
	ST_ASEPARSER_MESHANI *stAseMeshAni;

	D3DXVECTOR3 vt3WireFrame;
	int nMtrlREF;
};

//////////////////////////////////////////////////////////
// 실제 파일을 불러올 메쉬 구조체
//////////////////////////////////////////////////////////
struct ST_MESHDATA
{
	ENUM_STAT_FVF nFVF;

	int nTotalMesh;
	int *pnMeshFaceIndex;

	LPDIRECT3DTEXTURE9 lpTexture;
};

struct ST_PTCN_MESHDATA : public ST_MESHDATA
{
	D3DXVECTOR3		*pVp;
	D3DXVECTOR2		*pVt;
	DWORD			*pDwColor;
	D3DXVECTOR3		*pVn;
};

struct ST_PTN_MESHDATA : public ST_MESHDATA
{
	D3DXVECTOR3		*pVp;
	D3DXVECTOR2		*pVt;
	D3DXVECTOR3		*pVn;
};

struct ST_PCN_MESHDATA : public ST_MESHDATA
{
	D3DXVECTOR3		*pVp;
	DWORD			*pDwColor;
	D3DXVECTOR3		*pVn;
};

struct ST_PN_MESHDATA : public ST_MESHDATA
{
	D3DXVECTOR3		*pVp;
	D3DXVECTOR3		*pVn;
};

#endif

