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
	virtual void CollisionDetect(AvatarState* avatarState);
	virtual bool CollisionDetectOnGround(AvatarState* avatarState);
	virtual void UpdateGameItem(float elapsedSec, Level* level);
	bool IsActive();


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
	Point2f GetGameItemPos() const {
		return m_GameItemPos;
	}
	float GetGameItemWidth() const {
		return m_GameItemWidth;
	}
	float GetGameItemHeight() const {
		return m_GameItemHeight;
	}
	void SetPositionVelocity(Vector2f velocity, float elapsedSec)
	{
		m_GameItemPos += velocity * elapsedSec;
	}
	void SetGameItemPosY(float y)
	{
		m_GameItemPos.y = y;
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
	void CollisionDetect(AvatarState* avatarState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
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
	void CollisionDetect(AvatarState* avatarState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
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
	void CollisionDetect(AvatarState* avatarState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	//void UpdateGameItem(float elapsedSec);
};

class Pipe : public GameItem
{
public:
	Pipe(Point2f GameItemPos, float height);
	virtual ~Pipe();
	void Draw(AvatarState* avatarState) const;
	void CollisionDetect(AvatarState* avatarState);
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
	void CollisionDetect(AvatarState* avatarState);
	bool CollisionDetectOnGround(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
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
	void CollisionDetect(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
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
	void CollisionDetect(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
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
	void CollisionDetect(AvatarState* avatarState);
	void UpdateGameItem(float elapsedSec, Level* level);
private:
	Point2f m_PosCoin;

	int m_NrOfFrames;
	float m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	bool m_IsHit;
	float m_Teller;

};

