#pragma once
#include "raylib.h"

struct Bullet {
	Vector2 pos;
	float size;
	float direction;
	float speed;
	bool hurtsPlayer;
	float lifeTime;
	float spawnTime;
};

namespace Bullets {

	void Draw(Bullet bullet);
	void Update(Bullet& bullet);
	Bullet Create();
	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, float lifeTime, float spawnTime); // Sobrecarga, asume que son balas del jugador.
	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, float lifeTime, float spawnTime, bool hurtsPlayer);
}