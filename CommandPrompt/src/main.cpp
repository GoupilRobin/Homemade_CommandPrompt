#include <iostream>
#include "Window.h"
#include "WindowSDL.h"
#include "Renderer.h"
#include "RendererSDL.h"
#include "Color.h"
#include "Font.h"
#include "FontSDL.h"
#include "Text.h"
#include "TextSDL.h"
#include "TerminalBuffer.h"
#include "Terminal.h"

int main(int argc, char** argv)
{
	bool done = false;
	bool redraw = true;
	Window * window = new WindowSDL("Command Prompt", -1, -1, 640, 480, false);
	window->Create();
	window->OnWindowClosed.AddListener([&done]() { done = true; });
	//window->OnKeyDown.AddListener([](char key, unsigned int timestamp) { std::cout << "[OnKeyDown]" << key << " (" << (int)key << ") @" << timestamp << std::endl; });

	window->OnMouseEnterWindow.AddListener([&redraw]() { redraw = true; });
	window->OnWindowFocusGained.AddListener([&redraw]() { redraw = true; });
	window->OnWindowExposed.AddListener([&redraw]() { redraw = true; });
	window->OnWindowShown.AddListener([&redraw]() { redraw = true; });
	window->OnWindowMoved.AddListener([&redraw](int, int, int, int) { redraw = true; });
	window->OnWindowResized.AddListener([&redraw](int, int, int, int) { redraw = true; });
	window->OnWindowMaximized.AddListener([&redraw]() { redraw = true; });
	window->OnWindowRestored.AddListener([&redraw]() { redraw = true; });

	Renderer * renderer = new RendererSDL((WindowSDL *)window);

	Font * font = new FontSDL("C:/Users/james_D/Git/Homemade_CommandPrompt/CommandPrompt/resources/consola.ttf", 14);
	glm::vec2 monoCharSize;
	font->GetCharacterSize('0', monoCharSize);

	Terminal * terminal = new Terminal(window, 0, font);

	while (!done)
	{
		while (window->PollEvent());

		if (redraw)
		{
			terminal->Draw(renderer);

			renderer->Render();
		}
	}

	delete(terminal);
	delete(font);
	delete(renderer);
	delete(window);

    return 0;
}