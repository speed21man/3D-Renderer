#pragma once

#include "./Collision.h"

class CBillBoardCollision : public CCollision
{
public:
	bool PlaneCollision(CPlane &pPlane);
	//virtual bool PlaneCollision(RECT &rt);

public:
	CBillBoardCollision(void);
	~CBillBoardCollision(void);
};
