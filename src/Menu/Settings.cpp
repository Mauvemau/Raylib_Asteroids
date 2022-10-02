#include "Settings.h"
#include "Button.h"
#include "ProgramManager.h"

#include "raylib.h"

#include <iostream>

namespace Settings {
	const int amountButtons = (int)Options::COUNT;
	Button buttons[amountButtons];

	int currentResolution;
	bool fullscreen;

	void CenterWindow();
	void MyToggleFullscreen();
	void SetResolution(Resolution res);
	void ChangeResolution(Resolutions id);
	const char* GetResolutionName(Resolutions id);
	Resolution GetResolutionValue(Resolutions id);
	const char* GetButtonName(Options option);
	void SelectOption(Options option);
	void InitButtons(); // Inicializa los botones.
	void Draw();

	// --

	
	void CenterWindow() {
		int monitor = GetCurrentMonitor();
		Resolution monitorRes;
		monitorRes.width = GetMonitorWidth(monitor);
		monitorRes.height = GetMonitorHeight(monitor);
		Resolution windowRes = GetResolutionValue((Resolutions)currentResolution);
		SetWindowPosition((monitorRes.width * .5) - (windowRes.width * .5), (monitorRes.height * .5) - (windowRes.height * .5));
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
			buttons[(int)Options::RESOLUTION].col = DARKGRAY;
		}
		ToggleFullscreen();
		if(!fullscreen) {
			SetResolution(GetResolutionValue((Resolutions)currentResolution)); // Restaurar la resolucion a la actual si se sale de pantalla completa.
			CenterWindow();
			Init();
			buttons[(int)Options::RESOLUTION].col = RAYWHITE;
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
				if (currentResolution > (int)Resolutions::r1600x900) { // Rotar si pasa el maximo.
					currentResolution = 0;
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
		float spacing = 0;
		for (int i = 0; i < amountButtons; i++) {
			switch ((Options)i)
			{
			case Settings::Options::RESOLUTION:
				buttons[i] = Buttons::Create(i,
					Vector2{ (float)(GetScreenWidth() * .25), (float)(GetScreenHeight() * .5) },
					Vector2{ (float)(GetScreenWidth() * .3), (float)(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			case Settings::Options::FULLSCREEN:
				buttons[i] = Buttons::Create(i,
					Vector2{ (float)(GetScreenWidth() * .75), (float)(GetScreenHeight() * .5) },
					Vector2{ (float)(GetScreenWidth() * .3), (float)(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			case Settings::Options::RETURNTOMENU:
				buttons[i] = Buttons::Create(i,
					Vector2{ (float)(GetScreenWidth() * .5), (float)(GetScreenHeight() * .85) },
					Vector2{ (float)(GetScreenWidth() * .35), (float)(GetScreenHeight() * .1) },
					GetButtonName((Options)i));
				break;
			default:
				std::cout << "Invalid Button! [Settings.cpp - InitButtons]\n";
				break;
			}
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

		if(IsKeyPressed(KEY_ESCAPE))
			SetProgramStatus(ProgramStatus::MAINMENU);

		Draw();
	}

	void InitSettings() {
		currentResolution = (int)Resolutions::r1024x768;
		fullscreen = false;
	}

	void Init() {
		InitButtons();
	}
}