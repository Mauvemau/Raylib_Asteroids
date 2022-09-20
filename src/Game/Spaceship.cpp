#include "Spaceship.h"

namespace Spaceship {
	void Rotate(Ship& ship, float ang) {
		ship.rotation = ang;
	}

	void Draw(Ship ship) {
		DrawRectanglePro(
			{ ship.pos.x, ship.pos.y, ship.size.x, ship.size.y }, 
			{ (float)(ship.size.x  * .5), (float)(ship.size.y * .5) }, 
			ship.rotation, 
			RED);
	}

	Ship Create() {
		Ship ship;
		ship.pos = { 0, 0 };
		ship.size = { 0, 0 };
		ship.rotation = 0;
		return ship;
	}

	void Init(Ship& ship) {
		ship.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
		ship.size = { (float)(GetScreenWidth() * .02), (float)(GetScreenHeight() * .08) };
	}
}
