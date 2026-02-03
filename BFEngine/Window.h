#pragma once

#include ".\std.h"

class CWindow
{
public:
	//HINSTANCE m_hInst;
	//MSG m_Msg;

public:
	LRESULT WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	BOOL CreateWin(HINSTANCE hInst);

	bool Init(void);
	bool Release(void);

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//void Run(void);

public:
	CWindow(void);
	~CWindow(void);

private:
	void WndClassRegister(HINSTANCE hInst);
};
