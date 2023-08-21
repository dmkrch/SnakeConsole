#include "../header/Snake.h"

Snake::Snake()
{
	// head of snake
	m_cells.emplace_back(0, 0);
}

void Snake::ForEachCellInclHead(std::function<void(const SnakeCell &)> func)
{
	for (const auto & cell : m_cells)
		func(cell);
}

void Snake::Move(const MovementDirection & direction)
{
	// When snake moves, head moves to new direction. Each previous body cell transforms to next body cell coordinates

	// calculate new coords of head
	int newX = m_cells[0].GetX();
	int newY = m_cells[0].GetY();

	switch(direction)
	{
	case MovementDirection::Up:
		--newY;
		break;
	case MovementDirection::Down:
		++newY;
		break;
	case MovementDirection::Right:
		++newX;
		break;
	case MovementDirection::Left:
		--newX;
		break;
	default:
		break;
	}

	int tempX = -1;
	int tempY = -1;

	for (auto & snakeCell : m_cells)
	{
		tempX = snakeCell.GetX();
		tempY = snakeCell.GetY();

		snakeCell.SetX(newX);
		snakeCell.SetY(newY);

		newX = tempX;
		newY = tempY;
	}
}

ObjectType SnakeCell::GetType() const
{
	return ObjectType::SnakeCell;
}