#include "Plane.h"	
#include "./PlaneStatus.h"
#include "./PlaneBillBoard.h"
#include "./PlaneAnimation.h"
#include "./ControlObject.h"
#include "./PlaneOrthoAnimation.h"
//#include "./defaultCollision.h"
//#include "./BillBoardCollision.h"

//CDefaultCollision		_DefaultCollision;
//CBillBoardCollision		_BillBoardCollision;

CPlane::CPlane(void)
:m_pCtlObj(NULL)
,m_pPlaneStatus(NULL)
{
}

//CPlane::CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj)
//:m_pCtlObj(pControlObj)
//,m_pPlaneStatus(NULL)
//{
//	this->CreatePlane(Stat_Plane);
//}

//CPlane::CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj,  LPCTSTR filename)
//:m_pCtlObj(pControlObj)
//,m_pPlaneStatus(NULL)
//{
//	this->CreatePlane(Stat_Plane, filename);
//}

//	return true;
CPlane::CPlane(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj, LPCTSTR filename, int nTotalFrame, int nWFrame, int nHFrame)
:m_pCtlObj(pControlObj)
,m_pPlaneStatus(NULL)
{
	this->CreatePlane(Stat_Plane, filename, nTotalFrame, nWFrame, nHFrame);
}

CPlane::~CPlane(void)
{
}

bool CPlane::CreatePlane(ENUM_STAT_OBJECT stat_Plane, LPCTSTR filename, int nTotalFrame, int nWFrame, int nHFrame)
{
	if(!this->m_pPlaneStatus)
	{
		switch(stat_Plane)
		{
		case STATUS_BILLBOARD:
			if(filename)
				this->m_pPlaneStatus = new CPlaneBillBoard(filename);
			else
				this->m_pPlaneStatus = new CPlaneBillBoard;
			break;

		case STATUS_ANIMATION:
			if(nTotalFrame || nWFrame || nHFrame)
				this->m_pPlaneStatus = new CPlaneAnimation(filename, nTotalFrame, nWFrame, nHFrame);
			break;

		case STATUS_ORTHOANIMATION:
			if(nTotalFrame || nWFrame || nHFrame)
				this->m_pPlaneStatus = new CPlaneOrthoAnimation(filename, nTotalFrame, nWFrame, nHFrame);
			break;
		}
	}

	return true;
}

bool CPlane::Init(void)
{
	m_pPlaneStatus->Init();
	this->ChildInit();
	return true;
}

bool CPlane::Frame(void)
{
	m_pPlaneStatus->Frame();
	this->ChildFrame();

	if(m_pCtlObj) this->m_pCtlObj->RemoteDrawObj(*m_pPlaneStatus);

	return true;
}

bool CPlane::Render(void)
{
	m_pPlaneStatus->Render();
	this->ChildRender();
	return true;
}

bool CPlane::Release(void)
{
	if(m_pPlaneStatus)
	{
		m_pPlaneStatus->Release();
		delete m_pPlaneStatus;
		m_pPlaneStatus = NULL;
	}

	this->ChildRelease();

	return true;
}

bool CPlane::SetControlObject(CControlObject* pCtlObj)
{
	this->m_pCtlObj = pCtlObj;

	return true;
}

bool CPlane::ChildInit(void)
{
	return true;
}

bool CPlane::ChildFrame(void)
{
	return true;
}

bool CPlane::ChildRender(void)
{
	return true;
}

bool CPlane::ChildRelease(void)
{
	return true;
}