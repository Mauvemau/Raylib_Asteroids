#include "AssetLoader.h"

#include <iostream>

namespace Assets {

	const int musicAmount = (int)Musics::COUNT;
	Music musics[musicAmount];

	const int soundAmount = (int)Audio::COUNT;
	Sound sounds[soundAmount];

	const int spriteAmount = (int)Sprite::COUNT;
	Texture2D sprites[spriteAmount];

	void UnloadMusics();
	void LoadMusic(const char* path, int id);
	void LoadMusics();
	void UnloadAudios();
	void LoadAudio(const char* path, int id);
	void LoadAudios();
	void UnloadSprites();
	void LoadSprite(const char* path, int id);
	void LoadSprites();
	void InitAudio();

	// --

	void UnloadMusics() {
		for (int i = 0; i < musicAmount; i++) {
			UnloadMusicStream(musics[i]);
		}
	}

	void LoadMusic(const char* path, int id) {
		musics[id] = LoadMusicStream(path);
	}

	void LoadMusics() {
		for (int i = 0; i < musicAmount; i++) {
			switch ((Musics)i)
			{
			case Musics::FINAL_LEVEL:
				LoadMusic("resources/music/HoliznaCC0 - Final Level.mp3", i);
				break;
			default:
				std::cout << "[!] Invalid Music: AssetLoader - LoadMusics\n";
				break;
			}
		}
	}

	void LoadAudio(const char* path, int id) {
		sounds[id] = LoadSound(path);
	}

	void UnloadAudios() {
		for (int i = 0; i < soundAmount; i++) {
			UnloadSound(sounds[i]);
		}
	}

	void LoadAudios() {
		for (int i = 0; i < soundAmount; i++) {
			switch ((Audio)i)
			{
			case Audio::SHOOT:
				LoadAudio("resources/sounds/shoot.wav", i);
				break;
			case Audio::EXPLOSION_1:
				LoadAudio("resources/sounds/explosion_1.wav", i);
				break;
			case Audio::EXPLOSION_2:
				LoadAudio("resources/sounds/explosion_2.wav", i);
				break;
			case Audio::EXPLOSION_3:
				LoadAudio("resources/sounds/explosion_3.wav", i);
				break;
			case Audio::POWERUP:
				LoadAudio("resources/sounds/power_up.wav", i);
				break;
			case Audio::HURT:
				LoadAudio("resources/sounds/hurt.wav", i);
				break;
			case Audio::PAUSE:
				LoadAudio("resources/sounds/pause.wav", i);
				break;
			case Audio::PICKUP:
				LoadAudio("resources/sounds/pickup.wav", i);
				break;
			default:
				std::cout << "[!] Invalid Audio: AssetLoader - LoadAudios\n";
				break;
			}
		}
	}

	void LoadSprite(const char* path, int id) {
		sprites[id] = LoadTexture(path);
	}

	void UnloadSprites() {
		for (int i = 0; i < spriteAmount; i++) {
			UnloadTexture(sprites[i]);
		}
	}

	void LoadSprites() {
		for (int i = 0; i < spriteAmount; i++) {
			switch ((Sprite)i)
			{
			case Sprite::SPACESHIP:
				LoadSprite("resources/sprites/spaceship.png", i);
				break;
			case Sprite::ASTEROID_BIG:
				LoadSprite("resources/sprites/asteroid_big.png", i);
				break;
			case Sprite::ASTEROID_MED:
				LoadSprite("resources/sprites/asteroid_medium.png", i);
				break;
			case Sprite::ASTEROID_SMALL:
				LoadSprite("resources/sprites/asteroid_mini.png", i);
				break;
			case Sprite::TRAIL:
				LoadSprite("resources/sprites/trail.png", i);
				break;
			case Sprite::EXPLOSION_0:
				LoadSprite("resources/sprites/explosion/0.png", i);
				break;
			case Sprite::EXPLOSION_1:
				LoadSprite("resources/sprites/explosion/1.png", i);
				break;
			case Sprite::EXPLOSION_2:
				LoadSprite("resources/sprites/explosion/2.png", i);
				break;
			case Sprite::EXPLOSION_3:
				LoadSprite("resources/sprites/explosion/3.png", i);
				break;
			case Sprite::EXPLOSION_4:
				LoadSprite("resources/sprites/explosion/4.png", i);
				break;
			case Sprite::EXPLOSION_5:
				LoadSprite("resources/sprites/explosion/5.png", i);
				break;
			default:
				std::cout << "[!] Invalid Sprite: AssetLoader - LoadSprites\n";
				break;
			}
		}
	}

	void InitAudio() {
		InitAudioDevice();
	}

	// Global

	void StopMusic(Musics music) {
		StopMusicStream(musics[(int)music]);
	}

	void UpdateMusic(Musics music) {
		UpdateMusicStream(musics[(int)music]);
	}

	void ResumeMusic(Musics music) {
		ResumeMusicStream(musics[(int)music]);
	}

	void PauseMusic(Musics music) {
		PauseMusicStream(musics[(int)music]);
	}

	void PlayMusic(Musics music, float volume) {
		SetMusicVolume(musics[(int)music], volume);
		PlayMusicStream(musics[(int)music]);
	}

	void DrawSprite(Sprite sprite, Vector2 pos, Vector2 size, Vector2 pivot, float rotation, Color tint) {
		Texture2D texture = Assets::GetSprite(sprite);
		int textureWidth = texture.width;
		int textureHeight = texture.height;

		DrawTexturePro(texture,
			{ 0.0f, 0.0f, (float)textureWidth, (float)textureHeight },
			{ pos.x, pos.y, size.x, size.y },
			{ pivot.x, pivot.y },
			rotation, tint);
	}

	void PlayAudio(Audio sound, float volume) {
		SetSoundVolume(sounds[(int)sound], volume);
		PlaySound(sounds[(int)sound]);
	}

	Sprite GetAsteroidSprite(AsteroidType type) {
		Sprite sprite;
		switch (type)
		{
		case AsteroidType::BIG:
			sprite = Sprite::ASTEROID_BIG;
			break;
		case AsteroidType::MEDIUM:
			sprite = Sprite::ASTEROID_MED;
			break;
		case AsteroidType::SMALL:
			sprite = Sprite::ASTEROID_SMALL;
			break;
		default:
			sprite = Sprite::ASTEROID_BIG;
			std::cout << "[!] Invalid Asteroid Type: AssetLoader - GetAsteroidSprite\n";
			break;
		}
		return sprite;
	}

	Texture2D GetSprite(Sprite sprite) {
		return sprites[(int)sprite];
	}

	void Unload() {
		UnloadAudios();
		UnloadSprites();
		UnloadMusics();
	}

	void Init() {
		InitAudio();
		LoadAudios();
		LoadSprites();
		LoadMusics();
	}
}