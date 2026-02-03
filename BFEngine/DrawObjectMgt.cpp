#include "DrawObjectMgt.h"
#include "./DrawObject.h"
#include "./ControlObject.h"
#include "./Plane.h"
#include "./Mesh.h"

CDrawObjectMgt::CDrawObjectMgt(void)
{
}

CDrawObjectMgt::~CDrawObjectMgt(void)
{
	for(int i = 0; i < this->m_vecDrawObject.size() ; i++)
	{
		this->m_vecDrawObject[i]->Release();
		delete m_vecDrawObject[i];
	}

	this->m_vecDrawObject.clear();
}

//bool CDrawObjectMgt::AddObject(ENUM_STAT_OBJECT stat_object, CControlObject* ctlObj)
//{
//
//	CDrawObject *pDrawObj;
//
//	switch(stat_object)
//	{
//	case STATUS_BILLBOARD:
//		pDrawObj = new CPlane(STATUS_BILLBOARD, ctlObj);
//		pDrawObj->Init();
//		this->m_vecDrawObject.push_back(pDrawObj);
//		break;
//
//	case STATUS_ASEMESH:
//		//pDrawObj = new CMesh(STATUS_BILLBOARDz);
//		this->m_vecDrawObject.push_back(pDrawObj);
//		break;
//	}
//
//	return true;
//}

bool CDrawObjectMgt::AddObject(ENUM_STAT_OBJECT stat_object, CControlObject* ctlObj, LPCTSTR filename, int nTotalFrame, int nWFrame, int nHFrame)
{

	CDrawObject *pDrawObj;

	switch(stat_object)
	{
	case STATUS_BILLBOARD:
		pDrawObj = new CPlane(STATUS_BILLBOARD, ctlObj, filename);
		pDrawObj->Init();
		
		this->m_vecDrawObject.push_back(pDrawObj);
		break;

	case STATUS_ANIMATION:
		pDrawObj = new CPlane(STATUS_ANIMATION, ctlObj, filename, nTotalFrame, nWFrame, nHFrame);
		pDrawObj->Init();
		
		this->m_vecDrawObject.push_back(pDrawObj);
		break;

	case STATUS_ORTHOANIMATION:
		pDrawObj = new CPlane(STATUS_ANIMATION, ctlObj, filename, nTotalFrame, nWFrame, nHFrame);
		pDrawObj->Init();
		
		this->m_vecDrawObject.push_back(pDrawObj);
		break;

	case STATUS_ASEMESH:
		//pDrawObj = new CMesh(STATUS_BILLBOARDz);
		this->m_vecDrawObject.push_back(pDrawObj);
		break;
	}

	return true;
}

bool CDrawObjectMgt::AddObject(CDrawObject *pDrawObject)
{
	this->m_vecDrawObject.push_back(pDrawObject);
	return true;
}

bool CDrawObjectMgt::RenderObject(void)
{
	for(int i = 0; i < this->m_vecDrawObject.size() ; i++)
	{
		this->m_vecDrawObject[i]->Frame();
		this->m_vecDrawObject[i]->Render();
	}

	return true;
}