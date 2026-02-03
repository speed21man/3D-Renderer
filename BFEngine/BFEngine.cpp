#include ".\bfengine.h"
#include "./global.h"
//#include "./ASEObject.h"
#include "./ResourceMgt.h"
#include "./Plane.h"
#include "./ASEMeshParser.h"
#include "./ctlObjBillboard.h"
//#include <crtdbg.h>

BFEngine *g_pBFEngine = NULL;

BFEngine::BFEngine(void)
{
}

BFEngine::~BFEngine(void)
{
}

BFEngine::BFEngine(HINSTANCE hInst) 
:Engine(hInst)
{
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : BFEngine 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL BFEngine::Init()
{

	//this->m_pLight->Init();
	this->m_pInput->Init();
	this->m_pCamera->Init();

	this->m_pDebug->Init();

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : BFEngine 연산 처리부
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL BFEngine::Frame()
{

	#if defined(_DEBUG) || defined(DEBUG)
		this->m_pDebug->Frame();
	#endif

	//this->m_pLight->Frame();

	this->m_pInput->Frame();
	this->m_pCamera->Frame();
	this->m_pCamera->ControlCamera(*this->m_pInput);

	//this->m_pCamera->ControlCamera(*this->m_pInput);

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : BFEngine 랜더링 처리부
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL BFEngine::Render()
{
	g_pD3device->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
		0xff000000, 1.0f, 0L);

	if(SUCCEEDED(g_pD3device->BeginScene()))
	{
		return false;
	}

	//this->m_pLight->Render();

#if defined(_DEBUG) || defined(DEBUG)
		this->m_pDebug->Render();
#endif

	this->m_DrawObject.RenderObject();

	//this->m_pCamera->Render();

	g_pD3device->EndScene();
	
	g_pD3device->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.04.01
// 기능 : BFEngine 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL BFEngine::Release()
{
	return TRUE;
}


void BFEngine::Run()
{
	BOOL bGetMsg;
	MSG m_Msg;

	//메세지 루프에 진입시키기 위함
	PeekMessage(&m_Msg, NULL, 0U, 0U, PM_NOREMOVE);

	this->GameInit();

	while(WM_QUIT != m_Msg.message)
	{
		if(ActivateMode)
			bGetMsg = PeekMessage(&m_Msg, NULL, 0U, 0U, PM_REMOVE);
		else
			bGetMsg = GetMessage(&m_Msg, NULL, 0U, 0U);

		if(bGetMsg)
		{
			TranslateMessage( &m_Msg );
			DispatchMessage( &m_Msg );
		}
		else
		{
			if(ActivateMode)
			{
				this->Frame();
				this->GameLoop();
				this->Render();
			}
		}
	}
}

BOOL BFEngine::SetCameraMode(ENUM_STAT_CAMERA enum_CameraMode)
{
	switch(enum_CameraMode)
	{
	case STATUS_CAMERA_DEBUG:
		this->m_pCamera->Release();
		delete this->m_pCamera;
		this->m_pCamera = new CDebugCamera;
		this->m_pCamera->Init();
		break;

	case STATUS_CAMERA_STATIC:
		this->m_pCamera->Release();
		delete this->m_pCamera;
		this->m_pCamera = new CStaticCamera;
		this->m_pCamera->Init();
		break;
	}

	return TRUE;
}

BOOL BFEngine::GameLoop(void)
{
	return TRUE;
}

BOOL BFEngine::GameInit(void)
{
	return TRUE;
}
