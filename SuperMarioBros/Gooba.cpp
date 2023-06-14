#include "pch.h"
#include "Goomba.h"

Goomba::Goomba(Point2f GameItemPos) : Enemy(GameItemType::GoombaType, "Images/smb_enemies_sheet.png", 30, 30, GameItemPos, 16, 16, true, LiveItemState::Alive,
	Vector2f{-30.0f, 0.f}, Vector2f{0.0f, -581.0f},
	0, 0, 2, 0.2f, 2, 0, 15, 7, "Sounds/Goomba.mp3")
{
	
}
Goomba::~Goomba() {
}

