#include "pch.h"
#include "Level.h"

#include "pch.h"
#include "Level.h"

Level::Level(const std::string& imagePath, std::vector<std::string> verticesImagePaths  /* EN OOK DE GAMEELEMENTS */)
	: m_Vertices{}
	, m_pBackgroundTexture{new Texture(imagePath)}
	, m_GameItems{}
	, m_LiveItems{}
{
	for (size_t i = 0; i < verticesImagePaths.size(); i++) {
		std::vector<std::vector<Point2f>> m_VerticesTemp;
		SVGParser::GetVerticesFromSvgFile(verticesImagePaths[i], m_VerticesTemp);
		m_Vertices.push_back(m_VerticesTemp);
	}
}

Level::~Level()
{
	if (m_pBackgroundTexture) {
		delete m_pBackgroundTexture;
		m_pBackgroundTexture = NULL;
	}
	for (GameItem* GameItem : m_GameItems)
	{
		delete GameItem;
	}
	for (LiveItem* LiveItem : m_LiveItems)
	{
		delete LiveItem;
	}
}

void Level::DestroyGameItem(GameItem* gameItem) {
	/*GameItem->setActive(false);
	m_GameItems.delete(gameItem);*/
}

void Level::DrawBackground() const
{
	float sourceWidth{ m_pBackgroundTexture->GetWidth() / 14 };
	float sourceHeight{ m_pBackgroundTexture->GetHeight() / 10 };

	Rectf dst{ 0.f, 0.f,sourceWidth, sourceHeight };
	m_pBackgroundTexture->Draw();
}

void Level::HandleCollision(float elapsedSec, GameState* gameState) const
{
	AvatarState* avatarState = gameState->GetAvatarState();
	Point2f AvatarOrigin1{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y };
	Point2f AvatarOrigin2{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y + 30.f };

	Point2f gameItemOrigin1{};
	Point2f gameItemOrigin2{};

	utils::HitInfo
		hitInfo{};
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		
		if (utils::Raycast(m_Vertices.at(i).front(), AvatarOrigin1, AvatarOrigin2, hitInfo))
		{
			avatarState->SetVelocityYAvatar(0.f);
			avatarState->SetPositionYAvatar(hitInfo.intersectPoint.y);
		}
		
	}
	for (GameItem* GameItem : m_GameItems)
	{
		if (GameItem->IsActive()) 
		{ 
#
			GameItem->CollisionDetect(gameState);
		}
	}
	for (LiveItem* ALiveItem : m_LiveItems)
	{ 
		if (ALiveItem->IsActive())
		{
			ALiveItem->CollisionDetect(gameState);
			for (GameItem* GameItem : m_GameItems)
			{
				if (GameItem->IsActive())
				{
					ALiveItem->CollisionWithGameItemDetect(GameItem);
				}
			}
			for (LiveItem* OtherLiveItem: m_LiveItems)
			{
				if (OtherLiveItem->IsActive())
				{
					ALiveItem->CollisionWithLiveItemDetect(OtherLiveItem);
				}
			}

			Point2f liveItemOrigin1 = Point2f{ ALiveItem->GetGameItemPos().x + ALiveItem->GetGameItemWidth() / 2, ALiveItem->GetGameItemPos().y };
			Point2f liveItemOrigin2 = Point2f{ ALiveItem->GetGameItemPos().x + ALiveItem->GetGameItemWidth() / 2, ALiveItem->GetGameItemPos().y + ALiveItem->GetGameItemHeight() *5};
			for (size_t i = 0; i < m_Vertices.size(); i++) {

				if (utils::Raycast(m_Vertices.at(i).front(), liveItemOrigin1, liveItemOrigin2, hitInfo))
				{
					ALiveItem->SetVelocityY(0.f);
					ALiveItem->SetGameItemPosY(hitInfo.intersectPoint.y );
					ALiveItem->BounceFloor();
				}
			}
		}
	}
}

bool Level::IsOnGround(AvatarState* avatarState) const
{
	Point2f origin1{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y - 5 };
	Point2f origin2{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y + 30.f };

	utils::HitInfo
		hitInfo{};
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		if (utils::Raycast(m_Vertices.at(i).front(), origin1, origin2, hitInfo))
		{
			return true;
		}
		for (GameItem* GameItem : m_GameItems)
		{
			if (GameItem->IsActive())
			{
				if (GameItem->CollisionDetectOnGround(avatarState))
				{
					return true;
				}
			}
		}
	}
	return false;
	
}

void Level::AddGameItem(GameItem* gameItem)
{
	m_GameItems.push_back(gameItem);
}

void Level::AddLiveItem(LiveItem* liveItem)
{
	m_LiveItems.push_back(liveItem);
}

std::vector<GameItem*> Level::GetGameItems() const
{
	return m_GameItems;
}


void Level::DrawForeground(AvatarState* avatarState) const
{
	for (GameItem* GameItem : m_GameItems)
	{
		if (GameItem->IsActive())
		{
			GameItem->Draw(avatarState);
		}

	}
	for (LiveItem* LiveItem : m_LiveItems)
	{
		if (LiveItem->IsActive())
		{
			LiveItem->Draw(avatarState);
		}

	}
}

void Level::UpdateItems(float elapsedSec, Level* level)
{
	for (GameItem* GameItem : m_GameItems)
	{
		if (GameItem->IsActive())
		{
			GameItem->UpdateGameItem(elapsedSec, level);
		}

	}
	for (LiveItem* LiveItem : m_LiveItems)
	{
		if (LiveItem->IsActive())
		{
			LiveItem->UpdateGameItem(elapsedSec, level);
		}

	}
}

