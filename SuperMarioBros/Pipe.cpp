#include "pch.h"
#include "Pipe.h"

Pipe::Pipe(Point2f GameItemPos, float spriteClipHeight, float spriteClipWidth, float GameItemWidth, float GameItemHeight, Point2f* transportToPos) : GameItem(GameItemType::PipeType, "Images/tiles.png", spriteClipHeight, spriteClipWidth, GameItemPos, GameItemWidth, GameItemHeight, true, "")
, m_pSpriteTextureBottom{ new Texture("Images/tiles.png") }
, m_transportToPos(transportToPos)
{

}
Pipe::~Pipe()
{
	if (m_transportToPos) {
		delete m_transportToPos;
		m_transportToPos = NULL;
	}
	if (m_pSpriteTextureBottom) {
		delete m_pSpriteTextureBottom;
		m_pSpriteTextureBottom = NULL;
	}
}
void Pipe::CollisionDetect(GameState* gameState) {
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()),
		Vector2f(avatarState->GetVelocityAvatar()),
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		avatarState->SetVelocityXCollisionAvatar(0.f);
		avatarState->SetPositionXCollisionLeftAvatar(GetGameItemPos().x, avatarState->GetCurrentAvatar()->GetAvatarWidth());
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		avatarState->SetVelocityXCollisionAvatar(-1.f);
		avatarState->SetPositionXCollisionRightAvatar(GetGameItemPos().x, GetGameItemWidth());
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		avatarState->SetIsJumpingfalse();
		avatarState->SetVelocityYCollisionBottomAvatar();
		avatarState->SetPositionYCollisionBottomAvatar(GetGameItemPos().y, avatarState->GetCurrentAvatar()->GetAvatarHeight());
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		avatarState->SetVelocityYCollisionTopAvatar();
		avatarState->SetPositionYCollisionTopAvatar(GetGameItemPos().y, GetGameItemHeight());
		break;
	}
	}

}
bool Pipe::CollisionDetectOnGround(AvatarState* avatarState) {
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
