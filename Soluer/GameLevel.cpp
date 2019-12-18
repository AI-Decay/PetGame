#include "GameLevel.h"

std::shared_ptr<Graphics> GameLevel::gfx;

void GameLevel::Init(std::shared_ptr<Graphics> graphics) 
{
	gfx = graphics;
}