#ifndef Window_h_
#define Window_h_

#include <string>
#include "Event.h"

class Window
{
public:
	Window(const std::string & title, int x, int y, unsigned int width, unsigned int height, bool fullscreen = true) : m_Title(title), m_PosX(x), m_PosY(y), m_Width(width), m_Height(height), m_Fullscreen(fullscreen) {}
	virtual ~Window() {}

	virtual void Create() = 0;
	virtual bool PollEvent() = 0;

	virtual void SetFullscreen(bool value) { m_Fullscreen = value; }
	virtual void SetTitle(const std::string & value) { m_Title = value; }
	virtual bool IsFullscreen() const { return m_Fullscreen; }
	virtual const std::string & GetTitle() const { return m_Title; }
	virtual const unsigned int GetPosX() const { return m_PosX; }
	virtual const unsigned int GetPosY() const { return m_PosY; }
	virtual const unsigned int GetWidth() const { return m_Width; }
	virtual const unsigned int GetHeight() const { return m_Height; }

	EventV OnWindowShown;
	EventV OnWindowHidden;
	EventV OnWindowExposed;
	Event<int, int, int, int> OnWindowMoved; // fromX, fromY, toX, toY
	Event<int, int, int, int> OnWindowResized; // fromX, fromY, toX, toY
	EventV OnWindowMinimized;
	EventV OnWindowMaximized;
	EventV OnWindowRestored;
	EventV OnMouseEnterWindow;
	EventV OnMouseLeaveWindow;
	EventV OnWindowFocusGained;
	EventV OnWindowFocusLost;
	EventV OnWindowClosed;
	Event<char *, unsigned int, unsigned int> OnTextInput;
	Event<char, unsigned int> OnKeyDown;
	Event<char, unsigned int> OnKeyUp;

protected:
	std::string m_Title;
	int m_PosX;
	int m_PosY;
	int m_Width;
	int m_Height;
	bool m_Fullscreen;
};

#endif