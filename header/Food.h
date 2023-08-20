#pragma once

#include "Object2D.h"

class Food : public Object2D
{
	using Object2D::Object2D;

public:
	virtual ObjectType GetType() const override;
};
