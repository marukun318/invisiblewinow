#include	<windows.h>

const char *strClassName = "UnvisibleWindowClass";
const char *strTitle= " UnvisibleWindow";

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ウィンドウクラスの登録
	WNDCLASSEX wcex = { };
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= WS_EX_NOACTIVATE;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = nullptr;
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= strClassName;
	wcex.hIconSm		= nullptr;

	if(!RegisterClassEx(&wcex)) return 0;

	// ウィンドウ作成
	HWND hwnd;
	hwnd = CreateWindowEx(WS_EX_NOACTIVATE, strClassName , strTitle, WS_DISABLED /*WS_OVERLAPPEDWINDOW*/,
			0, 0, 1, 1,
			nullptr, nullptr, hInstance, nullptr);
	if (!hwnd) return 0;

	ShowWindow(hwnd, SW_HIDE); // Window非表示

	// メッセージループ
	MSG msg = { };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ここにメインタスクの処理を書く
			// 更新時間を計ったりする
			Sleep(1);		// dummy
		}
	}

	return msg.wParam;
}
