#include "pch.h"
#include "BlueDecorBlock.h"

BlueDecorBlock::BlueDecorBlock(Point2f GameItemPos) : GameItem(GameItemType::DecorBlockType, "Images/items-objects.png", 16, 16, GameItemPos, 16, 16, true, "Sounds/super-mario-coin-sound.mp3")
, m_Pos{ GetGameItemPos().x, GetGameItemPos().y }
{

}
BlueDecorBlock::~BlueDecorBlock()
{

}
void BlueDecorBlock::Draw(AvatarState* avatarState) const
{
	utils::SetColor(Color4f(0.36f, 0.58f, 0.99f, 1.f));
	utils::FillRect(Rectf(m_Pos.x, m_Pos.y, 16.f, 16.f));
}