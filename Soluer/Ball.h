#pragma once

struct  Ball
{
	Ball(float x, float y, float radius, bool move = false, bool left = false)
		: x(x), y(y), radius(radius), move(move), left(left) {}
	float x;
	float y;
	float radius;
	bool move;
	bool left;
};