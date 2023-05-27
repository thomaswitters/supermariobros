#pragma once
#include "LiveItem.h"

class Projectile : public LiveItem
{
public:
	Projectile(Point2f GameItemPos);
	virtual ~Projectile();

	virtual void UpdateGameItem(float elapsedSec, GameState* gameState); 
	virtual void CollisionDetect(GameState* gameState);
	virtual void CollisionWithGameItemDetect(GameItem* gameItem);
	virtual void CollisionWithLiveItemDetect(LiveItem* liveItem);

	virtual void BounceFloor();
	virtual bool IsEnemyOf(LiveItem* otherLiveItem);
};


