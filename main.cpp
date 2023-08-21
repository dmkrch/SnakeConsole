#include <iostream>

#include "./header/GameEngine.h"

int main()
{	
	GameEngine engine;

	return engine.Start() ? 0 : 1 ;
}