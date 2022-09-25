#pragma once

#include "Spaceship.h"

namespace Game {
	int GetGameTime();
	Ship GetPlayer();

	void SetPaused(bool val);

	void Update();
	void Init();
}