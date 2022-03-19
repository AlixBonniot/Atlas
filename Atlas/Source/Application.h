#ifndef APPLICATION_H
#define APPLICATION_H

#include "appinc.h"

class Application
{
public:
	Application() = default;
	Application(HINSTANCE hInstance, int nCmdShow);

	// Run() will start and run the application
	int Run(HINSTANCE hInstance, int nCmdShow);

	// Initialize() will handle the initializtion of all
	// the necessary components
	void Initialize();

	// Update() and Render() will be called each frame
	// to update and render the scene
	void Update();
	void Render();

	// Terminate() will clean up all the necessary components
	void Terminate();

	// IsDone() will tell if the application is shutting down
	bool IsDone(MSG message) const;

	// Window procedure to handle the message loop
	static LRESULT CALLBACK WindowProc(HWND handleWindow, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND m_handleWindow;

	static constexpr int m_clientWidth{ 1920 };
	static constexpr int m_clientHeight{ 1080 };
};

#endif