#pragma once

#include "./PlaneStatus.h"

class CPlaneAnimation : public CPlaneStatus
{
private:
	ST_PLANE m_Animation[6];

	LPCTSTR m_strTexFilename;

	int m_nAniFrame;
	int m_nAniTWidthCount;
	int m_nAniTHeightCount;

	float m_fAniTWidth;
	float m_fAniTHeight;
	float m_fAniFrameTime;

	float m_fAniFrameRate;

	float m_fGapWidth;
	float m_fGapHeight;

	D3DXMATRIX m_matRot;
	D3DXMATRIX m_matIdentity;
	D3DXQUATERNION m_quatRot;

public:
	virtual bool Init(void);
	virtual bool Frame(void);
	virtual bool Render(void);
	virtual bool Release(void);

public:
	CPlaneAnimation(LPCTSTR filename, int nTotalFrame, int nWidthNum, int nHeightNum);
	CPlaneAnimation(void);
	~CPlaneAnimation(void);
};
