#pragma once
#include "GameItem.h"

class ConcreteBlock : public GameItem
{
public:
	ConcreteBlock(Point2f GameItemPos);
	virtual ~ConcreteBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	virtual bool CanCollide(GameItem* gameItem) {
		if (gameItem->GetGameItemType() == GameItemType::FishType) return false;
		return true;
	}
};
