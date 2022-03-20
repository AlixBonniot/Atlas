#include "Application.h"
#include "Exception.h"

// WinMain is the entry point for any graphical Windows-based applications
_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	try
	{
		return Application{}.Run(hInstance, nCmdShow);
	}
	catch (const Exception& exception)
	{
		MessageBoxA(nullptr, exception.GetExceptionMessage(), exception.what(), MB_OK);
	}

	return -1;
}