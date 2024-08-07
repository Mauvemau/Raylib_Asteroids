#include "Pickup.h"
#include "AssetLoader.h"
#include "CollisionManager.h"
#include "Utils.h" // Para el spawn pos
#include "Game.h" // Para sumar score.
#include "Animations.h" // Para la rotacion

namespace Pickups {
	void Move(Pickup& pickup);
	float GetRandomSpeed();
	Vector2 GetSpriteSize(PickupType type);
	Sprite GetSprite(PickupType type);

	// --

	void Move(Pickup& pickup) {
		pickup.pos.x += pickup.speed * cosf(pickup.direction) * GetFrameTime();
		pickup.pos.y += pickup.speed * sinf(pickup.direction) * GetFrameTime();
	}

	float GetRandomSpeed() {
		return static_cast<float>(GetRandomValue(25, 100));
	}

	Vector2 GetSpriteSize(PickupType type) {
		float size;
		switch (type) {
		case PickupType::COIN:
			size = .01f;
			break;
		case PickupType::SUS:
			size = .02f;
			break;
		case PickupType::UPGRADE:
			size = .04f;
			break;
		default:
			std::cout << "Invalid type! [Pickup.cpp - GetSpriteSize]\n";
			size = .005f;
			break;
		}
		return Vector2{ static_cast<float>(GetScreenHeight() * size), static_cast<float>(GetScreenHeight() * size) };
	}

	Sprite GetSprite(PickupType type) {
		switch (type) {
		case PickupType::COIN:
			return Sprite::COIN;
			break;
		case PickupType::SUS:
			return Sprite::SUS;
			break;
		case PickupType::UPGRADE:
			return Sprite::UPGRADE;
			break;
		default:
			std::cout << "Invalid Pickup! [Pickup.cpp - GetPrickupSprite]\n";
			return Sprite::COIN;
			break;
		}
	}

	// Global

	void HandlePickup(PickupType pickup) {
		switch (pickup) {
		case PickupType::COIN:
			Game::AddScore(5);
			Assets::PlayAudio(Audio::PICKUP, .5f);
			break;
		case PickupType::SUS:
			Game::AddScore(100);
			Assets::PlayAudio(Audio::PICKUP, .5f);
			break;
		case PickupType::UPGRADE:
			Game::OpenUpgradeMenu();
			Assets::PlayAudio(Audio::POWERUP, .1f);
			Spaceship::ResetAcceleration(Game::GetPlayer());
			break;
		default:
			std::cout << "Invalid Pickup Type! [Pickup.cpp - HandlePickup]\n";
			break;
		}
	}

	void Draw(Pickup pickup) {
		Vector2 size = GetSpriteSize(pickup.type);
		float rotation = 0.0f;
		if (pickup.type == PickupType::SUS)
			rotation = Animations::Rotation();
		Assets::DrawSprite(GetSprite(pickup.type), pickup.pos, size,
			Vector2{ static_cast<float>(size.x * .5), static_cast<float>(size.y * .5) }, rotation, WHITE);
	}

	void AdjustToRes(Pickup& pickup){
		Vector2 relMulti = Utils::GetLastRelativePosition(pickup.pos);
		pickup.pos = { static_cast<float>(GetScreenWidth() * relMulti.x), static_cast<float>(GetScreenHeight() * relMulti.y) };
	}

	void Update(Pickup& pickup) {
		Move(pickup);
		Collisions::Update(pickup);
	}

	Pickup Create() {
		Pickup pickup;
		pickup.pos = { 0, 0 };
		pickup.type = PickupType::COIN;
		return pickup;
	}

	void Init(Pickup& pickup, PickupType type) {
		pickup.pos = Utils::GetRandomSpawnPosition();
		pickup.type = type;
		pickup.direction = static_cast<float>(GetRandomValue(0, 360));
		pickup.speed = GetRandomSpeed();
	}
}
