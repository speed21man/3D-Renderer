#include "Character.h"
#include "../BFEngine/global.h"
#include "../BFEngine/CtlObjOrtho.h"

#define FILEPATH "../Resource/kkk.tga"

CCharacter::CCharacter(void)
:CPlane(STATUS_ORTHOANIMATION, NULL, FILEPATH, 28, 8, 8)
{
}

CCharacter::CCharacter(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj, LPCTSTR filename, int nTotalFrame, int nWFrame, int nHFrame)
:CPlane(Stat_Plane, pControlObj, filename, nTotalFrame , nWFrame , nHFrame)
{
}

CCharacter::~CCharacter(void)
{
}


bool CCharacter::ChildInit()
{	
	m_pCharObjControl = new CCtlObjOrtho;
	m_pCharObjControl->SetPlanePosition(D3DXVECTOR3(0.0f ,0.0f, 0.0f));
	m_pCharObjControl->SetAlphaBlend(true);
	this->SetControlObject(m_pCharObjControl);
	m_pCharObjControl->SetAnimationFrame(6, 18);
	return true;
}

bool CCharacter::ChildFrame()
{
	return true;
}

bool CCharacter::ChildRender()
{
	//D3DXMATRIX tempProjection, tempOrtho;
	//D3DXMatrixIdentity(&tempProjection);
	//D3DXMatrixIdentity(&tempOrtho);
	//g_pD3device->GetTransform(D3DTS_PROJECTION, &tempProjection);

	//D3DXMatrixOrthoOffCenterLH(&tempOrtho, 0.0f, 1024.0f, 768.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

bool CCharacter::ChildRelease()
{
	delete m_pCharObjControl;

	return true;
}

bool CCharacter::SetCharacterPos(float fPosX, float fPosY)
{
	this->m_CharPos.x = fPosX;
	this->m_CharPos.y = -fPosY;
	this->m_CharPos.z = 0.0f;

	m_pCharObjControl->SetPlanePosition(this->m_CharPos);

	return true;
}