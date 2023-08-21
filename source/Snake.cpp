#include "../header/Snake.h"

#include <algorithm>
#include "Snake.h"

Snake::Snake()
	: m_direction(MovementDirection::Right)
{
	// create head of snake
	m_cells.emplace_back(0, 0);
}

void Snake::ForEachCell(const std::function<void(const SnakeCell &)> & func) const
{
	for (const auto & cell : m_cells)
		func(cell);
}

void Snake::Move()
{
	if (m_direction == MovementDirection::Nothing)
		return;

	// When snake moves, head moves to new direction. Each previous body cell transforms to next body cell coordinates

	// calculate new coords of head
	int newX = m_cells[0].GetX();
	int newY = m_cells[0].GetY();

	switch(m_direction)
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

void Snake::GetHeadCoords(int& x, int& y) const
{
	x = m_cells[0].GetX();
	y = m_cells[0].GetY();
}

bool Snake::IsHeadHitsBody() const
{
	if (m_cells.size() < static_cast<size_t>(2))
		return false;

	int headX = m_cells[0].GetX();
	int headY = m_cells[0].GetY();

	return std::any_of(m_cells.begin() + 1, m_cells.end(), [&headX, &headY](const SnakeCell & cell) 
	{
		return (cell.GetX() == headX) && (cell.GetY() == headY);
	});
}

void Snake::EatFood(int val)
{
	int newX = 0;
	int newY = 0;

	for (int i = 0; i < val; ++i)
	{
		newX = m_cells.back().GetX();
		newY = m_cells.back().GetY();

		// insert new body cell to opposite side of current direction
		switch (m_direction)
		{
		case MovementDirection::Down:
			--newY;
			break;
		case MovementDirection::Up:
			++newY;
			break;
		case MovementDirection::Right:
			--newX;
			break;
		case MovementDirection::Left:
			++newX;
			break;
		default:
			return;
		}

		m_cells.emplace_back(newX, newY);
	}
}

void Snake::SetDirection(const MovementDirection & direction)
{
	m_direction = direction;
}

MovementDirection Snake::GetDirection() const
{
	return m_direction;
}

int Snake::GetSize() const
{
	return m_cells.size();
}

ObjectType SnakeCell::GetType() const
{
	return ObjectType::SnakeCell;
}