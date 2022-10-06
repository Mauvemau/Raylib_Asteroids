#pragma once

/*
Extension de PauseMenu
*/

namespace Upgrades {
	enum class Options {
		HEALTH,
		FIRERATE,
		BULLETSIZE,
		BULLETRANGE,
		BULLETSPEED,
		RETURN,
		COUNT
	};

	void Draw();
	void Update();
	void Init();
}