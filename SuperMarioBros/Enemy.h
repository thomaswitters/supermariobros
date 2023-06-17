#pragma once
#include "LiveItem.h"

class Enemy : public LiveItem
{
public:
	Enemy(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
		Vector2f velocity, Vector2f acceleration,
		int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, const std::string& soundPath = "");

	virtual ~Enemy();

	virtual void UpdateGameItem(float elapsedSec, GameState* gameState) = 0;
	virtual void CollisionDetect(GameState* gameState);
	virtual void CollisionWithGameItemDetect(GameItem* gameItem);
	virtual void CollisionWithLiveItemDetect(LiveItem* liveItem);
};
