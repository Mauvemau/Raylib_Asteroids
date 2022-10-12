#include "GameOverMenu.h"
#include "Button.h"
#include "ProgramManager.h"
#include "AssetLoader.h" // Para la musica.
#include "Utils.h" // Para el texto centrado.
#include "Game/Game.h" // Para el score.
#include "SaveFileManager.h" // Para guardar el highscore.

#include <iostream>

namespace GameOver {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	bool isHighScore;
	long highScore;

	bool ManageHighScore(long score);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawText();
	void Draw();

	// --

	bool ManageHighScore(long score) {
		highScore = Saves::GetHighScore();
		if (score > highScore) {
			std::cout << "[High Score] New High score of " << score << "!!\n";
			Saves::SaveHighScore(score);
		}
		return (score > highScore);
	}

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
			Assets::StopMusic(Musics::FINAL_LEVEL);
			SetProgramStatus(ProgramStatus::INGAME);
			break;
		case GameOver::Options::RETURNTOMENU:
			Assets::StopMusic(Musics::FINAL_LEVEL);
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
				spacing += static_cast<float>(buttons[0].size.y + GetScreenHeight() * .025);
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .6) + spacing },
				Vector2{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .1) },
				GetButtonName((Options)i));
		}
	}

	void DrawText() {
		Utils::DrawCenteredText("Game Over",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .25) },
			static_cast<int>(GetScreenHeight() * .15f), RED);

		Utils::DrawCenteredText(TextFormat("Your Score: %i", Game::GetScore()),
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .375) },
			static_cast<int>(GetScreenWidth() * .05), RAYWHITE);

		if (!isHighScore) {
			if (highScore > 0) {
				Utils::DrawCenteredText(TextFormat("Best recorded Score: %i", highScore),
					{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .46) },
					static_cast<int>(GetScreenWidth() * .03), SKYBLUE);
			}
		}
		else {
			Utils::DrawCenteredText("Congratulations, you've set a new record!!!",
				{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .46) },
				static_cast<int>(GetScreenWidth() * .03), ORANGE);
		}

		Utils::DrawCenteredText(TextFormat("You have destroyed a total of %i Asteroids!", Game::GetAsteroidsDestroyed()),
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .5) },
			static_cast<int>(GetScreenWidth() * .02), GREEN);
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
		isHighScore = ManageHighScore(Game::GetScore());
	}
}