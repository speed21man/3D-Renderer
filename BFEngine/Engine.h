#pragma once

//#include "./Common.h"

//class CTimer;
#include ".\std.h"

class CDebug;
class CTimer;
class CInput;
class CWindow;
class CCamera;
class CLight;
class D3D;
//class CDlgEngineInit;

class Engine
{
public:
	CInput *m_pInput;
	CWindow *m_pWindow;
	CTimer *m_pTimer;
	D3D *m_pD3d;
	CDebug *m_pDebug;
	CLight *m_pLight;
	CCamera *m_pCamera;
	//CDlgEngineInit *m_pDlgInit;

public:
	//D3DXMATRIX m_matWorld;
	//D3DXMATRIX m_matView;
	//D3DXMATRIX m_matPerspect;

	bool ActivateMode;

public:
	BOOL Init(void);
	BOOL Release(void);
	//void Run(void);

public:
	Engine(void);
	Engine(HINSTANCE hInst);
	~Engine(void);

private:
	virtual BOOL Frame(void);
	virtual BOOL Render(void);
};
