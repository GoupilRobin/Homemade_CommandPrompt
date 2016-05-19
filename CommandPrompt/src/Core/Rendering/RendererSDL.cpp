#include "RendererSDL.h"
#include <SDL2/SDL.h>
#include "WindowSDL.h"
#include "Color.h"
#include "Text.h"
#include "Drawable.h"

RendererSDL::RendererSDL(Window * window) : Renderer(window)
{
	m_Renderer = SDL_CreateRenderer(static_cast<WindowSDL *>(window)->m_SDLWindowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_PreviousColor = Color(Color::Black);
}

RendererSDL::~RendererSDL()
{
	if (m_Renderer != 0x0)
	{
		SDL_DestroyRenderer(m_Renderer);
	}
}

void RendererSDL::Clear(const Color & color)
{
	if (color != m_PreviousColor)
	{
		m_PreviousColor = color;

		Uint8 r = (Uint8)(color.GetRed() * 255.0f);
		Uint8 g = (Uint8)(color.GetGreen() * 255.0f);
		Uint8 b = (Uint8)(color.GetBlue() * 255.0f);
		Uint8 a = (Uint8)(color.GetAlpha() * 255.0f);
		SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
	}

	SDL_RenderClear(m_Renderer);
}

void RendererSDL::Draw(Drawable * text)
{
	text->Draw(this);
}

void RendererSDL::Render()
{
	SDL_RenderPresent(m_Renderer);
}
