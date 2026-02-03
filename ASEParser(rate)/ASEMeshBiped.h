#pragma once

#include "./ASEMesh.h"

class ASEMeshBiped : public ASEMesh
{
public:
	bool bBipedCheck;

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	ASEMeshBiped(void);
	~ASEMeshBiped(void);
};
