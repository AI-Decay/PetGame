#pragma once
#include "SpriteSheet.h"
class Enemy
{
public:
	Enemy(std::unique_ptr<SpriteSheet> sprites, float x, float y, float speed, int hp, int damage)
		:sprites(move(sprites)), xPosition(x), yPosition(y), speed(speed), hp(hp), damage(damage) {}
	int hp;
	int damage;
	float xPosition;
	float yPosition;
	float speed;
	int frame = 0;
	bool loadEnemy = false;
	bool alive = true;
	std::unique_ptr<SpriteSheet> sprites;
	void Move(float max, float min)
	{
		yPosition += speed;
	if (yPosition > max)
		speed = -speed;
	if (yPosition < min)
		speed = -speed;
	}
};