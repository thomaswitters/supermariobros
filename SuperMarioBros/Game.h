#pragma once
#include "BaseGame.h"
#include "GameState.h"
#include "Level1.h"
#include "Camera.h"
#include <SoundStream.h>
#include "Hud.h"
#include <SoundEffect.h>
#include "BeginVieuw.h"
#include "LoadingScreen.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;
private:
	/*SoundStream* m_pSoundStreamMario;
	, m_pSoundStreamMario{ new SoundStream("Sounds/MarioJump.mp3") }*/

	GameState m_GameState;
	Hud* m_pHud;
	Level* m_pLevel;
	Camera* m_pCamera;
	SoundStream* m_SoundStreamMario;
	SoundEffect* m_SoundEffectMarioJump;
	SoundEffect* m_SoundEffectMarioFinnish;
	BeginVieuw* m_BeginScreen;
	LoadingScreen* m_LoadingScreen;
	

	Point2f m_CameraFollow;
	int m_AmountOfLives;
	int m_AmountCoins;

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	
};