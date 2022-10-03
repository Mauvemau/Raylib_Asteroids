#pragma once
#include "raylib.h"

enum class Anims { // Raylib es dueño del nombre Animations
	EXPLOSION,
	COUNT
};

struct Anim {
	Anims animation;
	int currentFrame;
	float lastFrame;
	Vector2 pos;
	Vector2 size;
};

namespace Animations {

	void PlayAnimation(Anims anim, Vector2 pos, Vector2 size);
	bool Blink();

	void Draw();
	void Update();
	void Init();
}