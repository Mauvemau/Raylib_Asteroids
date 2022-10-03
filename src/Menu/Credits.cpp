#include "Credits.h"
#include "Button.h" // El menu tiene botones.
#include "Utils.h" // Para el texto centrado.
#include "ProgramManager.h" // Para cambiar el estado del juego.

#include <iostream>

namespace Credits {
	const int amountButtons = (int)Options::COUNT;
	Button buttons[amountButtons];


	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawText();
	void Draw();

	// --

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case Credits::Options::RAYLIB:
			return "Raylib";
			break;
		case Credits::Options::MUSIC:
			return "HoliznaCC0";
			break;
		case Credits::Options::ANIMATION:
			return "9KeyStudio";
			break;
		case Credits::Options::SFX:
			return "Chiptone";
			break;
		case Credits::Options::SPRITES:
			return "Aseprite";
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
			std::cout << "Invalid Option! [MainMenu.cpp - SelectOption()]\n";
			break;
		}
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenWidth() * .06;
			buttons[i] = Buttons::Create(i,
				Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .15) + spacing },
				Vector2{ (float)(GetScreenWidth() * .3), (float)(GetScreenHeight() * .075) },
				GetButtonName((Options)i));
		}
	}

	void DrawText() {
		Utils::DrawCenteredText("Game Built using Raylib by Ray", { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .065) }, (float)(GetScreenHeight() * .05), PINK);
		Utils::DrawCenteredText("Game Music by HoliznaCC0", { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .225) }, (float)(GetScreenHeight() * .05), ORANGE);
		Utils::DrawCenteredText("Explosion Animation by 9KeyStudio", { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .38) }, (float)(GetScreenHeight() * .05), RED);
		Utils::DrawCenteredText("Sound Effects made using Chiptone", { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .535) }, (float)(GetScreenHeight() * .05), GREEN);
		Utils::DrawCenteredText("Sprites made using Aseprite", { (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .69) }, (float)(GetScreenHeight() * .05), SKYBLUE);
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

		Draw();
	}

	void Init() {
		InitButtons();
	}
}