#ifndef WindowSDL_h_
#define WindowSDL_h_

#include "Window.h"
#include <SDL2/SDL_stdinc.h>
#include <vector>

struct SDL_Window;
class RendererSDL;

class WindowSDL : public Window
{
public:
	WindowSDL(const std::string & title, int x, int y, int width, int height, bool fullscreen = true);
	~WindowSDL();

	void Create() override;
	bool PollEvent() override;
	SDL_Window * GetNativePointer() const { return m_SDLWindowPtr; }
	virtual void SetFullscreen(bool value) override;
	virtual void SetTitle(const std::string & value) override;

protected:
	SDL_Window * m_SDLWindowPtr;

	static int m_OpenedWindowsCount;
	static bool m_SDLInitialized;
	static bool m_SDLTTFInitialized;

	friend RendererSDL;
};

#endif