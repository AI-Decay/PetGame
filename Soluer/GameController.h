#pragma once
#include "GameLevel.h"
#include "Graphics.h"

class GameController
{
private:
	GameController() {};
	~GameController() {};
	static std::shared_ptr<GameLevel> currentLevel;
public:
	static void Init();
	static bool Loading;
	static void LoadInitialLevel(std::shared_ptr<GameLevel> level);
	static void SwitchLevel(std::shared_ptr<GameLevel> level);
	static void Render();
	static void Update();
	static void Move(float x, float y);
	static void Jump();
	static void Shot();
};