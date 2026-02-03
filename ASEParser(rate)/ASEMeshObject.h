#pragma once

#include "./ASEMesh.h"

class ASEMeshObject : public ASEMesh
{
public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	ASEMeshObject(void);
	~ASEMeshObject(void);
};
