#include <iostream>
#include "Window.h"
#include "WindowSDL.h"

#include <SDL2/SDL.h>

int main(int argc, char** argv)
{
	Window * window = new WindowSDL("Command Prompt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, false);
	window->Create();
	window->m_TestEvent.AddListener([] { std::cout << "HELLO WORLD!" << std::endl; });
	window->m_TestEvent.Invoke();

	bool done = false;

	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			}
		}
	}

	window->m_TestEvent.Invoke();
	delete(window);

    return 0;
}