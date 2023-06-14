#pragma once
#include "LiveItem.h"

enum ProjectileDirection { Left, Right };

class Projectile : public LiveItem
{
public:
	Projectile(Point2f GameItemPos, ProjectileDirection projectileDirection);
	virtual ~Projectile();

	virtual void UpdateGameItem(float elapsedSec, GameState* gameState); 
	virtual void CollisionDetect(GameState* gameState);
	virtual void CollisionWithGameItemDetect(GameItem* gameItem);
	virtual void CollisionWithLiveItemDetect(LiveItem* liveItem);

	virtual void BounceFloor();
	virtual bool IsEnemyOf(LiveItem* otherLiveItem);
};


