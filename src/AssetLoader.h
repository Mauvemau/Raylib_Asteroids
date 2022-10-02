#pragma once
#include "raylib.h"
#include "Game/Asteroid.h"

enum class Musics {
	FINAL_LEVEL,
	COUNT
};

enum class Audio {
	SHOOT,
	EXPLOSION_1,
	EXPLOSION_2,
	EXPLOSION_3,
	POWERUP,
	HURT,
	PAUSE,
	PICKUP,
	COUNT
};

enum class Sprite {
	SPACESHIP,
	ASTEROID_BIG,
	ASTEROID_MED,
	ASTEROID_SMALL,
	TRAIL,
	EXPLOSION_0,
	EXPLOSION_1,
	EXPLOSION_2,
	EXPLOSION_3,
	EXPLOSION_4,
	EXPLOSION_5,
	COUNT
};

namespace Assets {
	void StopMusic(Musics music);
	void UpdateMusic(Musics music);
	void ResumeMusic(Musics music);
	void PauseMusic(Musics music);
	void PlayMusic(Musics music, float volume);
	void PlayAudio(Audio sound, float volume);
	void DrawSprite(Sprite sprite, Vector2 pos, Vector2 size, Vector2 pivot, float rotation, Color tint);

	Sprite GetAsteroidSprite(AsteroidType type);
	Texture2D GetSprite(Sprite sprite);

	void Unload();
	void Init();

}