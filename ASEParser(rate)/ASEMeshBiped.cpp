#include "ASEMeshBiped.h"

#include "./global.h"

ASEMeshBiped::ASEMeshBiped(void)
{
	bBipedCheck = false;
}

ASEMeshBiped::~ASEMeshBiped(void)
{
}

bool ASEMeshBiped::Init(void)
{
	if(!bBipedCheck)
	{
		return false;
	}

	if(FAILED(g_pD3device->CreateVertexBuffer(m_nFaceCount * 3 * sizeof(ST_MESH), 
		0, ST_MESHNOTEXNODIFF::FVF, D3DPOOL_DEFAULT, &this->m_pVB, NULL)))
	{
		return false;
	}

	return true;
}

bool ASEMeshBiped::Frame(void)
{
	ST_MESHNOTEXNODIFF *pMesh;

	this->SetMatrix();

	if(!bBipedCheck)
	{	
		return false;
	}

	if(FAILED(m_pVB->Lock(0, 0, (void**)&pMesh, 0)))
	{
		return false;
	}

	for(int i = 0 ; i < this->m_nFaceCount ; i++)
	{
		pMesh->vp.x = this->m_mpIndexedVerTex[i]->pVec1->x;
		pMesh->vp.y = this->m_mpIndexedVerTex[i]->pVec1->y;
		pMesh->vp.z = this->m_mpIndexedVerTex[i]->pVec1->z;

		pMesh->vn.x = this->m_mpFaceNormal[i]->pVec1->x;
		pMesh->vn.y = this->m_mpFaceNormal[i]->pVec1->y;
		pMesh->vn.z = this->m_mpFaceNormal[i]->pVec1->z;

		pMesh++;

		pMesh->vp.x = this->m_mpIndexedVerTex[i]->pVec2->x;
		pMesh->vp.y = this->m_mpIndexedVerTex[i]->pVec2->y;
		pMesh->vp.z = this->m_mpIndexedVerTex[i]->pVec2->z;

		pMesh->vn.x = this->m_mpFaceNormal[i]->pVec2->x;
		pMesh->vn.y = this->m_mpFaceNormal[i]->pVec2->y;
		pMesh->vn.z = this->m_mpFaceNormal[i]->pVec2->z;

		pMesh++;

		pMesh->vp.x = this->m_mpIndexedVerTex[i]->pVec3->x;
		pMesh->vp.y = this->m_mpIndexedVerTex[i]->pVec3->y;
		pMesh->vp.z = this->m_mpIndexedVerTex[i]->pVec3->z;

		pMesh->vn.x = this->m_mpFaceNormal[i]->pVec3->x;
		pMesh->vn.y = this->m_mpFaceNormal[i]->pVec3->y;
		pMesh->vn.z = this->m_mpFaceNormal[i]->pVec3->z;

		pMesh++;
	}

	this->m_pVB->Unlock();

	return true;
}

bool ASEMeshBiped::Render(void)
{
	this->m_nFrame += 60.0f; 

	if(this->m_nFrame >= 3200.0f)
	{
		this->m_nFrame = 641.0f;
	}

	if(!bBipedCheck)
	{
		return false;
	}

	g_pD3device->SetTransform(D3DTS_WORLD, &this->m_matCalculate);

	g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_MESHNOTEXNODIFF));

	g_pD3device->SetFVF(ST_MESHNOTEXNODIFF::FVF);

	g_pD3device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, this->m_nFaceCount);

	g_pD3device->SetTransform(D3DTS_WORLD, g_pMatWorld);

	return true;
}

bool ASEMeshBiped::Release(void)
{
	//if(!bBipedCheck)
	//{
	//	return false;
	//}

	std::map<int, D3DXVECTOR3*>::iterator itVertex = this->m_mpVerTex.begin();

	for(itVertex; itVertex != this->m_mpVerTex.end() ; itVertex++)
	{
		delete itVertex->second;
	}

	this->m_mpVerTex.clear();

	std::map<int, D3DXVECTOR2*>::iterator itTVertex = this->m_mpTVertex.begin();

	for(itTVertex; itTVertex != this->m_mpTVertex.end() ; itTVertex++)
	{
		delete itTVertex->second;
	}

	this->m_mpTVertex.clear();

	std::map<int, D3DXVECTOR3*>::iterator itCVertex = this->m_mpCVertex.begin();

	for(itCVertex ; itCVertex != this->m_mpCVertex.end() ; itCVertex++)
	{
		delete itCVertex->second;
	}

	this->m_mpCVertex.clear();

	std::map<int, ST_FACENORMAL*>::iterator	itFaceNormal = this->m_mpFaceNormal.begin();

	for(itFaceNormal ; itFaceNormal != this->m_mpFaceNormal.end() ; itFaceNormal++)
	{
		delete itFaceNormal->second->pVec1;
		delete itFaceNormal->second;
	}

	this->m_mpFaceNormal.clear();

	//////////////////////////////////////////////////////

	for(UINT i = 0; i<m_mpMatRot.size(); i++)
	{
		delete m_mpMatRot[i]->pQuatRot;
		delete m_mpMatRot[i];
	}

	m_mpMatRot.clear();

	for(UINT i = 0; i<m_mpMatPos.size(); i++)
	{
		delete m_mpMatPos[i]->pVecPos;
		delete m_mpMatPos[i];
	}

	m_mpMatPos.clear();

	for(UINT i = 0; i<m_mpMatScale.size(); i++)
	{
		delete m_mpMatScale[i]->pVecPos;
		delete m_mpMatScale[i];
	}

	m_mpMatScale.clear();

	//////////////////////////////////////////////////////

	std::map<int, ST_VERTEX*>::iterator	itSTVertex = this->m_mpSTVertex.begin();

	for(itSTVertex ; itSTVertex != this->m_mpSTVertex.end() ; itSTVertex++)
	{
		delete itSTVertex->second;
	}

	this->m_mpSTVertex.clear();

	std::map<int, ST_MESHFACE*>::iterator itIndexedVerTex = this->m_mpIndexedVerTex.begin();

	for(itIndexedVerTex ; itIndexedVerTex != this->m_mpIndexedVerTex.end() ; itIndexedVerTex++)
	{
		delete itIndexedVerTex->second;
	}

	this->m_mpIndexedVerTex.clear();

	std::map<int, ST_FACECOLOR*>::iterator itIndexedCVertex = this->m_mpIndexedCVertex.begin();

	for(itIndexedCVertex ; itIndexedCVertex != this->m_mpIndexedCVertex.end() ; itIndexedCVertex++)
	{
		delete itIndexedCVertex->second;
	}

	this->m_mpIndexedCVertex.clear();

	std::map<int, ST_TEXTUREFACE*>::iterator itIndexedTFace = this->m_mpIndexedTFace.begin();

	for(itIndexedTFace ; itIndexedTFace != this->m_mpIndexedTFace.end() ; itIndexedTFace++)
	{
		delete itIndexedTFace->second;
	}

	this->m_mpIndexedTFace.clear();

	return true;
}