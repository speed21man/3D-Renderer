#include "CtlObjOrtho.h"

#include "./PlaneStatus.h"
#include "./global.h"

CCtlObjOrtho::CCtlObjOrtho(void)
:m_bAlpha(false)
,m_nBegineFrame(0)
,m_nEndFrame(0)
,m_fAniFrameRate(60.0f)
,m_fAniFrameTime(0.0f)
{

	D3DXQuaternionIdentity(&this->m_quatRot);
	D3DXMatrixIdentity(&this->m_matRot);
	D3DXMatrixIdentity(&this->m_matScl);
	D3DXMatrixIdentity(&this->m_matPos);
	D3DXMatrixIdentity(&this->m_matPlane);
}

CCtlObjOrtho::~CCtlObjOrtho(void)
{

}

bool CCtlObjOrtho::RemoteDrawObj(CPlaneStatus& DrawObj)
{
	this->m_matPlane = this->m_matScl * this->m_matRot * this->m_matPos;

	DrawObj.SetPlaneMatrix(this->m_matPlane);
	DrawObj.SetAlphaBlend(this->m_bAlpha);

	if(!this->m_nEndFrame)
		return false;

	this->m_fAniFrameTime += this->m_fAniFrameRate * 0.001f;
	if(this->m_nEndFrame <= (int)m_fAniFrameTime)  this->m_fAniFrameTime = this->m_nBegineFrame;

	DrawObj.SetAniFrame(this->m_fAniFrameTime);

	return true;
}

bool CCtlObjOrtho::BillBoardRot(float fRadian)
{
	//D3DXQuaternionIdentity(&this->m_quatRot);
	D3DXQuaternionRotationYawPitchRoll(&this->m_quatRot, 0.0f, 0.0f, fRadian);
	D3DXMatrixRotationQuaternion(&this->m_matRot, &this->m_quatRot);

	return true;
}