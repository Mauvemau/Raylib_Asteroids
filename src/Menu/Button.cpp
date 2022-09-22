#include "Button.h"
#include "Utils.h" // Para dibujar texto centrado.
#include "Game/CollisionManager.h" // Para la colision entre el cursor y el boton.

namespace Buttons {
	void CenterButton(Button& button);
	bool IsCursorInside(Button button);

	void CenterButton(Button& button) {
		button.pos.x -= (button.size.x * .5);
		button.pos.y -= (button.size.y * .5);
	}

	bool IsCursorInside(Button button) {
		return Collisions::Vector2RectCollision(GetMousePosition(), button.pos, button.size);
	}

	void Draw(Button button) {
		if (button.hovered) {
			DrawRectangle(button.pos.x, button.pos.y, button.size.x, button.size.y, button.col);
			Utils::DrawCenteredText(button.text, 
				Vector2{(float)(button.pos.x + (button.size.x * .5)), (float)(button.pos.y + (button.size.y * .5)) }, 
				(button.size.y * .5), BLACK);
		}
		else {
			DrawRectangleLines(button.pos.x, button.pos.y, button.size.x, button.size.y, button.col);
			Utils::DrawCenteredText(button.text,
				Vector2{ (float)(button.pos.x + (button.size.x * .5)), (float)(button.pos.y + (button.size.y * .5)) },
				(button.size.y * .5), button.col);
		}
	}

	bool Update(Button& button) {
		button.hovered = IsCursorInside(button);
		return (IsCursorInside(button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
	}

	Button Create(int id, Vector2 pos, Vector2 size) {
		Button button;
		button.id = id;
		button.pos = pos;
		button.size = size;
		button.col = RAYWHITE;
		button.text = "";
		button.hovered = false;
		CenterButton(button);
		return button;
	}

	Button Create(int id, Vector2 pos, Vector2 size, Color col) {
		Button button;
		button.id = id;
		button.pos = pos;
		button.size = size;
		button.col = col;
		button.text = "";
		button.hovered = false;
		CenterButton(button);
		return button;
	}

	Button Create(int id, Vector2 pos, Vector2 size, const char* text) {
		Button button;
		button.id = id;
		button.pos = pos;
		button.size = size;
		button.col = RAYWHITE;
		button.text = text;
		button.hovered = false;
		CenterButton(button);
		return button;
	}

	Button Create(int id, Vector2 pos, Vector2 size, Color col, const char* text) {
		Button button;
		button.id = id;
		button.pos = pos;
		button.size = size;
		button.col = col;
		button.text = text;
		button.hovered = false;
		CenterButton(button);
		return button;
	}
}