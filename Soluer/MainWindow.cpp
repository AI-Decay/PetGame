#include "Graphics.h"
#include <time.h>
#include "Level1.h"
#include "GameController.h"

#pragma comment(lib, "d2d1.lib")

int MainWindowWidth = 800;
int MainWondowHeight = 600;

static int ssseblan = 0;

std::shared_ptr<Graphics> graphics{ new Graphics() };


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			/*case VK_LEFT:
			{
				GameController::Move(-7.0f, 0.0f);
			}
			break;
			case VK_RIGHT:
			{
				GameController::Move(7.0f, 0.0f);
			}
			break;
			case VK_UP:
			{
				GameController::Jump();
			}
			break;
			case VK_SPACE:
			{
				GameController::Shot();
			}
			break;*/
			default:
				break;
			}
			break;
		}

		case WM_KEYUP:
		{

			break;
		}

		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
	}

	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = "MainWindow";

	if (!RegisterClassEx(&wcex))
		return -1;

	RECT rc{ 0, 0, MainWindowWidth, MainWondowHeight };
	AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
	HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW,"MainWindow", "Direct 2D Vid", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
				CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr,	hInstance, nullptr);

	if (!hwnd)
		return -1;
	
	if (!graphics->Init(hwnd))
		return -1;

	GameLevel::Init(graphics);

	ShowWindow(hwnd, nCmdShow);

	std::shared_ptr<GameLevel> a{ new Level1() };
	GameController::LoadInitialLevel(a);

	MSG msg{};
	msg.message = WM_NULL;



	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&msg);
		else
		{
			//Update
			GameController::Update();
			
			//Render
			graphics->BeginDraw();

			GameController::Render();

			graphics->EndDraw();
		}
		
		if (GetAsyncKeyState(VK_LEFT))
		{
			GameController::Move(-5.0f, 0.0f);
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			GameController::Move(5.0f, 0.0f);
		}
		if (GetAsyncKeyState(VK_UP))
		{
			GameController::Jump();
		}
		if(GetAsyncKeyState(VK_SPACE))
		{
			GameController::Shot();
		}
	}


	return 0;
}