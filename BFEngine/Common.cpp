#include ".\common.h"

CCommon::CCommon(void)
: m_bWindowMode(TRUE)
{
	memset(&this->m_DisMode, 0, sizeof(this->m_DisMode));
}

CCommon::~CCommon(void)
{
}

BOOL CCommon::SetDisplayMode(float width, float height)
{
	this->m_DisMode.Height = (UINT)height;
	this->m_DisMode.Width = (UINT)width;

	return TRUE;
}

BOOL CCommon::SetWindowMode(BOOL bWindowMode)
{
	this->m_bWindowMode = bWindowMode;

	return TRUE;
}
