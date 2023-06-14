#pragma once
#include "GameItem.h"

enum KindOfNormalBlock { Outside, Underground };
class NormalBlock : public GameItem
{
public:
	NormalBlock(Point2f GameItemPos, KindOfNormalBlock normalBlockType);
	virtual ~NormalBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_BeginPosY;
	KindOfNormalBlock m_NormalBlockType;
};