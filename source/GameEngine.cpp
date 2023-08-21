#include "../header/GameEngine.h"

#include <thread>
#include <optional>
#include <conio.h>

bool GameEngine::InvokeActions()
{
	for (const auto & action : m_actions)
	{
		if (!action(m_map))
			false;
	}

	return true;
}

void GameEngine::StartSettingDirection(bool isGameContinues)
{
	auto IsArrowWasPressed = [](int keyCode)
	{
		return keyCode == static_cast<int>(MovementDirection::Up) ||
			keyCode == static_cast<int>(MovementDirection::Down) ||
			keyCode == static_cast<int>(MovementDirection::Left) ||
			keyCode == static_cast<int>(MovementDirection::Right);
	};

	auto getKeyPressed = [&, this]()
	{
		int keyPressedCode = 0;

		while (isGameContinues)
		{
			// get the code of pressed key
			keyPressedCode = _getch();

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
	};

	std::thread keyThread(getKeyPressed);
}

bool GameEngine::Start()
{
	bool isGameContinues = true;

	StartSettingDirection(isGameContinues);

	while (isGameContinues)
	{
		// 1. Make a movement of snake
		m_map->MoveSnake();

		// 2. Make the actions: check for food, check for head hitting the body, etc (implemented in future - checking for enemies)
		if (!InvokeActions())
		{
			isGameContinues = false;
			break;
		}

		// set delay 0.5 seconds to main thread
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
	// snake can eat food
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		map->SnakeEatFoodAction();
		return true;
	});

	// snake head can't touch it's body
	RegisterNewAction([](std::unique_ptr<MapHolder>& map) -> bool
	{
		return map->IsSnakeHeadHitsBody() ? false : true;
	});
}