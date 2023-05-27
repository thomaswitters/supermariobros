#pragma once

#include "Avatar.h"

class Avatar;

class BiggerMan : public Avatar
{
public:
	BiggerMan();
	virtual ~BiggerMan();
	void Draw(const AvatarState* avatarState) const;
	void UpdateDraw(float elapsedSec);
};
