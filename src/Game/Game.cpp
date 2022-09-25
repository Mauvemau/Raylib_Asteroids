#include "Utils.h"
#include "Game.h"
#include "ObjectManager.h"

#include "Menu/PauseMenu.h" // Extension, menu de pausa.
#include "Menu/Hud.h" // Hud del juego.

#include <iostream>

Ship ship;

namespace Game {

	float gameTime; //Alternativa a GetTime, se inicia cuando comienza la partida, se pausa cuando el juego esta pausado.
	float lastTick; // Para el gameTime;
	bool paused;

	void TickTime(); // Avanza el gameTime.
	void ManageInput();
	void Draw();

	// --

	void TickTime() {
		if (!paused) { // Si el juego no esta pausado, hacer que el timer avanze
			if (GetTime() > lastTick) {
				gameTime += .05;
				lastTick = GetTime() + .05;
			}
		}
	}

	void ManageInput() {
		// Rotation
		if (GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0 &&
			Utils::GetDistance(ship.pos, GetMousePosition()) > (float)(ship.size.y * .25))
			Spaceship::Rotate(ship, Utils::CalculateRotationAngle(ship.pos, GetMousePosition()));

		// Acceleration
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) &&
			GetMouseX() < GetScreenWidth() && GetMouseX() > 0 &&
			GetMouseY() < GetScreenHeight() && GetMouseY > 0)
			Spaceship::Accelerate(ship, GetMousePosition());

		// Shooting
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			Spaceship::Shoot(ship);

		// Pausing
		if (IsKeyPressed(KEY_ESCAPE))
			SetPaused(true);
	}

	void Draw() {
		BeginDrawing();
		// Background
		ClearBackground(BLACK);
		// Ship
		Spaceship::Draw(ship);
		// Asteroids
		ObjManager::Draw();

		if (!paused)
			// Hud
			Hud::Draw();
		else
			// PauseMenu
			Pause::Draw();

		EndDrawing();
	}

	// Global

	float GetGameTime() {
		return gameTime;
	}

	Ship GetPlayer() {
		return ship;
	}

	void SetPaused(bool val) {
		paused = val;
	}

	void Update() {
		TickTime();
		if (!paused) {
			// Input
			ManageInput();
			// Ship
			Spaceship::Update(ship);
			// Asteroids
			ObjManager::Update();
			// Hud
			Hud::Update();
		}
		else
			// PauseMenu
			Pause::Update();

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
		// Asteroids
		ObjManager::Init();
		
		for (int i = 0; i < 5; i++) {
			ObjManager::ActivateAsteroid((AsteroidType)
				GetRandomValue((int)AsteroidType::BIG, (int)AsteroidType::SMALL));
		}
	}
}