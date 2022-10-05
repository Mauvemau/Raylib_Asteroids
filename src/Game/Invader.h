#pragma once

#include "Spaceship.h"

namespace Invader {
	void Draw(Ship ship);
	void Update(Ship& ship, Ship target);
	void Init(Ship& ship);
}