#pragma once

#include <vector>
#include <functional>
#include <optional>

#include "Snake.h"
#include "MapHolder.h"

class GameEngine
{
public:
	GameEngine();

	// starts the main cycle of game: movement and other things
	bool Start();

	// registers new actions of game behavior
	void RegisterNewAction(std::function<bool(std::unique_ptr<MapHolder> & mapHolder)> && func);

private:
	// invokes registered actions one by one
	bool InvokeActions();

	// creates new thread for key press tracking; returns new direction
	std::optional<MovementDirection> GetNewDirection();

private:
	std::vector<std::function<bool(std::unique_ptr<MapHolder> &)>> m_actions;
	std::unique_ptr<MapHolder> m_map;
};

