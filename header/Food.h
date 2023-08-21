#pragma once

#include "Object2D.h"

// snake's food to grow in size
class Food : public Object2D
{
	using base_t = Object2D;

public:
	virtual ObjectType GetType() const override;

	Food(int x, int y, int value = 1);

	int GetFoodValue() const;

private:
	int m_foodValue;
};
