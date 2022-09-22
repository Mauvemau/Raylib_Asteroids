#pragma once
/*
Maneja los loops y distintas pantallas del juego.
*/

enum class ProgramStatus {
	MAINMENU,
	INGAME
};

void SetGameShouldClose(bool value);
void SetProgramStatus(ProgramStatus status);
void StartProgram();