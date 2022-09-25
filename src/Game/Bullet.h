#pragma once
#include "raylib.h"

struct Bullet {
	Vector2 pos;
	float size;
	float direction;
	float speed;
	bool hurtsPlayer;
};

namespace Bullets {

	void Draw(Bullet bullet);
	void Update(Bullet& bullet, int id);
	Bullet Create();
	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed); // Sobrecarga, asume que son balas del jugador.
	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, bool hurtsPlayer);
}