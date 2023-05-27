#include "pch.h"
#include "ConcreteBlockQ.h"

ConcreteBlockQ::ConcreteBlockQ(Point2f GameItemPos) : GameItem(GameItemType::ConcreteBlockQType, "Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true, "Sounds/smb_bump.wav")
{

}
ConcreteBlockQ::~ConcreteBlockQ()
{

}
void ConcreteBlockQ::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ GetSpriteClipWidth() * 3, GetSpriteClipHeight() ,sourceWidth,sourceHeight };
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight };

	GetSpriteTexture()->Draw(dst, src);
}
void ConcreteBlockQ::CollisionDetect(GameState* gameState) {
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		//avatarRect.left = itemRect.left + itemRect.width;
		avatarState->SetVelocityXCollisionAvatar(0.f);
		avatarState->SetPositionXCollisionLeftAvatar(GetGameItemPos().x, avatarState->GetCurrentAvatar()->GetAvatarWidth());
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		//avatarRect.left = itemRect.left;
		avatarState->SetVelocityXCollisionAvatar(-1.f);
		avatarState->SetPositionXCollisionRightAvatar(GetGameItemPos().x, GetGameItemWidth());

		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		GetSoundEffect()->SetVolume(30);
		GetSoundEffect()->Play(false);
		//avatarRect.bottom = itemRect.bottom - avatarRect.height;
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
bool ConcreteBlockQ::CollisionDetectOnGround(AvatarState* avatarState) {
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

