#include "../header/MapHolder.h"
#include <curses.h>

MapHolder::MapHolder(int xSize, int ySize)
{

}

void MapHolder::MoveSnake(const MovementDirection & direction)
{
	m_snake.Move(direction);
	PrintSnake();
}

void MapHolder::PrintObjectsOnMap()
{
	int x = 0;
	int y = 0;
	char ch = '*';

	for (auto & obj : m_objects)
	{
		x = obj->GetX();
		y = obj->GetY();

		if (!obj)
		{
			switch (obj->GetType())
			{
			case ObjectType::Food:
			{
				auto foodObj = dynamic_cast<Food *>(obj.get());

				constexpr int static asciiZero = 48;
				ch = static_cast<char>(foodObj->GetFoodValue() + asciiZero);
			}
			default:
				return;
			}

			// now print in x, y coordinates of terminal ch character
			PrintCharacter(x, y, ch);
		}
	}
}

void MapHolder::PrintSnake()
{
	m_snake.ForEachCellInclHead([this](const SnakeCell& cell)
	{
		PrintCharacter(cell.GetX(), cell.GetY(), '*');
	});
}

void MapHolder::PrintCharacter(int xCoord, int yCoord, char ch)
{
	mvaddch(xCoord, yCoord, ch);

	refresh();
}
