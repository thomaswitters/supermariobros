#pragma once
#include "Enemy.h"

class Fish : public Enemy
{
public:
	Fish(Point2f GameItemPos);
	virtual ~Fish();
	void UpdateGameItem(float elapsedSec, GameState* gameState);

	virtual bool CanCollide(GameItem* gameItem) {
		if (gameItem->GetGameItemType() == GameItemType::ProjectileType) return false;

		return true;
	}
private:
	float m_SecFishFloats;
	float m_JumpHeight;
};