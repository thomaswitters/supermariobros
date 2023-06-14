#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
	Vector2f velocity, Vector2f acceleration,
	int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, const std::string& soundPath) :
	LiveItem(gameItemType, imagePath, spriteClipHeight, spriteClipWidth, GameItemPos, GameItemWidth, GameItemHeight,
		IsActive, liveItemState,
		velocity, acceleration,
		animStartFrameX, animStartFrameY, nrOfFrames, nrFramesPerSec, animStartDyingFrameX, animStartDyingFrameY, imageAmountHoriFrames, imageAmountVertiFrames, soundPath)
{
}

Enemy::~Enemy() 
{

}
void Enemy::UpdateGameItem(float elapsedSec, GameState* gameState) {
	Level* level = gameState->GetLevel();
	switch (m_LiveItemState) {
	case LiveItemState::Alive:
	{ 
		m_AnimTime += elapsedSec;
		int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) }; 
		m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

		SetVelocityEnemy(m_Acceleration, elapsedSec);
		/*m_Velocity += m_Acceleration * elapsedSec;  */
		SetPositionVelocity(m_Velocity, elapsedSec);
		break;
	}
	case LiveItemState::Dying:
	{
		m_DyingCounter = m_DyingCounter + elapsedSec;
		if (m_DyingCounter > 1.f)
		{
			m_LiveItemState = LiveItemState::Dead;
			SetActivefalse();
		}
		break;
	}
	}
}
void Enemy::CollisionDetect(GameState* gameState) {
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()),
		GetVelocity()
		);

	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		if (m_LiveItemState == LiveItemState::Alive)
		{
			// todo: should become gameState->die()
			if (gameState->GetAvatarState()->GetCurrentAvatar()->getAvatarType() != NormalManType)
			{
				//gameState->SetAvatar(gameState->GetNormalMan());
				gameState->ResetAvatar();
			}
			else
			{
				if (gameState->GetAvatarState()->GetActionState() != AvatarState::ActionState::dead && gameState->GetAvatarState()->GetCanBeHit() == true)
				{
					gameState->PlayerDies();
					gameState->GetAvatarState()->SetVelocityXCollisionAvatar(0.f);
					gameState->GetAvatarState()->SetVelocityYAvatar(float(sqrt(2.0f * 981.f * 100)));
				}
			}
			
		}
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		if (m_LiveItemState == LiveItemState::Alive)
		{
			if (gameState->GetAvatarState()->GetCurrentAvatar()->getAvatarType() != NormalManType)
			{
				//gameState->SetAvatar(gameState->GetNormalMan());
				gameState->ResetAvatar();
			}
			else
			{
				if (gameState->GetAvatarState()->GetActionState() != AvatarState::ActionState::dead && gameState->GetAvatarState()->GetCanBeHit() == true)
				{
					gameState->PlayerDies();
					gameState->GetAvatarState()->SetVelocityXCollisionAvatar(0.f);
					gameState->GetAvatarState()->SetVelocityYAvatar(float(sqrt(2.0f * 981.f * 100)));
				}
			}
		}
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		if (m_LiveItemState == LiveItemState::Alive)
		{
			if (gameState->GetAvatarState()->GetCurrentAvatar()->getAvatarType() != NormalManType)
			{
				//gameState->SetAvatar(gameState->GetNormalMan());
				gameState->ResetAvatar();
			}
			else
			{
				if (gameState->GetAvatarState()->GetActionState() != AvatarState::ActionState::dead && gameState->GetAvatarState()->GetCanBeHit() == true)
				{
					gameState->PlayerDies();
					gameState->GetAvatarState()->SetVelocityXCollisionAvatar(0.f);
					gameState->GetAvatarState()->SetVelocityYAvatar(float(sqrt(2.0f * 981.f * 100)));
				}
			}
		}
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		if (m_LiveItemState == LiveItemState::Alive)
		{
			if (gameState->GetAvatarState()->GetActionState() != AvatarState::ActionState::dead)
			{
				gameState->GetAvatarState()->SetVelocityYAvatar(float(sqrt(2.0f * 981.f * 10)));
			}
		}
		if (m_LiveItemState == LiveItemState::Alive)
		{
			if (gameState->GetAvatarState()->GetActionState() != AvatarState::ActionState::dead)
			{
				m_LiveItemState = LiveItemState::Dying;
			}
			
		}
		
		break;
	}
	}

}
void Enemy::CollisionWithGameItemDetect(GameItem* gameItem)
{
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(GetGameItemPos().x,
			GetGameItemPos().y,
			GetGameItemWidth(),
			GetGameItemHeight()),
		GetVelocity(),
		Rectf(gameItem->GetGameItemPos().x,
			gameItem->GetGameItemPos().y,
			gameItem->GetGameItemWidth(),
			gameItem->GetGameItemHeight()
		)
	);

	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		
		m_Velocity.x *= (-1);
		SetGameItemPosX(gameItem->GetGameItemPos().x - GetGameItemWidth());
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{

		m_Velocity.x *= (-1);
		SetGameItemPosX(gameItem->GetGameItemPos().x + GetGameItemWidth()*2);
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{

		SetVelocityY(0.f);
		SetGameItemPosY(gameItem->GetGameItemPos().y + gameItem->GetGameItemHeight());
		break;

	}
	}
}
void Enemy::CollisionWithLiveItemDetect(LiveItem* liveItem)
{
	if (this == liveItem) return;
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(GetGameItemPos().x ,
			GetGameItemPos().y,
			GetGameItemWidth(),
			GetGameItemHeight()),
		GetVelocity(),
		Rectf(liveItem->GetGameItemPos().x,
			liveItem->GetGameItemPos().y,
			liveItem->GetGameItemWidth(),
			liveItem->GetGameItemHeight()
		),
		liveItem->GetVelocity()
	);
	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
			
		m_Velocity.x *= (-1);
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		m_Velocity.x *= (-1);
		break;

	}
	}
}
