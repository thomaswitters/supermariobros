#include "pch.h"
#include "GameItem.h"

GameItem::GameItem(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, const std::string& soundPath)
	: m_GameItemType{ gameItemType }
	, m_pSpriteTexture{new Texture(imagePath)}
	, m_SpriteClipHeight{ spriteClipHeight }
	, m_SpriteClipWidth{ spriteClipWidth }
	, m_GameItemPos{ GameItemPos }
	, m_GameItemWidth{ GameItemWidth }
	, m_GameItemHeight{ GameItemHeight }
	, m_Active{ IsActive }
	, m_pSoundEffect{new SoundEffect(soundPath)}
{

}
GameItem::~GameItem()
{
	if (m_pSpriteTexture) {
		delete m_pSpriteTexture;
		m_pSpriteTexture = NULL;
	}
	if (m_pSoundEffect) {
		delete m_pSoundEffect;
		m_pSoundEffect = NULL;
	}
}
void GameItem::Draw(AvatarState* avatarState) const
{

}
void GameItem::CollisionDetect(GameState* gameState)
{

}
bool GameItem::CollisionDetectOnGround(AvatarState* avatarState)
{
	//return true;
	return false;
}
void GameItem::UpdateGameItem(float elapsedSec, GameState* gameState)
{

}
bool GameItem::IsActive()
{
	return m_Active;
}

