#include "raylib.h"

#include "ProgramManager.h"
#include "Game/Game.h"

const int screenWidth = 800;
const int screenHeight = 450;

void CloseProgram();
void UpdateProgram();
void InitProgram();

void CloseProgram() {
	CloseWindow();
}

void UpdateProgram() {
	while (!WindowShouldClose()) {
		Game::Update();
	}
}

void InitProgram() {
	InitWindow(screenWidth, screenHeight, "Raylib Asteroids!");
	Game::Init();
}

void StartProgram() {
	InitProgram();
	UpdateProgram();
	CloseProgram();
}