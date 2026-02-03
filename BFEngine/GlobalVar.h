#pragma once

#include "std.h"

class CGlobalVar
{
private:
	D3DDISPLAYMODE m_d3dDisMode;

	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matPerspect;

private:
	static CGlobalVar *m_pGlobalVar;

public:
	static CGlobalVar *CreateInstance(void)
	{
		if(!m_pGlobalVar)
			m_pGlobalVar = new CGlobalVar;

		return m_pGlobalVar;
	}

	static void DeleteInstance(void)
	{
		if(m_pGlobalVar)
		{
			delete 	m_pGlobalVar;
			m_pGlobalVar = NULL;
		}
	}

public:
	const D3DDISPLAYMODE GetDisplayMode(void)	{	return this->m_d3dDisMode;	};
	const D3DXMATRIX GetWorldMatrix(void)		{	return this->m_matWorld;	};
	const D3DXMATRIX GetViewMatrix(void)		{	return this->m_matView;		};
	const D3DXMATRIX GetPerspectMatrix(void)	{	return this->m_matPerspect;	};

public:
	void SetWorldMatrix(D3DXMATRIX *matWorld)		{	memcpy(&this->m_matWorld, matWorld, sizeof(D3DXMATRIX));		};
	void SetViewMatrix(D3DXMATRIX *matView)			{	memcpy(&this->m_matView, matView, sizeof(D3DXMATRIX));			};
	void SetPerspectMatrix(D3DXMATRIX *matPerspect)	{	memcpy(&this->m_matPerspect, matPerspect, sizeof(D3DXMATRIX));	};
	void SetDisplayMode(D3DDISPLAYMODE *DisMode)	{	memcpy(&this->m_d3dDisMode, DisMode, sizeof(D3DDISPLAYMODE));	};

public:
	D3DXMATRIX* const CalculateWorldMatrix(void)	{	return &this->m_matWorld;		};
	D3DXMATRIX* const CalculateViewMatrix(void)		{	return &this->m_matView;		};
	D3DXMATRIX* const CalculatePerspectMatrix(void)	{	return &this->m_matPerspect;	};

public:
	CGlobalVar(void);
	~CGlobalVar(void);
//	CGloblaVar(const CGloblaVar& rhs);
};