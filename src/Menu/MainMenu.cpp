#include "MainMenu.h"
#include "Button.h" // El menu tiene botones.
#include "ProgramManager.h" // Para cambiar el estado del juego.

#include <iostream>

namespace MainMenu {
	const int amountButtons = (int)Options::COUNT;
	Button buttons[amountButtons];

	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void Draw();

	// --

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case MainMenu::Options::PLAY:
			return "Play";
			break;
		case MainMenu::Options::SETTINGS:
			return "Settings";
			break;
		case MainMenu::Options::CREDITS:
			return "Credits";
			break;
		case MainMenu::Options::EXIT:
			return "Exit";
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
		case MainMenu::Options::PLAY:
			SetProgramStatus(ProgramStatus::INGAME);
			break;
		case MainMenu::Options::SETTINGS:
			break;
		case MainMenu::Options::CREDITS:
			break;
		case MainMenu::Options::EXIT:
			SetGameShouldClose(true);
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
				spacing += buttons[0].size.y + GetScreenWidth() * .025;
			buttons[i] = Buttons::Create(i,
				Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .45) + spacing },
				Vector2{ (float)(GetScreenWidth() * .3), (float)(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
		}
	}

	void Draw() {
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < amountButtons; i++) {
			Buttons::Draw(buttons[i]);
		}

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