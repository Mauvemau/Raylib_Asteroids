#include "Animations.h"
#include "Game.h"
#include "AssetLoader.h"

#include <iostream>

namespace Animations {
	// Blink
	const float blinkInterval = 0.25f;
	bool blink;
	float nextBlink;

	// Rotation
	const float rotationSpeed = 0.1f;
	float rotation;
	float nextRotate;

	// Animations
	const float animationFrameTime = 0.1f;
	const int maxAnimations = 25;
	Anim animations[maxAnimations];
	int activeAnimations;

	int GetAnimationIndex(Anims animation);
	int GetFrameAmount(Anims animation);
	void FinishAnimation(int id);
	Anim Create(Anims animation, Vector2 pos, Vector2 size);
	void Update(int id);

	// --

	int GetAnimationIndex(Anims animation) {
		switch (animation)
		{
		case Anims::EXPLOSION:
			return 5;
			break;
		default:
			std::cout << "Invalid Animation! [Animations.cpp - GetAnimationIndex]\n";
			return 0;
			break;
		}
	}

	int GetFrameAmount(Anims animation) {
		switch (animation)
		{
		case Anims::EXPLOSION:
			return 5;
			break;
		default:
			std::cout << "Invalid Animation! [Animations.cpp - GetFrameAmount]\n";
			return 0;
			break;
		}
	}

	void FinishAnimation(int id) {
		if (id < activeAnimations) {
			animations[id] = animations[activeAnimations - 1];
			activeAnimations--;
		}
	}

	Anim Create(Anims animation, Vector2 pos, Vector2 size) {
		Anim anim;
		anim.animation = animation;
		anim.currentFrame = 0;
		anim.lastFrame = 0;
		anim.pos = pos;
		anim.size = size;
		return anim;
	}

	void Update(int id) {
		if (animations[id].lastFrame < Game::GetGameTime()) {
			if (animations[id].currentFrame < GetFrameAmount(animations[id].animation)) {
				animations[id].currentFrame++;
				animations[id].lastFrame = Game::GetGameTime() + animationFrameTime;
			}
			else {
				FinishAnimation(id);
			}
		}
	}

	// Global

	float Rotation() {
		return rotation;
	}

	void PlayAnimation(Anims anim, Vector2 pos, Vector2 size) {
		animations[activeAnimations] = Create(anim, pos, size);
		activeAnimations++;
	}

	bool Blink() {
		if (!Game::GetIsHalted()) {
			return true;
		}
		else {
			if (nextBlink < Game::GetGameTime()) {
				blink = !blink;
				nextBlink = Game::GetGameTime() + blinkInterval;
			}
		}
		return blink;
	}

	void Draw() {
		for (int i = 0; i < activeAnimations; i++) {
			Assets::DrawSprite((Sprite)(GetAnimationIndex(animations[i].animation) + animations[i].currentFrame),
				animations[i].pos,
				animations[i].size,
				Vector2{ static_cast<float>(animations[i].size.x * .5), static_cast<float>(animations[i].size.y * .5) },
				0,
				WHITE);
		}
	}

	void Update() {
		for (int i = 0; i < activeAnimations; i++) {
			Update(i);
		}
		if (nextRotate < Game::GetGameTime()) {
			rotation++;
			nextRotate = Game::GetGameTime() + rotationSpeed;
		}
	}

	void Init() {
		blink = false;
		nextBlink = 0;
		activeAnimations = 0;
		rotation = 0;
		nextRotate = 0;
	}
}