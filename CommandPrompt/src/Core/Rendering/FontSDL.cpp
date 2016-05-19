#include "FontSDL.h"
#include <stdexcept>
#include <string>
#include <glm/vec2.hpp>

FontSDL::FontSDL(char * path, unsigned int size) : Font(path, size)
{
	size_t len = strnlen_s(path, _MAX_PATH);
	m_FontPath = new char[len + 1];
	strcpy_s(m_FontPath, len + 1, path);

	SetSize(size);
}

FontSDL::~FontSDL()
{
	for (int i = 0; i < m_CachedFontDatas.size(); ++i)
	{
		TTF_CloseFont(m_CachedFontDatas[i].Font);
	}

	delete[] m_FontPath;
}

void FontSDL::SetSize(unsigned int size)
{
	Font::SetSize(size);

	for (int i = 0; i < m_CachedFontDatas.size(); ++i)
	{
		if (m_CachedFontDatas[i].Size == m_Size)
		{
			m_FontSDL = m_CachedFontDatas[i].Font;
			return;
		}
	}

	m_FontSDL = TTF_OpenFont(m_FontPath, m_Size);

	if (m_FontSDL == 0x0)
	{
		std::string str = "Could not open font '";
		str.append(m_FontPath).append("'");
		throw new std::runtime_error(str);
	}

	// Restore style
	SetFontStyle(TTF_STYLE_NORMAL, true);
	SetBold(m_Bold);
	SetItalic(m_Italic);
	SetUnderline(m_Underline);
	SetStrikeThrough(m_StrikeThrough);

	int w, h;
	TTF_SizeUNICODE(m_FontSDL, (Uint16 *)u"0", &w, &h);
	m_LineHeight = h;

	m_CachedFontDatas.push_back(FontData(m_FontSDL, m_Size));
}

void FontSDL::SetBold(bool status)
{
	Font::SetBold(status);

	SetFontStyle(TTF_STYLE_BOLD, m_Bold);
}

void FontSDL::SetItalic(bool status)
{
	Font::SetItalic(status);

	SetFontStyle(TTF_STYLE_ITALIC, m_Italic);
}

void FontSDL::SetUnderline(bool status)
{
	Font::SetUnderline(status);

	SetFontStyle(TTF_STYLE_UNDERLINE, m_Underline);
}

void FontSDL::SetStrikeThrough(bool status)
{
	Font::SetStrikeThrough(m_StrikeThrough);

	SetFontStyle(TTF_STYLE_STRIKETHROUGH, status);
}

void FontSDL::GetCharacterSize(const char & c, glm::vec2 & size)
{
	int w, h;
	Uint16 str[2] = { c, '\0' };
	TTF_SizeUNICODE(m_FontSDL, str, &w, &h);
	size.x = w;
	size.y = h;
}

void FontSDL::SetFontStyle(int style, bool status)
{
	int renderStyle = TTF_GetFontStyle(m_FontSDL);
	if (status)
	{
		renderStyle |= style;
	}
	else
	{
		renderStyle &= ~style;
	}
	TTF_SetFontStyle(m_FontSDL, renderStyle);
}
