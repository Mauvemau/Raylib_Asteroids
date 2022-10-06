#include "Upgrades.h"
#include "Button.h"
#include "Utils.h"
#include "PauseMenu.h"
#include "Game/Game.h"

namespace Upgrades {
	const int amountButtons = (int)Options::COUNT;
	Button buttons[amountButtons];

	Color GetButtonColor(Options option);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawText();

	// --

	Color GetButtonColor(Options option) {
		switch (option) {
		case Upgrades::Options::RETURN:
			return RED;
			break;
		default:
			return GREEN;
			break;
		}
	}

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case Upgrades::Options::HEALTH:
			return "+1 Life";
			break;
		case Upgrades::Options::FIRERATE:
			return "+15% Fire Rate";
			break;
		case Upgrades::Options::BULLETSIZE:
			return "+50% Bullet Size";
			break;
		case Upgrades::Options::BULLETRANGE:
			return "+20% Bullet Range";
			break;
		case Upgrades::Options::BULLETSPEED:
			return "+20% Bullet Speed";
			break;
		case Upgrades::Options::RETURN:
			return "I don't need upgrades";
		default:
			std::cout << "Invalid Option! [Upgrades.cpp - GetButtonName]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option) {
		case Upgrades::Options::HEALTH:
			Game::AddLive(1);
			break;
		case Upgrades::Options::FIRERATE:
			Game::GetPlayer().cannon.fireRate = (float)(Game::GetPlayer().cannon.fireRate * .85f);
			break;
		case Upgrades::Options::BULLETSIZE:
			Game::GetPlayer().cannon.caliber = (float)(Game::GetPlayer().cannon.caliber * 1.5f);
			break;
		case Upgrades::Options::BULLETRANGE:
			Game::GetPlayer().cannon.range = (float)(Game::GetPlayer().cannon.range * 1.2f);
			break;
		case Upgrades::Options::BULLETSPEED:
			Game::GetPlayer().cannon.power = (float)(Game::GetPlayer().cannon.power * 1.2f);
			break;
		default:
			break;
		}
		Pause::FinishUpgrading();
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenHeight() * .025;
			buttons[i] = Buttons::Create(i,
				Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .3) + spacing },
				Vector2{ (float)(GetScreenWidth() * .325), (float)(GetScreenHeight() * .075) },
				GetButtonColor((Options)i),
				GetButtonName((Options)i));
		}
	}

	void DrawText() {
		Utils::DrawCenteredText("You picked up a PowerUp!",
			Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .15) },
			GetScreenHeight() * .075, SKYBLUE);
		Utils::DrawCenteredText("Please select an upgrade",
			Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .225) },
			GetScreenHeight() * .03, RAYWHITE);
	}

	// Global

	void Draw() {
		for (int i = 0; i < amountButtons; i++) {
			Buttons::Draw(buttons[i]);
		}
		DrawText();
	}

	void Update() {
		for (int i = 0; i < amountButtons; i++) {
			if (Buttons::Update(buttons[i]))
				SelectOption((Options)buttons[i].id);
		}
	}

	void Init() {
		InitButtons();
	}
}