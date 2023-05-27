#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(Point2f GameItemPos);
	virtual ~Goomba();

	virtual bool CanCollide(GameItem* gameItem) {
		if (gameItem->GetGameItemType() == GameItemType::ProjectileType) return false;

		return true;
	}

};

