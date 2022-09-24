#pragma once

#include "Spaceship.h"

namespace Game {
	Ship GetPlayer();

	void SetPaused(bool val);

	void Update();
	void Init();
}