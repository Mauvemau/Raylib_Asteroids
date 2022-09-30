#include "GameOverMenu.h"
#include "Button.h"
#include "ProgramManager.h"

#include <iostream>

namespace GameOver {
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
		case GameOver::Options::PLAYAGAIN:
			return "Play Again";
			break;
		case GameOver::Options::RETURNTOMENU:
			return "Return to Menu";
			break;
		default:
			std::cout << "Invalid Option! [GameOverMenu.cpp - GetButtonName]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option)
		{
		case GameOver::Options::PLAYAGAIN:
			SetProgramStatus(ProgramStatus::INGAME);
			break;
		case GameOver::Options::RETURNTOMENU:
			SetProgramStatus(ProgramStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid Option! [GameOverMenu.cpp - SelectOption]\n";
			break;
		}
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += (float)(buttons[0].size.y + GetScreenWidth() * .025);
			buttons[i] = Buttons::Create(i,
				Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .55) + spacing },
				Vector2{ (float)(GetScreenWidth() * .35), (float)(GetScreenHeight() * .1) },
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