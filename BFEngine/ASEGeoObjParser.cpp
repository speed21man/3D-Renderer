#include "ASEGeoObjParser.h"

CASEGeoObjParser::CASEGeoObjParser(void)
:m_stAseMesh(NULL)
,m_stAseMeshAni(NULL)
{
}

CASEGeoObjParser::CASEGeoObjParser(FILE *pFile)
:CASEParser(pFile)
,m_stAseMesh(NULL)
,m_stAseMeshAni(NULL)
{

}

CASEGeoObjParser::~CASEGeoObjParser(void)
{
	SAFEDEL(this->m_stAseMesh);
}

void CASEGeoObjParser::ErrorMsg(int nErrIndex)
{
	switch(nErrIndex)
	{
	case 0:
		MessageBox(NULL, "NODE_TM 파싱 중 오류가 발생했습니다.","파싱 오류", MB_OK);
		break;

	case 1:
		MessageBox(NULL, "MESH 파싱 중 오류가 발생했습니다.","파싱 오류", MB_OK);
		break;
	}

	_asm {
		int 3;
	}
}

bool CASEGeoObjParser::ParsingGeoObjData(void)
{
	this->InitGeoObject();

	// 현재 노드이름을 확인한다.
	this->GetDataFromString("*NODE_NAME", &this->m_GeoObject.strNodeName, TYPE_STRING);

	// 부모 노드를 확인한다 없을시 빈 문자열 값을 넘긴다.
	if(this->GetDataFromNext("*NODE_PARENT"))
		this->GetDataFromString("*NODE_PARENT", &this->m_GeoObject.strParentName, TYPE_STRING);
	else
		memset(&this->m_GeoObject.strParentName, 0, sizeof(this->m_GeoObject.strParentName));

	// *NODE_TM 이 없을시 에러 코드 0 발생
	if(!this->GetDataFromNext("*NODE_TM"))
		this->ErrorMsg(0);
	else
	{
		this->GetDataFromString("*NODE_TM");
		this->ParsingNodeTM();
	}

	this->GetDataFromString("}");

	// *MESH 이 없을시 에러 코드 1 발생
	if(!this->GetDataFromNext("*MESH"))
		this->ErrorMsg(1);

	// 메쉬 생성
	SAFENEW(m_stAseMesh, ST_ASEPARSER_MESH);
	this->InitMeshData();
	this->ParsingMesh();

	return true;
}

bool CASEGeoObjParser::ParsingNodeTM(void)
{
	this->GetDataFromString("*INHERIT_POS", &this->m_GeoObject.vt3inhPos, TYPE_VERTEX);
	this->GetDataFromString("*INHERIT_ROT", &this->m_GeoObject.vt3inhRot, TYPE_VERTEX);
	this->GetDataFromString("*INHERIT_SCL", &this->m_GeoObject.vt3inhScl, TYPE_VERTEX);

	this->GetDataFromString("*TM_ROW0", &this->m_GeoObject.matVecGeoObj[0], TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_ROW1", &this->m_GeoObject.matVecGeoObj[2], TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_ROW2", &this->m_GeoObject.matVecGeoObj[1], TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_ROW3", &this->m_GeoObject.matVecGeoObj[3], TYPE_ASEVERTEX);

	this->GetDataFromString("*TM_POS", &this->m_GeoObject.vt3Pos, TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_ROTAXIS", &this->m_GeoObject.vt3RotAxis, TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_SCALE", &this->m_GeoObject.vt3Scale, TYPE_ASEVERTEX);
	this->GetDataFromString("*TM_SCALEAXIS", &this->m_GeoObject.vt3ScaleAxis, TYPE_ASEVERTEX);

	return true;
}

bool CASEGeoObjParser::ParsingMesh(void)
{
	this->GetDataFromString("*MESH_NUMVERTEX", &this->m_stAseMesh->nMeshVertexCount, TYPE_INT);
	this->GetDataFromString("*MESH_NUMFACES", &this->m_stAseMesh->nMeshFaceCount, TYPE_INT);

	if(this->GetDataFromNext("*MESH_VERTEX_LIST"))
	{
		this->GetDataFromString("*MESH_VERTEX_LIST");
		this->ParsingMeshVertexList();
		this->GetDataFromString("}");
	}

	if(this->GetDataFromNext("*MESH_NUMTVERTEX"))
	{
		this->GetDataFromString("*MESH_NUMTVERTEX");
		if(this->ParsingMeshTextureVertexList())
			this->GetDataFromString("}");
	}
	else
	{
		this->m_stAseMesh->vt3TVertexList= NULL;
		this->m_stAseMesh->vt3TFaceList = NULL;
	}

	if(this->GetDataFromNext("*MESH_NORMALS"))
	{
		this->GetDataFromString("*MESH_NORMALS");
		this->ParsingMeshNormal();
		this->GetDataFromString("}");
	}
	else
	{
		this->m_stAseMesh->vt3MeshNormals = NULL;
	}

	this->m_GeoObject.stAseMesh = this->m_stAseMesh;

	// 공백
	//this->GetDataFromString("}");
	this->GetDataFromString("*PROP_MOTIONBLUR");
	this->GetDataFromString("*PROP_CASTSHADOW");
	this->GetDataFromString("*PROP_RECVSHADOW");

	// 애니메이션 정보 파싱
	if(this->GetDataFromNext("*TM_ANIMATION"))
	{
		SAFENEW(m_stAseMeshAni, ST_ASEPARSER_MESHANI);
		this->InitMeshAniData();

		this->GetDataFromString("*TM_ANIMATION");
		this->ParsingMeshAnimation();
		this->GetDataFromString("}");
	}

	if(this->GetDataFromNext("*MATERIAL_REF"))
	{
		this->GetDataFromString("*MATERIAL_REF", &this->m_GeoObject.nMtrlREF, TYPE_INT);
	}

	if(this->GetDataFromNext("*WIREFRAME_COLOR"))
	{
		this->GetDataFromString("*WIREFRAME_COLOR", &this->m_GeoObject.vt3WireFrame, TYPE_VERTEX);
	}

	return true;
}

bool CASEGeoObjParser::ParsingMeshVertexList(void)
{
	D3DXVECTOR3 *vt3MeshVertex = CreateD3DXVector3(this->m_stAseMesh->nMeshVertexCount);

	for(int i = 0 ; i < this->m_stAseMesh->nMeshVertexCount ; i++)
	{
		this->GetASEFileVertex3Data(&vt3MeshVertex[i]);
	}

	D3DXVECTOR4 *vt4MeshFace = this->CreateD3DXVector4(this->m_stAseMesh->nMeshFaceCount);

	for(int i = 0 ; i < this->m_stAseMesh->nMeshVertexCount ; i++)
	{
		this->GetASEFileVertex4Data(&vt4MeshFace[i]);
	}

	this->m_stAseMesh->vt3MeshVertexList = vt3MeshVertex;
	this->m_stAseMesh->vt4MeshFaceList = vt4MeshFace;

	return true;
}

bool CASEGeoObjParser::ParsingMeshTextureVertexList(void)
{
	this->GetDataFromString("*MESH_NUMTVERTEX", &this->m_stAseMesh->nTextureVertexCount, TYPE_INT);
		
	// nTextureVertexCount == 0 이 아닐 경우에만 실행
	if(!this->m_stAseMesh->nTextureVertexCount)
	{
		this->m_stAseMesh->vt3TVertexList= NULL;
		this->m_stAseMesh->vt3TFaceList = NULL;
		return false;
	}

	D3DXVECTOR3 *vt3TextureVertex = CreateD3DXVector3(this->m_stAseMesh->nTextureVertexCount);

	for(int i = 0 ; i < this->m_stAseMesh->nTextureVertexCount ; i++)
	{
		this->GetASEFileVertex3Data(&vt3TextureVertex[i]);
	}

	this->GetDataFromString("*MESH_NUMTVFACES", &this->m_stAseMesh->nTextureFaceCount, TYPE_INT);

	D3DXVECTOR3 *vt3TextureFace = CreateD3DXVector3(this->m_stAseMesh->nTextureFaceCount);

	for(int i = 0 ; i < this->m_stAseMesh->nTextureFaceCount ; i++)
	{
		this->GetASEFileVertex3Data(&vt3TextureFace[i]);
	}

	this->m_stAseMesh->vt3TVertexList = vt3TextureVertex;
	this->m_stAseMesh->vt3TFaceList= vt3TextureFace;

	return true;
}

bool CASEGeoObjParser::ParsingMeshNormal(void)
{
	this->m_stAseMesh->nNormalCount = this->m_stAseMesh->nMeshFaceCount * 3;

	if(!this->m_stAseMesh->nNormalCount)
	{
		this->m_stAseMesh->vt3MeshNormals= NULL;
		return false;
	}

	// 각 버텍스의 노멀 정보기 때문에 face에서 3을 곱해야 한다.
	D3DXVECTOR3 *vt3VertexNormal = CreateD3DXVector3(this->m_stAseMesh->nMeshFaceCount * 3);

	for(int i = 0 ; i < this->m_stAseMesh->nMeshFaceCount; i++)
	{
		this->GetASEFileSkipData();
		this->GetASEFileVertex3Data(&vt3VertexNormal[ i * 3 ] );
		this->GetASEFileVertex3Data(&vt3VertexNormal[ i * 3 ] + 1 );
		this->GetASEFileVertex3Data(&vt3VertexNormal[ i * 3 ] + 2 );
	}

	this->m_stAseMesh->vt3MeshNormals = vt3VertexNormal;

	return true;
}

bool CASEGeoObjParser::ParsingMeshAnimation(void)
{
	this->GetDataFromString("*NODE_NAME", &this->m_stAseMeshAni->NodeName, TYPE_STRING);

	ST_ANI_VERTEXPOS *vt3AniPos = NULL;
	int nPosCount, nRotCount, nSclCount;

	nPosCount = 0;

	if(this->GetDataFromNext("*CONTROL_POS_TRACK") ||
		this->GetDataFromNext("*CONTROL_POS_TCB") ||
		this->GetDataFromNext("*CONTROL_POS_BEZIER"))
	{
		this->GetASEFileSkipData();
	
		while(1)
		{
			if(!vt3AniPos)
				vt3AniPos = new ST_ANI_VERTEXPOS;
			else
				vt3AniPos = (ST_ANI_VERTEXPOS*)realloc(vt3AniPos, sizeof(ST_ANI_VERTEXPOS) * (nPosCount + 1));

			this->GetASEFileVertex3Data(&vt3AniPos->vt3AniPos, &vt3AniPos->nPosFrame);

			nPosCount++;

			if(this->GetDataFromNext("}"))
			{
				this->m_stAseMeshAni->pAniPos = vt3AniPos;
				this->m_stAseMeshAni->nAniPosCount = nPosCount;
				break;
			}
		}
	}

	ST_ANI_QUATROT *vt3AniRot = NULL;
	nRotCount = 0;

	if(this->GetDataFromNext("*CONTROL_ROT_TRACK") ||
		this->GetDataFromNext("*CONTROL_ROT_TCB") ||
		this->GetDataFromNext("*CONTROL_ROT_BEZIER"))
	{
		this->GetASEFileSkipData();
	
		while(1)
		{
			if(!vt3AniRot)
				vt3AniRot = new ST_ANI_QUATROT;
			else
				vt3AniRot = (ST_ANI_QUATROT*)realloc(vt3AniRot, sizeof(ST_ANI_QUATROT) * (nRotCount + 1));

			this->GetASEFileQuaternionData(&vt3AniRot->qtRot, &vt3AniRot->nRotFrame);
	
			nRotCount++;

			if(this->GetDataFromNext("}"))
			{
				this->m_stAseMeshAni->pAniRot = vt3AniRot;
				this->m_stAseMeshAni->nAniRotCount = nRotCount;
				break;
			}
		}
	}

	if(this->GetDataFromNext("*CONTROL_SCALE_BEZIER"))
	{
		this->GetASEFileSkipData();

		while(1)
		{
			if(this->GetDataFromNext("}"))
				break;
		}
	}
	
	this->m_GeoObject.stAseMeshAni = this->m_stAseMeshAni;

	return true;
}

bool CASEGeoObjParser::InitGeoObject(void)
{
	memset(&this->m_GeoObject.strNodeName, 0, sizeof(this->m_GeoObject.strNodeName));
	memset(&this->m_GeoObject.strParentName, 0, sizeof(this->m_GeoObject.strParentName));

	memset(&this->m_GeoObject.vt3inhPos, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3inhRot, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3inhScl, 0, sizeof(D3DXVECTOR3));

	memset(&this->m_GeoObject.matVecGeoObj, 0, sizeof(this->m_GeoObject.matVecGeoObj));

	memset(&this->m_GeoObject.vt3Pos, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3RotAxis, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3Scale, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3ScaleAxis, 0, sizeof(D3DXVECTOR3));
	memset(&this->m_GeoObject.vt3WireFrame, 0, sizeof(D3DXVECTOR3));

	this->m_GeoObject.stAseMesh = NULL;
	this->m_GeoObject.stAseMeshAni = NULL;

	this->m_stAseMesh = NULL;
	this->m_stAseMeshAni = NULL;

	this->m_GeoObject.nMtrlREF = -1;

	return true;
}

bool CASEGeoObjParser::InitMeshData(void)
{
	this->m_stAseMesh->nMeshFaceCount = 0;
	this->m_stAseMesh->nMeshVertexCount = 0;
	this->m_stAseMesh->nNormalCount = 0;
	this->m_stAseMesh->nTextureFaceCount = 0;
	this->m_stAseMesh->nTextureVertexCount = 0;

	this->m_stAseMesh->vt3MeshNormals = NULL;
	this->m_stAseMesh->vt3MeshVertexList = NULL;
	this->m_stAseMesh->vt3TFaceList = NULL;
	this->m_stAseMesh->vt3TVertexList = NULL;
	this->m_stAseMesh->vt4MeshFaceList = NULL;

	return true;
}

bool CASEGeoObjParser::InitMeshAniData(void)
{
	this->m_stAseMeshAni->nAniPosCount = 0;
	this->m_stAseMeshAni->nAniRotCount = 0;
	this->m_stAseMeshAni->nAniSclCount = 0;

	memset(&this->m_stAseMeshAni->NodeName, 0, sizeof(this->m_stAseMeshAni->NodeName));

	this->m_stAseMeshAni->pAniPos = NULL;
	this->m_stAseMeshAni->pAniRot = NULL;
	this->m_stAseMeshAni->pAniScl = NULL;

	return true;
}

