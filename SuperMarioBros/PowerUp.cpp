#include "pch.h"
#include "PowerUp.h"

PowerUp::PowerUp(Point2f GameItemPos) : GameItem(GameItemType::PowerUpType, "Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true, "Sounds/smb_powerup.wav")
, m_PosPowerUp{ GetGameItemPos().x, GetGameItemPos().y }
, m_Teller{}
, m_IsHitFlower{ false }
, m_IsHitMushRoom{ false }
, m_CanPickUpFlower{ false }
, m_CanPickUpMushRoom{ false }
, m_NrOfFrames{ 4 }
, m_NrFramesPerSec{ 0.1f }
, m_AnimTime{}
, m_AnimFrame{}
, m_Velocity{ 0.f, 0.f }
, m_Acceleration{ 0.f, -598.f }
{

}
PowerUp::~PowerUp()
{

}
void PowerUp::Draw(AvatarState* avatarState) const
{
	if (/*avatarState->GetCurrentAvatar()->getAvatarType() == NormalManType*/m_IsHitMushRoom)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 36 };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 13 };

		Rectf src{ GetSpriteClipWidth() * 0, GetSpriteClipHeight(),sourceWidth,sourceHeight };
		Rectf dst{ m_PosPowerUp.x,m_PosPowerUp.y,sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
		//utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight);
	}
	else if (/*avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType*/m_IsHitFlower)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 36 };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 14 };

		Rectf src{ GetSpriteClipWidth() * (0 + m_AnimFrame), GetSpriteClipHeight() * 3,sourceWidth,sourceHeight };
		Rectf dst{ m_PosPowerUp.x, m_PosPowerUp.y,sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
		//utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
		//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight);
	}

}
void PowerUp::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()),
		Vector2f(avatarState->GetVelocityAvatar()),
		Rectf(m_PosPowerUp.x, m_PosPowerUp.y, GetGameItemWidth(), GetGameItemHeight()));


	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		if (m_CanPickUpFlower)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);
			gameState->SetAvatar(gameState->GetFlowerMan());
			SetActivefalse();
		}
		if (m_CanPickUpMushRoom)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);
			gameState->SetAvatar(gameState->GetBiggerMan());
			SetActivefalse();
		}
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		if (m_CanPickUpFlower)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);

			gameState->SetAvatar(gameState->GetFlowerMan());
			SetActivefalse();
		}
		if (m_CanPickUpMushRoom)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);
			gameState->SetAvatar(gameState->GetBiggerMan());
			SetActivefalse();
		}

		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			if (!m_IsHitMushRoom)
			{
				m_IsHitFlower = true;
			}

		}
		else if (avatarState->GetCurrentAvatar()->getAvatarType() == NormalManType)
		{
			if (!m_IsHitFlower)
			{
				m_IsHitMushRoom = true;
			}
		}

		if (m_CanPickUpFlower)
		{
			gameState->SetAvatar(gameState->GetFlowerMan());
			
			SetActivefalse();

		}
		if (m_CanPickUpMushRoom)
		{
			gameState->SetAvatar(gameState->GetBiggerMan());
			SetActivefalse();
		}
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		
		if (m_CanPickUpFlower)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);
			//GameState.SetAvatar(GameState.GetFlowerMan());
			gameState->SetAvatar(gameState->GetFlowerMan());
			SetActivefalse();

		}
		if (m_CanPickUpMushRoom)
		{
			GetSoundEffect()->SetVolume(30);
			GetSoundEffect()->Play(false);
			gameState->SetAmountPointsPlus(1000);
			gameState->SetAvatar(gameState->GetBiggerMan());
			SetActivefalse();
		}
		break;
	}
	}

}
bool PowerUp::CollisionDetectOnGround(AvatarState* avatarState)
{
	return false;
}
void PowerUp::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	m_AnimTime += elapsedSec;
	int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
	m_AnimFrame = totalFramesElapsed % m_NrOfFrames;



	if (m_IsHitFlower)
	{
		if (m_Teller < 16)
		{
			m_PosPowerUp.y = m_PosPowerUp.y + 0.5f;
			m_Teller = m_Teller + 0.5f;

		}
		if (m_Teller >= 10)
		{
			m_CanPickUpFlower = true;
		}

	}
	if (m_IsHitMushRoom)
	{
		if (m_Teller < 16)
		{
			m_PosPowerUp.y = m_PosPowerUp.y + 0.5f;
			m_Teller = m_Teller + 0.5f;
		}
		if (m_Teller >= 10)
		{
			m_CanPickUpMushRoom = true;
			/*m_Velocity += m_Acceleration * elapsedSec;
			m_PosPowerUp.x += m_Velocity.x * elapsedSec;
			m_PosPowerUp.y += m_Velocity.y * elapsedSec;*/
		}

	}


}

