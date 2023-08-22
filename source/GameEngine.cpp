#include "../header/GameEngine.h"

#include <thread>
#include <optional>
#include <curses.h>
#include <math.h>
#include "GameEngine.h"

bool GameEngine::InvokeActions()
{
	for (const auto & action : m_actions)
	{
		if (!action(m_map))
			return false;
	}

	return true;
}

bool GameEngine::UpdateDirection() const
{
	auto IsArrowWasPressed = [](int keyCode)
	{
		return keyCode == static_cast<int>(MovementDirection::Up) ||
			keyCode == static_cast<int>(MovementDirection::Down) ||
			keyCode == static_cast<int>(MovementDirection::Left) ||
			keyCode == static_cast<int>(MovementDirection::Right);
	};

	int keyPressedCode = 0;

	while (m_isGameContinues)
	{
		// get the code of pressed key
		keyPressedCode = getch();

		// if arrow was not pressed - skip
		if (!IsArrowWasPressed(keyPressedCode))
			continue;

		// get current direction; snake can't move to opposite direction
		auto currentDirection = m_map->GetSnakeDirection();

		switch (currentDirection)
		{
		case MovementDirection::Down:
		{
			if (keyPressedCode == static_cast<int>(MovementDirection::Up))
				continue;
			break;
		}
		case MovementDirection::Up:
		{
			if (keyPressedCode == static_cast<int>(MovementDirection::Down))
				continue;
			break;
		}
		case MovementDirection::Right:
		{
			if (keyPressedCode == static_cast<int>(MovementDirection::Left))
				continue;

			break;
		}
		case MovementDirection::Left:
		{
			if (keyPressedCode == static_cast<int>(MovementDirection::Right))
				continue;

			break;
		}
		default:
		{
			continue;
		}
		}

		// set new direction
		m_map->SetSnakeDirection(static_cast<MovementDirection>(keyPressedCode));
	}
}

bool GameEngine::Start()
{	
	std::thread keyThread(&GameEngine::UpdateDirection, this);

	while (m_isGameContinues)
	{
		// Invoke the registered actions
		if (!InvokeActions())
			m_isGameContinues = false;

		// delay is set according to snake size
		std::this_thread::sleep_for(std::chrono::milliseconds(int(500 * pow(0.9, (float)m_map->GetSnakeSize()))));
	}

	keyThread.join();

	return m_isGameContinues;
}

void GameEngine::RegisterNewAction(std::function<bool(std::unique_ptr<MapHolder> &)> && func)
{
	m_actions.emplace_back(func);
}

GameEngine::GameEngine()
	: m_map(std::make_unique<MapHolder>(15, 15))
{
	// setting up ncurses lib's window
	initscr();
	noecho();

	// snake can eat food
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		map->MoveSnake();
		return true;
	});

	// snake can eat food
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		map->SnakeEatFoodAction();
		return true;
	});

	// print all objects
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		map->PrintObjectsOnMap();
		return true;
	});

	// snake head can't touch it's body
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		return map->IsSnakeHeadHitsBody() ? false : true;
	});
}

GameEngine::~GameEngine()
{
	endwin();
}
