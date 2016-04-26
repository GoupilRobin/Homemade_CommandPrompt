#include "Window.h"

#include "WindowEvent.h"

Window::Window(const std::string & title, int x, int y, int width, int height, bool fullscreen) :
	m_Title(title), m_PosX(x), m_PosY(y), m_Width(width), m_Height(height), m_Fullscreen(fullscreen)
{
}

Window::~Window()
{
}
