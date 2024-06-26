#include "Spaceship.h"
#include "Utils.h"
#include "CollisionManager.h" // Para manejar las colisiones.
#include "ObjectManager.h" // Para disparar balas.
#include "Game.h" // Para el Gametime.
#include "Animations.h" // Para el blink.
#include "AssetLoader.h" // Para la textura.

namespace Spaceship {
	void Move(Ship& ship);
	void LimitAcceleration(Ship& ship);
	void InitCannon(Cannon& cannon);
	Cannon CreateCannon();

	// --

	void Move(Ship& ship) {
		ship.pos.x += (ship.acceleration.x * GetFrameTime()) * ship.speed;
		ship.pos.y += (ship.acceleration.y * GetFrameTime()) * ship.speed;
	}

	void LimitAcceleration(Ship& ship) {
		if (ship.acceleration.x > ship.maxAccel) {
			ship.acceleration.x = ship.maxAccel;
		}
		if (ship.acceleration.x < -ship.maxAccel) {
			ship.acceleration.x = -ship.maxAccel;
		}
		if (ship.acceleration.y > ship.maxAccel) {
			ship.acceleration.y = ship.maxAccel;
		}
		if (ship.acceleration.y < -ship.maxAccel) {
			ship.acceleration.y = -ship.maxAccel;
		}
	}

	void InitCannon(Cannon& cannon) {
		cannon.isEvil = false;
		cannon.fireRate = .25f;
		cannon.power = static_cast<float>(GetScreenHeight() * .9);
		cannon.range = .8f;
		cannon.caliber = static_cast<float>(GetScreenHeight() * .005);
		cannon.lastShot = 0;
	}

	Cannon CreateCannon() {
		Cannon cannon;
		cannon.isEvil = false;
		cannon.fireRate = 0;
		cannon.power = 0;
		cannon.range = 0;
		cannon.caliber = 0;
		cannon.lastShot = 0;
		return cannon;
	}

	// Global

	float GetCollisionRadius(Ship ship) {
		return static_cast<float>(ship.size.x * .5);
	}

	void Shoot(Ship& ship) {
		if (ship.cannon.fireRate < (Game::GetGameTime() - ship.cannon.lastShot)) {
			ship.cannon.lastShot = Game::GetGameTime();
			ObjManager::ActivateBullet(ship.pos,
				ship.cannon.caliber,
				Utils::DegreesToRadians(ship.rotation - 90.0f),
				ship.cannon.power,
				ship.cannon.range,
				false);
			Assets::PlayAudio(Audio::SHOOT, .5);
		}
	}

	void ResetAcceleration(Ship& ship) {
		ship.acceleration = { 0, 0 };
	}

	void Accelerate(Ship& ship, Vector2 target) {
		Vector2 vectorDir = Utils::GetTargetVector(ship.pos, target);
		Vector2 normalizedDir;
		normalizedDir.x = (vectorDir.x / Utils::Modulo(vectorDir));
		normalizedDir.y = (vectorDir.y / Utils::Modulo(vectorDir));

		ship.acceleration.x += normalizedDir.x * GetFrameTime();
		ship.acceleration.y += normalizedDir.y * GetFrameTime();
		LimitAcceleration(ship);
	}

	void Rotate(Ship& ship, float ang) {
		ship.rotation = ang;
	}

	void Draw(Ship ship) {
#ifdef _DEBUG
		DrawCircle(static_cast<int>(ship.pos.x), static_cast<int>(ship.pos.y), GetCollisionRadius(ship), Fade(GREEN, .25));
#endif

		if (Animations::Blink())
			Assets::DrawSprite(Sprite::SPACESHIP, ship.pos,
				{ static_cast<float>(ship.size.x * 2), static_cast<float>(ship.size.y * 2) },
				{ static_cast<float>(ship.size.x), static_cast<float>(ship.size.y) },
				ship.rotation, WHITE);
	}

	void AdjustToRes(Ship& ship){
		Vector2 relMulti = Utils::GetLastRelativePosition(ship.pos);
		ship.pos = { static_cast<float>(GetScreenWidth() * relMulti.x), static_cast<float>(GetScreenHeight() * relMulti.y) };
		ship.size = { static_cast<float>(GetScreenHeight() * .02), static_cast<float>(GetScreenHeight() * .02) };
	}

	void Update(Ship& ship) {
		if (!Game::GetIsHalted()) {
			Move(ship);
		}
		Collisions::Update(ship);
	}

	Ship Create() {
		Ship ship;
		ship.pos = { 0, 0 };
		ship.size = { 0, 0 };
		ship.acceleration = { 0, 0 };
		ship.rotation = 0;
		ship.maxAccel = 0;
		ship.cannon = CreateCannon();
		return ship;
	}

	void Init(Ship& ship) {
		ship.pos = { static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .5) };
		ship.size = { static_cast<float>(GetScreenHeight() * .02), static_cast<float>(GetScreenHeight() * .02) };
		ship.speed = 400.0f;
		ship.maxAccel = 1.0f;
		InitCannon(ship.cannon);
	}
	void Init(Ship& ship, Vector2 pos, float speed, float maxAccel) {
		ship.pos = pos;
		ship.size = { static_cast<float>(GetScreenHeight() * .02), static_cast<float>(GetScreenHeight() * .02) };
		ship.speed = speed;
		ship.maxAccel = maxAccel;
		InitCannon(ship.cannon);
	}
}
