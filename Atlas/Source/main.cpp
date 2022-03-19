#include "Application.h"

// WinMain is the entry point for any graphical Windows-based applications
_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	return Application{}.Run(hInstance, nCmdShow);
}