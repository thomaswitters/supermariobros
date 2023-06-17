#include "pch.h"
#include "NormalBlock.h"

NormalBlock::NormalBlock(Point2f GameItemPos, KindOfNormalBlock normalBlockType) : GameItem(GameItemType::NormalBlockType, "Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true, "Sounds/smb_bump.wav")
, m_Velocity{0.f, 0.f}
, m_Acceleration{0.f, -981.f}
, m_BeginPosY{ GetGameItemPos().y }
, m_NormalBlockType{ normalBlockType }
{
	
}
NormalBlock::~NormalBlock()
{
}
void NormalBlock::Draw(AvatarState* avatarState) const
{
	if (m_NormalBlockType == KindOfNormalBlock::Outside)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

		Rectf src{ GetSpriteClipWidth(), GetSpriteClipHeight() ,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
	}
	else if (m_NormalBlockType == KindOfNormalBlock::Underground)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

		Rectf src{ GetSpriteClipWidth()*2, GetSpriteClipHeight()*3 ,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
	}
}
void NormalBlock::CollisionDetect(GameState* gameState) {
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(		avatarState->GetPositionAvatar().x, 
					avatarState->GetPositionAvatar().y, 
					avatarState->GetCurrentAvatar()->GetAvatarWidth(), 
					avatarState->GetCurrentAvatar()->GetAvatarHeight()
		), 
		avatarState->GetVelocityAvatar(), 
		Rectf(		GetGameItemPos().x, 
					GetGameItemPos().y, 
					GetGameItemWidth(), 
					GetGameItemHeight())
	);
	
	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		//avatarRect.left = itemRect.left - avatar.width;
		avatarState->SetVelocityXCollisionAvatar(0.f);
		avatarState->SetPositionXCollisionLeftAvatar(GetGameItemPos().x, avatarState->GetCurrentAvatar()->GetAvatarWidth());
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		//avatarRect.left = itemRect.left + item.width;
		avatarState->SetVelocityXCollisionAvatar(-1.f);
		avatarState->SetPositionXCollisionRightAvatar(GetGameItemPos().x, GetGameItemWidth());
		break;
		
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		//avatarRect.bottom = itemRect.bottom - avatarRect.height;
		if (avatarState->GetCurrentAvatar()->getAvatarType() == NormalManType)
		{
			m_Velocity.y = float(sqrt(2.0f * 981.f * 6));

			GetSoundEffect()->SetVolume(50);
			GetSoundEffect()->Play(false);
		}
		if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
			gameState->SetAmountPointsPlus(50);
			SetActivefalse();
		}
		avatarState->SetIsJumpingfalse();
		avatarState->SetVelocityYCollisionBottomAvatar();
		avatarState->SetPositionYCollisionBottomAvatar(GetGameItemPos().y, avatarState->GetCurrentAvatar()->GetAvatarHeight());
	
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		//avatarRect.bottom = itemRect.bottom + itemRect.height;
		avatarState->SetVelocityYCollisionTopAvatar();
		avatarState->SetPositionYCollisionTopAvatar(GetGameItemPos().y, GetGameItemHeight());
		break;
	}
	}

}
bool NormalBlock::CollisionDetectOnGround(AvatarState* avatarState) {
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop)
	{
		return true;
	}
	return false;
}
void NormalBlock::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	//float beginPos{ GetGameItemPos().y };

//	m_Velocity += m_Acceleration * elapsedSec;
	m_Velocity.x += m_Acceleration.x * elapsedSec;
	m_Velocity.y += m_Acceleration.y * elapsedSec;
	SetPositionVelocity(m_Velocity, elapsedSec);

	if (GetGameItemPos().y <= m_BeginPosY)
	{
		SetGameItemPosY(m_BeginPosY);
	}
}


