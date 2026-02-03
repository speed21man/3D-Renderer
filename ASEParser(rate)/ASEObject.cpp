#include "ASEObject.h"

#include "./global.h"
#include "./ASEDefine.h"
#include "./ASEMtrl.h"
#include "./ASEMesh.h"
#include "./ASEMeshBiped.h"
#include "./ASEMeshObject.h"

ASEObject::ASEObject(void)
{
}

ASEObject::~ASEObject(void)
{
}


bool ASEObject::Init(void)
{
	return true;
}

bool ASEObject::Frame(void)
{
	for(int i = 0 ; i < this->m_nBipedCount ; i++)
	{
		ASEMeshBiped *tmp = this->GetFineBiped(i);
		tmp->Frame();
	}

	for(int i = 0 ; i < this->m_nGeoObjectCount; i++)
	{
		ASEMeshObject *tmp = this->GetFineMesh(i);
		tmp->Frame();
	}

	//ST_MESH *pMesh;

	//if(FAILED(m_pVB->Lock(0, 0, (void**)&pMesh, 0)))
	//{
	//	return false;
	//}

	//for(int j = 0 ; j < this->m_nGeoObjectCount ; j++)
	//{
	//	for(int k = 0 ; k < this->m_nSubMtrl ; k++)
	//	{
	//		ST_VERTEX* pStVertex = GetFineSubMeshVertex(j)->GetSTVertex(k);

	//		if(GetFineSubMeshVertex(j)->m_pMeshmtrl->m_nSubMaterialCount)
	//			ST_SubMaterial* pStSubMtrl = GetFineSubMeshVertex(j)->m_pMeshmtrl->FineSubMaterial(k);
	//


	//		//DWORD temp;

	//		//if(GetFineSubMeshVertex(j)->m_pMeshmtrl)
	//		//{
	//			//ST_SubMaterial* pStSubMtrl = GetFineSubMeshVertex(j)->m_pMeshmtrl->FineSubMaterial(k);
	//			//temp = 
	//		
	//			for(int r = 0 ; r < pStVertex->VertexCount ; r++)
	//			{
	//				pMesh->vp.x = pStVertex->st_mpVertex[r]->x;
	//				pMesh->vp.y = pStVertex->st_mpVertex[r]->y;
	//				pMesh->vp.z = pStVertex->st_mpVertex[r]->z;

	//				pMesh->vn.x = pStVertex->st_mpFaceNormal[r]->x;
	//				pMesh->vn.y = pStVertex->st_mpFaceNormal[r]->y;
	//				pMesh->vn.z = pStVertex->st_mpFaceNormal[r]->z;

	//				//pMesh[i].vc = D3DCOLOR_COLORVALUE(
	//				//	(this->GetFineMaterial(0)->FineSubMaterial(0))->SubMtrl.Diffuse.r,
	//				//	(this->GetFineMaterial(0)->FineSubMaterial(0))->SubMtrl.Diffuse.g,
	//				//	(this->GetFineMaterial(0)->FineSubMaterial(0))->SubMtrl.Diffuse.b,
	//				//	(this->GetFineMaterial(0)->FineSubMaterial(0))->SubMtrl.Diffuse.a);

	//				//pMesh->vc = D3DCOLOR_COLORVALUE(pStVertex->st_mpCVertex[r]->x, pStVertex->st_mpCVertex[r]->y, pStVertex->st_mpCVertex[r]->z, 1.0f);
	//				pMesh->vc = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

	//				//pMesh->vc = D3DCOLOR_COLORVALUE(
	//				//	pStSubMtrl->SubMtrl.Diffuse.r,
	//				//	pStSubMtrl->SubMtrl.Diffuse.g,
	//				//	pStSubMtrl->SubMtrl.Diffuse.b,
	//				//	pStSubMtrl->SubMtrl.Diffuse.a);

	//				pMesh->vt.x = pStVertex->st_mpTFace[r]->x;
	//				pMesh->vt.y = pStVertex->st_mpTFace[r]->y;

	//				pMesh++;
	//			}
	//		//}
	//		//else
	//		//{
	//		//
	//		//	this->m_nSubMtrl = 1;

	//		//	pMesh->vp.x = pStVertex->st_mpVertex[r]->x;
	//		//	pMesh->vp.y = pStVertex->st_mpVertex[r]->y;
	//		//	pMesh->vp.z = pStVertex->st_mpVertex[r]->z;

	//		//	pMesh->vn.x = pStVertex->st_mpFaceNormal[r]->x;
	//		//	pMesh->vn.y = pStVertex->st_mpFaceNormal[r]->y;
	//		//	pMesh->vn.z = pStVertex->st_mpFaceNormal[r]->z;

	//		//	temp = D3DCOLOR_COLORVALUE(255,	255, 0, 255);
	//		//}
	//	}
	//}

	//m_pVB->Unlock();

	return true;
}

bool ASEObject::Render(void)
{
	g_pD3device->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3device->SetRenderState(D3DRS_ZENABLE, TRUE);

	for(int i = 0 ; i < this->m_nBipedCount ; i++)
	{
		ASEMeshBiped *tmp = this->GetFineBiped(i);
		tmp->Render();
	}

	ASEMeshObject *tmp;
	for(int i = 0 ; i < this->m_nGeoObjectCount; i++)
	{
		tmp = this->GetFineMesh(i);
		tmp->Render();
	}

	//g_pD3device->SetTransform(D3DTS_WORLD, g_pMatWorld);

	//g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_MESH));

	//g_pD3device->SetFVF(ST_MESH::FVF);

	//int VertexCount = 0;

	//for(int j = 0 ; j < this->m_nGeoObjectCount ; j++)
	//{	
	//	for(int k = 0 ; k < this->m_nSubMtrl ; k++)
	//	{
	//		ST_VERTEX* pStVertex = GetFineSubMeshVertex(j)->GetSTVertex(k);

	//		if(GetFineSubMeshVertex(j)->m_pMeshmtrl->m_nSubMaterialCount)
	//		{
	//			ST_SubMaterial* pStSubMtrl = GetFineSubMeshVertex(j)->m_pMeshmtrl->FineSubMaterial(k);
	//			g_pD3device->SetMaterial(&pStSubMtrl->SubMtrl);
	//			g_pD3device->SetTexture(0, pStSubMtrl->SubTexture);
	//		}
	//		else
	//		{
	//			g_pD3device->SetMaterial(&GetFineSubMeshVertex(j)->m_pMeshmtrl->m_Mtrl);
	//			g_pD3device->SetTexture(0, GetFineSubMeshVertex(j)->m_pMeshmtrl->m_pTexture);
	//		}

	//		g_pD3device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//		g_pD3device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//		g_pD3device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//		

	//		//if(GetFineSubMeshVertex(j)->m_pMeshmtrl)
	//		//{
	//		//	ST_SubMaterial* pStSubMtrl = GetFineSubMeshVertex(j)->m_pMeshmtrl->FineSubMaterial(k);
	//		//	g_pD3device->SetTexture(0, pStSubMtrl->SubTexture);
	//		//}
	//		//else
	//		//{
	//		//	g_pD3device->SetTexture(0, NULL);
	//		//}

	//		g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, VertexCount, pStVertex->VertexCount/3);

	//		VertexCount += pStVertex->VertexCount;
	//	}
	//}

	return true;
}

bool ASEObject::Release(void)
{
	for(int i = 0 ; i < this->m_nBipedCount ; i++)
	{
		ASEMeshBiped *tmp = this->GetFineBiped(i);
		tmp->Release();
	}

	for(int i = 0 ; i < this->m_nGeoObjectCount; i++)
	{
		ASEMeshObject *tmp = this->GetFineMesh(i);
		tmp->Release();
	}

	std::map<int, ASEMtrl*>::iterator itMtrl = this->m_mpMtrl.begin();

	for(itMtrl ; itMtrl != this->m_mpMtrl.end() ;itMtrl++)
	{
		itMtrl->second->Release();
		delete itMtrl->second;
	}

	this->m_mpMtrl.clear();

	std::map<int, ASEMesh*>::iterator itMeshBiped = this->m_mpMeshBiped.begin();

	for(itMeshBiped; itMeshBiped != this->m_mpMeshBiped.end() ;itMeshBiped++)
	{
		itMeshBiped->second->Release();
		delete itMeshBiped->second;
	}

	this->m_mpMeshBiped.clear();

	std::map<int, ASEMesh*>::iterator itMeshVertex = this->m_mpMeshVertex.begin();\

	for(itMeshVertex; itMeshVertex != this->m_mpMeshVertex.end() ;itMeshVertex++)
	{
		itMeshVertex->second->Release();
		delete itMeshVertex->second;
	}

	this->m_mpMeshVertex.clear();

	return true;
}

bool ASEObject::CreateMesh(char* filename)
{
	this->LoadASEFile(filename);

	for(int i = 0 ; i < this->m_nBipedCount ; i++)
	{
		ASEMeshBiped *tmp = this->GetFineBiped(i);
		tmp->Init();
	}

	for(int i = 0 ; i < this->m_nGeoObjectCount; i++)
	{
		ASEMeshObject *tmp = this->GetFineMesh(i);
		tmp->Init();
	}


	//int Count = 0;

	//for(int j = 0 ; j < this->m_nGeoObjectCount ; j++)
	//{
	//	for(int k = 0 ; k < this->m_nSubMtrl ; k++)
	//	{
	//		int GeoVertexCount = GetFineSubMeshVertex(j)->m_nFaceCount;

	//		Count += GeoVertexCount;
	//	}
	//}

	//if(FAILED(g_pD3device->CreateVertexBuffer(Count * 3 * sizeof(ST_MESH), 
	//	0, ST_MESH::FVF, D3DPOOL_DEFAULT, &this->m_pVB, NULL)))
	//{
	//	return false;
	//}

	return true;
}