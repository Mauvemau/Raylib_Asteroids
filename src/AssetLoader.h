#pragma once
#include "raylib.h"
#include "Game/Asteroid.h"

enum class Audio {
	SHOOT,
	EXPLOSION_1,
	EXPLOSION_2,
	EXPLOSION_3,
	POWERUP,
	HURT,
	COUNT
};

enum class Sprite {
	SPACESHIP,
	ASTEROID_BIG,
	ASTEROID_MED,
	ASTEROID_SMALL,
	TRAIL,
	COUNT
};

namespace Assets {

	void PlayAudio(Audio sound, float volume);
	void DrawSprite(Sprite sprite, Vector2 pos, Vector2 size, Vector2 pivot, float rotation, Color tint);

	Sprite GetAsteroidSprite(AsteroidType type);
	Texture2D GetSprite(Sprite sprite);

	void Unload();
	void Init();

}