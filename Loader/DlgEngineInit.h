#pragma once

#include "../BFEngine/std.h"

class CDlgEngineInit
{
public:
	BOOL Init(HINSTANCE hInst);
	BOOL Release(void);

public:
	static BOOL CALLBACK DlgMsgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	CDlgEngineInit(void);
	~CDlgEngineInit(void);
};
