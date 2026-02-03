#pragma once

#include "./DrawObject.h"

class CMeshStatus;

class CMesh : public CDrawObject
{
public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	CMesh(CMeshStatus *DefaultMesh);
	CMesh(void);
	~CMesh(void);
};
