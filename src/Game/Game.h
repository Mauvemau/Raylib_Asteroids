#pragma once

#include "Spaceship.h"

namespace Game {
	void AddLive(int amount);
	void RemoveLive(int amount);

	int GetLives();
	float GetGameTime();
	Ship& GetPlayer();
	bool GetIsHalted();
	float GetHaltTime();

	void SetPaused(bool val);
	void SetHalted();

	void Update();
	void Init();
}