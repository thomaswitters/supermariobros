#include "pch.h"
#include "VerticalPipe.h"

VerticalPipe::VerticalPipe(VerticalDirection verticalDirection, Point2f GameItemPos, float height, Point2f* transportToPos) :
	Pipe(GameItemPos, 32.f, 32.f, 32.f, height, transportToPos)
	, m_VerticalDirection{ verticalDirection }
{
}
VerticalPipe::~VerticalPipe()
{
}
void VerticalPipe::Draw(AvatarState* avatarState) const
{
	if (m_VerticalDirection == VerticalDirection::FromTopToBottom)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 10.5f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

		Rectf src{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 5,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight + GetGameItemHeight() - 15.f };

		Rectf src2{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 4.5f,sourceWidth,sourceHeight };
		Rectf dst2{ GetGameItemPos().x, GetGameItemPos().y + sourceHeight + GetGameItemHeight() - 15 - 16 ,sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
		GetSpriteTextureBottom()->Draw(dst2, src2);
	}
	else if (m_VerticalDirection == VerticalDirection::FromBottomToTop)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 10.5f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

		Rectf src{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 5,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight + GetGameItemHeight() - 15.f};

		Rectf src2{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 4.5f,sourceWidth,sourceHeight };
		Rectf dst2{ GetGameItemPos().x, GetGameItemPos().y - 2.f,sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
		GetSpriteTextureBottom()->Draw(dst2, src2);
		
	}
}
void VerticalPipe::CollisionDetect(GameState* gameState) {
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()), 
		Vector2f(avatarState->GetVelocityAvatar()), 
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	switch (location)
	{

	case CollisionDetectionHelper::CollisionLocation::avatorBumpsFromTheTop:
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if ((pStates[SDL_SCANCODE_DOWN]) && (GetTransportToPos() != NULL)) {
			avatarState->SetActionState(AvatarState::ActionState::isGoingTroughPipe);
			avatarState->TravelTo(GetTransportToPos(), PrepareForTravelAnimation::FallDown);
			return;
		}
		break;
	}
	}
	Pipe::CollisionDetect(gameState);

}

