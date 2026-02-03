#pragma once

#include "./std.h"

class CDrawObject
{
public:
	virtual bool Init(void) = 0;
	virtual bool Frame(void) = 0;
	virtual bool Render(void) = 0;
	virtual bool Release(void) = 0;

public:
	CDrawObject(void);
	~CDrawObject(void);
};
