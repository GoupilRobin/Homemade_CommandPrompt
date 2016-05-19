#ifndef FontSDL_h_
#define FontSDL_h_

#include "Font.h"
#include "SDL2/SDL_ttf.h"
#include <vector>

class TextSDL;
class TextLineSDL;

class FontSDL : public Font
{
public:
	FontSDL(char * path, unsigned int size);
	~FontSDL();

	void SetSize(unsigned int size) override;
	void SetBold(bool status) override;
	void SetItalic(bool status) override;
	void SetUnderline(bool status) override;
	void SetStrikeThrough(bool status) override;
	void GetCharacterSize(const char & c, glm::vec2 & size) override;

protected:
	void SetFontStyle(int style, bool status);

	char * m_FontPath;
	TTF_Font * m_FontSDL;

	struct FontData
	{
		FontData(TTF_Font * font, unsigned int size) : Font(font), Size(size) { }
		TTF_Font * Font;
		unsigned int Size;
	};

	std::vector<FontData> m_CachedFontDatas;

	friend TextSDL;
	friend TextLineSDL;
};

#endif