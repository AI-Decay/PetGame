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
	float xPosition;
	float yPosition;
	float jumpHight = 120.0f;
	bool jump = false;
public:
	static void Init(std::shared_ptr<Graphics> graphics);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Move(float x, float y) = 0;
	virtual void Jump() = 0;
	virtual void Shot() = 0;
	void EnableJump() { jump = true; }
	std::pair<float, float> GetPosition() const { return { xPosition, yPosition }; }
	void SetPosition(float x, float y) { xPosition = x; yPosition = y; }
};