#pragma once

#pragma comment (lib, "../Lib/BFEngine.lib")

#include "../BFEngine/std.h"
#include "../BFEngine/Global.h"

class CPlane;
class CControlObject;
class CCharacter;

class CGameMain : public BFEngine
{
public:
	CCharacter *m_pCharacter;

public:
	virtual BOOL GameInit(void);

public:
	virtual BOOL GameLoop(void);

public:
	CGameMain(HINSTANCE hInst);
	CGameMain(void);
	~CGameMain(void);
};
