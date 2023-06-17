#pragma once
#include <utils.h>
#include <Texture.h>
#include "AvatarState.h"
#include "Level.h"

class GameItem;
class Level1: public Level
{
public:
	Level1();
	virtual ~Level1();
	void SetupLevel();
	void ResetLevel();
	void DrawForeground() const;
};

