#pragma once

#include "./std.h"
#include <dinput.h>

class CInput
{
public:
	LPDIRECTINPUT8			m_pDi;
	LPDIRECTINPUTDEVICE8	m_pDidevKey;
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;
	BYTE					m_KeyState[256];
	DIMOUSESTATE			m_MouseState;

public:
	BOOL InitDirectInput(bool Keyboard, bool mouse);
	BOOL KeyProcess(BYTE *key);
	BOOL MouseProcess(DIMOUSESTATE *MouseState);

public:
	BOOL Init(void);
	BOOL Frame(void);
	BOOL Render(void);
	BOOL Release(void);

public:
	CInput(void);
	virtual ~CInput(void);
};
