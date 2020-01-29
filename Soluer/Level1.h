#pragma once
#include "GameLevel.h"
#include "Platform.h"
#include "Graphics.h"
#include "GameController.h"
#include "Ball.h"
#include "Enemy.h"
#include "Hero.h"
#include <vector>


class Level1 : public GameLevel
{
	float y = 0.0f;
	float ySpeed = 0.0f;
	int timeJump = 0;
	std::unique_ptr<Enemy> enemy;
	std::unique_ptr<Hero> hero;
	std::vector<Ball> VectorBall;
	int frame = 0;
	std::vector<Platform> VectorPlatform;
public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update() override;
	void Move(float x, float y) override;
	void Jump() override;
	void Shot() override;
};