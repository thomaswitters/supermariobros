#pragma once
#include "GameItem.h"

class LiveItem : public GameItem
{
public:
	enum LiveItemState { Alive, Dying, Dead };

	LiveItem(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
		Vector2f velocity, Vector2f acceleration, 
		int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, const std::string& soundPath = "");

	virtual ~LiveItem();

	LiveItemState GetLiveItemState() const;
	void SetLiveItemState(LiveItemState liveItemState);

	void Draw(AvatarState* avatarState) const;

	virtual void UpdateGameItem(float elapsedSec, GameState* gameState) = 0;
	virtual void CollisionDetect(GameState* gameState) = 0;
	virtual void CollisionWithGameItemDetect(GameItem* gameItem) = 0;
	virtual void CollisionWithLiveItemDetect(LiveItem* liveItem) = 0;
	virtual void BounceFloor() {}

	void SetVelocityY(float y)
	{
		m_Velocity.y = y;

	}
	void SetVelocityX(float x)
	{
		m_Velocity.x = x;

	}
	void SetVelocityEnemy(Vector2f acceleration, float elapsedSec)
	{
		m_Velocity += m_Acceleration * elapsedSec;
	}

	Vector2f GetVelocity()
	{
		return m_Velocity;
	}

	/*
	 * Is this LiveItem an enemy of other (enemies). E.g. a fireball shot by the avatar is an enemy
	 */
	virtual bool IsEnemyOf(LiveItem* otherLiveItem) {
		return false;
	}

protected:
	int GetNrOfFrames() 
	{ 
		return m_NrOfFrames; 
	}

	float GetNrFramesPerSec() 
	{
		return m_NrFramesPerSec;
	}

	float GetAnimTime()
	{
		return m_AnimTime;
	}

	int GetAnimFrame() 
	{
		return m_AnimFrame;
	}


protected:
	LiveItemState m_LiveItemState { LiveItemState::Alive };

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	int m_AnimStartFrameX;
	int m_AnimStartFrameY;

	int m_AnimStartDyingFrameX;
	int m_AnimStartDyingFrameY;

	int m_ImageAmountHoriFrames; 
	int m_ImageAmountVertiFrames;

	Vector2f m_Velocity;
	Vector2f m_Acceleration;

	float m_DyingCounter;
};
