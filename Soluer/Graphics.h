#pragma once
#include <memory>
#include <Windows.h>
#include <d2d1.h>

class Graphics
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
public:
	Graphics();
	~Graphics();

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }

	bool Init(HWND windowHandle);

	void BeginDraw();

	void EndDraw();

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
};