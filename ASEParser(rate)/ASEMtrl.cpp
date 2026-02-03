#include "ASEMtrl.h"

ASEMtrl::ASEMtrl(void)
{
	memset(&this->m_Mtrl, 0, sizeof(this->m_Mtrl));
	m_nSubMaterialCount = 0;
	m_pTexture = NULL;
}

ASEMtrl::~ASEMtrl(void)
{
}

bool ASEMtrl::AddSubMaterial(int nIndex)
{
	ST_SubMaterial *tmp = new ST_SubMaterial;

	//memset(tmp, 0, sizeof(ST_SubMaterial));

	memset(&tmp->SubMtrl, 0, sizeof(D3DMATERIAL9));
	tmp->SubTexture = NULL;

	this->m_mpSubMaterial.insert(std::make_pair(nIndex, tmp));

	return true;
}

ST_SubMaterial* ASEMtrl::FineSubMaterial(int nIndex)
{
	std::map<int ,ST_SubMaterial*>::iterator itPos;

	itPos = this->m_mpSubMaterial.find(nIndex);

	return itPos->second;
}

bool ASEMtrl::SetSubMaterialCount(int nCount)
{
	this->m_nSubMaterialCount = nCount;

	return true;
}

bool ASEMtrl::Init(void)
{
	return true;
}

bool ASEMtrl::Release(void)
{
	if(m_pTexture)
	{
		m_pTexture->Release();
	}

	std::map<int ,ST_SubMaterial*>::iterator itSubMaterial = this->m_mpSubMaterial.begin();

	for(itSubMaterial ;itSubMaterial != this->m_mpSubMaterial.end() ; itSubMaterial++)
	{
		if(itSubMaterial->second->SubTexture)
		{
			itSubMaterial->second->SubTexture->Release();
		}

		delete itSubMaterial->second;
	}

	this->m_mpSubMaterial.clear();

	return true;
}