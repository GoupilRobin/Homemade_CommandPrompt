#ifndef TextSDL_h_
#define TextSDL_h_

#include "Text.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "VariableMonitor.h"

struct SDL_Surface;
struct SDL_Texture;
class FontSDL;

class TextSDL : public Text
{
public:
	TextSDL(Font * font, const char16_t * str = 0x0, const Color & color = Color::White, bool smooth = true);
	~TextSDL();

	void Draw(Renderer * renderer) override;

	void SetFont(Font * font) override;
	void SetStr(const char16_t * str) override;
	void SetColor(const Color & color) override;
	void SetPosition(const glm::vec2 & position) override;
	void SetScale(const glm::vec2 & scale) override;
	void SetAlignment(const Alignment & alignment) override;

protected:
	void UpdateCachedFont();
	void UpdateColor();
	void UpdateSize();
	void UpdateRect();
	void UpdateTextSurface();

	SDL_Color m_ColorSDL;
	SDL_Surface * m_TextSurfaceSDL;
	SDL_Rect m_RectSDL;
	FontSDL * m_CachedFont;
	VariableMonitor<FontSDL> m_CachedFontMonitor;
	Renderer * m_CachedRenderer;
	SDL_Texture * m_CachedRendererTexture;
	bool m_UpdateRendererTexture;
	static glm::vec2 m_AlignmentOffsets[3];
};

#endif