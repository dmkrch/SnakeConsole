#include <iostream>

#include "./header/GameEngine.h"

int main()
{	
	GameEngine engine;

	// snake head can't touch it's body
	engine.RegisterNewAction([](std::unique_ptr<MapHolder> & map) -> bool
	{
		return true;
	});

	// snake can eat food
	engine.RegisterNewAction([](std::unique_ptr<MapHolder> & map) -> bool
	{
		return true;
	});

	return engine.Start() ? 0 : 1 ;
}