#include "pch.h"
#include "GameItem.h"

GameItem::GameItem(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive)
	: m_SpriteTexture{new Texture(imagePath)}
	, m_SpriteClipHeight{ spriteClipHeight }
	, m_SpriteClipWidth{ spriteClipWidth }
	, m_GameItemPos{ GameItemPos }
	, m_GameItemWidth{ GameItemWidth }
	, m_GameItemHeight{ GameItemHeight }
	, m_Active{ IsActive }
{

}
GameItem::~GameItem()
{
	if (m_SpriteTexture) {
		delete m_SpriteTexture;
		m_SpriteTexture = NULL;
	}
}
void GameItem::Draw(AvatarState* avatarState) const
{

}
void GameItem::CollisionDetect(GameState* gameState)
{

}
bool GameItem::CollisionDetectOnGround(AvatarState* avatarState)
{
	//return true;
	return false;
}
void GameItem::UpdateGameItem(float elapsedSec, Level* level)
{

}
bool GameItem::IsActive()
{
	if (m_Active)
	{
		return true;
	}
	else
	{
		return false;
	}
}


NormalBlock::NormalBlock(Point2f GameItemPos) : GameItem("Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true)
, m_Velocity{0.f, 0.f}
, m_Acceleration{0.f, -981.f}
, m_BeginPosY{ GetGameItemPos().y }
{
	
}
NormalBlock::~NormalBlock()
{
}
void NormalBlock::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f};
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ GetSpriteClipWidth(), GetSpriteClipHeight() ,sourceWidth,sourceHeight};
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight };
	
	GetSpriteTexture()->Draw(dst, src);
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, 16.f, 16.f);
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

		}
		if (avatarState->GetCurrentAvatar()->getAvatarType() == BiggerManType || avatarState->GetCurrentAvatar()->getAvatarType() == FlowerManType)
		{
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
void NormalBlock::UpdateGameItem(float elapsedSec, Level* level)
{
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



QuestionBlock::QuestionBlock(Point2f GameItemPos) : GameItem("Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true)
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
void QuestionBlock::UpdateGameItem(float elapsedSec, Level* level)
{
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
			//gameState.GetLevel()->AddGameItem(new ConcreteBlock(Point2f(GetGameItemPos().x, m_BeginPosY)));
			level->AddGameItem(new ConcreteBlock(Point2f(GetGameItemPos().x, m_BeginPosY)));
		}

		//std::cout << m_Counter << std::endl;
	}
}


ConcreteBlock::ConcreteBlock(Point2f GameItemPos) : GameItem("Images/tiles.png", 16.f, 16.f, GameItemPos, 16.f, 16.f, true)
{

}
ConcreteBlock::~ConcreteBlock()
{

}
void ConcreteBlock::Draw(AvatarState* avatarState) const
{
	float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ GetSpriteClipWidth() * 3, GetSpriteClipHeight() ,sourceWidth,sourceHeight };
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth, sourceHeight };

	GetSpriteTexture()->Draw(dst, src);
}
void ConcreteBlock::CollisionDetect(GameState* gameState) {
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
bool ConcreteBlock::CollisionDetectOnGround(AvatarState* avatarState) {
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


Pipe::Pipe(Point2f GameItemPos, float height) : GameItem("Images/tiles.png", 32.f, 32.f, GameItemPos, 32.f, height, true)
, m_SpriteTextureBottom{ new Texture ("Images/tiles.png") }
{

}
Pipe::~Pipe()
{
	if (m_SpriteTextureBottom) {
		delete m_SpriteTextureBottom;
		m_SpriteTextureBottom = NULL;
	}
}
void Pipe::Draw(AvatarState* avatarState) const
{
	/*float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ 16.f * 15,16.f ,sourceWidth,sourceHeight };
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight };
	GetSpriteTexture()->Draw(dst, src);*/

	float sourceWidth{ GetSpriteTexture()->GetWidth() / 10.5f };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

	Rectf src{ 0.f,32 * 5,sourceWidth,sourceHeight };
	Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight + GetGameItemHeight() - 15.f };

	Rectf src2{ 0.f,32 * 4.5f,sourceWidth,sourceHeight };
	Rectf dst2{ GetGameItemPos().x, GetGameItemPos().y + sourceHeight + GetGameItemHeight() - 15 - 16,sourceWidth, sourceHeight };



	GetSpriteTexture()->Draw(dst, src);
	m_SpriteTextureBottom->Draw(dst2, src2);
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, 16.f, 16.f);
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


PowerUp::PowerUp(Point2f GameItemPos) : GameItem("Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true)
, m_PosPowerUp{ GetGameItemPos().x, GetGameItemPos().y }
, m_Teller{}
, m_IsHitFlower{false}
, m_IsHitMushRoom{false}
, m_CanPickUpFlower{false}
, m_CanPickUpMushRoom{false}
, m_NrOfFrames{ 4 }
, m_NrFramesPerSec{ 0.1f }
, m_AnimTime{}
, m_AnimFrame{}
{

}
PowerUp::~PowerUp()
{

}
void PowerUp::Draw(AvatarState* avatarState) const
{
	if (/*avatarState->GetCurrentAvatar()->getAvatarType() == NormalManType*/m_IsHitMushRoom)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth()/36};
		float sourceHeight{ GetSpriteTexture()->GetHeight()/13};

		Rectf src{ GetSpriteClipWidth()*0, GetSpriteClipHeight(),sourceWidth,sourceHeight };
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
		Rectf (m_PosPowerUp.x, m_PosPowerUp.y, GetGameItemWidth(), GetGameItemHeight()));

	
	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
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
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight:
	{
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
			//GameState.SetAvatar(GameState.GetFlowerMan());
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
	}

}
bool PowerUp::CollisionDetectOnGround(AvatarState* avatarState)
{
	return false;
}
void PowerUp::UpdateGameItem(float elapsedSec, Level* level)
{
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
		if (m_Teller >= 2)
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
		if(m_Teller >= 2)
		{
			m_CanPickUpMushRoom = true;
		}

	}


}


DecorBlock::DecorBlock(Point2f GameItemPos) : GameItem("Images/tiles.png", 8.f, 8.f, GameItemPos, 16.f, 16.f, true)
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
void DecorBlock::UpdateGameItem(float elapsedSec, Level* level)
{
	
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


FlagPole::FlagPole(Point2f GameItemPos) : GameItem("Images/tiles.png", 16.f, 16.f, GameItemPos, 4, 145, true)
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
		m_IsHit = true;
		std::cout << "hit";
	}
	else if (location == CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheRight)
	{
		m_IsHit = true;
		std::cout << "hit";
	}
	else if(location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom)
	{
		m_IsHit = true;
		std::cout << "hit";
	}
	else if(location == CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop)
	{
		m_IsHit = true;
		std::cout << "hit";
	}
}
void FlagPole::UpdateGameItem(float elapsedSec, Level* level)
{
	if (m_IsHit)
	{
		m_FlagPoleYPos = m_FlagPoleYPos -1.5f;
		if (m_FlagPoleYPos <= GetGameItemPos().y)
		{
			m_FlagPoleYPos = GetGameItemPos().y;
			gameState->LevelWon();
		}
	}

}


Coin::Coin(Point2f GameItemPos) : GameItem("Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true)
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
		m_IsHit = true;
	}
}
void Coin::UpdateGameItem(float elapsedSec, Level* level)
{
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


LiveItem::LiveItem(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState, 
	Vector2f velocity, Vector2f acceleration,
	int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, int liveItemType) :
	GameItem(imagePath, spriteClipHeight, spriteClipWidth, GameItemPos, GameItemWidth, GameItemHeight, IsActive)
	, m_NrOfFrames{nrOfFrames}
	, m_NrFramesPerSec{ nrFramesPerSec }
	, m_AnimTime{ 0.0f}
	, m_AnimFrame{ 0 }
	, m_AnimStartFrameX{ animStartFrameX }
	, m_AnimStartFrameY{ animStartFrameY }
	, m_AnimStartDyingFrameX{ animStartDyingFrameX }
	, m_AnimStartDyingFrameY{ animStartDyingFrameY }
	, m_Velocity{ velocity }
	, m_Acceleration{ acceleration }
	, m_DyingCounter{0.f}
	, m_ImageAmountHoriFrames{ imageAmountHoriFrames }
	, m_ImageAmountVertiFrames{ imageAmountVertiFrames }
	, m_LiveItemType{ liveItemType }
{}
LiveItem::~LiveItem() {
}
LiveItem::LiveItemState LiveItem::GetLiveItemState() const {
	return m_LiveItemState;
}
void LiveItem::SetLiveItemState(LiveItemState liveItemState) {
	m_LiveItemState = liveItemState;
}
void LiveItem::Draw(AvatarState* avatarState) const {

	float sourceWidth{ GetSpriteTexture()->GetWidth() / m_ImageAmountHoriFrames };
	float sourceHeight{ GetSpriteTexture()->GetHeight() / m_ImageAmountVertiFrames };

	Rectf src{ };
	Rectf dst{ };

	if (m_LiveItemState == LiveItemState::Alive)
	{
		src = Rectf{ GetSpriteClipWidth() * (m_AnimStartFrameX + m_AnimFrame) , GetSpriteClipHeight() * (m_AnimStartFrameY + 1),sourceWidth,sourceHeight };
		dst = Rectf{ GetGameItemPos().x - GetGameItemWidth()/2, GetGameItemPos().y, sourceWidth,sourceHeight };

	}
	else if (m_LiveItemState == LiveItemState::Dying)
	{

		src = Rectf{ GetSpriteClipWidth() * (m_AnimStartDyingFrameX), GetSpriteClipHeight() * (m_AnimStartDyingFrameY + 1),sourceWidth,sourceHeight };
		dst = Rectf{ GetGameItemPos().x - GetGameItemWidth() / 2, GetGameItemPos().y, sourceWidth,sourceHeight };

	}
	if (m_Velocity.x < 0.f) {
		glPushMatrix();
		glTranslatef(GetGameItemPos().x + GetGameItemWidth() / 2, GetGameItemPos().y + GetGameItemHeight(), 0);
		glScalef(-1, 1, 1);
		glTranslatef(-GetGameItemPos().x - GetGameItemWidth() / 2, -GetGameItemPos().y - GetGameItemHeight(), 0);

		GetSpriteTexture()->Draw(dst, src);
		glPopMatrix();
	}
	else {
		GetSpriteTexture()->Draw(dst, src);
	}
	//utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight());
}


Enemy::Enemy(const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
	Vector2f velocity, Vector2f acceleration,
	int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, int liveItemType) :
	LiveItem(imagePath, spriteClipHeight, spriteClipWidth, GameItemPos, GameItemWidth, GameItemHeight,
		IsActive, liveItemState,
		velocity, acceleration,
		animStartFrameX, animStartFrameY, nrOfFrames, nrFramesPerSec, animStartDyingFrameX, animStartDyingFrameY, imageAmountHoriFrames, imageAmountVertiFrames, liveItemType)
{
}

Enemy::~Enemy() 
{

}
void Enemy::UpdateGameItem(float elapsedSec, Level* level) {
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
				gameState->SetAvatar(gameState->GetNormalMan());
			}
			else
			{
				avatarState->SetActionState(AvatarState::ActionState::dead);
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
				gameState->SetAvatar(gameState->GetNormalMan());
			}
			else
			{
				avatarState->SetActionState(AvatarState::ActionState::dead);
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
				gameState->SetAvatar(gameState->GetNormalMan());
			}
			else
			{
				avatarState->SetActionState(AvatarState::ActionState::dead);
			}
		}
		break;
	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		if (m_LiveItemState == LiveItemState::Alive)
		{
			m_LiveItemState = LiveItemState::Dying;
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

}

Goomba::Goomba(Point2f GameItemPos) : Enemy("Images/smb_enemies_sheet.png", 30, 30, GameItemPos, 16, 20, true, LiveItemState::Alive,
	Vector2f{-30.0f, 0.f}, Vector2f{0.0f, -581.0f},
	0, 0, 2, 0.2f, 2, 0, 15, 7, GOOMBA_TYPE)
{
}
Goomba::~Goomba() {
}

Projectile::Projectile(Point2f GameItemPos) : LiveItem("Images/fireball.png", 12, 12, GameItemPos, 12, 12, true, LiveItemState::Dying,
	Vector2f{ 140.0f, 0.f }, Vector2f{ 0.0f, -400.f},
	0, 0, 2, 0.2f, 2, 0, 3, 1, PROJECTILE_TYPE)
{
}
Projectile::~Projectile() {
}
void Projectile::UpdateGameItem(float elapsedSec, Level* level)
{
	

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
		Rectf(GetGameItemPos().x - GetGameItemWidth() / 2,
			GetGameItemPos().y,
			GetGameItemWidth(),
			GetGameItemHeight()),
		GetVelocity(),
		Rectf(gameItem->GetGameItemPos().x,
			gameItem->GetGameItemPos().y,
			gameItem->GetGameItemWidth(),
			gameItem->GetGameItemHeight()/2
		)
	);
	
	switch (location)
	{
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheBottom:
	{

		m_LiveItemState = LiveItemState::Dying;
		break;

	}
	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{

		m_Velocity.y = float(sqrt(2.0f * 400.f * 10));
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
	if (this == liveItem) return;
	if (IsEnemyOf(liveItem)) {
		CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
			Rectf(GetGameItemPos().x - GetGameItemWidth() / 2,
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
			liveItem->SetLiveItemState(LiveItemState::Dying);
			m_LiveItemState = LiveItemState::Dying;
			break;

		}
		case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
		{
			liveItem->SetLiveItemState(LiveItemState::Dying);
			m_LiveItemState = LiveItemState::Dying;
			break;

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
	return otherLiveItem->GetLiveItemType() != GetLiveItemType();
}
