#pragma once

#include "Engine.h"
#include "./DrawObjectMgt.h"

class ASEObject;
class CPlane;
class CDrawObjectMgt;
class CControlObject;

class BFEngine : public Engine 
{
public:
	CDrawObjectMgt m_DrawObject;

public:
	BOOL Init(void);
	BOOL Release(void);

	virtual BOOL Frame(void);
	virtual BOOL Render(void);

	virtual BOOL GameInit(void);
	virtual BOOL GameLoop(void);

public:
	BOOL SetCameraMode(ENUM_STAT_CAMERA enum_CameraMode);

public:
	void Run(void);

//public:
//	bool BeginEngine(HINSTANCE hInst);

public:
	BFEngine(void);
	BFEngine(HINSTANCE hInst);
	~BFEngine(void);
};
