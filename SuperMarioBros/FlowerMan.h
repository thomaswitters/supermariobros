#pragma once

#include "Avatar.h"

class Avatar;

class FlowerMan : public Avatar
{
public:
	FlowerMan();
	virtual ~FlowerMan();
	void Draw(const AvatarState* avatarState) const;
	void UpdateDraw(float elapsedSec);
};
//m_Shape{ 50, 280, 10, 20 },
//m_HorSpeed{ 2.5f },
//m_JumpSpeed{ 80.0f },
//m_Velocity{ 0.0f, 0.0f },
//m_Acceleration{ 0.0f, -981.0f },
