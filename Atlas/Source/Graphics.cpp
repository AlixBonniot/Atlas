#include "Graphics.h"
#include "Exception.h"

Graphics::Graphics(const int displayWidth, const int displayHeight)
: m_displayWidth{ displayWidth }
, m_displayHeight{ displayHeight }
{
}

void Graphics::Initialize()
{
	Test(DXGI_ERROR_CACHE_CORRUPT);
}

void Graphics::Render()
{
}

void Graphics::Terminate()
{
}

int Graphics::GetDisplayWidth() const
{
	return m_displayWidth;
}

int Graphics::GetDisplayHeight() const
{
	return m_displayHeight;
}
