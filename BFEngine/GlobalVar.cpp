#include ".\globalvar.h"
#include "./global.h"

CGlobalVar *CGlobalVar::m_pGlobalVar = NULL;

CGlobalVar::CGlobalVar(void)
{
	D3DXMatrixIdentity(&this->m_matWorld);
	D3DXMatrixIdentity(&this->m_matView);
	D3DXMatrixIdentity(&this->m_matPerspect);
}

CGlobalVar::~CGlobalVar(void)
{
}

//CGloblaVar::CGloblaVar(const CGloblaVar& rhs)
//{
//}