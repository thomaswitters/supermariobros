#include "pch.h"
#include "BlackDecorBlock.h"

BlackDecorBlock::BlackDecorBlock(Point2f GameItemPos) : GameItem(GameItemType::DecorBlockType, "Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true, "Sounds/super-mario-coin-sound.mp3")
	, m_Pos{ GetGameItemPos().x, GetGameItemPos().y }
{

}
BlackDecorBlock::~BlackDecorBlock()
{

}
void BlackDecorBlock::Draw(AvatarState* avatarState) const
{
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	utils::FillRect(Rectf(m_Pos.x, m_Pos.y, 16.f, 16.f));
}