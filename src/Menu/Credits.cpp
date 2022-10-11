#include "Credits.h"
#include "Button.h" // El menu tiene botones.
#include "Utils.h" // Para el texto centrado.
#include "ProgramManager.h" // Para cambiar el estado del juego.

#include <iostream>

namespace Credits {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	Color GetButtonColor(Options option);
	float GetButtonWidth(Options option);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawText();
	void Draw();

	// --


	Color GetButtonColor(Options option) {
		switch (option)
		{
		case Credits::Options::RAYLIB:
			return RED;
			break;
		case Credits::Options::MUSIC:
			return GREEN;
			break;
		case Credits::Options::ANIMATION:
			return SKYBLUE;
			break;
		case Credits::Options::SFX:
			return ORANGE;
			break;
		case Credits::Options::SPRITES:
			return PINK;
			break;
		default:
			return RAYWHITE;
			break;
		}
	}

	float GetButtonWidth(Options option) {
		switch (option)
		{
		case Credits::Options::RETURNTOMENU:
			return static_cast<float>(GetScreenWidth() * .3);
			break;
		default:
			return static_cast<float>(GetScreenWidth() * .5);
			break;
		}
	}

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case Credits::Options::RAYLIB:
			return "Game Built using Raylib by Ray";
			break;
		case Credits::Options::MUSIC:
			return "Game Music by HoliznaCC0";
			break;
		case Credits::Options::ANIMATION:
			return "Explosion Animation by 9KeyStudio";
			break;
		case Credits::Options::SFX:
			return "Sound Effects made using Chiptone";
			break;
		case Credits::Options::SPRITES:
			return "Sprites made using Aseprite";
			break;
		case Credits::Options::RETURNTOMENU:
			return "Return to Menu";
			break;
		default:
			std::cout << "Invalid Option! [MainMenu.cpp - GetButtonname()]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option)
		{
		case Credits::Options::RAYLIB:
			OpenURL("https://www.raylib.com");
			break;
		case Credits::Options::MUSIC:
			OpenURL("https://freemusicarchive.org/music/holiznacc0/gamer-beats/final-level/");
			break;
		case Credits::Options::ANIMATION:
			OpenURL("https://opengameart.org/content/pixel-art-explosion-animation");
			break;
		case Credits::Options::SFX:
			OpenURL("https://sfbgames.itch.io/chiptone");
			break;
		case Credits::Options::SPRITES:
			OpenURL("https://www.aseprite.org");
			break;
		case Credits::Options::RETURNTOMENU:
			SetProgramStatus(ProgramStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid Option! [MainMenu.cpp - SelectOption]\n";
			break;
		}
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenHeight() * .03f;
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .24) + spacing },
				Vector2{ GetButtonWidth((Options)i), static_cast<float>(GetScreenWidth() * .05) },
				GetButtonColor((Options)i),
				GetButtonName((Options)i));
		}
	}

	void DrawText() {

	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < amountButtons; i++) {
			Buttons::Draw(buttons[i]);
		}

		DrawText();

		EndDrawing();
	}

	// Global

	void Update() {
		for (int i = 0; i < amountButtons; i++) {
			if (Buttons::Update(buttons[i]))
				SelectOption((Options)buttons[i].id);
		}

		if(GetKeyPressed())
			SetProgramStatus(ProgramStatus::MAINMENU);

		Draw();
	}

	void Init() {
		InitButtons();
	}
}