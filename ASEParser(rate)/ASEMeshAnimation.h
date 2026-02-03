#pragma once

#include "./std.h"
#include <vector>

class ASEMeshAnimation
{
public:
	char NodeName[256];

public:
	D3DXMATRIX							m_matAniMatrix;

	std::vector<D3DXQUATERNION *>		m_vQuatRot;
	std::vector<D3DXVECTOR3	*>			m_vQuatPos;

	//D3DXMATRIX							m_matScale;

public:
	bool SetAnimationMatrix(void);
	//bool SetAniParser(void);

public:
	ASEMeshAnimation(void);
	~ASEMeshAnimation(void);
};
