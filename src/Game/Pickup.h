#pragma once

#include "raylib.h"

enum class PickupType {
	COIN,
	SUS,
	UPGRADE
};

struct Pickup {
	Vector2 pos;
	PickupType type;
	float direction;
	float speed;
};

namespace Pickups {
	void HandlePickup(PickupType pickup);

	void Draw(Pickup pickup);
	void Update(Pickup& pickup);
	Pickup Create();
	void Init(Pickup& pickup, PickupType type);
}