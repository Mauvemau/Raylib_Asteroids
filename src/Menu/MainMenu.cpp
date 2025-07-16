#include "MainMenu.h"
#include "Button.h" // El menu tiene botones.
#include "ProgramManager.h" // Para cambiar el estado del juego.
#include "Utils.h" // Para el texto centrado.
#include "SaveFileManager.h" // Para mostrar el highscore.

#include <iostream>

namespace MainMenu {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	long highscore;

	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawCredits();
	void DrawText();
	void Draw();

	// --

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case MainMenu::Options::PLAY:
			return "Play";
			break;
#ifdef _WIN32
		case MainMenu::Options::SETTINGS:
			return "Settings";
			break;
#endif // _WIN32
		case MainMenu::Options::CREDITS:
			return "Credits";
			break;
#ifndef PLATFORM_WEB
		case MainMenu::Options::EXIT:
			return "Exit";
			break;
#endif
		default:
			std::cout << "Invalid Option! [MainMenu.cpp - GetButtonname]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option)
		{
		case MainMenu::Options::PLAY:
			SetProgramStatus(ProgramStatus::INGAME);
			break;
#ifdef _WIN32
		case MainMenu::Options::SETTINGS:
			SetProgramStatus(ProgramStatus::SETTINGS);
			break;
#endif // _WIN32
		case MainMenu::Options::CREDITS:
			SetProgramStatus(ProgramStatus::CREDITS);
			break;
#ifndef PLATFORM_WEB
		case MainMenu::Options::EXIT:
			SetGameShouldClose(true);
			break;
#endif
		default:
			std::cout << "Invalid Option! [MainMenu.cpp - SelectOption()]\n";
			break;
		}
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenHeight() * .025f;
#ifdef PLATFORM_WEB
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .5) + spacing },
				Vector2{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
#else
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .45) + spacing },
				Vector2{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
#endif
		}
	}

	void DrawCredits() {
		const char* text = "Game by Mauvemau, powered by Raylib.";
		int fontSize = static_cast<int>(GetScreenHeight() * .025f);
		int textWide = MeasureText(text, fontSize);
		DrawText(text, static_cast<int>((GetScreenWidth() * .99) - textWide), static_cast<int>((GetScreenHeight() * .99) - fontSize), fontSize, WHITE);
	}

	void DrawText() {
		Utils::DrawCenteredText("Astray", 
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .17) },
			static_cast<int>(GetScreenHeight() * .2f), SKYBLUE);
		Utils::DrawCenteredText("An Asteroids-like Game", 
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .26) },
			static_cast<int>(GetScreenHeight() * .035f), ORANGE);
		if (highscore > 0) {
			Utils::DrawCenteredText(TextFormat("High Score: %i", highscore),
				{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .375) },
				static_cast<int>(GetScreenHeight() * .032f), PINK);
		}
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < amountButtons; i++) {
			Buttons::Draw(buttons[i]);
		}

		DrawText();
		DrawCredits();

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

	void AdjustToRes() {
		InitButtons();
	}

	void Init() {
		AdjustToRes();
		highscore = Saves::GetHighScore();
	}
}
