#include "Level1.h"

void Level1::Load()
{
	frame = 0;
	xPosition = 0.0f;
	yPosition = 200.0f;
	sprites = std::unique_ptr<SpriteSheet>(new SpriteSheet(L"lopata.png", gfx, 120, 150));
	//spritesEnemy = new SpriteSheet(L"sticker.png", gfx, 200, 300);
	enemy = std::unique_ptr<Enemy>(new Enemy(std::unique_ptr<SpriteSheet>(new SpriteSheet(L"sticker.png", gfx, 200, 300)),
	50.f, 60.0f, 3.0f, 40, 10));
	time = std::unique_ptr<GameTime>(new GameTime());
	VectorPlatform.push_back(Platform( 50.0f, 500.0f, 180.0f, 520.0f, false, 0.5f, 0.5f, 0.5f, 1.0f));
	VectorPlatform.push_back(Platform(250.0f, 400.0f, 380.0f, 420.0f, false, 0.5f, 0.5f, 0.5f, 1.0f));
	VectorPlatform.push_back(Platform(450.0f, 300.0f, 580.0f, 320.0f, false, 0.5f, 0.5f, 0.5f, 1.0f));
	VectorPlatform.push_back(Platform(650.0f, 200.0f, 780.0f, 220.0f, true,  0.5f, 0.5f, 0.5f, 1.0f));
}

void Level1::Unload()
{

}

void Level1::Render()
{
	gfx->ClearScreen(0.6f, 0.0f, 1.0f);
	for (auto x : VectorPlatform)
	{
		gfx->DrawRectangle(x.x1, x.y1, x.x2, x.y2, x.r, x.g, x.b, x.a);
	}
	sprites->Draw(frame, xPosition, yPosition);
	if(enemy->loadEnemy)
	enemy->sprites->Draw(enemy->frame, enemy->xPosition, enemy->yPosition);
	for (auto ball : VectorBall)
	{
		if (ball.move)
			gfx->DrawCircle(ball.x, ball.y, ball.radius, 0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Level1::Update()
{
	if (jump)
		Jump();
	else
	yPosition += 2.5f;

	if (enemy->hp == 20)
 		enemy->frame = 1;
	else if (enemy->hp == 5)
		enemy->frame = 2;
	else if (enemy->hp <= 0)
	{
		enemy->loadEnemy = false;
  		enemy->alive = false;
	}

	if(enemy->loadEnemy)
	enemy->Move(250, 0);
	

	for (int i = 0; i < VectorBall.size(); i++)
	{
		if (VectorBall[i].left)
			VectorBall[i].x += 5.0f;
		else
			VectorBall[i].x -= 5.0f;
		if (enemy->loadEnemy && VectorBall[i].x == (enemy->xPosition - static_cast<int>(enemy->xPosition)%5 + 150) && 
			(VectorBall[i].y > enemy->yPosition + 30 && VectorBall[i].y < enemy->yPosition + 270))
		{
			VectorBall.erase(VectorBall.begin() + i);
			enemy->hp--;
		}
		else
		if (VectorBall[i].x > 800 || VectorBall[i].x < -100)
			VectorBall.erase(VectorBall.begin() + i);
	}


	VectorPlatform[3].Move(550, 150);

	for (auto x : VectorPlatform)
	{
		if (yPosition > x.y1 - 130 && xPosition >= x.x1 - 80 && xPosition <= x.x2 - 45)
		{
			yPosition = x.y1 - 130;
			if(VectorPlatform[3].x1 == x.x1 && enemy->alive)
			{ 
				enemy->loadEnemy = true;
			}
		}
		
	}

	if (xPosition > 700) xPosition = 700.0f;
	if (xPosition < -20) xPosition = -20.0f;
}

void Level1::Move(float x, float y)
{
	if (x > 0)
	{
		xPosition += x;
		if (frame != 1)
			frame = 1;
	}
	else
	{
		xPosition += x;
		if (frame)
			frame = 0;
	}
}

void Level1::Jump()
{
	if (jumpHight != 0)
	{
		yPosition -= 2.5f;
		jumpHight -= 2.5;
	}
	else
	{
		jumpHight = 150.0f;
		jump = false;
	}
}

void Level1::Shot()
{
	/*if (VectorBall.empty())
	{
		if (frame)
			VectorBall.push_back(Ball{ xPosition + 85, yPosition + 40, 5, true, true });
		else
			VectorBall.push_back(Ball{ xPosition + 40, yPosition + 40, 5, true, false });
	}
	else
	{
		if ((VectorBall.back().x - xPosition > -100) && frame)
			VectorBall.push_back(Ball{ xPosition + 40, yPosition + 40, 5, true, false });
		else if ((xPosition - VectorBall.back().x > -55) && !frame)
			VectorBall.push_back(Ball{ xPosition + 85, yPosition + 40, 5, true, true });
	}*/


 	if(time->Duration() > 0)
	{
		if (frame)
			VectorBall.push_back(Ball{ xPosition + 85, yPosition + 40, 5, true, true });
		else
			VectorBall.push_back(Ball{ xPosition + 40, yPosition + 40, 5, true, false });

		time->ResetTime();
	}
}