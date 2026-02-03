#include "ASEMesh.h"

#include "./ASEMtrl.h"
#include "./global.h"

ASEMesh::ASEMesh(void)
{
	memset(m_chNodeName, 0, sizeof(m_chNodeName));
	this->m_pMeshmtrl = NULL;

	this->m_nFrame = 0.0f;
	this->m_nTotalTick = 0;

	this->m_pParentMesh = NULL;
	D3DXMatrixIdentity(&this->m_matMatrix);
	D3DXMatrixIdentity(&this->m_matCalculate);
	D3DXMatrixIdentity(&this->m_matAniMatrix);
	D3DXQuaternionIdentity(&this->m_matRot);
	memset(&this->m_matPos, 0 , sizeof(D3DXVECTOR3));
	memset(&this->m_matScale, 0 , sizeof(D3DXVECTOR3));
}

ASEMesh::~ASEMesh(void)
{
}

bool ASEMesh::AddSTVertex(int Num)
{

	for(int i = 0 ; i < Num ; i++)
	{
		ST_VERTEX *tmpVertex = new ST_VERTEX;
		tmpVertex->VertexCount = 0;
		this->m_mpSTVertex.insert(std::make_pair(i, tmpVertex));
	}

	return true;
}

bool ASEMesh::SetSTVertex(int nSubMtrl, D3DXVECTOR3* pVec, D3DXVECTOR2* pFace, D3DXVECTOR3* pColor, D3DXVECTOR3* pNormal)
{
	this->AddVertex(nSubMtrl, pVec);

	if(pFace)
	{
		this->AddTextureFace(nSubMtrl, pFace);
	}

	if(pColor)
	{
		this->AddFaceColor(nSubMtrl, pColor);
	}

	this->AddFaceNormal(nSubMtrl, pNormal);

	return true;
}

ST_VERTEX* ASEMesh::GetSTVertex(int nSubMtrl)
{
	std::map<int, ST_VERTEX*>::iterator itPos;

	itPos = this->m_mpSTVertex.find(nSubMtrl);

	return itPos->second;
}

bool ASEMesh::AddVertex(int nSubMtrl, D3DXVECTOR3* pVec)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	tmp->VertexCount++;

	tmp->st_mpVertex.push_back(pVec);

	return true;
}

bool ASEMesh::AddTextureFace(int nSubMtrl, D3DXVECTOR2* pVec)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	tmp->st_mpTFace.push_back(pVec);

	return true;
}

bool ASEMesh::AddFaceNormal(int nSubMtrl, D3DXVECTOR3* pVec)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	tmp->st_mpFaceNormal.push_back(pVec);

	return true;
}

bool ASEMesh::AddFaceColor(int nSubMtrl, D3DXVECTOR3* pVec)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	tmp->st_mpCVertex.push_back(pVec);

	return true;
}

D3DXVECTOR3* ASEMesh::GetVertex(int nSubMtrl, int nIndex)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	return tmp->st_mpVertex[nIndex];
}

D3DXVECTOR2* ASEMesh::GetTextureFace(int nSubMtrl, int nIndex)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	return tmp->st_mpTFace[nIndex];
}

D3DXVECTOR3* ASEMesh::GetFaceNormal(int nSubMtrl, int nIndex)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	return tmp->st_mpFaceNormal[nIndex];
}

D3DXVECTOR3* ASEMesh::GetFaceColor(int nSubMtrl, int nIndex)
{
	ST_VERTEX *tmp = this->GetSTVertex(nSubMtrl);

	return tmp->st_mpCVertex[nIndex];
}

bool ASEMesh::AddSubMtrlIndex(int nIndex, int nSubMtrl)
{
	this->m_mnSubMtrl.insert(std::make_pair(nIndex, nSubMtrl));

	return true;
}

int ASEMesh::GetSubMtrlIndex(int nIndex)
{
	std::map<int, int>::iterator itPos;

	itPos = this->m_mnSubMtrl.find(nIndex);

	return itPos->second;
}

bool ASEMesh::SortSubMaterialVertex(void)
{
	int MaterialSize = this->m_pMeshmtrl->m_nSubMaterialCount;

	if(MaterialSize)
	{
		this->AddSTVertex(MaterialSize);
	}
	else
	{
		this->AddSTVertex(1);
	}

	for(int i = 0; i < this->m_nFaceCount ; i++)
	{
		int nSubMtrl = this->GetSubMtrlIndex(i);
		ST_MESHFACE* pMeshFace = this->GetVertexIndex(i);
		ST_FACENORMAL* pFaceNormal = this->GetNormalVertex(i);
		ST_TEXTUREFACE* pTextureFace = this->GetTextureIndex(i);
		//ST_FACECOLOR* pFaceColor = this->GetColorVertex(i);

		//this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec1, pTextureFace->pVec1, pFaceColor ->pVec1, pFaceNormal->pVec1);
		//this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec2, pTextureFace->pVec2, pFaceColor ->pVec2, pFaceNormal->pVec2);
		//this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec3, pTextureFace->pVec3, pFaceColor ->pVec3, pFaceNormal->pVec3);

		if(!MaterialSize)
		{
			pMeshFace->nMtrl = 0;
		}

		this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec1, pTextureFace->pVec1, 0, pFaceNormal->pVec1);
		this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec2, pTextureFace->pVec2, 0, pFaceNormal->pVec2);
		this->SetSTVertex(pMeshFace->nMtrl, pMeshFace->pVec3, pTextureFace->pVec3, 0, pFaceNormal->pVec3);
	}

	return true;
}

bool ASEMesh::NoMaterialRefVeretex(void)
{
	for(int i = 0; i < this->m_nFaceCount ; i++)
	{
		ST_MESHFACE* pMeshFace = this->GetVertexIndex(i);
		ST_FACENORMAL* pFaceNormal = this->GetNormalVertex(i);
		//ST_TEXTUREFACE* pTextureFace = this->GetTextureIndex(i);

		this->SetSTVertex(0, pMeshFace->pVec1, 0, 0, pFaceNormal->pVec1);
		this->SetSTVertex(0, pMeshFace->pVec2, 0, 0, pFaceNormal->pVec2);
		this->SetSTVertex(0, pMeshFace->pVec3, 0, 0, pFaceNormal->pVec3);
	}
	
	return true;
}

bool ASEMesh::SetFaceCount(int nCount)
{
	this->m_nFaceCount = nCount;

	return true;
}

//int ASEMesh::GetSubMaterialCount(int nIndex)
//{
//	std::map<int, int>::iterator itPos;	
//
//	itPos = this->m_mnSubMtrl.find(nIndex);
//
//	return itPos->second;
//}

ST_MESHFACE* ASEMesh::GetVertexIndex(int nIndex)
{
	std::map<int, ST_MESHFACE*>::iterator itPos;

	itPos = this->m_mpIndexedVerTex.find(nIndex);

	return itPos->second;
}

ST_TEXTUREFACE* ASEMesh::GetTextureIndex(int nIndex)
{
	std::map<int, ST_TEXTUREFACE*>::iterator itPos;

	itPos = this->m_mpIndexedTFace.find(nIndex);

	return itPos->second;
}

ST_FACENORMAL* ASEMesh::GetNormalVertex(int nIndex)
{
	std::map<int, ST_FACENORMAL*>::iterator itPos;

	itPos = this->m_mpFaceNormal.find(nIndex);

	return itPos->second;
}

ST_FACECOLOR* ASEMesh::GetColorVertex(int nIndex)
{
	std::map<int, ST_FACECOLOR*>::iterator itPos;

	itPos = this->m_mpIndexedCVertex.find(nIndex);

	return itPos->second;
}

bool ASEMesh::Init(void)
{
	//this->SubMaterialCount = this->m_pMeshmtrl->m_nSubMaterialCount;

	//if(!SubMaterialCount)
	//{
	//	SubMaterialCount = 1;
	//}

	//if(FAILED(g_pD3device->CreateVertexBuffer(m_nFaceCount * 3 * sizeof(ST_MESH), 
	//	0, ST_MESH::FVF, D3DPOOL_DEFAULT, &this->m_pVB, NULL)))
	//{
	//	return false;
	//}

	return true;
}

bool ASEMesh::Frame(void)
{
	//ST_MESH *pMesh;

	//if(FAILED(m_pVB->Lock(0, 0, (void**)&pMesh, 0)))
	//{
	//	return false;
	//}

	//for(int i = 0; i < SubMaterialCount ; i++)
	//{
	//	ST_VERTEX* pStVertex = this->GetSTVertex(i);

	//	if(this->m_pMeshmtrl->m_nSubMaterialCount)
	//		ST_SubMaterial* pStSubMtrl = m_pMeshmtrl->FineSubMaterial(i);
	//		
	//	for(int j = 0 ; j< pStVertex->VertexCount ; j++)
	//	{
	//		pMesh->vp.x = pStVertex->st_mpVertex[j]->x;
	//		pMesh->vp.y = pStVertex->st_mpVertex[j]->y;
	//		pMesh->vp.z = pStVertex->st_mpVertex[j]->z;

	//		pMesh->vn.x = pStVertex->st_mpFaceNormal[j]->x;
	//		pMesh->vn.y = pStVertex->st_mpFaceNormal[j]->y;
	//		pMesh->vn.z = pStVertex->st_mpFaceNormal[j]->z;

	//		pMesh->vc = D3DCOLOR_COLORVALUE(1.0f, 1.0f, 1.0f, 1.0f);

	//		pMesh->vt.x = pStVertex->st_mpTFace[j]->x;
	//		pMesh->vt.y = pStVertex->st_mpTFace[j]->y;

	//		pMesh++;
	//	}
	//}

	//this->m_pVB->Unlock();

	return true;
}

bool ASEMesh::Render(void)
{
	//g_pD3device->SetStreamSource(0, this->m_pVB, 0 ,sizeof(ST_MESH));

	//g_pD3device->SetFVF(ST_MESH::FVF);

	//int VertexCount = 0;

	//for(int i = 0 ; i < SubMaterialCount ; i++)
	//{
	//	ST_VERTEX* pStVertex = GetSTVertex(i);

	//	if(m_pMeshmtrl->m_nSubMaterialCount)
	//	{
	//		ST_SubMaterial* pStSubMtrl = m_pMeshmtrl->FineSubMaterial(i);
	//		g_pD3device->SetMaterial(&pStSubMtrl->SubMtrl);
	//		g_pD3device->SetTexture(0, pStSubMtrl->SubTexture);
	//	}
	//	else
	//	{
	//		g_pD3device->SetMaterial(&m_pMeshmtrl->m_Mtrl);
	//		g_pD3device->SetTexture(0, m_pMeshmtrl->m_pTexture);
	//	}

	//	g_pD3device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//	g_pD3device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//	g_pD3device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//	g_pD3device->DrawPrimitive(D3DPT_TRIANGLELIST, VertexCount, pStVertex->VertexCount/3);

	//	VertexCount += pStVertex->VertexCount;
	//}

	return true;
}
	
bool ASEMesh::Release(void)
{
	return true;
}

bool ASEMesh::SetMatrix(void)
{
	D3DXMATRIX tmpMat;

	D3DXQuaternionIdentity(&this->m_matRot);
	//D3DXMatrixIdentity(&this->m_matMatrix);
	//D3DXMatrixIdentity(&this->m_matCalculate);

	D3DXMatrixIdentity(&tmpMat);

	CalculateRotSlerp();
	
	//if(m_mpMatRot.size())
	//{
	//	int  = this->GetAniRotTick(m_nFrame);


	//	if(!Index && this->m_pParentMesh)
	//	{
	//		D3DXMatrixInverse(&this->m_matParentInvertMat, 0, &this->m_pParentMesh->m_matMatrix);
	//		D3DXMatrixMultiply(&m_matMatrix, &m_matMatrix, &this->m_matParentInvertMat);

	//		m_matMatrix._41 = 0.0f;
	//		m_matMatrix._42 = 0.0f;
	//		m_matMatrix._43 = 0.0f;
	//		m_matMatrix._44 = 1.0f;
	//	}
	//	else
	//	{
	//		D3DXQuaternionSlerp(&m_matRot, 
	//			this->m_mpMatRot[Index]->pQuatRot,
	//			this->m_mpMatRot[Index + 1]->pQuatRot,
	//			(m_nFrame - this->m_mpMatRot[Index]->nTick) / (this->m_mpMatRot[Index + 1]->nTick - this->m_mpMatRot[Index]->nTick));

	//		
	//		D3DXMatrixRotationQuaternion(&m_matMatrix, &m_matRot);
	//	}
	//}

	memset(&this->m_matPos, 0, sizeof(D3DXVECTOR3));
	CalculatePosSlerp();



	//if(m_mpMatPos.size())
	//{
	//	int Index = this->GetAniPosTick(m_nFrame);

	//	if(!Index && this->m_pParentMesh)
	//	{

	//		D3DXMatrixInverse(&this->m_matParentInvertMat, 0, &this->m_pParentMesh->m_matMatrix);
	//		D3DXMatrixMultiply(&tmpMat, &tmpMat, &this->m_matParentInvertMat);

	//		this->m_matPos.x = tmpMat._41;
	//		this->m_matPos.y = tmpMat._42;
	//		this->m_matPos.z = tmpMat._43;

	//	}
	//	else if(!Index && !this->m_pParentMesh)
	//	{
	//		
	//		//D3DXVECTOR3 tmpVec;

	//		//tmpVec = (*(this->m_mpMatPos[Index]->pVecPos) -  this->m_matPos) *
	//		//			(((float)m_nFrame) / (float)(this->m_mpMatPos[Index]->nTick));

	//		//this->m_matPos = *(this->m_mpMatPos[Index]->pVecPos) + tmpVec;
	//	
	//	}
	//	else
	//	{

	//		D3DXVECTOR3 tmpVec;

	//		tmpVec = (*(this->m_mpMatPos[Index + 1]->pVecPos) - *(this->m_mpMatPos[Index]->pVecPos)) *
	//					(((float)m_nFrame - (float)this->m_mpMatPos[Index]->nTick) / (float)(this->m_mpMatPos[Index + 1]->nTick - this->m_mpMatPos[Index]->nTick));

	//		this->m_matPos = *(this->m_mpMatPos[Index]->pVecPos) + tmpVec;

	//	}
	//}

	if(this->m_pParentMesh)
	{
		D3DXMatrixMultiply(&m_matCalculate, &m_matAniMatrix, &this->m_pParentMesh->m_matCalculate);
		//this->m_matMatrix = m_matCalculate;
	}
	else
	{
		D3DXMATRIX tmpMat;
		D3DXMatrixIdentity(&tmpMat);
		D3DXMatrixMultiply(&m_matCalculate, &m_matAniMatrix, &tmpMat);
	}

	//D3DXMatrixInverse(&this->m_matParentInvertMat, 0, &m_matCalculate);

	//else
	//{
	//	D3DXMATRIX tmpMat;
	//	D3DXMatrixIdentity(&tmpMat);

	//	D3DXMatrixMultiply(&m_matMatrix, &m_matMatrix, &tmpMat);
	//}

	return true;
}

ST_ANIROT* ASEMesh::GetAniRotTick(int CurFrame)
{
	for(int i = 0 ; i < m_mpMatRot.size(); i++)
	{
		if(CurFrame >= this->m_mpMatRot[i]->nTick)
		{
			if( i + 1 < this->m_mpMatRot.size())
			{
				if(CurFrame <= this->m_mpMatRot[i+1]->nTick)
				{
					return this->m_mpMatRot[i];
				}
			}
		}
	}

	return NULL;
}

ST_ANIPOS* ASEMesh::GetAniPosTick(int CurFrame)
{
	for(int i = 0 ; i < m_mpMatPos.size(); i++)
	{
		if(CurFrame >= this->m_mpMatPos[i]->nTick)
		{
			if( i + 1 < this->m_mpMatPos.size())
			{
				if(CurFrame <= this->m_mpMatPos[i+1]->nTick)
				{
					return this->m_mpMatPos[i];
				}
			}
		}
	}

	return NULL;
}

ST_ANIROT* ASEMesh::GetNextAniRotTick(int CurFrame)
{
	for(int i = 0 ; i < m_mpMatRot.size(); i++)
	{
		if(CurFrame <= this->m_mpMatRot[i]->nTick)
		{
			return this->m_mpMatRot[i];
		}
	}

	return NULL;
}

ST_ANIPOS* ASEMesh::GetNextAniPosTick(int CurFrame)
{
	for(int i = 0 ; i < m_mpMatPos.size(); i++)
	{
		if(CurFrame <= this->m_mpMatPos[i]->nTick)
		{
			return this->m_mpMatPos[i];
		}
	}

	return NULL;
}

bool ASEMesh::CalculateRotSlerp(void)
{
	ST_ANIROT *pAniRot, *pNextAniRot;
	ST_ANIROT tmpAniRot;
	D3DXQUATERNION tmpQuat;

	if(this->GetAniRotTick(this->m_nFrame))
	{
		pAniRot = this->GetAniRotTick(this->m_nFrame);

		pNextAniRot = this->GetNextAniRotTick(this->m_nFrame);

		if(pNextAniRot)
		{
			pNextAniRot = this->GetNextAniRotTick(this->m_nFrame);

			memcpy(&tmpAniRot, pAniRot, sizeof(ST_ANIROT));

			memcpy(&tmpQuat, tmpAniRot.pQuatRot, sizeof(D3DXQUATERNION));

			D3DXQuaternionSlerp(&m_matRot, 
					&tmpQuat,
					pNextAniRot->pQuatRot,
					(float)(m_nFrame - tmpAniRot.nTick) / (pNextAniRot->nTick - tmpAniRot.nTick));
		}
		else
		{
			memcpy(&tmpAniRot, pAniRot, sizeof(ST_ANIROT));
			memcpy(&m_matRot, tmpAniRot.pQuatRot, sizeof(D3DXQUATERNION));
		}

		//memcpy(&tmpAniRot, pAniRot, sizeof(ST_ANIROT));

		

		//D3DXQuaternionSlerp(&m_matRot, 
		//	&tmpQuat,
		//	pNextAniRot->pQuatRot,
		//	(m_nFrame - pAniRot->nTick) / (pNextAniRot->nTick - pAniRot->nTick));
		//
		D3DXMatrixRotationQuaternion(&m_matAniMatrix, &m_matRot);
	}
	else
	{
		if(this->m_pParentMesh)
		{
			//D3DXMatrixInverse(&this->m_pParentMesh->m_matParentInvertMat, 0, &this->m_pParentMesh->m_matMatrix);
			D3DXMatrixMultiply(&m_matAniMatrix, &m_matMatrix, &this->m_pParentMesh->m_matParentInvertMat);


		}
		else
		{
			m_matAniMatrix = m_matMatrix;
		}

		m_matAniMatrix._41 = 0.0f;
		m_matAniMatrix._42 = 0.0f;
		m_matAniMatrix._43 = 0.0f;
		m_matAniMatrix._44 = 1.0f;
	}

	return true;
}

bool ASEMesh::CalculatePosSlerp(void)
{
	D3DXMATRIX tmpMat;
	D3DXVECTOR3 tmpVec, tmpVec1;
	ST_ANIPOS *pAniPos, *pNextAniPos;

	//if(this->GetAniPosTick(this->m_nFrame))
	//{

	if(this->GetAniPosTick(this->m_nFrame))
	{
		pAniPos = this->GetAniPosTick(this->m_nFrame);
		pNextAniPos = this->GetNextAniPosTick(this->m_nFrame);

		ST_ANIPOS tmpAniPos;

		if(pNextAniPos)
		{
			D3DXVECTOR3 tmpTotalVec;

			memcpy(&tmpAniPos, pAniPos, sizeof(ST_ANIPOS));
			
			memcpy(&tmpVec1, tmpAniPos.pVecPos, sizeof(D3DXVECTOR3));

			tmpTotalVec = (*(pNextAniPos->pVecPos) - tmpVec1) *
				(((float)m_nFrame - tmpAniPos.nTick) / (float)(pNextAniPos->nTick- tmpAniPos.nTick));
			tmpVec = tmpVec1 + tmpTotalVec;
		}
		else
		{
			tmpVec = *(pAniPos->pVecPos);
		}
	}
	else
	{
		if(this->m_pParentMesh)
		{
			//D3DXMatrixInverse(&this->m_pParentMesh->m_matParentInvertMat, 0, &this->m_pParentMesh->m_matMatrix);
			D3DXMatrixMultiply(&tmpMat, &m_matMatrix, &this->m_pParentMesh->m_matParentInvertMat);

			tmpVec.x = tmpMat._41;
			tmpVec.y = tmpMat._42;
			tmpVec.z = tmpMat._43;

		}
		else
		{
			tmpVec = this->m_matPos;
		}
	}

	//D3DXMatrixMultiply(&m_matAniMatrix, &tmpMat, &m_matAniMatrix);

	m_matAniMatrix._41 = tmpVec.x;
	m_matAniMatrix._42 = tmpVec.y;
	m_matAniMatrix._43 = tmpVec.z;

	return true;
}