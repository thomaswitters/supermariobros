#include "pch.h"
#include "DecorBlock.h"

DecorBlock::DecorBlock(Point2f GameItemPos) : GameItem(GameItemType::DecorBlockType, "Images/tiles.png", 8.f, 8.f, GameItemPos, 16.f, 16.f, true, "")
, m_IsHit{false}
, m_BeginPosSquar1{ GetGameItemPos().x, GetGameItemPos().y}
, m_BeginPosSquar2{ GetGameItemPos().x , GetGameItemPos().y + GetGameItemHeight()/2}
, m_BeginPosSquar3{ GetGameItemPos().x + GetGameItemWidth()/2, GetGameItemPos().y + GetGameItemHeight()/2}
, m_BeginPosSquar4{ GetGameItemPos().x + GetGameItemWidth()/2, GetGameItemPos().y}
, m_Velocity1{ 0.f, 0.f }
, m_Velocity2{ 0.f, 0.f }
, m_Velocity3{ 0.f, 0.f }
, m_Velocity4{ 0.f, 0.f }
, m_Acceleration1{ -120.f, -781.f }
, m_Acceleration2{ -100.f, -781.f }
, m_Acceleration3{ 100.f, -781.f }
, m_Acceleration4{ 120.f, -781.f }
, m_CountHit{}
{

}
DecorBlock::~DecorBlock()
{

}
void DecorBlock::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 42.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 56.f };

	Rectf src1{ GetSpriteClipWidth() * 2, GetSpriteClipHeight() * 2,sourceWidth,sourceHeight};
	Rectf dst1{ m_BeginPosSquar1.x, m_BeginPosSquar1.y, sourceWidth, sourceHeight};

	Rectf src2{ GetSpriteClipWidth() * 2, GetSpriteClipHeight(),sourceWidth,sourceHeight};
	Rectf dst2{ m_BeginPosSquar2.x, m_BeginPosSquar2.y, sourceWidth, sourceHeight};

	Rectf src3{ GetSpriteClipWidth() * 3, GetSpriteClipHeight(),sourceWidth,sourceHeight};
	Rectf dst3{ m_BeginPosSquar3.x, m_BeginPosSquar3.y, sourceWidth, sourceHeight};

	Rectf src4{ GetSpriteClipWidth() * 3, GetSpriteClipHeight() * 2,sourceWidth,sourceHeight};
	Rectf dst4{ m_BeginPosSquar4.x, m_BeginPosSquar4.y, sourceWidth, sourceHeight};

	

	utils::SetColor(Color4f(0.36f, 0.58f, 0.99f, 1.f));
	utils::FillRect(GetGameItemPos().x, GetGameItemPos().y, sourceWidth*2, sourceHeight*2);

	if (m_IsHit)
	{
		GetSpriteTexture()->Draw(dst1, src1);
		GetSpriteTexture()->Draw(dst2, src2);
		GetSpriteTexture()->Draw(dst3, src3);
		GetSpriteTexture()->Draw(dst4, src4);
	}
	
}
void DecorBlock::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom)
	{
		if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			m_IsHit = true; 
			m_CountHit++;
			if (m_CountHit == 1)
			{
				m_Velocity1.y = float(sqrt(2.0f * 781.f * 10));
				m_Velocity2.y = float(sqrt(2.0f * 781.f * 15));
				m_Velocity3.y = float(sqrt(2.0f * 781.f * 15));
				m_Velocity4.y = float(sqrt(2.0f * 781.f * 10));
			}
			
		}
		
	}
}
void DecorBlock::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();

	if (m_IsHit)
	{	

		

		m_Velocity1 += m_Acceleration1 * elapsedSec;
		m_BeginPosSquar1.x += m_Velocity1.x * elapsedSec;
		m_BeginPosSquar1.y += m_Velocity1.y * elapsedSec;
		
		m_Velocity2 += m_Acceleration2 * elapsedSec;
		m_BeginPosSquar2.x += m_Velocity2.x * elapsedSec;
		m_BeginPosSquar2.y += m_Velocity2.y * elapsedSec;

		m_Velocity3 += m_Acceleration3 * elapsedSec;
		m_BeginPosSquar3.x += m_Velocity3.x * elapsedSec;
		m_BeginPosSquar3.y += m_Velocity3.y * elapsedSec;

		m_Velocity4 += m_Acceleration4 * elapsedSec;
		m_BeginPosSquar4.x += m_Velocity4.x * elapsedSec;
		m_BeginPosSquar4.y += m_Velocity4.y * elapsedSec;
	}
}
