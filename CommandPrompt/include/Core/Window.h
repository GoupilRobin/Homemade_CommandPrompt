#ifndef Window_h_
#define Window_h_

#include <string>
#include "Event.h"

class Window
{
public:
	Window(const std::string & title, int x, int y, int width, int height, bool fullscreen = true);
	~Window();

	virtual void Create() = 0;
	virtual bool PollEvent() = 0;

	bool IsFullscreen() const { return m_Fullscreen; }
	virtual void SetFullscreen(bool value) { m_Fullscreen = value; }
	const std::string & GetTitle() const { return m_Title; }
	virtual void SetTitle(const std::string & value) { m_Title = value; }

	EventV m_TestEvent;

protected:
	std::string m_Title;
	int m_PosX;
	int m_PosY;
	int m_Width;
	int m_Height;
	bool m_Fullscreen;
};

#endif