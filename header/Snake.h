#pragma once

#include <vector>
#include <functional>

#include "Object2D.h"

enum class MovementDirection
{
	Up,
	Down,
	Right,
	Left,
	Nothing,
};

class SnakeCell : public Object2D
{
	using Object2D::Object2D;

public:
	virtual ObjectType GetType() const override;
};

class Snake
{
public:
	Snake();

	void ForEachCellInclHead(std::function<void(const SnakeCell&)> func);

	void Move(const MovementDirection & direction);

private:
	// snake head and it's body; snake's head is m_cells[0]
	std::vector<SnakeCell> m_cells;
};

