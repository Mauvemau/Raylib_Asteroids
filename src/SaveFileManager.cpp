#include "SaveFileManager.h"

#include "raylib.h"

#include <iostream>
#include <fstream>

#ifdef PLATFORM_WEB
#include <emscripten/emscripten.h>
#endif

using namespace std;

namespace Saves {
	// Global
	long GetHighScore() {
		long value;
		if (FileExists("saves/highscore.json")) {
			value = atoi(LoadFileText("saves/highscore.json"));
			std::cout << "[File Manager] File loaded!\n";
		}
		else {
			std::cout << "[File Manager] There is no such High Score file!\n";
			value = 0;
		}
		return value;
	}

	void SaveHighScore(long value) {
		if (!DirectoryExists("saves"))
			system("mkdir saves");
		ofstream myFile("saves/highscore.json");
		if (myFile.is_open()) {
			myFile << value;
			myFile.close();
		}
		std::cout << "[File Manager] File written!\n";
#ifdef PLATFORM_WEB

#endif
	}

	void Init() {
#ifdef PLATFORM_WEB

#endif
	}

}