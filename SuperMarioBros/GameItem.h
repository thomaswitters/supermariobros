#pragma once
#include <Texture.h>
#include "CollisionDetectionHelper.h"
#include "AvatarState.h"
#include "GameState.h"
#include "Avatar.h"

class AvatarState;
class GameState;
class Avatar;
class Level;

class GameItem
{
public:
	GameItem(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive);
	virtual ~GameItem();
	virtual void Draw(AvatarState* avatarState) const;
	virtual void CollisionDetect(GameState* gameState);
	virtual bool CollisionDetectOnGround(AvatarState* avatarState);
	virtual void UpdateGameItem(float elapsedSec, GameState* gameState);
	bool IsActive();
	Point2f GetGameItemPos() const {
		return m_GameItemPos;
	}
	float GetGameItemWidth() const {
		return m_GameItemWidth;
	}
	float GetGameItemHeight() const {
		return m_GameItemHeight;
	}
	void SetGameItemPosY(float y)
	{
		m_GameItemPos.y = y;
	}
	void SetGameItemPosX(float x)
	{
		m_GameItemPos.x = x;
	}

protected:
	Texture* GetSpriteTexture() const {
		return m_SpriteTexture;
	}
	float GetSpriteClipHeight() const {
		return m_SpriteClipHeight;
	}
	float GetSpriteClipWidth() const {
		return m_SpriteClipWidth;
	}
	
	
	void SetPositionVelocity(Vector2f velocity, float elapsedSec)
	{
//		m_GameItemPos += velocity * elapsedSec;
		m_GameItemPos.x += velocity.x * elapsedSec;
		m_GameItemPos.y += velocity.y * elapsedSec;
	}
	
	void SetActivefalse()
	{
		m_Active = false;
	}

private:
	bool m_Active;
	Texture* m_SpriteTexture;
	float m_SpriteClipHeight;
	float m_SpriteClipWidth;
	Point2f m_GameItemPos;
	float m_GameItemWidth;
	float m_GameItemHeight;
};

class NormalBlock : public GameItem
{
public:
	NormalBlock(Point2f GameItemPos);
	virtual ~NormalBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_BeginPosY;
};

class QuestionBlock : public GameItem
{
public:
	QuestionBlock(Point2f GameItemPos);
	virtual ~QuestionBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
protected:
	bool GetIsHitFlower() const
	{
		return m_IsHitFlower;
	}
	bool GetIsHitMushRoom() const
	{
		return m_IsHitMushRoom;
	}

private:
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_BeginPosY;
	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
	float m_Counter;

	bool m_IsHitFlower;
	bool m_IsHitMushRoom;
};

class ConcreteBlock : public GameItem
{
public:
	ConcreteBlock(Point2f GameItemPos);
	virtual ~ConcreteBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	//void UpdateGameItem(float elapsedSec);
};

class Pipe : public GameItem
{
public:
	Pipe(Point2f GameItemPos, float height);
	virtual ~Pipe();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
private:
	Texture* m_SpriteTextureBottom;
};


class PowerUp : public GameItem
{
public:
	PowerUp(Point2f GameItemPos);
	virtual ~PowerUp();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosPowerUp;
	float m_Teller;

	bool m_IsHitFlower;
	bool m_IsHitMushRoom;
	bool m_CanPickUpFlower;
	bool m_CanPickUpMushRoom;

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;
};



class DecorBlock : public GameItem
{
public:
	DecorBlock(Point2f GameItemPos);
	virtual ~DecorBlock();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	bool m_IsHit;
	Point2f m_BeginPosSquar1;
	Point2f m_BeginPosSquar2;
	Point2f m_BeginPosSquar3;
	Point2f m_BeginPosSquar4;
	Vector2f m_Velocity1;
	Vector2f m_Velocity2;
	Vector2f m_Velocity3;
	Vector2f m_Velocity4;
	Vector2f m_Acceleration1;
	Vector2f m_Acceleration2;
	Vector2f m_Acceleration3;
	Vector2f m_Acceleration4;

	int m_CountHit;
};

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

class Coin : public GameItem
{
public:
	Coin(Point2f GameItemPos);
	virtual ~Coin();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(GameState* gameState);
	void UpdateGameItem(float elapsedSec, GameState* gameState);
private:
	Point2f m_PosCoin;

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	bool m_IsHit;
	float m_Teller;

};

class LiveItem : public GameItem
{
public:
	enum LiveItemState { Alive, Dying, Dead };

	LiveItem(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState, 
		Vector2f velocity, Vector2f acceleration, 
		int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, int liveItemType);

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

	int GetLiveItemType()
	{
		return m_LiveItemType;
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

	int m_LiveItemType;	// int to allow pluggable live items
};

class Enemy : public LiveItem
{
public:
	Enemy(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
		Vector2f velocity, Vector2f acceleration,
		int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, int liveItemType);

	virtual ~Enemy();

	virtual void UpdateGameItem(float elapsedSec, GameState* gameState);
	virtual void CollisionDetect(GameState* gameState);
	virtual void CollisionWithGameItemDetect(GameItem* gameItem);
	virtual void CollisionWithLiveItemDetect(LiveItem* liveItem);
};

#define GOOMBA_TYPE 1
class Goomba : public Enemy
{
public:
	Goomba(Point2f GameItemPos);
	virtual ~Goomba();
};

#define PROJECTILE_TYPE 2
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
