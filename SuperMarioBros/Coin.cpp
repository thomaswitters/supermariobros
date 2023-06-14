#include "pch.h"
#include "Coin.h"

Coin::Coin(Point2f GameItemPos) : GameItem(GameItemType::CoinType, "Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true, "Sounds/super-mario-coin-sound.mp3")
, m_PosCoin{ GetGameItemPos().x, GetGameItemPos().y }
, m_NrOfFrames{4}
, m_NrFramesPerSec{0.2f}
, m_AnimTime{}
, m_AnimFrame{}
, m_IsHit{false}
, m_Teller{}
{

}
Coin::~Coin()
{

}
void Coin::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 36 };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 14 };

	Rectf src{ GetSpriteClipWidth() * (0 + m_AnimFrame), GetSpriteClipHeight() * 7,sourceWidth,sourceHeight };
	Rectf dst{ m_PosCoin.x , m_PosCoin.y,sourceWidth, sourceHeight };

	GetSpriteTexture()->Draw(dst, src);
}
void Coin::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom)
	{
		if (m_Teller == 0.f)
		{
			gameState->SetAmountCoinsPlus(1);
			GetSoundEffect()->SetVolume(70);
			GetSoundEffect()->Play(false);
		}
		
		m_IsHit = true;
		
	}
}
void Coin::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	m_AnimTime += elapsedSec;
	int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
	m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

	if (m_IsHit)
	{
		
		if (m_Teller < 11)
		{
			m_PosCoin.y = m_PosCoin.y + 2.5f;
			m_Teller = m_Teller + 0.5f;
		}
		else if (m_Teller >= 11 && m_Teller < 22)
		{
			m_PosCoin.y = m_PosCoin.y - 2.5f;
			m_Teller = m_Teller + 0.5f;
		}
		else if (m_Teller >= 22)
		{
			SetActivefalse();
		}

	}
}

