#pragma once

#include "Spaceship.h"

namespace Game {
	void AddScore(int amount);
	void AddLive(int amount);
	void RemoveLive(int amount);
	void OpenUpgradeMenu();

	bool GetHasStarted(); // Devuelve si el juego comenzó o si el jugador sigue leyendo el tutorial.
	bool GetInvaderActive();
	long GetScore();
	int GetLives();
	float GetGameTime();
	Ship& GetInvader();
	Ship& GetPlayer();
	bool GetIsHalted();
	float GetHaltTime();

	void SetInvader(bool active);
	void SetPaused(bool val);
	void SetHalted();

	void Update();
	void Init();
}