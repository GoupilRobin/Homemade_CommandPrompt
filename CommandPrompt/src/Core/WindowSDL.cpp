#include "WindowSDL.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include "WindowEvent.h"

bool WindowSDL::m_SDLInitialized = false;
const std::vector<WindowSDL::EventPair> WindowSDL::m_EventsConversion = {
	WindowSDL::EventPair(WindowEvent::QUIT, SDL_QUIT),
	WindowSDL::EventPair(WindowEvent::WINDOW_EVENT, SDL_WINDOWEVENT),
	WindowSDL::EventPair(WindowEvent::KEY_PRESSED, SDL_KEYDOWN),
	WindowSDL::EventPair(WindowEvent::KEY_RELEASED, SDL_KEYUP),
	WindowSDL::EventPair(WindowEvent::MOUSE_MOVED, SDL_MOUSEMOTION),
	WindowSDL::EventPair(WindowEvent::MOUSE_BUTTON_RELEASED, SDL_MOUSEBUTTONDOWN),
	WindowSDL::EventPair(WindowEvent::MOUSE_BUTTON_RELEASED, SDL_MOUSEBUTTONUP),
	WindowSDL::EventPair(WindowEvent::MOUSE_WHEEL_MOTION, SDL_MOUSEWHEEL),
	WindowSDL::EventPair(WindowEvent::CLIPBOARD_UPDATED, SDL_CLIPBOARDUPDATE),
	WindowSDL::EventPair(WindowEvent::FILE_DROPPED, SDL_CLIPBOARDUPDATE),
	WindowSDL::EventPair(WindowEvent::RENDER_TRAGET_RESET, SDL_RENDER_TARGETS_RESET),
};

WindowSDL::WindowSDL(const std::string & title, int x, int y, int width, int height, bool fullscreen) :
	Window(title, x, y, width, height, fullscreen), m_SDLWindowPtr(NULL)
{
	if (!m_SDLInitialized)
	{
		int res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
		if (res != 0)
		{
			throw new std::runtime_error("Could not initialize SDL: " + std::string(SDL_GetError()));
		}
		m_SDLInitialized = true;
	}
}

WindowSDL::~WindowSDL()
{
	if (m_SDLWindowPtr != NULL)
	{
		SDL_DestroyWindow(m_SDLWindowPtr);
	}

	if (m_SDLInitialized)
	{
		SDL_Quit();
		m_SDLInitialized = false;
	}
}

void WindowSDL::Create()
{
	int defaultFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if (m_Fullscreen)
	{
		defaultFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	m_SDLWindowPtr = SDL_CreateWindow(m_Title.c_str(),
		m_PosX,
		m_PosY,
		m_Width, m_Height,
		defaultFlags);

	if (m_SDLWindowPtr == NULL)
	{
		throw new std::runtime_error("Could not create SDL window: " + std::string(SDL_GetError()));
	}
}

bool WindowSDL::PollEvent()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			break;
		}
	}
	return false;
}

void WindowSDL::SetFullscreen(bool value)
{
	if (IsFullscreen() != value)
	{
		Window::SetFullscreen(value);
		if (value)
		{
			SDL_SetWindowFullscreen(GetNativePointer(), SDL_WINDOW_FULLSCREEN);
		}
		else
		{
			SDL_SetWindowFullscreen(GetNativePointer(), 0);
		}
	}
}

void WindowSDL::SetTitle(const std::string & value)
{
	Window::SetTitle(value);
	SDL_SetWindowTitle(GetNativePointer(), value.c_str());
}

Uint32 WindowSDL::ConvertSDL_EventType(Uint32 evtype)
{
	for (int i = 0; i < m_EventsConversion.size(); ++i)
	{
		if (m_EventsConversion[i].eventSDLType == evtype)
		{
			return m_EventsConversion[i].eventType;
		}
	}

	return -1;
}
