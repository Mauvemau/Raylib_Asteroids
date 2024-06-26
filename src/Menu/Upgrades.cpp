#include "Upgrades.h"
#include "Button.h"
#include "Utils.h"
#include "PauseMenu.h"
#include "Game/Game.h"

#include <iostream>

namespace Upgrades {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	float maxFireRate;
	float maxCaliber;
	float maxRange;
	float maxPower;

	bool IsCapped(Options option);
	void CheckCaps(Cannon& cannon);
	Color GetButtonColor(Options option);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawText();

	// --

	bool IsCapped(Options option) {
		Cannon cannon = Game::GetPlayer().cannon;

		switch (option)
		{
		case Upgrades::Options::FIRERATE:
			if (cannon.fireRate == maxFireRate)
				return true;
			break;
		case Upgrades::Options::BULLETSIZE:
			if (cannon.caliber == maxCaliber)
				return true;
			break;
		case Upgrades::Options::BULLETRANGE:
			if (cannon.range == maxRange)
				return true;
			break;
		case Upgrades::Options::BULLETSPEED:
			if (cannon.power == maxPower)
				return true;
			break;
		default:
			break;
		}

		return false;
	}

	void CheckCaps(Cannon& cannon) {
		if (cannon.fireRate < maxFireRate) {
			std::cout << "Maximum Fire Rate reached.\n";
			cannon.fireRate = maxFireRate;
		}
		if (cannon.caliber > maxCaliber) {
			std::cout << "Maximum Bullet Size reached.\n";
			cannon.caliber = maxCaliber;
		}
		if (cannon.range > maxRange) {
			std::cout << "Maximum Bullet Range reached.\n";
			cannon.range = maxRange;
		}
		if (cannon.power > maxPower) {
			std::cout << "Maximum Bullet Speed reached.\n";
			cannon.power = maxPower;
		}
	}

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
			return "+20% Fire Rate";
			break;
		case Upgrades::Options::BULLETSIZE:
			return "+50% Bullet Size";
			break;
		case Upgrades::Options::BULLETRANGE:
			return "+40% Bullet Range";
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
			Game::GetPlayer().cannon.fireRate = static_cast<float>(Game::GetPlayer().cannon.fireRate * .8f);
			break;
		case Upgrades::Options::BULLETSIZE:
			Game::GetPlayer().cannon.caliber = static_cast<float>(Game::GetPlayer().cannon.caliber * 1.5f);
			break;
		case Upgrades::Options::BULLETRANGE:
			Game::GetPlayer().cannon.range = static_cast<float>(Game::GetPlayer().cannon.range * 1.4f);
			break;
		case Upgrades::Options::BULLETSPEED:
			Game::GetPlayer().cannon.power = static_cast<float>(Game::GetPlayer().cannon.power * 1.2f);
			break;
		default:
			break;
		}
		CheckCaps(Game::GetPlayer().cannon);
		Pause::FinishUpgrading();
	}

	void InitButtons() {
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			if (i > 0)
				spacing += buttons[0].size.y + GetScreenHeight() * .025f;
			buttons[i] = Buttons::Create(i,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .3) + spacing },
				Vector2{ static_cast<float>(GetScreenWidth() * .325), static_cast<float>(GetScreenHeight() * .075) },
				GetButtonColor((Options)i),
				GetButtonName((Options)i));
		}
	}

	void DrawText() {
		Utils::DrawCenteredText("You picked up a PowerUp!",
			Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .15) },
			static_cast<int>(GetScreenHeight() * .075f), SKYBLUE);
		Utils::DrawCenteredText("Please select an upgrade",
			Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .225) },
			static_cast<int>(GetScreenHeight() * .03f), RAYWHITE);
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
			if (IsCapped((Options)i)) {
				buttons[i].col = DARKGRAY;
			}
			if (Buttons::Update(buttons[i])) {
				if(!IsCapped((Options)i))
					SelectOption((Options)buttons[i].id);
			}
		}
	}

	void AdjustToRes() {
		InitButtons();
	}

	void Init() {
		AdjustToRes();

		maxFireRate = .085f;
		maxCaliber = static_cast<float>(GetScreenHeight() * .015);
		maxRange = 2.0f;
		maxPower = static_cast<float>(GetScreenHeight() * 1.75);
	}
}
