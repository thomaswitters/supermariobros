#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(Point2f GameItemPos, ProjectileDirection projectileDirection) : LiveItem(GameItemType::ProjectileType, "Images/fireball.png", 12, 12, GameItemPos, 7, 7, true, LiveItemState::Dying,
	Vector2f{ 240.0f, 0.f }, Vector2f{ 0.0f, -800.f},
	0, 0, 2, 0.2f, 2, 0, 3, 1, "Sounds/smb_fireball.wav")
{
	GetSoundEffect()->SetVolume(30);
	GetSoundEffect()->Play(false);
	if (projectileDirection == ProjectileDirection::Left)
	{
		SetVelocityX(-240.f);
	}
	else
	{
		SetVelocityX(240.f);
	}
}

Projectile::~Projectile() {
}

void Projectile::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();

	
	//SetGameItemPosY(GetGameItemPos().y + float(1.5f * GolfbewegingInPercent(m_AnimTime, 1.f)));
	switch (m_LiveItemState) {
	case LiveItemState::Alive:
	{
		m_AnimTime += elapsedSec;
		int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
		m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

		m_Velocity += m_Acceleration * elapsedSec;
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
void Projectile::CollisionDetect(GameState* gameState)
{

}
void Projectile::CollisionWithGameItemDetect(GameItem* gameItem)
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
			gameItem->GetGameItemHeight()-10
		)
	);
	
	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{
		//if(gameItem.get)
		m_LiveItemState = LiveItemState::Dying;
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{

		m_Velocity.y = float(sqrt(2.0f * 400.f * 10));
		//m_LiveItemState = LiveItemState::Dying;

		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
		m_LiveItemState = LiveItemState::Dying;
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		m_LiveItemState = LiveItemState::Dying;
		break;

	}
	}
}
void Projectile::CollisionWithLiveItemDetect(LiveItem* liveItem)
{
	//if (this == liveItem) return;
	if (IsEnemyOf(liveItem)) {
		CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
			Rectf(GetGameItemPos().x,
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

		if (liveItem->GetLiveItemState() != LiveItemState::Dying)
		{
			switch (location)
			{
			case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
			case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
			case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
			{

				if (m_LiveItemState != LiveItemState::Dying)
				{
					liveItem->SetLiveItemState(LiveItemState::Dying);
				}


				SetLiveItemState(LiveItemState::Dying);


				break;

			}
			}
		}
		
	}
}
void Projectile::BounceFloor()
{
	m_Velocity.y = float(sqrt(2.0f * 400.f * 10));
}
bool Projectile::IsEnemyOf(LiveItem* otherLiveItem) 
{
	return otherLiveItem->GetGameItemType() != GetGameItemType();
}


