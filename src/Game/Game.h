#pragma once

#include "Spaceship.h"

namespace Game {
	float GetGameTime();
	Ship GetPlayer();

	void SetPaused(bool val);

	void Update();
	void Init();
}