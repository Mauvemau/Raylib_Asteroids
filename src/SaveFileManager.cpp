#include "SaveFileManager.h"

#include "raylib.h"

#include <iostream>

using namespace std;

namespace Saves {

	const string folder = "saves";

	const char* GetPath(string name);

	// --

	const char* GetPath(string name) {
		return (folder + "/" + name + ".json").c_str;
	}

	// Global
	const char* ReadFile(string name) {
		const char* value;
		value = LoadFileText(GetPath(name));
		return value;
	}

	void WriteFile(string name, string value) {
		SaveFileText(GetPath(name), value.c_str);
	}
}