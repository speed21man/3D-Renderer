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

protected:
	const D3DDISPLAYMODE GetDisplayMode(void)	{	return this->m_d3dDisMode;	};
	const D3DXMATRIX GetWorldMatrix(void)		{	return this->m_matWorld;	};
	const D3DXMATRIX GetViewMatrix(void)		{	return this->m_matView;		};
	const D3DXMATRIX GetPerspectMatrix(void)	{	return this->m_matPerspect;	};

protected:
	void SetWorldMatrix(D3DXMATRIX matWorld)		{	this->m_matWorld = matWorld;		};
	void SetViewMatrix(D3DXMATRIX matView)			{	this->m_matView = matView;			};
	void SetPerspectMatrix(D3DXMATRIX matPerspect)	{	this->m_matPerspect = matPerspect;	};

protected:
	static CGlobalVar* CreateInstance(void)
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

protected:
	CGlobalVar(void);
	~CGlobalVar(void);
};
