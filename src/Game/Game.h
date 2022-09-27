#pragma once

#include "Spaceship.h"

namespace Game {
	void Finish();

	float GetGameTime();
	Ship& GetPlayer();
	bool GetIsHalted();
	float GetHaltTime();

	void SetPaused(bool val);
	void SetHalted();

	void Update();
	void Init();
}