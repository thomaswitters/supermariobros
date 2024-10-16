#include "pch.h"
#include "Level.h"
#include "LiveItem.h"

#include "pch.h"
#include "Level.h"

Level::Level(const std::string& imagePath, std::vector<std::string> verticesImagePaths  /* EN OOK DE GAMEELEMENTS */)
	: m_Vertices{}
	, m_pBackgroundTexture{new Texture(imagePath)}
	, m_pGameItems{}
	, m_pLiveItems{}
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
	
	DestroyAllItems();

}

void Level::DestroyAllItems() {
	
	for (size_t i = 0; i < m_pGameItems.size(); i++)
	{
		GameItem* GameItem = m_pGameItems[i];
		delete GameItem;
	}
	m_pGameItems.clear();

	for (size_t i = 0; i < m_pLiveItems.size(); i++)
	{
		LiveItem* ALiveItem = m_pLiveItems[i];
		delete ALiveItem;
	}

	m_pLiveItems.clear();
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

void Level::HandleCollision(float elapsedSec, GameState* gameState, Point2f& cameraPos) const
{
	
	AvatarState* avatarState = gameState->GetAvatarState();
	Point2f AvatarOrigin1{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y };
	Point2f AvatarOrigin2{ avatarState->GetPositionAvatar().x + 5.f, avatarState->GetPositionAvatar().y + 30.f };

	Point2f gameItemOrigin1{};
	Point2f gameItemOrigin2{};

	utils::HitInfo
		hitInfo{};
	
	if (avatarState->GetActionState() != AvatarState::ActionState::dead)
	{
		for (size_t i = 0; i < m_Vertices.size(); i++) {

			if (utils::Raycast(m_Vertices.at(i).front(), AvatarOrigin1, AvatarOrigin2, hitInfo))
			{
				avatarState->SetVelocityYAvatar(0.f);
				avatarState->SetPositionYAvatar(hitInfo.intersectPoint.y);
			}

		}
	}
	
	
	for (size_t i = 0; i < m_pGameItems.size(); i++)
	{
		GameItem* AGameItem = m_pGameItems[i];
		//if (AGameItem == DecorBlock)
		if (AGameItem->IsActive())
		{ 
			if (avatarState->GetActionState() != AvatarState::ActionState::dead)
			{
				AGameItem->CollisionDetect(gameState);
			}
		}
	}

	for (size_t i = 0; i < m_pLiveItems.size(); i++)
	{
		LiveItem* ALiveItem = m_pLiveItems[i];
		if (ALiveItem->IsActive())
		{
			ALiveItem->CollisionDetect(gameState);

			/* Example detection...
			   Goomba->CanCollide(Decor)
			*/
			for (size_t i = 0; i < m_pGameItems.size(); i++)
			{
				GameItem* AGameItem = m_pGameItems[i];
				if (AGameItem != ALiveItem && AGameItem->IsActive() && AGameItem->CanCollide(ALiveItem))
				{
					ALiveItem->CollisionWithGameItemDetect(AGameItem);
				}
			}

			/* Example detection...
			   Goomba->CanCollide(Vuurbal)
			   Vuurbal->CanCollide(Goomba)
			*/
			for (size_t i = 0; i < m_pLiveItems.size(); i++)
			{
				LiveItem* OtherLiveItem = m_pLiveItems[i];
				if (OtherLiveItem != ALiveItem && OtherLiveItem->IsActive() && ALiveItem->CanCollide(OtherLiveItem))
				{
					
					if (cameraPos.x + Window().width / 2 >= ALiveItem->GetGameItemPos().x && cameraPos.y + Window().height >= ALiveItem->GetGameItemPos().y)
					{
						ALiveItem->CollisionWithLiveItemDetect(OtherLiveItem);
					}
				}
			}

			Point2f liveItemOrigin1 = Point2f{ ALiveItem->GetGameItemPos().x + ALiveItem->GetGameItemWidth() / 2, ALiveItem->GetGameItemPos().y };
			Point2f liveItemOrigin2 = Point2f{ ALiveItem->GetGameItemPos().x + ALiveItem->GetGameItemWidth() / 2, ALiveItem->GetGameItemPos().y + ALiveItem->GetGameItemHeight() *5};
			for (size_t i = 0; i < m_Vertices.size(); i++) {

				if (utils::Raycast(m_Vertices.at(i).front(), liveItemOrigin1, liveItemOrigin2, hitInfo))
				{
					if (ALiveItem->GetGameItemType() != GameItemType::FishType)
					{
						ALiveItem->SetVelocityY(0.f);
						ALiveItem->SetGameItemPosY(hitInfo.intersectPoint.y);
					}
					
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

		for (size_t i = 0; i < m_pGameItems.size(); i++)
		{
			GameItem* GameItem = m_pGameItems[i];
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
	m_pGameItems.push_back(gameItem);
}

void Level::AddLiveItem(LiveItem* liveItem)
{
	m_pLiveItems.push_back(liveItem);
}

std::vector<GameItem*> Level::GetGameItems() const
{
	return m_pGameItems;
}


void Level::DrawForeground(AvatarState* avatarState) const
{
	for (size_t i = 0; i < m_pGameItems.size(); i++)
	{
		GameItem* GameItem = m_pGameItems[i];
		if (GameItem->IsActive())
		{
			GameItem->Draw(avatarState);
		}
	}

	for (size_t i = 0; i < m_pLiveItems.size(); i++)
	{
		LiveItem* ALiveItem = m_pLiveItems[i];
		if (ALiveItem->IsActive())
		{
			ALiveItem->Draw(avatarState);
		}

	}	
}

void Level::UpdateItems(float elapsedSec, GameState* gameState, Point2f cameraPos)
{
	Level* level = gameState->GetLevel();
	for (size_t i = 0; i < m_pGameItems.size(); i++) 
	{
		GameItem* GameItem = m_pGameItems[i];
		if (GameItem->IsActive())
		{
			GameItem->UpdateGameItem(elapsedSec, gameState);
		}
	}

	//25.f width avatar
	
	for (size_t i = 0; i < m_pLiveItems.size(); i++)
	{
		LiveItem* ALiveItem = m_pLiveItems[i];

		if (ALiveItem->IsActive())
		{
			if (cameraPos.x + Window().width / 2 + 35.f >= ALiveItem->GetGameItemPos().x && cameraPos.y + Window().height >= ALiveItem->GetGameItemPos().y)
			{
				ALiveItem->UpdateGameItem(elapsedSec, gameState);
			}
		}

	}
}

