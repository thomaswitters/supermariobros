#include "pch.h"
#include "Level.h"

#include "pch.h"
#include "Level.h"

Level::Level(const std::string& imagePath, std::vector<std::string> verticesImagePaths  /* EN OOK DE GAMEELEMENTS */)
	: m_Vertices{}
	, m_pBackgroundTexture{new Texture(imagePath)}
	, m_GameItems{}
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

void Level::HandleCollision(AvatarState* avatarState) const
{
	Point2f origin1{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y };
	Point2f origin2{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y + 30.f };

	utils::HitInfo
		hitInfo{};
	for (size_t i = 0; i < m_Vertices.size(); i++) {
		
		if (utils::Raycast(m_Vertices.at(i).front(), origin1, origin2, hitInfo))
		{
			avatarState->SetVelocityYAvatar(0.f);
			avatarState->SetPositionYAvatar(hitInfo.intersectPoint.y);
		}
	}
	for (GameItem* GameItem : m_GameItems)
	{
		if (GameItem->IsActive())
		{
			GameItem->CollisionDetect(avatarState);
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
}

void Level::UpdateGameItem(float elapsedSec, Level* level)
{
	for (GameItem* GameItem : m_GameItems)
	{
		if (GameItem->IsActive())
		{
			GameItem->UpdateGameItem(elapsedSec, level);
		}
		
	}
}