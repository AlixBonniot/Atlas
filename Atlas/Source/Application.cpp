#include "Application.h"

#include <cassert>

Application::Application(HINSTANCE hInstance, int nCmdShow)
: m_handleWindow{}
{
}

int Application::Run(HINSTANCE hInstance, int nCmdShow)
{
	constexpr wchar_t className[]{ L"Atlas" };
	constexpr wchar_t windowName[]{ L"Atlas Engine" };

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
	RECT clientWindow{ 0, 0, m_clientWidth, m_clientHeight };
	AdjustWindowRect(&clientWindow, WS_OVERLAPPEDWINDOW, FALSE);

	const int screenWidth{ GetSystemMetrics(SM_CXSCREEN) };
	const int screenHeight{ GetSystemMetrics(SM_CYSCREEN) };

	// We create a window and return an handle to it
	HWND handleWindow = CreateWindow(
		className, windowName, WS_OVERLAPPEDWINDOW,
		(screenWidth / 2) - (m_clientWidth / 2), (screenHeight / 2) - (m_clientHeight / 2),
		clientWindow.right - clientWindow.left, clientWindow.bottom - clientWindow.top,
		nullptr, nullptr, hInstance, nullptr
	);

	// Safety check
	if (handleWindow == nullptr)
	{
		return 0;
	}

	// We initialize the application
	Initialize();

	// We show the window
	ShowWindow(handleWindow, nCmdShow);

	/** Game loop **/
	MSG message{};
	while (!IsDone(message))
	{
		// We handle the case when the user quit the application
		if (message.message == WM_QUIT)
		{
			break;
		}

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

void Application::Initialize()
{
}

void Application::Update()
{
}

void Application::Render()
{
}

void Application::Terminate()
{
}

bool Application::IsDone(MSG message) const
{
	// We hit the application when the user hit ESCAPE
	return message.wParam == VK_ESCAPE;
}

// WindowProc is the procedure called every time
// application receives a message
LRESULT Application::WindowProc(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
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
