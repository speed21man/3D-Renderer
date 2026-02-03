#pragma once

#include "./ControlObject.h"

class CCtlObjOrtho : public CControlObject
{
private:
	D3DXMATRIX m_matPlane;

	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_matScl;
	D3DXMATRIX m_matRot;
	D3DXMATRIX m_matPos;

	//D3DXVECTOR3 m_vt3Pos;
	bool m_bAlpha;

	int m_nBegineFrame, m_nEndFrame;
	float m_fAniFrameTime, m_fAniFrameRate;

	virtual bool RemoteDrawObj(CPlaneStatus& DrawObj);

public:
	bool BillBoardRot(float fRadian);

	// 인라인 함수들
	bool SetAlphaBlend(bool bAlpha)				{	this->m_bAlpha = bAlpha; return true;	}
	bool SetPlaneScale(float fScale)			{	this->m_matScl._11 = fScale;this->m_matScl._22 = fScale;this->m_matScl._33 = fScale;return true;	}
	bool SetPlanePosition(D3DXVECTOR3 &vt3Pos)	{	this->m_matPos._41 = vt3Pos.x;	this->m_matPos._42 = vt3Pos.y;	this->m_matPos._43 = vt3Pos.z;	return true;	}
	bool SetAnimationFrame(int nBeginFrame, int nEndFrame) 	{	this->m_fAniFrameTime = this->m_nBegineFrame = nBeginFrame;		this->m_nEndFrame = nEndFrame;		return true;	}

public:
	CCtlObjOrtho(void);
	virtual ~CCtlObjOrtho(void);
};
