#ifndef TextLineSDL_h_
#define TextLineSDL_h_

#include "Text.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "VariableMonitor.h"
#include "Drawable.h"

struct SDL_Surface;
struct SDL_Texture;
class FontSDL;
class TextSDL;

class TextLineSDL : public Drawable
{/*
public:
	~TextLineSDL();

protected:
	TextLineSDL(TextSDL * owner, unsigned int lineCount, const char16_t * str = 0x0);

	void Draw(Renderer * renderer) override;

	void SetStr(const char16_t * str);

	void UpdateTextSurface();
	void UpdateSize();
	void UpdateRect();

	TextSDL * m_Owner;
	unsigned int m_LineCount;
	const char16_t * m_Str;
	SDL_Surface * m_TextSurfaceSDL;
	SDL_Rect m_RectSDL;
	glm::vec2 m_Size;

	Renderer * m_CachedRenderer;
	SDL_Texture * m_CachedRendererTexture;
	bool m_UpdateRendererTexture;

	friend TextSDL;*/
};

#endif