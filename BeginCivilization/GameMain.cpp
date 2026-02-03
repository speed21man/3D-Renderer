#include "GameMain.h"

#include "../BFEngine/Plane.h"
#include "../BFEngine/DrawObjectMgt.h"
#include "../BFEngine/ctlObjBillboard.h"
#include "./Character.h"

CGameMain::CGameMain(HINSTANCE hInst)
:BFEngine(hInst)
{
}

CGameMain::CGameMain(void)
{
}

CGameMain::~CGameMain(void)
{
}

BOOL CGameMain::GameInit(void)
{
	//this->SetCameraMode(STATUS_CAMERA_STATIC);
	m_pCharacter = new CCharacter;
	m_pCharacter->Init();
	m_DrawObject.AddObject(m_pCharacter);

	m_pCharacter->SetCharacterPos(300.0f, 300.0f);

	m_pCharacter = new CCharacter(STATUS_ANIMATION, NULL, "../Resource/kkk.tga", 28, 8 , 8);
	m_pCharacter->Init();
	m_DrawObject.AddObject(m_pCharacter);

	return TRUE;

	//D3DXMatrixOrthoOffCenterLH( &matOrtho, 0.0f, vp.Width, vp.Height, 0.0f , 0.0f, 1.0f );
}

BOOL CGameMain::GameLoop(void)
{
	return TRUE;
}
