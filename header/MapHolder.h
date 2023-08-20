#pragma once

#include <vector>
#include <memory>

#include "Object2D.h"
#include "Snake.h"
#include "Food.h"

class MapHolder
{
public:
	MapHolder(int xSize, int ySize);

	// moves the snake due to direction
	void MoveSnake(const MovementDirection & direction);

	void PrintObjectsOnMap();
	void PrintSnake();

private:
	void PrintCharacter(int xCoord, int yCoord, char ch);

private:
	Snake m_snake;

	std::vector<std::unique_ptr<Object2D>> m_objects;
};

