#include "Invader.h"
#include "Utils.h"
#include "AssetLoader.h"
#include "Utils.h" // Para el random spawm position.
#include "ObjectManager.h"
#include "Game.h"

namespace Invader {

	void Shoot(Ship& ship);
	void InitCannon(Cannon& cannon);

	// --

	void Shoot(Ship& ship) {
		if (ship.cannon.fireRate < (Game::GetGameTime() - ship.cannon.lastShot)) {
			ship.cannon.lastShot = Game::GetGameTime();
			ObjManager::ActivateBullet(ship.pos,
				ship.cannon.caliber,
				Utils::DegreesToRadians(ship.rotation - 90.0f),
				ship.cannon.power,
				ship.cannon.range,
				true);
			Assets::PlayAudio(Audio::SHOOT, .5);
		}
	}

	void InitCannon(Cannon& cannon) {
		cannon.isEvil = true;
		cannon.fireRate = .5f;
		cannon.power = static_cast<float>(GetScreenHeight() * .5);
		cannon.range = 1.8f;
		cannon.caliber = static_cast<float>(GetScreenWidth() * .003);
		cannon.lastShot = 0;
	}

	//Global

	void Draw(Ship ship) {
#ifdef _DEBUG
		DrawCircle(static_cast<int>(ship.pos.x), static_cast<int>(ship.pos.y), Spaceship::GetCollisionRadius(ship), Fade(GREEN, .25));
#endif

		Assets::DrawSprite(Sprite::INVADER, ship.pos,
			{ static_cast<float>(ship.size.x * 2), static_cast<float>(ship.size.y * 2) },
			{ static_cast<float>(ship.size.x), static_cast<float>(ship.size.y) },
			ship.rotation, WHITE);
	}

	void Update(Ship& ship, Ship target) {
		Spaceship::Rotate(ship, Utils::CalculateRotationAngle(ship.pos, target.pos));
		Spaceship::Accelerate(ship, target.pos);
		Spaceship::Update(ship);
		Shoot(ship);
	}

	void Init(Ship& ship) {
		ship.pos = Utils::GetRandomSpawnPosition();
		ship.size = { static_cast<float>(GetScreenHeight() * .03), static_cast<float>(GetScreenHeight() * .03) };
		ship.speed = 300.0f;
		ship.maxAccel = .5f;
		InitCannon(ship.cannon);
	}
}