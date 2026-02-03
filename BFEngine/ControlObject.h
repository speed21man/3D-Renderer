#pragma once

#include "./std.h"
#include "./PlaneStatus.h"
//#include "./DrawObject.h"

class CPlane;

class CControlObject
{
private:
	virtual bool RemoteDrawObj(CPlaneStatus& DrawObj) = 0;

public:
	friend class CPlane;

public:
	CControlObject(void);
	~CControlObject(void);
};
