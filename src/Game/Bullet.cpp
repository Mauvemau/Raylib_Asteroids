#include "Bullet.h"

#include <iostream> // Para cos, sin.

namespace Bullets {

	void Move(Bullet& bullet);

	// --

	void Move(Bullet& bullet) {
		bullet.pos.x += bullet.speed * cosf(bullet.direction) * GetFrameTime();
		bullet.pos.y += bullet.speed * sinf(bullet.direction) * GetFrameTime();
	}

	// Global

	void Draw(Bullet bullet) {
		DrawCircle(bullet.pos.x, bullet.pos.y, bullet.size, RAYWHITE);
	}

	void Update(Bullet& bullet) {
		Move(bullet);
	}

	Bullet Create() {
		Bullet bullet;
		bullet.pos = { 0, 0 };
		bullet.size = 0;
		bullet.direction = 0;
		bullet.speed = 0;
		bullet.hurtsPlayer = false;
		return bullet;
	}

	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed) {
		bullet.pos = pos;
		bullet.size = size;
		bullet.direction = direction;
		bullet.speed = speed;
		bullet.hurtsPlayer = false;
	}

	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, bool hurtsPlayer) {
		bullet.pos = pos;
		bullet.size = size;
		bullet.direction = direction;
		bullet.speed = speed;
		bullet.hurtsPlayer = hurtsPlayer;
	}
}