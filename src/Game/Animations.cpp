#include "Animations.h"
#include "Game.h"

namespace Animations {
	const float blinkInterval = 0.25;

	bool blink;
	float nextBlink;

	bool Blink() {
		if (!Game::GetIsHalted()) {
			return true;
		}
		else {
			if (nextBlink < Game::GetGameTime()) {
				blink = !blink;
				nextBlink = Game::GetGameTime() + blinkInterval;
			}
		}
		return blink;
	}

	void Init() {
		blink = false;
		nextBlink = 0;
	}
}