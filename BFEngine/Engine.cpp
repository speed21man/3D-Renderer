#include "./engine.h"
#include "./global.h"

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 생성자와 소멸자
// 반환값 : 없음
//////////////////////////////////////////////////////////////////
Engine::Engine(void)
:m_pTimer(NULL),
m_pInput(NULL),
m_pWindow(NULL),
m_pD3d(NULL),
m_pDebug(NULL),
m_pCamera(NULL),
m_pLight(NULL),
ActivateMode(true)
{
	this->Init();
}

Engine::~Engine(void)
{
	this->Release();
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 메세지 루프 
//        ActivateMode(true == 최대화 상태 : false == 최소화 상태)
// 반환값 : 없음
//////////////////////////////////////////////////////////////////
//void Engine::Run()
//{
//	BOOL bGetMsg;
//	MSG m_Msg;
//
//	//메세지 루프에 진입시키기 위함
//	PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE);
//
//	while(WM_QUIT != m_Msg.message)
//	{
//		if(ActivateMode)
//			bGetMsg = PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE);
//		else
//			bGetMsg = GetMessage(&m_Msg, NULL, 0, 0);
//
//		if(bGetMsg)
//		{
//			TranslateMessage( &m_Msg );
//			DispatchMessage( &m_Msg );
//		}
//		else
//		{
//			if(ActivateMode)
//			{
//				this->Frame();
//				this->Render();
//			}
//		}
//	}
//}


//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 연산에 관련된 처리를 하는 곳
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL Engine::Frame()
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 랜더링에 관련된 처리를 하는 곳
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL Engine::Render()
{
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 엔진 초기화
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL Engine::Init()
{	
	//this->m_pD3d
	//	this->m_pInput
	//	this->m_pTimer
	SAFENEW(this->m_pWindow, CWindow);
	SAFENEW(this->m_pD3d, D3D);
	SAFENEW(this->m_pInput, CInput);
	SAFENEW(this->m_pCamera, CDebugCamera);
	//SAFENEW(this->m_pLight, CLight);


#if defined(_DEBUG) || defined(DEBUG)
	SAFENEW(this->m_pDebug, CDebug);
#endif

	//D3DXMatrixIdentity(&this->m_matWorld);
	//D3DXMatrixIdentity(&this->m_matView);
	//D3DXMatrixIdentity(&this->m_matPerspect);
	//SAFENEW(this->m_pDlgInit, CDlgEngineInit);

	//this->m_pWindow = new CWindow;
	//this->m_pD3d = new D3D;

	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.25
// 기능 : 엔진 해제
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
BOOL Engine::Release()
{
	_SAFEDEL(this->m_pWindow);
	_SAFEDEL(this->m_pD3d);
	_SAFEDEL(this->m_pInput);
	_SAFEDEL(this->m_pCamera);
	//_SAFEDEL(this->m_pLight);

#if defined(_DEBUG) || defined(DEBUG)
	_SAFEDEL(this->m_pDebug);
#endif
	return TRUE;
}

//////////////////////////////////////////////////////////////////
// 작성자 : 박정엽
// 작성일 : 08.03.26
// 기능 : 인스턴스를 포함한 생성자(오토)
// 반환값 : BOOL
//////////////////////////////////////////////////////////////////
Engine::Engine(HINSTANCE hInst)
:m_pTimer(NULL),
m_pInput(NULL),
m_pWindow(NULL),
m_pD3d(NULL),
m_pDebug(NULL),
m_pCamera(NULL),
m_pLight(NULL),
ActivateMode(true)
{
	this->Init();
	//this->m_pDlgInit->Init(hInst);
	//this->m_pWindow->CreateWin(hInst);
	//this->m_pD3d->Init();
}