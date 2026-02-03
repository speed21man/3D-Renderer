#pragma once

#include "./Collision.h"

class CDefaultCollision : public CCollision
{
public:
	virtual bool PlaneCollision(CPlane& pPlane);

public:
	CDefaultCollision(void);
	~CDefaultCollision(void);
};
