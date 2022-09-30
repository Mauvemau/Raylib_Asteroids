#include "PauseMenu.h"
#include "Button.h"
#include "Game/Game.h" // Para controlar la pausa del juego.
#include "ProgramManager.h" // Para controlar el estado del programa y poder reiniciar y volver al menu.
#include "Utils.h" // Para el texto centrado

#include <iostream>

namespace Pause {
	const int amountButtons = (int)Options::COUNT;
	Button buttons[amountButtons];

	void DrawMenuText();
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();

	// --

	void DrawMenuText() {
		Utils::DrawCenteredText("GAME PAUSED", 
			Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .25) }, 
			GetScreenHeight() * .1, RAYWHITE);
	}

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case Pause::Options::RESUME:
			return "Resume";
			break;
		case Pause::Options::RESTART:
			return "Restart";
			break;
		case Pause::Options::RETURNTOMENU:
			return "Return to Menu";
			break;
		default:
			std::cout << "Invalid Option! [PauseMenu.cpp - GetButtonname()]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option)
		{
		case Pause::Options::RESUME:
			Game::SetPaused(false);
			break;
		case Pause::Options::RESTART:
			SetProgramStatus(ProgramStatus::INGAME);
			break;
		case Pause::Options::RETURNTOMENU:
			SetProgramStatus(ProgramStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid Option! [PauseMenu.cpp - SelectOption()]\n";
			break;
		}
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenWidth() * .025;
			buttons[i] = Buttons::Create(i,
				Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .5) + spacing },
				Vector2{ (float)(GetScreenWidth() * .325), (float)(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
		}
	}

	// Global

	void Draw() {
		// Simplemente dibujamos, ya que este draw se encuentra adentro del draw de Game.
		for (int i = 0; i < amountButtons; i++) {
			Buttons::Draw(buttons[i]);
		}
		DrawMenuText();
	}

	void Update() {
		for (int i = 0; i < amountButtons; i++) {
			if (Buttons::Update(buttons[i]))
				SelectOption((Options)buttons[i].id);
		}

		if (IsKeyPressed(KEY_ESCAPE))
			Game::SetPaused(false);
	}

	void Init() {
		InitButtons();
	}
}