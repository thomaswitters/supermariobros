#pragma once
#include <utils.h>
#include <Texture.h>
#include "AvatarState.h"
#include "Level.h"

class Level2: public Level
{

public:
	Level2();
	virtual ~Level2();
	void DrawForeground() const;
	bool HasReachedEnd(const Rectf& actorShape);
};

