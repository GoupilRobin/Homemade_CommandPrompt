#include "WindowSDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <exception>

int WindowSDL::m_OpenedWindowsCount = 0;
bool WindowSDL::m_SDLInitialized = false;
bool WindowSDL::m_SDLTTFInitialized = false;

WindowSDL::WindowSDL(const std::string & title, int x, int y, int width, int height, bool fullscreen) :
	Window(title, x, y, width, height, fullscreen), m_SDLWindowPtr(0x0)
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
	
	
	if (!m_SDLTTFInitialized)
	{
		int res = TTF_Init();
		if (res != 0)
		{
			throw new std::runtime_error("Could not initialize SDL TTF: " + std::string(SDL_GetError()));
		}
		m_SDLTTFInitialized = true;
	}

	m_OpenedWindowsCount++;
}

WindowSDL::~WindowSDL()
{
	if (m_SDLWindowPtr != 0x0)
	{
		SDL_DestroyWindow(m_SDLWindowPtr);
		m_SDLWindowPtr = 0x0;
	}

	// if this is the last opened window, clean context
	if (m_OpenedWindowsCount == 1)
	{
		if (m_SDLInitialized)
		{
			SDL_Quit();
			m_SDLInitialized = false;
		}
		if (m_SDLTTFInitialized)
		{
			TTF_Quit();
			m_SDLTTFInitialized = false;
		}
	}

	m_OpenedWindowsCount--;
}

void WindowSDL::Create()
{
	int defaultFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
	if (m_Fullscreen)
	{
		defaultFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	m_SDLWindowPtr = SDL_CreateWindow(m_Title.c_str(),
		m_PosX == -1 ? SDL_WINDOWPOS_UNDEFINED : m_PosX,
		m_PosY == -1 ? SDL_WINDOWPOS_UNDEFINED : m_PosY,
		m_Width, m_Height,
		defaultFlags);

	if (m_SDLWindowPtr == NULL)
	{
		throw new std::runtime_error("Could not create SDL window: " + std::string(SDL_GetError()));
	}
}

bool WindowSDL::PollEvent()
{
	int oldPosX = m_PosX;
	int oldPosY = m_PosY;
	int oldWidth = m_Width;
	int oldHeight = m_Height;

	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_SHOWN:
				OnWindowShown.Invoke();
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				OnWindowHidden.Invoke();
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				OnWindowExposed.Invoke();
				break;
			case SDL_WINDOWEVENT_MOVED:
				m_PosX = event.window.data1;
				m_PosY = event.window.data2;
				OnWindowMoved.Invoke(oldPosX, oldPosY, event.window.data1, event.window.data2);
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_Width = event.window.data1;
				m_Height = event.window.data2;
				OnWindowResized.Invoke(oldWidth, oldHeight, event.window.data1, event.window.data2);
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				OnWindowMinimized.Invoke();
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				OnWindowMaximized.Invoke();
				break;
			case SDL_WINDOWEVENT_RESTORED:
				OnWindowRestored.Invoke();
				break;
			case SDL_WINDOWEVENT_ENTER:
				OnMouseEnterWindow.Invoke();
				break;
			case SDL_WINDOWEVENT_LEAVE:
				OnMouseLeaveWindow.Invoke();
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				OnWindowFocusGained.Invoke();
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				OnWindowFocusLost.Invoke();
				break;
			case SDL_WINDOWEVENT_CLOSE:
				OnWindowClosed.Invoke();
				break;
			default:
				std::cerr << "Unknown window event received (" << (int)event.window.event << ")" << std::endl;
				break;
			}
			break;
		case SDL_QUIT:
			OnWindowClosed.Invoke();
			break;
		case SDL_TEXTINPUT:
			OnTextInput.Invoke(event.text.text, (unsigned int)strnlen_s(event.text.text, SDL_TEXTINPUTEVENT_TEXT_SIZE), (unsigned int)event.text.timestamp);
			break;
		case SDL_KEYDOWN:
			OnKeyDown.Invoke(event.key.keysym.sym, (unsigned int)event.key.timestamp);
			break;
		case SDL_KEYUP:
			OnKeyUp.Invoke(event.key.keysym.sym, (unsigned int)event.key.timestamp);
			break;
		}

		return true;
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
