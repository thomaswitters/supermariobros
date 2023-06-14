#include "pch.h"
#include "HorizontalPipe.h"

HorizontalPipe::HorizontalPipe(HorizonDirection horizonDirection, Point2f GameItemPos, float width, Point2f* transportToPos) :
	Pipe(GameItemPos, 32.f, 16.f, width, 32.f, transportToPos, "Sounds/Pipes.mp3")
	, m_HorizonDirection{ horizonDirection }
{
	
}
HorizontalPipe::~HorizontalPipe()
{

}
void HorizontalPipe::Draw(AvatarState* avatarState) const
{
	if (m_HorizonDirection == HorizonDirection::FromLeftToRight)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 21.f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 14 };

		Rectf src{ GetSpriteClipWidth() * 3.f ,GetSpriteClipHeight() * 5.f,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y, sourceWidth + GetGameItemWidth() - 16, sourceHeight};

		Rectf src2{ GetSpriteClipWidth() * 2.f ,GetSpriteClipHeight() * 5.f,sourceWidth,sourceHeight };
		Rectf dst2{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight};

		GetSpriteTexture()->Draw(dst, src);
		GetSpriteTextureBottom()->Draw(dst2, src2);
	}
	/*else if (m_HorizonDirection == HorizonDirection::FromRightToLeft)
	{
		float sourceWidth{ GetSpriteTexture()->GetWidth() / 10.5f };
		float sourceHeight{ GetSpriteTexture()->GetHeight() / 28 };

		Rectf src{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 5,sourceWidth,sourceHeight };
		Rectf dst{ GetGameItemPos().x, GetGameItemPos().y,sourceWidth, sourceHeight + GetGameItemHeight() - 15.f };

		Rectf src2{ GetSpriteClipWidth() * 0 ,GetSpriteClipHeight() * 4.5f,sourceWidth,sourceHeight };
		Rectf dst2{ GetGameItemPos().x, GetGameItemPos().y - 2.f,sourceWidth, sourceHeight };

		GetSpriteTexture()->Draw(dst, src);
		GetSpriteTextureBottom()->Draw(dst2, src2);

	}*/
}
void HorizontalPipe::CollisionDetect(GameState* gameState)
{
	AvatarState* avatarState = gameState->GetAvatarState();
	CollisionDetectionHelper::CollisionLocation location = CollisionDetectionHelper::determineCollisionDir(
		Rectf(avatarState->GetPositionAvatar().x, avatarState->GetPositionAvatar().y, avatarState->GetCurrentAvatar()->GetAvatarWidth(), avatarState->GetCurrentAvatar()->GetAvatarHeight()),
		Vector2f(avatarState->GetVelocityAvatar()),
		Rectf(GetGameItemPos().x, GetGameItemPos().y, GetGameItemWidth(), GetGameItemHeight()));

	switch (location)
	{

	case CollisionDetectionHelper::CollisionLocation::avatorBumpsOnTheLeft:
	{
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if ((pStates[SDL_SCANCODE_RIGHT]) && (GetTransportToPos() != NULL)) {
			avatarState->SetActionState(AvatarState::ActionState::isGoingTroughPipe);
			avatarState->TravelTo(GetTransportToPos(), PrepareForTravelAnimation::FallDown);
			GetSoundEffect()->SetVolume(70);
			GetSoundEffect()->Play(false);
			return;
		}
		break;
	}
	}
	Pipe::CollisionDetect(gameState);
}
