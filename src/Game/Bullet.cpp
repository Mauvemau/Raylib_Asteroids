#include "Bullet.h"
#include "CollisionManager.h" // Para manejar las colisiones.
#include "AssetLoader.h" // Para el sprite del trail
#include "Utils.h"

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
		Vector2 trailEnd;
		Color col;
		if (!bullet.hurtsPlayer)
			col = WHITE;
		else
			col = RED;

		trailEnd.x = (float)(bullet.pos.x + (-bullet.speed * .1) * cosf(bullet.direction));
		trailEnd.y = (float)(bullet.pos.y + (-bullet.speed * .1) * sinf(bullet.direction));
		DrawCircle(bullet.pos.x, bullet.pos.y, bullet.size, col);

		
		Assets::DrawSprite(Sprite::TRAIL, bullet.pos,
			{ (float)(bullet.size + bullet.speed * .1), (float)(bullet.size * 2) },
			{ (float)(bullet.size + bullet.speed * .1), (float)(bullet.size * 1) },
			Utils::RadiansToDegrees(bullet.direction), col);

		//DrawLineEx(bullet.pos, trailEnd, (bullet.size * .5), Fade(RAYWHITE, .25));
	}

	void Update(Bullet& bullet) {
		Move(bullet);
		Collisions::Update(bullet);
	}

	Bullet Create() {
		Bullet bullet;
		bullet.pos = { 0, 0 };
		bullet.size = 0;
		bullet.direction = 0;
		bullet.speed = 0;
		bullet.hurtsPlayer = false;
		bullet.lifeTime = 0;
		bullet.spawnTime = 0;
		return bullet;
	}

	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, float lifeTime, float spawnTime) {
		bullet.pos = pos;
		bullet.size = size;
		bullet.direction = direction;
		bullet.speed = speed;
		bullet.hurtsPlayer = false;
		bullet.lifeTime = lifeTime;
		bullet.spawnTime = spawnTime;
	}

	void Init(Bullet& bullet, Vector2 pos, float size, float direction, float speed, float lifeTime, float spawnTime, bool hurtsPlayer) {
		bullet.pos = pos;
		bullet.size = size;
		bullet.direction = direction;
		bullet.speed = speed;
		bullet.hurtsPlayer = hurtsPlayer;
		bullet.lifeTime = lifeTime;
		bullet.spawnTime = spawnTime;
	}
}