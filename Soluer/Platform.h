#pragma once
struct Platform
{
	float r;
	float g;
	float b;
	float a;
	float x1, y1;
	float x2, y2;
	bool move;

	Platform(float x1, float y1, float x2, float y2, bool move = false,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f)
		: x1(x1), y1(y1), x2(x2), y2(y2), move(move), r(r), g(g), b(b), a(a) {}

	void SetColor(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Move(float max, float min)
	{
		if (move)
		{
			y1 += 2.0f;
			y2 += 2.0f;
			if (y1 > max)
				move = false;
		}
		else
		{
			y1 -= 2.0f;
			y2 -= 2.0f;
			if (y1 < min)
				move = true;
		}
	}
};