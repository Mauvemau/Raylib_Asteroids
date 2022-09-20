#include "Spaceship.h"
#include "Utils.h"

namespace Spaceship {
	void Move(Ship& ship);

	void Move(Ship& ship) {
		ship.pos.x += (ship.vectorDir.x * GetFrameTime()) * ship.speed;
		ship.pos.y += (ship.vectorDir.y * GetFrameTime()) * ship.speed;
	}

	void Accelerate(Ship& ship, Vector2 target) {
		Vector2 vectorDir = Utils::GetTargetVector(ship.pos, target);
		Vector2 normalizedDir;
		normalizedDir.x = (vectorDir.x / Utils::Modulo(vectorDir));
		normalizedDir.y = (vectorDir.y / Utils::Modulo(vectorDir));

		

		ship.vectorDir.x += normalizedDir.x;
		ship.vectorDir.y += normalizedDir.y;
	}

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

	void Update(Ship& ship) {
		Move(ship);
	}

	Ship Create() {
		Ship ship;
		ship.pos = { 0, 0 };
		ship.size = { 0, 0 };
		ship.vectorDir = { 0, 0 };
		ship.rotation = 0;
		ship.speed = 0;
		return ship;
	}

	void Init(Ship& ship) {
		ship.pos = { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) };
		ship.size = { (float)(GetScreenWidth() * .02), (float)(GetScreenHeight() * .08) };
		ship.speed = .1f;
	}
	void Init(Ship& ship, Vector2 pos, float speed) {
		ship.pos = pos;
		ship.speed = speed;
	}
}
