// Project1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Project1.h"
#include "resource.h"
#include "CBlock.h"
#include "CTetris.h"


#define BLOCK_DOWN_TIMER 1
#define BLOCK_AI_TIMER	2
#define BLOCK_DOWN_SPEED 500


#define MAX_LOADSTRING 100

// 全局变量:


CTetris* pTetris = nullptr;
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。
	//srand((unsigned)time(NULL));



	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT1));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		600, 300, (COL + 11) * WIDTH, (ROW + 2) * HEIGHT, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
	{
		switch (wParam)
		{
		case BLOCK_DOWN_TIMER:
		{
			if (pTetris)
			{
				if (pTetris->BlockDown() == -1)
				{
					PostQuitMessage(0);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
		}
		break;
		case BLOCK_AI_TIMER:
		{

			if (pTetris)
			{
				int nShape = 0;
				int nMove = 0;
				pTetris->BlockRoateAndMove(&nShape, &nMove);
				if (nShape)
				{
					//发送旋转信号
					PostMessage(hWnd, WM_KEYDOWN, VK_UP, 0);
				}
				else
				{
					if (nMove < 0)
					{
						//发送向左信号
						PostMessage(hWnd, WM_KEYDOWN, VK_LEFT, 0);
					}
					else if (nMove > 0)
					{
						//发送向右信号
						PostMessage(hWnd, WM_KEYDOWN, VK_RIGHT, 0);
					}
				}

			}
			return 0;
		}
		break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case VK_UP:
		{

			if (pTetris)
			{
				pTetris->BlockRotate();
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case VK_DOWN:
		{

			if (pTetris)
			{
				if (pTetris->BlockDown() == -1)
				{
					PostQuitMessage(0);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case VK_LEFT:
		{
			if (pTetris)
			{
				pTetris->BlockLeft();
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case VK_RIGHT:
		{

			if (pTetris)
			{
				pTetris->BlockRight();
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case MENU_START:
		{
			if (pTetris)
			{
				delete pTetris;
				pTetris = nullptr;
			}
			pTetris = new CTetris();
			if (pTetris)
			{
				pTetris->InitGame();
				SetTimer(hWnd, BLOCK_DOWN_TIMER, BLOCK_DOWN_SPEED, NULL);

			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		case MENU_PAUSE:
		{
			MessageBox(0, "MENU_PAUSE", "Menu", MB_OKCANCEL);
		}
		break;
		case MENU_EXIT:
		{
			DestroyWindow(hWnd);
			break;
		}
		break;
		case MENU_AI:
		{

			KillTimer(hWnd, BLOCK_DOWN_TIMER);
			SetTimer(hWnd, BLOCK_DOWN_TIMER, BLOCK_DOWN_SPEED/5, NULL);
			SetTimer(hWnd, BLOCK_AI_TIMER, BLOCK_DOWN_SPEED/5, NULL);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		if (pTetris)
		{
			pTetris->ShowGame(hdc);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, BLOCK_DOWN_TIMER);
		KillTimer(hWnd, BLOCK_AI_TIMER);
		PostQuitMessage(0);

	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
