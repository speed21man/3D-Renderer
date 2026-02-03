#include "ASEMeshObject.h"
#include "./global.h"
#include "./ASEmtrl.h"

ASEMeshObject::ASEMeshObject(void)
{
	SubMaterialCount = 0;
	//SubMaterialCount = 1;
}

ASEMeshObject::~ASEMeshObject(void)
{
}

bool ASEMeshObject::Init(void)
{
	if(FAILED(g_pD3device->CreateVertexBuffer(m_nFaceCount * 3 * sizeof(ST_MESH), 
		0, ST_MESH::FVF, D3DPOOL_DEFAULT, &this->m_pVB, NULL)))
	{
		return false;
	}

	this->SubMaterialCount = this->m_pMeshmtrl->m_nSubMaterialCount;

	return true;
}

bool ASEMeshObject::Frame(void)
{
	ST_MESH *pMesh;

	this->SetMatrix();

	if(FAILED(m_pVB->Lock(0, 0, (void**)&pMesh, 0)))
	{
		return false;
	}

	if(!SubMaterialCount)
	{
		SubMaterialCount = 1;
	}

	for(int i = 0; i < SubMaterialCount ; i++)
	{
		ST_VERTEX* pStVertex = this->GetSTVertex(i);

		if(this->m_pMeshmtrl->m_nSubMaterialCount)
			ST_SubMaterial* pStSubMtrl = m_pMeshmtrl->FineSubMaterial(i);
			
		for(int j = 0 ; j< pStVertex->VertexCount; j++)
		{
			pMesh->vp.x = pStVertex->st_mpVertex[j]->x;
			pMesh->vp.y = pStVertex->st_mpVertex[j]->y;
			pMesh->vp.z = pStVertex->st_mpVertex[j]->z;

			pMesh->vn.x = pStVertex->st_mpFaceNormal[j]->x;
			pMesh->vn.y = pStVertex->st_mpFaceNormal[j]->y;
			pMesh->vn.z = pStVertex->st_mpFaceNormal[j]->z;

			pMesh->vc = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

			pMesh->vt.x = pStVertex->st_mpTFace[j]->x;
			pMesh->vt.y = pStVertex->st_mpTFace[j]->y;

			pMesh++;
		}
	}

	this->m_pVB->Unlock();

	return true;
}

bool ASEMeshObject::Render(void)
{
	g_pD3device->SetTransform(D3DTS_WORLD, &this->m_matCalculate);

	g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_MESH));

	g_pD3device->SetFVF(ST_MESH::FVF);

	int VertexCount = 0;

	for(int i = 0 ; i < SubMaterialCount ; i++)
	{
		ST_VERTEX* pStVertex = GetSTVertex(i);

		if(m_pMeshmtrl->m_nSubMaterialCount)
		{
			ST_SubMaterial* pStSubMtrl = m_pMeshmtrl->FineSubMaterial(i);
			g_pD3device->SetMaterial(&pStSubMtrl->SubMtrl);
			g_pD3device->SetTexture(0, pStSubMtrl->SubTexture);
		}
		else
		{
			g_pD3device->SetMaterial(&m_pMeshmtrl->m_Mtrl);
			g_pD3device->SetTexture(0, m_pMeshmtrl->m_pTexture);
		}

		g_pD3device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, VertexCount, pStVertex->VertexCount/3);

		VertexCount += pStVertex->VertexCount;
	}

	g_pD3device->SetTransform(D3DTS_WORLD, g_pMatWorld);

	//D3DXMATRIX tmpMat;
	//D3DXMatrixIdentity(&tmpMat);
	//g_pD3device->SetTransform(D3DTS_WORLD, &tmpMat);

	return true;
}

bool ASEMeshObject::Release(void)
{
	std::map<int, D3DXVECTOR3*>::iterator itVertex = this->m_mpVerTex.begin();

	for(itVertex; itVertex != this->m_mpVerTex.end() ; itVertex++)
	{
		delete itVertex->second;
	}

	this->m_mpVerTex.clear();

	std::map<int, D3DXVECTOR2*>::iterator itTVertex = this->m_mpTVertex.begin();

	for(itTVertex ; itTVertex != this->m_mpTVertex.end() ; itTVertex++)
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
		delete [] itFaceNormal->second->pVec1;
		//delete itFaceNormal->second->pVec2;
		//delete itFaceNormal->second->pVec3;

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
