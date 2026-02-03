#pragma comment (lib, "../Lib/BFEngine.lib")

#include "../BFEngine/std.h"
#include "../BFEngine/Global.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	g_pBFEngine = new BFEngine(hInst);

	g_pBFEngine->m_pD3d->Init();

	g_pBFEngine->m_pWindow->CreateWin(hInst);
	g_pBFEngine->m_pD3d->CreateDevice9();
	g_pBFEngine->Init();
	//g_pBFEngine->m_pInput->Init();
	//g_pBFEngine->m_pCamera->Init();

	g_pBFEngine->Run();

	g_pBFEngine->Release();

	delete g_pBFEngine;

	return true;
}

