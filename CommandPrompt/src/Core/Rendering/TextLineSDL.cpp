/*#include "TextLineSDL.h"
#include "TextSDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_render.h"
#include "FontSDL.h"
#include "RendererSDL.h"

TextLineSDL::TextLineSDL(TextSDL * owner, unsigned int lineCount, const char16_t * str) :
	m_Owner(owner), m_LineCount(lineCount), m_TextSurfaceSDL(0x0), m_CachedRenderer(0x0), m_CachedRendererTexture(0x0)
{
	SetStr(str);
}

TextLineSDL::~TextLineSDL()
{
	if (m_TextSurfaceSDL != 0x0)
	{
		SDL_FreeSurface(m_TextSurfaceSDL);
		m_TextSurfaceSDL = 0x0;
	}

	if (m_CachedRendererTexture != 0x0)
	{
		SDL_DestroyTexture(m_CachedRendererTexture);
		m_CachedRendererTexture = 0x0;
	}
}

void TextLineSDL::Draw(Renderer * renderer)
{
	if (renderer == 0x0 || m_TextSurfaceSDL == 0x0) return;

	if (m_CachedRenderer != renderer)
	{
		m_CachedRenderer = renderer;
		m_UpdateRendererTexture = true;
	}

	if (m_UpdateRendererTexture)
	{
		SDL_DestroyTexture(m_CachedRendererTexture);
		m_CachedRendererTexture = SDL_CreateTextureFromSurface(static_cast<const RendererSDL *>(renderer)->m_Renderer, m_TextSurfaceSDL);
		m_UpdateRendererTexture = false;
	}

	SDL_RenderCopy(static_cast<const RendererSDL *>(renderer)->m_Renderer, m_CachedRendererTexture, NULL, &m_RectSDL);
}

void TextLineSDL::SetStr(const char16_t * str)
{
	m_Str = str;

	UpdateSize();
	UpdateTextSurface();
	m_UpdateRendererTexture = true;
}

void TextLineSDL::UpdateSize()
{
	int width, height;
	TTF_SizeUNICODE(m_Owner->m_CachedFont->m_FontSDL, (Uint16 *)m_Str, &width, &height);
	m_Size.x = width * m_Owner->m_Scale.x;
	m_Size.y = height * m_Owner->m_Scale.y;

	UpdateRect();
}

void TextLineSDL::UpdateRect()
{
	m_RectSDL = {
		(int)(m_Owner->m_Position.x + m_Size.x * m_Owner->m_AlignmentOffsets[m_Owner->m_Alignment].x),
		(int)(m_Owner->m_Position.y + m_Size.y * m_Owner->m_AlignmentOffsets[m_Owner->m_Alignment].y + m_Size.y * m_LineCount),
		(int)m_Size.x,
		(int)m_Size.y
	};
}

void TextLineSDL::UpdateTextSurface()
{
	if (m_TextSurfaceSDL != 0x0)
	{
		SDL_FreeSurface(m_TextSurfaceSDL);
		m_TextSurfaceSDL = 0x0;
	}

	if (m_Owner->m_Smooth)
	{
		m_TextSurfaceSDL = TTF_RenderUNICODE_Blended(m_Owner->m_CachedFont->m_FontSDL, (Uint16 *)m_Str, m_Owner->m_ColorSDL);
	}
	else
	{
		m_TextSurfaceSDL = TTF_RenderUNICODE_Solid(m_Owner->m_CachedFont->m_FontSDL, (Uint16 *)m_Str, m_Owner->m_ColorSDL);
	}
}
*/