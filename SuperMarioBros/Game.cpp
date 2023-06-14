#include "pch.h"
#include "Game.h"
#include <utils.h>

Game::Game( const Window& window ) 
	:BaseGame{ window }
	, m_SoundEffectMarioFinnish{ new SoundEffect("Sounds/MarioFinnish.mp3")}
	, m_AmountOfLives{ m_GameState.GetAmountOfLives() }
	, m_AmountCoins{ m_GameState.GetAmountCoins()}
	, ZoomCamera{1.f, 1.f}
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pLevel = new Level1();
	m_pCamera = new Camera{ Window().width, Window().height };
	m_pHud = new Hud{ Point2f(Window().width, Window().height*2), int(400), 1, m_AmountOfLives, m_AmountCoins, 000000};
	m_BeginScreen = new BeginVieuw();
	m_LoadingScreen = new LoadingScreen(m_BeginScreen, 1, m_AmountOfLives);
}

void Game::Cleanup( )
{
	if (m_pLevel) {
		delete m_pLevel;
		m_pLevel = NULL;
	}
	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pHud != NULL) {
		delete m_pHud;
		m_pHud = NULL;
	}
	
	
	delete m_SoundEffectMarioFinnish;
	delete m_BeginScreen;
	delete m_LoadingScreen;
}

void Game::Update( float elapsedSec )
{
	

	m_LoadingScreen->Update(elapsedSec, &m_GameState);
	if (m_LoadingScreen->HasLoadGame())
	{
		if (ZoomCamera.x <= 2.f)
		{
			ZoomCamera.x += 0.01f;
		}
		if (ZoomCamera.y <= 2.f)
		{
			ZoomCamera.y += 0.01f;
		}
		

		m_GameState.UpdateDrawAvatar(elapsedSec);
		m_GameState.SetLevel(m_pLevel);

		m_pLevel->UpdateItems(elapsedSec, &m_GameState, m_CameraFollow);
		m_GameState.UpdateAvatar(elapsedSec, m_pLevel, m_CameraFollow);

		m_pLevel->HandleCollision(elapsedSec, &m_GameState, m_CameraFollow);


		m_pCamera->SetLevelBoundaries(Rectf{ 0.0f ,0.f,  3376.f, 480.f });
		m_pCamera->SetLevelBoundaries2(Rectf{ 768.0f ,0.f,  3376.f, 240.f });


		if (m_GameState.GetAvatarState()->GetVelocityAvatar().x >= 0.f && m_GameState.GetAvatarState()->GetPositionAvatar().x >= m_CameraFollow.x || m_GameState.GetAvatarState()->GetPositionAvatar().y <= 250.f)
		{
			if (m_GameState.GetAvatarState()->GetActionState() != AvatarState::ActionState::dead)
			{
				/*if (m_GameState.GetAvatarState()->GetPositionAvatar().y >= 272.f)
				{*/
					m_CameraFollow = m_GameState.GetAvatarState()->GetPositionAvatar();
				//}
			}
		}

		m_pHud->Update(elapsedSec, &m_GameState);
	}
	
	
	//std::cout << Teller << std::endl;
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
}

void Game::Draw( ) const
{
	ClearBackground( );
	
	if (m_BeginScreen->HasStartedGame())
	{
		glPushMatrix();
		{
			// T R S
			glScalef(ZoomCamera.x, ZoomCamera.y, 1.f);
			m_pCamera->Transform(Point2f{ m_CameraFollow });

			m_pLevel->DrawBackground();
			m_pLevel->DrawForeground(m_GameState.GetAvatarState());
			m_GameState.DrawAvatar();


		}
		glPopMatrix();
		m_pHud->Draw();
	}
	m_LoadingScreen->Draw();
	if (!m_BeginScreen->HasStartedGame())
	{
		m_BeginScreen->Draw();
	}
	

	//utils::DrawLine(54.f, 600.f, 54.f, 0.f);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_1:
	case SDLK_KP_1:
		
		break;
	case SDLK_2:
	case SDLK_KP_2:
		//m_SoundStreamMario->Play(true);
		//m_SoundEffectMarioJump->Play(false);
		break;
	case SDLK_3:
	case SDLK_KP_3:
		//m_SoundStreamMario->Play(true);
		m_SoundEffectMarioFinnish->Play(false);
		break;
	case SDLK_UP:
		//m_SoundStreamMario->SetVolume(m_SoundStreamMario->GetVolume() + 1);
		break;
	case SDLK_DOWN:
		//m_SoundStreamMario->SetVolume(m_SoundStreamMario->GetVolume() - 1);
		break;
	case SDLK_p:
		//m_SoundStreamMario->Pause();
		break;
	case SDLK_r:
		//m_SoundStreamMario->Resume();
		break;
	case SDLK_s:
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_BeginScreen->ProcessMouseMotionEvent(e);
	m_pHud->ProcessMouseMotionEvent(e);
	
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	m_pHud->ProcessMouseDownEvent(e);
	
}



void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	m_BeginScreen->ProcessMouseUpEvent(e);
	m_pHud->ProcessMouseUpEvent(e);
	
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
