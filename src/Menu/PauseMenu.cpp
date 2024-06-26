#include "PauseMenu.h"
#include "Button.h"
#include "Game/Game.h" // Para controlar la pausa del juego.
#include "ProgramManager.h" // Para controlar el estado del programa y poder reiniciar y volver al menu.
#include "Utils.h" // Para el texto centrado
#include "AssetLoader.h" // Para la musica.
#include "Upgrades.h" // Para los powerups.

#include <iostream>

namespace Pause {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	bool upgrading;

	void DrawText();
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();

	// --

	void DrawText() {
		Utils::DrawCenteredText("GAME PAUSED", 
			Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .25) },
			static_cast<int>(GetScreenHeight() * .1f), RAYWHITE);
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
			Assets::StopMusic(Musics::FINAL_LEVEL);
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
				spacing += buttons[0].size.y + GetScreenHeight() * .025f;
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .5) + spacing },
				Vector2{ static_cast<float>(GetScreenWidth() * .325), static_cast<float>(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
		}
	}

	// Global

	void FinishUpgrading() {
		upgrading = false;
		SelectOption(Options::RESUME);
	}

	void StartUpgrading() {
		upgrading = true;
	}

	void Draw() {
		// Simplemente dibujamos, ya que este draw se encuentra adentro del draw de Game.
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, .5));
		if (!upgrading) {
			for (int i = 0; i < amountButtons; i++) {
				Buttons::Draw(buttons[i]);
			}
			DrawText();
		}
		else {
			Upgrades::Draw();
		}
	}

	void Update() {
		if (!upgrading) {
			for (int i = 0; i < amountButtons; i++) {
				if (Buttons::Update(buttons[i]))
					SelectOption((Options)buttons[i].id);
			}

			if (IsKeyPressed(KEY_ESCAPE))
				Game::SetPaused(false);
		}
		else {
			Upgrades::Update();
		}
	}

	void AdjustToRes() {
		InitButtons();
		Upgrades::AdjustToRes();
	}

	void Init() {
		AdjustToRes();
		Upgrades::Init();
		upgrading = false;
	}
}
