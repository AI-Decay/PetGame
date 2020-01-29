#pragma once
#include <memory>
#include "Graphics.h"
#include "SpriteSheet.h"
#include "GameTime.h"

class GameLevel
{
protected:
	static std::shared_ptr<Graphics> gfx;
	std::unique_ptr<GameTime> time;
	float jumpHight = 100.0f;
	bool jump = false;
	bool mRight = false;
	bool mLeft = false;
	bool onPlatform = false;
public:
	static void Init(std::shared_ptr<Graphics> graphics);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Move(float x, float y) = 0;
	virtual void Jump() = 0;
	virtual void Shot() = 0;
	void EnableJump() { if(onPlatform) jump = true; }
	void EnablemRight() { mRight = true; }
	void EnablemLeft() { mLeft = true; }
	void JumpHeightDefault() { jumpHight = 100.0f; }
};