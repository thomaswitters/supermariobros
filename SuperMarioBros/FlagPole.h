#pragma once
#include "GameItem.h"

class FlagPole : public GameItem
{
public:
	FlagPole(Point2f GameItemPos);
	virtual ~FlagPole();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Texture* m_pTexture;
	bool m_IsHit;
	float m_FlagPoleYPos;
};
