#pragma once

#include ".\std.h"

class CTimer;

class CCommon
{
private:
	D3DDISPLAYMODE m_DisMode;
	BOOL m_bWindowMode;

public:
	CTimer *m_pTimer;

public:
	BOOL SetDisplayMode(float width, float height);
	BOOL SetWindowMode(BOOL bWindowMode);

public:
	const D3DDISPLAYMODE GetDisplayMode(void) {	return this->m_DisMode;	}; 
	const BOOL GetWindowMode(void) { return this->m_bWindowMode;	};

public:
	CCommon(void);
	~CCommon(void);
};
