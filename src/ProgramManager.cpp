#include "raylib.h"

#include "ProgramManager.h"
#include "Game/Game.h"

const int screenWidth = 1024;
const int screenHeight = 768;

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
	InitWindow(screenWidth, screenHeight, "Raylib Asteroids");
	SetTargetFPS(200);
	Game::Init();
}

void StartProgram() {
	InitProgram();
	UpdateProgram();
	CloseProgram();
}