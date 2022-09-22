#pragma once
#include "raylib.h"

struct Button {
	int id;
	Vector2 pos;
	Vector2 size;
	Color col;
	const char* text;
	bool hovered;
};

namespace Buttons {
	void Draw(Button button);
	bool Update(Button& button);
	Button Create(int id, Vector2 pos, Vector2 size); // Creates a text-less white button.
	Button Create(int id, Vector2 pos, Vector2 size, Color col); // Creates a text-less button with custom color.
	Button Create(int id, Vector2 pos, Vector2 size, const char* text); // Creates a white button with text.
	Button Create(int id, Vector2 pos, Vector2 size, Color col, const char* text); // Creates a button with text and custom color.
}