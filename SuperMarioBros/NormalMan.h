#pragma once

#include "Avatar.h"

class Avatar;

class NormalMan : public Avatar
{
public:
	NormalMan();
	virtual ~NormalMan();
	void Draw(const AvatarState* avatarState) const;
	void UpdateDraw(float elapsedSec);

	bool canBumpGameItem() const {
		return true;
	}
private:
	float m_TimerIsHit;
	float m_TimeInterval;
};
