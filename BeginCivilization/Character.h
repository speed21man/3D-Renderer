#pragma once

#include "../BFEngine/Plane.h"

class CControlObject;
class CCtlObjOrtho;

class CCharacter : public CPlane
{
private:
	CCtlObjOrtho *m_pCharObjControl;
	D3DXVECTOR3 m_CharPos;

protected:
	virtual bool ChildInit();
	virtual bool ChildFrame();
	virtual bool ChildRender();
	virtual bool ChildRelease();

public:
	bool SetCharacterPos(float fPosX, float fPosY);

	D3DXVECTOR3& GetCharacterPos(void) {	return this->m_CharPos;	};

public:
	CCharacter(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj = NULL, LPCTSTR filename = NULL, int nTotalFrame = 0, int nWFrame = 0, int nHFrame = 0);
	CCharacter(void);
	~CCharacter(void);
};
