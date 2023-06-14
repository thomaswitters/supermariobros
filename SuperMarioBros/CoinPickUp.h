#pragma once
#include "GameItem.h"

class CoinPickup : public GameItem
{
public:
	CoinPickup();
	CoinPickup(Point2f GameItemPos);
	virtual ~CoinPickup();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosCoin;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
};