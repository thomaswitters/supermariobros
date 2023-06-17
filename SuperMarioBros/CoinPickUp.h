#pragma once
#include "GameItem.h"

class CoinPickup : public GameItem
{
public:
	CoinPickup(Point2f GameItemPos);
	virtual ~CoinPickup();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
	virtual bool CanCollide(GameItem* gameItem) {
		if (gameItem->GetGameItemType() == GameItemType::FishType) return false;
		return true;
	}
private:
	Point2f m_PosCoin;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
};