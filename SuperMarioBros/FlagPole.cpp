#include "pch.h"
#include "FlagPole.h"

FlagPole::FlagPole(Point2f GameItemPos) : GameItem(GameItemType::FlagPoleType, "Images/tiles.png", 16.f, 16.f, GameItemPos, 4, 145, true, "Sounds/MarioFinnish.mp3")
, m_pTexture{new Texture("Images/flag.png")}
, m_IsHit{ false }
, m_FlagPoleYPos{ GetGameItemPos().y + (16 * 7.8f) }
{

}
FlagPole::~FlagPole()
{
	if (m_pTexture) {
		delete m_pTexture;
		m_pTexture = NULL;
	}

}
void FlagPole::Draw(AvatarState* avatarState) const
{
	

	float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src1{ (GetSpriteClipWidth()) * 16, (GetSpriteClipHeight()) * 10,sourceWidth,sourceHeight};
	Rectf dst1{ GetGameItemPos().x - GetGameItemWidth()/2 * 3, GetGameItemPos().y, sourceWidth, sourceHeight * 9 };

	//background
	utils::SetColor(Color4f(0.36f, 0.58f, 0.99f, 1.f));
	utils::FillRect(GetGameItemPos().x - GetGameItemWidth() * 4 - 2.f, GetGameItemPos().y + (16 * 7.8f), sourceWidth * 2, sourceHeight * 2);
	//end background

	GetSpriteTexture()->Draw(dst1, src1);

	float sourceWidth3{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight3{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src3{ GetSpriteClipWidth() * 16, GetSpriteClipHeight() * 9,sourceWidth3,sourceHeight3 };
	Rectf dst3{ GetGameItemPos().x - GetGameItemWidth()/2 * 3, GetGameItemPos().y + (16 * 9), sourceWidth3, sourceHeight3};

	GetSpriteTexture()->Draw(dst3, src3);


	float sourceWidth2{ m_pTexture->GetWidth()};
	float sourceHeight2{ m_pTexture->GetHeight()};

	Rectf src2{ GetSpriteClipWidth() * 0.f, GetSpriteClipHeight() * 0.f ,sourceWidth2,sourceHeight2 };
	Rectf dst2{ GetGameItemPos().x - GetGameItemWidth() * 4, m_FlagPoleYPos, sourceWidth2, sourceHeight2 };

	m_pTexture->Draw(dst2, src2);

	//utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), 135);

}
void FlagPole::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft)
	{
		/*if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			
		}*/
		avatarState->SetActionState(AvatarState::ActionState::grabing);
		m_IsHit = true;
	}
	else if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight)
	{
		avatarState->SetActionState(AvatarState::ActionState::grabing);
		m_IsHit = true;
	}
	else if(location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom)
	{
		avatarState->SetActionState(AvatarState::ActionState::grabing);
		m_IsHit = true;
	}
	else if(location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop)
	{
		avatarState->SetActionState(AvatarState::ActionState::grabing);
		m_IsHit = true;
	}
}
void FlagPole::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	if (m_IsHit)
	{
		
		m_FlagPoleYPos = m_FlagPoleYPos -0;
		if (m_FlagPoleYPos <= GetGameItemPos().y)
		{
			m_FlagPoleYPos = GetGameItemPos().y;
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->LevelWon();
		}
	}

}
