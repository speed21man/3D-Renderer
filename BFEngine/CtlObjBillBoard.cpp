#include "CtlObjBillBoard.h"
//#include "./Plane.h"
//#include "./PlaneBillBoard.h"
#include "./PlaneStatus.h"
#include "./global.h"

CCtlObjBillBoard::CCtlObjBillBoard(void)
:m_bAlpha(false)
{

	D3DXQuaternionIdentity(&this->m_quatRot);
	D3DXMatrixIdentity(&this->m_matRot);
	D3DXMatrixIdentity(&this->m_matScl);
	D3DXMatrixIdentity(&this->m_matPos);
	D3DXMatrixIdentity(&this->m_matPlane);
	
	
	memset(&m_vt3Pos, 0 , sizeof(D3DXVECTOR3));
}
CCtlObjBillBoard::~CCtlObjBillBoard(void)
{

}

bool CCtlObjBillBoard::RemoteDrawObj(CPlaneStatus& DrawObj)
{
	this->m_matPlane = DrawObj.GetPlaneMatrix();
	
	D3DXMATRIX viewmat, invmat;

	g_pD3device->GetTransform(D3DTS_VIEW, &viewmat);
	D3DXMatrixInverse(&invmat, 0, &viewmat);

	invmat._41 = m_vt3Pos.x;
	invmat._42 = m_vt3Pos.y;
	invmat._43 = m_vt3Pos.z;

	// 회전이 추가된 빌보드 연산
	this->m_matPlane = this->m_matScl * this->m_matRot * invmat;
	//this->m_matPlane = this->m_matScl * this->m_matRot * this->m_matPos;

	DrawObj.SetPlaneMatrix(this->m_matPlane);
	DrawObj.SetAlphaBlend(this->m_bAlpha);

	return true;
}
bool CCtlObjBillBoard::SetAlphaBlend(bool bAlpha)
{	
	this->m_bAlpha = bAlpha;

	return true;
}

bool CCtlObjBillBoard::BillBoardRot(float fRadian)
{
	//D3DXQuaternionIdentity(&this->m_quatRot);
	D3DXQuaternionRotationYawPitchRoll(&this->m_quatRot, 0.0f, 0.0f, fRadian);
	D3DXMatrixRotationQuaternion(&this->m_matRot, &this->m_quatRot);

	return true;
}

bool CCtlObjBillBoard::SetPlanePosition(D3DXVECTOR3 &vt3Pos)
{
	this->m_vt3Pos = vt3Pos;

	this->m_matPos._41 = m_vt3Pos.x;
	this->m_matPos._42 = m_vt3Pos.y;
	this->m_matPos._43 = m_vt3Pos.z;
	return true;
}

bool CCtlObjBillBoard::SetPlaneScale(float fScale)
{
	this->m_matScl._11 = fScale;
	this->m_matScl._22 = fScale;
	this->m_matScl._33 = fScale;

	return true;
}