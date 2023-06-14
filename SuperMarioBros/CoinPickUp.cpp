#include "pch.h"
#include "CoinPickup.h"

CoinPickup::CoinPickup(Point2f GameItemPos) : GameItem(GameItemType::CoinPickupType,"Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true, "Sounds/smb_powerup.wav")
	, m_PosCoin{ GetGameItemPos().x , GetGameItemPos().y }
	, m_NrOfFrames{ 4 }
	, m_NrFramesPerSec{ 0.2f }
	, m_AnimTime{}
	, m_AnimFrame{}
{

}

CoinPickup::~CoinPickup()
{

}
void CoinPickup::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 36 };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 14 };

	Rectf src{ GetSpriteClipWidth() * (0 + m_AnimFrame), GetSpriteClipHeight() * 6,sourceWidth,sourceHeight };
	Rectf dst{ m_PosCoin.x , m_PosCoin.y,sourceWidth, sourceHeight };

	GetSpriteTexture()->Draw(dst, src);
}
void CoinPickup::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()),
		Vector2f(avatarState->GetVelocityAvatar()),
		Rectf(m_PosCoin.x, m_PosCoin.y, GetGameItemWidth(), GetGameItemHeight()));


	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		gameState->SetAmountCoinsPlus(1);
		SetActivefalse();
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		gameState->SetAmountCoinsPlus(1);
		SetActivefalse();
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		gameState->SetAmountCoinsPlus(1);
		SetActivefalse();
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		gameState->SetAmountCoinsPlus(1);
		SetActivefalse();
		break;
	}
	}
}
void CoinPickup::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	m_AnimTime += elapsedSec;
	int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
	m_AnimFrame = totalFramesElapsed % m_NrOfFrames;
}