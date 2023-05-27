#pragma once
#include "GameItem.h"

class ConcreteBlockQ : public GameItem
{
public:
	ConcreteBlockQ(Point2f GameItemPos);
	virtual ~ConcreteBlockQ();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
};
