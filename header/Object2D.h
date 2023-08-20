#pragma once

enum class ObjectType
{
	SnakeCell,
	Snake,
	Food,
};

class Object2D
{
public:
	Object2D(int x, int y)
		: m_x(x)
		, m_y(y)
	{}

	int GetX() const;
	int GetY() const;

	void SetX(int x);
	void SetY(int y);

	virtual ObjectType GetType() const = 0;

private:
	int m_x;
	int m_y;
};
