#pragma once

#include "./ASEParserDef.h"
#include "./ASEMesh.h"

class CASEProcess
{
public:
	virtual bool ASEFrame(CASEMesh& AseMesh) = 0;
	virtual bool ASERender(CASEMesh& AseMesh) = 0;
};

class CASE_PTCN_Frame : public CASEProcess
{
public:
	virtual bool ASEFrame(CASEMesh& AseMesh);
	virtual bool ASERender(CASEMesh& AseMesh);
};

class CASE_PTN_Frame : public CASEProcess
{
public:
	virtual bool ASEFrame(CASEMesh& AseMesh);
	virtual bool ASERender(CASEMesh& AseMesh);
};

class CASE_PN_Frame : public CASEProcess
{
public:
	virtual bool ASEFrame(CASEMesh& AseMesh);
	virtual bool ASERender(CASEMesh& AseMesh);
};
