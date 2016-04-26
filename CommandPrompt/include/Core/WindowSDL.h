#ifndef WindowSDL_h_
#define WindowSDL_h_

#include "Window.h"
#include <SDL2/SDL_stdinc.h>
#include <vector>

struct SDL_Window;
class WindowEvent;

class WindowSDL : public Window
{
public:
	WindowSDL(const std::string & title, int x, int y, int width, int height, bool fullscreen = true);
	~WindowSDL();

	void Create() override;
	bool PollEvent();
	SDL_Window * GetNativePointer() const { return m_SDLWindowPtr; }
	virtual void SetFullscreen(bool value) override;
	virtual void SetTitle(const std::string & value) override;

protected:
	SDL_Window * m_SDLWindowPtr;

	static bool m_SDLInitialized;

protected:
	class EventPair
	{
	public:
		EventPair(Uint32 event, Uint32 sdlEvent) : eventType(event), eventSDLType(sdlEvent) { }

		Uint32 eventType;
		Uint32 eventSDLType;
	};

	static const std::vector<EventPair> m_EventsConversion;
	Uint32 ConvertSDL_EventType(Uint32 evtype);
};

#endif