#pragma once

/*
Extension de Game
*/

namespace Pause {
	enum class Options {
		RESUME,
		RESTART,
		RETURNTOMENU,
		COUNT
	};

	void Draw(); // Este menu tiene un draw publico, ya que funciona como una extension de Game.h
	void Update();
	void Init();
}