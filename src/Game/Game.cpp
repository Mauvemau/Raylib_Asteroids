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

	int lives;

	bool started;
	bool paused;

	// Constantes
	const float invaderInterval = 45.0f; // Cada cuanto aparece el invader.
	const float upgradeInterval = 20.0f; // Cada cuanto recibimos un powerup.
	const float increaseInverval = 25.0f; // La cantidad de segundos que tienen que pasar para que se aumente el cap de asteroides.

	// HardCaps
	const int asteroidHardCap = 35;
	const int pickupHardCap = 20;

	// SoftCaps (Limitadores que cambian al avanzar el juego)
	int asteroidCap; // Limite actual de asteroides.
	int pickupCap;
	int increaseAmount; // La cantidad de unidades en la que sube el softcap en el siguiente intervalo.

	float nextInvader;
	float nextUpgrade;
	float nextIncrease; // El tiempo en el que sucedera el proximo intervalo.

	// Stats
	unsigned long score;
	unsigned long asteroidsDestroyed;
	unsigned long goldCollected;
	unsigned long astronautsRescued;

	void FinishGame();
	void HandleGameLogic();
	void TickTime(); // Avanza el gameTime.
	void ManageInput();
	void Draw();

	// --

	void FinishGame() {
		SetProgramStatus(ProgramStatus::GAMEOVER);
	}

	void StartGame() {
		if (!started) {
			Init();
			started = true;
			Assets::PlayMusic(Musics::FINAL_LEVEL, .25);
		}
	}

	void HandleGameLogic() {
		if (ObjManager::GetActiveAsteroids() < asteroidCap) {
			ObjManager::ActivateAsteroid((AsteroidType)GetRandomValue(static_cast<int>(AsteroidType::BIG), static_cast<int>(AsteroidType::MEDIUM)));
		}
		if (ObjManager::GetActivePickups() < pickupCap) {
			if (GetRandomValue(1, 10) < 2)
				ObjManager::ActivatePickup(PickupType::SUS);
			else
				ObjManager::ActivatePickup(PickupType::COIN);
		}
		if (nextIncrease < GetGameTime()) {
			if (asteroidCap < asteroidHardCap)
				asteroidCap += increaseAmount;
			else 
				asteroidCap = asteroidHardCap;

			if (pickupCap < pickupHardCap)
				pickupCap += increaseAmount;
			else
				pickupCap = pickupHardCap;

			if (increaseAmount < 3) {
				increaseAmount++;
			}
			nextIncrease = GetGameTime() + increaseInverval;
		}
		if (nextInvader < GetGameTime()) {
			SetInvader(true);
			nextInvader = GetGameTime() + invaderInterval;
		}
		if (nextUpgrade < GetGameTime()) {
			ObjManager::ActivatePickup(PickupType::UPGRADE);
			nextUpgrade = GetGameTime() + upgradeInterval;
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
			Utils::GetDistance(ship.pos, GetMousePosition()) > static_cast<float>(ship.size.y * .25f) &&
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

		// Tutorial
		if (IsKeyPressed(KEY_F))
			StartGame();

#ifdef _DEBUG
		if (IsKeyPressed(KEY_F4)) {
			FinishGame();
		}
		if (IsKeyPressed(KEY_F3)) {
			SetInvader(true);
		}
		if (IsKeyPressed(KEY_F2)) {
			OpenUpgradeMenu();
		}
#endif
	}

	void Draw() {
		BeginDrawing();
		// Background
		ClearBackground(BLACK);
		// Asteroids / Bullets / Pickups
		ObjManager::Draw();
		// Ship
		Spaceship::Draw(ship);
		//Invader
		if(invaderActive)
			Invader::Draw(invader);
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

	void OpenUpgradeMenu() {
		if (!paused) {
			paused = true;
			Pause::StartUpgrading();
			Assets::PauseMusic(Musics::FINAL_LEVEL);
		}
	}

	void AddScore(int amount) {
		score += amount;
	}

	void AddLive(int amount) {
		lives += amount;
	}

	void RemoveLive(int amount) {
		lives -= amount;
		if (lives < 0)
			FinishGame();
	}

	bool GetHasStarted() {
		return started;
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
		else {
			Assets::ResumeMusic(Musics::FINAL_LEVEL);
		}
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
			if(started)
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

		started = false;
		gameTime = 0;
		haltResumes = 0;

		lives = 0;
		AddLive(4);

		// Stats
		score = 0;
		asteroidsDestroyed = 0;
		goldCollected = 0;
		astronautsRescued = 0;

		// SoftCaps
		asteroidCap = 5;
		pickupCap = 5;
		increaseAmount = 1;

		nextInvader = GetGameTime() + invaderInterval;
		nextUpgrade = GetGameTime() + upgradeInterval;
		nextIncrease = GetGameTime() + increaseInverval;
	}
}