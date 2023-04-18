#include "pch.h"
#include "Game.h"
#include <utils.h>

Game::Game( const Window& window ) 
	:BaseGame{ window }
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
}

void Game::Update( float elapsedSec )
{
	m_GameState.UpdateDrawAvatar(elapsedSec);
	m_GameState.SetLevel(m_pLevel);
	
	m_GameState.UpdateAvatar(elapsedSec, m_pLevel, m_CameraFollow);
	m_pLevel->UpdateItems(elapsedSec, &m_GameState, m_CameraFollow);
	m_pLevel->HandleCollision(elapsedSec, &m_GameState);
	

	m_pCamera->SetLevelBoundaries(Rectf{ 0.0f ,0.f,  3376.f, 480.f });

	
	if (m_GameState.GetAvatarState()->GetVelocityAvatar().x >= 0.f && m_GameState.GetAvatarState()->GetPositionAvatar().x >= m_CameraFollow.x || m_GameState.GetAvatarState()->GetPositionAvatar().x <= 0.f && m_GameState.GetAvatarState()->GetVelocityAvatar().x >= 0.f)
	{
		if (m_GameState.GetAvatarState()->GetActionState() != AvatarState::ActionState::dead)
		{
			if (m_GameState.GetAvatarState()->GetPositionAvatar().y >= 272.f)
			{
				m_CameraFollow = m_GameState.GetAvatarState()->GetPositionAvatar();
			}
		}
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
	
	glPushMatrix();
	{
		// T R S
		m_pCamera->Transform(Point2f{ m_CameraFollow });
		m_pLevel->DrawBackground();
		m_pLevel->DrawForeground(m_GameState.GetAvatarState());
		m_GameState.DrawAvatar();
	}
	glPopMatrix();
	
	//utils::DrawLine(54.f, 600.f, 54.f, 0.f);
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
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
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
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

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
