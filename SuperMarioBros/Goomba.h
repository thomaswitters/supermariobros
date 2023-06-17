#pragma once
#include "Enemy.h"

class Goomba : public Enemy
{
public:
	Goomba(Point2f GameItemPos);
	virtual ~Goomba();
	void UpdateGameItem(float elapsedSec, GameState* gameState);

	virtual bool CanCollide(GameItem* gameItem) {
		if (gameItem->GetGameItemType() == GameItemType::ProjectileType) return false;

		return true;
	}

};

