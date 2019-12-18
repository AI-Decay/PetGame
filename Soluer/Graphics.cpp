#include "Graphics.h"

Graphics::Graphics()
	: factory(NULL), renderTarget(NULL), brush(NULL) {};

Graphics::~Graphics() 
{
	if(factory) factory->Release();
	if(renderTarget) renderTarget->Release();
	if(brush) brush->Release();
};

void Graphics::BeginDraw()
{
	renderTarget->BeginDraw();
}

void Graphics::EndDraw()
{
	renderTarget->EndDraw();
}

bool Graphics::Init(HWND windowHandle)
{
	if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory) != S_OK)
		return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);
	if (factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget) != S_OK)
		return false;

	if (renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 1, 0, 0), &brush) != S_OK)
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a)
{
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_RECT_F rectangle = D2D1::RectF(x1, y1, x2, y2);

	renderTarget->FillRectangle(rectangle, brush);
	renderTarget->DrawRectangle(rectangle, brush, 0.0f);
}
