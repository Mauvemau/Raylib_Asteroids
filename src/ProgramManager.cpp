#include "raylib.h"

#include "ProgramManager.h"
#include "Menu/MainMenu.h"
#include "Menu/Settings.h"
#include "Menu/GameOverMenu.h"
#include "Menu/Credits.h"
#include "Game/Game.h"
#include "AssetLoader.h" // Para cargar los assets.
#include "Utils.h"

#include <iostream>

ProgramStatus programStatus; // El estado actual del juego.
bool gameShouldClose; // Para salir del game loop.

const int screenWidth = 1024;
const int screenHeight = 768;

static void InitRespectiveStatus(ProgramStatus status);
static void CloseProgram();
static void AdjustResolution();
static void UpdateProgram();
static void InitProgram();

// --

void InitRespectiveStatus(ProgramStatus status) {
	switch (status)
	{
	case ProgramStatus::MAINMENU:
		MainMenu::Init();
		break;
	case ProgramStatus::INGAME:
		Game::Init();
		break;
	case ProgramStatus::GAMEOVER:
		GameOver::Init();
		break;
	case ProgramStatus::CREDITS:
		Credits::Init();
		break;
	case ProgramStatus::SETTINGS:
		Settings::Init();
		break;
	default:
		std::cout << "Invalid program Status! [ProgramManager.cpp - InitRespectiveStatus()]\n";
		break;
	}
}

void CloseProgram() {
	Assets::Unload();
	CloseWindow();
}

void AdjustResolution(){
	if(IsWindowResized()) {
		switch (programStatus)
		{
			case ProgramStatus::MAINMENU:
				MainMenu::AdjustToRes();
				break;
			case ProgramStatus::INGAME:
				Game::AdjustToRes();
				break;
			case ProgramStatus::GAMEOVER:
				GameOver::AdjustToRes();
				break;
			case ProgramStatus::CREDITS:
				Credits::AdjustToRes();
				break;
			case ProgramStatus::SETTINGS:
				Settings::AdjustToRes();
				break;
			default:
				std::cout << "Invalid program Status! [ProgramManager.cpp - UpdateProgram()]\n";
				break;
		}
		Utils::AdjustLastFrameSize(GetScreenWidth(), GetScreenHeight());
	}
}

void UpdateProgram() {
	while (!WindowShouldClose() && !gameShouldClose) {
		switch (programStatus)
		{
		case ProgramStatus::MAINMENU:
			MainMenu::Update();
			break;
		case ProgramStatus::INGAME:
			Game::Update();
			break;
		case ProgramStatus::GAMEOVER:
			GameOver::Update();
			break;
		case ProgramStatus::CREDITS:
			Credits::Update();
			break;
		case ProgramStatus::SETTINGS:
			Settings::Update();
			break;
		default:
			std::cout << "Invalid program Status! [ProgramManager.cpp - UpdateProgram()]\n";
			break;
		}
		AdjustResolution();
	}
}

void InitProgram() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, "Astray");
	SetWindowMinSize(640, 360);
	SetExitKey(KEY_NULL); // No queremos que la ventana se cierre con escape.
	Assets::Init(); // Cargamos los assets.
	Settings::InitSettings(); // Se inicializan las settings default cuando se ejecuta el programa.
	SetProgramStatus(ProgramStatus::MAINMENU);
	Utils::AdjustLastFrameSize(GetScreenWidth(), GetScreenHeight());
}

// Global

void SetGameShouldClose(bool value) {
	gameShouldClose = value;
}

void SetProgramStatus(ProgramStatus status) {
	InitRespectiveStatus(status);
	programStatus = status;
}

void StartProgram() {
	InitProgram();
	UpdateProgram();
	CloseProgram();
}
