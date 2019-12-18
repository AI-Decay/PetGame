#include "GameController.h"


std::shared_ptr<GameLevel> GameController::currentLevel;
bool GameController::Loading;

void GameController::LoadInitialLevel(std::shared_ptr<GameLevel> level)
{
	Loading = true;
	currentLevel = level;
	currentLevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(std::shared_ptr<GameLevel> level)
{
	Loading = true;
	currentLevel->Unload();
	level->Load();
	currentLevel = level;
	Loading = false;
}

void GameController::Render()
{
	if (Loading) return;
	currentLevel->Render();
}

void GameController::Update()
{
	if (Loading) return;
	currentLevel->Update();
}

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

void GameController::Move(float x, float y)
{
	currentLevel->Move(x, y);
}

void GameController::Jump()
{
	currentLevel->EnableJump();
}

void GameController::Shot()
{
	currentLevel->Shot();
}