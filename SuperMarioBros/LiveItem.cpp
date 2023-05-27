#include "pch.h"
#include "LiveItem.h"

LiveItem::LiveItem(const GameItemType gameItemType, const std::string& imagePath, float spriteClipHeight, float spriteClipWidth, Point2f GameItemPos, float GameItemWidth, float GameItemHeight, bool IsActive, LiveItemState liveItemState,
	Vector2f velocity, Vector2f acceleration,
	int animStartFrameX, int animStartFrameY, int nrOfFrames, float nrFramesPerSec, int animStartDyingFrameX, int animStartDyingFrameY, int imageAmountHoriFrames, int imageAmountVertiFrames, const std::string& soundPath) :
	GameItem(gameItemType, imagePath, spriteClipHeight, spriteClipWidth, GameItemPos, GameItemWidth, GameItemHeight, IsActive, soundPath)
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
	//utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	//utils::DrawRect(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight());
}

