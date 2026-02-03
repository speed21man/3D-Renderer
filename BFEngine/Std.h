#ifndef _STD_H
#define _STD_H

#define DIRECTINPUT_VERSION     0x0800

#define SAFENEW(A, B)		{ if(!A) A = new B;								}
#define _SAFENEW(A, B)		{ if(!A) { A = new B; A->Init(); }				}

#define SAFEDEL(A)			{ if(A) delete A; (A)=NULL;						}
#define SAFEARRAYDEL(A)	{ if(A) { delete[] A; } (A)=NULL;				}
#define _SAFEDEL(A)			{ if(A) { A->Release(); delete A; } (A)=NULL;	}

#define SAFERELEASE(A)		{ if(A) A->Release(); (A)=NULL;					}


#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <tchar.h>

#pragma comment		(lib, "d3dx9.lib")
#pragma comment		(lib, "d3d9.lib")
#pragma comment		(lib, "dinput8.lib")
//#pragma comment		(lib, "Version.lib")
#pragma comment		(lib, "dxguid.lib")
#pragma comment		(lib, "winmm.lib")

#pragma warning(disable : 4786)
#pragma warning(disable : 4267)
#pragma warning(disable : 4101)
#pragma warning(disable : 4244)
#pragma warning(disable : 4267)
#pragma warning(disable : 4996)

//struct ST_DISPLAYMODE
//{
//	D3DDISPLAYMODE D3dDisMode;
//	BOOL bFullScreen;
//};


enum FILE_INPUT_TYPE
{
	TYPE_NULL,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_VERTEX,
	TYPE_ASEVERTEX
};

struct ST_DEBUGLINE
{
	D3DXVECTOR3 m_Line;
	DWORD Color;
};

//struct ST_MESHFACE
//{
//	D3DXVECTOR3* pVec1;
//	D3DXVECTOR3* pVec2;
//	D3DXVECTOR3* pVec3;
//
//	int nMtrl;
//};
//
//struct ST_TEXTUREFACE
//{
//	D3DXVECTOR2* pVec1;
//	D3DXVECTOR2* pVec2;
//	D3DXVECTOR2* pVec3;
//};
//
//struct ST_FACENORMAL
//{
//	D3DXVECTOR3* pVec1;
//	D3DXVECTOR3* pVec2;
//	D3DXVECTOR3* pVec3;
//};
//
//struct ST_FACECOLOR
//{
//	D3DXVECTOR3* pVec1;
//	D3DXVECTOR3* pVec2;
//	D3DXVECTOR3* pVec3;
//};
//
//struct ST_VERTEX
//{
//	int VertexCount;
//
//	std::vector<D3DXVECTOR3*> st_mpVertex;
//	std::vector<D3DXVECTOR2*> st_mpTFace;
//	std::vector<D3DXVECTOR3*> st_mpCVertex;
//	std::vector<D3DXVECTOR3*> st_mpFaceNormal;
//};
//
//struct ST_ANIROT
//{
//	int nTick;
//	D3DXQUATERNION* pQuatRot;
//};
//
//struct ST_ANIPOS
//{
//	int nTick;
//	D3DXVECTOR3* pVecPos;
//};
//
//struct ST_ANISCALE
//{
//	int nTick;
//	D3DXVECTOR3* pVecPos;
//};

struct ST_DX_PTCN_MESH
{
	//enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) };
	D3DXVECTOR3			vp;
	D3DXVECTOR3			vn;
	D3DCOLOR			vc;
	D3DXVECTOR2			vt;
};

struct ST_DX_PTN_MESH
{
	//enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) };
	D3DXVECTOR3			vp;
	D3DXVECTOR3			vn;
	D3DXVECTOR2			vt;
};

struct ST_DX_PCN_MESH
{
	//enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE) };
	D3DXVECTOR3			vp;
	D3DXVECTOR3			vn;
	D3DCOLOR			vc;
};

struct ST_DX_PN_MESH
{
	//enum { FVF = (D3DFVF_XYZ | D3DFVF_NORMAL) };
	D3DXVECTOR3			vp;
	D3DXVECTOR3			vn;
};

struct ST_PLANE
{
	enum { FVF = (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1) };
	D3DXVECTOR3			vp;
	D3DCOLOR			vc;
	D3DXVECTOR2			vt;
};

struct ST_DEBUGCAMERA
{
	enum { FVF = (D3DFVF_XYZ) };
	D3DXVECTOR3			vp;
};

struct ST_TEXTURE
{
	D3DSURFACE_DESC ddsd;
	LPDIRECT3DTEXTURE9 pTexture;

	ST_TEXTURE(LPDIRECT3DTEXTURE9 lpTex, D3DSURFACE_DESC &desc)
	{
		memcpy(&this->ddsd, &desc, sizeof(D3DSURFACE_DESC));
		this->pTexture = lpTex;
	}
};

enum ENUM_STAT_FVF {STATUS_FVF_NONE, STATUS_FVF_PTCN, STATUS_FVF_PTN, STATUS_FVF_PCN, STATUS_FVF_PN};

enum ENUM_STAT_OBJECT {STATUS_BILLBOARD, STATUS_ANIMATION, STATUS_ORTHOANIMATION, STATUS_ASEMESH};
enum ENUM_STAT_CAMERA {STATUS_CAMERA_DEBUG, STATUS_CAMERA_STATIC};


#define FVFDEBUGLINE  D3DFVF_XYZ | D3DFVF_DIFFUSE

#define WNDWIDTH 800
#define WNDHEIGHT 600
#define WNDMODE TRUE
#define STENCILMODE TRUE
//#define D3DSTENCILFORMAT D3DFMT_D16
#define D3DSTENCILFORMAT D3DFMT_D24S8

#define ADADPTMODE D3DADAPTER_DEFAULT
//#define BEHAVIORMODE D3DCREATE_SOFTWARE_VERTEXPROCESSING
#define BEHAVIORMODE D3DCREATE_HARDWARE_VERTEXPROCESSING
#define DEVTYPE D3DDEVTYPE_HAL

#define DIALOGIMAGEPATH "../Resource/d3dlogo.bmp"
#define MASKCOLOR 0x00000000

//#define pGlobalVar				CGlobalVar::CreateInstance()
//#define g_pMatWorld				CGlobalVar::CreateInstance()->CalculateWorldMatrix()
//#define g_pMatView				CGlobalVar::CreateInstance()->CalculateViewMatrix()
//#define g_pMatPerspect			CGlobalVar::CreateInstance()->CalculatePerspectMatrix()

#endif