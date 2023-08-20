#include "GameEngine.h"

#include <thread>
#include <optional>

bool GameEngine::InvokeActions()
{
	for (const auto & action : m_actions)
	{
		if (!action(m_map))
			false;
	}

	return true;
}

std::optional<MovementDirection> GameEngine::GetNewDirection()
{
	std::optional<MovementDirection> newDirection;

	auto waitForKeyPress = []()
	{

	};

	return newDirection;
}

bool GameEngine::Start()
{
	bool isGameContinues = true;

	MovementDirection direction = MovementDirection::Nothing;

	while (isGameContinues)
	{
		// 1. Make a movement of snake
		m_map->MoveSnake(direction);

		// 2. Make the actions
		if (!InvokeActions())
			isGameContinues = false;
		
		// 3. If ok - get new direction
		if (auto newDirection = GetNewDirection())
			direction = newDirection.value();
	}

	return isGameContinues;
}

void GameEngine::RegisterNewAction(std::function<bool(std::unique_ptr<MapHolder> &)> && func)
{
	m_actions.emplace_back(func);
}

GameEngine::GameEngine()
	: m_map(std::make_unique<MapHolder>(15, 15))
{
	// init
}