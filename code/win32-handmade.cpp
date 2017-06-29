#include <windows.h>

LRESULT CALLBACK
MainWindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;

	switch(uMsg)
	{
		case WM_SIZE:
		{
			OutputDebugString("WM_SIZE\n");
		} break;

		case WM_DESTROY:
		{
			OutputDebugString("WM_DESTROY\n");
		} break;

		case WM_CLOSE:
		{
			OutputDebugString("WM_CLOSE\n");
		} break;

		case WM_ACTIVATEAPP:
		{
			OutputDebugString("WM_ACTIVATEAPP\n");
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(hwnd, &paint);
			int x = paint.rcPaint.left;
			int y = paint.rcPaint.top;
			int width = paint.rcPaint.right - paint.rcPaint.left;
			int height = paint.rcPaint.bottom - paint.rcPaint.top;
			PatBlt(deviceContext, x, y, width, height, BLACKNESS);
			EndPaint(hwnd, &paint);
		} break;

		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		} break;
	}

	return(result);
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS windowClass = {};
	windowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	windowClass.lpfnWndProc = MainWindowCallback;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = "HandmadeHeroWindowClass";

	if (RegisterClass(&windowClass))
	{
		HWND windowHandle = CreateWindowEx(
		0,
		windowClass.lpszClassName,
		"Handmade Hero",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		hInstance,
		0);

		if (windowHandle)
		{
			for (;;)
			{
				MSG windowMessage;
				BOOL windowMessageResult = GetMessage(&windowMessage, 0, 0, 0);
				if (windowMessageResult > 0)
				{
					TranslateMessage(&windowMessage);
					DispatchMessage(&windowMessage);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			// TODO: logging
		}
	}
	else
	{
		// TODO: logging
	}

	return(0);
}