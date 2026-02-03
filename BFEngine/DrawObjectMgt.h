#pragma once

#include "./std.h"
#include <vector>

using namespace std;

class CDrawObject;
class CControlObject;

class CDrawObjectMgt
{
private:
	vector<CDrawObject*> m_vecDrawObject;
	bool CreateDrawObject();

public:
	bool AddObject(ENUM_STAT_OBJECT stat_object, CControlObject* ctlObj = NULL, LPCTSTR filename = NULL, int nTotalFrame = 0, int nWFrame = 0, int nHFrame = 0);
	bool AddObject(CDrawObject *pDrawObject);
	bool RenderObject(void);

public:
	CDrawObjectMgt(void);
	~CDrawObjectMgt(void);
};
