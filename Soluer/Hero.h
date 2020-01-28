#pragma once
#include "SpriteSheet.h"

class Hero
{
public:
	int hp;
	int damage;
	float xPosition;
	float yPosition;
	float speed;
	int frame = 0;
	bool alive = true;
public:
	std::unique_ptr<SpriteSheet> sprites;
	Hero(std::unique_ptr<SpriteSheet> sprites, float x, float y, float speed, int hp, int damage)
		:sprites(move(sprites)), xPosition(x), yPosition(y), speed(speed), hp(hp), damage(damage) {}
	~Hero() {}
};