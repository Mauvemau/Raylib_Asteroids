#include "Utils.h"
#include "Game.h"
#include "ProgramManager.h"
#include "ObjectManager.h"
#include "Animations.h" // Para inicializarlas.
#include "AssetLoader.h" // Para el sonido
#include "Invader.h"

#include "Menu/PauseMenu.h" // Extension, menu de pausa.
#include "Menu/Hud.h" // Hud del juego.

#include <iostream>

namespace Game {

	Ship ship;
	Ship invader;

	bool invaderActive;

	float gameTime; //Alternativa a GetTime, se inicia cuando comienza la partida, se pausa cuando el juego esta pausado.
	float lastTick; // Para el gameTime;

	const float haltTime = 3; // Cantidad de segundos que el juego se detiene antes de comenzar a mover la pelota.
	float haltResumes; // El tiempo en el cual la pelota puede comenzar a moverse nuevamente.

	unsigned long score;
	int lives;

	bool paused;

	void FinishGame();
	void HandleGameLogic();
	void TickTime(); // Avanza el gameTime.
	void ManageInput();
	void Draw();

	// --

	void FinishGame() {
		SetProgramStatus(ProgramStatus::GAMEOVER);
	}

	void HandleGameLogic() {
		int asteroidLimit;
		bool invaders;
		if (gameTime < 30.0f) {
			asteroidLimit = 5;
			invaders = false;
		}
		else if (gameTime >= 30.0f && gameTime < 90.0f) {
			asteroidLimit = 10;
			invaders = true;
		}
		else if (gameTime >= 90.0f && gameTime < 120.0f) {
			asteroidLimit = 20;
		}
		else if (gameTime >= 120.0f) {
			asteroidLimit = 30;
		}

		if (ObjManager::GetActiveAsteroids() < asteroidLimit) {
			ObjManager::ActivateAsteroid((AsteroidType)
				GetRandomValue((int)AsteroidType::BIG, (int)AsteroidType::SMALL));
		}
	}

	void TickTime() {
		if (!paused) { // Si el juego no esta pausado, hacer que el timer avanze
			if (GetTime() > lastTick) {
				gameTime += .01;
				lastTick = GetTime() + .01;
			}
		}
	}

	void ManageInput() {
		// Rotation
		if (GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0 &&
			Utils::GetDistance(ship.pos, GetMousePosition()) > (float)(ship.size.y * .25) &&
			!GetIsHalted())
			Spaceship::Rotate(ship, Utils::CalculateRotationAngle(ship.pos, GetMousePosition()));

		// Acceleration
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) &&
			GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0 &&
			!GetIsHalted())
			Spaceship::Accelerate(ship, GetMousePosition());

		// Shooting
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !GetIsHalted())
			Spaceship::Shoot(ship);

		// Pausing
		if (IsKeyPressed(KEY_ESCAPE))
			SetPaused(true);

#ifdef _DEBUG
		if (IsKeyPressed(KEY_F4)) {
			FinishGame();
		}

		if (IsKeyPressed(KEY_F3)) {
			SetInvader(true);
		}
#endif
	}

	void Draw() {
		BeginDrawing();
		// Background
		ClearBackground(BLACK);
		// Ship
		Spaceship::Draw(ship);
		//Invader
		if(invaderActive)
			Invader::Draw(invader);
		// Asteroids
		ObjManager::Draw();
		// Animations
		Animations::Draw();

		if (!paused)
			// Hud
			Hud::Draw();
		else
			// PauseMenu
			Pause::Draw();

		EndDrawing();
	}

	// Global

	void AddScore(int amount) {
		score += amount;
	}

	void AddLive(int amount) {
		lives += amount;
	}

	void RemoveLive(int amount) {
		lives -= amount;
		if (lives < 0)
			lives = 0;
	}

	bool GetInvaderActive() {
		return invaderActive;
	}

	long GetScore() {
		return score;
	}

	int GetLives() {
		return lives;
	}

	float GetGameTime() {
		return gameTime;
	}

	Ship& GetInvader() {
		return invader;
	}

	Ship& GetPlayer() {
		return ship;
	}

	bool GetIsHalted() {
		return (GetGameTime() < haltResumes);
	}

	float GetHaltTime() {
		return haltResumes;
	}

	void SetInvader(bool active) {
		invaderActive = active;
		if(invaderActive)
			Invader::Init(invader);
	}

	void SetPaused(bool val) {
		paused = val;
		if (paused) {
			Assets::PauseMusic(Musics::FINAL_LEVEL);
			Assets::PlayAudio(Audio::PAUSE, .5);
		}
		else
			Assets::ResumeMusic(Musics::FINAL_LEVEL);
	}

	void SetHalted() {
		if(!GetIsHalted())
			haltResumes = GetGameTime() + haltTime;
	}

	void Update() {
		TickTime();
		if (!paused) {
			// Input
			ManageInput();
			// GameLogic
			HandleGameLogic();
			// Ship
			Spaceship::Update(ship);
			if (!GetIsHalted()) {
				// Asteroids
				ObjManager::Update();
				//Invader
				if(invaderActive)
					Invader::Update(invader, ship);
			}
			// Animations
			Animations::Update();
			// Hud
			Hud::Update();
		}
		else
			// PauseMenu
			Pause::Update();

		Assets::UpdateMusic(Musics::FINAL_LEVEL);
		Draw();
	}

	void Init() {
		// Hud
		Hud::Init();
		// PauseMenu
		Pause::Init();
		paused = false;
		// Ship
		ship = Spaceship::Create();
		Spaceship::Init(ship);
		// Invader
		invader = Spaceship::Create();
		SetInvader(false);
		// Asteroids
		ObjManager::Init();
		// Animations
		Animations::Init();

		gameTime = 0;
		haltResumes = 0;
		lives = 0;
		score = 0;
		AddLive(4);

		for (int i = 0; i < 10; i++) {
			ObjManager::ActivatePickup();
		}
		ObjManager::ActivatePickup(PickupType::SUS);
		ObjManager::ActivatePickup(PickupType::UPGRADE);

		Assets::PlayMusic(Musics::FINAL_LEVEL, .25);
	}
}