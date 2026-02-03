#pragma comment (lib, "../Lib/BFEngine.lib")

//#import "../Lib/BFEngine.lib" tlbid(101)

#include "../BFEngine/std.h"
#include "../BFEngine/Global.h"
#include "./DlgEngineInit.h"
//#include <crtdbg.h>

//#include "./resource1.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	//_CrtSetBreakAlloc(85); 

	CDlgEngineInit *pDlgEngineInit = NULL;
	g_pBFEngine = new BFEngine(hInst);

	SAFENEW(pDlgEngineInit, CDlgEngineInit);

	g_pBFEngine->m_pD3d->Init();
	pDlgEngineInit->Init(hInst);

	g_pBFEngine->m_pWindow->CreateWin(hInst);
	g_pBFEngine->m_pD3d->CreateDevice9();
	g_pBFEngine->Init();
	g_pBFEngine->m_pInput->Init();
	g_pBFEngine->m_pCamera->Init();

	g_pBFEngine->Run();

	g_pBFEngine->Release();

	delete g_pBFEngine;

	//_CrtMemDumpAllObjectsSince(0);

	return true;
}

