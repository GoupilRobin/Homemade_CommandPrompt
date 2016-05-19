#include "TextSDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_render.h"
#include "FontSDL.h"
#include "RendererSDL.h"

glm::vec2 TextSDL::m_AlignmentOffsets[] = {
	glm::vec2(0.0f, 0.0f),// Left
	glm::vec2(-0.5f, 0.0f),// Center
	glm::vec2(-1.0f, 0.0f),// Right
};

TextSDL::TextSDL(Font * font, const char16_t * str, const Color & color, bool smooth) :
	Text(font, str, color, smooth), m_ColorSDL({ 0xFF, 0xFF, 0xFF, 0xFF }), m_TextSurfaceSDL(0x0), m_CachedFont(0x0), m_CachedFontMonitor(m_CachedFont), m_UpdateRendererTexture(true), m_CachedRendererTexture(0x0)
{
	UpdateCachedFont();
}

TextSDL::~TextSDL()
{
	if (m_TextSurfaceSDL != 0x0)
	{
		SDL_FreeSurface(m_TextSurfaceSDL);
	}
	if (m_CachedRendererTexture != 0x0)
	{
		SDL_DestroyTexture(m_CachedRendererTexture);
	}
}

void TextSDL::Draw(Renderer * renderer)
{
	if (renderer == 0x0 || m_TextSurfaceSDL == 0x0) return;

	if (m_CachedFontMonitor.IsModified())
	{
		UpdateCachedFont();
		m_UpdateRendererTexture = true;
	}

	if (m_CachedRenderer != renderer)
	{
		m_CachedRenderer = renderer;
		m_UpdateRendererTexture = true;
	}

	if (m_UpdateRendererTexture)
	{
		if (m_CachedRendererTexture != 0x0)
		{
			SDL_DestroyTexture(m_CachedRendererTexture);
		}
		m_CachedRendererTexture = SDL_CreateTextureFromSurface(static_cast<const RendererSDL *>(renderer)->m_Renderer, m_TextSurfaceSDL);
		m_UpdateRendererTexture = false;
	}

	SDL_RenderCopy(static_cast<const RendererSDL *>(renderer)->m_Renderer, m_CachedRendererTexture, NULL, &m_RectSDL);
}

void TextSDL::SetFont(Font * font)
{
	Text::SetFont(font);

	UpdateCachedFont();
}

void TextSDL::SetStr(const char16_t * str)
{
	Text::SetStr(str);

	UpdateSize();
	UpdateTextSurface();
	m_UpdateRendererTexture = true;
}

void TextSDL::SetColor(const Color & color)
{
	Text::SetColor(color);

	UpdateColor();
}

void TextSDL::SetPosition(const glm::vec2 & position)
{
	Text::SetPosition(position);

	UpdateRect();
}

void TextSDL::SetScale(const glm::vec2 & scale)
{
	Text::SetScale(scale);

	UpdateSize();
}

void TextSDL::SetAlignment(const Alignment & alignment)
{
	Text::SetAlignment(alignment);

	UpdateRect();
}

void TextSDL::UpdateCachedFont()
{
	m_CachedFont = static_cast<FontSDL *>(m_Font);
	m_CachedFontMonitor.SetTarget(m_CachedFont);
	m_CachedFontMonitor.Update();
	UpdateColor();
	UpdateTextSurface();
	UpdateSize();
}

void TextSDL::UpdateColor()
{
	m_ColorSDL = { (Uint8)(m_Color.GetRed() * 255.0f), (Uint8)(m_Color.GetGreen() * 255.0f), (Uint8)(m_Color.GetBlue() * 255.0f), (Uint8)(m_Color.GetAlpha() * 255.0f) };
	UpdateTextSurface();
}

void TextSDL::UpdateSize()
{
	int width, height;
	TTF_SizeUNICODE(m_CachedFont->m_FontSDL, (Uint16 *)m_Str, &width, &height);
	m_Size.x = width * m_Scale.x;
	m_Size.y = height * m_Scale.y;

	UpdateRect();
}

void TextSDL::UpdateRect()
{
	m_RectSDL = { (int)(m_Position.x + m_Size.x * m_AlignmentOffsets[m_Alignment].x), (int)(m_Position.y + m_Size.y * m_AlignmentOffsets[m_Alignment].y), (int)m_Size.x, (int)m_Size.y };
}

void TextSDL::UpdateTextSurface()
{
	if (m_TextSurfaceSDL != 0x0)
	{
		SDL_FreeSurface(m_TextSurfaceSDL);
		m_TextSurfaceSDL = 0x0;
	}

	if (m_Smooth)
	{
		m_TextSurfaceSDL = TTF_RenderUNICODE_Blended(m_CachedFont->m_FontSDL, (Uint16 *)m_Str, m_ColorSDL);
	}
	else
	{
		m_TextSurfaceSDL = TTF_RenderUNICODE_Solid(m_CachedFont->m_FontSDL, (Uint16 *)m_Str, m_ColorSDL);
	}
}
