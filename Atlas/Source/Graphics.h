#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics
{
public:
	Graphics(const int displayWidth, const int displayHeight);

	void Initialize();
	void Render();
	void Terminate();

	int GetDisplayWidth() const;
	int GetDisplayHeight() const;

private:
	int m_displayWidth;
	int m_displayHeight;
};

#endif