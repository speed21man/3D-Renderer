#pragma once

#include "./std.h"
#include "./DrawObject.h"
//#include "./ControlObject.h" 
//#include "./DefaultCollision.h"

class CControlObject;
class CPlaneStatus;

//extern CDefaultCollision _DefaultCollision;

class CPlane : public CDrawObject
{
//public:
//	friend class CControlObject;

private:
	bool CreatePlane(ENUM_STAT_OBJECT stat_Plane, LPCTSTR filename, int nTotalFrame = 0, int nWFrame = 0, int nHFrame = 0);

public:
	CControlObject				*m_pCtlObj;
	CPlaneStatus				*m_pPlaneStatus;

	//CCollision					*m_pCollision;

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

	bool SetControlObject(CControlObject* pCtlObj);

protected:
	virtual bool ChildInit(void);
	virtual bool ChildFrame(void);
	virtual bool ChildRender(void);
	virtual bool ChildRelease(void);

public:
	//CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj = NULL);
	CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj = NULL, LPCTSTR filename = NULL, int nTotalFrame = 0, int nWFrame = 0, int nHFrame = 0);
	//CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj = NULL, LPCTSTR filename = NULL);
	
	CPlane(void);
	virtual ~CPlane(void);
};
