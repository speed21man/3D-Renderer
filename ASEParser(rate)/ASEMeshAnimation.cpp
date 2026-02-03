#include "ASEMeshAnimation.h"

ASEMeshAnimation::ASEMeshAnimation(void)
{
	memset(NodeName, 0, sizeof(NodeName));
}

ASEMeshAnimation::~ASEMeshAnimation(void)
{
}

bool ASEMeshAnimation::SetAnimationMatrix(void)
{
	return true;
}
