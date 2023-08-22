#include "../header/MapHolder.h"

#include <algorithm>
#include <curses.h>
#include "MapHolder.h"

MapHolder::MapHolder(int xSize, int ySize)
	: m_xSize(xSize)
	, m_ySize(ySize)
{
	Init();
}

void MapHolder::MoveSnake()
{
	m_snake.Move();
}

void MapHolder::PrintObjectsOnMap()
{
	// clear screen
	clear();

	// print snake
	m_snake.ForEachCell([this](const SnakeCell & cell)
	{
		PrintCharacter(cell.GetX(), cell.GetY(), 'o');
	});

	// print other objects
	int x = 0;
	int y = 0;
	char ch = '-';

	for (auto & obj : m_othersObjects)
	{
		x = obj->GetX();
		y = obj->GetY();

		if (!obj)
			continue;

		switch (obj->GetType())
		{
		case ObjectType::Food:
		{
			auto foodObj = dynamic_cast<Food *>(obj.get());

			constexpr int static asciiZero = 48;
			ch = static_cast<char>(foodObj->GetFoodValue() + asciiZero);
			break;
		}
		default:
		{
			return;	
		}
		}

		// now print in x, y coordinates of terminal ch character
		PrintCharacter(x, y, ch);
	}
}

void MapHolder::SnakeEatFoodAction()
{
	int x = 0;
	int y = 0;

	m_snake.GetHeadCoords(x, y);

	auto cellIt = std::find_if(m_othersObjects.begin(), m_othersObjects.end(), [&x, &y](const std::unique_ptr<Object2D>& obj)
	{
		if (!obj)
			return false;

		if (obj->GetType() == ObjectType::Food)
			return (x == obj->GetX()) && (y == obj->GetY());

		return false;
	});

	if (cellIt != m_othersObjects.end())
	{
		auto foodObj = dynamic_cast<Food*>(cellIt->get());

		// eat food
		m_snake.EatFood(foodObj->GetFoodValue());

		// delete food from m_objects
		m_othersObjects.erase(cellIt);
	}
}

bool MapHolder::IsSnakeHeadHitsBody()
{
	return m_snake.IsHeadHitsBody();
}

void MapHolder::SetSnakeDirection(const MovementDirection& direction)
{
	m_snake.SetDirection(direction);
}

MovementDirection MapHolder::GetSnakeDirection() const
{
	return m_snake.GetDirection();
}

int MapHolder::GetSnakeSize() const
{
	m_snake.GetSize();
}

void MapHolder::Init()
{
	// add some food to map
	m_othersObjects.emplace_back(std::make_unique<Food>(7, 7));
	m_othersObjects.emplace_back(std::make_unique<Food>(12, 11, 2));
	m_othersObjects.emplace_back(std::make_unique<Food>(3, 7, 3));
	m_othersObjects.emplace_back(std::make_unique<Food>(14, 13, 5));
	m_othersObjects.emplace_back(std::make_unique<Food>(8, 2, 2));
	m_othersObjects.emplace_back(std::make_unique<Food>(3, 11, 1));
	m_othersObjects.emplace_back(std::make_unique<Food>(11, 7, 4));
	m_othersObjects.emplace_back(std::make_unique<Food>(12, 7, 4));
	m_othersObjects.emplace_back(std::make_unique<Food>(13, 7, 4));
	m_othersObjects.emplace_back(std::make_unique<Food>(14, 7, 4));
	m_othersObjects.emplace_back(std::make_unique<Food>(15, 7, 4));

	// todo: add inital enemies to map
}

void MapHolder::PrintCharacter(int xCoord, int yCoord, char ch)
{
	mvaddch(yCoord, xCoord, ch);
	refresh();
}
