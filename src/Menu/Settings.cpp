#include "Settings.h"
#include "Button.h"
#include "ProgramManager.h"
#include "Utils.h" // Para el texto centrado.

#include "raylib.h"

#include <iostream>

namespace Settings {
	const int amountButtons = static_cast<int>(Options::COUNT);
	Button buttons[amountButtons];

	int currentResolution;
	bool fullscreen;

	bool IsResBiggerThanMonitor(Resolution res);
	void CenterWindow();
	void MyToggleFullscreen();
	void SetResolution(Resolution res);
	void ChangeResolution(Resolutions id);
	const char* GetResolutionName(Resolutions id);
	Resolution GetResolutionValue(Resolutions id);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons();
	void DrawHeader(const char* text, Options option);
	void DrawText();
	void Draw();

	// --

	bool IsResBiggerThanMonitor(Resolution res) {
		int monitor = GetCurrentMonitor();
		return (res.width > GetMonitorWidth(monitor) || res.height > GetMonitorHeight(monitor));
	}

	void CenterWindow() {
		int monitor = GetCurrentMonitor();
		Resolution monitorRes;
		monitorRes.width = GetMonitorWidth(monitor);
		monitorRes.height = GetMonitorHeight(monitor);
		Resolution windowRes = GetResolutionValue((Resolutions)currentResolution);
		SetWindowPosition(static_cast<int>((monitorRes.width * .5) - (windowRes.width * .5)), static_cast<int>((monitorRes.height * .5) - (windowRes.height * .5)));
	}

	void MyToggleFullscreen() {
		fullscreen = !fullscreen;
		if (fullscreen) {
			int monitor = GetCurrentMonitor();
			Resolution res;
			res.width = GetMonitorWidth(monitor);
			res.height = GetMonitorHeight(monitor);
			SetResolution(res);
			Init();
		}
		ToggleFullscreen();
		if (!fullscreen) {
			SetResolution(GetResolutionValue((Resolutions)currentResolution)); // Restaurar la resolucion a la actual si se sale de pantalla completa.
			CenterWindow();
			Init();
		}
	}

	void SetResolution(Resolution res) {
		SetWindowSize(res.width, res.height);
		std::cout << "Resolution set to: " << res.width << "x" << res.height << "!\n";
	}

	void ChangeResolution(Resolutions id) {
		SetResolution(GetResolutionValue((Resolutions)id));
		CenterWindow();
		Init();
	}

	const char* GetResolutionName(Resolutions id) {
		const char* name;
		switch (id)
		{
		case Settings::Resolutions::r640x480:
			name = "640x480";
			break;
		case Settings::Resolutions::r800x600:
			name = "800x600";
			break;
		case Settings::Resolutions::r1024x768:
			name = "1024x768";
			break;
		case Settings::Resolutions::r1152x864:
			name = "1152x864";
			break;
		case Settings::Resolutions::r1280x720:
			name = "1280x720";
			break;
		case Settings::Resolutions::r1280x1024:
			name = "1280x1024";
			break;
		case Settings::Resolutions::r1360x768:
			name = "1360x768";
			break;
		case Settings::Resolutions::r1600x900:
			name = "1600x900";
			break;
		default:
			name = "Error";
			std::cout << "Invalid Resolution id! [Settings.cpp - GetResolutionName]\n";
			break;
		}
		return name;
	}

	Resolution GetResolutionValue(Resolutions id) {
		Resolution res;
		switch (id)
		{
		case Settings::Resolutions::r640x480:
			res = { 640, 480 };
			break;
		case Settings::Resolutions::r800x600:
			res = { 800, 600 };
			break;
		case Settings::Resolutions::r1024x768:
			res = { 1024, 768 };
			break;
		case Settings::Resolutions::r1152x864:
			res = { 1152, 864 };
			break;
		case Settings::Resolutions::r1280x720:
			res = { 1280, 720 };
			break;
		case Settings::Resolutions::r1280x1024:
			res = { 1280, 1024 };
			break;
		case Settings::Resolutions::r1360x768:
			res = { 1360, 768 };
			break;
		case Settings::Resolutions::r1600x900:
			res = { 1600, 900 };
			break;
		default:
			std::cout << "Invalid Resolution id! [Settings.cpp - GetResolutionValue]\n";
			res = { 1024, 768 };
			break;
		}
		return res;
	}

	const char* GetButtonName(Options option) {
		switch (option)
		{
		case Settings::Options::RESOLUTION:
			return GetResolutionName((Resolutions)currentResolution);
			break;
		case Settings::Options::FULLSCREEN:
			return (fullscreen ? "Windowed" : "Fullscreen");
			break;
		case Settings::Options::RETURNTOMENU:
			return "Return To Menu";
			break;
		default:
			std::cout << "Invalid Option! [Settings.cpp - GetButtonName]\n";
			return "Error";
			break;
		}
	}

	void SelectOption(Options option) {
		switch (option)
		{
		case Settings::Options::RESOLUTION:
			if (!fullscreen) { // Solo permitir cambiar resolucion si el juego se encuentra en modo ventana.
				currentResolution++;
				if (currentResolution > static_cast<int>(Resolutions::r1600x900)) { // Rotar si pasa el maximo.
					currentResolution = 0;
				}
				if (currentResolution > static_cast<int>(Resolutions::r1024x768)) { // Si es mayor que el default.
					if (IsResBiggerThanMonitor(GetResolutionValue((Resolutions)currentResolution))) // Si la resolucion es mas grande que el monitor.
						currentResolution = 0; // Rotar
				}
				ChangeResolution((Resolutions)currentResolution);
			}
			break;
		case Settings::Options::FULLSCREEN:
			MyToggleFullscreen();
			break;
		case Settings::Options::RETURNTOMENU:
			SetProgramStatus(ProgramStatus::MAINMENU);
			break;
		default:
			std::cout << "Invalid Option! [Settings.cpp - SelectOption]\n";
			break;
		}
	}

	void InitButtons() {
		for (int i = 0; i < amountButtons; i++) {
			switch ((Options)i)
			{
			case Settings::Options::RESOLUTION:
				buttons[i] = Buttons::Create(i,
					Vector2{ static_cast<float>(GetScreenWidth() * .25), static_cast<float>(GetScreenHeight() * .5) },
					Vector2{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			case Settings::Options::FULLSCREEN:
				buttons[i] = Buttons::Create(i,
					Vector2{ static_cast<float>(GetScreenWidth() * .75), static_cast<float>(GetScreenHeight() * .5) },
					Vector2{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			case Settings::Options::RETURNTOMENU:
				buttons[i] = Buttons::Create(i,
					Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .85) },
					Vector2{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			default:
				std::cout << "Invalid Button! [Settings.cpp - InitButtons]\n";
				break;
			}
		}
	}

	void DrawHeader(const char* text, Options option) {
		Vector2 pos = { (buttons[static_cast<int>(option)].pos.x + static_cast<float>(buttons[static_cast<int>(option)].size.x * .5)),
						(buttons[static_cast<int>(option)].pos.y - static_cast<float>(buttons[static_cast<int>(option)].size.x * .1)) };
		Utils::DrawCenteredText(text, pos, static_cast<int>(GetScreenHeight() * .03f), RAYWHITE);
	}

	void DrawText() {
		Utils::DrawCenteredText("Settings",
			{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .2) },
			static_cast<int>(GetScreenHeight() * .07f), ORANGE);

		DrawHeader("Click to switch resolution", Options::RESOLUTION);
		DrawHeader("Fullscreen/Windowed", Options::FULLSCREEN);
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
		if (!fullscreen) {
			buttons[static_cast<int>(Options::RESOLUTION)].col = RAYWHITE;
		}
		else {
			buttons[static_cast<int>(Options::RESOLUTION)].col = DARKGRAY;
		}

		if (IsKeyPressed(KEY_ESCAPE))
			SetProgramStatus(ProgramStatus::MAINMENU);

		Draw();
	}

	void InitSettings() {
		currentResolution = static_cast<int>(Resolutions::r1024x768);
		fullscreen = false;
	}

	void AdjustToRes() {
		InitButtons();
	}

	void Init() {
		AdjustToRes();
	}
}