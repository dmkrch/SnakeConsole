#include "../header/Food.h"
#include "Food.h"

ObjectType Food::GetType() const
{
    return ObjectType::Food;
}

Food::Food(int x, int y, int value /* = 1*/)
    : base_t(x, y)
    , m_foodValue(value)
{

}

int Food::GetFoodValue() const
{
    return m_foodValue;
}
