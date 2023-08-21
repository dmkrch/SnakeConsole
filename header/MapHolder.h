#pragma once

#include <vector>
#include <memory>

#include "Object2D.h"
#include "Snake.h"
#include "Food.h"

// stores every object in game
class MapHolder
{
public:
	MapHolder(int xSize, int ySize);

	// moves the snake due to direction
	void MoveSnake();

	// prints objects on map
	void PrintObjectsOnMap();

	// checks for food and eat if necessary
	void SnakeEatFoodAction();

	// checks if snake head hits it's body
	bool IsSnakeHeadHitsBody();

	void SetSnakeDirection(const MovementDirection & direction);
	MovementDirection GetSnakeDirection() const;

	int GetSnakeSize() const;

private:
	void Init();

	void PrintCharacter(int xCoord, int yCoord, char ch);

private:
	std::vector<std::unique_ptr<Object2D>> m_othersObjects;
	Snake m_snake;
	int m_xSize;
	int m_ySize;
};

