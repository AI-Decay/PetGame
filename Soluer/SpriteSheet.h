#pragma once

#include <wincodec.h>
#include "Graphics.h"

#pragma comment(lib, "windowscodecs.lib")

class SpriteSheet
{
private:
	std::shared_ptr<Graphics> gfx;
	ID2D1Bitmap* bmp;
	int spriteWidth;
	int spriteHeight;
	int spriteAccross;

public:
	SpriteSheet(const wchar_t* filename, std::shared_ptr<Graphics> graphics);
	SpriteSheet(const wchar_t* filename, std::shared_ptr<Graphics> graphics, int spriteWidth, int spriteHeight);
	~SpriteSheet();

	void Draw();
	void Draw(int index, int x, int y);
};