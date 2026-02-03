#pragma once

#include "../BFEngine/Plane.h"

class CControlObject;
class CCtlObjOrtho;

class CBackground : public CPlane
{
private:
	CCtlObjOrtho *m_pCharObjControl;

protected:
	virtual bool ChildInit();
	virtual bool ChildFrame();
	virtual bool ChildRender();
	virtual bool ChildRelease();

public:
	CBackground(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj = NULL, LPCTSTR filename = NULL, int nTotalFrame = 0, int nWFrame = 0, int nHFrame = 0);
	CBackground(void);
	~CBackground(void);
};
