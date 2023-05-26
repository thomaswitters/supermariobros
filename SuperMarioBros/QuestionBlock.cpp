#include "pch.h"
#include "QuestionBlock.h"
#include "ConcreteBlockQ.h"

QuestionBlock::QuestionBlock(Point2f GameItemPos) : GameItem(GameItemType::QuestionBlockType, "Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true, "")
, m_Velocity{ 0.f, 0.f }
, m_Acceleration{ 0.f, -981.f }
, m_BeginPosY{ GetGameItemPos().y }
, m_NrOfFrames{ 2 }
, m_NrFramesPerSec{ 0.3f }
, m_AnimTime{}
, m_AnimFrame{}
, m_Counter{}
, m_IsHitFlower{false}
, m_IsHitMushRoom{false}
{

}
QuestionBlock::~QuestionBlock()
{

}
void QuestionBlock::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ 16.f * (15 + m_AnimFrame),16.f ,sourceWidth,sourceHeight };
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight };

	utils::SetColor(Color4f(0.36f, 0.58f, 0.99f, 1.f));
	utils::FillRect(GetGameItemPos().x, m_BeginPosY, sourceWidth, sourceHeight);

	GetSpriteTexture()->Draw(dst, src);
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, 16.f, 16.f);
}
void QuestionBlock::CollisionDetect(GameState* gameState) {
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
		
		//avatarRect.bottom = itemRect.bottom - avatarRect.height;
		if(avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType || avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType)
		{
			m_Velocity.y = float(sqrt(2.0f * 981.f * 6));
			m_IsHitFlower = true;
		}
		else if (avatarState->GetCurrentAvatar()->getAvatarType() == NormalManType)
		{
			m_Velocity.y = float(sqrt(2.0f * 981.f * 6));
			m_IsHitMushRoom = true;
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
/*
voor het blokje dat wordt vernietigd en een nieuw blokje maakt:
gameState->getLevel()->addGameItem(new BetonBlock(positie van mij);
gameState->getLevel()->deactivateGameItem(this);
*/
bool QuestionBlock::CollisionDetectOnGround(AvatarState* avatarState) {
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
void QuestionBlock::UpdateGameItem(float elapsedSec, GameState* gameState)
{
	Level* level = gameState->GetLevel();
	m_AnimTime += elapsedSec;
	int totalFramesElapsed{ int(m_AnimTime / m_NrFramesPerSec) };
	m_AnimFrame = totalFramesElapsed % m_NrOfFrames;

	m_Velocity += m_Acceleration * elapsedSec;
	SetPositionVelocity(m_Velocity, elapsedSec);


	if (GetGameItemPos().y <= m_BeginPosY)
	{
		m_Velocity.y = 0.f;
		SetGameItemPosY(m_BeginPosY);
	}
	if (m_IsHitFlower || m_IsHitMushRoom)
	{
		m_Counter++;
		if (m_Counter >= 15.f)
		{
			SetActivefalse();
			level->AddGameItem(new ConcreteBlockQ(Point2f(GetGameItemPos().x, m_BeginPosY)));
		}

		//std::cout << m_Counter << std::endl;
	}
}

