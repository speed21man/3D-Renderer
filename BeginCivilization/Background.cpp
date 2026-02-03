#include "Background.h"

#define FILEPATH0 "../Resource/Scrollback0.bmp"
#define FILEPATH1 "../Resource/Scrollback1.bmp"
#define FILEPATH2 "../Resource/Scrollback2.bmp"
#define FILEPATH3 "../Resource/Scrollback3.bmp"

CBackground::CBackground(void)
:CPlane(STATUS_ORTHOANIMATION, NULL, FILEPATH0, 28, 8, 8)
{
}

CBackground::CBackground(ENUM_STAT_OBJECT Stat_Plane, CControlObject* pControlObj, LPCTSTR filename, int nTotalFrame, int nWFrame, int nHFrame)
:CPlane(Stat_Plane, pControlObj, filename, nTotalFrame , nWFrame , nHFrame)
{
}

CBackground::~CBackground(void)
{
}

bool CBackground::ChildInit()
{
	return true;
}

bool CBackground::ChildFrame()
{
	return true;
}

bool CBackground::ChildRender()
{
	return true;
}

bool CBackground::ChildRelease()
{
	return true;
}
