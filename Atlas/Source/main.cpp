#include <cassert>
#include <windows.h>

// WindowProc is the procedure called every time
// application receives a message
LRESULT CALLBACK WindowProc(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// TO-DO: proper application closing when we hit ESCAPE
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;
	// Message sent when the window is being destroyed
	case WM_DESTROY:
		// We indicate to the system that there is a request to terminate (quit)
		PostQuitMessage(0);
		break;

	// Default window procedure
	default:
		return DefWindowProc(handleWindow, message, wParam, lParam);
	}

	return 0;
}

// WinMain is the entry point for any graphical Windows-based applications
_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	constexpr wchar_t className[]{ L"Atlas" };
	constexpr wchar_t windowName[]{ L"Atlas Engine" };
	constexpr int clientWidth{ 1920 };
	constexpr int clientHeight{ 1080 };

	// We first create a window class and register it
	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	windowClass.lpszClassName = className;
	windowClass.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	assert(RegisterClassEx(&windowClass) != 0 && "Unable to register the window class");

	// We compute the desired client window size
	RECT clientWindow{ 0, 0, clientWidth, clientHeight };
	AdjustWindowRect(&clientWindow, WS_OVERLAPPEDWINDOW, FALSE);

	const int screenWidth{ GetSystemMetrics(SM_CXSCREEN) };
	const int screenHeight{ GetSystemMetrics(SM_CYSCREEN) };

	// We create a window and return an handle to it
	HWND handleWindow = CreateWindow(
		className, windowName, WS_OVERLAPPEDWINDOW, 
		(screenWidth / 2) - (clientWidth / 2), (screenHeight / 2) - (clientHeight / 2),
		clientWindow.right - clientWindow.left, clientWindow.bottom - clientWindow.top,
		nullptr, nullptr, hInstance, nullptr
	);

	// Safety check
	if (handleWindow == nullptr)
	{
		return 0;
	}

	// We show the window
	ShowWindow(handleWindow, nCmdShow);

	/** Game loop **/
	MSG message{};

	// We handle the case when the user quit the application
	while (message.message != WM_QUIT)
	{
		// We dispatch incoming messages
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			// We translate virtual-key messages into character messages
			TranslateMessage(&message);
			// We dispatch the messages to the window procedure
			DispatchMessage(&message);
		}
	}

	// If the application exits with WM_QUIT message
	// we return the exit value contained in the wParam parameter
	return static_cast<char>(message.wParam);
}