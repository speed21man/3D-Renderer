
#include "./GameMain.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	CGameMain *pGameMain = new CGameMain(hInst);

	pGameMain->m_pD3d->Init();

	pGameMain->m_pWindow->CreateWin(hInst);
	pGameMain->m_pD3d->CreateDevice9();
	pGameMain->Init();
	
	pGameMain->Run();

	pGameMain->Release();

	delete pGameMain;

	return true;
}

