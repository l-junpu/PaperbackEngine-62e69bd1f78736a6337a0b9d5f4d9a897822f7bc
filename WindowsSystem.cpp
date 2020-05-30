#include "WindowsSystem.h"

WindowsSystem* WindowsSystem::w_Instance = nullptr;

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (MessageBox(hwnd, "Really quit?", "My application", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
			FreeConsole();
		}
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}
}

// Default constructor for WindowsSystem Class
WindowsSystem::WindowsSystem() : wc{}, msg{}, hwnd() {}

void WindowsSystem::Init(HINSTANCE _currentInstance, const char* _windowName, int _x, int _y, LPCSTR _className, HCURSOR _cursor, HBRUSH _bgColor) {
	wc.hInstance = _currentInstance;								// Current instance
	wc.lpszClassName = _className;									// Name of class
	wc.hCursor = _cursor;											// Cursor type (Style)
	wc.hbrBackground = _bgColor;									// Background color of console window
	wc.lpfnWndProc = WindowProcessMessages;							// Process messages (Not done)
	RegisterClass(&wc);												// Register the Windows Class

	hwnd = CreateWindow("MyWindowsSystem", _windowName,				// Name of class, name of console window
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,							// Window style
		CW_USEDEFAULT, CW_USEDEFAULT,								// Window initial position
		_x, _y,														// Window size
		nullptr, nullptr, nullptr, nullptr);
}

void WindowsSystem::ProcessMessage() {
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		// Related to keyboard input
		TranslateMessage(&msg);
		// Tells OS to call winproc
		DispatchMessage(&msg);
	}
}

WindowsSystem* WindowsSystem::Instance() {
	// Create a new WindowsSystem class
	if (!w_Instance)
		w_Instance = new WindowsSystem;
	return w_Instance;
}

void WindowsSystem::UnloadInstance() {
	// Delete WindowsSystem class
	delete w_Instance;
	w_Instance = nullptr;
}