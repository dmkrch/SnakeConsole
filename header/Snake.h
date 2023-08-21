#pragma once

#include <vector>
#include <functional>

#include "Object2D.h"

// direction of objects' movement; value is pared with arrow's ascii code on keyboard
enum class MovementDirection
{
	Up = 119, // w small
	Down = 115,
	Right = 100,
	Left = 97,
	Nothing = 0,
};

// snake part of body (head as well)
class SnakeCell : public Object2D
{
	using Object2D::Object2D;

public:
	virtual ObjectType GetType() const override;
};

// snake object
class Snake
{
public:
	Snake();

	// do func to every snake cell incl. head
	void ForEachCell(const std::function<void(const SnakeCell &)> & func) const;

	// move snake into m_direction
	void Move();

	// sets head coords to x, y
	void GetHeadCoords(int & x, int & y) const;

	// check if head has same coords as one of body cell
	bool IsHeadHitsBody() const;

	// eat food with value (amount of food)
	void EatFood(int val);

	void SetDirection(const MovementDirection& direction);
	MovementDirection GetDirection() const;

	int GetSize() const;

private:
	// snake head and it's body; snake's head is m_cells[0]
	std::vector<SnakeCell> m_cells;

	// current snake's direction
	MovementDirection m_direction;
};

