#include "ASEParser.h"

#include "./global.h"
#include "./ASEDefine.h"
#include "./ASEMtrl.h"
#include "./ASEMesh.h"
//#include "./ASEMeshAnimation.h"
#include "./ASEMeshBiped.h"
#include "./ASEMeshObject.h"

ASEParser::ASEParser(void)
{
	this->m_nSubMtrl = 1;
}

ASEParser::~ASEParser(void)
{
}

bool ASEParser::LoadASEFile(char* filename)
{
	FileOpen(filename);

	//this->GetDataFromString("*");
	//this->GetDataFromString("{");

	if(this->GetDataFromString("*SCENE"))
	{
		this->GetDataFromString("*SCENE_FIRSTFRAME", &this->m_nStartFrame, TYPE_INT);
		this->GetDataFromString("*SCENE_LASTFRAME", &this->m_nLastFrame, TYPE_INT);
		this->GetDataFromString("*SCENE_TICKSPERFRAME", &this->m_nTickPerSec, TYPE_INT);

		this->m_nAniTickCount = this->m_nLastFrame * this->m_nTickPerSec;
	}

	if(this->GetDataFromString("*MATERIAL_LIST"))
	{
		this->GetDataFromString("*MATERIAL_COUNT", &this->m_nMaterialCount, TYPE_INT);

		for(int i = 0; i < this->m_nMaterialCount; i++)
		{
			SetMaterialData(i);

			if(this->CheckString("*SUBMATERIAL", "{"))
			{
				this->GetDataFromString("*NUMSUBMTLS", &this->m_nSubMtrl, TYPE_INT);

				for(int j = 0; j < this->m_nSubMtrl; j++)
				{
					SetSubMaterialData(i,j);
					SetDiffuseMapData(i,j);
				}
			}
			else
			{
				SetDiffuseMapDataRef(i);
			}
		}
	}

	this->m_nGeoObjectCount = 0;
	this->m_nBipedCount = 0;

	while(!feof(this->m_pStream))
	{
		if(this->GetDataFromString("*GEOMOBJECT"))
		{
			int ntmpMtrl;
			
			this->GetDataFromString("*NODE_NAME", &this->m_pString, TYPE_STRING);

			char tmpNodeName[256];

			memcpy(tmpNodeName, this->m_pString, sizeof(this->m_pString));

			this->m_pString[3] = 0;

			if(strcmp(this->m_pString, "Bip"))
			{
				SetGeoMObjectData(m_nGeoObjectCount);
				this->m_nGeoObjectCount++;
				//this->SetAnimationData();
				//continue;
			}
			else
			{
				SetGeoMBipedData(m_nBipedCount);
				m_nBipedCount++;

			}
			//SetGeoMObjectData(m_nGeoObjectCount);

			memcpy(this->m_pMeshVertex->m_chNodeName, tmpNodeName, sizeof(tmpNodeName));
			this->m_pMeshVertex->m_nTotalTick = this->m_nAniTickCount;

			if(this->GetDataFromNext("*NODE_PARENT"))
			{
				this->GetDataFromString("*NODE_PARENT", &this->m_pString, TYPE_STRING);
				memcpy(this->m_pMeshVertex->m_ParentNodeName, this->m_pString, sizeof(this->m_pString));
			}

			SetMeshData();

			if(this->CheckString("*MATERIAL_REF", "*GEOMOBJECT"))
			{
				this->GetDataFromString("*MATERIAL_REF", &ntmpMtrl, TYPE_INT);
				this->SetMaterialREF(ntmpMtrl);
				this->m_pMeshVertex->SortSubMaterialVertex();
			}
			else
			{
				//this->m_pMeshVertex->NoMaterialRefVeretex();
			}

			this->SetAnimationData();
		}

		if(feof(this->m_pStream))
			break;

		
	}

	SetAniMatrixData();

	FileClose();

	return true;
}

bool ASEParser::SetASESceneData(void)
{
	return true;
}

bool ASEParser::SetAnimationData(void)
{
	D3DXVECTOR3 *tmpVector;
	D3DXQUATERNION *tmpQuaternion, *tmpQuaternion1;

	tmpQuaternion1 = NULL;
	tmpQuaternion = NULL;

	int tmpAniTick = 0;

	//ASEMeshAnimation *pTmpMeshAni = new ASEMeshAnimation;
	//
	//this->m_pMeshAni = pTmpMeshAni;

	//this->m_vpMeshAni.push_back(pTmpMeshAni);

	if(!this->CheckString("*TM_ANIMATION", "*GEOMOBJECT"))
	{
		return false;
	}

	this->GetDataFromString("*TM_ANIMATION");
	this->GetDataFromString("*NODE_NAME", &this->m_pString, TYPE_STRING);

	memcpy(this->m_pMeshVertex->m_pAniNodeName, this->m_pString, sizeof(this->m_pString));

	if(this->CheckString("*CONTROL_POS_TRACK", "*GEOMOBJECT") ||
		this->CheckString("*CONTROL_POS_TCB", "*GEOMOBJECT") ||
		this->CheckString("*CONTROL_POS_BEZIER", "*GEOMOBJECT")
		)
	{
		this->GetDataFromString("*CONTROL_POS_TRACK");

		while(1)
		{
			tmpAniTick = 0;

			tmpVector = new D3DXVECTOR3;

			fgets(this->m_pBuffer, 256, this->m_pStream);

			sscanf(this->m_pBuffer, "%s %d %f %f %f", 
				this->m_pString, &tmpAniTick, 
				&tmpVector->x, &tmpVector->z, &tmpVector->y);	

			ST_ANIPOS *tmpAniPos = new ST_ANIPOS;

			tmpAniPos->nTick = tmpAniTick;
			tmpAniPos->pVecPos = tmpVector;

			this->m_pMeshVertex->m_mpMatPos.push_back(tmpAniPos);

			//m_pMeshAni->m_vQuatPos.push_back(tmpVector);

			//char tmp[256];

			//sprintf(tmp, "}");

			//if(!strcmp(this->m_pString, tmp))
			//{
			//	break;
			//}

			if(this->GetDataFromNext("}"))
			{
				break;
			}

			//if(this->m_nAniTickCount <= tmpAniTick)
			//	break;
		}
	}

	if(this->CheckString("*CONTROL_ROT_TRACK", "*GEOMOBJECT") ||
		this->CheckString("*CONTROL_ROT_TCB", "*GEOMOBJECT") ||
		this->CheckString("*CONTROL_ROT_BEZIER", "*GEOMOBJECT"))
	{
		this->GetDataFromString("*CONTROL_ROT_TRACK");

		while(1)
		{
			tmpAniTick = 0;

			tmpQuaternion = new D3DXQUATERNION;

			float fTmpX, fTmpY, fTmpZ, fTmpW;

			fgets(this->m_pBuffer, 256, this->m_pStream);

			sscanf(this->m_pBuffer, "%s %d %f %f %f %f", 
				this->m_pString, &tmpAniTick, 
				&fTmpX, &fTmpZ, &fTmpY, &fTmpW);		

			tmpQuaternion->x = (float)sinf(fTmpW / 2.0f) * fTmpX;
			tmpQuaternion->y = (float)sinf(fTmpW / 2.0f) * fTmpY;
			tmpQuaternion->z = (float)sinf(fTmpW / 2.0f) * fTmpZ;
			tmpQuaternion->w = (float)cosf(fTmpW / 2.0f);

			//tmpQuaternion->x = fTmpX;
			//tmpQuaternion->y = fTmpZ;
			//tmpQuaternion->z = fTmpY;
			//tmpQuaternion->w = fTmpW;

			ST_ANIROT *tmpAniRot = new ST_ANIROT;

			if(tmpQuaternion1)
			{
				D3DXQuaternionMultiply(tmpQuaternion, tmpQuaternion1, tmpQuaternion);
			}

			tmpAniRot->nTick = tmpAniTick;
			tmpAniRot->pQuatRot = tmpQuaternion;

			//tmpAniRot->nTick = tmpAniTick;
			//tmpAniRot->pQuatRot = tmpQuaternion;

			this->m_pMeshVertex->m_mpMatRot.push_back(tmpAniRot);

			tmpQuaternion1 = tmpQuaternion;

			//m_pMeshAni->m_vQuatRot.push_back(tmpQuaternion);

			//if(!strcmp(this->m_pString, "}"))
			//{
			//	break;
			//}

			if(this->GetDataFromNext("}"))
			{
				break;
			}

			//if(this->m_nAniTickCount <= tmpAniTick)
			//	break;
		}
	}

	if(this->CheckString("*CONTROL_SCALE_BEZIER", "*GEOMOBJECT"))
	{
		this->GetDataFromString("*CONTROL_SCALE_BEZIER");
	}

	return true;
}

bool ASEParser::SetMeshData(void)
{
	D3DXVECTOR3 tmpVec;

	this->GetDataFromString("*TM_ROW0", &tmpVec, TYPE_VERTEX);

	this->m_pMeshVertex->m_matMatrix._11 = tmpVec.x;
	this->m_pMeshVertex->m_matMatrix._13 = tmpVec.y;
	this->m_pMeshVertex->m_matMatrix._12 = tmpVec.z;

	this->GetDataFromString("*TM_ROW1", &tmpVec, TYPE_VERTEX);

	this->m_pMeshVertex->m_matMatrix._31 = tmpVec.x;
	this->m_pMeshVertex->m_matMatrix._33 = tmpVec.y;
	this->m_pMeshVertex->m_matMatrix._32 = tmpVec.z;

	this->GetDataFromString("*TM_ROW2", &tmpVec, TYPE_VERTEX);

	this->m_pMeshVertex->m_matMatrix._21 = tmpVec.x;
	this->m_pMeshVertex->m_matMatrix._23 = tmpVec.y;
	this->m_pMeshVertex->m_matMatrix._22 = tmpVec.z;

	this->GetDataFromString("*TM_ROW3", &tmpVec, TYPE_VERTEX);

	this->m_pMeshVertex->m_matMatrix._41 = tmpVec.x;
	this->m_pMeshVertex->m_matMatrix._43 = tmpVec.y;
	this->m_pMeshVertex->m_matMatrix._42 = tmpVec.z;

	this->GetDataFromString("*TM_POS", &tmpVec, TYPE_VERTEX);

	this->m_pMeshVertex->m_matPos.x = tmpVec.x;
	this->m_pMeshVertex->m_matPos.y = tmpVec.z;
	this->m_pMeshVertex->m_matPos.z = tmpVec.y;

	D3DXMatrixInverse(&this->m_pMeshVertex->m_matParentInvertMat, 
		0,
		&this->m_pMeshVertex->m_matMatrix);

	float tmpfloat;

	this->GetDataFromString("*TM_ROTAXIS", &tmpVec, TYPE_VERTEX);
	this->GetDataFromString("*TM_ROTANGLE", &tmpfloat, TYPE_FLOAT);

	this->m_pMeshVertex->m_matRot.x = (float)sinf( tmpfloat / 2.0f ) * tmpVec.x;
	this->m_pMeshVertex->m_matRot.y = (float)sinf( tmpfloat / 2.0f ) * tmpVec.z;
	this->m_pMeshVertex->m_matRot.z = (float)sinf( tmpfloat / 2.0f ) * tmpVec.y;
	this->m_pMeshVertex->m_matRot.w = (float)cosf( tmpfloat / 2.0f );

	this->GetDataFromString("*MESH_NUMVERTEX", &m_nTotalVertex, TYPE_INT);
	this->GetDataFromString("*MESH_NUMFACES", &m_nTotalFace, TYPE_INT);

	this->GetDataFromString("*MESH_VERTEX_LIST");

	this->m_pMeshVertex->m_nFaceCount = this->m_nTotalFace;

	for(int i = 0; i < m_nTotalVertex; i++)
	{
		this->SetVertexData();
	}

	this->GetDataFromString("*MESH_FACE_LIST");

	for(int i = 0 ; i < m_nTotalFace; i++)
	{
		this->SetVertexFaceListData(i);
	}

	if(this->CheckString("*MESH_TVERTLIST", "*MESH_NORMALS"))
	{
		this->GetDataFromString("*MESH_NUMTVERTEX", &m_nTotalTVertex, TYPE_INT);
		this->GetDataFromString("*MESH_TVERTLIST");

		for(int i = 0; i < this->m_nTotalTVertex; i++)
		{
			this->SetTextureUVData();
		}

		this->GetDataFromString("*MESH_NUMTVFACES", &m_nTotalTFace, TYPE_INT);
		this->GetDataFromString("*MESH_TFACELIST");

		for(int i = 0; i < this->m_nTotalTFace; i++)
		{
			this->SetTextureUVFaceData();
		}	
	}

	if(this->CheckString("*MESH_CVERTLIST", "*MESH_NORMALS"))
	{
		this->GetDataFromString("*MESH_NUMCVERTEX", &m_nTotalCTertex, TYPE_INT);
		this->GetDataFromString("*MESH_CVERTLIST");

		for(int i = 0; i < this->m_nTotalCTertex ; i++)
		{
			this->SetVertexColorData();
		}

		this->GetDataFromString("*MESH_NUMCVFACES", &m_nTotalCFace, TYPE_INT);
		this->GetDataFromString("*MESH_CFACELIST");

		for(int i = 0; i < this->m_nTotalCFace ; i++)
		{
			this->SetVertexColorFaceData();
		}
	}

	this->GetDataFromString("*MESH_NORMALS");

	for(int i = 0; i < m_nTotalFace; i++)
	{
		this->SetFaceNormalData();
	}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

	//this->GetDataFromString("*MESH_NUMVERTEX", &m_nTotalVertex, TYPE_INT);
	//this->GetDataFromString("*MESH_NUMFACES", &m_nTotalFace, TYPE_INT);

	//this->GetDataFromString("*MESH_VERTEX_LIST");

	//int nVertexNum = 0;
	//D3DXVECTOR3 tmpVector;

	//for(int i = 0; i < m_nTotalVertex; i++)
	//{
	//	fgets(this->m_pBuffer, 255, this->m_pStream);
	//	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//		this->m_pString, &nVertexNum, 
	//		&tmpVector.x, &tmpVector.z, &tmpVector.y);
	//	
	//	this->SetVertexData(nVertexNum, &tmpVector);
	//}

	//this->GetDataFromString("*MESH_FACE_LIST");

	//int nIndex1, nIndex2, nIndex3, tmpInt;

	//for(int i = 0; i < m_nTotalFace; i++)
	//{
	//	fgets(this->m_pBuffer, 255, this->m_pStream);
	//	sscanf(this->m_pBuffer, "%s %s %s %d %s %d %s %d %s %d %s %d %s %d %s %d", 
	//		this->m_pString, this->m_pString,
	//		this->m_pString, &nIndex1, 
	//		this->m_pString, &nIndex3,
	//		this->m_pString, &nIndex2,
	//		this->m_pString, &tmpInt,
	//		this->m_pString, &tmpInt,
	//		this->m_pString, &tmpInt,
	//		this->m_pString, &tmpInt,
	//		this->m_pString, &tmpInt);
	//	
	//	this->SetIndexedVertexData(nIndex1);
	//	this->SetIndexedVertexData(nIndex2);
	//	this->SetIndexedVertexData(nIndex3);
	//}
	
////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

	//this->GetDataFromString("*MESH_NUMTVERTEX", &m_nTotalTVertex, TYPE_INT);

	//this->GetDataFromString("*MESH_TVERTLIST");

	//for(int i = 0; i < this->m_nTotalTVertex; i++)
	//{
	//	D3DXVECTOR3 tmpVec;

	//	fgets(this->m_pBuffer, 255, this->m_pStream);
	//	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//					this->m_pString,
	//					&tmpInt,
	//					&tmpVec.x,
	//					&tmpVec.y,
	//					&tmpVec.z);

	//	//tmpVec.x = 1.0f - tmpVec.x;
	//	tmpVec.y = 1.0f - tmpVec.y;

	//	this->SetTVertexData(tmpInt, &tmpVec);
	//}

	//this->GetDataFromString("*MESH_NUMTVFACES", &m_nTotalTFace, TYPE_INT);

	//this->GetDataFromString("*MESH_TFACELIST");

	//for(int i = 0; i < this->m_nTotalTFace; i++)
	//{
	//	D3DXVECTOR3 tmpVec;

	//	int tmp1, tmp2, tmp3;

	//	fgets(this->m_pBuffer, 255, this->m_pStream);
	//	sscanf(this->m_pBuffer, "%s %d %d %d %d", 
	//					this->m_pString,
	//					&tmpInt,
	//					&tmp1,
	//					&tmp3,
	//					&tmp2);

	//	this->SetIndexedTFaceData(tmp1);
	//	this->SetIndexedTFaceData(tmp2);
	//	this->SetIndexedTFaceData(tmp3);
	//}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////

	//D3DXVECTOR3 tmpVecNormal1, tmpVecNormal2, tmpVecNormal3;

	//if(this->GetDataFromString("*MESH_NORMALS"))
	//{
	//	for(int i = 0; i < m_nTotalFace; i++)
	//	{
	//		fgets(this->m_pBuffer, 255, this->m_pStream);
	//		sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//			this->m_pString, 
	//			&tmpInt,
	//			this->m_pString, 
	//			this->m_pString, 
	//			this->m_pString);

	//		fgets(this->m_pBuffer, 255, this->m_pStream);
	//		sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//			this->m_pString,
	//			&tmpInt,
	//			&tmpVecNormal1.x, 
	//			&tmpVecNormal1.z, 
	//			&tmpVecNormal1.y);

	//		//this->SetFaceNormalData(&tmpVecNormal);

	//		fgets(this->m_pBuffer, 255, this->m_pStream);
	//		sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//			this->m_pString, 
	//			&tmpInt,
	//			&tmpVecNormal3.x, 
	//			&tmpVecNormal3.z, 
	//			&tmpVecNormal3.y);

	//		//this->SetFaceNormalData(&tmpVecNormal);

	//		fgets(this->m_pBuffer, 255, this->m_pStream);
	//		sscanf(this->m_pBuffer, "%s %d %f %f %f", 
	//			this->m_pString, 
	//			&tmpInt,
	//			&tmpVecNormal2.x, 
	//			&tmpVecNormal2.z, 
	//			&tmpVecNormal2.y);

	//		this->SetFaceNormalData(&tmpVecNormal1);
	//		this->SetFaceNormalData(&tmpVecNormal2);
	//		this->SetFaceNormalData(&tmpVecNormal3);
	//	}
	//}

	return true;
}

//bool ASEParser::SetASEVertexData(void)
//{
//	return true;
//}
//
//bool ASEParser::SetASEIndexedVertexData(void)
//{
//	return true;
//}

ASEMtrl* const ASEParser::GetFineMaterial(int nIndex)
{
	std::map<int, ASEMtrl*>::iterator itPos;

	itPos = this->m_mpMtrl.find(nIndex);

	return itPos->second;	
}

LPDIRECT3DTEXTURE9 ASEParser::CreateMeshTexture(LPCTSTR filename)
{
	LPDIRECT3DTEXTURE9 pTexture;
	
	D3DXCreateTextureFromFileEx( g_pD3device,
									filename,
									D3DX_DEFAULT,
									D3DX_DEFAULT,
									D3DX_DEFAULT,
									//D3DX_FROM_FILE,
									0,
									D3DFMT_UNKNOWN, //D3DFMT_FROM_FILE, //
									D3DPOOL_MANAGED,
									//D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
									//D3DX_FILTER_TRIANGLE|D3DX_FILTER_MIRROR, 
									D3DX_FILTER_LINEAR,   //D3DX_FILTER_LINEAR,
									D3DX_FILTER_LINEAR,   //D3DX_FILTER_LINEAR,
									MASKCOLOR,     // 투명컬러키
									NULL,
									NULL,
									&pTexture );

	return pTexture;
}

///////////////////////////////////////////////////////////////////////////////////////
//마테리얼 정보 저장
///////////////////////////////////////////////////////////////////////////////////////

bool ASEParser::SetMaterialData(int nIndex)
{
	//this->GetDataFromString("*MATERIAL_COUNT", &m_nMaterialCount, TYPE_INT);

	//for(int i = 0; i < this->m_nMaterialCount; i++)
	//{
	//int nMaterialNum;

	D3DXVECTOR3 tmpVec;

	memset(&tmpVec, 0, sizeof(tmpVec));

	this->AddMaterialData(nIndex);

	//this->GetDataFromString("*MATERIAL");
	//nMaterialNum = this->SetMaterialData(nIndex);

	this->GetDataFromString("*MATERIAL_AMBIENT", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nIndex)->m_Mtrl.Ambient.a = 1.0f;
	this->GetFineMaterial(nIndex)->m_Mtrl.Ambient.r = tmpVec.x;
	this->GetFineMaterial(nIndex)->m_Mtrl.Ambient.g = tmpVec.y;
	this->GetFineMaterial(nIndex)->m_Mtrl.Ambient.b = tmpVec.z;

	this->GetDataFromString("*MATERIAL_DIFFUSE", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nIndex)->m_Mtrl.Diffuse.a = 1.0f;
	this->GetFineMaterial(nIndex)->m_Mtrl.Diffuse.r = tmpVec.x;
	this->GetFineMaterial(nIndex)->m_Mtrl.Diffuse.g = tmpVec.y;
	this->GetFineMaterial(nIndex)->m_Mtrl.Diffuse.b = tmpVec.z;

	this->GetDataFromString("*MATERIAL_SPECULAR", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nIndex)->m_Mtrl.Specular.a = 1.0f;
	this->GetFineMaterial(nIndex)->m_Mtrl.Specular.r = tmpVec.x;
	this->GetFineMaterial(nIndex)->m_Mtrl.Specular.g = tmpVec.y;
	this->GetFineMaterial(nIndex)->m_Mtrl.Specular.b = tmpVec.z;

	//}

	return true;
}

bool ASEParser::SetSubMaterialData(int nMtrlIndex, int nIndex)
{
	//this->GetDataFromString("*NUMSUBMTLS", &this->m_nSubMtrl, TYPE_INT);
	//
	//for(int i = 0; i < this->m_nSubMtrl; i++)
	//{
		//char Filetmp[256];
		//memset(Filetmp, 0, sizeof(Filetmp));

	D3DXVECTOR3 tmpVec;

	memset(&tmpVec, 0, sizeof(tmpVec));

	this->GetDataFromString("*SUBMATERIAL");

	ASEMtrl *tmpMtrl;

	tmpMtrl = this->GetFineMaterial(nMtrlIndex);

	tmpMtrl->SetSubMaterialCount(this->m_nSubMtrl);

	tmpMtrl->AddSubMaterial(nIndex);

	this->GetDataFromString("*MATERIAL_AMBIENT", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Ambient.a = 255.0f;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Ambient.r = tmpVec.x;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Ambient.g = tmpVec.y;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Ambient.b = tmpVec.z;

	this->GetDataFromString("*MATERIAL_DIFFUSE", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Diffuse.a = 255.0f;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Diffuse.r = tmpVec.x;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Diffuse.g = tmpVec.y;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Diffuse.b = tmpVec.z;

	this->GetDataFromString("*MATERIAL_SPECULAR", &tmpVec, TYPE_VERTEX);

	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Specular.a = 255.0f;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Specular.r = tmpVec.x;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Specular.g = tmpVec.y;
	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubMtrl.Specular.b = tmpVec.z;
	//}

	return true;
}

bool ASEParser::SetDiffuseMapData(int nMtrlIndex, int nIndex)
{
	this->GetDataFromString("*BITMAP", &this->m_pString, TYPE_STRING);

	this->GetFineMaterial(nMtrlIndex)->FineSubMaterial(nIndex)->SubTexture = this->CreateMeshTexture(this->m_pString);

	return true;
}

bool ASEParser::SetDiffuseMapDataRef(int nIndex)
{
	this->GetDataFromString("*BITMAP", &this->m_pString, TYPE_STRING);

	this->GetFineMaterial(nIndex)->m_pTexture = this->CreateMeshTexture(this->m_pString);

	return true;
}

int ASEParser::AddMaterialData(int nIndex)
{
	ASEMtrl* tmpASEMtrl = new ASEMtrl;

	this->m_mpMtrl.insert(std::make_pair(nIndex, tmpASEMtrl));

	return nIndex;
}

ASEMesh* ASEParser::SetGeoMObjectData(int nIndex)
{
	ASEMesh* tmpMeshVertex = new ASEMeshObject;

	this->m_mpMeshVertex.insert(std::make_pair(nIndex, tmpMeshVertex));

	this->m_pMeshVertex = tmpMeshVertex;

	return tmpMeshVertex;
}

ASEMesh* ASEParser::SetGeoMBipedData(int nIndex)
{
	ASEMesh* tmpMeshVertex = new ASEMeshBiped;

	this->m_mpMeshBiped.insert(std::make_pair(nIndex, tmpMeshVertex));

	this->m_pMeshVertex = tmpMeshVertex;

	return tmpMeshVertex;
}

bool ASEParser::SetVertexData(void)
{
	int nVertexNum = 0;

	D3DXVECTOR3 v0;

	D3DXVECTOR3* tmpVector = new D3DXVECTOR3;

	//memset(tmpVector, 0, sizeof(tmpVector));

	fgets(this->m_pBuffer, 256, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString, &nVertexNum, 
		&tmpVector->x, &tmpVector->z, &tmpVector->y);

	D3DXVec3TransformCoord(&v0, tmpVector, &m_pMeshVertex->m_matParentInvertMat);

	tmpVector->x = v0.x;
	tmpVector->y = v0.y;
	tmpVector->z = v0.z;

	this->m_pMeshVertex->m_mpVerTex.insert(std::make_pair(nVertexNum, tmpVector));	

	return true;
}

bool ASEParser::SetVertexFaceListData(int nIndex)
{
	

	//for(int i = 0; i < m_nTotalFace; i++)
	//{
		int nIndex1, nIndex2, nIndex3, nMtrl, tmpInt;

		fgets(this->m_pBuffer, 255, this->m_pStream);
		sscanf(this->m_pBuffer, "%s %s %s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d", 
			this->m_pString, this->m_pString,
			this->m_pString, &nIndex1, 
			this->m_pString, &nIndex3,
			this->m_pString, &nIndex2,
			this->m_pString, &tmpInt,
			this->m_pString, &tmpInt,
			this->m_pString, &tmpInt,
			this->m_pString, &tmpInt,
			this->m_pString, &nMtrl);
	
		
		this->ConvertIndextoVertex(nIndex, nIndex1, nIndex2, nIndex3, nMtrl);

		this->m_pMeshVertex->m_mnSubMtrl.insert(std::make_pair(nIndex, nMtrl));
	//}

	return true;
}

D3DXVECTOR3* ASEParser::GetVertexIndex(int nIndex)
{
	std::map<int, D3DXVECTOR3*>::iterator itPos;
	
	itPos = this->m_pMeshVertex->m_mpVerTex.find(nIndex);

	return itPos->second;
}

bool ASEParser::ConvertIndextoVertex(int nIndex, int nIndex1, int nIndex2, int nIndex3, int nMtrl)
{
	ST_MESHFACE* tmpMeshFace = new ST_MESHFACE;

	tmpMeshFace->pVec1 = GetVertexIndex(nIndex1);
	tmpMeshFace->pVec2 = GetVertexIndex(nIndex2);
	tmpMeshFace->pVec3 = GetVertexIndex(nIndex3);

	tmpMeshFace->nMtrl = nMtrl;

	this->m_pMeshVertex->m_mpIndexedVerTex.insert(std::make_pair(nIndex, tmpMeshFace));

	return true;
}

bool ASEParser::SetTextureUVData(void)
{
	int nIndex;
	D3DXVECTOR2 *tmpVec = new D3DXVECTOR2;

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f", 
					this->m_pString,
					&nIndex,
					&tmpVec->x,
					&tmpVec->y);

	//tmpVec.x = 1.0f - tmpVec.x;
	tmpVec->y = 1.0f - tmpVec->y;

	this->m_pMeshVertex->m_mpTVertex.insert(std::make_pair(nIndex, tmpVec));

	return true;
}

bool ASEParser::SetTextureUVFaceData(void)
{
	D3DXVECTOR3 tmpVec;

	int tmp1, tmp2, tmp3, tmpIndex;

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %d %d %d", 
					this->m_pString,
					&tmpIndex,
					&tmp1,
					&tmp3,
					&tmp2);

	this->ConvertIndextoTextureUV(tmpIndex, tmp1, tmp2, tmp3);

	return true;
}

D3DXVECTOR2* ASEParser::GetTextureUVIndex(int nIndex)
{
	std::map<int, D3DXVECTOR2*>::iterator itPos;

	itPos = this->m_pMeshVertex->m_mpTVertex.find(nIndex);

	return itPos->second;
	
}

bool ASEParser::ConvertIndextoTextureUV(int nIndex, int nIndex1, int nIndex2, int nIndex3)
{
	ST_TEXTUREFACE* tmpTextureFace = new ST_TEXTUREFACE;

	tmpTextureFace->pVec1 = this->GetTextureUVIndex(nIndex1);
	tmpTextureFace->pVec2 = this->GetTextureUVIndex(nIndex2);
	tmpTextureFace->pVec3 = this->GetTextureUVIndex(nIndex3);

	this->m_pMeshVertex->m_mpIndexedTFace.insert(std::make_pair(nIndex, tmpTextureFace));

	return true;
}

bool ASEParser::SetFaceNormalData(void)
{
	int nIndex, tmpInt;
	D3DXVECTOR3* tmpVecNormal = new D3DXVECTOR3[3];

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString, 
		&nIndex,
		this->m_pString, 
		this->m_pString, 
		this->m_pString);

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString,
		&tmpInt,
		&tmpVecNormal[0].x, 
		&tmpVecNormal[0].z, 
		&tmpVecNormal[0].y);

	//this->SetFaceNormalData(&tmpVecNormal);

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString, 
		&tmpInt,
		&tmpVecNormal[2].x, 
		&tmpVecNormal[2].z, 
		&tmpVecNormal[2].y);

	//this->SetFaceNormalData(&tmpVecNormal);

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString, 
		&tmpInt,
		&tmpVecNormal[1].x, 
		&tmpVecNormal[1].z, 
		&tmpVecNormal[1].y);

	SetVertexNormalData(nIndex, &tmpVecNormal[0], &tmpVecNormal[1], &tmpVecNormal[2]);

	return true;
}

bool ASEParser::SetVertexNormalData(int nIndex, D3DXVECTOR3* pVec1, D3DXVECTOR3* pVec2, D3DXVECTOR3* pVec3)
{
	ST_FACENORMAL* tmpFaceNormal = new ST_FACENORMAL;

	tmpFaceNormal->pVec1 = pVec1;
	tmpFaceNormal->pVec2 = pVec2;
	tmpFaceNormal->pVec3 = pVec3;

	this->m_pMeshVertex->m_mpFaceNormal.insert(std::make_pair(nIndex, tmpFaceNormal));

	return true;
}

bool ASEParser::SetMaterialREF(int nIndex)
{
	this->m_pMeshVertex->m_pMeshmtrl = this->GetFineMaterial(nIndex);

	return true;
}

bool ASEParser::SetSortVertex(void)
{
	return true;
}

ASEMesh* const ASEParser::GetFineSubMeshVertex(int nIndex)
{
	std::map<int, ASEMesh*>::iterator itPos;

	itPos = this->m_mpMeshVertex.find(nIndex);

	return itPos->second;	
}

bool ASEParser::SetVertexColorData(void)
{
	int nIndex, tmpInt;
	D3DXVECTOR3* tmpVecColor = new D3DXVECTOR3[3];

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %f %f %f", 
		this->m_pString, 
		&nIndex,
		&tmpVecColor->x, 
		&tmpVecColor->z, 
		&tmpVecColor->y);
	
	this->m_pMeshVertex->m_mpCVertex.insert(std::make_pair(nIndex, tmpVecColor));

	return true;
}


bool ASEParser::SetVertexColorFaceData(void)
{
	int nIndex, nIndex1, nIndex2, nIndex3;

	fgets(this->m_pBuffer, 255, this->m_pStream);
	sscanf(this->m_pBuffer, "%s %d %d %d %d", 
		this->m_pString, 
		&nIndex,
		&nIndex1, 
		&nIndex3, 
		&nIndex2);	

	this->ConvertIndextoVertexColor(nIndex, nIndex1, nIndex2, nIndex3);

	return true;
}

bool ASEParser::ConvertIndextoVertexColor(int nIndex, int nIndex1, int nIndex2, int nIndex3)
{
	ST_FACECOLOR* ptmpFaceColor = new ST_FACECOLOR;

	ptmpFaceColor->pVec1 = this->GetFaceColorIndex(nIndex1);
	ptmpFaceColor->pVec2 = this->GetFaceColorIndex(nIndex2);
	ptmpFaceColor->pVec3 = this->GetFaceColorIndex(nIndex3);

	this->m_pMeshVertex->m_mpIndexedCVertex.insert(std::make_pair(nIndex, ptmpFaceColor));

	return true;
}

D3DXVECTOR3* ASEParser::GetFaceColorIndex(int nIndex)
{
	std::map<int, D3DXVECTOR3*>::iterator itPos;

	itPos = this->m_pMeshVertex->m_mpCVertex.find(nIndex);

	return itPos->second;
}

ASEMeshBiped* ASEParser::GetFineBiped(int nIndex)
{
	std::map<int, ASEMesh*>::iterator itPos;

	itPos = this->m_mpMeshBiped.find(nIndex);

	return (ASEMeshBiped*)(itPos->second);
}

ASEMeshObject* ASEParser::GetFineMesh(int nIndex)
{
	std::map<int, ASEMesh*>::iterator itPos;

	itPos = this->m_mpMeshVertex.find(nIndex);

	return (ASEMeshObject*)(itPos->second);
}


bool ASEParser::SetAniMatrixData(void)
{
	std::map<int, ASEMesh*>::iterator itAseMesh,itAseVertex, itAseBiped, itAseMainBiped;

	for(itAseMainBiped = this->m_mpMeshBiped.begin(); itAseMainBiped != this->m_mpMeshBiped.end(); itAseMainBiped++)
	{
		for(itAseBiped = this->m_mpMeshBiped.begin(); itAseBiped != this->m_mpMeshBiped.end(); itAseBiped++)
		{
			if(!strcmp(itAseMainBiped->second->m_ParentNodeName, itAseBiped->second->m_chNodeName))
			{
				itAseMainBiped->second->m_pParentMesh = itAseBiped->second;
			}
		}
	}

	for(itAseMesh = this->m_mpMeshVertex.begin(); itAseMesh != this->m_mpMeshVertex.end() ; itAseMesh++)
	{
		for(itAseBiped = this->m_mpMeshBiped.begin(); itAseBiped != this->m_mpMeshBiped.end() ; itAseBiped++)
		{
			if(!strcmp(itAseMesh->second->m_ParentNodeName, itAseBiped->second->m_chNodeName ))
			{
				itAseMesh->second->m_pParentMesh = itAseBiped->second;
			}
			
		}
	}

	return true;
}