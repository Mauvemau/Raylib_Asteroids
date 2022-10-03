#include "raylib.h"

#include "ProgramManager.h"
#include "Menu/MainMenu.h"
#include "Menu/Settings.h"
#include "Menu/GameOverMenu.h"
#include "Menu/Credits.h"
#include "Game/Game.h"
#include "AssetLoader.h" // Para cargar los assets.

#include <iostream>

ProgramStatus programStatus; // El estado actual del juego.
bool gameShouldClose; // Para salir del game loop.

const int screenWidth = 1024;
const int screenHeight = 768;

void InitRespectiveStatus(ProgramStatus status);

void CloseProgram();
void UpdateProgram();
void InitProgram();

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
	}
}

void InitProgram() {
	InitWindow(screenWidth, screenHeight, "Raylib Asteroids");
	SetExitKey(KEY_NULL); // No queremos que la ventana se cierre con escape.
	Assets::Init(); // Cargamos los assets.
	Settings::InitSettings(); // Se inicializan las settings default cuando se ejecuta el programa.
	SetProgramStatus(ProgramStatus::MAINMENU);
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