#pragma once

class CPlane;

class CCollision
{
public:
	// 플랜 충돌
	//virtual bool PlaneCollision(RECT& rt)			= 0;
	virtual bool PlaneCollision(CPlane& pPlane)		= 0;
	
public:
	CCollision(void);
	~CCollision(void);
};
