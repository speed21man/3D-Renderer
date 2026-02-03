#pragma once

#include "./ControlObject.h"

class CCtlObjBillBoard : public CControlObject
{
private:
	D3DXMATRIX m_matPlane;

	D3DXQUATERNION m_quatRot;
	D3DXMATRIX m_matScl;
	D3DXMATRIX m_matRot;
	D3DXMATRIX m_matPos;

	D3DXVECTOR3 m_vt3Pos;
	bool m_bAlpha;

	virtual bool RemoteDrawObj(CPlaneStatus& DrawObj);

public:
	bool BillBoardRot(float fRadian);
	bool SetPlanePosition(D3DXVECTOR3 &vt3Pos);
	bool SetPlaneScale(float fScale);
	bool SetAlphaBlend(bool bAlpha);

public:
	CCtlObjBillBoard(void);
	virtual ~CCtlObjBillBoard(void);
};

