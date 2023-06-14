#pragma once
#include <Texture.h>
#include "CollisionDetectionHelper.h"
#include "AvatarState.h"
#include "GameState.h"
#include "Avatar.h"
#include <SoundEffect.h>

class AvatarState;
class GameState;
class Avatar;
class Level;

enum GameItemType {
	NormalBlockType, QuestionBlockType, PipeType, ConcreteBlockQType, ConcreteBlockType, PowerUpType, DecorBlockType, FlagPoleType, CoinType, GoombaType, ProjectileType, CoinPickupType
};

class GameItem
{
public:
	GameItem(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, const std::string& soundPath = "");
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
	virtual bool CanCollide(GameItem* gameItem) { return true; }

	GameItemType GetGameItemType() {
		return m_GameItemType;
	}

protected:
	Texture* GetSpriteTexture() const {
		return m_pSpriteTexture;
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

	SoundEffect* GetSoundEffect() const {
		return m_pSoundEffect;
	}

private:
	GameItemType m_GameItemType;
	bool m_Active;
	Texture* m_pSpriteTexture;
	float m_SpriteClipHeight;
	float m_SpriteClipWidth;
	Point2f m_GameItemPos;
	float m_GameItemWidth;
	float m_GameItemHeight;

	SoundEffect* m_pSoundEffect;
};
