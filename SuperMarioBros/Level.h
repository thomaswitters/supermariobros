#pragma once
#include <utils.h>
#include <Texture.h>
#include "AvatarState.h"
#include <SVGParser.h>
#include "GameItem.h"

class AvatarState;
class GameItem;
class LiveItem;
class GameState;
class Level
{
public:
	/* Use a vecotr of verticesImagePath: I didn't know how to create 1 svg to represent all vertices, hence I chose to introduce a vector with multiple svg's */
	Level(const std::string& imagePath, std::vector<std::string> verticesImagePath);
	virtual ~Level();
	virtual void ResetLevel() = 0;

	void DrawBackground() const;
	void DrawForeground(AvatarState* avatarState) const;
	void HandleCollision(float elapsedSec, GameState* gameState, Point2f& cameraPos) const;
	bool IsOnGround(AvatarState* avatarState) const;

	void UpdateItems(float elapsedSec, GameState* gameState, Point2f cameraPos);

	void DestroyGameItem(GameItem* gameItem);
	void AddGameItem(GameItem* gameItem);

	void AddLiveItem(LiveItem* liveItem);

	void DestroyAllItems();

protected:
	std::vector<GameItem*> GetGameItems() const;
	std::vector<LiveItem*> GetLiveItems() const;

private:
	std::vector<std::vector<std::vector<Point2f>>> m_Vertices;
	Texture* m_pBackgroundTexture;

	std::vector<GameItem*> m_pGameItems;
	std::vector<LiveItem*> m_pLiveItems;
};

